//
//  ProtectChristmasModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ProtectChristmasModule.h"

bool ProtectChristmasModule::preventSave()
{
	return true;
}

void ProtectChristmasModule::unregisterForEvents()
{
}

void ProtectChristmasModule::onUpdate()
{
}

ProtectChristmasModule::~ProtectChristmasModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ProtectChristmasModule);

void ProtectChristmasModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ProtectChristmasModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_bStart);
	REFLECTION_CLASSBUILDER_FIELD(int, m_nProtectDestroyIndex);

	REFLECTION_CLASSBUILDER_END(ProtectChristmasModule);
}

void ProtectChristmasModule::initializeModule()
{
}
