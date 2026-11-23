//
//  Log_TGA.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-22.
//

#include "SexyAppFramework/Common.h"

#include "LogCollector/LogCollector.h"
#include "DNode/DValue.h"

/////////////// Info ///////////////

Log_TGA& Log_TGA::getLogInfo(const std::string& i_logId, OUT_PARAM DValue& value)
{
	DValueVector values;
	values.push_back(DValue(getClientTime()));
	values.push_back(DValue(i_logId));
	value = values;
	return *this;
}

Log_TGA& Log_TGA::getBasicInfo(OUT_PARAM DValue& value)
{
	DValueVector& values = value.asDValueVector();
	values.push_back(DValue(getTargetPlatform()));
	values.push_back(DValue(getDefineID()));
	values.push_back(DValue(getUserID()));
	values.push_back(DValue(getCharacterID()));
	values.push_back(DValue(getChannelID()));
	values.push_back(DValue(getProfileCreatedTime()));
	values.push_back(DValue(getVersionID()));
	values.push_back(DValue(getSignature()));
	return *this;
}

Log_TGA& Log_TGA::getBasicInfoForLogin(OUT_PARAM DValue& value)
{
	DValueVector& values = value.asDValueVector();
	values.push_back(DValue(getTargetPlatform()));
	values.push_back(DValue(getDefineID()));
	values.push_back(DValue(getCharacterID()));
	values.push_back(DValue(getUniqueCharacterID()));
	values.push_back(DValue(getChannelID()));
	values.push_back(DValue(getProfileCreatedTime()));
	values.push_back(DValue(getVersionID()));
	values.push_back(DValue(getSignature()));
	return *this;
}

Log_TGA& Log_TGA::getOtherInfo(const std::vector<std::string>& otherParams, OUT_PARAM DValue& value)
{
	DValueVector& values = value.asDValueVector();
	std::vector<std::string>::const_iterator it = otherParams.begin();
	std::vector<std::string>::const_iterator end = otherParams.end();
	for (; it != end; ++it)
		values.push_back(DValue(*it));
	return *this;
}
