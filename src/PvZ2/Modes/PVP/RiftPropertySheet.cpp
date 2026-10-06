//
//  RiftPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RiftPropertySheet.h"

RiftPropertySheet::~RiftPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftPropertySheet);

void RiftPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftLocalNoteConfig);
	REFLECTION_CLASSBUILDER_END(RiftLocalNoteConfig);

	REFLECTION_CLASSBUILDER_BEGIN(RiftPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, HowToPlayData);
	REFLECTION_CLASSBUILDER_END(RiftPropertySheet);
}
