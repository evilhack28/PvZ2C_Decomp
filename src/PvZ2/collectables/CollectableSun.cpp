//
//  CollectableSun.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CollectableSun.h"

CollectableSun::CollectableSun()
{
}

CollectableSun::~CollectableSun()
{
}

CollectableSunType::~CollectableSunType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableSun);

void CollectableSun::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableSun);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Collectable);

		REFLECTION_CLASSBUILDER_FIELD(SunType, m_sunType);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_selfAutoCollect);
	REFLECTION_CLASSBUILDER_END(CollectableSun);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableSunType);

void CollectableSunType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableSunType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

		REFLECTION_CLASSBUILDER_FIELD(int, SunValue);
	REFLECTION_CLASSBUILDER_END(CollectableSunType);
}
