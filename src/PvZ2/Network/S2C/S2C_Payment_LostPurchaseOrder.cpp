//
//  S2C_Payment_LostPurchaseOrder.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_Payment_LostPurchaseOrder);

void S2C_Payment_LostPurchaseOrder::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NetworkPaymentInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, orderId, on);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, skuId, pdi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<PaymentBundleInfo>, bundleInfos, ol);
	REFLECTION_CLASSBUILDER_END(NetworkPaymentInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_Payment_LostPurchaseOrder);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NetworkPaymentInfo>, m_payments, pl);
	REFLECTION_CLASSBUILDER_END(S2C_Payment_LostPurchaseOrder);

}
