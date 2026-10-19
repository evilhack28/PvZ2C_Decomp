//
//  PopAnim.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//

#include "SexyAppFramework/Common.h"
#include "PopAnim.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/MemoryImage.h"
#include "SexyAppFramework/DeviceImage.h"
#include "SexyAppFramework/Buffer.h"
#include "SexyAppFramework/PopAnimListener.h"
#include "ReflectionBuilder.h"

using namespace Sexy;

void AffineMatrixMultiply2d(PopTransformMatrix* theResult, const PopTransformMatrix* theA, const PopTransformMatrix* theB);

struct BlendSrcData
{
	PATransform mTransform;
	Color mColor;
};

/////////////// Lifecycle ///////////////

PopAnim::PopAnim(int theId, PopAnimListener* theListener)
	: mAdditive(false)
{
	mId = theId;
	mListener = theListener;
	mColor = Color(Color::White);
	mAnimRate = 0;
	mAnimRunning = false;
	mMainSpriteInst = NULL;
	mMainAnimDef = NULL;
	Clear();
	mPaused = false;
	mTransDirty = true;
	mImgScale = 1.0f;
	mDrawScale = 1.0f;
	mBlendTicksTotal = 0.0f;
	mBlendTicksCur = 0.0f;
	mBlendDelay = 0.0f;
}

PopAnim::PopAnim(const PopAnim& rhs)
{
	*this = rhs;
	mMainSpriteInst = new PASpriteInst();
	mMainSpriteInst->mDef = NULL;
	mMainSpriteInst->mParent = NULL;
	mMainAnimDef->mRefCount++;
}

PopAnim::~PopAnim()
{
	Clear();
}

PopAnim* PopAnim::Duplicate() const
{
	return new PopAnim(*this);
}

void PopAnim::Clear()
{
	mColor = Color(Color::White);
	mAnimRunning = false;
	mAnimRate = 0;
	if (mMainAnimDef != NULL)
	{
		if (mMainAnimDef->mRefCount != 0)
			mMainAnimDef->mRefCount--;
		else
		{
			mMainAnimDef->mSpriteDefVector.clear();
			delete mMainAnimDef;
		}
	}
	mMainAnimDef = NULL;
	mTransDirty = true;
	delete mMainSpriteInst;
	mMainSpriteInst = NULL;
}

/////////////// Accessors ///////////////

bool PopAnim::IsActive() const
{
	return mAnimRunning;
}

void PopAnim::SetPAMColor(const Color& theColor)
{
	mColor = theColor;
}

int PopAnim::GetLabelFrame(const std::string& theFrameLabel)
{
	return mMainAnimDef->mMainSpriteDef->GetLabelFrame(theFrameLabel);
}

bool PopAnim::Fail(const std::string& theError)
{
	mMainAnimDef->mError = theError;
	return false;
}

void PopAnim::ResetAnim()
{
	ResetAnimHelper(mMainSpriteInst);
	mAnimRunning = false;
	mBlendTicksTotal = 0.0f;
	mBlendTicksCur = 0.0f;
	mBlendDelay = 0.0f;
}

void PopAnim::AnimUpdate(float i_increment)
{
	IncSpriteInstFrame(mMainSpriteInst, NULL, i_increment);
	PrepSpriteInstFrame(mMainSpriteInst, NULL);
}

void PopAnim::DrawDebugOverlayForSprite(Graphics* i_g, PASpriteInst* i_sprite, PATransform* i_parentTransform, int i_depth)
{
}

/////////////// Loading ///////////////

void PopAnim::Load_Init()
{
	Clear();
}

bool PopAnim::LoadFile(const std::string& theFileName)
{
	Load_Init();

	std::string aExt;
	int aDotPos = theFileName.rfind('.');
	if (aDotPos != -1)
		aExt = Lower(theFileName.substr(aDotPos));

	return Load_LoadPam(theFileName);
}

