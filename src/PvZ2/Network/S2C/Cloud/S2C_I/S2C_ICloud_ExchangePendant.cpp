//
//  S2C_ICloud_ExchangePendant.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_ExchangePendant);

void S2C_ICloud_ExchangePendant::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_ExchangePendant);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlantPendantInfo, m_plantPendantInfo, pe);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_BonusInfo, m_plantPendantChipInfo, pec);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_ExchangePendant);
}
