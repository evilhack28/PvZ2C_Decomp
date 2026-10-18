//
//  NewAvatarGeneralSkillBoost.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "PlantNewAvatarCommon.h"

NewAvatarGeneralSkillBoost::~NewAvatarGeneralSkillBoost()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(NewAvatarGeneralSkillBoost);

void NewAvatarGeneralSkillBoost::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NewAvatarGeneralSkillBoost);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantNewAvatar);

		REFLECTION_CLASSBUILDER_FIELD(float, BoostRate);
	REFLECTION_CLASSBUILDER_END(NewAvatarGeneralSkillBoost);
}
