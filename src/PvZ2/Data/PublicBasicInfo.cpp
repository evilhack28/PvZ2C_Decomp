//
//  PublicBasicInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "LogCollector/LogCollector.h"
#include "LawnApp.h"
#include "AuthMgr.h"
#include "ProfileMgr.h"
#include "DNode/DString.h"
#include "DefineIDMgr.h"
#include "IdentifierMgr.h"
#include "gameNetWork/NetworkMgr.h"
#include "SexyAppFramework/IDiagDriver.h"
#include <GLES2/gl2.h>
#include <sstream>
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Basic info ///////////////

__attribute__((noclone, noinline)) static DString FormatLocalTime(time_t i_time)
{
	tm* aTime = localtime(&i_time);
	DString aResult;
	aResult.format("%d-%02d-%02d %02d:%02d:%02d", aTime->tm_year + 1900, aTime->tm_mon + 1, aTime->tm_mday, aTime->tm_hour, aTime->tm_min, aTime->tm_sec);
	return aResult;
}

std::string PublicBasicInfo::getDefineID()
{
	return LazySingleton<DefineIDMgr>::GetInstance().GetNewUserDefineID();
}

std::string PublicBasicInfo::getSignature()
{
	return LazySingleton<DefineIDMgr>::GetInstance().GetSignature();
}

std::string PublicBasicInfo::getProfileCreatedTime()
{
	return gLawnApp->GetProfileCreatedTime();
}

std::string PublicBasicInfo::getVersionID()
{
	return gSexyAppBase->mProductVersion;
}

std::string PublicBasicInfo::getUniqueCharacterID()
{
	std::string aID = LazySingleton<AuthMgr>::GetInstance().GetCharacterId();
	if (aID.empty())
	{
		Android::Diag::GetUniqueCharacterID(aID);
		LazySingleton<AuthMgr>::GetInstance().SetCharacterId(aID);
	}
	return aID;
}

std::string PublicBasicInfo::getProjectCode()
{
	return "309878";
}

std::string PublicBasicInfo::getPublicIP()
{
	return "unknown";
}

std::string PublicBasicInfo::getTargetPlatform()
{
	return "Android";
}

std::string PublicBasicInfo::getConnectType()
{
	return gLawnApp->GetNetworkType();
}

std::string PublicBasicInfo::getChannelID()
{
	std::string aChannel = "unknown";
	aChannel = Android::Util::GetPackageName();
	return aChannel;
}

std::string PublicBasicInfo::getLocalIP()
{
	return "unknown";
}

std::string PublicBasicInfo::getServerID()
{
	return "unknown";
}

std::string PublicBasicInfo::getOSVersion()
{
	if (gSexyAppBase->mDiagDriver != NULL)
		return gSexyAppBase->mDiagDriver->GetInfoStringSafe(Sexy::IDiagDriver::INFO_OSVersion);
	return "unknown";
}

std::string PublicBasicInfo::getGPUModel()
{
	return (const char*)glGetString(GL_RENDERER);
}

std::string PublicBasicInfo::getDeviceModel()
{
	return gLawnApp->GetDeviceType();
}

std::string PublicBasicInfo::getPCPID()
{
	return LazySingleton<ProfileMgr>::GetInstance().GetAccountName();
}

PublicBasicInfo::PublicBasicInfo()
	: bNeedUserID(false)
{
}

void PublicBasicInfo::setNeedUserID(bool iNeedUserID)
{
	bNeedUserID = iNeedUserID;
}

std::string PublicBasicInfo::getMemory()
{
	if (gSexyAppBase && gSexyAppBase->mDiagDriver)
	{
		double aUsed = gSexyAppBase->mDiagDriver->GetInfoNumber(Sexy::IDiagDriver::INFO_MemoryUsed);
		double anAvailable = gSexyAppBase->mDiagDriver->GetInfoNumber(Sexy::IDiagDriver::INFO_MemoryAvailable);
		double aTotal = anAvailable + aUsed;
		DString aString;
		aString.format("%7.2fMB", aTotal / 1048576.0);
		return aString.c_str();
	}
	return "unknown";
}

std::string PublicBasicInfo::getStorage()
{
	std::string aUserDataFolder = Android::Resources::GetUserDataFolder((Sexy::AndroidAppDriver*)gLawnApp);
	std::string anExternalFilesDirectory = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp);
	long aUserBlockCount = Android::Resources::GetFileSystemBlockCount(aUserDataFolder);
	long anExternalBlockCount = Android::Resources::GetFileSystemBlockCount(anExternalFilesDirectory);
	long aUserBlockSize = Android::Resources::GetFileSystemBlockSize(aUserDataFolder);
	long anExternalBlockSize = Android::Resources::GetFileSystemBlockSize(anExternalFilesDirectory);
	DString aString;
	aString.format("phone:%7.2fG,sdcard:%7.2fG", (float)(aUserBlockSize * aUserBlockCount) / 1073741824.0f, (float)(anExternalBlockSize * anExternalBlockCount) / 1073741824.0f);
	return aString.c_str();
}

std::string PublicBasicInfo::getResolutionOfScreen()
{
	int aWidth = 0;
	int aHeight = 0;
	Android::Graphics::GetScreenSizeInPoints(&aWidth, &aHeight);
	aWidth = aWidth / 2 * 2;
	aHeight = aHeight / 2 * 2;
	std::stringstream aStream(std::ios::out | std::ios::in);
	aStream.str("");
	aStream << aWidth << " X " << aHeight;
	return aStream.str();
}

PublicBasicInfo& PublicBasicInfo::getResult(const std::string& result, OUT_PARAM DValue& value)
{
	if (value.isDValueMap())
		value.asDValueMap()["Result"] = result;
	return *this;
}

PublicBasicInfo& PublicBasicInfo::getBasicInfo(OUT_PARAM DValue& value)
{
	DValueMap aMap;
	aMap["Device_ID"] = getPCPID();
	aMap["User_ID"] = getUserID();
	aMap["Character_ID"] = getCharacterID();
	aMap["Client_time"] = getClientTime();
	aMap["Version_ID"] = getVersionID();
	aMap["Channel_ID"] = getChannelID();
	aMap["Session_ID"] = getSessionID();
	aMap["Project_Code"] = getProjectCode();
	value = aMap;
	return *this;
}

PublicBasicInfo& PublicBasicInfo::getBehavior(OUT_PARAM DValue & i_arg)
{
}

std::string PublicBasicInfo::getCharacterID()
{
	std::stringstream aStream(std::ios::out | std::ios::in);
	aStream.str("");
	INetworkMsgProcess* aProcess = NetworkMgr::Instance()->GetNewNetWorkProcess();
	if (aProcess)
		aStream << aProcess->INetworkMsgProcess::GetPlayUserId();
	return aStream.str();
}

static std::string sUserID;

std::string PublicBasicInfo::getUserID()
{
	if (sUserID.size() == 0)
	{
		sUserID = Sexy::LazySingleton<IdentifierMgr>::GetInstance().GetUUID();
		if (bNeedUserID && sUserID.size() == 0)
			sUserID = Sexy::LazySingleton<IdentifierMgr>::GetInstance().GenerateLocalUUID();
	}
	return sUserID;
}

std::string PublicBasicInfo::getClientTime()
{
	return FormatLocalTime(time(NULL)).c_str();
}
