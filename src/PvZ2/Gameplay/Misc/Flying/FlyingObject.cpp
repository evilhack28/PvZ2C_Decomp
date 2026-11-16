//
//  FlyingObject.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FlyingObject.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FlyingObject);

void FlyingObject::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FlyingObject);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(Sexy::Point, _currentGridPoint);
		REFLECTION_CLASSBUILDER_FIELD(float, _speed);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, _effect);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, _parent);
	REFLECTION_CLASSBUILDER_END(FlyingObject);
}
