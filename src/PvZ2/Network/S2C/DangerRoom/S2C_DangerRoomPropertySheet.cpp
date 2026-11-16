//
//  S2C_DangerRoomPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_DangerRoomPropertySheet);

void S2C_DangerRoomPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_DangerRoomPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, MinWaveCount, iwc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, MaxWaveCount, xwc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, WaveAddEach, wae);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, WaveAddInterval, wai);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, MinFlagWaveCount, ifwc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, MaxFlagWaveCount, xfwc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, MinLevelFlagWaveAdd, ilfwa);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, ZombieLevelBase, zlb);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, ZombieLevelAdd, zla);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, ZombieTypeCount, ztc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, BigZombieSureExistLevel, bzsel);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, LeaderMinWaveCost, lmwc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, LeaderProbability, lp);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, LeaderStrengthenRate, lsr);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, WealthGodProbability, wgp);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, SunLimit, sl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, SunAddBase, sab);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, SunAddEachLevel, sael);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, SunAddBossBase, sabb);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, SunAddBossEach, sabe);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, BossInterval, bi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, BossHpBaseFactor, bhbf);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, BossHpAddFactor, bhaf);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, StartingPoints, sp);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, BasePointIncrementPerWave, bpipw);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, BasePointIncrementPerLevel, bpipl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int32>, PlantPacketLimit, ppl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int32>, PlantPacketStart, pps);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int32>, PlantPacketAddEachLevel, ppa);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_ZombieLevelStat>, ZombieLevelStats, zls);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, MaxSelectedPlant, msp);
	REFLECTION_CLASSBUILDER_END(S2C_DangerRoomPropertySheet);

}
