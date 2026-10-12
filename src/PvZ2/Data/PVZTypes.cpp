//
//  PVZTypes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVZTypes.h"
#include "PVZDB.h"
#include "ProjectilePropertySheet.h"
#include "ZombieType.h"
#include "Zombie.h"
#include "CreatureType.h"
#include "Creature.h"
#include "WorldData.h"
#include "WorldMapUtils.h"
#include "MapEventItem.h"
#include "LevelUtils.h"
#include "LevelDefinition.h"
#include "LevelModule.h"
#include "StageModule.h"
#include "PlantType.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantHeadshot.h"
#include "MagentoService.h"
#include "CollectableType.h"
#include "ObjectTypeDirectory.h"
#include "UIEditor/StringHelper.h"
#include "LawnApp.h"

PVZTypes::PVZTypes()
{
}

PVZTypes::~PVZTypes()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZTypes);

void PVZTypes::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZTypes);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(PVZTypes);
}

/////////////// Verification ///////////////

void printVerificationMessage(const std::string& i_package, bool i_ok);

bool PVZTypes::VerifyProjectileTypes()
{
	Sexy::OutputDebugStrF("---------- Verifying contents of ProjectileTypes package...\n");
	std::map<std::string, RtWeakPtr<ProjectilePropertySheet> > contents;
	bool failed = false;
	for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROJECTILETYPES); (iter); ++(iter))
	{
		RtWeakPtr<ProjectilePropertySheet> sheet = *iter;
		std::string rtid;
		sheet.GetId().ToString(rtid, false);
		RtClass* sheetClass = sheet->GetClass();
		if (!sheetClass->IsDerivedFrom(ProjectilePropertySheet::StaticGetClass()))
		{
			failed = true;
			Sexy::OutputDebugStrF("Warning: Non-ProjectilePropertySheet object in table (type: %s, RTID: %s)!\n", sheetClass->GetName(), rtid.c_str());
		}
	}
	printVerificationMessage("ProjectileTypes", false);
	return !failed;
}

