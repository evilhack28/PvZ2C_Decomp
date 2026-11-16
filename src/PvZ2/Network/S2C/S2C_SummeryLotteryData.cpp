//
//  S2C_SummeryLotteryData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

S2C_SummeryLotteryData::S2C_SummeryLotteryData() : m_luck(0), m_totalLuck(0)
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_SummeryLotteryData);

void S2C_SummeryLotteryData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_SummeryLotteryData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(VacationMaterialItem, normalBonus, b);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(VacationMaterialItem, specialBonus, s);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<VacationMaterialItem>, m_material, il);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_luck, lt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_totalLuck, mt);
	REFLECTION_CLASSBUILDER_END(S2C_SummeryLotteryData);

}
