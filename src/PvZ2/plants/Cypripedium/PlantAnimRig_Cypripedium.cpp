//
//  PlantAnimRig_Cypripedium.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cypripedium.h"

PlantAnimRig_Cypripedium::~PlantAnimRig_Cypripedium()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Cypripedium);

void PlantAnimRig_Cypripedium::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Cypripedium);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, m_mode);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_isLv5);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Cypripedium);
}

std::string PlantAnimRig_Cypripedium::getPlantFoodMainAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}

PlantAnimRig_Cypripedium::PlantAnimRig_Cypripedium()
{
	m_mode = 1;
	m_isLv5 = 0;
}

void PlantAnimRig_Cypripedium::SetIsLevel5(bool i_arg)
{
	m_isLv5 = i_arg;
}

void PlantAnimRig_Cypripedium::SetAttackMode(int i_arg)
{
	m_mode = i_arg;
}
