//
//  StringRestrictionSet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "RestrictionSet.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(StringRestrictionSet);

void StringRestrictionSet::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(RestrictionSetType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(blacklist, (RestrictionSetType)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(whitelist, (RestrictionSetType)1);
	REFLECTION_ENUMBUILDER_END(RestrictionSetType);

	REFLECTION_CLASSBUILDER_BEGIN(StringRestrictionSet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(RestrictionSetType, ListType);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, List);
	REFLECTION_CLASSBUILDER_END(StringRestrictionSet);
}
