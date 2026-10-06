//
//  Effect_Barrage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_Barrage.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_Barrage);

void Effect_Barrage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BarrageWaveInfo);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, interval);
		REFLECTION_CLASSBUILDER_FIELD(std::string, barrageName);
	REFLECTION_CLASSBUILDER_END(BarrageWaveInfo);

	REFLECTION_CLASSBUILDER_BEGIN(Effect_Barrage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RealObject);

		REFLECTION_CLASSBUILDER_FIELD(BoardEntity *, m_shooter);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BarrageWaveInfo>, m_barrageWaves);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BarrageWaveInfo>::iterator, m_currentWave);
		REFLECTION_CLASSBUILDER_FIELD(Effect_Barrage *, viceBarrage);
	REFLECTION_CLASSBUILDER_END(Effect_Barrage);
}
