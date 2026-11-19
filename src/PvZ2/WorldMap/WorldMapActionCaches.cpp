//
//  WorldMapActionCaches.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include <algorithm>

#include "WorldMapActionCaches.h"

/////////////// Lifecycle ///////////////

WorldMapActionCaches::WorldMapActionCaches()
    : m_currentGroup(0)
{
}

WorldMapActionCaches::~WorldMapActionCaches()
{
}

/////////////// Cache ///////////////

void WorldMapActionCaches::Clear()
{
    m_cachedActions.clear();
}

void WorldMapActionCaches::Add(int i_group, const std::string& i_name, int i_popupNumAdd)
{
    if (i_name.empty() || i_popupNumAdd <= 0)
        return;

    std::map<int, std::vector<ActionCached> >::iterator group = m_cachedActions.find(i_group);
    if (group != m_cachedActions.end())
    {
        std::vector<ActionCached>::iterator it = std::find_if(group->second.begin(), group->second.end(), [&](const ActionCached& i_cached) { return i_cached.m_name == i_name; });
        if (it != group->second.end())
        {
            it->m_popupNumAdd += i_popupNumAdd;
            return;
        }
    }

    ActionCached cached;
    cached.m_name = i_name;
    cached.m_popupNumAdd = i_popupNumAdd;
    m_cachedActions[i_group].push_back(cached);
}

WorldMapActionCaches::ActionCached::ActionCached()
    : m_popupNumAdd(1)
{
}

WorldMapActionCaches::ActionCached::ActionCached(const ActionCached& i_other)
    : m_name(i_other.m_name)
    , m_popupNumAdd(i_other.m_popupNumAdd)
{
}

WorldMapActionCaches::ActionCached::ActionCached(ActionCached&& i_other)
    : m_name(static_cast<std::string&&>(i_other.m_name))
    , m_popupNumAdd(i_other.m_popupNumAdd)
{
}

WorldMapActionCaches::ActionCached& WorldMapActionCaches::ActionCached::operator=(ActionCached&& i_other)
{
    m_name = i_other.m_name;
    m_popupNumAdd = i_other.m_popupNumAdd;
    return *this;
}

void WorldMapActionCaches::Start()
{
    if (!m_cachedActions.empty())
        m_currentGroup = m_cachedActions.begin()->first;
}

void WorldMapActionCaches::End()
{
    m_cachedActions.erase(m_currentGroup);
    m_currentGroup = 0;
}
