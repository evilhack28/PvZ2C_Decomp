//
//  MonthlyCardMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-06.
//

#include "SexyAppFramework/Common.h"

#include "MonthlyCardMgr.h"
#include "PlayerInfo.h"
#include "ProfileUtils.h"
#include "UserInfo.h"
#include "gameNetWork/PacketID.h"
#include "DNode/DNodeWidget.h"
#include "GameEventMgr.h"
#include "ActivityManager.h"

/////////////// Colors ///////////////

static ColorDataVector s_monthlyColors[C_Count];

/////////////// MonthlyCardMgr ///////////////

MonthlyCardMgr::MonthlyCardMgr()
	: m_currentColor(C_Brown)
{
	gMessageRouter->Subscribe(&Message::OnLuaNotify, Sexy::MakeDelegate(*this, &MonthlyCardMgr::OnLuaNotify));
}

MonthlyCardMgr::~MonthlyCardMgr()
{
	gMessageRouter->Unsubscribe(this);
}

const ColorDataVector& MonthlyCardMgr::GetColor(MonthlyColor i_color)
{
	return s_monthlyColors[i_color];
}

const ColorDataVector& MonthlyCardMgr::GetColor()
{
	return GetColor(m_currentColor);
}

bool MonthlyCardMgr::CanRefreshFreeStatus(MonthlyFreeType i_type)
{
	bool result = false;
	if (i_type == Free_MysteryCrystal)
		result = m_commonData.FreeCrystalAmount > 0;
	else if (i_type == Free_Fuel)
		result = m_commonData.FreeFuelAmount > 0;
	else if (i_type == Free_PVZ1Mode_TimeEnergy)
		result = m_commonData.FreeTimeEnergyAmount > 0;
	return result;
}

void MonthlyCardMgr::SetCommonData(const MonthlyCardCommonData& i_data)
{
	m_commonData = i_data;
}

void MonthlyCardMgr::SetCommonData(int i_freeCrystalAmount, int i_freeFuelAmount, int i_freeChangeNameCount, int i_monthlyChangeNamePrice, int i_normalChangeNamePrice, int i_freeTimeEnergyCount)
{
	m_commonData = MonthlyCardCommonData(i_freeCrystalAmount, i_freeFuelAmount, i_freeChangeNameCount, i_monthlyChangeNamePrice, i_normalChangeNamePrice, i_freeTimeEnergyCount);
}

MonthlyChangeNameType MonthlyCardMgr::GetChangeNameType()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (profile && profile->IsMonthlyCardActivated(E_MC_MAKE_UP))
		return GetFreeChangeNameCount() <= 0 ? N_MonthlyCard : N_Free;
	return N_Normal;
}

int MonthlyCardMgr::GetChangeNameCost()
{
	if (GetChangeNameType() == N_Free)
		return 0;
	if (!UserInfo::getInstance()->getChangeName())
		return 0;
	if (GetChangeNameType() == N_MonthlyCard)
		return m_commonData.MonthlyChangeNamePrice;
	return m_commonData.NormalChangeNamePrice;
}

int MonthlyCardMgr::GetMonthlyCardType()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (!profile)
		return 0;
	if (profile->IsMonthlyCardActivated(E_MC_SUPER))
		return MONTHLY_CARD_SUPER_QUERY;
	if (profile->IsMonthlyCardActivated(E_MC_CLASSICAL))
		return MONTHLY_CARD_CLASSIC_QUERY;
	return profile->IsMonthlyCardActivated(E_MC_MAKE_UP) ? MONTHLY_CARD_MAKEUP_QUERY : 0;
}

bool MonthlyCardMgr::CanGetFreeMysteryCrystal()
{
	return ProfileMgr::GetInstance().GetCurrentProfile()->IsMonthlyCardActivated(E_MC_CLASSICAL);
}

bool MonthlyCardMgr::CanGetFreeFuel()
{
	return ProfileMgr::GetInstance().GetCurrentProfile()->IsMonthlyCardActivated(E_MC_SUPER);
}

bool MonthlyCardMgr::CanChangeColor()
{
	return ProfileMgr::GetInstance().GetCurrentProfile()->IsMonthlyCardActivated(E_MC_MAKE_UP);
}

void MonthlyCardMgr::UpdateCurrentColor()
{
	gMessageRouter->Post(Message::NotifyColorChanged);
}

void MonthlyCardMgr::OnLuaNotify(const std::string& rStrEvent)
{
	if (rStrEvent != "monthly_card_query")
		return;
	bool can = CanChangeColor();
	if (can)
		return;
	SetCurrentColor((MonthlyColor)can);
	UpdateCurrentColor();
}

void MonthlyCardMgr::UploadColor()
{
	std::map<std::string, std::string> params;
	params["i"] = DString(m_currentColor).c_str();
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_MONTHLY_CARD_UPLOAD_COLOR, params, 30.0f, [this](const std::string& i_response)
	{
	}, true, true, "[NET_CONNECTING]", 0);
}

void MonthlyCardMgr::RequestFreeItems(MonthlyFreeType i_type)
{
	std::map<std::string, std::string> params;
	if (i_type == Free_MysteryCrystal)
		params["ai"] = std::to_string((int)Activity_MysteryStore);
	else if (i_type == Free_Fuel)
		params["ai"] = std::to_string((int)Activity_Rift);
	else if (i_type == Free_PVZ1Mode_TimeEnergy)
		params["ai"] = std::to_string((int)Activity_PVZ1_Mode);
	params["t"] = std::to_string(GetMonthlyCardType());
	params["i"] = "0";
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_DAVE_TREASURE_REWARD, params, 30.0f, [this, i_type](const std::string& i_response)
	{
	}, true, true, "[NET_CONNECTING]", 0);
}
