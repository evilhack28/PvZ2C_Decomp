//
//  PaddedRoomModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PaddedRoomModule.h"

PaddedRoomModule::PaddedRoomModule()
{
}

PaddedRoomModule::~PaddedRoomModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PaddedRoomModule);

void PaddedRoomModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PaddedRoomModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(PaddedRoomModule);
}