bool PopAnim::Load_LoadPam(const std::string& theFileName)
{
	bool aResult = false;
	if (mMainAnimDef == NULL)
	{
		mMainSpriteInst = new PASpriteInst();
		mMainSpriteInst->mParent = NULL;
		mMainSpriteInst->mDef = NULL;

		mMainAnimDef = new PopAnimDef();
		mMainAnimDef->mLoadedPamFile = theFileName;

		Buffer aBuffer;
		std::string aPamFileDir = GetFileDir(theFileName);
		aResult = gSexyAppBase->ReadBufferFromFile(theFileName, &aBuffer, true);
		if (!aResult)
		{
			aResult = Fail("Unable to load file: " + theFileName);
		}
		else if (aBuffer.ReadInt32() != 0xBAF01954)
		{
			aResult = Fail("Invalid header");
		}
		else
		{
			mMainAnimDef->mVersion = aBuffer.ReadInt32();
			if ((unsigned)mMainAnimDef->mVersion >= 7)
			{
				aResult = Fail("Invalid version");
			}
			else
			{
				mAnimRate = aBuffer.ReadByte();
				mAnimRect.mX = aBuffer.ReadInt16() / 20;
				mAnimRect.mY = aBuffer.ReadInt16() / 20;
				mAnimRect.mWidth = (uint16)aBuffer.ReadInt16() / 20;
				mAnimRect.mHeight = (uint16)aBuffer.ReadInt16() / 20;

				int aNumImages = aBuffer.ReadInt16();
				mMainAnimDef->mImageVector.resize(aNumImages);
				for (int anImageNum = 0; anImageNum < aNumImages; anImageNum++)
				{
					PAImage* aPAImage = &mMainAnimDef->mImageVector[anImageNum];
					aPAImage->mImage = NULL;
					aPAImage->mDrawMode = 0;

					std::string aName = aBuffer.ReadString();
					std::string aFlags;

					int aParenStart = aName.find('(');
					int aParenEnd = aName.find(')');
					if (!(aParenStart == -1 || aParenEnd == -1 || aParenEnd <= aParenStart)) {
						aFlags = Lower(aName.substr(aParenStart + 1, aParenEnd - aParenStart - 1));
						aName = Trim(aName.substr(0, aParenStart) + aName.substr(aParenEnd + 1));
					} else {
						int aDollarPos = aName.find('$');
						if (aDollarPos != -1)
						{
							aFlags = Lower(aName.substr(0, aDollarPos));
							aName = Trim(aName.substr(aDollarPos + 1));
						}
					}

					aPAImage->mCols = 1;
					aPAImage->mRows = 1;
					int aBracketStart = aName.find('[');
					int aBracketEnd = aName.find(']');
					if (aBracketStart != -1 && aBracketEnd != -1 && aBracketStart < aBracketEnd)
					{
						std::string aGrid = Lower(aName.substr(aBracketStart + 1, aBracketEnd - aBracketStart - 1));
						aName = Trim(aName.substr(0, aBracketStart) + aName.substr(aBracketEnd + 1));
						int aCommaPos = aGrid.find(',');
						if (aCommaPos != -1)
						{
							aPAImage->mCols = atoi(aGrid.substr(0, aCommaPos).c_str());
							aPAImage->mRows = atoi(aGrid.substr(aCommaPos + 1).c_str());
						}
					}

					if (aFlags.find("add") != std::string::npos)
						aPAImage->mDrawMode = 1;

					if (mMainAnimDef->mVersion < 4)
					{
						aPAImage->mOrigWidth = -1;
						aPAImage->mOrigHeight = -1;
					}
					else
					{
						aPAImage->mOrigWidth = aBuffer.ReadInt16();
						aPAImage->mOrigHeight = aBuffer.ReadInt16();
					}

					if (mMainAnimDef->mVersion == 1)
					{
						float aRot = aBuffer.ReadInt16() * 0.001f;
						float aSin = sinf(aRot);
						float aCos = cosf(aRot);
						aPAImage->mTransform.mMatrix.m00 = aCos;
						aPAImage->mTransform.mMatrix.m10 = aSin;
						aPAImage->mTransform.mMatrix.m11 = aCos;
						aPAImage->mTransform.mMatrix.m01 = -aSin;
					}
					else
					{
						aPAImage->mTransform.mMatrix.m00 = (aBuffer.ReadInt32() * 7.6293945e-7f) / mImgScale;
						aPAImage->mTransform.mMatrix.m01 = (aBuffer.ReadInt32() * 7.6293945e-7f) / mImgScale;
						aPAImage->mTransform.mMatrix.m10 = (aBuffer.ReadInt32() * 7.6293945e-7f) / mImgScale;
						aPAImage->mTransform.mMatrix.m11 = (aBuffer.ReadInt32() * 7.6293945e-7f) / mImgScale;
					}
					aPAImage->mTransform.mMatrix.m02 = aBuffer.ReadInt16() * 0.05f;
					aPAImage->mTransform.mMatrix.m12 = aBuffer.ReadInt16() * 0.05f;

					aPAImage->mImageName = aName;
					if (aPAImage->mImageName.length() == 0) {
						MixedImagePtr anImage;
						bool aIsNew = false;
						gSexyAppBase->mResourceManager->GetImage(anImage, "!whitepixel", NULL, &aIsNew);
						if (aIsNew)
						{
							MemoryImage* aMemImage = ((Image*)anImage)->Cast<MemoryImage>();
							aMemImage->Create(1, 1);
							aMemImage->SetImageMode(false, false);
							*aMemImage->GetBits(0, 0) = 0xFFFFFFFF;
							aMemImage->CommitBits();
						}
						aPAImage->mImage = ((Image*)anImage)->Cast<DeviceImage>();
					} else {
						int aPos = 0;
						while ((int)aName.length() > aPos)
						{
							int aCommaPos = aName.find(',', aPos);
							if (aCommaPos == -1)
							{
								Load_GetImage(aPAImage, aPamFileDir, aName.substr(aPos));
								break;
							}
							std::string aOrigName = aName.substr(aPos, aCommaPos - aPos);
							aPos = aCommaPos + 1;
							Load_GetImage(aPAImage, aPamFileDir, aOrigName);
						}
					}

					if (mMainAnimDef->mError.length() != 0)
					{
						aResult = false;
						goto done;
					}
				}

				int aNumSprites = aBuffer.ReadInt16();
				mMainAnimDef->mSpriteDefVector.resize(aNumSprites);
				for (int aSpriteNum = 0; aSpriteNum < aNumSprites; aSpriteNum++)
				{
					if (!LoadSpriteDef(&aBuffer, &mMainAnimDef->mSpriteDefVector[aSpriteNum]))
					{
						aResult = false;
						goto done;
					}
				}

				if (mMainAnimDef->mVersion < 4 || aBuffer.ReadBoolean())
				{
					mMainAnimDef->mMainSpriteDef = new PASpriteDef();
					if (!LoadSpriteDef(&aBuffer, mMainAnimDef->mMainSpriteDef))
					{
						aResult = false;
						goto done;
					}
				}

				mMainAnimDef->mLoaded = true;
			}
		}
	}

done:
	return aResult;
}

