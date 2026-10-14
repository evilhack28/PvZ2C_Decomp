//
//  ActivityConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ActivityConfig.h"
#include "LawnApp.h"
#include "Board.h"
#include "PvZ/TodLib/TodStringFile.h"

ActivityConfig::~ActivityConfig()
{
}

/////////////// Accessors ///////////////

std::string ActivityConfig::GetActivityTopic() const
{
	return m_sActivityTopic;
}

std::string ActivityConfig::GetActivityStoreBannerImageS() const
{
	return m_sActivityStoreBannerImage;
}

int ActivityConfig::GetMaxCoinSpecialCollected() const
{
	int base = m_maxCoinSpecialCollected;
	int extra = 0;
	if (gLawnApp->m_board)
		extra = gLawnApp->m_board->GetExtraMaxCoinSpecialCollected();
	return base + extra;
}

/////////////// Activity time ///////////////

bool ActivityConfig::IsActivityDays()
{
	return GetCurrentActivityTimeStatus(ActivityDate.iStartDate, ActivityDate.iEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsActivityCentreDays()
{
	return GetCurrentActivityTimeStatus(ActivityCentreDate.iStartDate, ActivityCentreDate.iEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsAvatarBonusActivated()
{
	return GetCurrentActivityTimeStatus(m_stAvatarBonusActivateData.EventStartDate, m_stAvatarBonusActivateData.EventEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsDailyAchievementActivated()
{
	return GetCurrentActivityTimeStatus(m_strDailyAchievementActivatedData.iStartDate, m_strDailyAchievementActivatedData.iEndDate) == ActivityTimeStatus_Open && m_strDailyAchievementActivatedData.bIsActivated;
}

bool ActivityConfig::IsStoreGiftsActivated()
{
	return GetCurrentActivityTimeStatus(m_strStoreGiftsActivatedData.iStartDate, m_strStoreGiftsActivatedData.iEndDate) == ActivityTimeStatus_Open && m_strStoreGiftsActivatedData.bIsActivated;
}

bool ActivityConfig::IsStorePlantGiftsActivated()
{
	return GetCurrentActivityTimeStatus(m_strStorePlantGiftsActivatedData.iStartDate, m_strStorePlantGiftsActivatedData.iEndDate) == ActivityTimeStatus_Open && m_strStorePlantGiftsActivatedData.bIsActivated;
}

bool ActivityConfig::IsRedPacksEntryActivated()
{
	return GetCurrentActivityTimeStatus(m_strRedPackClosedData.iStartDate, m_strRedPackClosedData.iEndDate) == ActivityTimeStatus_Open && m_strRedPackClosedData.bIsActivated;
}

bool ActivityConfig::IsRedPackActivated()
{
	return IsCurrentActivityLocalTimeValid(m_strRedPackActivatedData.iStartDate, m_strRedPackActivatedData.iEndDate) && m_strRedPackActivatedData.bIsActivated;
}

bool ActivityConfig::IsLanternRiddlesActivated()
{
	return IsCurrentActivityLocalTimeValid(m_strLanternRiddlesActivatedData.iStartDate, m_strLanternRiddlesActivatedData.iEndDate) && m_strLanternRiddlesActivatedData.bIsActivated;
}

bool ActivityConfig::IsSpringBossActivated()
{
	return m_stSpringBossActivatedData.iMaxTimesPerDay > 0 && GetCurrentActivityTimeStatus(m_stSpringBossActivatedData.iEventStartDate, m_stSpringBossActivatedData.iEventEndDate) == ActivityTimeStatus_Open;
}

int ActivityConfig::GetChristmasAccessoryPrice(int i_type)
{
	switch (i_type)
	{
	case 2:
		return m_stChristmasAccessoryData.coinsPrice;
	case 3:
		return m_stChristmasAccessoryData.gemsPrice;
	default:
		return 0;
	}
}

std::vector<int> ActivityConfig::GetGoldenEggList()
{
	return m_stGoldenEggData.vecGoldenEggBonus;
}

int ActivityConfig::GetChristmasAccessoryMaxChances(int i_type)
{
	switch (i_type)
	{
	case 1:
		return m_stChristmasAccessoryData.freeMaxTime;
	case 2:
		return m_stChristmasAccessoryData.coinMaxTime;
	case 3:
		return m_stChristmasAccessoryData.gemMaxTime;
	default:
		return 0;
	}
}

bool ActivityConfig::HasLanternRiddlesStarted()
{
	if (!m_strLanternRiddlesActivatedData.bIsActivated)
		return false;
	return HasCurrentActivityLocalTimeStarted(m_strLanternRiddlesActivatedData.iStartDate) && !HasCurrentActivityLocalTimeStarted(m_strLanternRiddlesActivatedData.iEntryCloseDate);
}

bool ActivityConfig::HasRedPackStarted()
{
	if (!m_strRedPackActivatedData.bIsActivated)
		return false;
	return HasCurrentActivityLocalTimeStarted(m_strRedPackActivatedData.iStartDate) && !HasCurrentActivityLocalTimeStarted(m_strRedPackActivatedData.iEntryCloseDate);
}

bool ActivityConfig::IsBossFightActivatedAtTime(const tm i_time)
{
	int date = (i_time.tm_year + 1900) * 10000 + (i_time.tm_mon + 1) * 100 + i_time.tm_mday;
	return date >= m_stBossFightActivateData.EventStartDate && date <= m_stBossFightActivateData.EventEndDate;
}

bool ActivityConfig::IsSpringGiftActivatedAtTime(const tm i_time)
{
	int date = (i_time.tm_year + 1900) * 10000 + (i_time.tm_mon + 1) * 100 + i_time.tm_mday;
	return date >= m_stSpringGiftActivatedData.iEventStartDate && date <= m_stSpringGiftActivatedData.iEventEndDate;
}

bool ActivityConfig::IsDangerRoomActivated(bool i_checkReward)
{
	if (i_checkReward)
		return GetCurrentActivityTimeStatus(m_strDangerRoomActivatedData.iRewardStartDate, m_strDangerRoomActivatedData.iRewardEndDate) == ActivityTimeStatus_Open;
	return GetCurrentActivityTimeStatus(m_strDangerRoomActivatedData.iEventStartDate, m_strDangerRoomActivatedData.iEventEndDate) == ActivityTimeStatus_Open && m_strDangerRoomActivatedData.bIsActivated;
}

int ActivityConfig::GetWeeklyGameModeCount(FestivalGameMode eType) const
{
	FestivalGameMode mode = eType != FestivalGameMode_WealthGod ? eType : FestivalGameMode_CrazyYeti;
	for (size_t i = 0; i != WeeklyGameModesCountList.size(); i++)
	{
		if (WeeklyGameModesCountList[i].eModeType == mode)
			return WeeklyGameModesCountList[i].iCount;
	}
	return 0;
}

bool ActivityConfig::IsGeneralSaleFirstAward(std::string& Sku)
{
	for (size_t i = 0; i != GeneralSaleObjectList.size(); i++)
	{
		if (GeneralSaleObjectList[i].sSku == Sku)
			return GeneralSaleObjectList[i].bFirstAward;
	}
	return false;
}

BossLevel ActivityConfig::GetBossLevelInfoByIndex(int i_index)
{
	if ((size_t)i_index < m_stBossFightActivateData.BossLevels.size())
		return m_stBossFightActivateData.BossLevels[i_index];
	return m_stBossFightActivateData.BossLevels[0];
}

bool ActivityConfig::IsGeneralSale(std::string& Sku)
{
	for (size_t i = 0; i != GeneralSaleObjectList.size(); i++)
	{
		if (GeneralSaleObjectList[i].sSku == Sku)
			return true;
	}
	return false;
}

int ActivityConfig::GetBossFightBonusPieceCount(int i_index)
{
	int pieceMin;
	int pieceMax;
	if ((size_t)i_index < m_stBossFightActivateData.BossLevels.size())
	{
		pieceMin = m_stBossFightActivateData.BonusAccessories[i_index].pieceMin;
		pieceMax = m_stBossFightActivateData.BonusAccessories[i_index].pieceMax;
	}
	else
	{
		pieceMin = m_stBossFightActivateData.BonusAccessories[0].pieceMin;
		pieceMax = m_stBossFightActivateData.BonusAccessories[0].pieceMax;
	}
	ProbabilitySet<int> pieces;
	for (int count = pieceMin; count <= pieceMax; count++)
		pieces.AddItem(count, 1);
	return pieces.PickItem();
}

ActivityTimeStatus ActivityConfig::GetCurrentActivityTimeStatus(int iStartDate, int iEndDate)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime <= 0)
		return ActivityTimeStatus_NotOpen;
	struct tm* now = gLawnApp->BeijingTime(&realTime);
	int today = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
	if (today < iStartDate)
		return ActivityTimeStatus_NotOpen;
	return today > iEndDate ? ActivityTimeStatus_Close : ActivityTimeStatus_Open;
}

bool ActivityConfig::HasCurrentActivityTimeStarted(int iStartDate)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime <= 0)
		return false;
	struct tm* now = gLawnApp->BeijingTime(&realTime);
	int today = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
	return today >= iStartDate;
}

bool ActivityConfig::HasCurrentActivityLocalTimeStarted(int iStartDate)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime <= 0)
		return false;
	struct tm* now = gLawnApp->BeijingTime(&realTime);
	std::string today = Sexy::StrFormat("%04d%02d%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	return atoi(today.c_str()) >= iStartDate;
}

bool ActivityConfig::IsCurrentActivityLocalTimeValid(int iStartDate, int iEndDate)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime <= 0)
		return false;
	struct tm* now = gLawnApp->BeijingTime(&realTime);
	std::string today = Sexy::StrFormat("%04d%02d%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	int date = atoi(today.c_str());
	return date >= iStartDate && date <= iEndDate;
}

