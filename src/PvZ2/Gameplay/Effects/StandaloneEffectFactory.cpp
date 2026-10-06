//
//  StandaloneEffectFactory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "StandaloneEffectFactory.h"
#include "StandaloneEffect.h"
#include "Effect_PopAnim.h"
#include "Effect_StaticImage.h"

/////////////// StandaloneEffectFactory ///////////////

StandaloneEffectFactory::StandaloneEffectFactory(PVZDB::TableIndex i_table)
	: mTableIndex(i_table)
{
}

StandaloneEffect* StandaloneEffectFactory::AddEffect(Sexy::RtClass *i_effectClass)
{
	return GameObject::Create(i_effectClass, mTableIndex)->CastChecked<StandaloneEffect>();
}

Effect_StaticImage* StandaloneEffectFactory::CreateCenteredScreenSpaceEffectStaticImage()
{
	Effect_StaticImage *effect = AddEffect<Effect_StaticImage>()->CastChecked<Effect_StaticImage>();
	effect->SetIsScreenSpaceEffect(true);
	effect->SetCentered(true);
	effect->SetKeepAlive(true);
	return effect;
}

Effect_PopAnim* StandaloneEffectFactory::CreateCenteredScreenSpaceEffectPopAnim()
{
	Effect_PopAnim *effect = AddEffect<Effect_PopAnim>()->CastChecked<Effect_PopAnim>();
	effect->SetIsScreenSpaceEffect(true);
	effect->SetCentered(true);
	effect->SetKeepAlive(true);
	return effect;
}

StandaloneEffectFactory& StandaloneEffectFactory::GetEffectsTableFactory()
{
	static StandaloneEffectFactory sFactory(PVZDB::TableIndex(0x31));
	return sFactory;
}

StandaloneEffectFactory& StandaloneEffectFactory::GetOutsideOfTableFactory()
{
	static StandaloneEffectFactory sFactory(PVZDB::TableIndex(-1));
	return sFactory;
}
