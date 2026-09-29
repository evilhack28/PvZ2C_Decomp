//
//  ArcadeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ArcadeModule.h"

ArcadeModule::ArcadeModule()
{
}

ArcadeModule::~ArcadeModule()
{
}

ArcadeModuleProperties::ArcadeModuleProperties()
{
}

ArcadeModuleProperties::~ArcadeModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArcadeModule);

void ArcadeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArcadeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(ArcadeModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArcadeModuleProperties);

void ArcadeModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArcadeModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(ArcadeModuleProperties);
}

#include "ArcadeModule.h"
void ArcadeModule::onPostLoad()
{
	 ArcadeModule::onAnyLoad();
}
