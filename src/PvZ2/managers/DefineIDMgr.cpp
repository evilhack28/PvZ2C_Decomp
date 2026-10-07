//
//  DefineIDMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DefineIDMgr.h"
#include "ProfileMgr.h"
#include "AuthMgr.h"
#include "MD5.h"
#include "LawnApp.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/NetworkCacheQueue.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Lifecycle ///////////////

DefineIDMgr::DefineIDMgr()
{
}

DefineIDMgr::~DefineIDMgr()
{
}

/////////////// Accessors ///////////////

std::string DefineIDMgr::GetSignature()
{
	return ProfileMgr::GetInstance().GetPurchaseBroker()->GetSignature();
}

/////////////// Logic ///////////////

std::string DefineIDMgr::GetNewUserDefineID()
{
	std::string result("");
	std::string deviceId = ProfileMgr::GetInstance().GetPurchaseBroker()->GetDeviceID();
	if (AuthMgr::GetInstance().HasNoAuth() && deviceId == "")
	{
		result = "cd47ff5aa7491de630bcb042304d2d76";
	}
	else
	{
		std::string appName = gLawnApp->GetAppNameForiCloud();
		std::string source = deviceId + static_cast<std::string&&>(appName);
		MD5 md5(source);
		result = md5.toString();
	}
	return result;
}

void DefineIDMgr::ClearSaveDefineID()
{
	std::string userDataDir("");
	std::string externalDir("");
	userDataDir = Android::Resources::GetUserDataFolder((Sexy::AndroidAppDriver*)gLawnApp);
	externalDir = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp);
	std::string phoneIdPath = userDataDir + "/" + "phoneid.dat";
	std::string sdcardIdPath = externalDir + "/" + "sdcardid.dat";
	if (gSexyAppBase->FileExists(phoneIdPath))
	{
		gSexyAppBase->EraseFile(phoneIdPath);
	}
	if (gSexyAppBase->FileExists(sdcardIdPath))
	{
		gSexyAppBase->EraseFile(sdcardIdPath);
	}
}

std::string DefineIDMgr::GetUserDefineID()
{
	std::string macAddress;
	std::string imei;
	if (gLawnApp->IsAndroidSDKInitEnd() == 1 && gLawnApp->GetAndroidSDKInitStatus() == 0)
	{
		Android::Diag::GetDeviceIMEI(imei);
		Android::Diag::GetPrimaryMACAddress(macAddress);
	}
	std::string defineId = MD5(imei + macAddress + gLawnApp->GetAppNameForiCloud()).toString();
	if (imei.empty())
	{
		defineId.clear();
	}
	if (AuthMgr::GetInstance().HasNoAuth())
	{
		return defineId;
	}
	std::string phoneDir("");
	std::string externalDir("");
	phoneDir = Android::Resources::GetUserDataFolder((Sexy::AndroidAppDriver*)gLawnApp);
	externalDir = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp);
	if (phoneDir.size() == 0 || externalDir.size() == 0)
	{
		return defineId;
	}
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	if (process == nullptr)
	{
		return defineId;
	}
	NetworkCacheQueue* queue = process->GetNetworkCacheQueue();
	if (queue == nullptr)
	{
		return defineId;
	}
	std::string phoneIdPath = phoneDir + "/" + "phoneid.dat";
	std::string sdcardIdPath = externalDir + "/" + "sdcardid.dat";
	if (gSexyAppBase->FileExists(phoneIdPath) && gSexyAppBase->FileExists(sdcardIdPath))
	{
		if (queue->getDefineID().size() != 0)
		{
			Sexy::Buffer phoneBuffer;
			if (!gSexyAppBase->ReadBufferFromFile(phoneIdPath, &phoneBuffer))
			{
				return defineId;
			}
			std::string phoneLine = phoneBuffer.ReadLine();
			Sexy::Buffer sdcardBuffer;
			if (!gSexyAppBase->ReadBufferFromFile(sdcardIdPath, &sdcardBuffer))
			{
				return defineId;
			}
			std::string sdcardLine = sdcardBuffer.ReadLine();
			if (phoneLine.size() != 0 && sdcardLine.size() != 0)
			{
				if (sdcardLine == queue->getDefineID() && phoneLine == queue->getDefineID())
				{
					return queue->getDefineID();
				}
			}
		}
	}
	queue->setDefineID(defineId);
	NetworkMgr::Instance()->GetNewNetWorkProcess()->SaveCache();
	Sexy::Buffer buffer;
	buffer.WriteBytes((const uchar*)defineId.c_str(), defineId.size());
	if (gSexyAppBase->FileExists(phoneIdPath))
	{
		gSexyAppBase->EraseFile(phoneIdPath);
	}
	if (gSexyAppBase->FileExists(sdcardIdPath))
	{
		gSexyAppBase->EraseFile(sdcardIdPath);
	}
	gSexyAppBase->WriteBufferToFile(phoneIdPath, &buffer);
	gSexyAppBase->WriteBufferToFile(sdcardIdPath, &buffer);
	return defineId;
}
