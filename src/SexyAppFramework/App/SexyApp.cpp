//
//  SexyApp.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyApp.h"
#include "Crypt/RegKey.h"

using namespace Sexy;

extern const char* BUILD_INFO_MARKER;

extern const char* SIGNATURE_CODE_MARKER;

/////////////// Lifecycle ///////////////

SexyApp::SexyApp()
{
	gSexyApp = this;
	mCheckPartnerSig = true;
	mTimesPlayed = 0;
	mTimesExecuted = 0;
	mTimedOut = false;
	mIsRegistered = false;
	mBuildUnlocked = false;
	mDownloadId = 0;
	mRegSource = "ingame";
	mSkipAd = false;
	mDontUpdate = false;
	mLastVerCheckQueryTime = 0;
	mCompanyName = "PopCap";
	mFullCompanyName = "PopCap Games";

	char aBuildNumStr[9] = {0};
	strncpy(aBuildNumStr, BUILD_INFO_MARKER, 8);
	mBuildNum = atoi(aBuildNumStr);
	if (mBuildNum != 0)
		mBuildDate = BUILD_INFO_MARKER + 8;
}

SexyApp::~SexyApp()
{
	gSexyApp = NULL;
}

/////////////// Update ///////////////

void SexyApp::UpdateFrames()
{
	SexyAppBase::UpdateFrames();
}

bool SexyApp::ShouldCheckForUpdate()
{
	return false;
}

void SexyApp::UpdateCheckQueried()
{
	time_t aTime;
	time(&aTime);
	mLastVerCheckQueryTime = aTime;
}

void SexyApp::URLOpenSucceeded(const std::string& theURL)
{
	SexyAppBase::URLOpenSucceeded(theURL);
	if (mShutdownOnURLOpen)
		mSkipAd = true;
}

void SexyApp::OpenUpdateURL()
{
	Shutdown();
}

bool SexyApp::OpenHTMLTemplate(const std::string& theTemplateFile, const DefinesMap& theDefinesMap)
{
	return false;
}

void SexyApp::Init()
{
	OutputDebugStrF(L"Product: %ls\r\n", ToSexyString(mProdName).c_str());
	OutputDebugStrF(L"Version: %ls\r\n", ToSexyString(mProductVersion).c_str());
	SexyAppBase::Init();
	if (IsScreenSaver())
		mSkipAd = true;
	mTimesExecuted++;
}

void SexyApp::UpdateFramesPaused()
{
	SexyAppBase::UpdateFramesPaused();
}

void SexyApp::PreTerminate()
{
}

void SexyApp::PreDisplayHook()
{
}

void SexyApp::HandleNotifyGameMessageCommandLine(const std::wstring& theCommandLine)
{
}

void SexyApp::WriteRegistrationInfo(std::string theRegUser, std::string theRegCode, int theTimesPlayed, int theTimesExecuted)
{
}

void SexyApp::ReadRegistrationInfo(std::string* theUser, std::string* theKey, int* theTimesPlayed, int* theTimesExecuted)
{
}

void SexyApp::ReadFromRegistry()
{
	SexyAppBase::ReadFromRegistry();
}

void SexyApp::WriteToRegistry()
{
	SexyAppBase::WriteToRegistry();
	RegistryWriteInteger("LastVerCheckQueryTime", mLastVerCheckQueryTime);
	if (mRegUserName.length() == 0 && mUserName.length() != 0 && mRegCode.length() != 0)
		mRegUserName = mUserName;
	WriteRegistrationInfo(mRegUserName, mRegCode, mTimesPlayed, mTimesExecuted);
}

bool SexyApp::OpenRegisterPage()
{
	DefinesMap aDefinesMap;
	return OpenRegisterPage(aDefinesMap);
}

void SexyApp::GetSEHWebParams(DefinesMap* theDefinesMap)
{
	theDefinesMap->insert(DefinesMap::value_type("username", mUserName));
	theDefinesMap->insert(DefinesMap::value_type("buildnum", StrFormat("%d", mBuildNum)));
	theDefinesMap->insert(DefinesMap::value_type("builddate", mBuildDate));
	theDefinesMap->insert(DefinesMap::value_type("referid", mReferId));
}

