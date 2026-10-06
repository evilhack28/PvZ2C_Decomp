//
//  SkyCityStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-05.
//

#include "Common.h"
#include "SkyCityStage.h"
#include "AirshipProgressMeter.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "BoardConstants.h"
#include "BoardTransforms.h"
#include "Zombie.h"
#include "SkyCannonUI.h"
#include "UIWidget.h"
#include "ReviveUI.h"
#include "StartGameButton.h"
#include "WaveGenerator.h"
#include "HardLevelModule.h"
#include "LevelDefinition.h"
#include "FadeOutOutro.h"
#include "Outros.h"
#include "UIHelper.h"
#include "Utils.h"
#include "Effect_PopAnim.h"
#include "PopAnimRig.h"
#include "Effect_BouncingArrow.h"
#include "SunDropperModule.h"
#include "Wave.h"
#include "CrazyNPCManager.h"
#include "ZombieType.h"
#include "CannonRocket.h"
#include "Cheats.h"
#include "AudioMgr.h"

#include "ReflectionBuilder.h"

static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_TIANKONG("IMAGE_BACKGROUNDS_SKYCITY_TIANKONG");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_SHIELD_1("IMAGE_BACKGROUNDS_SKYCITY_SHIELD_1");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_SHIELD_2("IMAGE_BACKGROUNDS_SKYCITY_SHIELD_2");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_SHIELD_3("IMAGE_BACKGROUNDS_SKYCITY_SHIELD_3");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_SHIELD_4("IMAGE_BACKGROUNDS_SKYCITY_SHIELD_4");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_FIRE1_BG("IMAGE_BACKGROUNDS_SKYCITY_FIRE1_BG");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_FIRE2_BG("IMAGE_BACKGROUNDS_SKYCITY_FIRE2_BG");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_FIRE3_BG("IMAGE_BACKGROUNDS_SKYCITY_FIRE3_BG");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_ENGINE("IMAGE_BACKGROUNDS_SKYCITY_ENGINE");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_TEXTURE2("IMAGE_BACKGROUNDS_SKYCITY_TEXTURE2");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_YUN1("IMAGE_BACKGROUNDS_SKYCITY_YUN1");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_YUN2("IMAGE_BACKGROUNDS_SKYCITY_YUN2");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_SKYCITY_YUN3("IMAGE_BACKGROUNDS_SKYCITY_YUN3");

static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPLEFT("IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPLEFT");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_TOP("IMAGE_UI_POWERUPS_SHOCK_BORDER_TOP");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPRIGHT("IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPRIGHT");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_LEFT("IMAGE_UI_POWERUPS_SHOCK_BORDER_LEFT");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_RIGHT("IMAGE_UI_POWERUPS_SHOCK_BORDER_RIGHT");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMLEFT("IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMLEFT");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_BOTTOM("IMAGE_UI_POWERUPS_SHOCK_BORDER_BOTTOM");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMRIGHT("IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMRIGHT");

static CachedResourcePtr<Sexy::Image> IMAGE_DOWNARROW("IMAGE_DOWNARROW");

RT_CLASS_IMPLEMENT(SkyCityStage);
void SkyCityStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CloudImageInfo);
		REFLECTION_CLASSBUILDER_FIELD(float, PosX);
		REFLECTION_CLASSBUILDER_FIELD(float, PosY);
		REFLECTION_CLASSBUILDER_FIELD(int, Type);
		REFLECTION_CLASSBUILDER_FIELD(float, Scale);
		REFLECTION_CLASSBUILDER_FIELD(float, Width);
	REFLECTION_CLASSBUILDER_END(CloudImageInfo);

	REFLECTION_CLASSBUILDER_BEGIN(ShakeInDamagePercent);
		REFLECTION_CLASSBUILDER_FIELD(bool, Shaked);
		REFLECTION_CLASSBUILDER_FIELD(float, Percent);
	REFLECTION_CLASSBUILDER_END(ShakeInDamagePercent);

	REFLECTION_CLASSBUILDER_BEGIN(SkyCityStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_ignoreRevive);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_playerLost);
		REFLECTION_CLASSBUILDER_FIELD(int, m_indexProjectile);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_IsCannonIntro);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_IsBoardIntro);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isAutoFire);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_canAutoFire);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeAutoFire);
		REFLECTION_CLASSBUILDER_FIELD(float, m_airShipHealth);
		REFLECTION_CLASSBUILDER_FIELD(float, m_airShipHealthMax);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_thunderActive);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_cannonActive);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isGamestart);
		REFLECTION_CLASSBUILDER_FIELD(int, m_offset_x);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_cannonLevel);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_boardLevel);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_cannonPosition);
		REFLECTION_CLASSBUILDER_FIELD(float, m_cannonScale);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<CloudImageInfo>, m_CloudInfos);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ShakeInDamagePercent>, m_ShakeInfos);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_cannonEffect);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_airscrewEffect1);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_airscrewEffect2);
		REFLECTION_CLASSBUILDER_FIELD(Color, m_effect1Color);
		REFLECTION_CLASSBUILDER_FIELD(Color, m_effect2Color);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_touchPos);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_StateCannonIntro);
		REFLECTION_CLASSBUILDER_FIELD(float, m_hardScale);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(std::vector<RtWeakPtr<RtObject> >, m_bouncingArrows);
	REFLECTION_CLASSBUILDER_END(SkyCityStage);
}

RT_CLASS_IMPLEMENT(SkyCityStageProperties);
void SkyCityStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SkyCityStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, MaxAirShipHealth);
		REFLECTION_CLASSBUILDER_FIELD(bool, HasGridItemAirShip);
		REFLECTION_CLASSBUILDER_FIELD(bool, HasCannon);
		REFLECTION_CLASSBUILDER_FIELD(float, AutoCannonDamage1);
		REFLECTION_CLASSBUILDER_FIELD(float, AutoCannonDamage2);
		REFLECTION_CLASSBUILDER_FIELD(float, AutoCannonDamage3);
		REFLECTION_CLASSBUILDER_FIELD(float, SkillCannonDamage2);
		REFLECTION_CLASSBUILDER_FIELD(float, SkillCannonDamage3);
		REFLECTION_CLASSBUILDER_FIELD(float, AutoFireInterval);
		REFLECTION_CLASSBUILDER_FIELD(float, SkillFireInterval);
	REFLECTION_CLASSBUILDER_END(SkyCityStageProperties);
}


