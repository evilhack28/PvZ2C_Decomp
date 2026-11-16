//
//  HotUITextEntry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUITextEntry.h"

HotUITextEntryProperties::~HotUITextEntryProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUITextEntry);

void HotUITextEntry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUITextEntry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUITextEntry);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUITextEntryProperties);

void HotUITextEntryProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUITextEntryProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::string, DefaultText);
		REFLECTION_CLASSBUILDER_FIELD(int, MaxCharacters);
		REFLECTION_CLASSBUILDER_FIELD(bool, UseNumericKeyboard);
	REFLECTION_CLASSBUILDER_END(HotUITextEntryProperties);
}
