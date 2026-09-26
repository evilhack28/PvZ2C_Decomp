//
//  ArenaInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArenaInfo.h"

ArenaInfo::~ArenaInfo()
{
}

ArenaInfo::ArenaInfo()
{
	ArenaPlantList1.clear();
	ArenaPlantList2.clear();
	ArenaPlantList3.clear();
}

ArenaInfo::ArenaInfo(const ArenaInfo& i_info)
{
	ArenaPlantList1 = i_info.ArenaPlantList1;
	ArenaPlantList2 = i_info.ArenaPlantList2;
	ArenaPlantList3 = i_info.ArenaPlantList3;
}

void ArenaInfo::RestartArenaInfo()
{
	ArenaPlantList1.clear();
	ArenaPlantList2.clear();
	ArenaPlantList3.clear();
}

ArenaInfo& ArenaInfo::operator=(const ArenaInfo& i_info)
{
	ArenaPlantList1 = i_info.ArenaPlantList1;
	ArenaPlantList2 = i_info.ArenaPlantList2;
	ArenaPlantList3 = i_info.ArenaPlantList3;
	return *this;
}
