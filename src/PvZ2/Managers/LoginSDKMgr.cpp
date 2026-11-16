//
//  LoginSDKMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "Social/LoginSDKMgr.h"
#include "Social/SinaSDK.h"
#include "Social/WechatSDK.h"

/////////////// LoginSDKMgr ///////////////

LoginSDKMgr::LoginSDKMgr()
	: m_receivedBindingData(false)
{
}

LoginSDKMgr::~LoginSDKMgr()
{
	if (m_sinaSDK)
	{
		delete m_sinaSDK;
		m_sinaSDK = NULL;
	}
	if (m_wechatSDK)
	{
		delete m_wechatSDK;
		m_wechatSDK = NULL;
	}
}

void LoginSDKMgr::SDKLogin(int sdkType, const Sexy::Delegate1<int>& i_callBack)
{
}

void LoginSDKMgr::DoSDKShare(int sdkType, const std::string& i_url, bool toTimeLine)
{
}

bool LoginSDKMgr::IsSDKInstalled(int sdkType)
{
	return false;
}

void LoginSDKMgr::setSinaSDKUUID(const std::string& value)
{
	m_sinaSDKUUID = value;
}

void LoginSDKMgr::setWechatSDKUUID(const std::string& value)
{
	m_wechatSDKUUID = value;
}

void LoginSDKMgr::setTencentUUID(const std::string& value)
{
	m_tencentSDKUUID = value;
}

std::string LoginSDKMgr::getSinaSDKUUID() const
{
	return m_sinaSDKUUID;
}

std::string LoginSDKMgr::getWechatSDKUUID() const
{
	return m_wechatSDKUUID;
}

std::string LoginSDKMgr::getTencentSDKUUID() const
{
	return m_tencentSDKUUID;
}

bool LoginSDKMgr::isAlreadyBoundSinaSDK() const
{
	return m_sinaSDKUUID != "";
}

bool LoginSDKMgr::isAlreadyBoundWechatSDK() const
{
	return m_wechatSDKUUID != "";
}

bool LoginSDKMgr::isAlreadyBoundTencentSDK() const
{
	return m_tencentSDKUUID != "";
}
