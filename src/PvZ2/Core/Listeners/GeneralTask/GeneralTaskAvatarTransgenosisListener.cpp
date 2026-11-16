//
//  GeneralTaskAvatarTransgenosisListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "GeneralTask.h"

GeneralTaskAvatarTransgenosisListener::GeneralTaskAvatarTransgenosisListener()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GeneralTaskAvatarTransgenosisListener);

void GeneralTaskAvatarTransgenosisListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskAvatarTransgenosisListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskAvatarTransgenosisListener);
}
