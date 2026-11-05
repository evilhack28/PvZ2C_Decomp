//
//  CardGameRoundModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "AnimationMgr.h"
#include "RenderQueue.h"
#include "CardGameRound.h"
#include "LevelModuleManager.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardGameRoundModule);

/////////////// Lifecycle ///////////////

CardGameRoundModule::CardGameRoundModule()
{
}

CardGameRoundModule::~CardGameRoundModule()
{
	int count = m_Rounds.size();
	for (int i = 0; i < count; i++)
	{
		if (m_Rounds[i] != NULL)
		{
			delete m_Rounds[i];
			m_Rounds[i] = NULL;
		}
	}
	m_Rounds.clear();
}

/////////////// Logic ///////////////

void CardGameRoundModule::postInitialize()
{
	m_Rounds.clear();
}

void CardGameRoundModule::registerForEvents()
{
	getManager()->RegisterOnLevelInit(Sexy::MakeDelegate(*this, &CardGameRoundModule::onLevelInit));
	getManager()->RegisterOnGameplayStarted(Sexy::MakeDelegate(*this, &CardGameRoundModule::onGameplayStarted));
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &CardGameRoundModule::onUpdate));
}

void CardGameRoundModule::onLevelInit()
{
}

void CardGameRoundModule::onGameplayStarted()
{
	m_Rounds.clear();
	const CardGameRoundModuleProperties* props = getProps<CardGameRoundModuleProperties>();
	int count = props->RoundProps.size();
	for (int i = 0; i < count; i++)
	{
		CardGameRound* round = new CardGameRound;
		round->Init(props->RoundProps[i]);
		m_Rounds.push_back(round);
	}
}

void CardGameRoundModule::onUpdate()
{
}

/////////////// Reflection ///////////////

void CardGameRoundModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardGameRoundModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;
	REFLECTION_CLASSBUILDER_END(CardGameRoundModule);
}
