//
//  RiftSchedule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RiftSchedule.h"

RiftSchedule::~RiftSchedule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftSchedule);

void RiftSchedule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftSubEventDefinition);
		REFLECTION_CLASSBUILDER_FIELD(std::string, SubEventPropertyKey);
	REFLECTION_CLASSBUILDER_END(RiftSubEventDefinition);

	REFLECTION_CLASSBUILDER_BEGIN(RiftEventDefinition);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RiftSubEventDefinition>, SubEvents);
	REFLECTION_CLASSBUILDER_END(RiftEventDefinition);

	REFLECTION_CLASSBUILDER_BEGIN(RiftSchedule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RiftEventDefinition>, Events);
	REFLECTION_CLASSBUILDER_END(RiftSchedule);
}
