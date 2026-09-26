//
//  AdaptorJoustWinStreakDialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustWinStreakDialog.h"

AdaptorJoustWinStreakDialog::AdaptorJoustWinStreakDialog()
{
}

AdaptorJoustWinStreakDialog::~AdaptorJoustWinStreakDialog()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustWinStreakDialog);

void AdaptorJoustWinStreakDialog::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustWinStreakDialog);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustWinStreakDialog);
}
