//
//  PurchaseConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "PurchaseBroker.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PurchaseConfig);

void PurchaseConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PurchaseConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ErrorProvincePurchase);
		REFLECTION_CLASSBUILDER_FIELD(bool, ShowPurchaseConfirm);
	REFLECTION_CLASSBUILDER_END(PurchaseConfig);
}
