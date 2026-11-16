//
//  CardGameOutro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CardGameOutro.h"

CardGameOutro::CardGameOutro()
{
	m_resultScreen = 0;
	m_challengeWinNum = 0;
}

CardGameOutroProperties::~CardGameOutroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardGameOutro);

void CardGameOutro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardGameOutro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModule);

	REFLECTION_CLASSBUILDER_END(CardGameOutro);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardGameOutroProperties);

void CardGameOutroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardGameOutroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, Modes);
	REFLECTION_CLASSBUILDER_END(CardGameOutroProperties);
}

void CardGameOutro::postInitialize()
{
}

#include "CardGameOutro.h"
void CardGameOutro::onNotifyCardSelectDone()
{
	 CardGameOutro::startBoardFade();
}

#include "CardGameOutro.h"
void CardGameOutro::OnNarrativeTutorialEndCompleted()
{
	 CardGameOutro::onPlayAgain();
}

void CardGameOutro::onUpdate()
{
}

void CardGameOutro::gameStart()
{
}
