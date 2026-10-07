//
//  ArtifactMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-07.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactMgr.h"
#include "ProfileMgr.h"
#include <algorithm>
#include "PlayerInfo.h"
#include "LawnApp.h"
#include "Board.h"
#include "DangerRoomManager.h"
#include "ArtifactModule.h"
#include "NameMapper.h"
#include "PVZDB.h"
#include "LevelBasedModifierModule.h"
#include "TodLib/TodStringFile.h"
#include "Artifact.h"
#include "LevelModuleManager.h"
#include "PlantBoostMgr.h"
#include "BoardArtifactButton.h"
#include "gameNetWork/PacketID.h"
#include "DNode/DNodeWidget.h"

namespace RiftUtils { bool IsPlayingRiftLevel(); }
namespace PlantWarsUtils { bool IsPlayingPlantWarsLevel(); }
namespace MiniGameCollectionUtils { bool IsPlayingMiniGameCollectionLevel(); }
#include "RunningSubway.h"
#include "SkyCityStage.h"
#include "ArenaPlantModule.h"
#include "IntroArenaTutorialBattleModule.h"
#include "CustomLevelUtils.h"
#include "CardGameUtils.h"
#include "NewPVPUtils.h"

namespace BoardHelpers
{
	float ApplyLevelBasedModifierValue(float i_originalValue, int i_type, int i_subType = -1, int i_index = 0);
}

/////////////// Construction ///////////////

ArtifactMgr::ArtifactMgr()
{
	m_tempBoostValue = 0.0f;
	m_orderId = "";
	m_currentPropVer = 0;
	m_globalArtifactId = -1;
	m_blessLegendLeftCount = 0;
	m_freePlantingLeftCount = 0;
	m_freeNoCDLeftCount = 0;
	InitDefaultImprovedProps();
	gMessageRouter->Subscribe(&Message::GetArtifactBoosts, Sexy::MakeDelegate(*this, &ArtifactMgr::OnGetArtifactBoosts));
}

ArtifactMgr::~ArtifactMgr()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Accessors ///////////////

void ArtifactMgr::SetArtifact(ArtifactData i_data)
{
	m_currentArtifact = i_data;
}

void ArtifactMgr::SetOrderId(const std::string& i_id)
{
	m_orderId = i_id;
}

const std::string& ArtifactMgr::GetOrderId()
{
	return m_orderId;
}

bool ArtifactMgr::IsUnsharedBoost(ArtifactBoostType i_type)
{
	return (unsigned)(i_type - 9) <= 2;
}

void ArtifactMgr::TriggerArtifact(int i_usedTimes)
{
	gMessageRouter->Post(&Message::NotifyArtifactButtonDepress, i_usedTimes);
}

bool ArtifactMgr::CanFreeNoCD()
{
	return GetFreeNoCDLeftCount() > 0;
}

bool ArtifactMgr::CanFreePlanting()
{
	return GetFreePlantingLeftCount() > 0;
}

bool ArtifactMgr::IsGlobalBoost(const ArtifactBoostInfo& i_boost)
{
	return GetBoostRareByBoostId(i_boost.BoostId) > BoostRarity_Epic;
}

void ArtifactMgr::CheatTestField(int i_id)
{
	RemoveActivatedArtifact();
	ProfileMgr::GetInstance().GetCurrentProfile()->SetCurrentArtifact(i_id);
}

float ArtifactMgr::CalculateExpValue(std::string& i_srcField, int i_id)
{
	GetRealExpression(i_srcField, i_id);
	return ArtifactUtils::GetExpressionResult(i_srcField);
}

ArtifactData ArtifactMgr::GetArtifact()
{
	return m_currentArtifact;
}

const std::vector<ArtifactImprovedPropertySheet*> ArtifactMgr::GetProps()
{
	return m_improvedProps;
}

static std::vector<ArtifactBoostPropertySheetPtr> s_emptyBoostProps;

const std::vector<ArtifactBoostPropertySheetPtr>& ArtifactMgr::GetEnabledBoostProps(int i_artifactId)
{
	ArtifactImprovedPropertySheet* props = getArtifactImprovedPropsById(i_artifactId);
	if (props != NULL)
		return props->EnabledBoost;
	return s_emptyBoostProps;
}

/////////////// Boost lookup ///////////////

static ArtifactBoostPropertySheetPtr s_emptyBoostSheet;

const ArtifactBoostPropertySheetPtr& ArtifactMgr::getBoostSheet(int i_artifactId, int i_boostId)
{
	ArtifactImprovedPropertySheet* props = getArtifactImprovedPropsById(i_artifactId);
	if (props != NULL)
		return getBoostById(props->EnabledBoost, i_boostId);
	return s_emptyBoostSheet;
}

