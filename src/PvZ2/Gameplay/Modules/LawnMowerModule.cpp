//
//  LawnMowerModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LawnMowerModule.h"
#include "LawnApp.h"
#include "Board.h"
#include "BuyItemUI.h"
#include "CustomLevelUtils.h"
#include "ResourceHelpers.h"
#include "LawnMower.h"
#include "PVZDB.h"
#include "ADManager.h"
#include "CustomLevelUtils.h"
#include "CustomLevelEncourageModule.h"
#include "UICustomLevelSetting.h"
#include "GameStateMgr.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "WorldMapUtils.h"
#include "WorldData.h"
#include "Zombie.h"
#include "DangerRoomManager.h"
#include "LevelDefinition.h"
#include "StageModule.h"
#include "AnimationControllerHelpers.h"
#include "AnimationMgr.h"
#include "BoardConstants.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

LawnMowerModule::LawnMowerModule()
{
}

LawnMowerModule::~LawnMowerModule()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(LawnMowerModule);

void LawnMowerModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LawnMowerModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_bonusLawnMowersRemaining);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, m_respawnsRemaining);
	REFLECTION_CLASSBUILDER_END(LawnMowerModule);
}

/////////////// Accessors ///////////////

float LawnMowerModule::GetEntryAnimDuration()
{
	return getProps<LawnMowerProperties>()->MowerEntryAnimDuration;
}

bool LawnMowerModule::HasUntriggeredMowerInRow(uint8 i_rowIndex)
{
	return GetUntriggeredMowerInRow(i_rowIndex) != NULL;
}

/////////////// Logic ///////////////

// BoardHelpers.h pulls in RiftUtils.h, which needs a header we do not have
namespace BoardHelpers
{
	MowerSpawnOverride GetLevelOverride_MowerSpawn();
}

bool LawnMowerModule::canTriggerNormalADMower()
{
	return true;
}

void LawnMowerModule::AddMowerToSaveData(uint8 i_rowIndex)
{
	gLawnApp->m_board->m_mowerAllowedInRow[i_rowIndex] = true;
}

bool LawnMowerModule::hasMowerInSaveData(uint8 i_rowIndex)
{
	return gLawnApp->m_board->m_mowerAllowedInRow[i_rowIndex];
}

std::vector<LawnMower*> LawnMowerModule::getMowerBoardEntitiesInRow(uint8 i_rowIndex)
{
	std::vector<LawnMower*> mowers;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BOARDENTITIES); it; ++it)
	{
		LawnMower* mower = BoardEntityPtr(*it)->Cast<LawnMower>();
		if (mower && mower->GetRow() == i_rowIndex)
			mowers.push_back(mower);
	}
	return mowers;
}

LawnMower* LawnMowerModule::GetUntriggeredMowerInRow(uint8 i_rowIndex)
{
	std::vector<LawnMower*> mowers = getMowerBoardEntitiesInRow(i_rowIndex);
	for (std::vector<LawnMower*>::iterator it = mowers.begin(); it != mowers.end(); ++it)
	{
		LawnMower* mower = *it;
		if (mower->GetMowerState() != MOWER_TRIGGERED)
			return mower;
	}
	return NULL;
}

void LawnMowerModule::prepareMowerForRow(int i_rowIndex)
{
	if (shouldCreateMowerInRow(i_rowIndex))
	{
		PopAnim* mowerAnim = getMowerAnim();
		std::string activatedAudioEvent = getMowerAudio();
		LawnMower* mower = GameObject::Create<LawnMower>(PVZDB::TABLE_BOARDENTITIES);
		mower->LawnMowerInitialize(mowerAnim, i_rowIndex, activatedAudioEvent, getIdleAnimWeights());
		mower->SetExplodeAtGridX(getProps<LawnMowerProperties>()->MowerExplodeAtGridX);
	}
}

void LawnMowerModule::addPreparedMowers()
{
	float entryAnimDuration = GetEntryAnimDuration();
	AnimateLawnMowers* animateMowers = AnimateLawnMowers::Create(entryAnimDuration + (BoardConstants::NUMBER_OF_ROWS() + 1) * 0.1f, entryAnimDuration);
	gLawnApp->m_board->m_animationMgr->Add(animateMowers->GetPtr());
}

