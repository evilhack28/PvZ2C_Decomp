//
//  PlayerList.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "PlayerList.h"
#include "UUIDCreator.h"

/////////////// PlayerList ///////////////

PlayerList::PlayerList(UUIDCreator& i_uuidCreator)
	: m_UUIDCreator(i_uuidCreator)
{
}

PlayerList::~PlayerList()
{
}

std::map<std::string, std::string>& PlayerList::Get()
{
	return idToName;
}

std::string PlayerList::Create(std::string i_name)
{
	std::string id = m_UUIDCreator.Create();
	idToName.insert(std::make_pair(id, i_name));
	return id;
}

void PlayerList::Load(std::string i_pcp_id)
{
}

void PlayerList::LoadViaFacebook()
{
}

void PlayerList::Remove(std::string i_pcp_id)
{
}

void PlayerList::Rename(std::string i_pcp_id, std::string i_name)
{
}

void PlayerList::LogoutFacebook(std::string i_pcp_id)
{
}

bool PlayerList::IsBoundToFacebook(std::string i_pcp_id)
{
	return false;
}
