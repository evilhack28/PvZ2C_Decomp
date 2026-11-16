//
//  PlantAnimRig_OlivePit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OlivePit.h"

PlantAnimRig_OlivePit::PlantAnimRig_OlivePit()
{
}

PlantAnimRig_OlivePit::~PlantAnimRig_OlivePit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_OlivePit);

void PlantAnimRig_OlivePit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_OlivePit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_chewLoopEnd);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_avatar);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_OlivePit);
}