void SkyCityStage::AddResourceRequirements(std::set<std::string>& io_resGroupNames)
{
	StageModule::AddResourceRequirements(io_resGroupNames);
	io_resGroupNames.insert("skycity_cannon");
	io_resGroupNames.insert("thunder");
	io_resGroupNames.insert("PlantCoconutCannonAudio");
	io_resGroupNames.insert("PlantPotatomineAudio");
	io_resGroupNames.insert("PlantCherryBombAudio");
}


void SkyCityStage::initializeModule()
{
	StageModule::initializeModule();
}


void SkyCityStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &SkyCityStage::addBackgroundToRenderQueue));
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &SkyCityStage::onUpdate));
	getManager()->RegisterOnGameplayStarted(Sexy::MakeDelegate(*this, &SkyCityStage::onGameplayStarted));
	gLawnApp->m_board->RegisterTouchGameplayObject(Sexy::MakeDelegate(*this, &SkyCityStage::handleTouch), 4, BoardEntityPtr(), Sexy::MakeDelegate(*this, &SkyCityStage::cancelTouch));
	gMessageRouter->Subscribe(Message::SkyCannonPressed, Sexy::MakeDelegate(*this, &SkyCityStage::onSkyCannonPressed));
	gMessageRouter->Subscribe(Message::ThunderStart, Sexy::MakeDelegate(*this, &SkyCityStage::onThunderStart));
	gMessageRouter->Subscribe(Message::ThunderEnd, Sexy::MakeDelegate(*this, &SkyCityStage::onThunderEnd));
	gMessageRouter->Subscribe(Message::AirshipTakeDamage, Sexy::MakeDelegate(*this, &SkyCityStage::onAirshipTakeDamage));
	gMessageRouter->Subscribe(Message::ProgressMeterSetFlagCount, Sexy::MakeDelegate(*this, &SkyCityStage::onProgressMeterSetFlagCount));
	gMessageRouter->Subscribe(Message::ReviveSucceed, Sexy::MakeDelegate(*this, &SkyCityStage::onReviveSucceed));
	gMessageRouter->Subscribe(Message::ReviveClose, Sexy::MakeDelegate(*this, &SkyCityStage::onReviveClose));
	gMessageRouter->Subscribe(Message::StartGameButtonPressed, Sexy::MakeDelegate(*this, &SkyCityStage::onStartGameButtonPressed));
}


void SkyCityStage::onLevelLoaded()
{
	StageModule::onLevelLoaded();
	PlayerInfo* player = ProfileMgr::GetInstance().GetCurrentProfile();
	if (player)
	{
		if (CheatManager::GetInstancePtr() && CheatManager::GetInstancePtr()->GetToggleValue("AutoTestAllLevel"))
		{
			player->UnlockGameFeature(FEATURE_CANNON_INTRO);
		}
		if (!player->GameFeatureIsUnlocked(FEATURE_CANNON_INTRO) && !gLawnApp->IsInModule(Module_Pooyan | Module_Fishing | Module_Besiege))
		{
			if (player->GetReconstructionLevel("skycity", ReconstructionType_Cannon) > 0)
			{
				m_canAutoFire = false;
				m_IsCannonIntro = true;
				gLawnApp->m_board->m_bCanBuyPresent = false;
			}
		}
	}
	const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
	if (props)
	{
		if (props->HasGridItemAirShip)
		{
			Board* board = gLawnApp->m_board;
			for (int i = 0; i < BoardConstants::NUMBER_OF_ROWS(); i++)
			{
				board->AddGridItem("airship", 2, i, 1);
			}
		}
		if (props->HasCannon && !gLawnApp->IsInModule(Module_Besiege))
		{
			AirshipProgressMeter* meter = UIWidget::CreateWidget(RtName(L"UIAirshipProgress"), true)->Cast<AirshipProgressMeter>();
			if (meter)
			{
				if (m_boardLevel > 0)
				{
					meter->SetShield(true);
				}
				else
				{
					meter->SetShield(false);
				}
			}
			SetCannonLevel(m_cannonLevel);

			Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
			effect->CreatePopAnimRig(GetPAMByName("POPANIM_CANNON_ANIM_SKYCITY_1"), NULL);
			effect->SetCentered(true);
			effect->SetBoardSpaceOrigin(SexyVector3(INV_S(m_cannonPosition.x) + 355.0f, INV_S(m_cannonPosition.y) + 110.0f, 0), -1);
			effect->SetRenderLayerOverride(99999);
			effect->PlayLoopingAnimation("idle");
			effect->SetScale(m_cannonScale);
			effect->SetManuallyDrawn(true);
			m_effect1Color = effect->GetPopAnimRig()->GetPAMColor();
			m_airscrewEffect1 = effect->GetPtr();

			effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
			effect->CreatePopAnimRig(GetPAMByName("POPANIM_CANNON_ANIM_SKYCITY_2"), NULL);
			effect->SetCentered(true);
			effect->SetBoardSpaceOrigin(SexyVector3(INV_S(m_cannonPosition.x) + 330.0f, INV_S(m_cannonPosition.y) + 620.0f, 0), -1);
			effect->SetRenderLayerOverride(99999);
			effect->PlayLoopingAnimation("idle");
			effect->SetScale(m_cannonScale);
			effect->SetManuallyDrawn(true);
			m_effect2Color = effect->GetPopAnimRig()->GetPAMColor();
			m_airscrewEffect2 = effect->GetPtr();
		}
	}
	{
		CloudImageInfo info;
		info.PosX = S(200);
		info.PosY = S(150);
		info.Scale = RandRangeFloat(0.6f, 1.2f);
		info.Step = RandRangeFloat(0.1f, 0.4f) + 1.2f;
		info.SetType(0);
		m_CloudInfos.push_back(info);
	}
	{
		CloudImageInfo info;
		info.PosX = S(500);
		info.PosY = S(250);
		info.Scale = RandRangeFloat(0.6f, 1.2f);
		info.Step = RandRangeFloat(0.8f, 1.2f) + 1.2f;
		info.SetType(1);
		m_CloudInfos.push_back(info);
	}
	{
		CloudImageInfo info;
		info.PosX = S(700);
		info.PosY = S(350);
		info.Scale = RandRangeFloat(0.6f, 1.2f);
		info.Step = RandRangeFloat(0.8f, 1.2f) + 1.2f;
		info.SetType(2);
		m_CloudInfos.push_back(info);
	}
	{
		CloudImageInfo info;
		info.PosX = S(1000);
		info.PosY = S(250);
		info.Scale = RandRangeFloat(0.6f, 1.2f);
		info.Step = RandRangeFloat(0.2f, 0.4f) + 1.2f;
		info.SetType(1);
		m_CloudInfos.push_back(info);
	}
	{
		CloudImageInfo info;
		info.PosX = S(1200);
		info.PosY = S(450);
		info.Scale = RandRangeFloat(0.6f, 1.2f);
		info.Step = RandRangeFloat(1.4f, 1.8f) + 1.2f;
		info.SetType(2);
		m_CloudInfos.push_back(info);
	}
	{
		CloudImageInfo info;
		info.PosX = S(1450);
		info.PosY = S(350);
		info.Scale = RandRangeFloat(0.6f, 1.2f);
		info.Step = RandRangeFloat(0.8f, 1.2f) + 1.2f;
		info.SetType(0);
		m_CloudInfos.push_back(info);
	}
	resetShakeInfos();
	if (!gLawnApp->IsInModule(Module_Besiege))
	{
		float x = -100.0f;
		float width = 1000.0f;
		if (getProps<SkyCityStageProperties>()->HasGridItemAirShip)
		{
			x = BoardTransforms::GridToBoardSpaceXUnbounded(GetShipWidth());
			width = 800.0f;
		}
		BoardRegionSky* region = gLawnApp->m_board->AddRegion<BoardRegionSky>();
		region->SetRegionFromBoardCoordinates(Sexy::FRect(x, 0, width, 600.0f));
	}
}


