//
//  NostalgiaAchievementDialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "NostalgiaAchievementDialog.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(NostalgiaAchievementDialog);

void NostalgiaAchievementDialog::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NostalgiaAchievementDialog);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(NostalgiaAchievementDialog);
}
