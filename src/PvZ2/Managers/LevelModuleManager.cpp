//
//  LevelModuleManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "LevelModuleManager.h"
#include "LawnApp.h"
#include "Board.h"
#include "CardGameUtils.h"
#include "NewPVPUtils.h"
#include "PVZDB.h"
#include "StageModule.h"
#include "LevelModule.h"
#include "PlantTrialConfig.h"
#include "LevelDefinition.h"
#include "RiftThemeMgr.h"
#include "ArtifactMgr.h"
#include "HeroPlantMgr.h"

#include "ReflectionBuilder.h"

/////////////// Accessors ///////////////

StageModule* LevelModuleManager::GetStageModule()
{
	return m_modules[0]->Cast<StageModule>();
}

bool LevelModuleManager::IsLoadComplete()
{
	return gLawnApp->IsGroupLoadComplete(std::vector<std::string>(m_resourceGroupNames.begin(), m_resourceGroupNames.end()));
}

/////////////// Logic ///////////////

void LevelModuleManager::AddRiftThemeModule()
{
	RiftThemeMgr::GetInstance().AddThemeModuleIfNeeded();
}

void LevelModuleManager::AddArtifactModuleIfNeeded()
{
	ArtifactMgr::GetInstance().AddArtifactModuleIfNeeded();
}

void LevelModuleManager::AddHeroPlantModulesIfNeeded()
{
	HeroPlantMgr::GetInstance().AddHeroPlantModuleIfNeeded();
}

void LevelModuleManager::StartLoad()
{
	for (int i = 0; i < m_modules.size(); i++)
		gatherModuleResources(m_modules[i], m_resourceGroupNames);

	gLawnApp->PrepareLoadGroups(std::vector<std::string>(m_resourceGroupNames.begin(), m_resourceGroupNames.end()));
	m_resourceGroupList.clear();
	m_resourceGroupList.insert(m_resourceGroupList.begin(), m_resourceGroupNames.begin(), m_resourceGroupNames.end());
}

void LevelModuleManager::Unload()
{
	gLawnApp->DeleteGroups(std::vector<std::string>(m_resourceGroupNames.begin(), m_resourceGroupNames.end()));
	m_resourceGroupNames.clear();
	m_resourceGroupList.clear();
}

void LevelModuleManager::CompleteLoad()
{
	gLawnApp->FinalizeGroupLoads(std::vector<std::string>(m_resourceGroupNames.begin(), m_resourceGroupNames.end()));
}

void LevelModuleManager::IncreaseRefCounts()
{
	gLawnApp->LoadGroups(std::vector<std::string>(m_resourceGroupNames.begin(), m_resourceGroupNames.end()));
}

void LevelModuleManager::ReduceRefCounts()
{
	gLawnApp->DeleteGroups(std::vector<std::string>(m_resourceGroupNames.begin(), m_resourceGroupNames.end()));
}

void LevelModuleManager::gatherModuleResources(LevelModule* i_module, std::set<std::string>& o_groupNames)
{
	i_module->AddResourceRequirements(o_groupNames);
	i_module->GetPropsPtr()->GatherResourceRequirements(o_groupNames);
	const char* className = i_module->GetClass()->GetName();
	if (gLawnApp->mResourceManager->GetResourceGroupNamed(className))
		o_groupNames.insert(className);
}

void LevelModuleManager::gatherModuleInstanceAndPropertySheetResources(LevelModule* i_module, std::set<std::string>& o_groupNames) const
{
	i_module->GetPropsPtr()->GatherResourceRequirements(o_groupNames);
}

LevelModule* LevelModuleManager::GetModuleByClass(RtClass* i_moduleClass)
{
	for (size_t i = 0; i < m_modules.size(); i++)
	{
		LevelModule* module = m_modules[i];
		if (module && module->IsA(i_moduleClass))
			return module;
	}
	return NULL;
}

void LevelModuleManager::PostLoad()
{
	m_resourceGroupNames.insert(m_resourceGroupList.begin(), m_resourceGroupList.end());
	TrialData* trialData = GetTrialDataInTheLevel();
	if (trialData)
		gLawnApp->GetPlantTrialConfig().SetTrialDataCache(*trialData);
}

void LevelModuleManager::UnloadAllZombies()
{
	for (std::vector<std::string>::iterator it = m_resourceGroupList.begin(); it != m_resourceGroupList.end();)
	{
		if (it->find("Zombie") == std::string::npos)
		{
			++it;
			continue;
		}
		gLawnApp->DeleteGroup(*it);
		m_resourceGroupNames.erase(*it);
		it = m_resourceGroupList.erase(it);
	}
}

LevelModule* LevelModuleManager::createLevelModule(RtWeakPtr<const LevelModuleProperties> i_levelModule)
{
	LevelModule* module = GameObject::Create(i_levelModule->GetModuleClass(), PVZDB::TABLE_LEVELMODULEINSTANCES)->CastChecked<LevelModule>();
	module->InitializeModule(i_levelModule);
	return module;
}

void LevelModuleManager::AddModuleFromProperties(RtWeakPtr<const LevelModuleProperties> i_levelModule)
{
	m_modules.push_back(createLevelModule(i_levelModule)->GetPtr());
}

LevelModule* LevelModuleManager::AddRuntimeModuleFromProperties(RtWeakPtr<const LevelModuleProperties> i_levelModule)
{
	LevelModule* module = createLevelModule(i_levelModule);
	m_runtimeModulesToAdd.push_back(module);
	return module;
}

void LevelModuleManager::addInitializedLevelModule(LevelModule* i_module)
{
	m_modules.push_back(i_module->GetPtr());
}

void LevelModuleManager::AddVictoryModule(RtWeakPtr<LevelDefinition> i_levelDef)
{
	AddRuntimeModuleFromProperties(i_levelDef->VictoryModule);
}

void LevelModuleManager::AddPlantTrialModule()
{
	TrialData* trialData = GetTrialDataInTheLevel();
	if (trialData)
	{
		AddModuleFromProperties(gLawnApp->GetPlantTrialConfig().GetPlantTrialProperties());
		gLawnApp->GetPlantTrialConfig().SetTrialDataCache(*trialData);
	}
}

void LevelModuleManager::AddHardLevelModule()
{
	RtId id = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_LEVELMODULES, RtName(_S("HardLevelProps")));
	RtWeakPtr<LevelModuleProperties> props(id);
	if (props)
		AddModuleFromProperties(props);
}

void LevelModuleManager::AddCardGameModulesIfNeeded()
{
	if (CardGameUtils::IsPlayingCardGame())
	{
		RtId id = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_LEVELMODULES, RtName(_S("CardGameBoardModuleProps")));
		RtWeakPtr<LevelModuleProperties> props(id);
		if (props)
			gLawnApp->m_board->GetLevelModuleManager()->AddModuleFromProperties(props);
	}
}

void LevelModuleManager::AddNewPVPGameModulesIfNeeded()
{
	if (NewPVPUtils::IsPlayingNewPVP())
	{
		RtId id = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_LEVELMODULES, RtName(_S("NewPVPGameModuleProps")));
		RtWeakPtr<LevelModuleProperties> props(id);
		if (props)
			gLawnApp->m_board->GetLevelModuleManager()->AddModuleFromProperties(props);
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(LevelModuleManager);
