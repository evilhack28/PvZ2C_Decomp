//
//  Effect_JewelRabbit_hole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_JewelRabbit.h"

Effect_JewelRabbit_hole::Effect_JewelRabbit_hole()
{
}

Effect_JewelRabbit_hole::~Effect_JewelRabbit_hole()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_JewelRabbit_hole);

void Effect_JewelRabbit_hole::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_JewelRabbit_hole);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_gridPosition);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isDying);
		REFLECTION_CLASSBUILDER_FIELD(CurveSequence_SexyVector3, m_zombieSwallowCurve);
	REFLECTION_CLASSBUILDER_END(Effect_JewelRabbit_hole);
}