void SkyCityStage::SetCannonPosition(const SexyVector2& pos)
{
	m_cannonPosition = pos;
}


void SkyCityStage::SetCannonScale(float fScale)
{
	m_cannonScale = fScale;
}


int SkyCityStage::GetShipWidth()
{
	return 3;
}


bool SkyCityStage::IsHaveGridItemAirShip() const
{
	const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
	return props ? props->HasGridItemAirShip : false;
}


void SkyCityStage::onStartGameButtonPressed()
{
	m_isGamestart = true;
}


void SkyCityStage::onReviveClose()
{
	m_ignoreRevive = true;
}


void SkyCityStage::onThunderStart()
{
	m_thunderActive = true;
}


void SkyCityStage::onThunderEnd()
{
	m_thunderActive = false;
}


void SkyCityStage::cancelTouch()
{
	m_touchIdent = 0;
}


void SkyCityStage::onCannonIntroNarrationFinished()
{
	clearBouncingArrows();
	m_StateCannonIntro = CannonIntroState_UISkyCannonArrow;
	addUISkyCannonArrow();
}


void SkyCityStage::onReviveSucceed()
{
	m_airShipHealth = m_airShipHealthMax;
	if (m_airShipHealth >= 0.0f)
	{
		gMessageRouter->Post(&Message::AirshipSetPercentage, 100.0f);
	}
	resetShakeInfos();
}


SkyCityStageProperties::SkyCityStageProperties()
{
	MaxAirShipHealth = 100.0f;
	HasGridItemAirShip = true;
	HasCannon = true;
	AutoCannonDamage1 = 100.0f;
	AutoCannonDamage2 = 100.0f;
	AutoCannonDamage3 = 100.0f;
	SkillCannonDamage2 = 100.0f;
	SkillCannonDamage3 = 100.0f;
	AutoFireInterval = 30.0f;
	SkillFireInterval = 30.0f;
}


void SkyCityStage::clearBouncingArrows()
{
	for (int i = 0; i < m_bouncingArrows.size(); i++)
	{
		m_bouncingArrows[i]->Destroy();
	}
	m_bouncingArrows.clear();
}


void SkyCityStage::renderBesiegeBG(Graphics* i_g)
{
	TodDrawImageCenterScaledF(i_g, IMAGE_BACKGROUNDS_SKYCITY_TEXTURE2, S(250), S(103), m_cannonScale, m_cannonScale);
}


void SkyCityStage::resetShakeInfos()
{
	m_ShakeInfos.clear();
	m_ShakeInfos.push_back(ShakeInDamagePercent(0.8f, false));
	m_ShakeInfos.push_back(ShakeInDamagePercent(0.6f, false));
	m_ShakeInfos.push_back(ShakeInDamagePercent(0.4f, false));
	m_ShakeInfos.push_back(ShakeInDamagePercent(0.2f, false));
}


SkyCityStage::~SkyCityStage()
{
	if (m_cannonEffect)
	{
		m_cannonEffect->Destroy();
		m_cannonEffect.ClearId();
	}
	if (m_airscrewEffect1)
	{
		m_airscrewEffect1->Destroy();
		m_airscrewEffect1.ClearId();
	}
	if (m_airscrewEffect2)
	{
		m_airscrewEffect2->Destroy();
		m_airscrewEffect2.ClearId();
	}
}


SkyCityStage::SkyCityStage() :
	m_cannonPosition(0.0f, 0.0f),
	m_cannonScale(1.0f)
{
	m_offset_x = 0;
	m_indexProjectile = 0;
	m_boardLevel = BoardType_Level1;
	m_cannonLevel = CannonType_Level1;
	m_hardScale = 1.0f;

	PlayerInfo* player = ProfileMgr::GetInstance().GetCurrentProfile();
	if (player)
	{
		m_cannonLevel = (eCannonLevelType)player->GetReconstructionLevel("skycity", ReconstructionType_Cannon);
		m_boardLevel = (eBoardLevelType)player->GetReconstructionLevel("skycity", ReconstructionType_Board);
	}

	float health = m_boardLevel > 0 ? 8000.0f : 6000.0f;
	m_cannonActive = false;
	m_thunderActive = false;
	m_isAutoFire = false;
	m_IsCannonIntro = false;
	m_IsBoardIntro = false;
	m_playerLost = false;
	m_ignoreRevive = false;
	m_StateCannonIntro = CannonIntroState_Init;
	m_touchIdent = 0;
	m_airShipHealthMax = health;
	m_airShipHealth = health;
	m_timeAutoFire = PVZ_EOT();
	m_isGamestart = false;
	m_canAutoFire = true;
}



