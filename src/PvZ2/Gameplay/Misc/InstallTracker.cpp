//
//  InstallTracker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include <sstream>

#include "InstallTracker.h"
#include "TimeMgr.h"
#include "UserPrefsWrapper.h"

/////////////// InstallTracker ///////////////

int InstallTracker::GetDaysSinceInstall()
{
	int daysSinceInstall = 0;

	std::string installDate = UserPrefsWrapper::GetInstance().GetString("UdIdCheck", "");
	if (!installDate.empty())
	{
		int installDateValue = 0;
		if (Sexy::StringToInt(installDate, &installDateValue))
		{
			int today = gTimeMgr->GetDate();
			daysSinceInstall = (today - installDateValue) / 86400 + 1;
		}
	}

	return daysSinceInstall;
}

void InstallTracker::SetInstallDate()
{
	UserPrefsWrapper& userPrefs = UserPrefsWrapper::GetInstance();

	std::string installDate = userPrefs.GetString("UdIdCheck", "");
	if (installDate.empty())
	{
		std::stringstream dateStream;
		dateStream << gTimeMgr->GetDate();
		userPrefs.SetString("UdIdCheck", dateStream.str());
	}
}
