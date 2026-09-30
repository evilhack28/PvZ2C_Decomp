//
//  RiverCrossingModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RiverCrossingModule.h"

bool RiverCrossingModule::preventSave()
{
	return true;
}

void RiverCrossingModule::levelStarted()
{
}

void RiverCrossingModule::postInitialize()
{
}

RiverCrossingModule::~RiverCrossingModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiverCrossingModule);

void RiverCrossingModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiverCrossingModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_TimeFailure);
		REFLECTION_CLASSBUILDER_FIELD(RiverCrossingTarget, m_riverCrossingTarget);
		REFLECTION_CLASSBUILDER_FIELD(Sexy::TouchID, m_touchIdent);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_touchStart);
		REFLECTION_CLASSBUILDER_FIELD(RiverEntitiesManager, m_RiverEntitiesManager);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<StarvingChomper *>, m_starvingChompers);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RiverCrossingDodoRider *>, m_arrivedDodoRiders);
	REFLECTION_CLASSBUILDER_END(RiverCrossingModule);
}

void RiverCrossingModule::initializeModule()
{
}

void RiverCrossingModule::onRiverEntitySpawned(class RiverEntity * i_arg)
{
}