ArtifactBoostType ArtifactMgr::GetBoostTypeByBoostId(int i_artifactId, int i_boostId)
{
	ArtifactBoostType type = Boost_None;
	ArtifactImprovedPropertySheet* props = getArtifactImprovedPropsById(i_artifactId);
	if (props != NULL)
		type = getBoostById(props->EnabledBoost, i_boostId)->Type;
	return type;
}

int ArtifactMgr::GetBoostRareByBoostId(int i_artifactId, int i_boostId)
{
	ArtifactImprovedPropertySheet* props = getArtifactImprovedPropsById(i_artifactId);
	if (props == NULL)
		return -1;
	return getBoostById(props->EnabledBoost, i_boostId)->Rare;
}

bool ArtifactMgr::IsDangerRoom()
{
	if (gLawnApp->m_board->IsDangerRoom())
		return !DangerRoomManager::GetInstancePtr()->IsTrainingMode();
	return false;
}

bool ArtifactMgr::IsArtifactDisabled()
{
	if (gLawnApp->m_board != NULL)
	{
		LevelModuleManager* manager = gLawnApp->m_board->GetLevelModuleManager();
		if (manager != NULL)
			return manager->GetModuleByClass<ArtifactModule>() == NULL;
	}
	return true;
}

/////////////// Lookup helpers ///////////////

ArtifactImprovedPropertySheet* ArtifactMgr::getArtifactImprovedPropsById(int i_artifactId)
{
	std::vector<ArtifactImprovedPropertySheet*>::iterator it = std::find_if(m_improvedProps.begin(), m_improvedProps.end(),
		[i_artifactId](ArtifactImprovedPropertySheet* i_props) { return i_props->ArtifactId == i_artifactId; });
	if (it != m_improvedProps.end())
		return *it;
	return NULL;
}

const ArtifactBoostPropertySheetPtr& ArtifactMgr::getBoostById(const std::vector<ArtifactBoostPropertySheetPtr>& i_boosts, int i_id)
{
	std::vector<ArtifactBoostPropertySheetPtr>::const_iterator it = std::find_if(i_boosts.begin(), i_boosts.end(),
		[i_id](const ArtifactBoostPropertySheetPtr& i_boost) { return i_boost->Id == i_id; });
	if (it != i_boosts.end())
		return *it;
	return s_emptyBoostSheet;
}

int ArtifactMgr::GetBoostRareByBoostId(int i_boostId)
{
	const std::map<std::string, int>& artifacts = ArtifactMapper::GetInstance().GetMap();
	std::map<std::string, int>::const_iterator it;
	for (it = artifacts.begin(); it != artifacts.end(); ++it)
	{
		int rare = GetBoostRareByBoostId(it->second, i_boostId);
		if (rare != -1)
			return rare;
	}
	return -1;
}

static ArtifactBoostValueInfo s_emptyBoostValueInfo;

const ArtifactBoostValueInfo& ArtifactMgr::GetBoostValueRangeByBoostId(int i_artifactId, int i_boostId)
{
	ArtifactImprovedPropertySheet* props = getArtifactImprovedPropsById(i_artifactId);
	if (props != NULL)
		return getBoostById(props->EnabledBoost, i_boostId)->ValueRange;
	return s_emptyBoostValueInfo;
}

bool ArtifactMgr::hasPlantBoost(const std::vector<PlantBoost>& i_boosts, int i_boostType)
{
	return std::find_if(i_boosts.begin(), i_boosts.end(),
		[i_boostType](const PlantBoost& i_boost) { return i_boost.PlantBoostProps->Type == i_boostType; }) != i_boosts.end();
}

/////////////// Activated artifact ///////////////

float ArtifactMgr::GetActivatedArtifactCooldown()
{
	float result = 0.0f;
	ArtifactPtr artifact = GetActivatedArtifact();
	if (artifact)
		result = artifact->GetTriggerCooldown();
	return result;
}

float ArtifactMgr::GetActivatedArtifactLeftTime()
{
	float result = 0.0f;
	ArtifactPtr artifact = GetActivatedArtifact();
	if (artifact)
		result = artifact->GetTriggerLeftTime();
	return result;
}

int ArtifactMgr::GetActivatedArtifactUsedTime()
{
	int result = 0;
	ArtifactPtr artifact = GetActivatedArtifact();
	if (artifact)
		result = artifact->GetUsedTimes();
	return result;
}