bool PVZTypes::VerifyZombieTypes()
{
	Sexy::OutputDebugStrF("---------- Verifying contents of ZombieTypes package...\n");
	std::map<std::string, RtWeakPtr<const ZombieType> > contents;
	bool failed = false;
	for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIETYPES); (iter); ++(iter))
	{
		RtWeakPtr<const ZombieType> zombieType = *iter;
		RtClass* typeClass = zombieType->GetClass();
		std::string rtid;
		zombieType.GetId().ToString(rtid, false);
		if (!typeClass->IsDerivedFrom(ZombieType::StaticGetClass()))
		{
			failed = true;
			Sexy::OutputDebugStrF("Warning: Non-ZombieType object in table (type: %s, RTID: %s)!\n", typeClass->GetName(), rtid.c_str());
			continue;
		}
		RtWeakPtr<const ZombieType> entry = zombieType;
		const ZombieType* type = entry;
		if (type->TypeName.size() == 0)
		{
			failed = true;
			Sexy::OutputDebugStrF("ERROR: Empty TypeName on ZombieType object %s!\n", rtid.c_str());
			continue;
		}
		std::map<std::string, RtWeakPtr<const ZombieType> >::iterator found = contents.find(type->TypeName);
		bool duplicate = found != contents.end();
		if (duplicate)
		{
			failed = true;
			RtWeakPtr<const ZombieType> first = (*found).second;
			std::string firstRtid;
			first.GetId().ToString(firstRtid, false);
			Sexy::OutputDebugStrF("ERROR: Duplicate TypeName on ZombieType object (First RTID: %s, Duplicate RTID: %s)!\n", firstRtid.c_str(), rtid.c_str());
			continue;
		}
		contents[type->TypeName] = entry;
		Sexy::OutputDebugStrF("Verifying ZombieType '%s' %s... ", type->TypeName.c_str(), rtid.c_str());
		if (__builtin_expect(!!(!type->Enabled), 1))
		{
			Sexy::OutputDebugStrF("\n Zombie %s not enabled in game!\n", type->TypeName.c_str());
			continue;
		}
		bool typeFailed = duplicate;
		if (type->ZombieClass.size() != 0)
		{
			RtClass* zombieClass = RtClass::StaticGetClassNamed(type->ZombieClass.c_str());
			if (__builtin_expect(!!(zombieClass == NULL), 0))
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: ZombieClass class '%s' does not exist!\n", type->ZombieClass.c_str());
			}
			else if (__builtin_expect(!!(!zombieClass->IsDerivedFrom(Zombie::StaticGetClass())), 0))
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: ZombieClass class '%s' valid but does not from Zombie!\n", type->ZombieClass.c_str());
			}
		}
		else
			Sexy::OutputDebugStrF("\n ERROR: ZombieClass is not set!\n");
		RtWeakPtr<ZombiePropertySheet> props = type->Properties;
		if (__builtin_expect(!!(props.GetId().GetValue() == 0), 0))
		{
			typeFailed = true;
			Sexy::OutputDebugStrF("\n Error: Empty Properties value!\n");
		}
		else if (!props.IsValid())
		{
			typeFailed = true;
			std::string propsRtid;
			props.GetId().ToString(propsRtid, false);
			Sexy::OutputDebugStrF("\n ERROR: Properties value %s invalid!\n", propsRtid.c_str());
		}
		if (type->GetArtResourceGroups().size() == 0)
			Sexy::OutputDebugStrF("\n WARNING: No ResourceGroups specified!\n");
		else
		{
			const std::vector<std::string>& artGroups = type->GetArtResourceGroups();
			if (artGroups.size() == 0)
				Sexy::OutputDebugStrF("\n WARNING: No ResourceGroups specified!\n");
			for (size_t i = 0; i < artGroups.size(); i++)
			{
				if (gLawnApp->mResourceManager->GetResourceGroupNamed(artGroups[i]) == NULL)
				{
					typeFailed = true;
					Sexy::OutputDebugStrF("\n ERROR: ResourceGroups entry named '%s' doesn't exist!\n", artGroups[i].c_str());
				}
			}
			const std::vector<std::string>& audioGroups = type->GetAudioGroups();
			for (size_t i = 0; i < audioGroups.size(); i++)
			{
				if (__builtin_expect(!!(gLawnApp->mResourceManager->GetResourceGroupNamed(audioGroups[i]) == NULL), 0))
				{
					typeFailed = true;
					Sexy::OutputDebugStrF("\n ERROR: Audio ResourceGroup entry named '%s' doesn't exist!\n", audioGroups[i].c_str());
				}
			}
		}
		failed |= typeFailed;
		if (__builtin_expect(!!(!typeFailed), 1))
			Sexy::OutputDebugStrF("\n OK!\n");
	}
	printVerificationMessage("ZombieTypes", failed);
	return !failed;
}

