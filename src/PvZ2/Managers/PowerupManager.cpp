//
//  PowerupManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupManager.h"
#include "LawnApp.h"
#include "Board.h"
#include "TimeMgr.h"
#include "PacketID.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "UIWidget.h"
#include "PVZDB.h"
#include "PowerupType.h"
#include "PowerupHolderUI.h"
#include "PowerupUI.h"
#include "BoardTransforms.h"
#include "UIHelper.h"
#include "Utils.h"
#include "DangerRoomManager.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "RenderQueue.h"
#include "TGALogMgr.h"
#include "LevelDefinition.h"
#include "DString.h"
#include "RedPacketRewardInfo.h"

/////////////// Statics ///////////////

static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPLEFT, "IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPLEFT")
static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_TOP, "IMAGE_UI_POWERUPS_SHOCK_BORDER_TOP")
static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPRIGHT, "IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_TOPRIGHT")
static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_LEFT, "IMAGE_UI_POWERUPS_SHOCK_BORDER_LEFT")
static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_RIGHT, "IMAGE_UI_POWERUPS_SHOCK_BORDER_RIGHT")
static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMLEFT, "IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMLEFT")
static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_BOTTOM, "IMAGE_UI_POWERUPS_SHOCK_BORDER_BOTTOM")
static WEAKIMAGE(IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMRIGHT, "IMAGE_UI_POWERUPS_SHOCK_BORDER_CORNER_BOTTOMRIGHT")

/////////////// Functions ///////////////

bool PowerupManager::IsBlock()
{
	return mCacheConnectServer > 1;
}

void PowerupManager::onUseGemFinished(bool success)
{
	if (!success)
		CancelActivePowerup();
}

void PowerupManager::Update()
{
	for (int i = 0; i < m_powerups.size(); i++)
		m_powerups[i]->Update();
}

void PowerupManager::RemoveAllPowerups()
{
	while (m_powerups.size() != 0)
		RemovePowerup(m_powerups[0]->GetType()->TypeName);
}

int PowerupManager::GetCurrentPowerCost(BasePowerup* powerup)
{
	return powerup->GetType()->Cost + GetPowerAdditionCost(powerup);
}

void PowerupManager::onDrawActivePowerup(Sexy::Graphics* i_g)
{
	m_activePowerup->Draw(i_g);
}

void PowerupManager::AddDefaultPowerupsForLevel()
{
	std::string set = gLawnApp->m_board->GetLevelPowerupSet();
	if (!set.empty())
		addPowerupSet(set);
}

PowerupManager::~PowerupManager()
{
	if (gTimeMgr->GameIsPause())
		gTimeMgr->PauseGameOnly(false);
	gMessageRouter->Unsubscribe(this);
}

PowerupManager::PowerupManager()
{
	m_ignoreCost = false;
	m_powerupTimes = 0;
	gMessageRouter->Subscribe(&Message::LevelLoadComplete, Sexy::MakeDelegate(*this, &PowerupManager::OnLevelLoadComplete));
	gMessageRouter->Subscribe(&Message::BuyItemFinish, Sexy::MakeDelegate(*this, &PowerupManager::OnBuyItemFinish));
	gMessageRouter->Subscribe(&Message::MsgErrorRequest, Sexy::MakeDelegate(*this, &PowerupManager::onNetworkError));
	mCacheConnectServer = 0;
}

void PowerupManager::OnServerGemCallBack(const bool& i_Success)
{
}

void PowerupManager::OnLevelLoadComplete()
{
	for (int i = 0; i < m_powerups.size(); i++)
		LoadPropsFromMagento(m_powerups[i]->GetType());
}

void PowerupManager::DeactivatePowerup()
{
	gMessageRouter->Post(&Message::PowerupDeactivated, m_activePowerup);
	m_activePowerup.ClearId();
	m_selectedPowerup.ClearId();
}

void PowerupManager::LoadPropsFromMagento(PowerupType* i_powerupType)
{
	MagentoProductPropsPtr props = Magento::GetGesturePtr(i_powerupType->TypeName);
	i_powerupType->Cost = (int)roundf(props->GetPriceInUSD(false));
	i_powerupType->actid = props->actid;
	i_powerupType->m_purchaseType = props->GetPurchaseType();
}

