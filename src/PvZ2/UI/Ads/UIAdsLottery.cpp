//
//  UIAdsLottery.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "UIAdsLottery.h"

UIAdsLottery::UIAdsLottery()
{
	m_adsLotteryPanel = 0;
	m_lastTimes = 0;
	m_timeUp = 0;
	m_buttonLock = 0;
}

void UIAdsLottery::Draw(Sexy::Graphics* i_g)
{
	base_type::Draw(i_g);
}

