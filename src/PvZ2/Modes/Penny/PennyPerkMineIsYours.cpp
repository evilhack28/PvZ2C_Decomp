//
//  PennyPerkMineIsYours.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PennyPerkMineIsYours.h"

PennyPerkMineIsYours::PennyPerkMineIsYours()
{
}

PennyPerkMineIsYours::~PennyPerkMineIsYours()
{
}

PennyPerkMineIsYoursProperties::PennyPerkMineIsYoursProperties()
{
}

PennyPerkMineIsYoursProperties::~PennyPerkMineIsYoursProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkMineIsYours);

void PennyPerkMineIsYours::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkMineIsYours);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkTimedEffect);

	REFLECTION_CLASSBUILDER_END(PennyPerkMineIsYours);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkMineIsYoursProperties);

void PennyPerkMineIsYoursProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkMineIsYoursProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantTypeToSpawn);
	REFLECTION_CLASSBUILDER_END(PennyPerkMineIsYoursProperties);
}

#include "PennyPerkMineIsYours.h"
void PennyPerkMineIsYours::onUpdate()
{
	 PennyPerkMineIsYours::applyCondition();
}
