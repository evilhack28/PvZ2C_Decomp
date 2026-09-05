#include "SexyAppFramework/Common.h"

#include "EASquaredRewardHelper.h"
#include "AudioMgr.h"
#include "LawnApp.h"

int EASquaredRewardHelper::sm_numCoinsToRewardForCompletion = 0;
PVZ2UIAwardScreen* EASquaredRewardHelper::m_awardScreen = NULL;

void EASquaredRewardHelper::onCoinAwardScreenDismissed()
{
	if (m_awardScreen)
	{
		m_awardScreen->KillAwardScreen();
		gLawnApp->SafeDeleteWidget(m_awardScreen);
	}

	if (sm_numCoinsToRewardForCompletion > 0)
	{
		AwardsGranter::GiveAward(AWARD_Coins, "", sm_numCoinsToRewardForCompletion, AWARDCONTEXT_EASqaured, true);
		gAudioMgr->SendEvent("Play_UI_Game_Give_Coins");
		sm_numCoinsToRewardForCompletion = 0;
	}
}

void EASquaredRewardHelper::ShowCoinRewardsForAdCompletion(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason, int i_rewardQuantity)
{
	if (i_reason != EASquaredAdFinishedReason::Completed)
		return;

	sm_numCoinsToRewardForCompletion = i_rewardQuantity;
	m_awardScreen = new PVZ2UIAwardScreen();
	m_awardScreen->ShowAwardScreen();
	m_awardScreen->SetBackgroundType(AWARDSCREEN_BG_DARKENED);
	m_awardScreen->SetFadesOutOnEnd(true);
	m_awardScreen->SetOnAwardSequenceCompleted(Sexy::MakeDelegate(&EASquaredRewardHelper::onCoinAwardScreenDismissed));
	m_awardScreen->Start();
}
