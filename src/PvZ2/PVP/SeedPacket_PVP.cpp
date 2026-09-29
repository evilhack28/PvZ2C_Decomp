//
//  SeedPacket_PVP.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SeedPacket_PVP.h"

SeedPacket_PVP::~SeedPacket_PVP()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SeedPacket_PVP);

void SeedPacket_PVP::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SeedPacket_PVP);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedPacket);

	REFLECTION_CLASSBUILDER_END(SeedPacket_PVP);
}
