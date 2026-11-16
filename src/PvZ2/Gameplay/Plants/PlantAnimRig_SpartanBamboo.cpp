//
//  PlantAnimRig_SpartanBamboo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BambooSpartan.h"

PlantAnimRig_SpartanBamboo::PlantAnimRig_SpartanBamboo()
{
	m_hasShield = 1;
	m_berserker = 0;
	m_plantfood_count = (decltype(m_plantfood_count))2;
}

PlantAnimRig_SpartanBamboo::~PlantAnimRig_SpartanBamboo()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_SpartanBamboo);

void PlantAnimRig_SpartanBamboo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_SpartanBamboo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_Shielded);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasShield);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_SpartanBamboo);
}

int PlantAnimRig_SpartanBamboo::GetArmorStateCount()
{
	return false;
}

void PlantAnimRig_SpartanBamboo::SetArmorStateIndex(int i_index)
{
}
