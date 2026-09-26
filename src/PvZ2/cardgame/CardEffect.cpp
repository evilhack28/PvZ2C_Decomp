//
//  CardEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "CardEffect.h"

CardEffect::CardEffect()
{
	mEffectState = (decltype(mEffectState))0;
}

CardEffect::~CardEffect()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardEffect);

void CardEffect::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardEffect);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_END(CardEffect);
}