bool PowerupManager::IsMiniGamePerkPowerUp(const std::string& i_name)
{
	return i_name == "powerup_item_kill_all_zombies" || i_name == "powerup_special_item_x_ray" || i_name == "powerup_special_item_bowling" || i_name == "powerup_special_item_refresh_card" || i_name == "powerup_special_item_time_back";
}

BasePowerup* PowerupManager::GetBasePowerup(const PowerupType* i_powerupType)
{
	for (int i = 0; i < m_powerups.size(); i++)
	{
		if (m_powerups[i]->GetType() == i_powerupType)
			return m_powerups[i];
	}
	return NULL;
}

int PowerupManager::GetPowerAdditionCost(BasePowerup* powerup)
{
	if (powerup->GetType()->AdditionCost.empty())
		return 0;
	if ((size_t)m_powerupTimes >= powerup->GetType()->AdditionCost.size())
		return powerup->GetType()->AdditionCost[powerup->GetType()->AdditionCost.size() - 1];
	return powerup->GetType()->AdditionCost[m_powerupTimes];
}

int PowerupManager::GetCurrentPowerAdditionDamage(BasePowerup* powerup)
{
	int damage = 0;
	if (!powerup->GetType()->AdditionCost.empty())
	{
		std::vector<int>::iterator it = std::find(powerup->GetType()->AdditionCost.begin(), powerup->GetType()->AdditionCost.end(), mCacheGemCost - powerup->GetType()->Cost);
		if (it != powerup->GetType()->AdditionCost.end())
			damage = (it - powerup->GetType()->AdditionCost.begin()) * powerup->GetType()->AdditionDamage;
	}
	return damage;
}

void PowerupManager::SetMaxPurchasesAllowed(const int8 i_maxPurchases)
{
	for (size_t i = 0; i < m_powerups.size(); i++)
	{
		if (m_powerups[i]->GetPurchasesLeft() == -1)
			m_powerups[i]->SetMaxPurchasesAllowed(i_maxPurchases);
	}
}

void PowerupManager::onNetworkError(int erroId, const std::string& requestID)
{
	_PacketId packetId;
	if (requestID == packetId.ID_ICLOUD_USE_GEM)
	{
		if (gTimeMgr->GameIsPause())
		{
			gTimeMgr->PauseGameOnly(false);
			m_activePowerup->Deactivate();
		}
	}
}

void PowerupManager::OnBuyItemFinish(MsgResultInfo* io_result, const S2C_ICloud_GetConsumeGemInfo* pInfo, const S2C_PlayerInfo* pGemChanged)
{
	if (io_result && pInfo)
	{
		if (m_activePowerup.IsValid())
		{
			int actid = pInfo->m_actid;
			if (actid == m_activePowerup->GetType()->actid)
			{
				bool success = io_result->m_errorID == 0;
				onUseGemCallback(success);
			}
		}
	}
}

void PowerupManager::CancelActivePowerup()
{
	if (m_activePowerup)
	{
		m_activePowerup->Deactivate();
		m_activePowerup.ClearId();
	}
	else if (m_selectedPowerup)
	{
		m_selectedPowerup->Deselect();
		gMessageRouter->Post(&Message::PowerupDeselected, m_selectedPowerup);
	}
	m_selectedPowerup.ClearId();
}

void PowerupManager::ShowWidgets()
{
	UIWidget* holder = UIWidget::GetWidgetBySheetName("UIPowerupHolder");
	if (holder)
		holder->SetVisible(true);
}

void PowerupManager::AddToRenderQueue(RenderQueue* i_queue)
{
	if (m_selectedPowerup)
	{
		if (m_selectedPowerup->GetType()->ClassName != "PowerupTacticalCuke" && !IsMiniGamePerkPowerUp(m_selectedPowerup->GetType()->TypeName))
			i_queue->Add(399999, Sexy::MakeDelegate(*this, &PowerupManager::onDrawSelectionOnBoard));
	}
	if (m_activePowerup)
		i_queue->Add(1000000, Sexy::MakeDelegate(*this, &PowerupManager::onDrawActivePowerup));
}

