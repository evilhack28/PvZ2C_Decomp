//
//  ChallengeUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ChallengeUI.h"

ChallengeUI::~ChallengeUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ChallengeUI);

void ChallengeUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChallengeUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(int, m_succeeded);
		REFLECTION_CLASSBUILDER_FIELD(Sexy::Color, m_textColor);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_failTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_drawBox);
	REFLECTION_CLASSBUILDER_END(ChallengeUI);
}

void ChallengeUI::initLoadingResourcesGroupList()
{
}

void ChallengeUI::postDraw(Graphics* i_g)
{
}
