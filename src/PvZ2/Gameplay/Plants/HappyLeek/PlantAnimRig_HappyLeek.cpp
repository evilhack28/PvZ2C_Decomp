//
//  PlantAnimRig_HappyLeek.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HappyLeek.h"

PlantAnimRig_HappyLeek::~PlantAnimRig_HappyLeek()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HappyLeek);

void PlantAnimRig_HappyLeek::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HappyLeek);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, i_idleTag);
		REFLECTION_CLASSBUILDER_FIELD(int, m_attackcount);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HappyLeek);
}