bool PVZTypes::VerifyCreatureTypes()
{
	std::map<std::string, RtWeakPtr<const CreatureType> > contents;
	bool failed = false;
	for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_CREATURETYPES); (iter); ++(iter))
	{
		RtWeakPtr<const CreatureType> creatureType = *iter;
		RtClass* typeClass = creatureType->GetClass();
		std::string rtid;
		creatureType.GetId().ToString(rtid, false);
		if (!typeClass->IsDerivedFrom(CreatureType::StaticGetClass()))
		{
			Sexy::OutputDebugStrF("Warning: Non-CreatureType object in table (type: %s, RTID: %s)!\n", typeClass->GetName(), rtid.c_str());
			failed = true;
			continue;
		}
		RtWeakPtr<const CreatureType> entry = creatureType;
		const CreatureType* type = entry;
		if (__builtin_expect(!!(type->TypeName.size() == 0), 0))
		{
			Sexy::OutputDebugStrF("ERROR: Empty TypeName on CreatureType object %s!\n", rtid.c_str());
			failed = true;
			continue;
		}
		std::map<std::string, RtWeakPtr<const CreatureType> >::iterator found = contents.find(type->TypeName);
		if (found != contents.end())
		{
			RtWeakPtr<const CreatureType> first = (*found).second;
			std::string firstRtid;
			first.GetId().ToString(firstRtid, false);
			Sexy::OutputDebugStrF("ERROR: Duplicate TypeName on CreatureType object (First RTID: %s, Duplicate RTID: %s)!\n", firstRtid.c_str(), rtid.c_str());
			failed = true;
			continue;
		}
		contents[type->TypeName] = entry;
		bool typeFailed = false;
		if (__builtin_expect(!!(type->CreatureClass.size() == 0), 1))
			Sexy::OutputDebugStrF("\n ERROR: CreatureClass is not set!\n");
		else
		{
			RtClass* creatureClass = RtClass::StaticGetClassNamed(type->CreatureClass.c_str());
			if (__builtin_expect(!!(creatureClass == NULL), 1))
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: CreatureClass class '%s' does not exist!\n", type->CreatureClass.c_str());
			}
			else if (__builtin_expect(!!(!creatureClass->IsDerivedFrom(Creature::StaticGetClass())), 1))
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: CreatureClass class '%s' valid but does not from Creature!\n", type->CreatureClass.c_str());
			}
		}
		RtWeakPtr<ZombiePropertySheet> props = type->Properties;
		if (__builtin_expect(!!(props.GetId().GetValue() == 0), 0))
		{
			typeFailed = true;
			Sexy::OutputDebugStrF("\n Error: Empty Properties value!\n");
		}
		else if (!props.IsValid())
		{
			typeFailed = true;
			std::string propsRtid;
			props.GetId().ToString(propsRtid, false);
			Sexy::OutputDebugStrF("\n ERROR: Properties value %s invalid!\n", propsRtid.c_str());
		}
		if (__builtin_expect(!!(type->IsCreatureEnabled()), 0))
		{
			const std::vector<std::string>& artGroups = type->GetArtResourceGroups();
			if (artGroups.size() == 0)
				Sexy::OutputDebugStrF("\n WARNING: No ResourceGroups specified!\n");
			for (unsigned int i = 0; i < artGroups.size(); i++)
			{
				if (gLawnApp->mResourceManager->GetResourceGroupNamed(artGroups[i]) == NULL)
				{
					typeFailed = true;
					Sexy::OutputDebugStrF("\n ERROR: ResourceGroups entry named '%s' doesn't exist!\n", artGroups[i].c_str());
				}
			}
			const std::vector<std::string>& audioGroups = type->GetAudioGroups();
			for (size_t i = 0; i < audioGroups.size(); i++)
			{
				if (gLawnApp->mResourceManager->GetResourceGroupNamed(audioGroups[i]) == NULL)
				{
					typeFailed = true;
					Sexy::OutputDebugStrF("\n ERROR: Audio ResourceGroup entry named '%s' doesn't exist!\n", audioGroups[i].c_str());
				}
			}
		}
		const std::vector<std::string> audioCopy = type->GetAudioGroups();
		size_t n = audioCopy.size();
		for (size_t i = 0; i < n; i++)
		{
			if (gLawnApp->mResourceManager->GetResourceGroupNamed(audioCopy[i]) == NULL)
			{
				std::string propsId;
				props.GetId().ToString(propsId, false);
				if (__builtin_expect(!!(type->IsCreatureEnabled()), 0))
				{
					typeFailed = true;
					Sexy::OutputDebugStrF("\n ERROR: AudioGroups entry named '%s' doesn't exist!\n", audioCopy[i].c_str());
				}
			}
		}
		failed |= typeFailed;
	}
	printVerificationMessage("ZombieTypes", failed);
	return !failed;
}