void LawnMowerModule::AwardMowers(int i_mowerCount, bool i_createNow)
{
	for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS() && i_mowerCount > 0; row++)
	{
		if (!hasMowerInSaveData(row))
		{
			AddMowerToSaveData(row);
			i_mowerCount--;
			if (i_createNow)
				prepareMowerForRow(row);
		}
	}
	if (i_createNow)
		addPreparedMowers();
}

void LawnMowerModule::initializeMowerRespawn()
{
	int respawns = getProps<LawnMowerProperties>()->UnlimitedMowers ? INT_MAX : 0;
	switch (BoardHelpers::GetLevelOverride_MowerSpawn())
	{
	case MOWER_SPAWN_INFINITE:
		respawns = INT_MAX;
		break;
	case MOWER_SPAWN_REGEN_ONCE:
		respawns = 1;
		break;
	case MOWER_SPAWN_NONE:
	case MOWER_SPAWN_ONCE:
		respawns = 0;
		break;
	default:
		break;
	}
	for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
		m_respawnsRemaining.push_back(respawns);
}

void LawnMowerModule::onLawnMowerDie(LawnMower* i_mower)
{
	gLawnApp->m_board->GetStage();
	std::string activatedAudioEvent = getMowerAudio();
	if (m_bonusLawnMowersRemaining > 0 && !gLawnApp->m_board->IsGameplayEnded())
	{
		int row = i_mower->GetRow();
		LawnMower* mower = GameObject::Create<LawnMower>(PVZDB::TABLE_BOARDENTITIES);
		mower->LawnMowerInitialize(getMowerAnim(), row, activatedAudioEvent, getIdleAnimWeights());
		mower->SetExplodeAtGridX(getProps<LawnMowerProperties>()->MowerExplodeAtGridX);
		m_bonusLawnMowersRemaining--;
	}
}

void LawnMowerModule::createMowers()
{
	PopAnim* mowerAnim = getMowerAnim();
	std::string activatedAudioEvent = getMowerAudio();
	bool readyMowers = false;
	if (gLawnApp->m_board->GetLevelDefinition()->IsDangerRoom)
	{
		std::string worldName = gLawnApp->m_board->GetLevelDefinition()->StageModule->BelongsToWorld;
		DangerRoomInfo dangerRoomInfo = gDangerRoomMgr->GetDangerRoomInfo(false);
		readyMowers = dangerRoomInfo.CurrentLevel > 1;
	}
	for (int row = 0; row < gLawnApp->m_board->m_gridSizeY; row++)
	{
		if (gLawnApp->m_board->m_plantRow[row] != PLANTROW_DIRT && gLawnApp->m_board->m_mowerAllowedInRow[row])
		{
			LawnMower* mower = GameObject::Create<LawnMower>(PVZDB::TABLE_BOARDENTITIES);
			mower->LawnMowerInitialize(mowerAnim, row, activatedAudioEvent, getIdleAnimWeights());
			mower->SetExplodeAtGridX(getProps<LawnMowerProperties>()->MowerExplodeAtGridX);
			if (readyMowers)
				mower->SetMowerState(MOWER_READY);
		}
	}
}

void LawnMowerModule::onBuyItemOK(int i_type)
{
	if (i_type == BuyItemUI::BuyMower || i_type == BuyItemUI::AdsMower || i_type == BuyItemUI::NormalAdsMower)
	{
		if (i_type == BuyItemUI::AdsMower)
			m_adsMowerTimes++;
		if (m_iBuyMowerRow >= 0)
		{
			std::string name("buy_mower");
			std::string description("");
			std::string sku = BuyItemUI::GetSkuByType(BuyItemUI::BuyMower);
			gLawnApp->m_gameChargeType = 1;
			gMessageRouter->Post(&Message::GameCharge, name, description, sku);
			LawnMower* mower = GameObject::Create<LawnMower>(PVZDB::TABLE_BOARDENTITIES);
			mower->LawnMowerInitialize(getMowerAnim(), m_iBuyMowerRow, getMowerAudio(), getIdleAnimWeights());
			mower->StartMower();
			m_fBuyMowerCoolDown = 1.0f;
		}
		m_iBuyMowerRow = -1;
	}
}

