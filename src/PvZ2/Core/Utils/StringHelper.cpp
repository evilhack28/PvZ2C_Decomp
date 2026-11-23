//
//  StringHelper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include "UIEditor/StringHelper.h"
#include "ResourceHelpers.h"
#include "TodStringFile.h"
#include "SexyAppFramework/JsonReader.h"

template <typename T> T* FindResource_Impl(const std::string& i_id);

/////////////// Conversion ///////////////

SexyString StringHelper::ToStringValue(const std::string& str)
{
	SexyString aKey = Sexy::ToSexyString(str);
	SexyString aResult = TodStringTranslate(aKey);
	if (SexyStringCacheEnabled && aKey != aResult)
		CachedSexyStrings[str] = aResult;
	return aResult;
}

Sexy::Image* StringHelper::ToImage(const std::string& str, bool enableNull)
{
	return enableNull ? GetImageByNameWithUIFallback(str) : FindResource_Impl<Sexy::Image>(str);
}

bool StringHelper::ReadJson(const std::string& i_json, Sexy::StructuredData* o_data)
{
	if (!o_data)
		return false;

	int aLength = i_json.length();
	std::vector<uchar> aBuffer;
	aBuffer.resize(aLength + 1);
	memcpy(aBuffer.data(), i_json.data(), aLength);
	aBuffer[aLength] = 0;

	Sexy::JsonReader aReader;
	return aReader.Read(aBuffer.data(), aLength, o_data, NULL);
}
