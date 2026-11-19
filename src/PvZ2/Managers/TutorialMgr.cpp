//
//  TutorialMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "TutorialMgr.h"

/////////////// Queue ///////////////

void TutorialMgr::TryClearQueuedTutorial(MapTutorialState i_state)
{
	if (m_queuedTutorial == i_state && m_queuedTutorial != TUTORIAL_NONE)
		m_queuedTutorial = TUTORIAL_NONE;
}
