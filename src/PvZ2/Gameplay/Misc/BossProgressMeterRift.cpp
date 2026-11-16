//
//  BossProgressMeterRift.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BossProgressMeterRift.h"
#include "ChallengeScoringUI.h"
#include "GameEventMgr.h"
#include "ZombossRiftBattleModule.h"
#include "ResourceHelpers.h"
#include "ReflectionBuilder.h"
#include "RedPacketRewardInfo.h"

/////////////// Lifecycle ///////////////

BossProgressMeterRift::~BossProgressMeterRift()
{
}

BossProgressMeterRift::BossProgressMeterRift()
{
	m_lootPhaseActive = 0;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(BossProgressMeterRift);

void BossProgressMeterRift::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BossProgressMeterRift);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BossProgressMeter);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_lootPhaseActive);

	REFLECTION_CLASSBUILDER_END(BossProgressMeterRift);
}

/////////////// Logic ///////////////

static WEAKIMAGE(IMAGE_UI_HUD_INGAME_PROGRESS_METER_FILL_ZOMBOSS_BONUS, "IMAGE_UI_HUD_INGAME_PROGRESS_METER_FILL_ZOMBOSS_BONUS")

void BossProgressMeterRift::initLoadingResourcesGroupList()
{
}

void BossProgressMeterRift::Draw(Graphics* i_g)
{
	BossProgressMeter::Draw(i_g);
}

float BossProgressMeterRift::drawCalcFillPercent(int i_phaseNumber, float i_prevPhasePercentage)
{
	if (m_lootPhaseActive)
		return 100.0f;
	return BossProgressMeter::drawCalcFillPercent(i_phaseNumber, i_prevPhasePercentage);
}

void BossProgressMeterRift::onEnterLootPhase()
{
	getStageCounterUI()->SetRiftBonusMode(true);
	m_lootPhaseActive = true;
}

ImagePtr BossProgressMeterRift::getMeterFillImage()
{
	if (m_lootPhaseActive)
		return IMAGE_UI_HUD_INGAME_PROGRESS_METER_FILL_ZOMBOSS_BONUS;
	return BossProgressMeter::getMeterFillImage();
}

void BossProgressMeterRift::registerForEvents()
{
	BossProgressMeter::registerForEvents();
	gMessageRouter->Subscribe(Message::BossRiftEnterLootPhase, Sexy::MakeDelegate(*this, &BossProgressMeterRift::onEnterLootPhase));
}