int ArtifactMgr::GetActivatedArtifactMaxUsedTime()
{
	int result = 0;
	ArtifactPtr artifact = GetActivatedArtifact();
	if (artifact)
		result = artifact->GetMaxUsedTimes();
	return result;
}

bool ArtifactMgr::CanTriggerActivatedArtifact()
{
	ArtifactPtr artifact = GetActivatedArtifact();
	bool result = artifact;
	if (result)
		result = artifact->CanTriggerMain();
	return result;
}

static ArtifactData s_emptyArtifactData;
static NetworkArtifactBoostData s_emptyNetworkBoost;

ArtifactPtr ArtifactMgr::GetActivatedArtifact()
{
	if (m_activatedArtifact)
		return m_activatedArtifact;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ARTIFACT); it; ++it)
	{
		Artifact* artifact = PVZDB::GetInstance().GetTable(PVZDB::TABLE_ARTIFACT)->GetObjectForId(*it)->Cast<Artifact>();
		if (artifact != NULL)
		{
			m_activatedArtifact = artifact->GetPtr();
			break;
		}
	}
	return m_activatedArtifact;
}

void ArtifactMgr::RemoveActivatedArtifact()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ARTIFACT); it; ++it)
	{
		ArtifactPtr artifact(*it);
		artifact->Destroy();
	}
	m_currentArtifact = s_emptyArtifactData;
	SetTempBoostValue(0.0f);
}

void ArtifactMgr::AddArtifactModuleIfNeeded()
{
	if (artifactDisabled())
		return;
	Sexy::RtId id = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_LEVELMODULES, Sexy::RtName(_S("ArtifactModuleProps")));
	Sexy::RtWeakPtr<LevelModuleProperties> props(id);
	if (props)
		gLawnApp->m_board->GetLevelModuleManager()->AddModuleFromProperties(props);
}

const NetworkArtifactBoostData& ArtifactMgr::GetNetworkBoostById(const Network_ArtifactImprovedPropertySheet* props, int i_id)
{
	std::vector<NetworkArtifactBoostData>::const_iterator it = std::find_if(props->Boosts.begin(), props->Boosts.end(),
		[i_id](const NetworkArtifactBoostData& i_boost) { return i_boost.Id == i_id; });
	if (it != props->Boosts.end())
		return *it;
	return s_emptyNetworkBoost;
}

/////////////// Artifact info ///////////////

std::string ArtifactMgr::GetArtifactName(int i_id)
{
	ArtifactPropertiesPtr props = GetArtifactByTypeId(i_id);
	if (props)
		return props->Name;
	return "";
}

std::string ArtifactMgr::GetArtifactDescription(int i_id)
{
	ArtifactPropertiesPtr props = GetArtifactByTypeId(i_id);
	if (props)
		return props->Description;
	return "";
}

SexyString ArtifactMgr::GetImprovedName(int i_artifactId)
{
	SexyString result;
	ArtifactImprovedPropertySheet* props = getArtifactImprovedPropsById(i_artifactId);
	if (props != NULL)
		result = TodStringTranslate(Sexy::StringToSexyString(props->Name));
	return result;
}

SexyString ArtifactMgr::GetImprovedDescription(int i_artifactId)
{
	SexyString result;
	ArtifactImprovedPropertySheet* props = getArtifactImprovedPropsById(i_artifactId);
	if (props != NULL)
		result = TodStringTranslate(Sexy::StringToSexyString(props->Description));
	return result;
}

void ArtifactMgr::SyncArtifact(int i_id, int i_level, int i_stage)
{
	ArtifactPropertiesPtr props = GetArtifactByTypeId(i_id);
	if (props)
		addArtifact(props->TypeName, i_level, i_stage);
}

void ArtifactMgr::OnGetArtifactBoosts(int i_id, int i_type)
{
	if (!m_currentArtifact.PropsPtr)
	{
		SetGlobalArtifactId(-1);
		float value = 0.0f;
		int artifactId = GetGlobalExtraValue(value, i_id, i_type, -1);
		SetGlobalArtifactId(artifactId);
		SetTempBoostValue(value);
	}
}

void ArtifactMgr::InitProps(const Network_ArtifactImprovedPropertySheet* props, int i_networkVersion)
{
	m_currentPropVer = i_networkVersion;
	std::vector<NetworkArtifactBoostConfig>::const_iterator it = props->Configs.begin();
	std::vector<NetworkArtifactBoostConfig>::const_iterator end = props->Configs.end();
	for (; it != end; ++it)
		SyncLocalProps(props, (*it).ArtifactId, (*it).EnabledBoostInfos);
}

/////////////// Artifact data ///////////////

