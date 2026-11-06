//
//  WwiseSoundManagerConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseSoundManager.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

WwiseSoundManagerConfig::WwiseSoundManagerConfig()
{
	if (gSexyAppBase->mResStreamsManager->GetRSBPath().size() != 0)
		mAssetFilePath = gSexyAppBase->mResStreamsManager->GetRSBPath();
}
