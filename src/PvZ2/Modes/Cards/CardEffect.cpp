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
	mEffectState = CES_Invalid;
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

/////////////// Logic ///////////////

void CardEffect::InitializaEffect(CardEffectPropsPtr i_effectProps, RtWeakPtr<CardObject> i_cardObject)
{
	mEffectProps = i_effectProps;
	mCardObject = i_cardObject;
	mEffectState = CES_Initializa;
}

void CardEffect::DoEffect()
{
	mEffectState = CES_Starting;
}

void CardEffect::Interrupt()
{
	mEffectState = CES_Finish;
}

CardEffectState CardEffect::GetEffctState()
{
	return mEffectState;
}
