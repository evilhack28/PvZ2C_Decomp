//
//  Artifact.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"
#include "ArtifactMgr.h"
#include "DangerRoomManager.h"
#include "LawnApp.h"
#include "Board.h"
#include "LevelModuleManager.h"
#include "NameMapper.h"
#include "TodLib/TodStringFile.h"
#include "BoardArtifactButton.h"
#include "ArtifactDisplayBoard.h"
namespace RiftUtils { bool IsRiftTimedLevel(); }

ArtifactProperties::~ArtifactProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArtifactProperties);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Artifact);

void Artifact::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CommonData);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxUsedTimes);
		REFLECTION_CLASSBUILDER_FIELD(float, Cooldown);
	REFLECTION_CLASSBUILDER_END(CommonData);

	REFLECTION_CLASSBUILDER_BEGIN(Artifact);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ArtifactProperties>, m_props);
		REFLECTION_CLASSBUILDER_FIELD(CommonData, m_commonData);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextMainFieldTime);
	REFLECTION_CLASSBUILDER_END(Artifact);
}

void Artifact::registerForEvents()
{
}

void Artifact::DisplayPassiveSkill(float i_delay)
{
}

void Artifact::unregisterForEvents()
{
}

bool Artifact::CanGetArtifactBoosts(int i_id)
{
	return true;
}

void Artifact::ActivateSpeciallyOnDisplayBoard(int i_index)
{
}

/////////////// Trigger ///////////////

void Artifact::Initialize(ArtifactPropertiesPtr i_propsPtr)
{
	m_props = i_propsPtr;
}

int Artifact::GetUsedTimes()
{
	return m_usedTimes;
}

float Artifact::GetTriggerCooldown()
{
	return m_commonData.Cooldown;
}

void Artifact::OnNotifyArtifactButtonDepress(int i_usedTimes)
{
	m_usedTimes = i_usedTimes;
	TriggerMain();
}

void Artifact::OnStartBuff()
{
	m_startBuff = true;
}

void Artifact::TriggerMain()
{
	if (CanTriggerMain())
		DoTrigger();
}

float Artifact::GetTriggerLeftTime()
{
	float left = m_nextMainFieldTime - PVZ_T();
	if (left <= 0)
		left = 0;
	return left;
}

int Artifact::GetMaxUsedTimes()
{
	if (!ArtifactMgr::GetInstance().IsDangerRoom())
		return m_commonData.MaxUsedTimes;
	return DangerRoomManager::GetInstancePtr()->GetArtifactMaxTimes();
}

void Artifact::DoTrigger()
{
	m_nextMainFieldTime = PVZ_T() + m_commonData.Cooldown;
	m_doTrigger = true;
}

void Artifact::OnNotifyArtifactToolUsed()
{
	if (m_usedTimes > 0) {
		m_usedTimes--;
		if (m_usedTimes == 0)
			gMessageRouter->Post(&Message::NotifyRiftTimedUsedMax);
	}
}

void Artifact::Update()
{
	if (m_doTrigger && GetTriggerLeftTime() <= 0) {
		m_doTrigger = false;
		gMessageRouter->Post(&Message::ArtifactIdle);
	}
}

ArtifactPropertiesPtr Artifact::GetProps()
{
	return m_props;
}

bool Artifact::CanTriggerMain()
{
	if (m_activated && IsFieldActivated(MainField) && GetUsedTimes() <= GetMaxUsedTimes() && m_nextMainFieldTime <= PVZ_T())
		return true;
	return false;
}

const std::vector<std::string>& Artifact::GetArtResourceGroups()
{
	return ((ArtifactProperties*)GetProps())->ResourceGroups;
}

bool Artifact::IsFieldActivated(FieldType i_type)
{
	bool result = false;
	switch (i_type) {
	case PassiveField3:
		result = GetCurrentStage() > 3;
		break;
	case PassiveField2:
		result = GetCurrentStage() > 2;
		break;
	case PassiveField1:
		result = GetCurrentStage() > 1;
		break;
	case MainField:
		result = true;
		break;
	}
	return result;
}

void Artifact::EnsureResourceGroupsLoaded()
{
	if (gLawnApp->IsGroupLoadComplete(GetArtResourceGroups()))
		return;
	gLawnApp->m_board->LoadResourceGroupsForGameplay(GetArtResourceGroups());
}

float Artifact::GetBoostValue(ArtifactBoostType i_type)
{
	const std::string& name = ((ArtifactProperties*)GetProps())->TypeName;
	int id = ArtifactMapper::GetInstance().GetIdForName(name);
	return ArtifactMgr::GetInstance().GetBoostValue(id, i_type);
}

void Artifact::onPostLoad()
{
	LevelModuleManager* mgr = gLawnApp->m_board->GetLevelModuleManager();
	if (mgr)
		mgr->RegisterOnGameplayUpdate(Sexy::MakeDelegate(*this, &Artifact::Update));
}

void ArtifactProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactStageData);
		REFLECTION_CLASSBUILDER_FIELD(int32, StageMaterialRequire);
		REFLECTION_CLASSBUILDER_FIELD(int32, LevelUnlocked);
	REFLECTION_CLASSBUILDER_END(ArtifactStageData);

	REFLECTION_CLASSBUILDER_BEGIN(ArtifactProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, TypeName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ClassName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Description);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Name);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ArtifactStageData>, StageDatas);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, MainField);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PassiveField1);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PassiveField2);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PassiveField3);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantBoost>, Boosts);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantBoost>, GlobalBoosts);
		REFLECTION_CLASSBUILDER_FIELD(ArtifactDisplayActionsPropertyPtr, DisplayActions);
		REFLECTION_CLASSBUILDER_FIELD(ArtifactCultivationPropertyPtr, Cultivation);
		REFLECTION_CLASSBUILDER_FIELD(std::string, GetLevel);
		REFLECTION_CLASSBUILDER_FIELD(std::string, DemoLevel);
		REFLECTION_CLASSBUILDER_FIELD(ArtifactObtainWay, ObtainWay);
		REFLECTION_CLASSBUILDER_FIELD(std::string, DemoLevelWonMessage);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ResourceGroups);
		REFLECTION_CLASSBUILDER_FIELD(bool, IsNeedPedestal);
		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, TargetablePlantTypes);
	REFLECTION_CLASSBUILDER_END(ArtifactProperties);
}