bool PVZTypes::VerifyWorldMapAndLevels()
{
	Sexy::OutputDebugStrF("---------- Verifying WorldMapList...\n");
	bool failed = false;
	const WorldMapList* mapList = WorldMapUtils::GetWorldMapList();
	for (size_t worldIdx = 0; worldIdx < mapList->MapList.size(); worldIdx++)
	{
		WorldData* world = WorldMapUtils::GetWorldDataForEdit()->FindWorldDataByIndexInMapList(worldIdx);
		if (world == NULL)
			continue;
		for (size_t eventIdx = 0; eventIdx < world->m_eventList.size(); eventIdx++)
		{
			MapEventItem* event = &world->m_eventList[eventIdx];
			if (event->GetEventType() != MAPEVENT_LEVEL_ENTRANCE)
				continue;
			std::string levelName = event->GetDataString();
			const std::string& eventName = event->GetName();
			Sexy::OutputDebugStrF("Verifying Map Event (name: %s) hook to Level: %s...\n", eventName.c_str(), levelName.c_str());
			if (!Sexy::LazySingleton<LevelUtils>::GetInstance().DoesLevelExist(levelName))
			{
				failed = true;
				Sexy::OutputDebugStrF("  ERROR: Map Event (name: %s) is of type 'level' but does not reference a valid level! Level name: %s\n", eventName.c_str(), levelName.c_str());
				continue;
			}
			LevelDefinitionPtr level = Sexy::LazySingleton<LevelUtils>::GetInstance().LoadLevelDefinition(levelName, true);
			if (!level.IsValid())
			{
				failed = true;
				Sexy::OutputDebugStrF("  ERROR: Map Event (name: %s) failed to properly load level with name '%s'!\n", eventName.c_str(), levelName.c_str());
				continue;
			}
			const LevelDefinition* def = level;
			if (def->RandomLevelSet.size() == 0)
			{
				if (!static_cast<bool>(def->StageModule.GetId()))
				{
					failed = true;
					Sexy::OutputDebugStrF("  ERROR: Level (name: %s) doesn't have a StageModule!\n", levelName.c_str());
					continue;
				}
				if (!def->StageModule.IsValid())
				{
					failed = true;
					Sexy::OutputDebugStrF("  ERROR: Level (name: %s) has a StageModule specified, but it's not valid!\n", levelName.c_str());
					continue;
				}
				const RtObject* stage = def->StageModule.GetObject();
				if (!stage->IsA(StageModuleProperties::StaticGetClass()))
				{
					failed = true;
					Sexy::OutputDebugStrF("  ERROR: Level (name: %s) has a StageModule specified, but it's not of class StageModuleProperties! Instead, it is a '%s'\n", levelName.c_str(), stage->GetClass()->GetName());
					continue;
				}
			}
			for (int moduleIdx = 0; moduleIdx < def->Modules.size(); moduleIdx++)
			{
				RtId moduleId = def->Modules[moduleIdx];
				if (!(static_cast<bool>(moduleId)))
				{
					failed = true;
					Sexy::OutputDebugStrF("  ERROR: Level (name: %s) has an empty entry in its Modules list (index %d)!\n", levelName.c_str(), moduleIdx);
				}
				else
				{
					LevelModulePropertiesPtr moduleProps = moduleId;
					if (!moduleProps.IsValid())
					{
						failed = true;
						Sexy::OutputDebugStrF("  ERROR: Level (name: %s) has an invalid entry in its Modules list (index %d)!\n", levelName.c_str(), moduleIdx);
					}
					else
					{
						const RtObject* moduleObj = moduleProps.GetObject();
						LevelModuleProperties* props = moduleObj ? moduleObj->Cast<LevelModuleProperties>() : NULL;
						if (props == NULL)
						{
							failed = true;
							Sexy::OutputDebugStrF("  ERROR: Level (name: %s) has an entry in its Modules list (index %d) that does not derive from LevelModuleProperties! Instead, it is a '%s'\n", levelName.c_str(), moduleIdx, moduleObj->GetClass()->GetName());
						}
						else
						{
							RtClass* moduleClass = props->GetModuleClass();
							if (moduleClass == NULL || !moduleClass->IsDerivedFrom(LevelModule::StaticGetClass()))
							{
								failed = true;
								Sexy::OutputDebugStrF("  ERROR: Level (name: %s) includes a LevelModuleProperties object (index: %d, class: %s) that DOES NOT specify a valid LevelModule class in GetModuleClass(). Tell a programmer!\n", levelName.c_str(), moduleIdx, props->GetClass()->GetName());
							}
						}
					}
				}
			}
			Sexy::OutputDebugStrF("... done\n");
		}
	}
	printVerificationMessage("WorldMapEvents", failed);
	Sexy::LazySingleton<LevelUtils>::GetInstance().UnloadLevelDefinition();
	return !failed;
}