bool PopAnim::LoadSpriteDef(Buffer* theBuffer, PASpriteDef* theSpriteDef)
{
	IntToPAObjectPosMap aCurObjectPosMap;
	std::map<int, int> aCurObjectPosIndexMap;

	theSpriteDef->mObjectPosVector.reserve(512);
	theSpriteDef->mObjectDefVector.reserve(64);

	if (mMainAnimDef->mVersion > 5)
		theSpriteDef->mExportName = theBuffer->ReadString();

	if (mMainAnimDef->mVersion < 4)
	{
		theSpriteDef->mName = NULL;
		theSpriteDef->mAnimRate = (float)mAnimRate;
	}
	else
	{
		mMainAnimDef->mObjectNamePool.push_back(theBuffer->ReadString());
		theSpriteDef->mName = mMainAnimDef->mObjectNamePool.back().c_str();
		theSpriteDef->mAnimRate = theBuffer->ReadInt32() * 1.5258789e-5f;
	}

	int aNumFrames = theBuffer->ReadInt16();
	if (mMainAnimDef->mVersion >= 5)
	{
		theSpriteDef->mWorkAreaStart = theBuffer->ReadInt16();
		theSpriteDef->mWorkAreaDuration = theBuffer->ReadInt16();
	}
	else
	{
		theSpriteDef->mWorkAreaStart = 0;
		theSpriteDef->mWorkAreaDuration = aNumFrames - 1;
	}
	theSpriteDef->mWorkAreaDuration = std::min(theSpriteDef->mWorkAreaStart + theSpriteDef->mWorkAreaDuration, aNumFrames - 1) - theSpriteDef->mWorkAreaStart;

	theSpriteDef->mFrames.resize(aNumFrames);
	for (int aFrameNum = 0; aFrameNum < aNumFrames; aFrameNum++)
	{
		PAFrame* aFrame = &theSpriteDef->mFrames[aFrameNum];
		uint8 aFlags = theBuffer->ReadByte();

		if (aFlags & 1)
		{
			int aNumRemoves = theBuffer->ReadByte();
			if (aNumRemoves == 255)
				aNumRemoves = theBuffer->ReadInt16();

			for (int i = 0; i < aNumRemoves; i++)
			{
				int anObjectId = theBuffer->ReadInt16();
				if (anObjectId >= 2047)
					anObjectId = theBuffer->ReadInt32();

				std::map<int, int>::iterator anIndexFindItr = aCurObjectPosIndexMap.find(anObjectId);
				if (anIndexFindItr != aCurObjectPosIndexMap.end())
					aCurObjectPosIndexMap.erase(anIndexFindItr);

				IntToPAObjectPosMap::iterator aPosFindItr = aCurObjectPosMap.find(anObjectId);
				if (aPosFindItr != aCurObjectPosMap.end())
					aCurObjectPosMap.erase(aPosFindItr);
			}
		}

		std::vector<int> aFrameObjectIds;

		if (aFlags & 2)
		{
			int aNumAdds = theBuffer->ReadByte();
			if (aNumAdds == 255)
				aNumAdds = theBuffer->ReadInt16();

			for (int i = 0; i < aNumAdds; i++)
			{
				PAObjectPos anObjectPos;
				uint16 aWord = theBuffer->ReadInt16();
				anObjectPos.mObjectNum = aWord & 2047;
				if (anObjectPos.mObjectNum == 2047)
					anObjectPos.mObjectNum = theBuffer->ReadInt32();
				anObjectPos.mIsSprite = (aWord >> 15) & 1;
				anObjectPos.mIsAdditive = (aWord >> 14) & 1;

				anObjectPos.mResNum = theBuffer->ReadByte();
				if (anObjectPos.mResNum == 255)
					anObjectPos.mResNum = theBuffer->ReadInt16();

				anObjectPos.mRed = 255;
				anObjectPos.mGreen = 255;
				anObjectPos.mBlue = 255;
				anObjectPos.mAlpha = 255;

				if (aWord & 8192)
					theBuffer->ReadInt16();

				const char* aName = NULL;
				if (aWord & 4096)
				{
					mMainAnimDef->mObjectNamePool.push_back(theBuffer->ReadString());
					aName = mMainAnimDef->mObjectNamePool.back().c_str();
				}

				if (aWord & 2048)
					theBuffer->ReadInt32();

				if (anObjectPos.mObjectNum >= (int)theSpriteDef->mObjectDefVector.size())
					theSpriteDef->mObjectDefVector.resize(anObjectPos.mObjectNum + 1);

				theSpriteDef->mObjectDefVector[anObjectPos.mObjectNum].mName = aName;
				if (anObjectPos.mIsSprite)
					theSpriteDef->mObjectDefVector[anObjectPos.mObjectNum].mSpriteDef = &mMainAnimDef->mSpriteDefVector[anObjectPos.mResNum];

				aCurObjectPosMap.insert(IntToPAObjectPosMap::value_type(anObjectPos.mObjectNum, anObjectPos));
				aFrameObjectIds.push_back(anObjectPos.mObjectNum);
			}
		}

		if (aFlags & 4)
		{
			int aNumMoves = theBuffer->ReadByte();
			if (aNumMoves == 255)
				aNumMoves = theBuffer->ReadInt16();

			for (int i = 0; i < aNumMoves; i++)
			{
				uint16 aWord = theBuffer->ReadInt16();
				int anObjectId = aWord & 1023;
				if (anObjectId == 1023)
					anObjectId = theBuffer->ReadInt32();

				IntToPAObjectPosMap::iterator anItr = aCurObjectPosMap.find(anObjectId);
				if (anItr == aCurObjectPosMap.end())
					continue;

				PAObjectPos& anObjectPos = anItr->second;
				anObjectPos.mTransform.mMatrix.LoadIdentity();
				if (aWord & 4096)
				{
					anObjectPos.mTransform.mMatrix.m00 = theBuffer->ReadInt32() * 1.5258789e-5f;
					anObjectPos.mTransform.mMatrix.m01 = theBuffer->ReadInt32() * 1.5258789e-5f;
					anObjectPos.mTransform.mMatrix.m10 = theBuffer->ReadInt32() * 1.5258789e-5f;
					anObjectPos.mTransform.mMatrix.m11 = theBuffer->ReadInt32() * 1.5258789e-5f;
				}
				else if (aWord & 16384)
				{
					float aRot = theBuffer->ReadInt16() * 0.001f;
					float aSin = sinf(aRot);
					float aCos = cosf(aRot);
					if (mMainAnimDef->mVersion == 2)
						aSin = -aSin;
					anObjectPos.mTransform.mMatrix.m00 = aCos;
					anObjectPos.mTransform.mMatrix.m10 = aSin;
					anObjectPos.mTransform.mMatrix.m11 = aCos;
					anObjectPos.mTransform.mMatrix.m01 = -aSin;
				}

				PopTransformMatrix aTranslate;
				aTranslate.LoadIdentity();
				if (aWord & 2048)
				{
					aTranslate.m02 = theBuffer->ReadInt32() * 0.05f;
					aTranslate.m12 = theBuffer->ReadInt32() * 0.05f;
				}
				else
				{
					aTranslate.m02 = theBuffer->ReadInt16() * 0.05f;
					aTranslate.m12 = theBuffer->ReadInt16() * 0.05f;
				}
				anObjectPos.mTransform.mMatrix = aTranslate * anObjectPos.mTransform.mMatrix;

				if (aWord & 8192)
				{
					anObjectPos.mRed = theBuffer->ReadByte();
					anObjectPos.mGreen = theBuffer->ReadByte();
					anObjectPos.mBlue = theBuffer->ReadByte();
					anObjectPos.mAlpha = theBuffer->ReadByte();
				}

				if (aWord & 1024)
					theBuffer->ReadInt16();

				if (aCurObjectPosIndexMap.find(anObjectId) != aCurObjectPosIndexMap.end())
				{
					int aPosIndex = theSpriteDef->mObjectPosVector.size();
					theSpriteDef->mObjectPosVector.resize(aPosIndex + 1);
					theSpriteDef->mObjectPosVector[aPosIndex] = anObjectPos;
					aCurObjectPosIndexMap[anObjectId] = aPosIndex;
				}
			}
		}

		for (size_t i = 0; i < aFrameObjectIds.size(); i++)
		{
			IntToPAObjectPosMap::iterator anItr = aCurObjectPosMap.find(aFrameObjectIds[i]);
			if (!(anItr == aCurObjectPosMap.end()))
			{
				PAObjectPos& anEntry = anItr->second;
				int aPosIndex = theSpriteDef->mObjectPosVector.size();
				theSpriteDef->mObjectPosVector.resize(aPosIndex + 1);
				theSpriteDef->mObjectPosVector[aPosIndex] = anEntry;
				aCurObjectPosIndexMap.insert(std::map<int, int>::value_type(anEntry.mObjectNum, aPosIndex));
			}
		}

		if (aFlags & 8)
		{
			std::string aLabel = StringToUpper(theBuffer->ReadString());
			theSpriteDef->mLabels.insert(StringToIntMap::value_type(aLabel, aFrameNum));
		}

		if (aFlags & 16)
			aFrame->mHasStop = true;

		if (aFlags & 32)
		{
			int aNumCommands = theBuffer->ReadByte();
			aFrame->mCommandVector.resize(aNumCommands);
			for (int i = 0; i < aNumCommands; i++)
			{
				aFrame->mCommandVector[i].mCommand = theBuffer->ReadString();
				aFrame->mCommandVector[i].mParam = theBuffer->ReadString();
			}
		}

		aFrame->mFrameObjectPosIndexVector.resize(aCurObjectPosIndexMap.size());
		IntToPAObjectPosMap::iterator anObjectPosItr = aCurObjectPosMap.begin();
		std::map<int, int>::iterator anIndexItr = aCurObjectPosIndexMap.begin();
		for (size_t i = 0; anObjectPosItr != aCurObjectPosMap.end(); i++, ++anObjectPosItr, ++anIndexItr)
			aFrame->mFrameObjectPosIndexVector[i] = anIndexItr->second;
	}

	theSpriteDef->mObjectPosVector.shrink_to_fit();
	theSpriteDef->mObjectDefVector.shrink_to_fit();
	if (aNumFrames == 0)
		theSpriteDef->mFrames.resize(1);

	return true;
}

