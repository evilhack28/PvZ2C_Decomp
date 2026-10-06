//
//  PowerupPurchaseIntroProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupPurchaseIntro.h"

PowerupPurchaseIntroProperties::PowerupPurchaseIntroProperties()
{
}

PowerupPurchaseIntroProperties::~PowerupPurchaseIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupPurchaseIntroProperties);

void PowerupPurchaseIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupPurchaseIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(PowerupPurchaseIntroProperties);
}
