//
//  ComponentPlantLauncher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ComponentPlantLauncher.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentPlantLauncher);

void ComponentPlantLauncher::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentPlantLauncher);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_owner);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_cursorTextureName);
	REFLECTION_CLASSBUILDER_END(ComponentPlantLauncher);
}