ArtifactData ArtifactMgr::CreateArtifactData(std::string i_artifactName, int i_level, int i_stage)
{
	ArtifactData data;
	ArtifactPropertiesPtr props = PVZDB::GetInstance().FindObjectByAlias<ArtifactProperties>(PVZDB::TABLE_ARTIFACT_PROPERTIES, Sexy::RtName(Sexy::StringToSexyString(i_artifactName)));
	data.PropsPtr = props;
	data.CurrentLevel = i_level;
	data.CurrentStage = i_stage;
	return data;
}

void ArtifactMgr::addArtifact(std::string i_artifactName, int i_level, int i_stage)
{
	m_currentArtifact = CreateArtifactData(i_artifactName, i_level, i_stage);
}

ArtifactPropertiesPtr ArtifactMgr::GetArtifactByTypeId(int i_id)
{
	std::string name = ArtifactMapper::GetInstance().GetNameForId(i_id);
	ArtifactPropertiesPtr result;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ARTIFACT_PROPERTIES); it; ++it)
	{
		ArtifactProperties* sheet = NULL;
		{
			Sexy::RtId id = *it;
			ArtifactPropertiesPtr candidate(id);
			if (candidate)
			{
				Sexy::RtId sheetId = *it;
				ArtifactPropertiesPtr props(sheetId);
				sheet = props.GetObject()->Cast<ArtifactProperties>();
			}
		}
		if (sheet != NULL && sheet->TypeName == name)
		{
			result = *it;
			break;
		}
	}
	return result;
}

void ArtifactMgr::FillCommonData(CommonData& i_data)
{
	int fieldCount = m_currentArtifact.PropsPtr->MainField.size();
	float usesValue = (float)(int)CalculateFieldValue(MainField, fieldCount - 1);
	int maxUses = (int)usesValue;
	if (maxUses == 0)
	{
		usesValue = 1.0f;
		maxUses = 1;
	}
	i_data.MaxUsedTimes = maxUses;
	i_data.MaxUsedTimes = (int)BoardHelpers::ApplyLevelBasedModifierValue(usesValue, LevelBasedModifier_DefaultArtifactUseTimes, -1, 0);
	i_data.Cooldown = CalculateFieldValue(MainField, fieldCount - 2);
}

/////////////// Field values ///////////////

std::string ArtifactMgr::GetBoostAliases(PlantBoostType i_boostType)
{
	std::string result = "";
	switch (i_boostType)
	{
	case EXTRA_ATTACK:
		result = "BoostExtraAttack";
		break;
	case FAST_COOLDOWN:
		result = "BoostFastCooldown";
		break;
	case EXTRA_HITPOINTS:
		result = "BoostExtraHitPoints";
		break;
	default:
		break;
	}
	return result;
}

std::string ArtifactMgr::GetTargetFieldByFieldType(ArtifactPropertiesPtr i_propsPtr, FieldType i_type, int i_index)
{
	std::string result = "";
	if (i_propsPtr)
	{
		switch (i_type)
		{
		case MainField:
			result = i_propsPtr->MainField[i_index];
			break;
		case PassiveField1:
			result = i_propsPtr->PassiveField1[i_index];
			break;
		case PassiveField2:
			result = i_propsPtr->PassiveField2[i_index];
			break;
		case PassiveField3:
			result = i_propsPtr->PassiveField3[i_index];
			break;
		default:
			break;
		}
	}
	return result;
}

float ArtifactMgr::CalculateFieldValue(FieldType i_type, int i_index)
{
	float result = 0.0f;
	std::string field = GetTargetFieldByFieldType(m_currentArtifact.PropsPtr, i_type, i_index);
	if (!field.empty())
		result = CalculateExpValue(field, -1);
	return result;
}

float ArtifactMgr::CalculateFieldValue(ArtifactPropertiesPtr i_propsPtr, FieldType i_type, int i_index)
{
	float result = 0.0f;
	std::string field = GetTargetFieldByFieldType(i_propsPtr, i_type, i_index);
	if (!field.empty())
		result = CalculateExpValue(field, ArtifactMapper::GetInstance().GetIdForName(i_propsPtr->TypeName));
	return result;
}

/////////////// Boost info ///////////////

std::vector<CurrentArtifactBoostInfo> ArtifactMgr::GetCurrentBoostInfo(int i_artifactId, bool i_saved)
{
	std::vector<CurrentArtifactBoostInfo> unused;
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	std::vector<ArtifactBoostInfo> boostInfos = i_saved ? profile->GetArtifactInfoByID(i_artifactId).BoostInfos : profile->GetArtifactInfoByID(i_artifactId).UnsavedBoostInfos;
	return getCurrentBoostInfo(i_artifactId, boostInfos, -1);
}