Effect_BouncingArrow* SkyCityStage::addBouncingArrow(const Sexy::SexyVector2& i_screenLocation)
{
	Effect_BouncingArrow* arrow = gLawnApp->m_board->AddEffect<Effect_BouncingArrow>();
	arrow->SetArrowImage(IMAGE_DOWNARROW);
	arrow->SetBounceHeightsBoardSpace(20.0f, 40.0f);
	arrow->SetVisibility(true);
	arrow->SetScreenSpaceOrigin(i_screenLocation, 1000000);
	m_bouncingArrows.push_back(arrow->GetPtr());
	return arrow;
}


void SkyCityStage::onSkyCannonPressed()
{
	m_cannonActive = !m_cannonActive;
	if (m_IsCannonIntro && m_cannonActive && m_StateCannonIntro == CannonIntroState_UISkyCannonArrow)
	{
		clearBouncingArrows();
		m_StateCannonIntro = CannonIntroState_ZombieArrow;
		addBouncingArrow(SexyVector2(S(BoardTransforms::GridToBoardSpaceX(6) - BoardConstants::GRIDSQUARE_WIDTH() / 2),
		                             S(BoardTransforms::GridToBoardSpaceY(2) - BoardConstants::GRIDSQUARE_HEIGHT() / 2)));
	}
}


void SkyCityStage::onCannonFireAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animParam)
{
	if (m_isAutoFire)
	{
		return;
	}
	if (m_IsCannonIntro)
	{
		clearBouncingArrows();
		WaveManager* waveManager = gLawnApp->m_board->GetWaveManager();
		if (waveManager)
		{
			waveManager->SetPause(false);
		}
		SunDropperModule* sunDropper = gLawnApp->m_board->GetLevelModuleByClass<SunDropperModule>();
		if (sunDropper)
		{
			sunDropper->SetPaused(false);
		}
		m_IsCannonIntro = false;
		m_StateCannonIntro = CannonIntroState_Done;
		PlayerInfo* player = ProfileMgr::GetInstance().GetCurrentProfile();
		if (player)
		{
			player->UnlockGameFeature(FEATURE_CANNON_INTRO);
		}
		if (!gLawnApp->GetNarrationSystem()->IsNarrationActive())
		{
			gLawnApp->GetNarrationSystem()->StartNarrativeID("CANNON_USE_END_INTRO", Sexy::MakeDelegate(*this, &SkyCityStage::onCannonEndNarrationFinished));
		}
	}
	switch (m_cannonLevel)
	{
	case CannonType_Level1:
		{
			if (i_animCommand == "collect")
			{
				if (m_indexProjectile > 3)
				{
					m_canAutoFire = true;
				}
				ProjectilePropertySheetPtr props = PVZDB::GetInstance().FindObjectByAlias<ProjectilePropertySheet>(PVZDB::TABLE_PROJECTILETYPES, RtName(StringToSexyString("CannonFireDefault")));
				if (props.IsValid() && m_cannonEffect.IsValid())
				{
					Sexy::Point start;
					if (i_animLabel == "attack01_2")
					{
						start = Sexy::Point(200, 160);
					}
					else if (i_animLabel == "attack02_2")
					{
						start = Sexy::Point(240, 160);
					}
					else if (i_animLabel == "attack03_2")
					{
						start = Sexy::Point(280, 90);
					}
					Sexy::Point target(m_touchPos);
					double angle = atan2((double)(target.mY - start.mY), (double)(target.mX - start.mX));
					Projectile* projectile = gLawnApp->m_board->AddProjectile((float)start.mX, (float)start.mY, 0.0f, props, NULL, 0);
					projectile->JoinTeam(TEAM_PLANTS);
					projectile->SetRenderOrder(RENDER_LAYER_ABOVE_UI);
					projectile->SetRotation(-(float)angle);
					SexyVector3 speed(300.0f, 300.0f, 0.0f);
					float rotation = projectile->GetRotation();
					float cosR = cosf(rotation);
					float len = speed.Magnitude();
					projectile->SetVelocity(SexyVector3(len * cosR, -(sinf(rotation)) * len, 0.0f));
					m_indexProjectile++;
					AudioMgr::GetInstancePtr()->SendEvent("Play_CherryBomb");
				}
			}
		}
		break;
	case CannonType_Level2:
		if (i_animCommand == "collect")
		{
			m_canAutoFire = true;
			SexyVector2 start;
			float step = 100.0f;
			if (i_animLabel == "attack01_2")
			{
				start = SexyVector2(196.0f, 190.0f);
			}
			else if (i_animLabel == "attack02_2")
			{
				start = SexyVector2(260.0f, 120.0f);
			}
			else if (i_animLabel == "attack03_2")
			{
				start = SexyVector2(320.0f, 100.0f);
			}
			float slope = ((float)m_touchPos.mY - start.y) / ((float)m_touchPos.mX - start.x);
			double length;
			if (slope <= 0.0f)
			{
				slope = 1.0f;
				length = 1.4142135623730951;
			}
			else
			{
				length = sqrt(slope * slope + 1.0f);
			}
			const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
			for (int i = 1; i < 8; i++)
			{
				float dist = i * step * (1.0 / length);
				CannonRocket* rocket = GameObject::Create<CannonRocket>(PVZDB::TABLE_BOARDENTITIES);
				rocket->InitializeRocketController(Sexy::Point((int)(dist + start.x), (int)(start.y + dist * slope)), props->SkillCannonDamage2);
				rocket->StartCrosshairEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "missile_lock_reticle");
				rocket->StartRocketEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "", 0.2f + i * 0.2, 500.0f);
			}
		}
		break;
	}
}


void SkyCityStage::onCannonEndNarrationFinished()
{
	for (Sexy::RtDbTable::Iterator it =
	         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		ZombiePtr zombie = *it;
		if (zombie && !zombie->IsDying() && !zombie->IsBleedingOut() && zombie->IsOnScreen())
		{
			zombie->SetWalkingState();
		}
	}
}


