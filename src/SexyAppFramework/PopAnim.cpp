//
//  PopAnim.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//

#include "PopAnim.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/MemoryImage.h"
#include "SexyAppFramework/DeviceImage.h"
#include "SexyAppFramework/Buffer.h"

using namespace Sexy;

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
	if (mMainAnimDef != NULL)
		return false;

	mMainSpriteInst = new PASpriteInst();
	mMainSpriteInst->mParent = NULL;
	mMainSpriteInst->mDef = NULL;

	mMainAnimDef = new PopAnimDef();
	mMainAnimDef->mLoadedPamFile = theFileName;

	Buffer aBuffer;
	std::string aPamFileDir = GetFileDir(theFileName);
	if (!gSexyAppBase->ReadBufferFromFile(theFileName, &aBuffer))
		return Fail("Unable to load file: " + theFileName);

	if (aBuffer.ReadInt32() != 0xBAF01954)
		return Fail("Invalid header");

	mMainAnimDef->mVersion = aBuffer.ReadInt32();
	if (mMainAnimDef->mVersion >= 7)
		return Fail("Invalid version");

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
		if (aParenStart == -1 || aParenEnd == -1 || aParenEnd <= aParenStart)
		{
			int aDollarPos = aName.find('$');
			if (aDollarPos != -1)
			{
				aFlags = Lower(aName.substr(0, aDollarPos));
				aName = Trim(aName.substr(aDollarPos + 1));
			}
		}
		else
		{
			aFlags = Lower(aName.substr(aParenStart + 1, aParenEnd - aParenStart - 1));
			aName = Trim(aName.substr(0, aParenStart) + aName.substr(aParenEnd + 1));
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
		if (aName.length() == 0)
		{
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
		}
		else
		{
			int aPos = 0;
			while (aPos < (int)aName.length())
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
			return false;
	}

	int aNumSprites = aBuffer.ReadInt16();
	mMainAnimDef->mSpriteDefVector.resize(aNumSprites);
	for (int aSpriteNum = 0; aSpriteNum < aNumSprites; aSpriteNum++)
	{
		if (!LoadSpriteDef(&aBuffer, &mMainAnimDef->mSpriteDefVector[aSpriteNum]))
			return false;
	}

	if (mMainAnimDef->mVersion < 4 || aBuffer.ReadBoolean())
	{
		mMainAnimDef->mMainSpriteDef = new PASpriteDef();
		if (!LoadSpriteDef(&aBuffer, mMainAnimDef->mMainSpriteDef))
			return false;
	}

	mMainAnimDef->mLoaded = true;
	return true;
}

bool PopAnim::LoadSpriteDef(Buffer* theBuffer, PASpriteDef* theSpriteDef)
{
	IntToPAObjectPosMap aCurObjectPosMap;
	std::map<int, int> aCurObjectPosIndexMap;

	theSpriteDef->mObjectPosVector.reserve(512);
	theSpriteDef->mObjectDefVector.reserve(64);

	PopAnimDef* aDef = mMainAnimDef;
	if (aDef->mVersion > 5)
		theSpriteDef->mExportName = theBuffer->ReadString();

	if (aDef->mVersion < 4)
	{
		theSpriteDef->mName = NULL;
		theSpriteDef->mAnimRate = (float)mAnimRate;
	}
	else
	{
		aDef->mObjectNamePool.push_back(theBuffer->ReadString());
		theSpriteDef->mName = aDef->mObjectNamePool.back().c_str();
		theSpriteDef->mAnimRate = theBuffer->ReadInt32() * 1.5258789e-5f;
	}

	int aNumFrames = theBuffer->ReadInt16();
	if (aDef->mVersion < 5)
	{
		theSpriteDef->mWorkAreaStart = 0;
		theSpriteDef->mWorkAreaDuration = aNumFrames - 1;
	}
	else
	{
		theSpriteDef->mWorkAreaStart = theBuffer->ReadInt16();
		theSpriteDef->mWorkAreaDuration = theBuffer->ReadInt16();
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

				aCurObjectPosIndexMap.erase(anObjectId);
				aCurObjectPosMap.erase(anObjectId);
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
					aDef->mObjectNamePool.push_back(theBuffer->ReadString());
					aName = aDef->mObjectNamePool.back().c_str();
				}

				if (aWord & 2048)
					theBuffer->ReadInt32();

				if (anObjectPos.mObjectNum >= (int)theSpriteDef->mObjectDefVector.size())
					theSpriteDef->mObjectDefVector.resize(anObjectPos.mObjectNum + 1);

				theSpriteDef->mObjectDefVector[anObjectPos.mObjectNum].mName = aName;
				if (anObjectPos.mIsSprite)
					theSpriteDef->mObjectDefVector[anObjectPos.mObjectNum].mSpriteDef = &aDef->mSpriteDefVector[anObjectPos.mResNum];

				aCurObjectPosMap.insert(std::pair<int, PAObjectPos>(anObjectPos.mObjectNum, anObjectPos));
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
					if (aDef->mVersion == 2)
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
			if (anItr != aCurObjectPosMap.end())
			{
				int aPosIndex = theSpriteDef->mObjectPosVector.size();
				theSpriteDef->mObjectPosVector.resize(aPosIndex + 1);
				theSpriteDef->mObjectPosVector[aPosIndex] = anItr->second;
				aCurObjectPosIndexMap.insert(std::pair<int, int>(anItr->first, aPosIndex));
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
		std::map<int, int>::iterator anIndexItr = aCurObjectPosIndexMap.begin();
		for (size_t i = 0; i < aFrame->mFrameObjectPosIndexVector.size(); i++, ++anIndexItr)
			aFrame->mFrameObjectPosIndexVector[i] = anIndexItr->second;
	}

	theSpriteDef->mObjectPosVector.shrink_to_fit();
	theSpriteDef->mObjectDefVector.shrink_to_fit();
	if (aNumFrames == 0)
		theSpriteDef->mFrames.resize(1);

	return true;
}
