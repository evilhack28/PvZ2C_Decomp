//
//  PowerupType.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupType.h"

PowerupType::~PowerupType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupType);

void PowerupType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

	REFLECTION_CLASSBUILDER_FIELD(Color, BoardTimerColor);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, AdditionCost);
	REFLECTION_CLASSBUILDER_FIELD(PurchaseType, m_purchaseType);

	REFLECTION_CLASSBUILDER_END(PowerupType);
}
