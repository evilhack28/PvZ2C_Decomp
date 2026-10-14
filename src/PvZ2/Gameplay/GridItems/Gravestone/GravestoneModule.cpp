//
//  GravestoneModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GravestoneModule.h"

GravestoneModule::GravestoneModule()
{
}

GravestoneModule::~GravestoneModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GravestoneModule);

void GravestoneModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GravestoneModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_numSpawnerGravestonesActive);
	REFLECTION_CLASSBUILDER_END(GravestoneModule);
}
