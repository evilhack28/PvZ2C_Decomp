//
//  PVZ1ModeOutro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "PVZ1ModeNetworkMgr.h"
#include "PVZ1ModeOutro.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ1ModeOutro);

void PVZ1ModeOutro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1ModeOutro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModule);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(PVZ1ModeOutro);
}

RT_CLASS_IMPLEMENT(PVZ1ModeOutroProperties);

void PVZ1ModeOutroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1ModeOutroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModuleProperties);

	REFLECTION_CLASSBUILDER_END(PVZ1ModeOutroProperties);
}

void PVZ1ModeOutro::postInitialize()
{
}

void PVZ1ModeOutro::gameStart()
{
	m_startTime = PVZ_T();
}
