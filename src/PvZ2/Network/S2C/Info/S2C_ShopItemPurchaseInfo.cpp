//
//  S2C_ShopItemPurchaseInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ShopItemPurchaseInfo);

void S2C_ShopItemPurchaseInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ShopItemPurchaseInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, shop, si);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, item, gi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, amount, q);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, price, ci);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, currency, mi);
	REFLECTION_CLASSBUILDER_END(S2C_ShopItemPurchaseInfo);

}
