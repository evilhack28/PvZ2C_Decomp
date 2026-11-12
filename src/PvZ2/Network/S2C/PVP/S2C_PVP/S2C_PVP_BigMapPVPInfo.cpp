//
//  S2C_PVP_BigMapPVPInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "PVP/PVPDatas.h"
#include "LawnApp.h"

/////////////// Accessors ///////////////

int S2C_PVP_BigMapPVPInfo::GetHouseID()
{
	if (zoneId != 1)
		return (zoneId - 2) * 3 + zonePos + 4;
	return zonePos - 1;
}

bool S2C_PVP_BigMapPVPInfo::IsEvilDavid()
{
	return iDavidMaxCompleteCount != 0;
}

/////////////// Logic ///////////////

bool S2C_PVP_BigMapPVPInfo::CheckTime()
{
	if (status == STATUS_ATK_SUC || status == STATUS_EVIL_DAVID)
	{
		int64 now = gLawnApp->GetRealServerTime();
		if (time > 0 && now > 0 && now >= time)
		{
			time = 0;
			return true;
		}
	}
	return false;
}
