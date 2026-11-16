//
//  PlantAnimRig_MagicBeans.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_MagicBeans.h"

PlantAnimRig_MagicBeans::PlantAnimRig_MagicBeans()
{
}

PlantAnimRig_MagicBeans::~PlantAnimRig_MagicBeans()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_MagicBeans);

void PlantAnimRig_MagicBeans::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_MagicBeans);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_submerged);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_MagicBeans);
}
