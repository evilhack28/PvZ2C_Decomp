//
//  AdaptorJoustWinStreakDisplayEntry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustWinStreakDisplayEntry.h"

AdaptorJoustWinStreakDisplayEntry::AdaptorJoustWinStreakDisplayEntry()
{
}

AdaptorJoustWinStreakDisplayEntry::~AdaptorJoustWinStreakDisplayEntry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustWinStreakDisplayEntry);

void AdaptorJoustWinStreakDisplayEntry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustWinStreakDisplayEntry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustWinStreakDisplayEntry);
}

#include "AdaptorJoustWinStreakDisplayEntry.h"
void AdaptorJoustWinStreakDisplayEntry::onLinkToUIViewCreated()
{
	 AdaptorJoustWinStreakDisplayEntry::refresh();
}
