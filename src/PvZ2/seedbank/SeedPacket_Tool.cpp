//
//  SeedPacket_Tool.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SeedPacket_Tool.h"

SeedPacket_Tool::SeedPacket_Tool()
{
}

SeedPacket_Tool::~SeedPacket_Tool()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SeedPacket_Tool);

void SeedPacket_Tool::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SeedPacket_Tool);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedPacket);

	REFLECTION_CLASSBUILDER_END(SeedPacket_Tool);
}

SunCurrency SeedPacket_Tool::GetSunCost()
{
	return (SunCurrency)false;
}

bool SeedPacket_Tool::NeedDrawOffset()
{
	return true;
}
