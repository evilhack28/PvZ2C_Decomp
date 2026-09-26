//
//  SocialMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SocialMgr.h"
#include "GameEventMgr.h"

void SocialMgr::Destory()
{
}

const AuthInfo& SocialMgr::GetAuthInfo()
{
	return m_authInfo;
}

bool SocialMgr::LoginSocialPlatform(SocialPlatformType i_arg)
{
	return false;
}

bool SocialMgr::ShareContentToPlatform(const std::string& i_arg0, const std::string& i_arg1, const std::string& i_arg2, const std::string& i_arg3)
{
	return true;
}

bool SocialMgr::Init()
{
	return true;
}

SocialInfo* SocialMgr::GetSocialInfo() const
{
	return m_socialInfo;
}

SocialMgr::SocialMgr()
{
	m_socialPlatformType = SPT_None;
	m_socialInfo = new SocialInfo();
}

SocialMgr::~SocialMgr()
{
	delete m_socialInfo;
}

SocialPlatformType SocialMgr::GetSocialPlatformType()
{
	return m_socialPlatformType;
}

bool SocialMgr::LogoutSocialPlatform(bool bClean)
{
	m_socialPlatformType = SPT_None;
	gMessageRouter->Post(Message::SocialLogout);
	return true;
}

void SocialMgr::UpdateAuthInfo(S2C_AuthInfo& i_authInfo)
{
	m_authInfo.userId = i_authInfo.userId;
	m_authInfo.sessionKey = i_authInfo.sessionKey;
	m_authInfo.newUser = i_authInfo.newUser;
}