void SexyApp::HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue)
{
	if (theParamName == "-version")
	{
		std::string aVersionString =
			"Product: " + mProdName + "\r\n" +
			"Version: " + mProductVersion + "\r\n" +
			"Build Num: " + SexyStringToString(StrFormat(L"%d", mBuildNum)) + "\r\n" +
			"Build Date: " + mBuildDate;
		MsgBox(aVersionString, "Version Info", 0);
		DoExit(0);
	}
	else if (!(theParamName == "-betasite"))
		SexyAppBase::HandleCmdLineParam(theParamName, theParamValue);
}

void SexyApp::InitPropertiesHook()
{
	bool aCheckSig = false;
	if (!IsScreenSaver())
		aCheckSig = mCheckPartnerSig;
	LoadProperties("properties\\partner.xml", false, aCheckSig, true);

	bool noReg = GetBoolean("NoReg", false);
	if (noReg)
	{
		mIsRegistered = true;
		mBuildUnlocked = true;
	}

	mProdName = SexyStringToString(GetString("ProdName", StringToSexyString(mProdName)));

	if (!mForceFullscreen)
		mIsWindowed = GetBoolean("DefaultWindowed", mIsWindowed);

	SexyString aTitle = GetString("Title", L"");
	if (aTitle.length() > 0)
		mTitle = aTitle + L" " + StringToSexyString(mProductVersion);
}

bool SexyApp::CheckSignature(const Buffer& theBuffer, const std::string& theFileName)
{
	bool aResult = mSkipSignatureChecks;
	if (!aResult)
	{
		FILE* aSigFile = fopen((theFileName + ".sig").c_str(), "rb");
		if (aSigFile != NULL)
		{
			char aSigStr[25];
			fread(aSigStr, 1, 24, aSigFile);
			aSigStr[24] = 0;

			char* aData = new char[theBuffer.GetDataLen() + 4];

			char aCodeStr[9] = {0};
			strncpy(aCodeStr, SIGNATURE_CODE_MARKER, 8);
			int aCode = atoi(aCodeStr);
			aData[0] = aCode;
			aData[1] = aCode >> 8;
			aData[2] = aCode >> 16;
			aData[3] = (aCode >> 24) & 0xFF;
			int aDataLen = 4;

			theBuffer.SeekFront();
			while (!theBuffer.AtEnd())
			{
				char aChar = theBuffer.ReadByte();
				fread(&aChar, 1, 1, aSigFile);
				if (!isspace((uchar)aChar))
					aData[aDataLen++] = aChar;
			}
			fclose(aSigFile);

			BigInt n("D99BC76AB7B2578738E606F7");
			BigInt e("11");
			BigInt aHash = HashData(aData, aDataLen, 94);
			delete[] aData;

			BigInt aSig(aSigStr);
			aResult = aSig.ModPow(e, n) == aHash;
		}
	}
	return aResult;
}

bool SexyApp::OpenRegisterPage(const DefinesMap& theDefinesMap)
{
	DefinesMap aDefinesMap;
	aDefinesMap.insert(DefinesMap::value_type("Src", mRegSource));
	aDefinesMap.insert(DefinesMap::value_type("ProdName", mProdName));
	aDefinesMap.insert(DefinesMap::value_type("Version", mProductVersion));
	aDefinesMap.insert(DefinesMap::value_type("Variation", mVariation));
	aDefinesMap.insert(DefinesMap::value_type("ReferId", mReferId));
	aDefinesMap.insert(DefinesMap::value_type("DownloadId", StrFormat("%d", mDownloadId)));
	aDefinesMap.insert(DefinesMap::value_type("TimesPlayed", StrFormat("%d", mTimesPlayed)));
	aDefinesMap.insert(DefinesMap::value_type("TimesExecuted", StrFormat("%d", mTimesExecuted)));
	aDefinesMap.insert(DefinesMap::value_type("TimedOut", mTimedOut ? "Y" : "N"));

	std::string aStats;
	DefinesMap::const_iterator anItr = theDefinesMap.begin();
	while (anItr != theDefinesMap.end())
	{
		std::string aName = anItr->first;
		std::string aValue = anItr->second;
		aStats += StrFormat("%04X", aName.length()) + aName + "S" + StrFormat("%04X", aValue.length()) + aValue;
		++anItr;
	}
	aDefinesMap.insert(DefinesMap::value_type("Stats", aStats));

	if (FileExists("register.tpl"))
		return OpenHTMLTemplate("register.tpl", aDefinesMap);

	return OpenURL(mRegisterLink, false);
}