void PowerupManager::onUseGemCallback(const bool& success)
{
	if (success)
	{
		int cost = GetCurrentPowerCost(m_activePowerup);
		if (m_ignoreCost)
			cost = 0;
		mCacheGemCost = cost;
		int costFreeGems = std::min(cost, ProfileMgr::GetInstance().GetCurrentProfile()->GetGiveGems());
		gMessageRouter->Post(&Message::PowerupActivated, m_activePowerup, cost, costFreeGems);
		int wave = gLawnApp->m_board->GetCurrentWave();
		if (wave >= 0 && (size_t)wave < gLawnApp->m_board->m_vecPowerupConsumeInfo.size())
			gLawnApp->m_board->m_vecPowerupConsumeInfo[wave]++;
		m_powerupTimes++;
	}
	else
	{
		CancelActivePowerup();
		gLawnApp->ShowGemStoreConfirm(STORE_TYPE_GEM, true);
	}
}

void PowerupManager::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupManager);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BasePowerup> >, m_powerups);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<BasePowerup>, m_selectedPowerup);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<BasePowerup>, m_activePowerup);
		REFLECTION_CLASSBUILDER_FIELD(int, m_powerupTimes);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_ignoreCost);
	REFLECTION_CLASSBUILDER_END(PowerupManager);
}

RT_CLASS_IMPLEMENT(PowerupManager);

BasePowerup* PowerupManager::GetSelectedPowerup() const
{
	return m_selectedPowerup;
}

BasePowerup* PowerupManager::GetActivePowerup() const
{
	return m_activePowerup;
}

const std::vector<RtWeakPtr<BasePowerup> >& PowerupManager::GetPowerups() const
{
	return m_powerups;
}

void PowerupManager::addPowerupSet(const std::string& levelPowerupSet)
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	RtId setId = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_PROPERTYSHEETS, RtName(StringToSexyString(levelPowerupSet)));
	RtWeakPtr<LevelPowerupSet> set(setId);
	for (std::string name : set->Powerups)
	{
		RtWeakPtr<PowerupType> type = ObjectTypeDirectory<PowerupType>::GetInstancePtr()->GetTypeFromTypeName(name);
		if (type && profile->GetPowerupUnlockState(name))
			AddPowerup(name, false);
	}
}

void PowerupManager::AddConveyorPowerup(const std::string& i_powerupName)
{
	BasePowerup* powerup = NULL;
	PowerupTypePtr type = ObjectTypeDirectory<PowerupType>::GetInstancePtr()->GetTypeFromTypeName(i_powerupName);
	RtClass* powerupClass = RtClass::StaticGetClassNamed(type->ClassName.c_str());
	for (size_t i = 0; i < m_powerups.size(); i++)
	{
		if (m_powerups[i]->GetClass() == powerupClass)
			powerup = m_powerups[i];
	}
	if (!powerup)
	{
		powerup = GameObject::Create(powerupClass, PVZDB::TABLE_POWERUPINSTANCES)->CastChecked<BasePowerup>();
		powerup->SetPowerupType(type);
		m_powerups.push_back(powerup->GetPtr());
	}
	SelectPowerup(type, true);
}

void PowerupManager::AddPowerup(const std::string& i_powerupName, bool i_isLocked)
{
	PowerupTypePtr type = ObjectTypeDirectory<PowerupType>::GetInstancePtr()->GetTypeFromTypeName(i_powerupName);
	size_t i = 0;
	while (i < m_powerups.size())
	{
		if (m_powerups[i++]->GetType() == type)
			return;
	}
	BasePowerup* powerup = GameObject::Create(RtClass::StaticGetClassNamed(type->ClassName.c_str()), PVZDB::TABLE_POWERUPINSTANCES)->CastChecked<BasePowerup>();
	LoadPropsFromMagento(type);
	powerup->SetPowerupType(type);
	m_powerups.push_back(powerup->GetPtr());
	if (type->TypeName == "powerupdangerroomtacticalcuke")
		m_powerupTimes = DangerRoomManager::GetInstancePtr()->GetCukeUsedCount();
	UIWidget* holder = UIWidget::GetWidgetBySheetName("UIPowerupHolder");
	PowerupHolderUI* holderUI;
	if (holder)
		holderUI = holder->CastChecked<PowerupHolderUI>();
	else
		holderUI = UIWidget::CreateWidget(RtName(L"UIPowerupHolder"), false)->CastChecked<PowerupHolderUI>();
	holderUI->AddPowerup(type, i_isLocked);
	if (!i_isLocked)
		gMessageRouter->Broadcast(&Message::PowerupEquipped, i_powerupName);
}

