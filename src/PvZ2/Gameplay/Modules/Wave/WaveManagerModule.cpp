//
//  WaveManagerModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "Wave.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveManagerModule);

void WaveManagerModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveManagerModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(WaveManager, m_waveManager);
	REFLECTION_CLASSBUILDER_END(WaveManagerModule);
}

short WaveManagerModule::GetProfileDifficultyIndex()
{
	return false;
}