/////////////// Sprite instances ///////////////

void PopAnim::ResetAnimHelper(PASpriteInst* theSpriteInst)
{
	theSpriteInst->mFrameRepeats = 0;
	theSpriteInst->mLastUpdated = -1;
	theSpriteInst->mDelayFrames = 0;
	theSpriteInst->mOnNewFrame = true;
	theSpriteInst->mFrameNum = 0;
	for (int i = 0; i < (int)theSpriteInst->mChildren.size(); i++)
	{
		if (theSpriteInst->mChildren[i].mSpriteInst != NULL)
			ResetAnimHelper(theSpriteInst->mChildren[i].mSpriteInst);
	}
	mTransDirty = true;
}

PASpriteDef* PopAnim::FindSpriteDef(const char* theAnimName)
{
	if (mMainAnimDef != NULL)
	{
		for (unsigned int i = 0; i < mMainAnimDef->mSpriteDefVector.size(); i++)
		{
			if (strcasecmp(mMainAnimDef->mSpriteDefVector[i].mName, theAnimName) == 0)
				return &mMainAnimDef->mSpriteDefVector[i];
		}
	}
	return NULL;
}

PAObjectInst* PopAnim::GetObjectInst(const std::string& theName)
{
	SetupSpriteInst("");
	return mMainSpriteInst->GetObjectInst(theName);
}

void PopAnim::InitSpriteInst(PASpriteInst* theSpriteInst, PASpriteDef* theSpriteDef)
{
	theSpriteInst->mDef = theSpriteDef;
	theSpriteInst->mOnNewFrame = true;
	theSpriteInst->mFrameRepeats = 0;
	theSpriteInst->mFrameNum = 0;
	theSpriteInst->mDelayFrames = 0;
	theSpriteInst->mLastUpdated = -1;
	theSpriteInst->mSpriteVisibility = true;
	theSpriteInst->mChildren.clear();
	theSpriteInst->mChildren.resize(theSpriteDef->mObjectDefVector.size());

	for (int i = 0; i < (int)theSpriteDef->mObjectDefVector.size(); i++)
	{
		PAObjectDef* anObjectDef = &theSpriteDef->mObjectDefVector[i];
		PAObjectInst* anObjectInst = &theSpriteInst->mChildren[i];
		anObjectInst->mName = anObjectDef->mName;
		anObjectInst->mIsBlending = false;
		PASpriteDef* aChildSpriteDef = anObjectDef->mSpriteDef;
		if (aChildSpriteDef != NULL)
		{
			PASpriteInst* aSpriteInst = new PASpriteInst();
			aSpriteInst->mParent = theSpriteInst;
			InitSpriteInst(aSpriteInst, aChildSpriteDef);
			anObjectInst->mSpriteInst = aSpriteInst;
		}
}
}

bool PopAnim::SetupSpriteInst(const std::string& theName)
{
	if (mMainSpriteInst == NULL)
		return false;

	if (mMainSpriteInst->mDef != NULL && theName.length() == 0)
		return true;

	PASpriteDef* aMainSpriteDef = mMainAnimDef->mMainSpriteDef;
	if (aMainSpriteDef != NULL)
	{
		InitSpriteInst(mMainSpriteInst, aMainSpriteDef);
		return true;
	}

	if (mMainAnimDef->mSpriteDefVector.size() == 0)
		return false;

	std::string aName = theName;
	if (aName.length() == 0)
		aName = "main";

	PASpriteDef* aSpriteDef = NULL;
	for (int i = 0; i < (int)mMainAnimDef->mSpriteDefVector.size(); i++)
	{
		PASpriteDef* aDef = &mMainAnimDef->mSpriteDefVector[i];
		if (aDef->mName != NULL && strcasecmp(aDef->mName, aName.c_str()) == 0)
			aSpriteDef = aDef;
	}

	if (aSpriteDef == NULL)
		aSpriteDef = &mMainAnimDef->mSpriteDefVector[0];

	if (mMainSpriteInst->mDef != aSpriteDef)
	{
		if (mMainSpriteInst->mDef != NULL)
		{
			delete mMainSpriteInst;
			mMainSpriteInst = new PASpriteInst();
			mMainSpriteInst->mParent = NULL;
		}
		InitSpriteInst(mMainSpriteInst, aSpriteDef);
		mTransDirty = true;
	}
	return true;
}

/////////////// Playback ///////////////

bool PopAnim::Play(int theFrameNum, bool resetAnim)
{
	bool aSuccess = SetupSpriteInst("");
	if (aSuccess)
	{
		PASpriteInst* aSpriteInst = mMainSpriteInst;
		if (theFrameNum < (int)aSpriteInst->mDef->mFrames.size())
		{
			if (aSpriteInst->mFrameNum != (float)theFrameNum && __builtin_expect(resetAnim, 0))
			{
				ResetAnim();
				aSpriteInst = mMainSpriteInst;
			}

			mPaused = false;
			mAnimRunning = true;
			aSpriteInst->mDelayFrames = 0;
			aSpriteInst->mFrameRepeats = 0;
			aSpriteInst->mFrameNum = (float)theFrameNum;
			if (mBlendDelay == 0)
				DoFramesHit(aSpriteInst, NULL);
		}
		else
		{
			mAnimRunning = false;
			aSuccess = false;
		}
	}
	return aSuccess;
}

bool PopAnim::Play(const std::string& theFrameLabel, bool resetAnim)
{
	mAnimRunning = false;
	if (mMainAnimDef->mMainSpriteDef != NULL)
	{
		if (!SetupSpriteInst(""))
			return false;

		int aFrameNum = mMainAnimDef->mMainSpriteDef->GetLabelFrame(theFrameLabel);
		if (aFrameNum == -1)
			return false;

		mLastPlayedFrameLabel = theFrameLabel;
		return Play(aFrameNum, resetAnim);
	}

	SetupSpriteInst(theFrameLabel);
	return Play(mMainSpriteInst->mDef->mWorkAreaStart, resetAnim);
}