bool SkyCityStage::FireCannon(const Sexy::Point& i_boardSpace, bool checkBoard)
{
	m_touchPos = i_boardSpace;
	if (checkBoard && (i_boardSpace.mX < 200 || i_boardSpace.mX > 1000 || i_boardSpace.mY < 160 || i_boardSpace.mY > 760))
	{
		return false;
	}
	m_isAutoFire = false;
	float angle = atan2((double)(i_boardSpace.mX - 195), (double)(i_boardSpace.mY - 155));
	std::string anim = "attack01";
	if (angle >= 0.5235988f || angle < 0.0f) { if (angle >= 1.0471976f || angle < 0.5235988f) anim = "attack03_2"; else anim = "attack02_2"; } else anim = "attack01_2";
	Sexy::Rect rect(200, 160, BoardConstants::GRIDSQUARE_WIDTH() * 1.2, BoardConstants::GRIDSQUARE_HEIGHT());
	if (rect.Contains(i_boardSpace.mX, i_boardSpace.mY))
	{
		anim = "attack02_2";
		m_touchPos = BoardTransforms::GridToBoardSpaceUnbounded(Sexy::Point(2, 2));
	}
	if (m_cannonEffect)
	{
		AnimationSequence sequence;
		if (m_cannonLevel == CannonType_Level3)
		{
			sequence.AddSingleAnimation("attack");
		}
		else
		{
			sequence.AddSingleAnimation(anim);
		}
		sequence.AddLoopingAnimation("idle_2");
		m_cannonEffect->PlayAnimationSequence(sequence);
	}
	switch (m_cannonLevel)
	{
	case CannonType_Level2:
		m_canAutoFire = false;
		break;
	case CannonType_Level3:
	{
		Sexy::Point offsets[7] = {
			Sexy::Point(0, 0), Sexy::Point(-60, 0), Sexy::Point(60, 0), Sexy::Point(30, -30),
			Sexy::Point(-30, 30), Sexy::Point(-30, -30), Sexy::Point(30, 30)
		};
		const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
		for (int i = 0; i < 7; i++)
		{
			CannonRocket* rocket = GameObject::Create<CannonRocket>(PVZDB::TABLE_BOARDENTITIES);
			rocket->InitializeRocketController(Sexy::Point(i_boardSpace + offsets[i]), props->SkillCannonDamage3);
			rocket->StartCrosshairEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "missile_lock_reticle");
			rocket->StartRocketEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "", 1.2f + i * 0.2, 500.0f);
		}
		break;
	}
	case CannonType_Level1:
		m_canAutoFire = false;
		m_indexProjectile = 0;
		break;
	}
	return true;
}


void SkyCityStage::autoFire()
{
	ZombiePtr target = NULL;
	float minX = 800.0f;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		ZombiePtr zombie = *it;
		if (!zombie->IsDying() && !zombie->IsInvisible() && zombie->IsOnOpposingTeam(TEAM_PLANTS))
		{
			float x = zombie->GetPosition().x;
			if (!(x > 800.0f) && x < minX)
			{
				minX = x;
				target = zombie->GetPtr();
			}
		}
	}
	if (target.IsValid())
	{
	m_isAutoFire = true;
	SexyVector3 targetPos;
	targetPos = target->CalcProjectileTargetLocation(0.6f);
	float angle = atan2((double)targetPos.x, (double)targetPos.y);
	std::string anim = "attack01";
	if (angle >= 0.5235988f || angle < 0.0f) { if (angle >= 1.0471976f || angle < 0.5235988f) anim = "attack03"; else anim = "attack02"; } else anim = "attack01";
	if (m_cannonEffect)
	{
		AnimationSequence sequence;
		if (m_cannonLevel == CannonType_Level3)
		{
			sequence.AddSingleAnimation("attack");
		}
		else
		{
			sequence.AddSingleAnimation(anim);
		}
		sequence.AddLoopingAnimation("idle_2");
		m_cannonEffect->PlayAnimationSequence(sequence);
	}
	const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
	switch (m_cannonLevel)
	{
	case CannonType_Level2:
	{
		CannonRocket* rocket = GameObject::Create<CannonRocket>(PVZDB::TABLE_BOARDENTITIES);
		rocket->InitializeRocketController(Sexy::Point((int)targetPos.x, (int)targetPos.y), props->AutoCannonDamage2);
		rocket->StartCrosshairEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "missile_lock_reticle");
		rocket->StartRocketEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "", 1.2f, 500.0f);
		rocket = GameObject::Create<CannonRocket>(PVZDB::TABLE_BOARDENTITIES);
		rocket->InitializeRocketController(Sexy::Point((int)targetPos.x, (int)targetPos.y), props->AutoCannonDamage2);
		rocket->StartCrosshairEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "missile_lock_reticle");
		rocket->StartRocketEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "", 1.6f, 500.0f);
	}
		break;
	case CannonType_Level1:
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_CherryBomb");
		SexyVector3 delta = target->CalcPositionInTime(0.6f) - target->GetPosition();
		CannonRocket* rocket = GameObject::Create<CannonRocket>(PVZDB::TABLE_BOARDENTITIES);
		rocket->InitializeRocketController(Sexy::Point((int)(delta.x + targetPos.x), (int)targetPos.y), 0.0f);
		rocket->StartCrosshairEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "missile_lock_reticle");
		rocket->StartRocketEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT1", "", 1.0f, 500.0f);
		ProjectilePropertySheetPtr projProps = PVZDB::GetInstance().FindObjectByAlias<ProjectilePropertySheet>(PVZDB::TABLE_PROJECTILETYPES, RtName(StringToSexyString("AutoCannonFireDefault")));
		if (projProps.IsValid() && m_cannonEffect.IsValid())
		{
			Sexy::Point start;
			if (anim == "attack01")
			{
				start = Sexy::Point(200, 160);
			}
			else if (anim == "attack02")
			{
				start = Sexy::Point(240, 160);
			}
			else if (anim == "attack03")
			{
				start = Sexy::Point(280, 90);
			}
			double fireAngle = atan2((double)(targetPos.y - start.mY), (double)(targetPos.x - start.mX));
			Projectile* projectile = gLawnApp->m_board->AddProjectile((float)start.mX, (float)start.mY, 0.0f, projProps, NULL, 0);
			projectile->JoinTeam(TEAM_PLANTS);
			projectile->SetRenderOrder(RENDER_LAYER_ABOVE_UI);
			projectile->SetRotation(-(float)fireAngle);
			SexyVector3 speed(300.0f, 300.0f, 0.0f);
			float rotation = projectile->GetRotation();
			float cosR = cosf(rotation);
			float len = speed.Magnitude();
			projectile->SetVelocity(SexyVector3(len * cosR, -(sinf(rotation)) * len, 0.0f));
		}
	}
		break;
	case CannonType_Level3:
	{
		for (int i = 0; i < 6; i++)
		{
			CannonRocket* rocket = GameObject::Create<CannonRocket>(PVZDB::TABLE_BOARDENTITIES);
			rocket->InitializeRocketController(Sexy::Point((int)targetPos.x, (int)targetPos.y), props->AutoCannonDamage3);
			rocket->StartCrosshairEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT3", "missile_lock_reticle");
			rocket->StartRocketEffect("POPANIM_CANNON_ANIM_SKYCITY_FIRE_EFFECT3", "missile", 1.5 + i * 0.1, 500.0f);
		}
	}
		break;
	}
	}
}


