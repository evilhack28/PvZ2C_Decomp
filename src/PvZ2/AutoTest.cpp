//
//  AutoTest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "AutoTest.h"
#include "AudioMgr.h"
#include "LawnApp.h"
#include "talking_game.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AutoTest);

void AutoTest::updateState(bool i_arg)
{
}

void AutoTest::setIsOn(bool i_value)
{
	if (m_isOn != i_value)
	{
		m_isOn = i_value;
		if (i_value)
		{
			gLawnApp->mInteractiveSoundManager->StopAll();
			gLawnApp->mInteractiveSoundManager->Update();
			AudioMgr::GetInstancePtr()->SetAudioDriver(NULL);
			talkingGame::GetInstancePtr()->setPause(true);
		}
		else
		{
			talkingGame::GetInstancePtr()->setPause(false);
		}

		updateState(m_isOn);
	}
}

