//
//  Plant_LilyPad.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LilyPad.h"

PlantLilyPad::PlantLilyPad()
{
}

PlantLilyPad::~PlantLilyPad()
{
}

PlantTypeLilyPad::PlantTypeLilyPad()
{
}

PlantTypeLilyPad::~PlantTypeLilyPad()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantLilyPad);

void PlantLilyPad::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantLilyPad);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantLilyPad);
}