bool SkyCityStage::handleTouch(const Sexy::Touch& i_touch)
{
	bool active = m_cannonActive;
	if (active)
	{
		switch (i_touch.phase)
		{
		case Sexy::TOUCH_BEGAN:
			m_touchIdent = i_touch.ident;
			if (FireCannon(Sexy::Point(INV_S(i_touch.location.mX), INV_S(i_touch.location.mY)), true))
			{
				gMessageRouter->Post(&Message::SkyCannonUsed);
			}
			else
			{
				gMessageRouter->Post(&Message::SkyCannonTouchOutside);
				if (m_IsCannonIntro && m_StateCannonIntro == CannonIntroState_ZombieArrow)
				{
					clearBouncingArrows();
					m_StateCannonIntro = CannonIntroState_UISkyCannonArrow;
					addUISkyCannonArrow();
				}
			}
			m_cannonActive = false;
			break;
		case Sexy::TOUCH_ENDED:
			cancelTouch();
			break;
		case Sexy::TOUCH_CANCELED:
			cancelTouch();
			break;
		}
	}
	return active;
}


void SkyCityStage::onUpdate()
{
	m_offset_x -= 2.0f;
	if (m_offset_x <= -(double)IMAGE_BACKGROUNDS_SKYCITY_TIANKONG->mWidth)
	{
		m_offset_x = 0;
	}

	for (std::vector<CloudImageInfo>::iterator it = m_CloudInfos.begin(), end = m_CloudInfos.end(); it != end; ++it)
	{
		(*it).Update();
	}

	if (m_cannonEffect)
	{
		if (PVZ_T() > m_timeAutoFire)
		{
			if (m_canAutoFire && m_isGamestart)
			{
				autoFire();
			}
			const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
			m_timeAutoFire = PVZ_T() + props->AutoFireInterval;
		}
	}
}


void SkyCityStage::addUISkyCannonArrow()
{
	UIWidget* widget = UIWidget::GetWidgetBySheetName("UISkyCannon");
	if (widget)
	{
		Rect drawRect = widget->GetDrawRect();
		SexyVector2 offset(45.0f, -6.0f);
		Sexy::Point screenPos(UI_S(offset.x) + drawRect.mX, UI_S(offset.y) + drawRect.mY);
		Sexy::Point boardOffset = gLawnApp->m_board->GetBoardBaseOffset();
		Sexy::Point boardPos(screenPos - boardOffset);
		gLawnApp->m_board->TranslateScreenPositionToBoardPosition(boardPos);
		addBouncingArrow(SexyVector2(boardPos.mX, boardPos.mY));
	}
}


void SkyCityStage::onRenderAirscrew(Sexy::Graphics* i_g)
{
	if (m_airscrewEffect1)
	{
		if (InDamageFlash())
			m_airscrewEffect1->SetColor(GetDamageFlashColor());
		else
			m_airscrewEffect1->SetColor(m_effect1Color);
		m_airscrewEffect1->Draw(i_g);
	}
	if (m_airscrewEffect2)
	{
		if (InDamageFlash())
			m_airscrewEffect2->SetColor(GetDamageFlashColor());
		else
			m_airscrewEffect2->SetColor(m_effect2Color);
		m_airscrewEffect2->Draw(i_g);
	}
}


void SkyCityStage::renderRunBackground(Graphics* i_g)
{
	int offsetX = 0;
	if (!IsHaveGridItemAirShip())
	{
		offsetX = S(-100);
	}
	i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_TIANKONG, offsetX + m_offset_x, 0);
	i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_TIANKONG, offsetX + m_offset_x + IMAGE_BACKGROUNDS_SKYCITY_TIANKONG->mWidth, 0);
	i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_TIANKONG, offsetX + m_offset_x + IMAGE_BACKGROUNDS_SKYCITY_TIANKONG->mWidth * 2, 0);

	if (m_thunderActive)
	{
		GraphicsAutoState autoState(i_g);
		i_g->SetColor(Color(0, 0, 0, 76));
		i_g->mTransY = 0;
		i_g->mTransX = 0;
		i_g->FillRect(0, 0, gLawnApp->mWidth, gLawnApp->mHeight);
	}
	if (m_thunderActive)
	{
		i_g->SetColor(Color(54, 49, 41, 153));
		i_g->SetColorizeImages(true);
	}

	for (std::vector<CloudImageInfo>::iterator it = m_CloudInfos.begin(), end = m_CloudInfos.end(); it != end; ++it)
	{
		CloudImageInfo& cloud = *it;
		if (cloud.PosX > S(1300))
			continue;
		switch (cloud.Type)
		{
		case 1:
			i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_YUN2, (int)cloud.PosX, (int)cloud.PosY, (int)(IMAGE_BACKGROUNDS_SKYCITY_YUN2->mWidth * cloud.Scale), (int)(IMAGE_BACKGROUNDS_SKYCITY_YUN2->mHeight * cloud.Scale));
			break;
		case 2:
			i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_YUN3, (int)cloud.PosX, (int)cloud.PosY, (int)(IMAGE_BACKGROUNDS_SKYCITY_YUN3->mWidth * cloud.Scale), (int)(IMAGE_BACKGROUNDS_SKYCITY_YUN3->mHeight * cloud.Scale));
			break;
		case 0:
			i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_YUN1, (int)cloud.PosX, (int)cloud.PosY, (int)(IMAGE_BACKGROUNDS_SKYCITY_YUN1->mWidth * cloud.Scale), (int)(IMAGE_BACKGROUNDS_SKYCITY_YUN1->mHeight * cloud.Scale));
			break;
		}
	}

	if (m_thunderActive)
	{
		i_g->SetColorizeImages(false);
	}

	const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
	if (props && props->HasCannon && props->HasGridItemAirShip && !gLawnApp->IsInModule(Module_Besiege))
	{
		TodDrawImageCenterScaledF(i_g, IMAGE_BACKGROUNDS_SKYCITY_ENGINE, S(m_cannonPosition.x - 108.0f), S(m_cannonPosition.y - 2.0f), m_cannonScale, m_cannonScale);
		switch (m_cannonLevel)
		{
		case CannonType_Level2:
			TodDrawImageCenterScaledF(i_g, IMAGE_BACKGROUNDS_SKYCITY_FIRE2_BG, S(m_cannonPosition.x - 19.0f), S(m_cannonPosition.y - 42.0f), m_cannonScale, m_cannonScale);
			break;
		case CannonType_Level3:
			TodDrawImageCenterScaledF(i_g, IMAGE_BACKGROUNDS_SKYCITY_FIRE3_BG, S(m_cannonPosition.x - 6.0f), S(m_cannonPosition.y - 8.0f), m_cannonScale, m_cannonScale);
			break;
		case CannonType_Level1:
			TodDrawImageCenterScaledF(i_g, IMAGE_BACKGROUNDS_SKYCITY_FIRE1_BG, S(m_cannonPosition.x - 28.0f), S(m_cannonPosition.y - 45.0f), m_cannonScale, m_cannonScale);
			break;
		}
	}
}


