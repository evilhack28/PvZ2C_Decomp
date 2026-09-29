//
//  Plant_FireShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FireShroom.h"

PlantFireShroom::PlantFireShroom()
{
	m_isLevel5Attack = 0;
}

PlantFireShroom::~PlantFireShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFireShroom);

void PlantFireShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFireShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantIceShroom);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isLevel5Attack);
	REFLECTION_CLASSBUILDER_END(PlantFireShroom);
}

void PlantFireShroom::onSetDuplicate(bool i_arg)
{
}

bool PlantFireShroom::CanApplyPlantfood()
{
	return true;
}
