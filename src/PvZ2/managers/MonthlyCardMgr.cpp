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

void MonthlyCardMgr::SetCommonData(int i_p1, int i_p2, int i_p3, int i_p4, int i_p5, int i_p6)
{
	m_commonData = MonthlyCardCommonData(i_p1, i_p2, i_p3, i_p4, i_p5, i_p6);
}

MonthlyChangeNameType MonthlyCardMgr::GetChangeNameType()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (profile && profile->IsMonthlyCardActivated((eMonthlyCardType)1))
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
	if (profile->IsMonthlyCardActivated((eMonthlyCardType)4))
		return 17;
	if (profile->IsMonthlyCardActivated((eMonthlyCardType)2))
		return 4;
	return profile->IsMonthlyCardActivated((eMonthlyCardType)1) ? 18 : 0;
}

bool MonthlyCardMgr::CanGetFreeMysteryCrystal()
{
	return ProfileMgr::GetInstance().GetCurrentProfile()->IsMonthlyCardActivated((eMonthlyCardType)2);
}

bool MonthlyCardMgr::CanGetFreeFuel()
{
	return ProfileMgr::GetInstance().GetCurrentProfile()->IsMonthlyCardActivated((eMonthlyCardType)4);
}

bool MonthlyCardMgr::CanChangeColor()
{
	return ProfileMgr::GetInstance().GetCurrentProfile()->IsMonthlyCardActivated((eMonthlyCardType)1);
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
		params["ai"] = std::to_string(10809);
	else if (i_type == Free_Fuel)
		params["ai"] = std::to_string(10800);
	else if (i_type == Free_PVZ1Mode_TimeEnergy)
		params["ai"] = std::to_string(10836);
	params["t"] = std::to_string(GetMonthlyCardType());
	params["i"] = "0";
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_DAVE_TREASURE_REWARD, params, 30.0f, [this, i_type](const std::string& i_response)
	{
	}, true, true, "[NET_CONNECTING]", 0);
}
