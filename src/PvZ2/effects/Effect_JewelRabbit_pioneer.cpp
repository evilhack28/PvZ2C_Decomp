//
//  Effect_JewelRabbit_pioneer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_JewelRabbit.h"

Effect_JewelRabbit_pioneer::Effect_JewelRabbit_pioneer()
{
	m_hasCompletedSecondStage = 0;
}

Effect_JewelRabbit_pioneer::~Effect_JewelRabbit_pioneer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_JewelRabbit_pioneer);

void Effect_JewelRabbit_pioneer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_JewelRabbit_pioneer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_gridPosition);
		REFLECTION_CLASSBUILDER_FIELD(std::function<void(bool)>, m_retreatFunc);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasCompletedSecondStage);
	REFLECTION_CLASSBUILDER_END(Effect_JewelRabbit_pioneer);
}
