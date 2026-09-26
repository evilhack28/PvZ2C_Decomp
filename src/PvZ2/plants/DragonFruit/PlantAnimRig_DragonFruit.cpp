//
//  PlantAnimRig_DragonFruit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_DragonFruit.h"

PlantAnimRig_DragonFruit::~PlantAnimRig_DragonFruit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_DragonFruit);

void PlantAnimRig_DragonFruit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_DragonFruit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_blueFire);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_DragonFruit);
}

#include "PlantAnimRig.h"
void PlantAnimRig_DragonFruit::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}

PlantAnimRig_DragonFruit::PlantAnimRig_DragonFruit()
{
	m_blueFire = 0;
}
