//
//  GridItemZombossRobotBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_PVZ1_Robot.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombossRobotBall);

void GridItemZombossRobotBall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombossRobotBall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(float, m_trajectoriesTimer);
	REFLECTION_CLASSBUILDER_END(GridItemZombossRobotBall);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombossRobotBallProps);
