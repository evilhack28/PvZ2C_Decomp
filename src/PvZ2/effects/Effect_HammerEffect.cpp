//
//  Effect_HammerEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WhackAMoleModule.h"

Effect_HammerEffect::Effect_HammerEffect()
{
}

Effect_HammerEffect::~Effect_HammerEffect()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_HammerEffect);

void Effect_HammerEffect::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_HammerEffect);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_HammerEffect);
}

void Effect_HammerEffect::Destroy()
{
	 GameObject::Destroy();
}

void Effect_HammerEffect::onAnimStopped(const std::string& i_animLabel)
{
}
