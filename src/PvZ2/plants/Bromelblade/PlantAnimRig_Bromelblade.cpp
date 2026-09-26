//
//  PlantAnimRig_Bromelblade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Bromelblade.h"

PlantAnimRig_Bromelblade::~PlantAnimRig_Bromelblade()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Bromelblade);

void PlantAnimRig_Bromelblade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Bromelblade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_IsAvatarEnable);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Bromelblade);
}

PlantAnimRig_Bromelblade::PlantAnimRig_Bromelblade()
{
	m_IsAvatarEnable = 0;
}

void PlantAnimRig_Bromelblade::SetAvatar(bool i_arg)
{
	m_IsAvatarEnable = i_arg;
}