void ArtifactMgr::ConstructBoostInfos(const Network_ArtifactImprovedPropertySheet* props, std::vector<NetworkArtifactBoostData>& i_outs, const std::vector<int>& i_ins)
{
	std::vector<int>::const_iterator it = i_ins.begin();
	std::vector<int>::const_iterator end = i_ins.end();
	for (; it != end; ++it)
	{
		NetworkArtifactBoostData boost = GetNetworkBoostById(props, *it);
		if (boost.Id != -1)
			i_outs.push_back(boost);
	}
}

float ArtifactMgr::GetBoostValue(int i_artifactId, ArtifactBoostType i_type)
{
	bool canShare = true;
	float sharedValue = 0.0f;
	ProfileMgr::GetInstance().GetCurrentProfile();
	const std::map<std::string, int>& artifacts = ArtifactMapper::GetInstance().GetMap();
	std::map<std::string, int>::const_iterator it;
	it = artifacts.begin();
	float result = sharedValue;
	for (; it != artifacts.end(); ++it)
	{
		if (it->second == i_artifactId)
		{
			float rareValue = GetBoostValue(i_artifactId, i_type, 3);
			if (rareValue != 0.0f)
			{
				sharedValue = 0.0f;
				canShare = false;
			}
			result = GetBoostValue(i_artifactId, i_type, -1) + rareValue;
		}
		else if (sharedValue == 0.0f && canShare && !IsUnsharedBoost(i_type))
		{
			canShare = true;
			sharedValue = GetBoostValue(it->second, i_type, 3);
		}
	}
	return result + sharedValue;
}

void ArtifactMgr::InitDefaultImprovedProps()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ARTIFACTIMPROVEDPROPERTIES); it; ++it)
	{
		ArtifactImprovedPropertySheet* sheet = NULL;
		{
			Sexy::RtId id = *it;
			ArtifactImprovedPropertySheetPtr candidate(id);
			if (candidate)
			{
				Sexy::RtId sheetId = *it;
				ArtifactImprovedPropertySheetPtr props(sheetId);
				sheet = props.GetObject()->Cast<ArtifactImprovedPropertySheet>();
			}
		}
		if (sheet != NULL)
		{
			ArtifactImprovedPropertySheet* copy = new ArtifactImprovedPropertySheet();
			copy->Copy(*sheet);
			m_improvedProps.push_back(copy);
		}
	}
}

int ArtifactMgr::GetGlobalExtraValue(float& i_outValue, int i_plantId, int i_type, int i_currentArtifactId)
{
	int result = -1;
	float total = 0.0f;
	std::string plantName = PlantNameMapper::GetInstance().GetNameForId(i_plantId);
	const std::map<std::string, int>& artifacts = ArtifactMapper::GetInstance().GetMap();
	std::map<std::string, int>::const_iterator it;
	it = artifacts.begin();
	for (; it != artifacts.end(); ++it)
	{
		if (it->second != i_currentArtifactId && GetBoostValue(it->second, Global_Passive1, 3) > 0.0f)
		{
			result = it->second;
			total += getExtraValue(plantName, result, i_type);
		}
	}
	i_outValue = total;
	return result;
}

float ArtifactMgr::getExtraValue(const std::string& i_plantName, int i_currentArtifactId, int i_boostType)
{
	PlantTypePtr plantType = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(i_plantName);
	ArtifactPropertiesPtr props = GetArtifactByTypeId(i_currentArtifactId);
	float result = 0.0f;
	if (props && hasPlantBoost(props->Boosts, i_boostType))
	{
		if ((i_boostType & ~2) == 4)
		{
			if (!props.Get()->TargetablePlantTypes.IsIncluded((const PlantType*)plantType))
				goto done;
		}
		else if (i_boostType != 8 && i_boostType != 10)
			goto done;
		{
			ArtifactPropertiesPtr copy((const RtWeakPtrBase&)props);
			result = CalculateFieldValue(copy, PassiveField1, 0) * 0.01f;
		}
	}
done:
	return result;
}