void PowerupManager::RemovePowerup(const std::string& i_powerupName)
{
	PowerupTypePtr type = ObjectTypeDirectory<PowerupType>::GetInstancePtr()->GetTypeFromTypeName(i_powerupName);
	for (int i = 0; i < m_powerups.size(); i++)
	{
		if (type == m_powerups[i]->GetType())
		{
			UIWidget* holder = UIWidget::GetWidgetBySheetName("UIPowerupHolder");
			if (holder)
			{
				for (int c = 0; c < holder->GetChildCount(); c++)
				{
					RtWeakPtr<UIWidget> child = holder->GetChildId(c);
					if (static_cast<PowerupUI*>(child.operator->())->GetPowerupType() == type)
					{
						child->Destroy();
						break;
					}
				}
			}
			if (m_activePowerup == m_powerups[i])
			{
				m_activePowerup->Deactivate();
				m_activePowerup.ClearId();
			}
			else if (m_selectedPowerup == m_powerups[i])
			{
				m_selectedPowerup->Deselect();
				gMessageRouter->Post(&Message::PowerupDeselected, m_selectedPowerup);
				m_selectedPowerup.ClearId();
			}
			m_powerups[i]->Destroy();
			m_powerups.erase(m_powerups.begin() + i);
			break;
		}
	}
}

void PowerupManager::SelectPowerup(const PowerupType* i_powerupType, const bool i_ignoreCost)
{
	if (m_selectedPowerup)
	{
		BasePowerup* previous = m_selectedPowerup;
		m_selectedPowerup->Deselect();
		m_selectedPowerup = RtWeakPtr<BasePowerup>();
		if (previous->GetType() == i_powerupType)
		{
			gMessageRouter->Post(&Message::PowerupDeselected, previous);
			return;
		}
	}
	for (int i = 0; i < m_powerups.size(); i++)
	{
		if (m_powerups[i]->GetType() == i_powerupType)
		{
			if (m_powerups[i]->GetPurchasesLeft() == 0)
				return;
			PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
			bool ignoreCost = i_ignoreCost;
			if (!ignoreCost && !m_powerups[i]->GetIgnoreCost())
			{
				int cost = GetCurrentPowerCost(m_powerups[i]);
				switch (m_powerups[i]->GetType()->m_purchaseType)
				{
				case PURCHASE_COIN:
					if (profile->GetNumCoins(true) >= cost)
						ignoreCost = false;
					else
					{
						gLawnApp->ShowGemStoreConfirm(STORE_TYPE_COIN, true);
						return;
					}
					break;
				case PURCHASE_GEM:
					if (cost > 0 && profile->GetNumGems(true) >= cost)
						ignoreCost = false;
					else
					{
						gLawnApp->ShowGemStoreConfirm(STORE_TYPE_GEM, true);
						return;
					}
					break;
				}
			}
			else
			{
				ignoreCost = true;
				GetCurrentPowerCost(m_powerups[i]);
			}
			m_ignoreCost = ignoreCost;
			gLawnApp->m_board->ClearCachedCursor();
			m_selectedPowerup = m_powerups[i];
			m_selectedPowerup->Select();
			gMessageRouter->Post(&Message::PowerupSelected, m_selectedPowerup);
			break;
		}
	}
}