bool PVZTypes::VerifyPlantTypes()
{
	Sexy::OutputDebugStrF("---------- Verifying contents of PlantTypes package...\n");
	gLawnApp->LoadGroup("UI_HeadShot_BigPlant");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	std::map<std::string, RtWeakPtr<const PlantType> > contents;
	bool failed = false;
	for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTTYPES); (iter); ++(iter))
	{
		RtWeakPtr<const PlantType> plantType = *iter;
		RtClass* typeClass = plantType->GetClass();
		std::string rtid;
		plantType.GetId().ToString(rtid, false);
		if (!typeClass->IsDerivedFrom(PlantType::StaticGetClass()))
		{
			failed = true;
			Sexy::OutputDebugStrF("Warning: Non-PlantType object in table (type: %s, RTID: %s)!\n", typeClass->GetName(), rtid.c_str());
			continue;
		}
		RtWeakPtr<const PlantType> entry = plantType;
		const PlantType* type = entry;
		if (type->TypeName.size() == 0)
		{
			failed = true;
			Sexy::OutputDebugStrF("ERROR: Empty TypeName on PlantType object %s!\n", rtid.c_str());
			continue;
		}
		std::map<std::string, RtWeakPtr<const PlantType> >::iterator found = contents.find(type->TypeName);
		if (found != contents.end())
		{
			RtWeakPtr<const PlantType> first = (*found).second;
			std::string firstRtid;
			first.GetId().ToString(firstRtid, false);
			Sexy::OutputDebugStrF("ERROR: Duplicate TypeName on PlantType object (First RTID: %s, Duplicate RTID: %s)!\n", firstRtid.c_str(), rtid.c_str());
			failed = true;
			continue;
		}
		contents[type->TypeName] = entry;
		Sexy::OutputDebugStrF("Verifying PlantType '%s' %s... ", type->TypeName.c_str(), rtid.c_str());
		if (!type->Enabled)
		{
			Sexy::OutputDebugStrF("\n Plant %s is not enabled in game!\n", type->TypeName.c_str());
			continue;
		}
		bool typeFailed = false;
		if (type->PlantFramework.size() == 0)
		{
			typeFailed = true;
			Sexy::OutputDebugStrF("\n ERROR: Empty PlantFramework field!\n");
		}
		RtClass* frameworkClass = RtClass::StaticGetClassNamed(type->PlantFramework.c_str());
		if (frameworkClass == NULL)
		{
			typeFailed = true;
			Sexy::OutputDebugStrF("\n ERROR: PlantFramework class '%s' does not exist!\n", type->PlantFramework.c_str());
		}
		else if (!frameworkClass->IsDerivedFrom(PlantFramework::StaticGetClass()))
		{
			typeFailed = true;
			Sexy::OutputDebugStrF("\n ERROR: PlantFramework class '%s' is valid but does not derive from PlantFramework!\n", type->PlantFramework.c_str());
		}
		RtWeakPtr<PlantPropertySheet> props = type->Properties;
		if (props.GetId().GetValue() == 0)
		{
			typeFailed = true;
			Sexy::OutputDebugStrF("\n ERROR: No PlantPropertySheet specified!\n");
		}
		if (__builtin_expect(!!(props.IsValid()), 1))
		{
			if (static_cast<PlantPropertySheet*>(props.GetObject())->MinLevel == 0 || static_cast<PlantPropertySheet*>(props.GetObject())->MaxLevel == 0)
			{
				typeFailed = true;
				std::string propsRtid;
				props.GetId().ToString(propsRtid, false);
				Sexy::OutputDebugStrF("\n ERROR: Properties value %s for MinLevel or MaxLevel is invalid!\n", propsRtid.c_str());
			}
			if (static_cast<PlantPropertySheet*>(props.GetObject())->PlantLevelStats.size() < (size_t)static_cast<PlantPropertySheet*>(props.GetObject())->MaxLevel)
			{
				typeFailed = true;
				std::string propsRtid;
				props.GetId().ToString(propsRtid, false);
				Sexy::OutputDebugStrF("\n ERROR: Properties value %s for PlantLevelStats has something wrong on config!\n", propsRtid.c_str());
			}
			const int& maxLevel = static_cast<PlantPropertySheet*>(props.GetObject())->MaxLevel;
			int statCount = static_cast<PlantPropertySheet*>(props.GetObject())->PlantLevelStats.size();
			int levelCount = std::min(maxLevel, statCount);
			for (int i = 0; i < levelCount; i++)
			{
				RtWeakPtr<SkillPropertySheet> propertySkill = static_cast<PlantPropertySheet*>(props.GetObject())->PlantLevelStats[i].PropertySkillType;
				RtWeakPtr<SkillPropertySheet> advancedSkill = static_cast<PlantPropertySheet*>(props.GetObject())->PlantLevelStats[i].AdvancedSkillType;
				bool hasProperty = propertySkill.GetId().GetValue() != 0;
				if (hasProperty && !propertySkill.IsValid())
				{
					std::string skillRtid;
					propertySkill.GetId().ToString(skillRtid, false);
					Sexy::OutputDebugStrF("\n ERROR: Properties value %s is not configured in SkillTypes.json!\n", skillRtid.c_str());
					typeFailed = true;
					break;
				}
				bool hasAdvanced = advancedSkill.GetId().GetValue() != 0;
				if (hasAdvanced && !advancedSkill.IsValid())
				{
					std::string skillRtid;
					advancedSkill.GetId().ToString(skillRtid, false);
					Sexy::OutputDebugStrF("\n ERROR: Properties value %s is not configured in SkillTypes.json!\n", skillRtid.c_str());
					typeFailed = true;
					break;
				}
			}
		}
		if (type->PlantPieceEnabled)
		{
			bool hasConfig = false;
			MagentoCategoryPropsPtr levelUp = Magento::GetPlantLevelUp();
			bool detailedMissing = false;
			for (std::vector<MagentoProductPropsPtr>::iterator it = levelUp->Products.begin(); it != levelUp->Products.end(); ++it)
			{
				MagentoProductPropsPtr product = *it;
				std::string productRtid;
				product.GetId().ToString(productRtid, false);
				if (productRtid.find(type->TypeName, 0) == std::string::npos)
					continue;
				if (!product.IsValid())
				{
					typeFailed = true;
					Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for DETAILED level up in magento!\n", type->TypeName.c_str());
					detailedMissing = true;
					break;
				}
				hasConfig = true;
			}
			if (__builtin_expect(!!(!detailedMissing && !hasConfig), 0))
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for level up in magento!\n", type->TypeName.c_str());
			}
		}
		if (type->AvatarEnabled)
		{
			bool hasConfig = false;
			MagentoCategoryPropsPtr avatars = Magento::GetPlantPieceProductsData(true);
			bool detailedMissing = false;
			for (std::vector<MagentoProductPropsPtr>::iterator it = avatars->Products.begin(); it != avatars->Products.end(); ++it)
			{
				MagentoProductPropsPtr product = *it;
				std::string productRtid;
				product.GetId().ToString(productRtid, false);
				if (productRtid.find(type->TypeName, 0) == std::string::npos)
					continue;
				if (__builtin_expect(!!(!product.IsValid()), 0))
				{
					typeFailed = true;
					Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for DETAILED avatar in magento!\n", type->TypeName.c_str());
					detailedMissing = true;
					break;
				}
				hasConfig = true;
			}
			if (!hasConfig && !detailedMissing)
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for avatar in magento!\n", type->TypeName.c_str());
			}
		}
		if (StringHelper::ToImage(PlantHeadshot::PlantBigPrefix + Sexy::StringToUpper(type->TypeName), false) == NULL)
		{
			typeFailed = true;
			Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have image in UI_HeadShot_BigPlant!\n", type->TypeName.c_str());
		}
		if (type->PlantPieceEnabled)
		{
			if (type->PlantPieceImageName.empty())
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for plant piece image in PlantTypes.json!\n", type->TypeName.c_str());
			}
			else if (StringHelper::ToImage(type->PlantPieceImageName, false) == NULL)
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have plant piece image in PlantTypes.json!\n", type->TypeName.c_str());
			}
			std::string pieceName = "plant_piece_" + type->TypeName;
			RtWeakPtr<const CollectableType> piece = Sexy::LazySingleton<ObjectTypeDirectory<CollectableType> >::GetInstancePtr()->GetTypeFromTypeName(pieceName);
			if (!piece)
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for plant piece in CollectableTypes.json!\n", type->TypeName.c_str());
			}
			else if (piece->StandaloneImage.empty())
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have StandaloneImage in CollectableType.json!\n", type->TypeName.c_str());
			}
			else if (StringHelper::ToImage(piece->StandaloneImage, false) == NULL)
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have Piece StandaloneImage in CollectableType.json!\n", type->TypeName.c_str());
			}
		}
		if (__builtin_expect(!!(type->AvatarEnabled), 1))
		{
			if (type->AvatarPieceImageName.empty())
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for avatar piece image in PlantTypes.json!\n", type->TypeName.c_str());
			}
			else if (StringHelper::ToImage(type->AvatarPieceImageName, false) == NULL)
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have avatar piece image in PlantTypes.json!\n", type->TypeName.c_str());
			}
			std::string avatarName = "avatar_piece_" + type->TypeName;
			RtWeakPtr<const CollectableType> avatar = Sexy::LazySingleton<ObjectTypeDirectory<CollectableType> >::GetInstancePtr()->GetTypeFromTypeName(avatarName);
			if (!avatar)
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have config for avatar piece in CollectableTypes.json!\n", type->TypeName.c_str());
			}
			else if (__builtin_expect(!!(avatar->StandaloneImage.empty()), 0))
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have StandaloneImage in CollectableType.json!\n", type->TypeName.c_str());
			}
			else if (StringHelper::ToImage(avatar->StandaloneImage, false) == NULL)
			{
				typeFailed = true;
				Sexy::OutputDebugStrF("\n ERROR: Plant %s does not have Avatar StandaloneImage in CollectableType.json!\n", type->TypeName.c_str());
			}
		}
		failed |= typeFailed;
		if (typeFailed)
		{
			std::string propsRtid;
			props.GetId().ToString(propsRtid, false);
			Sexy::OutputDebugStrF("\n ERROR: Properties value %s invalid!\n", propsRtid.c_str());
		}
		else
		{
			Sexy::OutputDebugStrF("\n OK!\n");
		}
	}
	printVerificationMessage("PlantTypes", failed);
	gLawnApp->DeleteGroup("UI_HeadShot_BigPlant");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	return !failed;
}