void PopAnim::FrameHit(PASpriteInst* theSpriteInst, PAFrame* theFrame, PAObjectPos* theObjectPos)
{
	theSpriteInst->mOnNewFrame = false;

	for (int aCommandNum = 0; aCommandNum < (int)theFrame->mCommandVector.size(); aCommandNum++)
	{
		PACommand* aCommand = &theFrame->mCommandVector[aCommandNum];
		if (aCommand == NULL)
			continue;
		if (mListener != NULL && mListener->PopAnimCommand(mId, theSpriteInst, aCommand->mCommand, aCommand->mParam))
			continue;

		bool isDelay = Lower(aCommand->mCommand) == "delay";
		if (isDelay)
		{
			const std::string& aParam = aCommand->mParam;
			int aCommaPos = (int)aParam.find(',');
			if (aCommaPos == -1)
			{
				int aDelay = atoi(Trim(aParam).c_str());
				theSpriteInst->mDelayFrames = (int16)aDelay;
			}
			else
			{
				int aMin = atoi(Trim(aParam.substr(0, aCommaPos)).c_str());
				int aMax = atoi(Trim(aParam.substr(aCommaPos + 1)).c_str());
				if (aMax <= aMin)
					aMax = aMin + 1;
				theSpriteInst->mDelayFrames = (int16)(Rand() % (aMax - aMin) + aMin);
			}
		}
		else if (Lower(aCommand->mCommand) == "playsample")
		{
			bool isFirst = true;
			std::string aParams = aCommand->mParam;
			double aVolume = 1.0;
			int aPan = 0;
			double aSteps = 0.0;
			std::string aSampleName;
			while (aParams.size() != 0)
			{
				std::string aCurParam;
				int aCommaPos = (int)aParams.find(',');
				if (aCommaPos == -1)
					aCurParam = aParams;
				else
					aCurParam = aParams.substr(0, aCommaPos);

				if (isFirst)
				{
					aSampleName = aCurParam;
				}
				else
				{
					int aSpacePos;
					while ((aSpacePos = (int)aCurParam.find(' ')) != -1)
						aCurParam.erase(aCurParam.begin() + aSpacePos);

					if (strncasecmp(aCurParam.c_str(), "volume=", 7) == 0)
						StringToDouble(aCurParam.substr(7), &aVolume);
					else if (strncasecmp(aCurParam.c_str(), "pan=", 4) == 0)
						StringToInt(aCurParam.substr(4), &aPan);
					else if (strncasecmp(aCurParam.c_str(), "steps=", 6) == 0)
						StringToDouble(aCurParam.substr(6), &aSteps);
				}

				if (aCommaPos == -1)
					break;
				isFirst = false;
				aParams = aParams.substr(aCommaPos + 1);
			}

			if (mListener != NULL)
				mListener->PopAnimPlaySample(aSampleName, aPan, aVolume, aSteps);
		}
	}
}

void PopAnim::DoFramesHit(PASpriteInst* theSpriteInst, PAObjectPos* theObjectPos)
{
	PAFrame* aCurFrame = &theSpriteInst->mDef->mFrames[(int)theSpriteInst->mFrameNum];
	FrameHit(theSpriteInst, aCurFrame, theObjectPos);

	for (int i = 0; i < (int)aCurFrame->mFrameObjectPosIndexVector.size(); i++)
	{
		PAObjectPos* anObjectPos = &theSpriteInst->mDef->mObjectPosVector[aCurFrame->mFrameObjectPosIndexVector[i]];
		if (anObjectPos->mIsSprite)
		{
			PAObjectInst* anObjectInst = &theSpriteInst->mChildren[anObjectPos->mObjectNum];
			if (anObjectInst->mSpriteInst != NULL)
				DoFramesHit(anObjectInst->mSpriteInst, anObjectPos);
		}
	}
}

void PopAnim::DrawDebugOverlay(Graphics* g)
{
	DrawDebugOverlayForSprite(g, mMainSpriteInst, NULL, 0);
}

/////////////// Transforms ///////////////

void PopAnim::CalcObjectPos(const PASpriteInst* theSpriteInst, const PAObjectPos* objPos, PATransform* theTransform, Color* theColor)
{
	*theTransform = objPos->mTransform;
	*theColor = Color(objPos->mRed, objPos->mGreen, objPos->mBlue, objPos->mAlpha);

	if (mBlendTicksTotal != 0 && mMainSpriteInst == theSpriteInst)
	{
		const PAObjectInst* anObjectInst = &theSpriteInst->mChildren[objPos->mObjectNum];
		if (anObjectInst->mIsBlending)
		{
			float aBlendPct = mBlendTicksCur / mBlendTicksTotal;
			*theTransform = anObjectInst->mBlendSrcTransform.InterpolateTo(*theTransform, aBlendPct);
			*theColor = Color(
				(int)(theColor->mRed * aBlendPct + 0.5f + anObjectInst->mBlendSrcColor.mRed * (1.0f - aBlendPct)),
				(int)(theColor->mGreen * aBlendPct + 0.5f + anObjectInst->mBlendSrcColor.mGreen * (1.0f - aBlendPct)),
				(int)(theColor->mBlue * aBlendPct + 0.5f + anObjectInst->mBlendSrcColor.mBlue * (1.0f - aBlendPct)),
				(int)(theColor->mAlpha * aBlendPct + 0.5f + anObjectInst->mBlendSrcColor.mAlpha * (1.0f - aBlendPct)));
		}
	}
}

void PopAnim::UpdateTransforms()
{
	UpdateTransforms(mMainSpriteInst, NULL, mColor);
}

void PopAnim::UpdateTransforms(PASpriteInst* theSpriteInst, PATransform* theTransform, const Color& theColor)
{
	if (theTransform != NULL)
		theSpriteInst->mCurTransform = *theTransform;
	else
		theSpriteInst->mCurTransform.mMatrix = mTransform;
	theSpriteInst->mCurColor = theColor;

	int aFrameNum = (int)theSpriteInst->mFrameNum;
	if (aFrameNum < 0)
		return;

	PAFrame* aCurFrame = &theSpriteInst->mDef->mFrames[aFrameNum];
	if (aCurFrame == NULL || aCurFrame->mFrameObjectPosIndexVector.empty())
		return;

	PATransform aTransform;
	Color aColor;
	for (int i = 0; i < (int)aCurFrame->mFrameObjectPosIndexVector.size(); i++)
	{
		PAObjectPos* anObjectPos = &theSpriteInst->mDef->mObjectPosVector[aCurFrame->mFrameObjectPosIndexVector[i]];
		if (anObjectPos->mIsSprite)
		{
			CalcObjectPos(theSpriteInst, anObjectPos, &aTransform, &aColor);
			if (theTransform != NULL)
				aTransform = theTransform->TransformSrc(aTransform);
			UpdateTransforms(theSpriteInst->mChildren[anObjectPos->mObjectNum].mSpriteInst, &aTransform, aColor);
		}
	}
}

void PopAnim::PrepSpriteInstFrame(PASpriteInst* theSpriteInst, PAObjectPos* theObjectPos)
{
	PAFrame* aCurFrame = &theSpriteInst->mDef->mFrames[(int)theSpriteInst->mFrameNum];
	if (theSpriteInst->mOnNewFrame)
		FrameHit(theSpriteInst, aCurFrame, theObjectPos);

	if (aCurFrame->mHasStop)
	{
		if (theSpriteInst == mMainSpriteInst && mAnimRunning)
		{
			mAnimRunning = false;
			if (mListener != NULL)
				mListener->PopAnimStopped(mId);
		}
		return;
	}

	for (int i = 0; i < (int)aCurFrame->mFrameObjectPosIndexVector.size(); i++)
	{
		int anObjectPosIndex = aCurFrame->mFrameObjectPosIndexVector[i];
		PAObjectPos* anObjectPos = &theSpriteInst->mDef->mObjectPosVector[anObjectPosIndex];
		if (anObjectPos->mIsSprite)
		{
			PASpriteInst* aChildSpriteInst = theSpriteInst->mChildren[anObjectPos->mObjectNum].mSpriteInst;
			if (aChildSpriteInst != NULL)
			{
				int aFrameNum = (int)theSpriteInst->mFrameNum + theSpriteInst->mFrameRepeats * (int)theSpriteInst->mDef->mFrames.size();
				if (aFrameNum - 1 != aChildSpriteInst->mLastUpdated && aFrameNum != aChildSpriteInst->mLastUpdated)
				{
					aChildSpriteInst->mFrameRepeats = 0;
					aChildSpriteInst->mDelayFrames = 0;
					aChildSpriteInst->mOnNewFrame = true;
					aChildSpriteInst->mFrameNum = 0;
				}
				PrepSpriteInstFrame(aChildSpriteInst, anObjectPos);
				aChildSpriteInst->mLastUpdated = aFrameNum;
			}
		}
	}
}

