//
//  MomotaroRiderModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "MomotaroRiderModule.h"

MomotaroRiderModule::MomotaroRiderModule()
{
	m_riderHitByNinja = 0;
}

MomotaroRiderModule::~MomotaroRiderModule()
{
}

MomotaroRiderModuleProperties::~MomotaroRiderModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MomotaroRiderModule);

void MomotaroRiderModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MomotaroRiderModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RiverCrossingModule);

	REFLECTION_CLASSBUILDER_END(MomotaroRiderModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MomotaroRiderModuleProperties);

void MomotaroRiderModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NinjaProperties);
	REFLECTION_CLASSBUILDER_END(NinjaProperties);

	REFLECTION_CLASSBUILDER_BEGIN(MomotaroRiderModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RiverCrossingProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<NinjaProperties>, NinjaPlacements);
	REFLECTION_CLASSBUILDER_END(MomotaroRiderModuleProperties);
}

bool MomotaroRiderModule::isInRiver(Point point)
{
	return false;
}
