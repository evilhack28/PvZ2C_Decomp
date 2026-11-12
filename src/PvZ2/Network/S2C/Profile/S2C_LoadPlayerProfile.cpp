//
//  S2C_LoadPlayerProfile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "PlayerInfo.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_LoadPlayerProfile);

void S2C_LoadPlayerProfile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DeltaWorldMapEventInfo);
	REFLECTION_CLASSBUILDER_END(DeltaWorldMapEventInfo);

	REFLECTION_CLASSBUILDER_BEGIN(WorldSpecificKeys);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, WorldName, wn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(KeyCurrency, KeyCount, kc);
	REFLECTION_CLASSBUILDER_END(WorldSpecificKeys);

	REFLECTION_CLASSBUILDER_BEGIN(PlantPieceRecord);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, PlantId, pi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, PieceCount, pc);
	REFLECTION_CLASSBUILDER_END(PlantPieceRecord);

	REFLECTION_CLASSBUILDER_BEGIN(DeltaPlayerProfileInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, version, v);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint32, randomSeed, rs);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint32, coins, c);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, unlockedPlants, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<DeltaWorldMapEventInfo>, worldMapEventList, wm);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, level, l);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, tutorialProgress, tp);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, completedNarrationEvents, ne);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<WorldSpecificKeys>, worldSpecificKeys, wsk);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<PlantPieceRecord>, plantPieceRecords, ppr);
	REFLECTION_CLASSBUILDER_END(DeltaPlayerProfileInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_LoadPlayerProfileData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(DeltaPlayerProfileInfo, playerProfileData, sd);
	REFLECTION_CLASSBUILDER_END(S2C_LoadPlayerProfileData);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_LoadPlayerProfile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_userId, ui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint32, m_lastUpdateTime, lut);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_LoadPlayerProfileData, m_playerProfile, pr);
	REFLECTION_CLASSBUILDER_END(S2C_LoadPlayerProfile);
}
