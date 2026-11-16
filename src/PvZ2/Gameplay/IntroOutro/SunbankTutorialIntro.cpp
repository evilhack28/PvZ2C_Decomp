//
//  SunbankTutorialIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SunbankTutorialIntro.h"

SunbankTutorialIntro::SunbankTutorialIntro()
{
}

SunbankTutorialIntro::~SunbankTutorialIntro()
{
}

SunbankTutorialIntroProperties::SunbankTutorialIntroProperties()
{
}

SunbankTutorialIntroProperties::~SunbankTutorialIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SunbankTutorialIntro);

void SunbankTutorialIntro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SunbankTutorialIntro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isTutorialEnd);
	REFLECTION_CLASSBUILDER_END(SunbankTutorialIntro);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SunbankTutorialIntroProperties);

void SunbankTutorialIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SunbankTutorialIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(SunbankTutorialIntroProperties);
}
