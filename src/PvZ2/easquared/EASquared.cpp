// Reconstructed by EvilHack28 on 2026-09-05
#include "EASquared.h"
#include "EASquared_Android.h"
#include "EASquaredPropertySheet.h"
#include "Toggles.h"
#include "PVZDB.h"

EASquared::EASquared()
{
}

EASquared& EASquared::Instance()
{
	if (Toggles::GetInstance().IsEnabled("EASquared"))
		return Sexy::LazySingleton<EASquared_Android>::GetInstance();
	return Sexy::LazySingleton<EASquaredNullImpl>::GetInstance();
}

EASquaredPropertySheet* EASquared::GetProperties()
{
	return PVZDB::GetInstance().FindObjectByAlias<EASquaredPropertySheet>(PVZDB::TABLE_EASQUAREDCONFIG, Sexy::RtName(L"EASquaredConfig"));
}
