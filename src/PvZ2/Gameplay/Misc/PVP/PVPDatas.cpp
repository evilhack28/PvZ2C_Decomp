#include <ctime>
#include <string>
#include <utility>

typedef long long int64;
typedef int int32;

class LawnApp
{
public:
    time_t GetRealServerTime();
};
extern LawnApp *gLawnApp;

struct DefenderInfo
{
    DefenderInfo()
    {
        m_name = L"";
        m_profileId = 0;
        m_winCup = 0;
        m_lostCup = 0;
        m_winCurrency = 0;
    }

    std::wstring m_name;
    int32 m_profileId;
    int32 m_winCup;
    int32 m_lostCup;
    int32 m_winCurrency;
};

struct S2C_PVP_DefenderInfo
{
    S2C_PVP_DefenderInfo()
    {
        m_name = L"";
        m_profileId = -1;
        m_winCup = 0;
        m_lostCup = 0;
        m_winCurrency = 0;
    }

    std::wstring m_name;
    int32 m_profileId;
    int32 m_winCup;
    int32 m_lostCup;
    int32 m_winCurrency;
};

class S2C_PVP_BigMapInfo
{
public:
    int GetHouseID();

public:
    int64 occupyId = 0;
    int64 profileId = 0;
    std::wstring occupyname;
    int level = 0;
    int cupNum = 0;
    int cupMaxNum = 0;
    int goldNum = 0;
    int goldMaxNum = 0;
    int cupproducespeed = 0;
    int goldProduceSpeed = 0;
    int zoneId = 0;
    int zonePos = 0;
    int attackPrice = 0;
};

class S2C_PVP_BigMapPVPInfo
{
public:
    enum
    {
        STATUS_NONE = 0,
        STATUS_NORMAL = 1,
        STATUS_ATK_SUC = 2,
        STATUS_ATK_FAIL = 3,
        STATUS_EVIL_DAVID = 4,
    };

public:
    int GetHouseID();
    bool IsEvilDavid();
    bool CheckTime();

public:
    int64 occupyId = 0;
    std::wstring occupyname;
    int level = 0;
    int cupNum = 0;
    int cupGain = 0;
    int goldGain = 0;
    int zoneId = 0;
    int zonePos = 0;
    int status = 0;
    int time = 0;
    int iDavidCompleteCount = -1;
    int iDavidMaxCompleteCount = -1;
    int iAttackWinMedal = 0;
    int attackPrice = 0;
};

class PvPRankMonthReward
{
public:
    int32 oldCup = 0;
    int32 newCup = 0;
    int32 rewardCoin = 0;

    int32 rankOrder = -1;
    int32 rewardMedal = 0;
};

struct PVPCurrencyData
{
    int m_PVPCoin = 0;
    int m_PVPMedal = 0;
    int m_PVPCup = 0;
};

int S2C_PVP_BigMapPVPInfo::GetHouseID()
{
    if (zoneId == 1)
        return zonePos - 1;
    return (zoneId - 2) * 3 + zonePos + 4;
}

bool S2C_PVP_BigMapPVPInfo::IsEvilDavid()
{
    return iDavidMaxCompleteCount != 0;
}

bool S2C_PVP_BigMapPVPInfo::CheckTime()
{
    if (status == STATUS_ATK_SUC || status == STATUS_EVIL_DAVID)
    {
        time_t now = gLawnApp->GetRealServerTime();
        int t = time;
        if (now > 0 && t > 0 && now >= t)
        {
            time = 0;
            return true;
        }
    }
    return false;
}

int S2C_PVP_BigMapInfo::GetHouseID()
{
    if (zoneId == 1)
        return zonePos - 1;
    return (zoneId - 2) * 3 + zonePos + 4;
}

template <typename T>
static void emit()
{
    static T instance;
    static T copied(instance);
    static T moved(std::move(copied));
    instance = moved;
    instance = std::move(moved);
}

void _pvpdatas_emit()
{
    emit<DefenderInfo>();
    emit<S2C_PVP_DefenderInfo>();
    emit<S2C_PVP_BigMapInfo>();
    emit<S2C_PVP_BigMapPVPInfo>();
    emit<PvPRankMonthReward>();
    emit<PVPCurrencyData>();
}