void SkyCityStage::addBackgroundToRenderQueue(RenderQueue* i_queue)
{
	i_queue->Add(RENDER_LAYER_STAGE_BACKGROUND - 2, Sexy::MakeDelegate(*this, &SkyCityStage::renderRunBackground));
	if (m_cannonActive)
	{
		i_queue->Add(RENDER_LAYER_LAWN - 1, Sexy::MakeDelegate(*this, &SkyCityStage::onDrawSelectionOnBoard));
	}
	i_queue->Add(RENDER_LAYER_STAGE_BACKGROUND + 1, Sexy::MakeDelegate(*this, &SkyCityStage::onRenderCannon));
	i_queue->Add(RENDER_LAYER_STAGE_BACKGROUND - 1, Sexy::MakeDelegate(*this, &SkyCityStage::onRenderAirscrew));
	if (gLawnApp->IsInModule(Module_Besiege))
	{
		i_queue->Add(RENDER_LAYER_STAGE_BACKGROUND + 2, Sexy::MakeDelegate(*this, &SkyCityStage::renderBesiegeBG));
	}
}


void SkyCityStage::onGameplayStarted()
{
	if (!gLawnApp->m_board || !gLawnApp->m_board->GetLevelDefinition() || !gLawnApp->m_board->GetLevelDefinition()->IsBossFight)
		m_isGamestart = true;
	else
		m_isGamestart = false;
	PlayerInfo* player = ProfileMgr::GetInstance().GetCurrentProfile();
	HardLevelModule* hardModule = getManager()->GetModuleByClass<HardLevelModule>();
	if (hardModule)
	{
		m_airShipHealthMax = hardModule->GetDifficult() * m_airShipHealthMax;
		m_airShipHealth = m_airShipHealthMax;
		m_hardScale = hardModule->GetDifficult();
	}
	const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
	if (props && props->HasCannon && !gLawnApp->IsInModule(Module_Besiege) && player)
	{
		if (player->GetReconstructionLevel("skycity", ReconstructionType_Cannon) > 0)
		{
			SkyCannonUI* cannonUI = UIWidget::CreateWidget(Sexy::RtName(L"UISkyCannon"), true)->CastChecked<SkyCannonUI>();
			if (cannonUI)
			{
				cannonUI->SetCoolDownTime(props->SkillFireInterval);
			}
			m_timeAutoFire = PVZ_T() + props->AutoFireInterval;
			return;
		}
	}
	SetCanAutoFire(false);
}


void SkyCityStage::onRenderCannon(Sexy::Graphics* i_g)
{
	if (m_cannonEffect)
	{
		m_cannonEffect->Draw(i_g);
	}
	if (InDamageFlash())
	{
		i_g->SetColor(GetDamageFlashColor());
		i_g->SetColorizeImages(true);
	}
	const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
	if (props && props->HasGridItemAirShip && !gLawnApp->IsInModule(Module_Besiege))
	{
		switch (m_boardLevel)
		{
		case BoardType_Level2:
			i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_SHIELD_2, S(BoardConstants::GRIDSQUARE_WIDTH() + 195), S(102));
			break;
		case BoardType_Level3:
			i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_SHIELD_3, S(BoardConstants::GRIDSQUARE_WIDTH() + 195), S(102));
			break;
		case BoardType_Level1:
			if (m_airShipHealth <= m_hardScale * 6000.0f)
				i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_SHIELD_4, S(BoardConstants::GRIDSQUARE_WIDTH() + 195), S(134));
			else
				i_g->DrawImage(IMAGE_BACKGROUNDS_SKYCITY_SHIELD_1, S(BoardConstants::GRIDSQUARE_WIDTH() + 195), S(102));
			break;
		}
	}
	if (InDamageFlash())
	{
		i_g->SetColorizeImages(false);
	}
}


void SkyCityStage::onAirshipTakeDamage(float i_amount)
{
	FlashDamage();
	m_airShipHealth -= i_amount;
	if (!(m_airShipHealth < 0.0f))
	{
		float percent = m_airShipHealth / m_airShipHealthMax;
		for (std::vector<ShakeInDamagePercent>::iterator it = m_ShakeInfos.begin(), end = m_ShakeInfos.end(); it != end; ++it)
		{
			ShakeInDamagePercent& shake = *it;
			if (percent <= shake.Percent && !shake.Shaked)
			{
				gLawnApp->m_board->ShakeBoard(13, 13, 0.0f);
				shake.Shaked = true;
				break;
			}
		}
		gMessageRouter->Post(&Message::AirshipSetPercentage, percent * 100.0f);
	}

	if (m_airShipHealth <= m_airShipHealthMax * 0.2f && !m_ignoreRevive)
	{
		gLawnApp->ShowReviveUI(ReviveMode_AirShipCrash);
	}
	else if (m_airShipHealth <= 0.0f && !m_playerLost)
	{
		if (!gLawnApp->IsInModule(Module_Pooyan | Module_Fishing | Module_Besiege) && gLawnApp->m_board->TryTriggerPlayerLoss(OUTRO_FAILURE_FADE_WITH_MESSAGE))
		{
			m_playerLost = true;
			gLawnApp->m_board->GetOutroModule<FadeOutOutroModule>()->SetMessage(L"[AIRSHIP_CRASH_LOSS]");
		}
	}
}


