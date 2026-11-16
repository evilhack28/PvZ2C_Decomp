//
//  JamListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"
#include "PvZ/JamApplier.h"
#include "PvZ/AudioMgr.h"

void JamListener::OnMusicSyncBeat(AudioGameObjectId i_id)
{
	AudioMgr::GetInstancePtr()->AddDataToCallbackQueue(Sexy::IACT_MusicSyncBeat);
}

void JamListener::OnMusicSyncBar(AudioGameObjectId i_id)
{
	AudioMgr::GetInstancePtr()->AddDataToCallbackQueue(Sexy::IACT_MusicSyncBar);
}