SexyString ArtifactProperties::GetDescription()
{
	return TodStringTranslate(Sexy::StringToSexyString(Description));
}

SexyString ArtifactProperties::GetName()
{
	return TodStringTranslate(Sexy::StringToSexyString(Name));
}

Artifact::~Artifact()
{
	gMessageRouter->Unsubscribe(this);
}

float Artifact::GetExtraHpRate(const std::string& i_typeName)
{
	return 0;
}

float Artifact::GetExtraAttackRate(const std::string& i_typeName)
{
	return 0;
}

float Artifact::GetExtraReducedCooldown(const std::string& i_typeName)
{
	return 0;
}

float Artifact::GetExtraFastPlant(const std::string& i_typeName)
{
	return 0;
}

void Artifact::OnGetArtifactBoosts(int i_id, int i_type)
{
	if (!CanGetArtifactBoosts(i_id))
		return;

	std::string name = PlantNameMapper::GetInstance().GetNameForId(i_id);
	float value;
	switch (i_type) {
	case 4:
		value = GetExtraHpRate(name);
		break;
	case 6:
		value = GetExtraAttackRate(name);
		break;
	case 8:
		value = GetExtraReducedCooldown(name);
		break;
	case 10:
		value = GetExtraFastPlant(name);
		break;
	default:
		value = 0;
		goto finish;
	}
	if (value > 0)
	{
		float boost = GetBoostValue((ArtifactBoostType)7);
		asm("fmul %s0, %s0, %s1\n\tfadd %s1, %s0, %s1" : "+w"(boost), "+w"(value));
	}
finish:
	ArtifactProperties* props = (ArtifactProperties*)GetProps();
	int artId = ArtifactMapper::GetInstance().GetIdForName(props->TypeName);
	float extra = 0;
	ArtifactMgr::GetInstance().GetGlobalExtraValue(extra, i_id, i_type, artId);
	value += extra;
	ArtifactMgr::GetInstance().SetTempBoostValue(value);
}

Artifact::Artifact()
{
	m_activated = false;
	m_currentStage = 0;
	m_currentLevel = 1;
	m_usedTimes = 0;
	m_nextMainFieldTime = PVZ_EOT();
	m_doTrigger = false;
	m_startBuff = false;
	m_isOnDisplayBoard = false;
	m_autoClickInit = false;
	m_extraAttackRate = 0;
	m_extraHpRate = 0;
	gMessageRouter->Subscribe(&Message::NotifyArtifactToolUsed, Sexy::MakeDelegate(*this, &Artifact::OnNotifyArtifactToolUsed));
	gMessageRouter->Subscribe(&Message::NotifyArtifactButtonDepress, Sexy::MakeDelegate(*this, &Artifact::OnNotifyArtifactButtonDepress));
	gMessageRouter->Subscribe(&Message::GetArtifactBoosts, Sexy::MakeDelegate(*this, &Artifact::OnGetArtifactBoosts));
	gMessageRouter->Subscribe(&Message::StartBuff, Sexy::MakeDelegate(*this, &Artifact::OnStartBuff));
}

void Artifact::Activate()
{
	m_activated = true;
	m_nextMainFieldTime = 0;
	ArtifactMgr::GetInstance().FillCommonData(m_commonData);
	float cooldown = m_commonData.Cooldown;
	float reduce = GetBoostValue((ArtifactBoostType)4);
	asm volatile("" ::: "memory");
	m_commonData.Cooldown = m_commonData.Cooldown - reduce * cooldown;
	m_commonData.MaxUsedTimes = (int)(GetBoostValue((ArtifactBoostType)5) + (float)m_commonData.MaxUsedTimes);
	int usedTimes;
	if (ArtifactMgr::GetInstance().IsDangerRoom()) {
		usedTimes = DangerRoomManager::GetInstancePtr()->GetArtifactUsedTimes();
	} else {
		usedTimes = 0;
		if (RiftUtils::IsRiftTimedLevel())
			usedTimes = GetMaxUsedTimes();
	}
	m_usedTimes = usedTimes;
	LevelModuleManager* mgr = gLawnApp->m_board->GetLevelModuleManager();
	if (mgr)
		mgr->RegisterOnGameplayUpdate(Sexy::MakeDelegate(*this, &Artifact::Update));
	else
		gMessageRouter->Subscribe(&Message::ArtifactDisplayBoardUpdate, Sexy::MakeDelegate(*this, &Artifact::Update));
	bool inGame = gGameStateMgr->GetState() == GAME_Game;
	float sun = GetBoostValue((ArtifactBoostType)9);
	if (sun > 0 && inGame && gLawnApp->m_board)
		gLawnApp->m_board->AddSunMoney((int)sun);
	float noCD = GetBoostValue((ArtifactBoostType)10);
	if (noCD > 0 && inGame)
		ArtifactMgr::GetInstance().SetFreeNoCDLeftCount((int)noCD);
	gMessageRouter->Post(&Message::ActionComplete);
}