/////////////// Drawing ///////////////

void PopAnim::DrawSprite(Graphics* g, const PASpriteInst* theSpriteInst, const PATransform* theTransform, const Color& theColor, bool additive)
{
	if (!theSpriteInst->mSpriteVisibility || theColor.mAlpha <= 5)
		return;

	const PAFrame* aCurFrame = &theSpriteInst->mDef->mFrames[(int)theSpriteInst->mFrameNum];

	PATransform aTransform;
	Color aColor;
	PATransform aDrawTransform;
	std::vector<int>::const_iterator anItr = aCurFrame->mFrameObjectPosIndexVector.begin();
	std::vector<int>::const_iterator anEnd = aCurFrame->mFrameObjectPosIndexVector.end();
	for (; anItr != anEnd; ++anItr)
	{
		PAObjectPos* anObjectPos = &theSpriteInst->mDef->mObjectPosVector[*anItr];
		if (anObjectPos->mIsSprite)
		{
			PASpriteInst* aChildSpriteInst = theSpriteInst->mChildren[anObjectPos->mObjectNum].mSpriteInst;
			const Color& aChildColor = aChildSpriteInst->mCurColor;
			PopTransformMatrix aBaseTransform(mTransform);
			AffineMatrixMultiply2d(&aTransform.mMatrix, &aBaseTransform, &aChildSpriteInst->mCurTransform.mMatrix);
			aColor.mRed = aChildColor.mRed * theColor.mRed / 255;
			aColor.mGreen = aChildColor.mGreen * theColor.mGreen / 255;
			aColor.mBlue = aChildColor.mBlue * theColor.mBlue / 255;
			aColor.mAlpha = aChildColor.mAlpha * theColor.mAlpha / 255;
			DrawSprite(g, aChildSpriteInst, &aTransform, aColor, additive | anObjectPos->mIsAdditive);
		}
		else
		{
			if (mBlendTicksTotal == 0 || mMainSpriteInst != theSpriteInst)
			{
				AffineMatrixMultiply2d(&aTransform.mMatrix, &theTransform->mMatrix, &anObjectPos->mTransform.mMatrix);
				aColor.mRed = anObjectPos->mRed * theColor.mRed / 255;
				aColor.mGreen = anObjectPos->mGreen * theColor.mGreen / 255;
				aColor.mBlue = anObjectPos->mBlue * theColor.mBlue / 255;
				aColor.mAlpha = anObjectPos->mAlpha * theColor.mAlpha / 255;
			}
			else
			{
				CalcObjectPos(theSpriteInst, anObjectPos, &aTransform, &aColor);
				aTransform.mMatrix = theTransform->mMatrix * aTransform.mMatrix;
				aColor.mRed = aColor.mRed * theColor.mRed / 255;
				aColor.mGreen = aColor.mGreen * theColor.mGreen / 255;
				aColor.mBlue = aColor.mBlue * theColor.mBlue / 255;
				aColor.mAlpha = aColor.mAlpha * theColor.mAlpha / 255;
			}

			PAImage* aPAImage = &mMainAnimDef->mImageVector[anObjectPos->mResNum];
			AffineMatrixMultiply2d(&aDrawTransform.mMatrix, &aTransform.mMatrix, &aPAImage->mTransform.mMatrix);

			g->SetColorizeImages(true);
			g->SetColor(aColor);
			if (additive || anObjectPos->mIsAdditive)
				g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
			else
				g->SetDrawMode(aPAImage->mDrawMode);

			Image* anImage = aPAImage->mImage;
			Rect aSrcRect = anImage->GetCelRect(0);
			aDrawTransform.mMatrix.m02 = aSrcRect.mWidth * 0.5f * aDrawTransform.mMatrix.m00 + aSrcRect.mHeight * 0.5f * aDrawTransform.mMatrix.m01 + aDrawTransform.mMatrix.m02;
			aDrawTransform.mMatrix.m12 = aSrcRect.mWidth * 0.5f * aDrawTransform.mMatrix.m10 + aSrcRect.mHeight * 0.5f * aDrawTransform.mMatrix.m11 + aDrawTransform.mMatrix.m12;
			g->DrawImageMatrix(anImage, aDrawTransform.mMatrix.GetMatrix3(), aSrcRect, 0, 0);
		}
	}

	g->SetColorizeImages(false);
	g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
}

void PopAnim::DrawSpriteReplaceLayerWithImage(Graphics* g, const PASpriteInst* theSpriteInst, const PATransform* theTransform, const Color& theColor, bool additive, const std::string& theLayer, Image* theImage)
{
	const PAFrame* aCurFrame = &theSpriteInst->mDef->mFrames[(int)theSpriteInst->mFrameNum];

	PATransform aTransform;
	Color aColor;
	PATransform aDrawTransform;
	std::vector<int>::const_iterator anItr = aCurFrame->mFrameObjectPosIndexVector.begin();
	std::vector<int>::const_iterator anEnd = aCurFrame->mFrameObjectPosIndexVector.end();
	for (; anItr != anEnd; ++anItr)
	{
		PAObjectPos* anObjectPos = &theSpriteInst->mDef->mObjectPosVector[*anItr];
		if (anObjectPos->mIsSprite)
		{
			PASpriteInst* aChildSpriteInst = theSpriteInst->mChildren[anObjectPos->mObjectNum].mSpriteInst;
			const Color& aChildColor = aChildSpriteInst->mCurColor;
			PopTransformMatrix aBaseTransform(mTransform);
			AffineMatrixMultiply2d(&aTransform.mMatrix, &aBaseTransform, &aChildSpriteInst->mCurTransform.mMatrix);
			aColor.mRed = aChildColor.mRed * theColor.mRed / 255;
			aColor.mGreen = aChildColor.mGreen * theColor.mGreen / 255;
			aColor.mBlue = aChildColor.mBlue * theColor.mBlue / 255;
			aColor.mAlpha = aChildColor.mAlpha * theColor.mAlpha / 255;
			DrawSpriteReplaceLayerWithImage(g, aChildSpriteInst, &aTransform, aColor, additive | anObjectPos->mIsAdditive, theLayer, theImage);
		}
		else
		{
			if (mBlendTicksTotal == 0 || mMainSpriteInst != theSpriteInst)
			{
				AffineMatrixMultiply2d(&aTransform.mMatrix, &theTransform->mMatrix, &anObjectPos->mTransform.mMatrix);
				aColor.mRed = anObjectPos->mRed * theColor.mRed / 255;
				aColor.mGreen = anObjectPos->mGreen * theColor.mGreen / 255;
				aColor.mBlue = anObjectPos->mBlue * theColor.mBlue / 255;
				aColor.mAlpha = anObjectPos->mAlpha * theColor.mAlpha / 255;
			}
			else
			{
				CalcObjectPos(theSpriteInst, anObjectPos, &aTransform, &aColor);
				aTransform.mMatrix = theTransform->mMatrix * aTransform.mMatrix;
				aColor.mRed = aColor.mRed * theColor.mRed / 255;
				aColor.mGreen = aColor.mGreen * theColor.mGreen / 255;
				aColor.mBlue = aColor.mBlue * theColor.mBlue / 255;
				aColor.mAlpha = aColor.mAlpha * theColor.mAlpha / 255;
			}

			PAImage* aPAImage = &mMainAnimDef->mImageVector[anObjectPos->mResNum];
			AffineMatrixMultiply2d(&aDrawTransform.mMatrix, &aTransform.mMatrix, &aPAImage->mTransform.mMatrix);
			aDrawTransform = aTransform;

			g->SetColorizeImages(true);
			g->SetColor(aColor);
			if (additive || anObjectPos->mIsAdditive)
				g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
			else
				g->SetDrawMode(aPAImage->mDrawMode);

			Rect aSrcRect = theImage->GetCelRect(0);
			aDrawTransform.mMatrix.m02 = aSrcRect.mWidth * 0.5f * aDrawTransform.mMatrix.m00 + aSrcRect.mHeight * 0.5f * aDrawTransform.mMatrix.m01 + aDrawTransform.mMatrix.m02;
			aDrawTransform.mMatrix.m12 = aSrcRect.mWidth * 0.5f * aDrawTransform.mMatrix.m10 + aSrcRect.mHeight * 0.5f * aDrawTransform.mMatrix.m11 + aDrawTransform.mMatrix.m12;
			if (theSpriteInst->mDef->mExportName == theLayer)
				g->DrawImageMatrix(theImage, aDrawTransform.mMatrix.GetMatrix3(), aSrcRect, 0, 0);
		}
	}

	g->SetColorizeImages(false);
	g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
}

