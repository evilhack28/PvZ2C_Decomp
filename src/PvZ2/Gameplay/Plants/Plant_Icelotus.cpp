//
//  Plant_Icelotus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Icelotus.h"

PlantIcelotus::PlantIcelotus()
{
	_lifeLeftTime = (decltype(_lifeLeftTime))3;
	_lifeTimeMax = (decltype(_lifeTimeMax))3;
	_layerLimit1 = (decltype(_layerLimit1))2;
	_layerLimit2 = 1;
	_recoveryTime = PVZ_EOT();
}

PlantIcelotus::~PlantIcelotus()
{
}

PlantIcelotusProps::~PlantIcelotusProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantIcelotus);

void PlantIcelotus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantIcelotus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _recoveryTime);
	REFLECTION_CLASSBUILDER_END(PlantIcelotus);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantIcelotusProps);

void PlantIcelotusProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantIcelotusProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, FreezeRatio);
	REFLECTION_CLASSBUILDER_END(PlantIcelotusProps);
}

bool PlantIcelotus::FindHanabi()
{
	return true;
}

bool PlantIcelotus::CanApplyPlantfood()
{
	return true;
}
