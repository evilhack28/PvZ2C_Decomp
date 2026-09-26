//
//  PennyClassroomModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PennyClassroomModule.h"

PennyClassroomModule::PennyClassroomModule()
{
}

PennyClassroomModule::~PennyClassroomModule()
{
}

PennyClassroomModuleProperties::PennyClassroomModuleProperties()
{
}

PennyClassroomModuleProperties::~PennyClassroomModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyClassroomModule);

void PennyClassroomModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyClassroomModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(PennyClassroomModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyClassroomModuleProperties);

void PennyClassroomModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyClassroomModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA int>, PlantMap);

	REFLECTION_CLASSBUILDER_END(PennyClassroomModuleProperties);
}

void PennyClassroomModule::registerForEvents()
{
}
