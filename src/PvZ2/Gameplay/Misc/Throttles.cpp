//
//  Throttles.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include <sstream>

#include "Throttles.h"
#include "UserPrefsWrapper.h"
#include "WorldMapUtils.h"

/////////////// Lifecycle ///////////////

Throttles::~Throttles()
{
}

Throttles::Throttles(UserPrefsWrapper& userPrefsWrapper)
    : m_userPrefsWrapper(userPrefsWrapper), m_minVersion(""), m_reloadPropertySheets(false), m_giftingEnabled(true),
      m_seasonalCostumeEnabled(""), m_dataServiceDebugText(false)
{
    m_disabledWorlds.insert("prehistoric");
    m_disabledWorlds.insert("coming_soon");
}

/////////////// Accessors ///////////////

std::string Throttles::GetMinVersion()
{
    return m_minVersion;
}

void Throttles::SetMinVersion(std::string minVersion)
{
    m_minVersion = minVersion;
}

void Throttles::SetDeltaIntervalInMS(int interval)
{
    std::stringstream stream(std::ios_base::out | std::ios_base::in);
    stream << interval;
    m_userPrefsWrapper.SetString("DeltaIntervalMS", stream.str());
}

Throttles& Throttles::GetInstance()
{
    static Throttles instance(UserPrefsWrapper::GetInstance());
    return instance;
}

/////////////// Logic ///////////////

void Throttles::SetWorldDisabled(const std::string& i_worldName, bool i_disabled)
{
    if (i_disabled)
        m_disabledWorlds.insert(i_worldName);
    else
        m_disabledWorlds.erase(i_worldName);
    WorldMapUtils::LoadWorldMapData();
}

bool Throttles::WorldIsDisabled(const std::string& i_worldName)
{
    return m_disabledWorlds.find(i_worldName) != m_disabledWorlds.end();
}

pvztime_t Throttles::GetDeltaIntervalInS()
{
    pvztime_t interval = DEFAULT_DELTA_INTERVAL_S;
    std::string value = m_userPrefsWrapper.GetString("DeltaIntervalMS", "");
    if (!value.empty())
        interval = atof(value.c_str()) * 0.001;
    return interval;
}