bool ArtifactMgr::SyncLocalProps(const Network_ArtifactImprovedPropertySheet* props, int i_artifactId, const std::vector<int>& i_infos)
{
	std::vector<ArtifactImprovedPropertySheet*>::iterator it = std::find_if(m_improvedProps.begin(), m_improvedProps.end(),
		[i_artifactId](ArtifactImprovedPropertySheet* i_props) { return i_props->ArtifactId == i_artifactId; });
	if (it != m_improvedProps.end())
	{
		std::vector<NetworkArtifactBoostData> boosts;
		ConstructBoostInfos(props, boosts, i_infos);
		(*it)->SyncNetwork(boosts);
	}
	else
	{
		ArtifactImprovedPropertySheet* sheet = new ArtifactImprovedPropertySheet();
		sheet->ArtifactId = i_artifactId;
		std::vector<NetworkArtifactBoostData> boosts;
		ConstructBoostInfos(props, boosts, i_infos);
		sheet->SyncNetwork(boosts);
		m_improvedProps.push_back(sheet);
	}
	return true;
}

void ArtifactMgr::RecomputeEntityValues()
{
	if (gLawnApp->m_board && gLawnApp->m_board->IsDangerRoom())
	{
		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesOnBoard(entities, ENTITYTYPE_PLANT);
		std::vector<BoardEntity*>::iterator it = entities.begin();
		std::vector<BoardEntity*>::iterator end = entities.end();
		for (; it != end; ++it)
		{
			Plant* plant = (*it)->Cast<Plant>();
			if (plant)
			{
				int plantId = PlantNameMapper::GetInstance().GetIdForType(plant->GetType());
				plant->SetExtraHpRate(PlantBoostMgr::GetInstance().GetPlantBoostValue(plantId, EXTRA_HITPOINTS) + 1.0f);
				plant->Heal();
				plant->SetExtraNormalDamge(PlantBoostMgr::GetInstance().GetPlantBoostValue(plantId, EXTRA_ATTACK) + 1.0f);
			}
		}
	}
}

std::vector<CurrentArtifactBoostInfo> ArtifactMgr::getCurrentBoostInfo(int i_artifactId, const std::vector<ArtifactBoostInfo>& i_boostInfos, int i_rare)
{
	std::vector<CurrentArtifactBoostInfo> result;
	std::vector<ArtifactBoostInfo>::const_iterator it = i_boostInfos.begin();
	std::vector<ArtifactBoostInfo>::const_iterator end = i_boostInfos.end();
	for (; it != end; ++it)
	{
		const ArtifactBoostInfo& boost = *it;
		ArtifactBoostPropertySheetPtr sheet = getBoostSheet(i_artifactId, boost.BoostId);
		if (sheet && (i_rare == -1 || i_rare == sheet->Rare))
		{
			result.push_back(CurrentArtifactBoostInfo(sheet->Name, sheet->Description, sheet->Type, sheet->Rare, boost.BoostId, boost.Value));
		}
	}
	return result;
}

float ArtifactMgr::GetBoostValue(int i_artifactId, ArtifactBoostType i_type, int rare)
{
	float result;
	std::vector<ArtifactBoostInfo> boostInfos = ProfileMgr::GetInstance().GetCurrentProfile()->GetArtifactInfoByID(i_artifactId).BoostInfos;
	std::vector<ArtifactBoostInfo>::iterator it = boostInfos.begin();
	std::vector<ArtifactBoostInfo>::iterator end = boostInfos.end();
	for (; it != end; ++it)
	{
		const ArtifactBoostInfo& boost = *it;
		ArtifactBoostPropertySheetPtr sheet = getBoostSheet(i_artifactId, boost.BoostId);
		if (sheet && sheet->Type == i_type)
		{
			if (rare == -1 && sheet->Rare != 3)
			{
				result = boost.Value;
				if (result != 0.0f)
					return result;
			}
			else if (rare == sheet->Rare)
			{
				result = boost.Value;
				if (result != 0.0f)
					return result;
			}
		}
	}
	result = 0.0f;
	return result;
}

bool ArtifactMgr::needRequestTriggerArtifact()
{
	if (GetActivatedArtifact()->GetProps()->TypeName == "artifact_prismtower")
		return false;
	if (GetActivatedArtifact()->GetProps()->TypeName == "artifact_beehive")
		return false;
	if (GetActivatedArtifact()->GetProps()->TypeName == "artifact_acid")
		return false;
	if (GetActivatedArtifact()->GetProps()->TypeName == "artifact_swarm")
		return false;
	if (GetActivatedArtifact()->GetProps()->TypeName == "artifact_calabash")
		return false;
	if (gLawnApp->m_board && IsDangerRoom())
		return true;
	return false;
}

