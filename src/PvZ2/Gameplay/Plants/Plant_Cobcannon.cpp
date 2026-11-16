//
//  Plant_Cobcannon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cobcannon.h"

PlantCobcannon::~PlantCobcannon()
{
}

PlantTypeCobcannon::PlantTypeCobcannon()
{
}

PlantTypeCobcannon::~PlantTypeCobcannon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCobcannon);

void PlantCobcannon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCobcannon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_target);
	REFLECTION_CLASSBUILDER_END(PlantCobcannon);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeCobcannon);
