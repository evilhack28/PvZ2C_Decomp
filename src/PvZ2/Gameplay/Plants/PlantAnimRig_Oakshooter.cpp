//
//  PlantAnimRig_Oakshooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Oakshooter.h"

PlantAnimRig_Oakshooter::PlantAnimRig_Oakshooter()
{
}

PlantAnimRig_Oakshooter::~PlantAnimRig_Oakshooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Oakshooter);

void PlantAnimRig_Oakshooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Oakshooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isAdvanced);
	REFLECTION_CLASSBUILDER_FIELD(int, m_arrow_type);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Oakshooter);
}
