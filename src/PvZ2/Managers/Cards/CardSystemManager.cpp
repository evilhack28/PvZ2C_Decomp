//
//  CardSystemManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "CardSystem.h"
#include "CardObject.h"
#include "CardInfluence.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardSystemManager);

/////////////// Lifecycle ///////////////

CardSystemManager::CardSystemManager()
{
}

CardSystemManager::~CardSystemManager()
{
}

/////////////// Logic ///////////////

void CardSystemManager::Update()
{
}

RtWeakPtr<CardObject> CardSystemManager::CreateCardByID(int i_cardID)
{
	RtWeakPtr<CardObject> card = GameObject::Create(CardObject::StaticGetClass(), PVZDB::TABLE_CARD_OBJECTS)->GetPtr();
	card->initializeCardObject(CardUtils::GetCardType(i_cardID));
	mCardList.push_back(card);
	return card;
}

RtWeakPtr<CardObject> CardSystemManager::CreateCardByType(RtWeakPtr<CardObject> i_cardType)
{
	RtWeakPtr<CardObject> card = GameObject::Create(CardObject::StaticGetClass(), PVZDB::TABLE_CARD_OBJECTS)->GetPtr();
	card->initializeCardObject(i_cardType);
	mCardList.push_back(card);
	return card;
}

RtWeakPtr<InfluenceAura> CardSystemManager::RegisterAura(InfluenceAuraPropsPtr i_auraProps)
{
	RtClass* auraClass = i_auraProps->GetAuraClass();
	if (auraClass != NULL)
	{
		RtWeakPtr<InfluenceAura> aura = GameObject::Create(auraClass, PVZDB::TABLE_CARD_OBJECTS)->GetPtr();
		aura->InitializaAura(i_auraProps);
		mCardAuraMgr.RegisterAura(aura);
		return aura;
	}
	return RtWeakPtr<InfluenceAura>(nullptr);
}

void CardSystemManager::DeleteCard(RtWeakPtr<CardObject> i_cardObjectPtr)
{
	std::vector<RtWeakPtr<CardObject>>::iterator it = mCardList.begin();
	for (; it != mCardList.end(); ++it)
	{
		if (*it == i_cardObjectPtr)
		{
			mCardList.erase(it);
			if (i_cardObjectPtr.IsValid())
				i_cardObjectPtr->Destroy();
			i_cardObjectPtr.ClearId();
			return;
		}
	}
}

/////////////// Reflection ///////////////

void CardSystemManager::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardSystemManager);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;
	REFLECTION_CLASSBUILDER_END(CardSystemManager);
}
