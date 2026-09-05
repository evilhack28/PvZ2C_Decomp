// Reconstructed by EvilHack28 on 2026-09-05
#include "PVZVersion.h"
#include "PVZDB.h"
#include "drivers/app/android/JavaInterface.h"

PVZVersion Version::LoadedRSB()
{
	PVZVersion result;
	if (PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_VERSION))
	{
		result = *(PVZVersion*)Sexy::RtWeakPtr<PVZVersion>(*PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_VERSION));
	}
	return result;
}

PVZVersion Version::App()
{
	PVZVersion result;
	result.FromString(Android::Info::SysGetProductVersion());
	return result;
}
