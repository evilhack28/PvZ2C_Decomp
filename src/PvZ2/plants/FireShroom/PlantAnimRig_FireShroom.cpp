//
//  PlantAnimRig_FireShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FireShroom.h"

PlantAnimRig_FireShroom::~PlantAnimRig_FireShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_FireShroom);

void PlantAnimRig_FireShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_FireShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_IceShroom);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isLevel5Attack);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_FireShroom);
}
