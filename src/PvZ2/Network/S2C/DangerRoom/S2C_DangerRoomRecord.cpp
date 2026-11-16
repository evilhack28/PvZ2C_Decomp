//
//  S2C_DangerRoomRecord.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"
#include "MD5.h"
#include "pcpEncrypty/PCPEncrypt.h"

/////////////// Logic ///////////////

bool S2C_DangerRoomRecord::Compress()
{
	S2C_DangerRoomPlantNumArray plantNumArray;
	plantNumArray.m_plantNumList = m_plantNumList;
	std::string json;
	plantNumArray.ToJason(json);
	unsigned long compressedLength = 0x1400;
	AutoBuffer buffer(compressedLength);
	unsigned char* compressed = buffer.GetData();
	std::string encoded = base64_url_safe((const unsigned char*)json.c_str(), json.length());
	int result = gzcompress((unsigned char*)encoded.c_str(), encoded.length(), compressed, &compressedLength);
	if (result == 0)
	{
		m_plantNumStr = base64_url_safe(compressed, compressedLength);
		MD5 md5(m_plantNumStr);
		m_plantNumMD5 = md5.toString();
	}
	return result == 0;
}

bool S2C_DangerRoomRecord::Decompress()
{
	bool success = false;
	MD5 md5(m_plantNumStr);
	std::string digest = md5.toString();
	if (digest == m_plantNumMD5)
	{
		std::string decoded = base64_decode_url_safe(m_plantNumStr);
		unsigned long length = 0x100000;
		AutoBuffer buffer(length);
		unsigned char* data = buffer.GetData();
		if (gzdecompress((unsigned char*)decoded.c_str(), decoded.length(), data, &length) == 0)
		{
			data[length + 1] = '\0';
			decoded = (const char*)data;
			decoded = base64_decode_url_safe(decoded);
			decoded.insert(0, "{\"d\" : {\"pl\" : ");
			decoded += "}}";
			S2C_DangerRoomPlantNumArray plantNumArray;
			success = plantNumArray.SerializeJsonToObj(decoded, "d");
			if (success)
				m_plantNumList = plantNumArray.m_plantNumList;
		}
	}
	return success;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_DangerRoomRecord);

void S2C_DangerRoomRecord::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CthulhuDangerroomInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, TypeName, n);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Energy, e);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(pvztime_t, TriggerTimeSum, t);
	REFLECTION_CLASSBUILDER_END(CthulhuDangerroomInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_DangerRoomRecord);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_level, l);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_maxLevel, ml);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_maxLastWeekLevel, lwml);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int32>, m_mowers, lc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_plantfood, eb);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_plantfoodBuyCount, eub);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_plantNumStr, pl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_plantNumMD5, dm);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_sunNum, ls);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_dayScore, ds);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_cukeNum, bn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_cukeUsedNum, bu);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_medal, m);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_jumpCost, jc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_jumpLevel, jl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_rankPredict, par);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_scorePredict, pas);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_artifactOrderId, on);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_artifactLeftTimes, alt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_artifactMaxTimes, amt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<CthulhuDangerroomInfo>, m_cthulhuInfoList, cil);
	REFLECTION_CLASSBUILDER_END(S2C_DangerRoomRecord);
}
