//
//  PlantAnimRig_LavaGuava.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LavaGuava.h"

PlantAnimRig_LavaGuava::~PlantAnimRig_LavaGuava()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_LavaGuava);

void PlantAnimRig_LavaGuava::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_LavaGuava);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_PopAnim>>, m_linearCrackEffects);
		REFLECTION_CLASSBUILDER_FIELD(int, m_lengthOfCrack);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_startingSquare);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_LavaGuava);
}
