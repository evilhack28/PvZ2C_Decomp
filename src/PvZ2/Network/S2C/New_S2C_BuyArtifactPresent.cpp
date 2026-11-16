//
//  New_S2C_BuyArtifactPresent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"
#include "UIArtifactPresent.h"

New_S2C_BuyArtifactPresent::New_S2C_BuyArtifactPresent()
{
}

New_S2C_BuyArtifactPresent::~New_S2C_BuyArtifactPresent()
{
}

void New_S2C_BuyArtifactPresent::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_BuyArtifactPresent);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<NetworkArtifactPresentContent>, m_rewards, b);
	REFLECTION_CLASSBUILDER_END(New_S2C_BuyArtifactPresent);
}

RT_CLASS_IMPLEMENT(New_S2C_BuyArtifactPresent);