void PopAnim::Draw(Graphics* g)
{
	if (!mMainAnimDef->mLoaded)
		return;
	if (!SetupSpriteInst(""))
		return;

	if (mTransDirty)
	{
		UpdateTransforms();
		mTransDirty = false;
	}

	float aScale = mDrawScale;
	if (aScale > 0.98f && aScale < 1.02f)
	{
		PATransform aTransform;
		aTransform.mMatrix = mTransform;
		DrawSprite(g, mMainSpriteInst, &aTransform, mColor, mAdditive);
	}
	else
	{
		float m00 = mTransform.m00;
		float m01 = mTransform.m01;
		float m10 = mTransform.m10;
		float m11 = mTransform.m11;
		mTransform.m00 = m00 * aScale;
		mTransform.m01 = m01 * aScale;
		mTransform.m10 = m10 * aScale;
		mTransform.m11 = m11 * aScale;

		PATransform aTransform;
		aTransform.mMatrix = mTransform;
		DrawSprite(g, mMainSpriteInst, &aTransform, mColor, mAdditive);

		mTransform.m00 = m00;
		mTransform.m01 = m01;
		mTransform.m10 = m10;
		mTransform.m11 = m11;
	}
}

/////////////// Animation update ///////////////

void PopAnim::IncSpriteInstFrame(PASpriteInst* i_spriteInst, PAObjectPos* i_objectPos, float i_increment)
{
	int aLastFrameNum = (int)i_spriteInst->mFrameNum;
	PAFrame* aLastFrame = &i_spriteInst->mDef->mFrames[aLastFrameNum];
	if (aLastFrame->mHasStop)
		return;

	i_spriteInst->mFrameNum = i_increment + i_spriteInst->mFrameNum;
	int aNewFrameNum = (int)i_spriteInst->mFrameNum;
	if (aNewFrameNum - aLastFrameNum > 1)
		i_spriteInst->mFrameNum = aLastFrameNum + 1.9f;

	if (i_spriteInst == mMainSpriteInst)
	{
		if (!i_spriteInst->mDef->mFrames.back().mHasStop)
		{
			if (i_spriteInst->mDef->mWorkAreaStart + i_spriteInst->mDef->mWorkAreaDuration < (int)i_spriteInst->mFrameNum)
			{
				i_spriteInst->mFrameRepeats++;
				i_spriteInst->mFrameNum -= i_spriteInst->mDef->mWorkAreaDuration + 1;
				aNewFrameNum = (int)i_spriteInst->mFrameNum;
			}
			else
				aNewFrameNum = (int)mMainSpriteInst->mFrameNum;
		}
		else if ((int)i_spriteInst->mFrameNum < i_spriteInst->mDef->mWorkAreaStart + i_spriteInst->mDef->mWorkAreaDuration)
		{
			aNewFrameNum = (int)mMainSpriteInst->mFrameNum;
		}
		else
		{
			i_spriteInst->mOnNewFrame = true;
			i_spriteInst->mFrameNum = i_spriteInst->mDef->mWorkAreaStart + i_spriteInst->mDef->mWorkAreaDuration;
			if (i_spriteInst->mDef->mWorkAreaDuration != 0)
			{
				if (mAnimRunning)
				{
					mAnimRunning = false;
					if (mListener != NULL)
						mListener->PopAnimStopped(mId);
				}
				return;
			}
			i_spriteInst->mFrameRepeats++;
			aNewFrameNum = (int)i_spriteInst->mFrameNum;
		}
	}
	else
	{
		aNewFrameNum = (int)i_spriteInst->mFrameNum;
		if (aNewFrameNum >= (int)i_spriteInst->mDef->mFrames.size())
		{
			i_spriteInst->mFrameRepeats++;
			do
			{
				i_spriteInst->mFrameNum -= (int)i_spriteInst->mDef->mFrames.size();
				aNewFrameNum = (int)i_spriteInst->mFrameNum;
			} while (aNewFrameNum >= (int)i_spriteInst->mDef->mFrames.size());
		}
	}

	i_spriteInst->mOnNewFrame = aLastFrameNum != aNewFrameNum;
	if (i_spriteInst->mOnNewFrame && i_spriteInst->mDelayFrames > 0)
	{
		i_spriteInst->mDelayFrames--;
		i_spriteInst->mOnNewFrame = false;
		i_spriteInst->mFrameNum = aLastFrameNum;
		return;
	}

	for (int i = 0; i < (int)aLastFrame->mFrameObjectPosIndexVector.size(); i++)
	{
		int anObjectPosIndex = aLastFrame->mFrameObjectPosIndexVector[i];
		PAObjectPos* anObjectPos = &i_spriteInst->mDef->mObjectPosVector[anObjectPosIndex];
		if (anObjectPos->mIsSprite)
			IncSpriteInstFrame(i_spriteInst->mChildren[anObjectPos->mObjectNum].mSpriteInst, anObjectPos, i_increment);
	}
}