static LawnMower* FindMowerInRow(int i_row)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BOARDENTITIES); it; ++it)
	{
		LawnMower* mower = BoardEntityPtr(*it)->Cast<LawnMower>();
		if (mower && mower->GetRow() == i_row)
			return mower;
	}
	return NULL;
}

bool LawnMowerModule::isNeedBuyMower(int i_row)
{
	if (gLawnApp->m_board->m_plantRow[i_row] == PLANTROW_DIRT || !gLawnApp->m_board->m_mowerAllowedInRow[i_row])
		return false;
	if (FindMowerInRow(i_row))
		return false;
	Sexy::Rect attackRect = LawnMower::GetAttackRect(i_row);
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		Zombie* zombie = PVZDB::GetInstance().GetTable(PVZDB::TABLE_ZOMBIES)->GetObjectForId(*it)->Cast<Zombie>();
		if (zombie->CanBeMowed() && zombie->IsInRow(i_row) && !zombie->IsControlled()
			&& (zombie->CollidesWithType(COLLIDE_GRIDITEMS | COLLIDE_ALL_ZOMBIES) || zombie->CollidesWithFlying() || __builtin_expect(zombie->IsInvisible(), 0))
			&& attackRect.Intersects(zombie->GetCollisionRect()))
			return true;
	}
	return false;
}

void LawnMowerModule::initializeModule()
{
	m_bonusLawnMowersRemaining = 0;
	m_iBuyMowerRow = -1;
	m_adsMowerTimes = 0;
	m_fBuyMowerCoolDown = -1.0f;
	if (gLawnApp->m_board->GetLevelDefinition()->IsDangerRoom)
	{
		DangerRoomInfo dangerRoomInfo = gDangerRoomMgr->GetDangerRoomInfo(false);
		for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
			gLawnApp->m_board->m_mowerAllowedInRow[row] = gDangerRoomMgr->IsHaveMower(row);
	}
	else if (gLawnApp->m_board->GetLevelDefinition()->IsJoust)
	{
		for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
			gLawnApp->m_board->m_mowerAllowedInRow[row] = true;
	}
	else if (gLawnApp->m_board->GetLevelDefinition()->IsEpicTask)
	{
		for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
			gLawnApp->m_board->m_mowerAllowedInRow[row] = true;
	}
	else
	{
		bool hasMower;
		std::string worldName;
		std::string levelName = gLawnApp->m_board->GetLevel();
		WorldData* worldData = WorldMapUtils::GetWorldData()->FindWorldDataByLevelName(levelName);
		if (worldData)
		{
			worldName = worldData->m_worldName;
			hasMower = gLawnApp->IsWorldHaveMower(worldName);
		}
		else
			hasMower = false;
		if (BoardHelpers::GetLevelOverride_MowerSpawn() == MOWER_SPAWN_NONE)
			hasMower = false;
		for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
			gLawnApp->m_board->m_mowerAllowedInRow[row] = hasMower;
	}
}

void LawnMowerModule::postInitialize()
{
	if (!gLawnApp->m_board->GetLevelDefinition() || !gLawnApp->m_board->GetLevelDefinition()->IsDangerRoom)
	{
		bool allowMowers = BoardHelpers::GetLevelOverride_MowerSpawn() != MOWER_SPAWN_NONE;
		for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
			gLawnApp->m_board->m_mowerAllowedInRow[row] = allowMowers;
	}
	initializeMowerRespawn();
}

void LawnMowerModule::registerForEvents()
{
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &LawnMowerModule::onUpdate));
	gMessageRouter->Subscribe(&Message::ReadyForLawnItems, Sexy::MakeDelegate(*this, &LawnMowerModule::onReadyForMowers));
	gMessageRouter->Subscribe(&Message::MowerDie, Sexy::MakeDelegate(*this, &LawnMowerModule::onLawnMowerDie));
	gMessageRouter->Subscribe(&Message::BuyItemOK, Sexy::MakeDelegate(*this, &LawnMowerModule::onBuyItemOK));
	gMessageRouter->Subscribe(&Message::BuyItemCancel, Sexy::MakeDelegate(*this, &LawnMowerModule::onBuyItemCancel));
}

