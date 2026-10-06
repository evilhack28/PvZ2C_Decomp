//
//  ZombossRocket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombossRocket.h"

ZombossRocket::ZombossRocket()
{
}

ZombossRocket::~ZombossRocket()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossRocket);

void ZombossRocket::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossRocket);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetSquare);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_AutoDestoryTime);
	REFLECTION_CLASSBUILDER_END(ZombossRocket);
}