void ArtifactMgr::GetRealExpression(std::string& i_field, int i_id)
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	{
		std::allocator<char> alloc;
		std::string level("level", alloc);
		if (m_currentArtifact.PropsPtr)
			i_field = ArtifactUtils::ReplaceParameterEx(i_field, level, m_currentArtifact.CurrentLevel);
		else
			i_field = ArtifactUtils::ReplaceParameterEx(i_field, level, profile->GetArtifactInfoByID(i_id).Level);
	}
	{
		std::allocator<char> alloc;
		std::string stage("stage", alloc);
		if (m_currentArtifact.PropsPtr)
			i_field = ArtifactUtils::ReplaceParameterEx(i_field, stage, m_currentArtifact.CurrentStage);
		else
			i_field = ArtifactUtils::ReplaceParameterEx(i_field, stage, profile->GetArtifactInfoByID(i_id).Rank);
	}
}

void ArtifactMgr::TrySyncArtifact()
{
	RemoveActivatedArtifact();
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (profile->GetActiveTutorial() == TUTORIAL_ARTIFACT)
	{
		profile->CompleteTutorial(TUTORIAL_ARTIFACT);
		int artifactId = ArtifactMapper::GetInstance().GetIdForName("artifact_wind");
		SyncArtifact(artifactId, 30, 4);
		return;
	}
	if (profile->GetCurrentLevel().find("Artifact_Demo_") != std::string::npos)
	{
		std::string name = "artifact_" + Sexy::StringToLower(profile->GetCurrentLevel().substr(14));
		int artifactId = ArtifactMapper::GetInstance().GetIdForName(name);
		Sexy::OutputDebugStrF("ArtifactMgr::TrySyncArtifact %s %s", profile->GetCurrentLevel().c_str(), name.c_str());
		SyncArtifact(artifactId, 30, 4);
		return;
	}
	int artifactId = profile->GetCurrentArtifact();
	if (artifactId != 0)
	{
		int level = profile->GetArtifactInfoByID(artifactId).Level;
		int stage = profile->GetArtifactInfoByID(artifactId).Rank;
		SyncArtifact(artifactId, level, stage);
	}
	gMessageRouter->Post(&Message::ActionComplete);
}

void ArtifactMgr::RequestTriggerArtifact()
{
	if (m_activatedArtifact && !m_activatedArtifact->CanStartBuff())
		return;
	if (!needRequestTriggerArtifact())
	{
		TriggerArtifact(GetActivatedArtifactUsedTime() + 1);
		gMessageRouter->Post(&Message::ArtifactTrigger);
		return;
	}
	int type = 0;
	if (gLawnApp->m_board)
	{
		if (gLawnApp->m_board->IsDangerRoom())
			type = 1;
		else if (gLawnApp->m_board->GetLevelDefinition()->IsJoust)
			type = 3;
		else if (RiftUtils::IsPlayingRiftLevel())
			type = 2;
	}
	std::map<std::string, std::string> params;
	params["on"] = GetOrderId();
	params["t"] = DString(type).c_str();
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_TRIGGER_ARTIFACT, params, 30.0f, [this](const std::string& i_response)
	{
	}, true, true, "[NET_CONNECTING]", 0);
}

bool ArtifactMgr::artifactDisabled()
{
	if (gLawnApp->m_board)
	{
		if (gLawnApp->m_board->GetLevelDefinition()->IsWorldCup)
			return true;
		if (gLawnApp->m_board->GetLevelDefinition()->IsVasebreaker)
			return true;
		if (gLawnApp->m_board->GetLevelDefinition()->IsMiniGameMode)
			return true;
		if (gLawnApp->m_board->GetLevelDefinition()->IsArenaBattle)
			return true;
		if (gLawnApp->m_board->GetLevelDefinition()->IsArenaEdit)
			return true;
		if (gLawnApp->m_board->GetLevelDefinition()->IsArtifactDisabled)
			return true;
		if (gLawnApp->m_board->IsCurrentLevelBeghouled())
			return true;
		if (CustomLevelUtils::IsCustomLevel())
			return true;
		if (CardGameUtils::IsPlayingCardGame())
			return true;
		if (NewPVPUtils::IsPlayingNewPVP())
			return true;
		if (PlantWarsUtils::IsPlayingPlantWarsLevel())
			return true;
		if (MiniGameCollectionUtils::IsPlayingMiniGameCollectionLevel())
			return true;
	}
	if (gLawnApp->m_board->m_levelModuleManager->GetModuleByClass<SkyCityStage>())
		return true;
	if (gLawnApp->m_board->m_levelModuleManager->GetModuleByClass<RunningSubwayStage>())
		return true;
	if (gLawnApp->m_board->m_levelModuleManager->GetModuleByClass<ArenaPlantModule>())
		return true;
	if (gLawnApp->m_board->m_levelModuleManager->GetModuleByClass<IntroArenaTutorialBattleModule>())
		return true;
	if (BoardHelpers::ApplyLevelBasedModifierValue(1.0f, LevelBasedModifier_DefaultArtifactUseTimes, -1, 0) == 0.0f)
		return true;
	std::string levelName = "";
	if (gLawnApp->m_board)
		levelName = gLawnApp->m_board->GetLevel();
	Sexy::RtId id = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_LEVELMODULES, Sexy::RtName(_S("ArtifactModuleProps")));
	Sexy::RtWeakPtr<ArtifactModuleProperties> props(id);
	if (props)
	{
		std::vector<std::string>& blacklist = props->LevelBlacklist;
		std::vector<std::string>::iterator it = blacklist.begin();
		std::vector<std::string>::iterator end = blacklist.end();
		for (; end != it; ++it)
		{
			std::string name(*it);
			if (name == levelName)
				return true;
		}
	}
	return false;
}

