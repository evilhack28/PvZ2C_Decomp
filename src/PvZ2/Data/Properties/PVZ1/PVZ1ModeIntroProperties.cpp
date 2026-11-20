//
//  PVZ1ModeIntroProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "IntroPVZ1Mode.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ1ModeIntroProperties);

void PVZ1ModeIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1ModeIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, CurrentIntroStage);
	REFLECTION_CLASSBUILDER_END(PVZ1ModeIntroProperties);
}
