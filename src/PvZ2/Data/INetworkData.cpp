//
//  INetworkData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-16.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"

/////////////// Lifecycle ///////////////

INetworkData::INetworkData(const INetworkData &i_other) : RtObject(), DRef(i_other)
{
}

INetworkData::INetworkData(INetworkData &&i_other) : RtObject(), DRef(i_other)
{
}

INetworkData &INetworkData::operator=(const INetworkData &i_other)
{
	DRef::operator=(i_other);
	return *this;
}

INetworkData &INetworkData::operator=(INetworkData &&i_other)
{
	DRef::operator=(i_other);
	return *this;
}

INetworkData::~INetworkData()
{
}

/////////////// Serialization ///////////////

bool INetworkData::SerializeJson(const std::string &i_json)
{
	return SerializeJsonToObj(i_json, "d");
}

std::string INetworkData::SerializeObj()
{
	std::string aJson;
	SerializeObjToJson(aJson, "d");
	return aJson;
}

/////////////// Reflection ///////////////

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(INetworkData);

void INetworkData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_BonusInfo);
	REFLECTION_CLASSBUILDER_END(S2C_BonusInfo);

	REFLECTION_CLASSBUILDER_BEGIN(INetworkData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(INetworkData);
}
