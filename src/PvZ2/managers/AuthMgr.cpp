//
//  AuthMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AuthMgr.h"
#include "LawnApp.h"
#include "PVZ2UIDialog.h"
#include "PrimeText_Game.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/NetworkData.h"
#include "gameNetWork/PacketID.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Lifecycle ///////////////

AuthMgr::AuthMgr()
{
	m_reachLimit = false;
	m_noAuth = false;
	m_heatBeatTimer = 0.0f;
	m_heartBeatInterval = 0.0f;
	m_limitDesc = L"";
	m_desc = L"";
	m_characterId = "";
	m_token = "";
	gMessageRouter->Subscribe(Message::MsgErrorRequest, Sexy::MakeDelegate(*this, &AuthMgr::onMsgError));
}

AuthMgr::~AuthMgr()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Accessors ///////////////

void AuthMgr::SetToken(const std::string& i_token)
{
	m_token = i_token;
}

const std::string& AuthMgr::GetToken()
{
	return m_token;
}

void AuthMgr::SetLimitDesc(const std::wstring& i_desc)
{
	m_limitDesc = i_desc;
}

void AuthMgr::SetDesc(const std::wstring& i_desc)
{
	m_desc = i_desc;
}

void AuthMgr::SetCharacterId(const std::string& i_id)
{
	m_characterId = i_id;
}

const std::string& AuthMgr::GetCharacterId()
{
	return m_characterId;
}

void AuthMgr::SetAuthInfo(bool i_authed, bool i_illegal)
{
	m_authInfo.HasAuthed = i_authed;
	m_authInfo.IsIllegal = i_illegal;
}

bool AuthMgr::HasAuthed()
{
	return m_authInfo.HasAuthed;
}

/////////////// Auth check ///////////////

void AuthMgr::CheckLegal()
{
	if (HasAuthed())
		m_authInfo.IsIllegal = m_authInfo.Age < 18;
}

bool AuthMgr::NeedCheck()
{
	if (gLawnApp->IsServiceAvailable(Service_Auth) && m_authInfo.IsIllegal)
		return m_authInfo.HasAuthed;
	return false;
}

void AuthMgr::RequestAuth(const std::string& idcard, const std::string& name)
{
}

void AuthMgr::onMsgError(int erroId, const std::string& requestID)
{
}

/////////////// Heartbeat ///////////////

void AuthMgr::StartRequest()
{
	std::map<std::string, std::string> params;
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_AUTH_HEARTBEAT, params, 30.0f, [this](const std::string& i_response)
	{
	}, false, true, "[NET_CONNECTING]", 0);
}

void AuthMgr::Update(float dt)
{
	if (NeedCheck())
	{
		bool logined = NetworkMgr::Instance()->GetNewNetWorkProcess()->IsLogined();
		if (logined && m_heartBeatInterval != 0.0f && !m_reachLimit)
		{
			m_heatBeatTimer -= dt;
			if (gLawnApp->IsNetworkModuleOK() && m_heatBeatTimer <= 0.0f)
			{
				StartRequest();
				m_heatBeatTimer = m_heartBeatInterval;
			}
		}
	}
}

/////////////// Reach limit ///////////////

void AuthMgr::OnReachLimit()
{
	gLawnApp->KillPVZ2Dialog();
	Android::Device::ExitApp();
}

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

bool AuthMgr::HandleReachLimit()
{
	if (m_noAuth)
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(600), UIScaleNum(300));
		dialog->SetHeaderLabel(SexyString(L"[NO_AUTH_TITLE]"));
		dialog->SetFooterLabel(SexyString(L"[NO_AUTH_DESC]"));
		dialog->SetFooterAlign(DS_ALIGN_CENTER_VERTICAL_MIDDLE);
		dialog->SetFooterBottomPadding(UIScaleNum(2));
		dialog->SetBackgroundDarken(true, 0.5f);
		dialog->AddButton(SexyString(L"[OVERVIEW_CONFIRM]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
		return false;
	}
	else
	{
		SexyString limitDesc = Sexy::WStringToSexyString(m_limitDesc);
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
		dialog->SetHeaderLabel(Sexy::StringToWString("[AUTH_LIMIT_TITLE]"));
		dialog->SetFooterLabel(limitDesc);
		dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
		dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
		dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &AuthMgr::OnReachLimit)));
		return true;
	}
}
