//
//  ZombieAnimRig_LostCityGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityGargantuar.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_LostCityGargantuar::~ZombieAnimRig_LostCityGargantuar()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_LostCityGargantuar);

void ZombieAnimRig_LostCityGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_LostCityGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Gargantuar);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_hasTorch);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_LostCityGargantuar);
}

/////////////// Logic ///////////////

void ZombieAnimRig_LostCityGargantuar::SetTorchLayers(bool i_visible)
{
	if (m_hasTorch != i_visible)
	{
		m_hasTorch = i_visible;
		SetLayerVisibility("torch_end_lit", m_hasTorch);
		SetLayerVisibility("torch_fire_frame_01", m_hasTorch);
		SetLayerVisibility("torch_fire_fire_frame_01", m_hasTorch);
		SetLayerVisibility("torch_fire_frame_02", m_hasTorch);
		SetLayerVisibility("torch_fire_frame_03", m_hasTorch);
		SetLayerVisibility("torch_fire_frame_04", m_hasTorch);
	}
}
