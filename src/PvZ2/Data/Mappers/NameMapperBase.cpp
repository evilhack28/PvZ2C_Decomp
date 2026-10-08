//
//  NameMapperBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//
/////////////// Lifecycle ///////////////

#include "PvZ/NameMapper.h"
#include "PvZ/logServer/md5.h"
#include <sstream>

NameMapperBase::NameMapperBase()
{
}

NameMapperBase::NameMapperBase(const NameMapperBase& i_other)
    : m_map(i_other.m_map)
    , md5Check(i_other.md5Check)
{
}

NameMapperBase& NameMapperBase::operator=(const NameMapperBase& i_other)
{
    m_map = i_other.m_map;
    md5Check = i_other.md5Check;
    return *this;
}

NameMapperBase::~NameMapperBase()
{
}

/////////////// Accessors ///////////////

const std::map<std::string, int>& NameMapperBase::GetMap()
{
    return m_map;
}

bool NameMapperBase::ContainsId(int i_id)
{
    std::map<std::string, int>::iterator it = m_map.begin();
    while (true)
    {
        bool found = it != m_map.end();
        if (!found || (*it).second == i_id)
            return found;
        ++it;
    }
}

bool NameMapperBase::ContainsName(const std::string& i_name)
{
    return m_map.find(i_name) != m_map.end();
}

/////////////// Lookup ///////////////

int NameMapperBase::GetIdForName(const std::string& i_name)
{
    int id = -1;
    if (IsMapValid())
    {
        if (!(m_map.find(i_name) == m_map.end()))
            id = m_map.at(i_name);
    }
    return id;
}

std::string NameMapperBase::GetNameForId(int i_id)
{
    if (!IsMapValid())
        return "";
    std::map<std::string, int>::iterator it = m_map.begin();
    while (it != m_map.end())
    {
        if ((*it).second == i_id)
            return (*it).first;
        ++it;
    }
    return "";
}

/////////////// Checksum ///////////////

void NameMapperBase::Mondify(const std::string& i_name, int i_id)
{
    m_map[i_name] = i_id;
    CreateMD5Check();
}

void NameMapperBase::CreateMD5Check()
{
    std::stringstream stream(std::ios_base::out | std::ios_base::in);
    stream.str("");
    for (std::map<std::string, int>::iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
        stream << (*it).first;
        stream << (*it).second;
    }
    std::string text = stream.str();
    MD5 md5(text);
    md5Check = md5.toString();
}

bool NameMapperBase::IsMapValid()
{
    bool valid = md5Check.empty();
    if (!valid)
    {
        std::stringstream stream(std::ios_base::out | std::ios_base::in);
        stream.str("");
        for (std::map<std::string, int>::iterator it = m_map.begin(); it != m_map.end(); ++it)
        {
            stream << (*it).first;
            stream << (*it).second;
        }
        std::string text = stream.str();
        MD5 md5(text);
        valid = md5Check == md5.toString();
    }
    return valid;
}
