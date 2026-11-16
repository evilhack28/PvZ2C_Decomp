//
//  PlantAnimRig_Flamelady.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Flamelady.h"

PlantAnimRig_Flamelady::PlantAnimRig_Flamelady()
{
	m_fireState = 0;
}

PlantAnimRig_Flamelady::~PlantAnimRig_Flamelady()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Flamelady);

void PlantAnimRig_Flamelady::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Flamelady);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int, m_fireState);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Flamelady);
}

#include "PlantAnimRig.h"
void PlantAnimRig_Flamelady::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
