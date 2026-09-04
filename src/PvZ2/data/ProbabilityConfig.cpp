//
//  ProbabilityConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/ReflectionBuilder.h"

#include "ProbabilityConfig.h"
#include "PVZDB.h"

/////////////// ProbabilityConfig ///////////////

RT_CLASS_IMPLEMENT(ProbabilityConfig);

void ProbabilityConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ProbabilityConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, keys);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, values);
		REFLECTION_CLASSBUILDER_FIELD(std::string, title);
	REFLECTION_CLASSBUILDER_END(ProbabilityConfig);
}

const RtWeakPtr<ProbabilityConfig> ProbabilityConfig::GetProbabilityConfig(const SexyString& aliases)
{
	return PVZDB::GetInstance().FindObjectByAlias<ProbabilityConfig>(PVZDB::TABLE_PROBABILITY_CONFIG, RtName(aliases));
}

bool ProbabilityConfig::GetKeyValue(uint32 index, std::string& key, float& value)
{
	if (index >= keys.size())
	{
		return false;
	}

	key = keys[index];
	value = values[index];

	return true;
}

uint32 ProbabilityConfig::GetSize()
{
	return keys.size();
}
