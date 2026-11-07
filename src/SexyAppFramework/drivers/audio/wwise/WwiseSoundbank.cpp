//
//  WwiseSoundbank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseSoundbank.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include "ReflectionBuilder.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

WwiseSoundBank::WwiseSoundBank()
	: mBankDataBufferPtr(NULL)
	, mBankId(0)
	, mMode(LOAD_NONE)
{
}

WwiseSoundBank::~WwiseSoundBank()
{
	destroy();
}

void WwiseSoundBank::destroy()
{
	if (mBankId != 0)
	{
		if (mMode == LOAD_FULL && mBankDataBufferPtr != NULL)
			AK::SoundEngine::UnloadBank(mBankId, mBankDataBufferPtr);
		else if (mMode == LOAD_PARTIAL)
			AK::SoundEngine::PrepareBank(AK::SoundEngine::Preparation_Unload, mBankName.c_str(), AK::SoundEngine::AkBankContent_StructureOnly);
	}
	mBankDataBufferPtr = NULL;
	mBankId = 0;
}

/////////////// Accessors ///////////////

bool WwiseSoundBank::IsValidBank()
{
	return mBankId != 0;
}

AudioBankId WwiseSoundBank::GetBankId()
{
	return mBankId;
}

std::string WwiseSoundBank::GetBankName()
{
	return mBankName;
}

/////////////// Loading ///////////////

bool WwiseSoundBank::Load(const char* bankName)
{
	if (mMode != LOAD_NONE)
		return IsValidBank();

	if (mBankId == 0)
	{
		uint8* aBuffer = NULL;
		uint32 aSize;
		ResStreamsManager* aResStreamsManager = gSexyAppBase->mResStreamsManager;
		if (aResStreamsManager != NULL && aResStreamsManager->IsInitialized("dynamic.rsb"))
		{
			uint32 aGroupId = gSexyAppBase->mResStreamsManager->GetGroupForFile(bankName);
			if (aGroupId != (uint32)-1)
			{
				if (gSexyAppBase->mResStreamsManager->GetResidentFileBuffer(aGroupId, bankName, &aBuffer, &aSize))
				{
					if (aSize == 0)
						aBuffer = NULL;
				}
			}
		}

		if (aBuffer != NULL && AK::SoundEngine::LoadBank(aBuffer, aSize, mBankId) == AK_Success)
		{
			mBankName = std::string(bankName);
			mMode = LOAD_FULL;
			mBankDataBufferPtr = aBuffer;
		}
		else if (aBuffer == NULL && AK::SoundEngine::LoadBank(bankName, AK_DEFAULT_POOL_ID, mBankId) == AK_Success)
		{
			mBankName = std::string(bankName);
			mMode = LOAD_FULL;
			mBankDataBufferPtr = aBuffer;
		}
		else
		{
			mBankId = 0;
			OutputDebugStrF("Could not load SoundBank: %s.\n", bankName);
		}
	}
	return IsValidBank();
}

bool WwiseSoundBank::Prepare(const char* bankName)
{
	if (mMode != LOAD_NONE)
		return IsValidBank();

	if (AK::SoundEngine::PrepareBank(AK::SoundEngine::Preparation_Load, bankName, AK::SoundEngine::AkBankContent_StructureOnly) == AK_Success)
	{
		mMode = LOAD_PARTIAL;
		mBankName = std::string(bankName);
		mBankId = AK::SoundEngine::GetIDFromString(bankName);
	}
	else
	{
		mBankId = 0;
	}
	return IsValidBank();
}

void WwiseSoundBank::SetBankError()
{
	if (IsValidBank())
	{
		mBankId = 0;
		mMode = LOAD_NONE;
		OutputDebugStrF("Set Bank Error, SoundBank is Valid mBankId=[%d], mMode=[%d], mBankName=[%s]\n", mBankId, mMode, mBankName.c_str());
	}
	else
	{
		OutputDebugStrF("Set Bank Error, SoundBank is not Valid mBankId=[%d], mMode=[%d], mBankName=[%s]\n", mBankId, mMode, mBankName.c_str());
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(WwiseSoundBank);