void PowerupManager::onDrawSelectionOnBoard(Sexy::Graphics* i_g)
{
	Rect gridRect = gLawnApp->m_board->GetGridBoundingRect();
	gridRect = Rect(S(gridRect.mX), S(gridRect.mY), S(gridRect.mWidth), S(gridRect.mHeight));
	{
		GraphicsAutoState autoState(i_g);
		i_g->SetColorizeImages(true);
		Color selectColor = m_selectedPowerup->GetType()->BoardTimerColor;
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
	float percent = std::max(m_selectedPowerup->GetPowerupTimeRemaining() / m_selectedPowerup->GetType()->TotalTime, 0.0f);
	{
		GraphicsAutoState autoState(i_g);
		i_g->SetClipRect(gridRect);
		DrawRadialCooldown(i_g, percent, gridRect.mX + gridRect.mWidth / 2, gridRect.mY + gridRect.mHeight / 2, gridRect.mWidth, Color(0, 0, 0, 0), m_selectedPowerup->GetType()->BoardTimerColor);
	}
}

void PowerupManager::ActivatePowerup()
{
	m_activePowerup = m_selectedPowerup;
	int cost = GetCurrentPowerCost(m_activePowerup);
	int actid = m_activePowerup->GetType()->actid;
	if (m_ignoreCost)
		cost = 0;
	if (m_activePowerup->GetPurchasesLeft() > 0)
		m_activePowerup->SetMaxPurchasesAllowed(m_activePowerup->GetPurchasesLeft() - 1);
	if (IsMiniGamePerkPowerUp(m_activePowerup->GetType()->TypeName))
		return;
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (m_activePowerup->GetType()->TypeName == "powerupdangerroomtacticalcuke")
	{
		int cukeCount = DangerRoomManager::GetInstancePtr()->GetCukeCount();
		if (cukeCount > 0)
		{
			int remaining = cukeCount - 1;
			DangerRoomManager::GetInstancePtr()->SetCukeCount(remaining);
			gMessageRouter->Post(&Message::UseGemFinish, true);
			if (remaining == 0 && !DangerRoomManager::GetInstancePtr()->IsTrainingMode())
				m_activePowerup->SetIgnoreCost(false);
		}
		else
		{
			gTimeMgr->PauseGameOnly(true);
			if (profile->SubtractGems(cost, actid, new ICloudRequestCallbackFunction<PowerupManager, bool>(this, &PowerupManager::onUseGemCallback), 1, false) == -1)
			{
				gTimeMgr->PauseGameOnly(false);
				m_activePowerup->Deactivate();
			}
		}
		return;
	}
	std::string name = m_activePowerup->GetType()->TypeName;
	if (name == "poweruptacticalcuke" && profile->GetMonthlyCukeUsesLeft() > 0)
	{
		profile->ModifyPowerupUses("monthlycard_tacticalcuke", -1);
		gMessageRouter->Post(&Message::UseGemFinish, true);
		if (profile->GetMonthlyCukeUsesLeft() <= 0 && profile->GetPowerupUsesLeft("poweruptacticalcuke") <= 0)
			m_activePowerup->SetIgnoreCost(false);
	}
	else if (profile->GetPowerupUsesLeft(name) != 0)
	{
		profile->ModifyPowerupUses(name, -1);
		gMessageRouter->Post(&Message::UseGemFinish, true);
		if (profile->GetPowerupUsesLeft(name) <= 0)
			m_activePowerup->SetIgnoreCost(false);
	}
	else
	{
		switch (m_activePowerup->GetType()->m_purchaseType)
		{
		case PURCHASE_GEM:
			profile->SubtractGems(cost, actid, new ICloudRequestCallbackFunction<PowerupManager, bool>(this, &PowerupManager::onUseGemCallback), 1, false);
			break;
		case PURCHASE_COIN:
			if (gLawnApp->m_board->GetLevelDefinition() && gLawnApp->m_board->GetLevelDefinition()->IsVasebreaker)
			{
				TGAVaseBreakerData data;
				data._step = "2";
				data._usedSkill = m_activePowerup->GetType()->TypeName;
				data._coinAmt = DString(cost).c_str();
				TGALogMgr::GetInstance().LogVaseBreaker(data);
			}
			profile->SubtractCoins(cost);
			break;
		}
	}
}
