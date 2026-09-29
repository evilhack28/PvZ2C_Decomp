//
//  Plant_IcyCurrant.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_IcyCurrant.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantIcyCurrant);

void PlantIcyCurrant::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantIcyCurrant);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<IcyCurrantFence> >, m_fence);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isPowered);
	REFLECTION_CLASSBUILDER_END(PlantIcyCurrant);
}

#include "Plant_IcyCurrant.h"
void PlantIcyCurrant::OnRelocationBegun()
{
	 PlantIcyCurrant::ReleaseFence();
}

void PlantIcyCurrant::onKilled(bool i_arg)
{
}
