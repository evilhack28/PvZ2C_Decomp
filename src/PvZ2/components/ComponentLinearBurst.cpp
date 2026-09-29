//
//  ComponentLinearBurst.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ComponentLinearBurst.h"

ComponentLinearBurst::~ComponentLinearBurst()
{
}

ComponentLinearBurstProps::~ComponentLinearBurstProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentLinearBurst);

void ComponentLinearBurst::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DamageWithWeight);
		REFLECTION_CLASSBUILDER_FIELD(DamageInfoProps, DamageProps);
	REFLECTION_CLASSBUILDER_END(DamageWithWeight);

	REFLECTION_CLASSBUILDER_BEGIN(ComponentLinearBurstProps);
		REFLECTION_CLASSBUILDER_FIELD(TargetInfoProps, TargetProps);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DamageWithWeight>, DamagePropsVec);
	REFLECTION_CLASSBUILDER_END(ComponentLinearBurstProps);

	REFLECTION_CLASSBUILDER_BEGIN(ComponentLinearBurst);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ComponentBase);

		REFLECTION_CLASSBUILDER_FIELD(ComponentLinearBurstProps, m_props);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextCreateColumnEffectTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_distanceOfBurst);
	REFLECTION_CLASSBUILDER_END(ComponentLinearBurst);
}
