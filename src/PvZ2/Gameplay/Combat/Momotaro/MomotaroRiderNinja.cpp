//
//  MomotaroRiderNinja.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "MomotaroRiderNinja.h"

MomotaroRiderNinja::MomotaroRiderNinja()
{
}

MomotaroRiderNinja::~MomotaroRiderNinja()
{
}

MomotaroRiderNinjaPropertySheet::~MomotaroRiderNinjaPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MomotaroRiderNinja);

void MomotaroRiderNinja::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MomotaroRiderNinja);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantEggplantNinja);

	REFLECTION_CLASSBUILDER_END(MomotaroRiderNinja);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MomotaroRiderNinjaPropertySheet);

void MomotaroRiderNinjaPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MomotaroRiderNinjaPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(EggplantNinjaPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, SearchGrids);
	REFLECTION_CLASSBUILDER_END(MomotaroRiderNinjaPropertySheet);
}

bool MomotaroRiderNinja::CanApplyPlantfood()
{
	return false;
}
