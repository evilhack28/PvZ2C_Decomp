//
//  FlyingFireball.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FlyingFireball.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FlyingFireball);

void FlyingFireball::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FlyingFireball);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_burnTime);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetLocation);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_spawnDragonImp);
		REFLECTION_CLASSBUILDER_FIELD(CurveCollection_Float, m_movementCurves);
	REFLECTION_CLASSBUILDER_END(FlyingFireball);
}