bool ActivityConfig::IsDayFirstRewardActDays()
{
	bool result = false;
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		if (now != nullptr)
		{
			std::string today = Sexy::StrFormat("%04d%02d%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
			int date = atoi(today.c_str());
			if (date >= m_stDayFirstPayRewardData.iStartDate)
				if (date <= m_stDayFirstPayRewardData.iEndDate)
					result = true;
		}
	}
	return result;
}

time_t ActivityConfig::DateMKTime(int i_Date)
{
	struct tm date = {};
	date.tm_year = i_Date / 10000 - 1900;
	date.tm_mon = i_Date % 10000 / 100 - 1;
	date.tm_mday = i_Date % 100;
	date.tm_hour = 23;
	date.tm_min = 59;
	date.tm_sec = 59;
	return Sexy::GetTimegm(&date) - Sexy::GetBJTimeOffset();
}

void ActivityConfig::UTF8ChStringToUnicodeChString(std::string& UTF8ChString, std::wstring& UnicodeChString)
{
	int consumed = 1;
	const char* stream = UTF8ChString.c_str() + 1;
	while (UTF8ChString.size() > (size_t)consumed)
	{
		wchar_t ch;
		consumed += Sexy::GetNextUTF8CharFromStream(&stream, UTF8ChString.size() - consumed, &ch);
		UnicodeChString.push_back(ch);
	}
}

bool ActivityConfig::GetScrollBarBarTextContent(int nIndex, std::wstring& sScrollBarTextContent)
{
	if (nIndex < 0 || (size_t)nIndex > m_strScrollBarBark.BarkTextContent.size() - 1)
		return false;
	UTF8ChStringToUnicodeChString(m_strScrollBarBark.BarkTextContent[nIndex], sScrollBarTextContent);
	return true;
}

bool ActivityConfig::GetTipsTextContent(int nIndex, std::wstring& sTipsTextContent)
{
	if (nIndex < 0 || (size_t)nIndex > m_strTips.TipsContent.size() - 1)
		return false;
	UTF8ChStringToUnicodeChString(m_strTips.TipsContent[nIndex], sTipsTextContent);
	return true;
}

std::string ActivityConfig::GetBossFightBonusSkuID(int i_index)
{
	if ((size_t)i_index < m_stBossFightActivateData.BossLevels.size())
		return m_stBossFightActivateData.BonusAccessories[i_index].bonus;
	return m_stBossFightActivateData.BonusAccessories[0].bonus;
}

int ActivityConfig::GetBossFightBonusCount()
{
	return m_stBossFightActivateData.BonusAccessories.size();
}

/////////////// Data accessors ///////////////

const ScrollBarBarkData & ActivityConfig::GetScrollBarBarData()
{
	return m_strScrollBarBark;
}

const TipsData & ActivityConfig::GetTipsData()
{
	return m_strTips;
}

const MysteryCrystalDrop& ActivityConfig::GetMysteryCrystalDropData()
{
	return m_mysteryCrystalDropData;
}

const SpecialGameLevelRefreshData & ActivityConfig::GetRefreshPlantsPurchaseData()
{
	return m_strRefreshData;
}

const std::string & ActivityConfig::GetRechargePlantPieceTextContent()
{
	return m_strActivityRechargePlantPieceData.sTextContent;
}

const std::string & ActivityConfig::GetRechargePiecePlantName()
{
	return m_strActivityRechargePlantPieceData.sPlantName;
}

const std::vector<PieceDropData>& ActivityConfig::GetPieceDropDataList()
{
	return PieceDropDataList;
}

const SpringBossActivatedData& ActivityConfig::GetSpringBossActivatedData()
{
	return m_stSpringBossActivatedData;
}

const SpringGiftActivatedData& ActivityConfig::GetSpringGiftActivatedData()
{
	return m_stSpringGiftActivatedData;
}

const ChristmasAccessoryData& ActivityConfig::GetChristmasAccessoryData()
{
	return m_stChristmasAccessoryData;
}

const GoldenEggData& ActivityConfig::GetGoldenEggData()
{
	return m_stGoldenEggData;
}

const ChristmasProtectData& ActivityConfig::GetChristmasProtectData()
{
	return m_stChristmasProtectData;
}

const ChristmasLotteryData& ActivityConfig::GetChristmasLotteryData()
{
	return m_stChristmasLotteryData;
}

std::vector<BossLevel>& ActivityConfig::GetAllBossLevelInfo()
{
	return m_stBossFightActivateData.BossLevels;
}

int ActivityConfig::GetGoldenEggRewardRequstRMB()
{
	return m_stGoldenEggData.rewardRequstRMB;
}

int ActivityConfig::GetGoldenEggRewardHammerQuantity()
{
	return m_stGoldenEggData.rewardHammerQuantity;
}

int ActivityConfig::GetGoldenEggDailyHammerMax()
{
	return m_stGoldenEggData.dailyHammerMax;
}

int ActivityConfig::GetGoldenEggHammerStorageMax()
{
	return m_stGoldenEggData.HammerStorageMax;
}

int ActivityConfig::GetGoldenEggEggOpenGemCost()
{
	return m_stGoldenEggData.eggOpenGemCost;
}