std::vector<CurrentArtifactBoostInfo> ArtifactMgr::GetCurrentGlobalBoostInfo(int i_artifactId)
{
	std::vector<CurrentArtifactBoostInfo> result;
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	const std::map<std::string, int>& artifacts = ArtifactMapper::GetInstance().GetMap();
	std::map<std::string, int>::const_iterator it;
	it = artifacts.begin();
	for (; it != artifacts.end(); ++it)
	{
		std::vector<ArtifactBoostInfo> infos = profile->GetArtifactInfoByID(it->second).BoostInfos;
		std::vector<CurrentArtifactBoostInfo> boosts = getCurrentBoostInfo(i_artifactId, infos, 3);
		std::vector<CurrentArtifactBoostInfo>::iterator boost = boosts.begin();
		while (boost != boosts.end())
		{
			if (boost->Rare == 3 && (boost->Type == Global_Passive1 || IsUnsharedBoost(boost->Type)))
			{
				boost = boosts.erase(boost);
				continue;
			}
			bool dup = false;
			size_t count = result.size();
			size_t i = 0;
			while (i != count)
			{
				if ((*boost).Type == result[i].Type)
				{
					dup = true;
					break;
				}
				i++;
			}
			if (dup)
				boost = boosts.erase(boost);
			else
				++boost;
		}
		result.insert(result.end(), boosts.begin(), boosts.end());
	}
	return result;
}

/////////////// Plant boosts ///////////////

bool hasTargetBoostType(const std::vector<PlantBoost>& i_boosts, PlantBoostType i_boostType);

void ArtifactMgr::GetArtifactBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType)
{
	gMessageRouter->Post(&Message::GetArtifactBoosts, i_plantID, (int)i_boostType);
	if (m_tempBoostValue == 0.0f)
		return;
	ArtifactPropertiesPtr& cur = m_currentArtifact.PropsPtr;
	if (cur)
	{
		std::vector<PlantBoost>::iterator it = cur->Boosts.begin(), end = cur->Boosts.end();
		for (; it != end; ++it)
		{
			PlantBoost& boost = *it;
				if (boost.PlantBoostProps && boost.PlantBoostProps->Type == i_boostType)
			{
				boost.Values[0] = m_tempBoostValue;
				i_Boosts.push_back(&boost);
		}
		}
		it = cur->GlobalBoosts.begin();
		end = cur->GlobalBoosts.end();
		for (; it != end; ++it)
		{
			PlantBoost& boost = *it;
				if (boost.PlantBoostProps && boost.PlantBoostProps->Type == i_boostType && !hasTargetBoostType(cur->Boosts, i_boostType))
			{
				boost.Values[0] = m_tempBoostValue;
				i_Boosts.push_back(&boost);
		}
		}
	}
	else if (m_globalArtifactId != -1)
	{
		ArtifactPropertiesPtr props = GetArtifactByTypeId(m_globalArtifactId);
		if (props)
		{
			std::vector<PlantBoost>::iterator it = props->Boosts.begin(), end = props->Boosts.end();
			for (; it != end; ++it)
			{
				PlantBoost& boost = *it;
				if (boost.PlantBoostProps && boost.PlantBoostProps->Type == i_boostType)
				{
					boost.Values[0] = m_tempBoostValue;
					i_Boosts.push_back(&boost);
				}
			}
			it = props->GlobalBoosts.begin();
			end = props->GlobalBoosts.end();
			for (; it != end; ++it)
			{
				PlantBoost& boost = *it;
				if (boost.PlantBoostProps && boost.PlantBoostProps->Type == i_boostType && !hasTargetBoostType(props->Boosts, i_boostType))
				{
					boost.Values[0] = m_tempBoostValue;
					i_Boosts.push_back(&boost);
				}
			}
		}
	}
}
