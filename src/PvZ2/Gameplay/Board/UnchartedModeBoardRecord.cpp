//
//  UnchartedModeBoardRecord.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UnchartedModeNetworkMgr.h"

/////////////// Logic ///////////////

std::string UnchartedModeBoardRecord::SerializeObj()
{
	std::string aJson;
	SerializeObjToJson(aJson, "d");
	return aJson;
}

bool UnchartedModeBoardRecord::SerializeJson(const std::string &i_json)
{
	return SerializeJsonToObj(i_json, "d");
}