bool ActivityConfig::IsBossFightActivated()
{
	return GetCurrentActivityTimeStatus(m_stBossFightActivateData.EventStartDate, m_stBossFightActivateData.EventEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsChristmasAccessoryActived()
{
	return GetCurrentActivityTimeStatus(m_stChristmasAccessoryData.eventStartDate, m_stChristmasAccessoryData.eventEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsGoldenEggActived()
{
	return GetCurrentActivityTimeStatus(m_stGoldenEggData.eventStartDate, m_stGoldenEggData.eventEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsPlantBonusActivated()
{
	return GetCurrentActivityTimeStatus(m_stPlantBonusActivateData.EventStartDate, m_stPlantBonusActivateData.EventEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsSpringGiftActivated()
{
	return GetCurrentActivityTimeStatus(m_stSpringGiftActivatedData.iEventStartDate, m_stSpringGiftActivatedData.iEventEndDate) == ActivityTimeStatus_Open;
}

bool ActivityConfig::IsTwoYearActivated()
{
	return GetCurrentActivityTimeStatus(m_stTwoYearData.iStartDate, m_stTwoYearData.iEndDate) == ActivityTimeStatus_Open;
}

int ActivityConfig::GetBossFightConfigLevelsCount()
{
	return m_stBossFightActivateData.BossLevels.size();
}

bool ActivityConfig::IsFirstRechargeAward()
{
	return m_bFirstRechargeAward && IsActivityDays();
}

bool ActivityConfig::IsRechargePlantPieceValid()
{
	return m_strActivityRechargePlantPieceData.bValid && IsActivityDays();
}

void ActivityConfig::GetNoticeContent(std::wstring& sNoticeContent)
{
	UTF8ChStringToUnicodeChString(m_strNoticeContent.sNoticeTextContent, sNoticeContent);
}

bool ActivityConfig::IsAnyConsumptionTopicValid()
{
	return !GetConsumptionValidTopic().empty();
}

std::string ActivityConfig::GetConsumptionValidTopic()
{
	std::string topic;
	topic.clear();
	if (gLawnApp->GetRealBeijingTime() > 0 && m_stConsumptionActivedData.bIsActivated)
	{
		std::vector<ConsumptionActivedItem>::iterator it = std::find_if(m_stConsumptionActivedData.vActItem.begin(), m_stConsumptionActivedData.vActItem.end(), [this](const ConsumptionActivedItem& i_item) { return IsCurrentActivityLocalTimeValid(i_item.iStartDate, i_item.iEndDate); });
		if (!(it == m_stConsumptionActivedData.vActItem.end()))
			topic = it->strTopic;
	}
	return topic;
}

bool ActivityConfig::IsPlantOnSale(std::string& plantName)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		int year = now->tm_year + 1900;
		int yearBase = year * 10000;
		for (size_t i = 0; i != DiscountPlantList.size(); i++)
		{
			const DiscountPlant& plant = DiscountPlantList[i];
			if (!plant.IsAvatar && plant.PlantName == plantName)
			{
				int date = plant.DiscountDate;
				if (date / 10000 == year && now->tm_mon + 1 == (date - yearBase) / 100 && now->tm_mday == date % 100)
					return true;
			}
		}
	}
	return false;
}

bool ActivityConfig::IsAvatarOnSale(std::string& plantAvatarName)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		int year = now->tm_year + 1900;
		for (size_t i = 0; i != DiscountPlantList.size(); i++)
		{
			const DiscountPlant& plant = DiscountPlantList[i];
			if (plant.IsAvatar && plant.PlantName == plantAvatarName)
			{
				int date = plant.DiscountDate;
				if (date / 10000 == year && now->tm_mon + 1 == (date - year * 10000) / 100 && now->tm_mday == date % 100)
					return true;
			}
		}
	}
	return false;
}

std::string ActivityConfig::GetGeneralSale(std::string& Sku)
{
	for (size_t i = 0; i != GeneralSaleObjectList.size(); i++)
	{
		if (GeneralSaleObjectList[i].sSku == Sku)
			return GeneralSaleObjectList[i].sImage;
	}
	return std::string("");
}

std::string ActivityConfig::GetPlantImageOnSale(std::string& plantName)
{
	for (size_t i = 0; i != DiscountPlantList.size(); i++)
	{
		if (!DiscountPlantList[i].IsAvatar && DiscountPlantList[i].PlantName == plantName)
			return DiscountPlantList[i].DiscountImage;
	}
	return std::string("");
}

std::string ActivityConfig::GetAvatarImageOnSale(std::string& plantAvatarName)
{
	for (size_t i = 0; i != DiscountPlantList.size(); i++)
	{
		if (DiscountPlantList[i].IsAvatar && DiscountPlantList[i].PlantName == plantAvatarName)
			return DiscountPlantList[i].DiscountImage;
	}
	return std::string("");
}

int ActivityConfig::GetActivityPrice(std::string& productName, bool bAvatar, int iPrice)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		int year = now->tm_year + 1900;
		int yearBase = year * 10000;
		for (size_t i = 0; i != DiscountPlantList.size(); i++)
		{
			const DiscountPlant& plant = DiscountPlantList[i];
			if (plant.IsAvatar == bAvatar && plant.PlantName == productName)
			{
				int date = plant.DiscountDate;
				if (date / 10000 == year && now->tm_mon + 1 == (date - yearBase) / 100 && now->tm_mday == date % 100)
					return (int)((float)(iPrice * plant.Discount) * 0.01f);
			}
		}
	}
	return iPrice;
}

Sexy::Color::PredefinedColor ActivityConfig::GetActivityTextColor(std::string sColor) const
{
	std::string color = Sexy::StringToLower(sColor);
	if (color == "")
		return Sexy::Color::White;
	if (color == "black")
		return Sexy::Color::Black;
	if (color == "white")
		return Sexy::Color::White;
	if (color == "red")
		return Sexy::Color::Red;
	if (color == "orange")
		return Sexy::Color::Orange;
	if (color == "yellow")
		return Sexy::Color::Yellow;
	if (color == "green")
		return Sexy::Color::Green;
	if (color == "blue")
		return Sexy::Color::Blue;
	if (color == "purple")
		return Sexy::Color::Purple;
	if (color == "cyan")
		return Sexy::Color::Cyan;
	return Sexy::Color::White;
}

bool ActivityConfig::IsGeneralSaleOnDay(std::string& Sku)
{
	for (size_t i = 0; i < GeneralSaleObjectList.size(); i++)
	{
		if (GeneralSaleObjectList[i].sSku == Sku)
		{
			if (GeneralSaleObjectList[i].iDate == 0)
				return true;
			time_t realTime = gLawnApp->GetRealBeijingTime();
			if (realTime <= 0)
				return false;
			struct tm* now = gLawnApp->BeijingTime(&realTime);
			int date = GeneralSaleObjectList[i].iDate;
			if (date / 10000 == now->tm_year + 1900 && now->tm_mon + 1 == (date % 10000) / 100 && now->tm_mday == date % 100)
				return true;
		}
	}
	return false;
}

float ActivityConfig::GetGeneralSaleDiscountOnDay(std::string& Sku)
{
	for (size_t i = 0; i < GeneralSaleObjectList.size(); i++)
	{
		if (GeneralSaleObjectList[i].sSku == Sku)
		{
			time_t realTime = gLawnApp->GetRealBeijingTime();
			if (realTime <= 0)
				return 1.0f;
			struct tm* now = gLawnApp->BeijingTime(&realTime);
			int date = GeneralSaleObjectList[i].iDate;
			if (date / 10000 == now->tm_year + 1900 && now->tm_mon + 1 == (date % 10000) / 100 && now->tm_mday == date % 100)
			{
				if (GeneralSaleObjectList[i].fDiscount != 0.0f)
					return GeneralSaleObjectList[i].fDiscount;
				return 1.0f;
			}
		}
	}
	return 1.0f;
}

void ActivityConfig::GetTodayDiscountPlant(DiscountPlant& i_discountPlant)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		int year = now->tm_year + 1900;
		int month = now->tm_mon;
		for (size_t i = 0; i != DiscountPlantList.size(); i++)
		{
			const DiscountPlant& plant = DiscountPlantList[i];
			int date = plant.DiscountDate;
			if (date / 10000 == year && (date - year * 10000) / 100 == month + 1 && date % 100 == now->tm_mday)
			{
				i_discountPlant = plant;
				break;
			}
		}
	}
}

bool ActivityConfig::IsTargetTimeInDangerRoomPeriod(time_t i_targetTime)
{
	time_t now = gLawnApp->GetRealServerTime();
	bool result = false;
	if (now > 0)
	{
		int startDate = m_strDangerRoomActivatedData.iEventStartDate;
		struct tm startTime = {};
		startTime.tm_year = startDate / 10000 - 1900;
		startTime.tm_mon = startDate % 10000 / 100 - 1;
		startTime.tm_mday = startDate % 100;
		time_t startStamp = Sexy::GetTimegm(&startTime) - Sexy::GetBJTimeOffset();
		if (now >= startStamp)
		{
			time_t day = (now - startStamp) / (24 * 60 * 60) + 1;
			time_t weeks = day % 7 == 0 ? day / 7 : day / 7 + 1;
			time_t targetDay = (i_targetTime - startStamp) / (24 * 60 * 60) + 1;
			time_t targetWeeks = targetDay % 7 == 0 ? targetDay / 7 : targetDay / 7 + 1;
			result = weeks == targetWeeks;
		}
	}
	return result;
}

ChristmasAccessoryBonus ActivityConfig::GetChristmasAccessoryIdByIndex(int i_type, int i_index)
{
	switch (i_type)
	{
	case 2:
		for (std::vector<ChristmasAccessoryBonus>::iterator it = m_stChristmasAccessoryData.vecCoinIds.begin(); it != m_stChristmasAccessoryData.vecCoinIds.end(); ++it)
		{
			if (it->index == i_index)
				return *it;
		}
		break;
	case 3:
		for (std::vector<ChristmasAccessoryBonus>::iterator it = m_stChristmasAccessoryData.vecGemIds.begin(); it != m_stChristmasAccessoryData.vecGemIds.end(); ++it)
		{
			if (it->index == i_index)
				return *it;
		}
		break;
	case 1:
		for (std::vector<ChristmasAccessoryBonus>::iterator it = m_stChristmasAccessoryData.vecFreeIds.begin(); it != m_stChristmasAccessoryData.vecFreeIds.end(); ++it)
		{
			if (it->index == i_index)
				return *it;
		}
		break;
	}
	ChristmasAccessoryBonus bonus;
	return bonus;
}

