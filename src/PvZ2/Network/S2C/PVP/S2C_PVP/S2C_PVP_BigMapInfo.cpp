//
//  S2C_PVP_BigMapInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "PVP/PVPDatas.h"

/////////////// Accessors ///////////////

int S2C_PVP_BigMapInfo::GetHouseID()
{
	if (zoneId != 1)
		return (zoneId - 2) * 3 + zonePos + 4;
	return zonePos - 1;
}
