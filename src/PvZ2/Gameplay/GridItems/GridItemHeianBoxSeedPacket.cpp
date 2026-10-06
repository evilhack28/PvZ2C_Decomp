//
//  GridItemHeianBoxSeedPacket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHeianBox.h"

GridItemHeianBoxSeedPacket::GridItemHeianBoxSeedPacket()
{
	m_endTime = PVZ_EOT();
}

GridItemHeianBoxSeedPacket::~GridItemHeianBoxSeedPacket()
{
}

GridItemHeianBoxSeedPacketProps::~GridItemHeianBoxSeedPacketProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxSeedPacket);

void GridItemHeianBoxSeedPacket::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxSeedPacket);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBox);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_endTime);
	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxSeedPacket);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxSeedPacketProps);

void GridItemHeianBoxSeedPacketProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxSeedPacketProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBoxProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PresetList);
		REFLECTION_CLASSBUILDER_FIELD(float, DisableTime);
	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxSeedPacketProps);
}