bool ActivityConfig::GetStorePlantGiftImageBySku(const std::string& sSku, std::string& sImage)
{
	if (PlantGiftDataList.empty())
		return false;
	for (size_t i = 0; i != PlantGiftDataList.size(); i++)
	{
		if (sSku == PlantGiftDataList[i].sSku)
		{
			sImage = PlantGiftDataList[i].sImage;
			return true;
		}
	}
	return false;
}

int ActivityConfig::GetStorePlantGiftLevelActidByPlantName(const std::string& sPlantName)
{
	if (PlantGiftDataList.empty())
		return 0;
	for (size_t i = 0; i != PlantGiftDataList.size(); i++)
	{
		if (sPlantName == PlantGiftDataList[i].sPlantName)
			return PlantGiftDataList[i].actid;
	}
	return 0;
}

bool ActivityConfig::CheckCurrentLevelIsActivityLevel(const std::string& sLevelName) const
{
	for (int i = 0; i != WorldMapActivityPieceLevelList.size(); i++)
	{
		if (WorldMapActivityPieceLevelList[i].sLevelName == sLevelName)
			return WorldMapActivityPieceLevelList[i].bValid;
	}
	return false;
}

FestivalGameMode ActivityConfig::GetCurrentPlantPieceComeFrom(const std::string& sPlantPiece, bool IsAvatar)
{
	FestivalGameMode mode = _GetCurrentPlantPieceComeFrom(sPlantPiece, IsAvatar);
	if (__builtin_expect(mode != FestivalGameMode_CrazyYeti, 1))
		return mode;
	return IsSpringBossActivated() ? FestivalGameMode_WealthGod : FestivalGameMode_CrazyYeti;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ActivityConfig);

bool ActivityConfig::IsActivityNoticeOnce()
{
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	bool once;
	if (profile == nullptr)
	{
		once = false;
	}
	else
	{
		once = profile->GetShowNoticeOnce();
		profile->CloseShowNoticeOnce();
	}
	return once;
}

Image* ActivityConfig::GetRechargeImage()
{
	if (IsRechargePlantPieceValid())
	{
		Sexy::ResourceInfoTypes::ImageRes* info = gLawnApp->GetUIImageInfoFromStringId(m_strActivityRechargePlantPieceData.sImage);
		if (info != nullptr)
		{
			return info->GetImage();
		}
	}
	return nullptr;
}

Image* ActivityConfig::GetTipsImage()
{
	if (!m_strTips.TipsImage.empty())
	{
		if (IsActivityDays())
		{
			int index = 0;
			if ((int)m_strTips.TipsImage.size() > 1)
			{
				index = Sexy::Rand((int)m_strTips.TipsImage.size());
			}
			Sexy::ResourceInfoTypes::ImageRes* info = gLawnApp->GetUIImageInfoFromStringId(m_strTips.TipsImage[index]);
			if (info != nullptr)
			{
				return info->GetImage();
			}
		}
	}
	return nullptr;
}

