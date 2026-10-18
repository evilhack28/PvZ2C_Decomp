//
//  New_S2C_BuyNewerPresent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"
#include "UINewerPresent.h"

New_S2C_BuyNewerPresent::New_S2C_BuyNewerPresent()
{
}

New_S2C_BuyNewerPresent::~New_S2C_BuyNewerPresent()
{
}

void New_S2C_BuyNewerPresent::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_BuyNewerPresent);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<NetworkPresentContent>, m_rewards, b);
	REFLECTION_CLASSBUILDER_END(New_S2C_BuyNewerPresent);
}

RT_CLASS_IMPLEMENT(New_S2C_BuyNewerPresent);
