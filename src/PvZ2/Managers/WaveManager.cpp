//
//  WaveManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "Wave.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveManager);

void WaveManager::onExit(WaveState i_arg)
{
}

int WaveManager::GetWaveCount() const
{
	return m_waves.size();
}
