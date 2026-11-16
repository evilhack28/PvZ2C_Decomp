//
//  TimeUtil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-10.
//

#include "SexyAppFramework/Common.h"

#include "TimeMgr.h"
#include "TimeUtil.h"
#include "LawnApp.h"
#include "ActivityManager.h"
#include "TodLib/TodStringFile.h"
#include "TodLib/TodCommon.h"

/////////////// Time checks ///////////////

bool TimeUtil::CheckTimeEclapse(pvztime_t delta, pvztime_t startTime)
{
	return delta <= PVZ_T() - startTime;
}

bool TimeUtil::CheckTimeDayPass(time_t time, int days)
{
	return days <= (int)(gLawnApp->GetRealServerTime() / 86400) - (int)(time / 86400);
}

bool TimeUtil::CheckTimeHourPass(time_t time, int hours)
{
	return hours <= (int)(gLawnApp->GetRealServerTime() / 3600) - (int)(time / 3600);
}

bool TimeUtil::IsToday(time_t time)
{
	return (int)((gLawnApp->GetRealServerTime() - 57600) / 86400) == (int)((time - 57600) / 86400);
}

bool TimeUtil::IsInThisWeek(time_t time)
{
	return (int)((gLawnApp->GetRealServerTime() - 316800) / 604800) == (int)((time - 316800) / 604800);
}

/////////////// Countdown ///////////////

static bool IsPositive(int i_value)
{
	return i_value > 0;
}

pvztime_t TimeUtil::GetTimeCountdown(int index, int activityId)
{
	pvztime_t countdown;
	if (index == 1)
	{
		time_t now = gLawnApp->GetRealServerTime();
		countdown = (float)((((((int)now + 28800) / 86400) * 86400 + 86400) - 28800) - now);
	}
	else if (index == 2)
	{
		time_t now = gLawnApp->GetRealServerTime();
		countdown = (float)((((((int)now - 316800) / 604800) * 604800 + 604800) + 316800) - now);
	}
	else
	{
		countdown = INT_MAX;
		if (index == 3)
		{
			ActiveItem item = gActivityManager->GetActiveItem(activityId);
			countdown = INT_MAX;
			if (IsPositive(item.m_id) && item.m_bOpen)
				countdown = (float)item.GetLeftTimes();
		}
	}
	return countdown;
}

/////////////// Format ///////////////

static time_t ToLocalTimeStamp(time_t i_time)
{
	return i_time;
}

int TimeUtil::TimeStampToFormatTime(time_t i_time)
{
	time_t t = ToLocalTimeStamp(i_time > 0 ? i_time : Sexy::SexyTime() / 1000);
	struct tm* tm = gLawnApp->BeijingTime(&t);
	return (tm->tm_year + 1900) * 10000 + (tm->tm_mon + 1) * 100 + tm->tm_mday;
}

time_t TimeUtil::FormatTimeToTimeStamp(int i_time)
{
	struct tm tm = {};
	tm.tm_year = i_time / 10000 - 1900;
	tm.tm_mon = (i_time % 10000) / 100 - 1;
	tm.tm_mday = i_time % 100;
	tm.tm_hour = 23;
	tm.tm_min = 59;
	tm.tm_sec = 59;
	return Sexy::GetTimegm(&tm) - Sexy::GetBJTimeOffset();
}

pvztime_t TimeUtil::GetCurrentFormatTime()
{
	return TimeStampToFormatTime(gLawnApp->GetRealBeijingTime());
}

SexyString TimeUtil::GetTimeCountdownFormat(pvztime_t i_time, TimeLayout i_layout)
{
	SexyString result;
	int seconds = (int)i_time;
	if (i_layout == Layout_ddhh_hhmm_mmss)
	{
		if (seconds == INT_MAX)
			result = TodStringTranslate(_S("[UNLIMITED]"));
		else
		{
			if (seconds <= 86400)
			{
				if (seconds <= 3600)
				{
					if (seconds < 0)
					{
						result = TodStringTranslate(_S("[UNKNOWN]"));
						return result;
					}
					SexyString text = TodReplaceNumberString(SexyString(_S("[MIN_SEC]")), _S("{NUM1}"), seconds / 60);
					result = TodReplaceNumberString(text, _S("{NUM2}"), seconds % 60);
				}
				else
				{
					SexyString text = TodReplaceNumberString(SexyString(_S("[HOUR_MIN]")), _S("{NUM1}"), seconds / 3600);
					result = TodReplaceNumberString(text, _S("{NUM2}"), (seconds % 3600) / 60);
				}
			}
			else
			{
				SexyString text = TodReplaceNumberString(SexyString(_S("[DAY_HOUR]")), _S("{NUM1}"), seconds / 86400);
				result = TodReplaceNumberString(text, _S("{NUM2}"), (seconds % 86400) / 3600);
			}
		}
	}
	else if (i_layout == Layout_hhmmsss)
	{
		std::string text = std::to_string(seconds / 3600) + ":" + std::to_string((seconds % 3600) / 60) + ":" + std::to_string(seconds - (seconds / 60) * 60);
		result = Sexy::StringToSexyString(text);
	}
	return result;
}

SexyString TimeUtil::GetTimeCountdownFormat(pvztime_t i_startTime, pvztime_t i_endTime, TimeLayout i_layout)
{
	SexyString result;
	int seconds = (int)(i_endTime - i_startTime);
	if ((float)seconds < 0.0f)
		return L"";
	if (i_layout == Layout_hhmmsss)
	{
		std::string text = std::to_string(seconds / 3600) + ":" + std::to_string((seconds % 3600) / 60) + ":" + std::to_string(seconds - (seconds / 60) * 60);
		result = Sexy::StringToSexyString(text);
	}
	return result;
}
