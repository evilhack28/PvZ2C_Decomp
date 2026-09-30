//
//  CannonRocket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CannonRocket.h"

void CannonRocket::onDestroy()
{
}

CannonRocket::CannonRocket()
{
}

CannonRocket::~CannonRocket()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CannonRocket);

void CannonRocket::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CannonRocket);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetBoardPixel);
		REFLECTION_CLASSBUILDER_FIELD(float, m_damageAmount);
	REFLECTION_CLASSBUILDER_END(CannonRocket);
}

void CannonRocket::onUpdate()
{
}

bool CannonRocket::ShouldDrawShadow() const
{
	return false;
}