bool PopAnim::Load_GetImage(PAImage* theImage, const std::string& theFileDir, const std::string& theOrigName)
{
	MixedImagePtr anImage = Load_GetImageHook(theFileDir, theOrigName);
	if (!anImage)
		return false;

	anImage->mNumCols = theImage->mCols;
	anImage->mNumRows = theImage->mRows;
	if (theImage->mOrigWidth != -1 && theImage->mOrigHeight != -1)
	{
		theImage->mTransform.mMatrix.m02 += (theImage->mOrigWidth * mImgScale - anImage->mWidth) / (anImage->mNumCols + 1);
		theImage->mTransform.mMatrix.m12 += (theImage->mOrigHeight * mImgScale - anImage->mHeight) / (anImage->mNumRows + 1);
	}

	theImage->mImage = anImage->Cast<DeviceImage>();
	return true;
}

MixedImagePtr PopAnim::Load_GetImageHook(const std::string& theFileDir, const std::string& theOrigName)
{
	std::vector<std::string> aPathList;
	aPathList.push_back("images\\");
	aPathList.push_back("");

	for (int i = 0; i < (int)aPathList.size(); i++)
	{
		std::string aPath = GetPathFrom(aPathList[i], theFileDir);
		if (aPath.length() > 0 && aPath[aPath.length() - 1] != '\\' && aPath[aPath.length() - 1] != '/')
			aPath += "\\";
		aPath += theOrigName;

		ResourceManager::GetImageOptions anOptions;
		anOptions.mVariant = "";
		MixedImagePtr anImage;
		gSexyAppBase->mResourceManager->GetImage(anImage, aPath, &anOptions, NULL);
		if ((Image*)anImage != NULL)
		{
			MemoryImage* aMemoryImage = anImage->Cast<MemoryImage>();
			if (aMemoryImage != NULL)
				aMemoryImage->Palletize();
			return anImage;
		}
	}

	Fail("Unable to load image: " + theOrigName);
	return MixedImagePtr(RtId(), false);
}

void PopAnim::DrawReplaceLayerWithImage(Graphics* g, const std::string& theLayer, Image* theImage)
{
	if (!mMainAnimDef->mLoaded)
		return;
	if (!SetupSpriteInst(""))
		return;

	if (mTransDirty)
	{
		UpdateTransforms();
		mTransDirty = false;
	}

	float aScale = mDrawScale;
	if (aScale > 0.98f && aScale < 1.02f)
	{
		PATransform aTransform;
		aTransform.mMatrix = mTransform;
		DrawSpriteReplaceLayerWithImage(g, mMainSpriteInst, &aTransform, mColor, mAdditive, theLayer, theImage);
	}
	else
	{
		float m00 = mTransform.m00;
		float m01 = mTransform.m01;
		float m10 = mTransform.m10;
		float m11 = mTransform.m11;
		mTransform.m00 = m00 * aScale;
		mTransform.m01 = m01 * aScale;
		mTransform.m10 = m10 * aScale;
		mTransform.m11 = m11 * aScale;

		PATransform aTransform;
		aTransform.mMatrix = mTransform;
		DrawSpriteReplaceLayerWithImage(g, mMainSpriteInst, &aTransform, mColor, mAdditive, theLayer, theImage);

		mTransform.m00 = m00;
		mTransform.m01 = m01;
		mTransform.m10 = m10;
		mTransform.m11 = m11;
	}
}

bool PopAnim::BlendTo(const std::string& theFrameLabel, float theBlendTicks, float theAnimStartDelay)
{
	bool aSuccess = SetupSpriteInst("");
	if (!aSuccess)
		return aSuccess;

	if (mTransDirty)
	{
		UpdateTransforms();
		mTransDirty = false;
	}

	std::multimap<std::string, BlendSrcData> aBlendSrcMap;
	PASpriteInst* aMainSpriteInst = mMainSpriteInst;
	PAFrame* aCurFrame = &aMainSpriteInst->mDef->mFrames[(int)aMainSpriteInst->mFrameNum];
	PATransform aTransform;
	Color aColor;
	for (int i = 0; i < (int)aCurFrame->mFrameObjectPosIndexVector.size(); i++)
	{
		int aPosIndex = aCurFrame->mFrameObjectPosIndexVector[i];
		PASpriteInst* aSpriteInst = mMainSpriteInst;
		PAObjectPos* anObjectPos = &aSpriteInst->mDef->mObjectPosVector[aPosIndex];
		PAObjectInst* anObjectInst = &aSpriteInst->mChildren[anObjectPos->mObjectNum];
		if (anObjectInst->mSpriteInst != NULL)
		{
			const std::string& aKey = anObjectInst->mSpriteInst->mDef->mExportName;
			if (anObjectPos->mIsSprite)
			{
				aColor = anObjectInst->mSpriteInst->mCurColor;
				aTransform = anObjectInst->mSpriteInst->mCurTransform;
			}
			else
				CalcObjectPos(aSpriteInst, anObjectPos, &aTransform, &aColor);

			BlendSrcData aBlendSrcData;
			aBlendSrcData.mTransform = aTransform;
			aBlendSrcData.mColor = aColor;
			if (anObjectInst->mSpriteInst != NULL)
				aBlendSrcMap.insert(std::pair<const std::string, BlendSrcData>(aKey, aBlendSrcData));
		}
	}

	mBlendTicksTotal = theBlendTicks;
	mBlendDelay = theAnimStartDelay;
	mBlendTicksCur = 0;

	if (mMainAnimDef->mMainSpriteDef == NULL)
	{
		SetupSpriteInst(theFrameLabel);
		Play(mMainSpriteInst->mDef->mWorkAreaStart, false);
	}
	else
	{
		int aFrameNum;
		aSuccess = SetupSpriteInst("");
		if (aSuccess && (aFrameNum = mMainAnimDef->mMainSpriteDef->GetLabelFrame(theFrameLabel)) != -1)
		{
			mLastPlayedFrameLabel = theFrameLabel;
			Play(aFrameNum, false);
			mTransDirty = true;
		}
		else
			aSuccess = false;
	}

	if (aSuccess)
	{
		aMainSpriteInst = mMainSpriteInst;
		for (int i = 0; i < (int)aMainSpriteInst->mDef->mObjectDefVector.size(); i++)
		{
			PAObjectInst* anObjectInst = &aMainSpriteInst->mChildren[i];
			if (anObjectInst->mSpriteInst != NULL)
			{
				std::multimap<std::string, BlendSrcData>::iterator anItr = aBlendSrcMap.find(anObjectInst->mSpriteInst->mDef->mExportName);
				if (anItr != aBlendSrcMap.end())
				{
					anObjectInst->mIsBlending = true;
					anObjectInst->mBlendSrcColor = anItr->second.mColor;
					anObjectInst->mBlendSrcTransform = anItr->second.mTransform;
				}
				else
					anObjectInst->mIsBlending = false;
				aMainSpriteInst = mMainSpriteInst;
			}
		}

		while (aBlendSrcMap.size() != 0)
			aBlendSrcMap.erase(aBlendSrcMap.begin());
	}
	return aSuccess;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PopAnim);

void PopAnim::StaticClassInit()
{
	StaticGetClass()->SetInfoClass(InfoClass::StaticGetClass());
}
