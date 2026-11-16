//
//  Plant_Nightcap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Nightcap.h"

PlantNightcap::PlantNightcap()
{
	m_isInStealthMode = 0;
	m_extraX = 0;
}

PlantNightcap::~PlantNightcap()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantNightcap);

void PlantNightcap::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantNightcap);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isInStealthMode);
		REFLECTION_CLASSBUILDER_FIELD(int, m_extraX);
	REFLECTION_CLASSBUILDER_END(PlantNightcap);
}

void PlantNightcap::stopStealth()
{
}

#include "PlantFramework.h"
void PlantNightcap::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantNightcap::CanApplyPlantfood()
{
	return true;
}

void PlantNightcap::registerForEvents()
{
}

#include "PlantFramework.h"
void PlantNightcap::onDestroy()
{
	 PlantFramework::onDestroy();
}