void SkyCityStage::onDrawSelectionOnBoard(Sexy::Graphics* i_g)
{
	Rect gridRect = gLawnApp->m_board->GetGridBoundingRect();
	gridRect = Rect(S(gridRect.mX), S(gridRect.mY), S(gridRect.mWidth), S(gridRect.mHeight));
	{
		GraphicsAutoState autoState(i_g);
		i_g->SetColorizeImages(true);
		Color selectColor(255, 145, 250, 125);
		if (selectColor.mAlpha > 0)
		{
			selectColor.mAlpha = 255;
		}
		i_g->SetColor(selectColor);
		Draw9Slice(i_g, Rect(gridRect.mX - IMAGE_UI_POWERUPS_SHOCK_BORDER_LEFT->GetWidth(), gridRect.mY - IMAGE_UI_POWERUPS_SHOCK_BORDER_TOP->GetHeight(),
		                     gridRect.mWidth + IMAGE_UI_POWERUPS_SHOCK_BORDER_LEFT->GetWidth() * 2, gridRect.mHeight + IMAGE_UI_POWERUPS_SHOCK_BORDER_TOP->GetHeight() * 2),
		           IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPLEFT, IMAGE_UI_POWERUPS_SHOCK_BORDER_TOP, IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPRIGHT,
		           IMAGE_UI_POWERUPS_SHOCK_BORDER_LEFT, NULL, IMAGE_UI_POWERUPS_SHOCK_BORDER_RIGHT,
		           IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMLEFT, IMAGE_UI_POWERUPS_SHOCK_BORDER_BOTTOM, IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMRIGHT);
	}
	{
		GraphicsAutoState autoState(i_g);
		i_g->SetClipRect(gridRect);
		DrawRadialCooldown(i_g, 1.0f, gridRect.mX + gridRect.mWidth / 2, gridRect.mY + gridRect.mHeight / 2, gridRect.mWidth, Color(0, 0, 0, 0), Color(255, 145, 250, 125));
	}
}


void SkyCityStage::SetCannonLevel(eCannonLevelType i_level)
{
	m_cannonLevel = i_level;
	if (m_cannonEffect)
	{
		m_cannonEffect->Destroy();
		m_cannonEffect.ClearId();
	}
	Effect_PopAnim* effect = NULL;
	switch (m_cannonLevel)
	{
		case CannonType_Level2:
			effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
			effect->CreatePopAnimRig(GetPAMByName("POPANIM_CANNON_ANIM_SKYCITY_FIRE2"), NULL);
			effect->SetBoardSpaceOrigin(SexyVector3(INV_S(m_cannonPosition.x) + 216.0f, INV_S(m_cannonPosition.y) + 72.0f, 0.0f), -1);
			break;
		case CannonType_Level3:
			effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
			effect->CreatePopAnimRig(GetPAMByName("POPANIM_CANNON_ANIM_SKYCITY_FIRE3"), NULL);
			effect->SetBoardSpaceOrigin(SexyVector3(INV_S(m_cannonPosition.x) + 192.0f, INV_S(m_cannonPosition.y) + 58.0f, 0.0f), -1);
			break;
		case CannonType_Level1:
			effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
			effect->CreatePopAnimRig(GetPAMByName("POPANIM_CANNON_ANIM_SKYCITY_FIRE1"), NULL);
			effect->SetBoardSpaceOrigin(SexyVector3(INV_S(m_cannonPosition.x) + 200.0f, INV_S(m_cannonPosition.y) + 100.0f, 0.0f), -1);
			break;
	}
	if (effect)
	{
		effect->SetCentered(true);
		effect->SetRenderLayerOverride(RENDER_LAYER_STAGE_BACKGROUND + 1);
		effect->PlayLoopingAnimation("idle_2", PVZ_EOT());
		effect->SetScale(m_cannonScale);
		effect->SetManuallyDrawn(true);
		effect->GetPopAnimRig()->SetPopAnimCommandDelegate(Sexy::MakeDelegate(*this, &SkyCityStage::onCannonFireAnimCommand));
		const SkyCityStageProperties* props = getProps<SkyCityStageProperties>();
		if (props && props->HasCannon && props->HasGridItemAirShip && !gLawnApp->IsInModule(Module_Besiege))
		{
			effect->GetPopAnimRig()->SetLayerVisibility("bg", false);
		}
		m_cannonEffect = effect->GetPtr();
	}
}


void SkyCityStage::onProgressMeterSetFlagCount(int i_flagCount)
{
	if (m_IsCannonIntro)
	{
		ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("skycity")->EnsureResourceGroupsLoaded();

		ZombiePtr zombie1 = gLawnApp->m_board->AddZombieInRow(ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("skycity"), 2, 0)->GetPtr();
		zombie1->SetPosition(SexyVector3(BoardTransforms::GridToBoardSpaceX(6), BoardTransforms::GridToBoardSpaceY(2), 0));
		zombie1->SetIdleState();

		ZombiePtr zombie2 = gLawnApp->m_board->AddZombieInRow(ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("skycity"), 3, 0)->GetPtr();
		zombie2->SetPosition(SexyVector3(BoardTransforms::GridToBoardSpaceX(5), BoardTransforms::GridToBoardSpaceY(3), 0));
		zombie2->SetIdleState();

		if (!gLawnApp->GetNarrationSystem()->IsNarrationActive())
		{
			WaveManager* waveManager = gLawnApp->m_board->GetWaveManager();
			if (waveManager)
			{
				waveManager->SetPause(true);
			}
			SunDropperModule* sunDropper = gLawnApp->m_board->GetLevelModuleByClass<SunDropperModule>();
			if (sunDropper)
			{
				sunDropper->SetPaused(true);
			}

			addBouncingArrow(SexyVector2(S(BoardTransforms::GridToBoardSpaceX(0) - BoardConstants::GRIDSQUARE_WIDTH() / 2),
			                             S(BoardTransforms::GridToBoardSpaceY(0) - BoardConstants::GRIDSQUARE_HEIGHT())))->PointUp();
			gLawnApp->GetNarrationSystem()->StartNarrativeID("CANNON_USE_INTRO", Sexy::MakeDelegate(*this, &SkyCityStage::onCannonIntroNarrationFinished));
			m_StateCannonIntro = CannonIntroState_Use_Narrative;
		}
	}
}
