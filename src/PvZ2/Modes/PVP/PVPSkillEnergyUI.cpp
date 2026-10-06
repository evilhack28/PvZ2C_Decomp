//
//  PVPSkillEnergyUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVPSkillEnergyUI.h"

PVPSkillEnergyUI::~PVPSkillEnergyUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVPSkillEnergyUI);

void PVPSkillEnergyUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVPSkillEnergyUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(PVPSkillEnergyUI);
}
