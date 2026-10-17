//
//  LevelModuleProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-16.
//

#include "SexyAppFramework/Common.h"

#include "LevelModule.h"

RtClass* LevelModuleProperties::GetModuleClass() const
{
	return NULL;
}


#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelModuleProperties);

void LevelModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ResourceGroupNames);
		REFLECTION_CLASSBUILDER_FIELD(RtId, DifficultyProps);
		REFLECTION_CLASSBUILDER_FIELD(std::string, IconImage);
		REFLECTION_CLASSBUILDER_FIELD(std::string, IconText);

	REFLECTION_CLASSBUILDER_END(LevelModuleProperties);
}
