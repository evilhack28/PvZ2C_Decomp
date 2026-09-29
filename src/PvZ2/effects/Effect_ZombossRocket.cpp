//
//  Effect_ZombossRocket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_ZombossRocket.h"

Effect_ZombossRocket::Effect_ZombossRocket()
{
	m_IsZomboss = 0;
}

Effect_ZombossRocket::~Effect_ZombossRocket()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_ZombossRocket);

void Effect_ZombossRocket::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_ZombossRocket);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetBoardPixel);
		REFLECTION_CLASSBUILDER_FIELD(CurveCollection_Float, m_curves);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_IsZomboss);
	REFLECTION_CLASSBUILDER_END(Effect_ZombossRocket);
}
