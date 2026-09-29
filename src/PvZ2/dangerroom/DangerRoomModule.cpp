//
//  DangerRoomModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DangerRoomModule.h"

DangerRoomModuleProperties::DangerRoomModuleProperties()
{
}

DangerRoomModuleProperties::~DangerRoomModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DangerRoomModule);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DangerRoomModuleProperties);

void DangerRoomModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DangerRoomModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<WorldSpecificDangerRoomProperties>, WorldSpecificProperties);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<DangerRoomLevelDesigner> >, LevelDesigners);
	REFLECTION_CLASSBUILDER_END(DangerRoomModuleProperties);
}

#include "DangerRoomModule.h"
void DangerRoomModule::initGamePlay()
{
	 DangerRoomModule::setupMowerInformation();
}

void DangerRoomModule::onLevelEnded()
{
}
