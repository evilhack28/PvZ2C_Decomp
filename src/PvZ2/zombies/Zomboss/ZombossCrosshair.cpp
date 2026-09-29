//
//  ZombossCrosshair.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombossCrosshair.h"

void ZombossCrosshair::CounterRocketEffect()
{
}

void ZombossCrosshair::CounterCrosshairEffect()
{
}

void ZombossCrosshair::FadeOutCrosshairEffect()
{
}

ZombossCrosshair::ZombossCrosshair()
{
}

ZombossCrosshair::~ZombossCrosshair()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossCrosshair);

void ZombossCrosshair::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossCrosshair);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetSquare);
	REFLECTION_CLASSBUILDER_END(ZombossCrosshair);
}

void ZombossCrosshair::StartRocketEffect(const std::string& i_arg0, const std::string& i_arg1, float i_arg2, float i_arg3)
{
}

void ZombossCrosshair::onUpdate()
{
}
