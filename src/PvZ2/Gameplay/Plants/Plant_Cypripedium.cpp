//
//  Plant_Cypripedium.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cypripedium.h"

PlantCypripedium::PlantCypripedium()
{
}

PlantCypripedium::~PlantCypripedium()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCypripedium);

void PlantCypripedium::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCypripedium);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_FIELD(int, m_actionIdx);

	REFLECTION_CLASSBUILDER_END(PlantCypripedium);
}

void PlantCypripedium::UpdateActions()
{
}

#include "PlantFramework.h"
void PlantCypripedium::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
void PlantCypripedium::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantCypripedium::CanApplyPlantfood()
{
	return true;
}