void LawnMowerModule::onUpdate()
{
	if (m_fBuyMowerCoolDown > 0.0f)
	{
		m_fBuyMowerCoolDown -= PVZ_Dt();
		return;
	}
	int buyRow = -1;
	for (int row = 0; row < gLawnApp->m_board->m_gridSizeY; row++)
	{
		if (isNeedBuyMower(row))
		{
			if (buyRow != -1)
				return;
			buyRow = row;
		}
	}
	if (__builtin_expect(!!(buyRow < 0), 0))
		return;
	bool canBuyMower = CustomLevelUtils::IsCustomLevel() && gLawnApp->m_board->GetLevelModuleByClass<CustomLevelEncourageModule>()
		&& CustomLevelSettingManager::GetInstancePtr()->NeedShowAds()
		&& gGameStateMgr->GetLevelSource() == LEVELSOURCE_CustomLevelDownload
		&& gLawnApp->m_board->GetLevelModuleByClass<CustomLevelEncourageModule>()->CanBuyMower();
	bool isDangerRoom = gLawnApp->m_board && gLawnApp->m_board->IsDangerRoom();
	if (!isDangerRoom && !CustomLevelUtils::IsCustomLevel())
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		if (profile && profile->GetNumGems(false) > 19)
		{
			if (canTriggerNormalADMower() && ADManager::GetInstance().CanWatchAD(ADType_Mower))
				gLawnApp->ShowBuyItemUI(BuyItemUI::NormalAdsMower);
			else
				gLawnApp->ShowBuyItemUI(BuyItemUI::BuyMower);
		}
	}
	if (canBuyMower)
	{
		std::string packageName = Android::Util::GetPackageName();
		if (m_adsMowerTimes <= 4 && packageName != "com.popcap.pvz2cthd.todaygame")
			gLawnApp->ShowBuyItemUI(BuyItemUI::AdsMower);
	}
	m_iBuyMowerRow = buyRow;
}

const std::string& LawnMowerModule::getMowerAudio()
{
	return getProps<LawnMowerProperties>()->MowerActivatedAudioEvent;
}

const std::vector<int> LawnMowerModule::getIdleAnimWeights()
{
	return getProps<LawnMowerProperties>()->MowerIdleAnimWeights;
}

PopAnim* LawnMowerModule::getMowerAnim()
{
	Sexy::RtWeakPtr<Sexy::PopAnim> anim = GetPAMByName(getProps<LawnMowerProperties>()->MowerPopAnim);
	return anim;
}

void LawnMowerModule::onBuyItemCancel(int i_type)
{
	if (i_type == BuyItemUI::BuyMower || i_type == BuyItemUI::AdsMower || i_type == BuyItemUI::NormalAdsMower)
	{
		m_fBuyMowerCoolDown = PVZ_EOT();
		m_iBuyMowerRow = -1;
	}
}

bool LawnMowerModule::rowCanAcceptNewMower(int i_rowIndex)
{
	if (gLawnApp->m_board->m_plantRow[i_rowIndex] == PLANTROW_DIRT)
		return false;
	return !HasUntriggeredMowerInRow(i_rowIndex);
}

bool LawnMowerModule::shouldCreateMowerInRow(uint8 i_rowIndex)
{
	return rowCanAcceptNewMower(i_rowIndex) && gLawnApp->m_board->m_mowerAllowedInRow[i_rowIndex];
}

bool LawnMowerModule::ShouldRespawnMower(uint8 i_rowIndex)
{
	int& remaining = m_respawnsRemaining[i_rowIndex];
	if (remaining <= 0)
		return false;
	if (remaining == INT_MAX)
		return true;
	remaining--;
	return true;
}

void LawnMowerModule::onReadyForMowers()
{
	if (gLawnApp->m_board->GetLevelIsHard())
		return;
	if (CustomLevelUtils::IsCustomLevel())
		return;
	createMowers();
}
