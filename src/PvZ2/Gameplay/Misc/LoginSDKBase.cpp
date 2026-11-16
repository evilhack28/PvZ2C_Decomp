//
//  LoginSDKBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "LoginSDKBase.h"

/////////////// LoginSDKBase ///////////////

bool LoginSDKBase::HandleOpenURLFunc(const SexyURL& url)
{
	return HandleOpenURL(url);
}

void LoginSDKBase::RequestAuthorize(const Sexy::Delegate1<int>& i_callBack)
{
	ConnectOpenURLFunc();

	m_authorizeCallback = i_callBack;
}

void LoginSDKBase::ConnectOpenURLFunc()
{
}

void LoginSDKBase::DisconnectOpenURLFunc()
{
}
