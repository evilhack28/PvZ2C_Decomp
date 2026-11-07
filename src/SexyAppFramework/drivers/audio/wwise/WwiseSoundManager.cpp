//
//  WwiseSoundManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseSoundManager.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseInteractiveAudioDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

WwiseSoundManager::WwiseSoundManager(IInteractiveAudioDriver* InDriver)
	: InteractiveSoundManager(InDriver)
{
}

/////////////// Initialization ///////////////

bool WwiseSoundManager::Initialize(InteractiveSoundManagerConfig const& config)
{
	WwiseSoundManagerConfig const& wwiseConfig = static_cast<WwiseSoundManagerConfig const&>(config);
	bool result = InteractiveSoundManager::Initialize(config);
	if (!wwiseConfig.mAssetFilePath.empty())
		static_cast<WwiseInteractiveAudioDriver*>(mAudioDriver)->HACK_SetAndroidAssetInfo(wwiseConfig.mAssetFilePath);
	return result;
}
