//
//  RiftThemeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RiftThemeModule.h"

RiftThemeModule::RiftThemeModule()
{
}

RiftThemeModule::~RiftThemeModule()
{
}

RiftThemeModuleProperties::RiftThemeModuleProperties()
{
}

RiftThemeModuleProperties::~RiftThemeModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftThemeModule);

void RiftThemeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftThemeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(RiftThemeModule);
}

#include "RiftThemeModule.h"
void RiftThemeModule::onInit()
{
	 RiftThemeModule::initializeThemes();
}
