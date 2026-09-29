//
//  HotUISeedPacket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUISeedPacket.h"

HotUISeedPacket::~HotUISeedPacket()
{
}

HotUISeedPacketProperties::HotUISeedPacketProperties()
{
}

HotUISeedPacketProperties::~HotUISeedPacketProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUISeedPacket);

void HotUISeedPacket::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUISeedPacket);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUISeedPacket);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUISeedPacketProperties);

void HotUISeedPacketProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUISeedPacketProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

		REFLECTION_CLASSBUILDER_FIELD(HotUISeedPacketConfig, PacketConfig);
	REFLECTION_CLASSBUILDER_END(HotUISeedPacketProperties);
	REFLECTION_CLASSBUILDER_BEGIN(HotUISeedPacketConfig);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantType);
		REFLECTION_CLASSBUILDER_FIELD(bool, IsImitater);
		REFLECTION_CLASSBUILDER_FIELD(int, PlantLevel);
	REFLECTION_CLASSBUILDER_END(HotUISeedPacketConfig);

}
