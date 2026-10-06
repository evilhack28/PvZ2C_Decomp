//
//  WaveActionSnowBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WaveActionSnowBall.h"

WaveActionSnowBall::WaveActionSnowBall()
{
}

WaveActionSnowBall::~WaveActionSnowBall()
{
}

WaveActionSnowBallProps::~WaveActionSnowBallProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveActionSnowBall);

void WaveActionSnowBall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveActionSnowBall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(WaveActionSnowBall);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveActionSnowBallProps);

void WaveActionSnowBallProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SnowBallData);
	REFLECTION_CLASSBUILDER_END(SnowBallData);

	REFLECTION_CLASSBUILDER_BEGIN(WaveActionSnowBallProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<SnowBallData>, SnowBalls);
	REFLECTION_CLASSBUILDER_END(WaveActionSnowBallProps);
}

void WaveActionSnowBall::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void WaveActionSnowBall::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
