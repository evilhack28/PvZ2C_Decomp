//
//  SeedPacket_DangerRoom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SeedPacket_DangerRoom.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SeedPacket_DangerRoom);

void SeedPacket_DangerRoom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SeedPacket_DangerRoom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedPacket_PVP);

	REFLECTION_CLASSBUILDER_END(SeedPacket_DangerRoom);
}