bool ActivityConfig::IsCurrentWorldMapActivityLevelValid(const std::string& sLevelName)
{
	for (int i = 0; i != WorldMapActivityPieceLevelList.size(); i++)
	{
		if (WorldMapActivityPieceLevelList[i].sLevelName == sLevelName)
		{
			if (IsActivityDays() && WorldMapActivityPieceLevelList[i].bValid)
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool ActivityConfig::HaveGameModeToday(FestivalGameMode i_mode)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		int weekday = now->tm_wday;
		if ((size_t)weekday < WeeklyGameModes.size())
		{
			std::vector<FestivalGameMode>& modes = WeeklyGameModes[weekday];
			for (int i = 0; i != modes.size(); i++)
			{
				if (modes[i] == i_mode)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool ActivityConfig::IsWeeklyGameModesPlantArrayAvatar(FestivalGameMode eModeType, bool& IsAvatar)
{
	if (SpecialGameLevelGroupList.empty())
		return false;
	FestivalGameMode mode = eModeType != FestivalGameMode_WealthGod ? eModeType : FestivalGameMode_CrazyYeti;
	for (size_t i = 0; i != SpecialGameLevelGroupList.size(); i++)
	{
		if (SpecialGameLevelGroupList[i].eGameMode == mode)
		{
			IsAvatar = SpecialGameLevelGroupList[i].bIsAvatar;
			return true;
		}
	}
	return false;
}

int ActivityConfig::GetGetWeeklyGameModesPlantCount(FestivalGameMode eModeType, FestivalGameLevel eModeLevel) const
{
	if (!SpecialGameLevelGroupList.empty())
	{
		Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
		FestivalGameMode mode = eModeType != FestivalGameMode_WealthGod ? eModeType : FestivalGameMode_CrazyYeti;
		for (size_t i = 0; i != SpecialGameLevelGroupList.size(); i++)
		{
			if (SpecialGameLevelGroupList[i].eGameMode == mode)
			{
				const std::vector<PlantNameArray>& plants = SpecialGameLevelGroupList[i].plantNameArray;
				for (size_t j = 0; j != plants.size(); j++)
				{
					if (plants[j].eModeLevel == eModeLevel)
						return plants[j].iPlantCount;
				}
			}
		}
	}
	return 0;
}

float ActivityConfig::GetStorePlantGiftLevelDiscountBySku(const std::string& sSku, int iLevel) const
{
	if (!PlantGiftDataList.empty())
	{
		for (size_t i = 0; i != PlantGiftDataList.size(); i++)
		{
			if (sSku == PlantGiftDataList[i].sSku)
			{
				const std::vector<LevelGem>& gems = PlantGiftDataList[i].ExpensesData;
				for (size_t j = 0; j != gems.size(); j++)
				{
					if (gems[j].iLevel == iLevel)
						return gems[j].fDiscount;
				}
			}
		}
	}
	return 0.0f;
}

float ActivityConfig::GetStorePlantGiftLevelDiscountByPlantName(const std::string& sPlantName, int iLevel) const
{
	if (!PlantGiftDataList.empty())
	{
		for (size_t i = 0; i != PlantGiftDataList.size(); i++)
		{
			if (sPlantName == PlantGiftDataList[i].sPlantName)
			{
				const std::vector<LevelGem>& gems = PlantGiftDataList[i].ExpensesData;
				for (size_t j = 0; j != gems.size(); j++)
				{
					if (gems[j].iLevel == iLevel)
						return gems[j].fDiscount;
				}
			}
		}
	}
	return 0.0f;
}

bool ActivityConfig::GetStorePlantGiftLevelDiscountImageSBySku(const std::string& sSku, int iLevel, std::string& sImageId)
{
	if (!PlantGiftDataList.empty())
	{
		for (size_t i = 0; i != PlantGiftDataList.size(); i++)
		{
			if (sSku == PlantGiftDataList[i].sSku)
			{
				const std::vector<LevelGem>& gems = PlantGiftDataList[i].ExpensesData;
				for (size_t j = 0; j != gems.size(); j++)
				{
					if (gems[j].iLevel == iLevel)
					{
						sImageId = gems[j].sDiscoutImage;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool ActivityConfig::GetStorePlantGiftLevelDiscountImageSByPlantName(const std::string& sPlantName, int iLevel, std::string& sImageId)
{
	if (!PlantGiftDataList.empty())
	{
		for (size_t i = 0; i != PlantGiftDataList.size(); i++)
		{
			if (sPlantName == PlantGiftDataList[i].sPlantName)
			{
				const std::vector<LevelGem>& gems = PlantGiftDataList[i].ExpensesData;
				for (size_t j = 0; j != gems.size(); j++)
				{
					if (gems[j].iLevel == iLevel)
					{
						sImageId = gems[j].sDiscoutImage;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool ActivityConfig::IsCurrStorePlantGiftActivated(const std::string sku)
{
	for (std::vector<PlantGiftData>::iterator it = PlantGiftDataList.begin(); it != PlantGiftDataList.end(); ++it)
	{
		if (it->sSku == sku)
		{
			if (GetCurrentActivityTimeStatus(m_strStorePlantGiftsActivatedDataList[it->TimeIndex].iStartDate, m_strStorePlantGiftsActivatedDataList[it->TimeIndex].iEndDate) == ActivityTimeStatus_Open)
				return m_strStorePlantGiftsActivatedDataList[it->TimeIndex].bIsActivated;
			return false;
		}
	}
	return false;
}

int ActivityConfig::GetLeftActivityDays()
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime <= 0)
		return 0;
	int endDate = ActivityDate.iEndDate;
	struct tm endTime = {};
	endTime.tm_year = endDate / 10000 - 1900;
	endTime.tm_mon = endDate % 10000 / 100 - 1;
	endTime.tm_mday = endDate % 100;
	time_t endStamp = Sexy::GetTimegm(&endTime) - Sexy::GetBJTimeOffset();
	return (endStamp - realTime) / (24 * 60 * 60) + 1;
}

int ActivityConfig::GetLeftDangerRoomDays(bool i_reward)
{
	int result = 0;
	if (i_reward)
	{
		time_t now = gLawnApp->GetRealBeijingTime();
		if (now > 0)
		{
			int startDate = m_strDangerRoomActivatedData.iEventStartDate;
			struct tm startTime = {};
			startTime.tm_year = startDate / 10000 - 1900;
			startTime.tm_mon = startDate % 10000 / 100 - 1;
			startTime.tm_mday = startDate % 100;
			time_t startStamp = Sexy::GetTimegm(&startTime) - Sexy::GetBJTimeOffset();
			int endDate = m_strDangerRoomActivatedData.iRewardEndDate;
			struct tm endTime = {};
			endTime.tm_year = endDate / 10000 - 1900;
			endTime.tm_mon = endDate % 10000 / 100 - 1;
			endTime.tm_mday = endDate % 100;
			time_t endStamp = Sexy::GetTimegm(&endTime) - Sexy::GetBJTimeOffset();
			if (now <= endStamp && now >= startStamp)
			{
				int day = (now - startStamp) / (24 * 60 * 60) + 1;
				int weeks = day / 7 + (day % 7 != 0 ? 1 : 0);
				int left = weeks * 7 - day + 1;
				if (day >= 0)
					result = left;
			}
		}
	}
	else
	{
		time_t now = gLawnApp->GetRealServerTime();
		if (now > 0)
		{
			gLawnApp->BeijingTime(&now);
			int endDate = m_strDangerRoomActivatedData.iEventEndDate;
			struct tm endTime = {};
			endTime.tm_year = endDate / 10000 - 1900;
			endTime.tm_mon = endDate % 10000 / 100 - 1;
			endTime.tm_mday = endDate % 100;
			int endStamp = (int)Sexy::GetTimegm(&endTime) - (int)Sexy::GetBJTimeOffset();
			result = (endStamp - (int)now) / (24 * 60 * 60) + 1;
		}
	}
	return result;
}

int ActivityConfig::GetRemainTime(FestivalGameMode i_mode)
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		int remain = now->tm_hour * -3600 + now->tm_min * -60 - now->tm_sec;
		size_t count = WeeklyGameModes.size();
		for (size_t day = now->tm_wday; day < count * 2; day++)
		{
			std::vector<FestivalGameMode>& modes = WeeklyGameModes[(int)(day % count)];
			for (int i = 0; i != modes.size(); i++)
			{
				if (modes[i] == i_mode)
					return remain;
			}
			remain += 24 * 60 * 60;
		}
	}
	return 99 * 24 * 60 * 60;
}

std::vector<float> ActivityConfig::GetCurrentPieceDropPercentArray(const std::string & sPieceName, FestivalGameLevel eLevel) const
{
	std::vector<float> percents;
	percents.clear();
	if (!PieceDropDataList.empty())
	{
		size_t count = PieceDropDataList.size();
		for (int i = 0; i != count;)
		{
			const PieceDropData& data = PieceDropDataList[i++];
			if (sPieceName == data.sPieceName)
			{
				switch (eLevel)
				{
				case FestivalGameLevel_Hard:
					return data.PercentHardArray;
				case FestivalGameLevel_Medium:
					return data.PercentNormalArray;
				case FestivalGameLevel_Legend:
					return data.PercentLegendArray;
				default:
					return data.PercentNormalArray;
				}
			}
		}
	}
	return percents;
}

int ActivityConfig::GetCurrentPieceDropActivityCombat(const std::string & sPieceName) const
{
	size_t i = 0;
	if (!PieceDropDataList.empty())
	{
		size_t count = PieceDropDataList.size();
		while (i < count)
		{
			if (sPieceName == PieceDropDataList[i].sPieceName)
			{
				if (PieceDropDataList[i].iStartDate == 0 || PieceDropDataList[i].iEndDate == 0)
					break;
				time_t realTime = gLawnApp->GetRealBeijingTime();
				if (realTime <= 0)
					break;
				struct tm* now = gLawnApp->BeijingTime(&realTime);
				int date = (now->tm_year + 1900) * 10000 + now->tm_mon * 100 + 100 + now->tm_mday;
				const PieceDropData& data = PieceDropDataList[i];
				if (date >= data.iStartDate && date <= data.iEndDate)
				{
					int days = date - data.iStartDate;
					int hours = days * 24 + now->tm_hour;
					if (hours >= data.iStartTime / 100 + days * 24 && hours <= data.iEndTime / 100 + days * 24)
					{
						int minutes = days * 24 * 60 + now->tm_min;
						if (minutes >= data.iStartTime % 100 + days * 24 * 60 && minutes <= data.iEndTime % 100 + days * 24 * 60)
							return data.iActicityCombat;
					}
				}
				count = PieceDropDataList.size();
			}
			i++;
		}
	}
	return 1;
}

float ActivityConfig::GetCurrentPlantListDrowWeight(FestivalGameMode eModeType, FestivalGameLevel eModeLevel, EArrayType eArrayType) const
{
	if (!SpecialGameLevelGroupList.empty())
	{
		FestivalGameMode mode;
		if (eModeType != FestivalGameMode_WealthGod)
			mode = eModeType;
		else
			mode = FestivalGameMode_CrazyYeti;
		Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
		for (int i = 0; i != SpecialGameLevelGroupList.size(); i++)
		{
			const std::vector<PlantNameArray>& plants = SpecialGameLevelGroupList[i].plantNameArray;
			for (size_t j = 0; j != plants.size(); j++)
			{
				if (plants[j].eModeLevel == eModeLevel && SpecialGameLevelGroupList[i].eGameMode == mode)
				{
					switch (eArrayType)
					{
					case eArrayType_Few:
						return (float)plants[j].iFewWeight * 0.01f;
					case eArrayType_Normal:
						return (float)plants[j].iNormalWeight * 0.01f;
					case eArrayType_Rare:
						return (float)plants[j].iRareWeight * 0.01f;
					default:
						break;
					}
				}
			}
		}
	}
	return 1.0f;
}

int ActivityConfig::GetScrollBarBarkContentIndex()
{
	int index;
	switch (m_strScrollBarBark.strBarkProperty.eType)
	{
	case eBarkType_RandOneContent:
	{
		index = 0;
		int last = (int)m_strScrollBarBark.BarkTextContent.size() - 1;
		if (last > index)
			index = RandRangeInt(index, last);
		goto done;
	}
	case eBarkType_ListContent:
	{
		time_t realTime = gLawnApp->GetRealBeijingTime();
		if (realTime > 0)
		{
			struct tm* now = gLawnApp->BeijingTime(&realTime);
			int date = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
			size_t day = 0;
			index = 0;
			if (date >= ActivityDate.iStartDate && date <= ActivityDate.iEndDate)
			{
				index = date - ActivityDate.iStartDate + 1;
				day = index;
			}
			index = day < m_strScrollBarBark.BarkTextContent.size() ? index : 0;
			goto done;
		}
		break;
	}
	case eBarkType_Loop:
	{
		time_t realTime = gLawnApp->GetRealBeijingTime();
		if (realTime > 0)
		{
			struct tm* now = gLawnApp->BeijingTime(&realTime);
			int date = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
			index = 0;
			if (date >= ActivityDate.iStartDate && date <= ActivityDate.iEndDate)
				index = date - ActivityDate.iStartDate;
			size_t wide = index;
			size_t count = m_strScrollBarBark.BarkTextContent.size();
			if (wide >= count - 1)
				index = wide % count;
			if (__builtin_expect(!!(index >= 0 && count >= (size_t)index), 0))
				goto done;
		}
		break;
	}
	}
	index = 0;
done:
	return index;
}

GoldenEggProbility ActivityConfig::RollGoldenEggPieceCount()
{
	ProbabilitySet<int> eggs;
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	std::vector<GoldenEggProbility>::iterator it = m_stGoldenEggData.vecProbilityList.begin();
	std::vector<GoldenEggProbility>::iterator end = m_stGoldenEggData.vecProbilityList.end();
	int picked;
	if (profile != nullptr)
	{
		for (int i = 1; it != end; ++it, i++)
		{
			int weight = it->probility;
			if (!profile->IsOpenedIndex(i - 1))
				eggs.AddItem(i - 1, weight);
		}
		picked = eggs.PickItem();
		if (!m_stGoldenEggData.vecProbilityList[picked].refresh)
			profile->AddToGoldenEggOpenedInfo(picked);
		else
			profile->ResetGoldenEggOpenedInfo();
	}
	else
	{
		int i = 0;
		for (; it != end; ++it)
		{
			eggs.AddItem(i, it->probility);
			i++;
		}
		picked = eggs.PickItem();
	}
	return m_stGoldenEggData.vecProbilityList[picked];
}

int ActivityConfig::RollChristmasAccessoryIndex(int i_type)
{
	ProbabilitySet<int> accessories;
	switch (i_type)
	{
	case 2:
		{
			std::vector<ChristmasAccessoryBonus>& ids = m_stChristmasAccessoryData.vecCoinIds;
			std::vector<ChristmasAccessoryBonus>::iterator it = ids.begin();
			std::vector<ChristmasAccessoryBonus>::iterator end = ids.end();
			for (; it != end; ++it)
				accessories.AddItem((*it).index, (*it).probility);
		}
		break;
	case 3:
		{
			std::vector<ChristmasAccessoryBonus>& ids = m_stChristmasAccessoryData.vecGemIds;
			std::vector<ChristmasAccessoryBonus>::iterator it = ids.begin();
			std::vector<ChristmasAccessoryBonus>::iterator end = ids.end();
			for (; it != end; ++it)
				accessories.AddItem((*it).index, (*it).probility);
		}
		break;
	case 1:
		{
			std::vector<ChristmasAccessoryBonus>& ids = m_stChristmasAccessoryData.vecFreeIds;
			std::vector<ChristmasAccessoryBonus>::iterator it = ids.begin();
			std::vector<ChristmasAccessoryBonus>::iterator end = ids.end();
			for (; it != end; ++it)
				accessories.AddItem((*it).index, (*it).probility);
		}
		break;
	}
	return accessories.PickItem();
}

FestivalGameMode ActivityConfig::_GetCurrentPlantPieceComeFrom(const std::string & sPlantPiece, bool IsAvatar) const
{
	for (int i = 0; i < SpecialGameLevelGroupList.size(); i++)
	{
		for (size_t j = 0; j < SpecialGameLevelGroupList[i].plantNameArray.size(); j++)
		{
			if (!SpecialGameLevelGroupList[i].plantNameArray[j].ArrayRare.empty())
			{
				const std::vector<std::string>& names = SpecialGameLevelGroupList[i].plantNameArray[j].ArrayRare;
				for (size_t k = 0; k != names.size(); k++)
				{
					if (names[k] == sPlantPiece && SpecialGameLevelGroupList[i].bIsAvatar == IsAvatar)
						return SpecialGameLevelGroupList[i].eGameMode;
				}
			}
			if (!SpecialGameLevelGroupList[i].plantNameArray[j].ArrayFew.empty())
			{
				const std::vector<std::string>& names = SpecialGameLevelGroupList[i].plantNameArray[j].ArrayFew;
				for (size_t k = 0; k != names.size(); k++)
				{
					if (names[k] == sPlantPiece && SpecialGameLevelGroupList[i].bIsAvatar == IsAvatar)
						return SpecialGameLevelGroupList[i].eGameMode;
				}
			}
			if (__builtin_expect(!!(!SpecialGameLevelGroupList[i].plantNameArray[j].ArrayNormal.empty()), 1))
			{
				const std::vector<std::string>& names = SpecialGameLevelGroupList[i].plantNameArray[j].ArrayNormal;
				for (size_t k = 0; k != names.size(); k++)
				{
					if (names[k] == sPlantPiece && SpecialGameLevelGroupList[i].bIsAvatar == IsAvatar)
						return SpecialGameLevelGroupList[i].eGameMode;
				}
			}
		}
	}
	return FestivalGameMode_None;
}

bool ActivityConfig::GetGetWeeklyGameModesPlantArray(FestivalGameMode eModeType, FestivalGameLevel eModeLevel, EArrayType eArrayType, std::vector<std::string>& Array)
{
	if (!SpecialGameLevelGroupList.empty())
	{
		FestivalGameMode mode = eModeType != FestivalGameMode_WealthGod ? eModeType : FestivalGameMode_CrazyYeti;
		Array.clear();
		PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
		for (size_t i = 0; i != SpecialGameLevelGroupList.size(); i++)
		{
			if (SpecialGameLevelGroupList[i].eGameMode == mode)
			{
				const std::vector<PlantNameArray>& plants = SpecialGameLevelGroupList[i].plantNameArray;
				for (size_t j = 0; j != plants.size(); j++)
				{
					if (plants[j].eModeLevel != eModeLevel)
						continue;
					switch (eArrayType)
					{
					case eArrayType_Few:
						if (plants[j].ArrayFew.size() != 0)
						{
							Array.reserve(plants[j].ArrayFew.size());
							for (size_t k = 0; k < SpecialGameLevelGroupList[i].plantNameArray[j].ArrayFew.size(); k++)
							{
								std::string plantName = SpecialGameLevelGroupList[i].plantNameArray[j].ArrayFew[k];
								RtWeakPtr<const PlantType> plantType = Sexy::LazySingleton<ObjectTypeDirectory<PlantType> >::GetInstancePtr()->GetTypeFromTypeName(plantName);
								int maxLevel = plantType->GetProps()->MaxLevel;
								int minLevel = plantType->GetProps()->MinLevel;
								if (profile->GetIsPlantUnlocked(plantName))
								{
									if (maxLevel == minLevel)
									{
										if (!SpecialGameLevelGroupList[i].bIsAvatar)
											continue;
									}
								}
								Array.push_back(plantName);
							}
							return true;
						}
						break;
					case eArrayType_Normal:
						if (plants[j].ArrayNormal.size() != 0)
						{
							Array.reserve(plants[j].ArrayNormal.size());
							for (size_t k = 0; k < SpecialGameLevelGroupList[i].plantNameArray[j].ArrayNormal.size(); k++)
							{
								std::string plantName = SpecialGameLevelGroupList[i].plantNameArray[j].ArrayNormal[k];
								RtWeakPtr<const PlantType> plantType = Sexy::LazySingleton<ObjectTypeDirectory<PlantType> >::GetInstancePtr()->GetTypeFromTypeName(plantName);
								int maxLevel = plantType->GetProps()->MaxLevel;
								int minLevel = plantType->GetProps()->MinLevel;
								if (profile->GetIsPlantUnlocked(plantName))
								{
									if (maxLevel == minLevel)
									{
										if (!SpecialGameLevelGroupList[i].bIsAvatar)
											continue;
									}
								}
								Array.push_back(plantName);
							}
							return true;
						}
						break;
					case eArrayType_Rare:
						if (plants[j].ArrayRare.size() != 0)
						{
							Array.reserve(plants[j].ArrayRare.size());
							for (size_t k = 0; k < SpecialGameLevelGroupList[i].plantNameArray[j].ArrayRare.size(); k++)
							{
								std::string plantName = SpecialGameLevelGroupList[i].plantNameArray[j].ArrayRare[k];
								RtWeakPtr<const PlantType> plantType = Sexy::LazySingleton<ObjectTypeDirectory<PlantType> >::GetInstancePtr()->GetTypeFromTypeName(plantName);
								int maxLevel = plantType->GetProps()->MaxLevel;
								int minLevel = plantType->GetProps()->MinLevel;
								if (profile->GetIsPlantUnlocked(plantName))
								{
									if (maxLevel == minLevel)
									{
										if (!SpecialGameLevelGroupList[i].bIsAvatar)
											continue;
									}
								}
								Array.push_back(plantName);
							}
							return true;
						}
						break;
					}
				}
			}
		}
	}
	return false;
}

void ActivityConfig::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(FestivalGameMode);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(yeti, FestivalGameMode_CrazyYeti);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(gargantuar, FestivalGameMode_GargantuarCrisis);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(devil, FestivalGameMode_DevilInvade);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(wealth, FestivalGameMode_WealthGod);
	REFLECTION_ENUMBUILDER_END(FestivalGameMode);

	REFLECTION_ENUMBUILDER_BEGIN(FestivalGameLevel);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(Normal, FestivalGameLevel_Medium);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(Hard, FestivalGameLevel_Hard);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(Legend, FestivalGameLevel_Legend);
	REFLECTION_ENUMBUILDER_END(FestivalGameLevel);

	REFLECTION_CLASSBUILDER_BEGIN(ActivityDateData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
	REFLECTION_CLASSBUILDER_END(ActivityDateData);

	REFLECTION_CLASSBUILDER_BEGIN(NoticeContentData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sTitleBackGroundImage, TitleBackGroundImage);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sTitleTextContent, TitleTextContent);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sNoticeTextContent, NoticeTextContent);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(NoticeContentData);

	REFLECTION_ENUMBUILDER_BEGIN(EBarkType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(Rand, eBarkType_RandOneContent);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(List, eBarkType_ListContent);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(Loop, eBarkType_Loop);
	REFLECTION_ENUMBUILDER_END(EBarkType);

	REFLECTION_CLASSBUILDER_BEGIN(BarkPropertyData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sColorType, ColorType);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iDisplayCount, DisplayCount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, fScollSpeed, ScollSpeed);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, fDelayTime, DelayTime);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(EBarkType, eType, Type);
	REFLECTION_CLASSBUILDER_END(BarkPropertyData);

	REFLECTION_CLASSBUILDER_BEGIN(ScrollBarBarkData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(BarkPropertyData, strBarkProperty, BarkProperty);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, BarkTextContent);
	REFLECTION_CLASSBUILDER_END(ScrollBarBarkData);

	REFLECTION_CLASSBUILDER_BEGIN(TipsPropertyData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iBaseIndex, BaseIndex);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sColorType, ColorType);
	REFLECTION_CLASSBUILDER_END(TipsPropertyData);

	REFLECTION_CLASSBUILDER_BEGIN(TipsData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(TipsPropertyData, strTipsProperty, TipsProperty);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, TipsContent);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, TipsImage);
	REFLECTION_CLASSBUILDER_END(TipsData);

	REFLECTION_CLASSBUILDER_BEGIN(DailyAchievementActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(DailyAchievementActivatedData);

	REFLECTION_CLASSBUILDER_BEGIN(StoreGiftsActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(StoreGiftsActivatedData);

	REFLECTION_CLASSBUILDER_BEGIN(GachaRewardItem);
		REFLECTION_CLASSBUILDER_FIELD(int, objectId);
		REFLECTION_CLASSBUILDER_FIELD(int, Count);
		REFLECTION_CLASSBUILDER_FIELD(int, Probability);
	REFLECTION_CLASSBUILDER_END(GachaRewardItem);

	REFLECTION_CLASSBUILDER_BEGIN(DangerRoomActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEventStartDate, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEventEndDate, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iRewardStartDate, RewardStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iRewardEndDate, RewardEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(DangerRoomActivatedData);

	REFLECTION_CLASSBUILDER_BEGIN(SpringBossActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEventStartDate, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEventEndDate, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iMaxTimesPerDay, MaxTimesPerDay);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iRate, Rate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<RtWeakPtr<const ZombieType> >, veczombiesType, ZombieType);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<std::string>, veclevelName, ActivityLevel);
	REFLECTION_CLASSBUILDER_END(SpringBossActivatedData);

	REFLECTION_CLASSBUILDER_BEGIN(SSpringRewardInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME_UNSAFE(RtWeakPtr<const PlantType>, plantType, planttype);
		REFLECTION_CLASSBUILDER_FIELD(int, gem);
	REFLECTION_CLASSBUILDER_END(SSpringRewardInfo);

	REFLECTION_CLASSBUILDER_BEGIN(SpringGiftActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEventStartDate, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEventEndDate, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iAndroidCost, AndCost);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iIosCost, IosCost);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<SSpringRewardInfo>, vecrewards, Rewards);
	REFLECTION_CLASSBUILDER_END(SpringGiftActivatedData);

	REFLECTION_CLASSBUILDER_BEGIN(ChristmasAccessoryBonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, index, Index);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, objectId, ObjectId);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, quantity, Quantity);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, probility, Probility);
	REFLECTION_CLASSBUILDER_END(ChristmasAccessoryBonus);

	REFLECTION_CLASSBUILDER_BEGIN(ChristmasAccessoryData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventStartDate, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventEndDate, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, coinsPrice, CoinsPrice);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, gemsPrice, GemsPrice);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, freeMaxTime, FreeMaxTime);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, coinMaxTime, CoinMaxTime);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, gemMaxTime, GemMaxTime);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ChristmasAccessoryBonus>, vecFreeIds, FreeList);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ChristmasAccessoryBonus>, vecCoinIds, CoinList);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ChristmasAccessoryBonus>, vecGemIds, GemList);
	REFLECTION_CLASSBUILDER_END(ChristmasAccessoryData);

	REFLECTION_CLASSBUILDER_BEGIN(GoldenEggProbility);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, quantity, Quantity);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, probility, Probility);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, refresh, Refresh);
	REFLECTION_CLASSBUILDER_END(GoldenEggProbility);

	REFLECTION_CLASSBUILDER_BEGIN(GoldenEggData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventStartDate, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventEndDate, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, rewardRequstRMB, RewardRequstRMB);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, rewardHammerQuantity, RewardHammerQuantity);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, dailyHammerMax, DailyHammerMax);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, HammerStorageMax, HammerMax);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eggOpenGemCost, EggOpenGemCost);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, vecGoldenEggBonus, GoldenEggBonusList);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<GoldenEggProbility>, vecProbilityList, ProbilityList);
	REFLECTION_CLASSBUILDER_END(GoldenEggData);

	REFLECTION_CLASSBUILDER_BEGIN(ChristmasProtectData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventStartDate, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventEndDate, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, maxPlayCount, MaxPlayCount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<GachaRewardItem>, christmasTreeRewardList, ChristmasTreeRewardList);
	REFLECTION_CLASSBUILDER_END(ChristmasProtectData);

	REFLECTION_CLASSBUILDER_BEGIN(ChristmasLotteryData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventStartDate, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, eventEndDate, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, christmasLotteryCost, ChristmasLotteryCost);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, christmasLotterySpecialChance, ChristmasLotterySpecialChance);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, christmasLotterySpecialChanceCommon, ChristmasLotterySpecialChanceCommon);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<GachaRewardItem>, christmasGachaRewardList, ChristmasGachaRewardList);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<GachaRewardItem>, christmasGachaRewardSpecial, ChristmasGachaRewardSpecial);
	REFLECTION_CLASSBUILDER_END(ChristmasLotteryData);

	REFLECTION_CLASSBUILDER_BEGIN(BossLevel);
		REFLECTION_CLASSBUILDER_FIELD(std::string, WorldName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, LevelName);
	REFLECTION_CLASSBUILDER_END(BossLevel);

	REFLECTION_CLASSBUILDER_BEGIN(BossFightBonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, bonus, Bonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, pieceMin, Min);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, pieceMax, Max);
	REFLECTION_CLASSBUILDER_END(BossFightBonus);

	REFLECTION_CLASSBUILDER_BEGIN(BossFightActivateData);
		REFLECTION_CLASSBUILDER_FIELD(int, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD(int, EventEndDate);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BossLevel>, BossLevels);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BossFightBonus>, BonusAccessories);
	REFLECTION_CLASSBUILDER_END(BossFightActivateData);

	REFLECTION_CLASSBUILDER_BEGIN(CommonActivateData);
		REFLECTION_CLASSBUILDER_FIELD(int, EventStartDate);
		REFLECTION_CLASSBUILDER_FIELD(int, EventEndDate);
	REFLECTION_CLASSBUILDER_END(CommonActivateData);

	REFLECTION_CLASSBUILDER_BEGIN(DiscountPlant);
		REFLECTION_CLASSBUILDER_FIELD(int, DiscountDate);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantName);
		REFLECTION_CLASSBUILDER_FIELD(bool, IsAvatar);
		REFLECTION_CLASSBUILDER_FIELD(int, Discount);
		REFLECTION_CLASSBUILDER_FIELD(std::string, DiscountImage);
	REFLECTION_CLASSBUILDER_END(DiscountPlant);

	REFLECTION_CLASSBUILDER_BEGIN(GeneralSaleProp);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bFirstAward, FirstAward);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iDate, Date);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, fDiscount, Discount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sSku, Sku);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sImage, Image);
	REFLECTION_CLASSBUILDER_END(GeneralSaleProp);

	REFLECTION_CLASSBUILDER_BEGIN(PlantNameArray);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(FestivalGameLevel, eModeLevel, GameLevel);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iPlantCount, PlantCount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iNormalWeight, NormalWeight);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iFewWeight, FewWeight);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iRareWeight, RareWeight);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ArrayNormal);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ArrayFew);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ArrayRare);
	REFLECTION_CLASSBUILDER_END(PlantNameArray);

	REFLECTION_CLASSBUILDER_BEGIN(SpecialGameLevelRefreshData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(PurchaseType, eType, PurchaseType);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iPrice, Price);
	REFLECTION_CLASSBUILDER_END(SpecialGameLevelRefreshData);

	REFLECTION_CLASSBUILDER_BEGIN(SpecialGameLevelGroup);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(FestivalGameMode, eGameMode, SpecialGameLevelType);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsAvatar, IsAvatar);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<PlantNameArray>, plantNameArray, PlantNameArray);
	REFLECTION_CLASSBUILDER_END(SpecialGameLevelGroup);

	REFLECTION_CLASSBUILDER_BEGIN(WeeklyGameModesCount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(FestivalGameMode, eModeType, ModeType);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iCount, Count);
	REFLECTION_CLASSBUILDER_END(WeeklyGameModesCount);

	REFLECTION_CLASSBUILDER_BEGIN(PieceDropData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sPieceName, PieceName);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, PercentNormalArray);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, PercentHardArray);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, PercentLegendArray);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iActicityCombat, ActicityCombat);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartTime, StartTime);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndTime, EndTime);
	REFLECTION_CLASSBUILDER_END(PieceDropData);

	REFLECTION_CLASSBUILDER_BEGIN(LanternRiddlesActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEntryCloseDate, EntryCloseDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(LanternRiddlesActivatedData);

	REFLECTION_CLASSBUILDER_BEGIN(RedPackActivedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEntryCloseDate, EntryCloseDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(RedPackActivedData);

	REFLECTION_CLASSBUILDER_BEGIN(RedPackClosedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(RedPackClosedData);

	REFLECTION_CLASSBUILDER_BEGIN(StorePlantGiftsActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
	REFLECTION_CLASSBUILDER_END(StorePlantGiftsActivatedData);

	REFLECTION_CLASSBUILDER_BEGIN(LevelGem);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iLevel, Level);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, fDiscount, Discount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sDiscoutImage, DiscountImage);
	REFLECTION_CLASSBUILDER_END(LevelGem);

	REFLECTION_CLASSBUILDER_BEGIN(PlantGiftData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sSku, Sku);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sPlantName, PlantName);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sImage, Image);
		REFLECTION_CLASSBUILDER_FIELD(int, actid);
		REFLECTION_CLASSBUILDER_FIELD(int, TimeIndex);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<LevelGem>, ExpensesData);
	REFLECTION_CLASSBUILDER_END(PlantGiftData);

	REFLECTION_CLASSBUILDER_BEGIN(ActivityRechargePlantPieceData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bValid, Valid);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sTextContent, TextContent);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sImage, Image);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sPlantName, PlantName);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iPieceCount, PieceCount);
	REFLECTION_CLASSBUILDER_END(ActivityRechargePlantPieceData);

	REFLECTION_CLASSBUILDER_BEGIN(WorldMapActivityPieceLevelData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bValid, Valid);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, sLevelName, LevelName);
	REFLECTION_CLASSBUILDER_END(WorldMapActivityPieceLevelData);

	REFLECTION_CLASSBUILDER_BEGIN(ConsumptionActivedItem);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iStartDate, StartDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iEndDate, EndDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, strTopic, Topic);
	REFLECTION_CLASSBUILDER_END(ConsumptionActivedItem);

	REFLECTION_CLASSBUILDER_BEGIN(ConsumptionActivedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, bIsActivated, IsActivated);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ConsumptionActivedItem>, vActItem, ActItem);
	REFLECTION_CLASSBUILDER_END(ConsumptionActivedData);

	REFLECTION_CLASSBUILDER_BEGIN(MysteryCrystalDrop);
		REFLECTION_CLASSBUILDER_FIELD(int, NormalDropAmount);
		REFLECTION_CLASSBUILDER_FIELD(int, HardDropAmount);
	REFLECTION_CLASSBUILDER_END(MysteryCrystalDrop);

	REFLECTION_CLASSBUILDER_BEGIN(ActivityConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(ActivityDateData, ActivityDate);
		REFLECTION_CLASSBUILDER_FIELD(ActivityDateData, ActivityCentreDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(NoticeContentData, m_strNoticeContent, NoticeContent);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ActivityDateData, m_stDayFirstPayRewardData, DayFirstPayRewardData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(MysteryCrystalDrop, m_mysteryCrystalDropData, MysteryCrystalDropData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ActivityDateData, m_stTwoYearData, TwoYearData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ScrollBarBarkData, m_strScrollBarBark, ScrollBarBark);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(TipsData, m_strTips, Tips);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(DailyAchievementActivatedData, m_strDailyAchievementActivatedData, DailyAchievementActivatedDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(StoreGiftsActivatedData, m_strStoreGiftsActivatedData, StoreGiftsActivatedDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(StorePlantGiftsActivatedData, m_strStorePlantGiftsActivatedData, StorePlantGiftsActivatedDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(LanternRiddlesActivatedData, m_strLanternRiddlesActivatedData, LanternRiddlesActivatedDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(RedPackActivedData, m_strRedPackActivatedData, RedPackActivedDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(RedPackClosedData, m_strRedPackClosedData, RedPackClosedDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(DangerRoomActivatedData, m_strDangerRoomActivatedData, DangerRoomActivatedDate);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(SpringBossActivatedData, m_stSpringBossActivatedData, SpringBossActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(SpringGiftActivatedData, m_stSpringGiftActivatedData, SpringGiftActivatedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ChristmasAccessoryData, m_stChristmasAccessoryData, ChristmasAccessoryData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(GoldenEggData, m_stGoldenEggData, GoldenEggData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ChristmasProtectData, m_stChristmasProtectData, ChristmasProtectData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ChristmasLotteryData, m_stChristmasLotteryData, ChristmasLotteryData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(BossFightActivateData, m_stBossFightActivateData, BossFightActivateData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(CommonActivateData, m_stPlantBonusActivateData, PlantBonusActivateData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(CommonActivateData, m_stAvatarBonusActivateData, AvatarBonusActivateData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ActivityRechargePlantPieceData, m_strActivityRechargePlantPieceData, ActivityRechargePlantPiece);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(ConsumptionActivedData, m_stConsumptionActivedData, ConsumptionActivedData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_bFirstRechargeAward, FirstRechargeAward);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_iFirstRechargeAwardMultiple, FirstRechargeAwardMultiple);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sActivityStoreBannerImage, ActivityStoreBannerImage);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_bDoubleCoin, DoubleCoin);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_bAutoSunCollect, AutoSunCollect);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(SpecialGameLevelRefreshData, m_strRefreshData, SpecialGameLevelRefresh);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sActivityTopic, ActivityTopic);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_maxCoinSpecialCollected, MaxCoinSpecialCollected);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_cukePackageAddCount, CukePackageAddCount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector< std::vector<FestivalGameMode> >, WeeklyGameModes);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<GeneralSaleProp>, GeneralSaleObjectList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DiscountPlant>, DiscountPlantList);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<SpecialGameLevelGroup>, SpecialGameLevelGroupList, SpecialGameLevelGroup);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<WeeklyGameModesCount>, WeeklyGameModesCountList, WeeklyGameModesCount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PieceDropData>, PieceDropDataList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantGiftData>, PlantGiftDataList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<WorldMapActivityPieceLevelData>, WorldMapActivityPieceLevelList);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<StorePlantGiftsActivatedData>, m_strStorePlantGiftsActivatedDataList, StorePlantGiftsActivatedDateList);
	REFLECTION_CLASSBUILDER_END(ActivityConfig);

}

SexyString ActivityConfig::GetTodayDiscountPlantName()
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	if (realTime > 0)
	{
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		int year = now->tm_year + 1900;
		int month = now->tm_mon;
		int yearBase = year * 10000;
		for (size_t i = 0; i != DiscountPlantList.size(); i++)
		{
			int date = DiscountPlantList[i].DiscountDate;
			if (date / 10000 == year && (date - yearBase) / 100 == month + 1 && date % 100 == now->tm_mday)
			{
				std::string categoryName = DiscountPlantList[i].IsAvatar ? "Avatars" : "Plants";
				std::string storeName = "iOS PvZ2 Store";
				MagentoCategoryPropsPtr category = Magento::GetStoreCategory(storeName, categoryName);
				if (category)
				{
					for (size_t j = 0; j < category->Products.size(); j++)
					{
						if (category->Products[j]->ObjectItem == DiscountPlantList[i].PlantName)
							return TodStringTranslate(Sexy::UTF8StringToWString(category->Products[j]->GetLocalizedShortDescription()));
					}
				}
				break;
			}
		}
	}
	return SexyString(L"");
}
