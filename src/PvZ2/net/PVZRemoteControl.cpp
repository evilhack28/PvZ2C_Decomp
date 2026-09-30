//
//  PVZRemoteControl.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZRemoteControl.h"

void PVZRemoteControl::Play()
{
}

PVZRemoteControl::PVZRemoteControl()
{
}

PVZRemoteControl::~PVZRemoteControl()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZRemoteControl);

void PVZRemoteControl::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZRemoteControl);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(PVZRemoteControl);
}
