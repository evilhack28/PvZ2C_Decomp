//
//  PlantAnimRig_PotatoMine.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_PotatoMine.h"

PlantAnimRig_PotatoMine::PlantAnimRig_PotatoMine()
{
}

PlantAnimRig_PotatoMine::~PlantAnimRig_PotatoMine()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_PotatoMine);

void PlantAnimRig_PotatoMine::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_PotatoMine);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_submerged);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_PotatoMine);
}
