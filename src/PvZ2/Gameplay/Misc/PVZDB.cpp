//
//  PVZDB.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVZDB.h"
#include "ResourceManager.h"
#include "SexyAppBase.h"
#include "IAntiHackDriver.h"
#include "GameObject.h"
#include "ArcadePropertySheet.h"
#include "SexyAppFramework/drivers/crashtracking/CrashTracking.h"
#include "PVZGameInfo.h"
#include "GameEventMgr.h"
#include "PVZRemoteControl.h"
#include "LawnApp.h"

extern Sexy::ResourceManager* gResourceManager;

class ArmorPropertySheet;
class ArmorPropertySheetUtils;
class ArtifactProperties;
class ArtifactTimeProperties;
class BoardPropertySheet;
class ButtercupProps;
class CardGameBoardConfig;
class ComponentWarmingRadiusGlobalProperties;
class CrownFlowerProps;
class CustomLevelConfig;
class DragonBabyBruitProps;
class DragonBruitProps;
class EASquaredPropertySheet;
class EMPeaProps;
class FirecrackerFlowerProps;
class GarlicProps;
class GeneralPlantChipsExchangeConfig;
class GridItemType;
class GumnutProps;
class HotUIConfig;
class JoustCrownRewardDefinition;
class JoustLeaderboardDefinition;
class JoustLevelSet;
class JoustProgressiveRewardDefinition;
class JoustPropertySheet;
class JoustSchedule;
class JoustTournamentRewardDefinition;
class LevelModifierModuleCollection;
class MiniGamePerkProperties;
class MusicalJamProperties;
class NPCDataSheet;
class NewPVPAreaProperties;
class PVZ1CopycatsModuleProperties;
class PVZ1ModePropertySheet;
class PennyPerkProperties;
class PennyPerkShockwaveProjectileProperties;
class PerkProgressionProperties;
class PlantPediaConfig;
class PlantPropertySheet;
class PlantTristerixAphyllusProps;
class PlantTypeIntensiveCarrot;
class ProbabilityConfig;
class ProjectilePropertySheet;
class RiftConfigSheet;
class RiftFirstClearRewards;
class RiftLevelUnlocksProperties;
class RiftPropertySheet;
class RiftSchedule;
class RiftSubEventProperties;
class RiftThemeProperties;
class RiftZombossRewards;
class TideEffectsProps;
class TorchwoodProps;
class UIWidgetSheet;
class WaveManagerProperties;
class WorldMapPropertySheet;
class ZombiePropertySheet;
class ZombieResistenceConfig;
class ZombieTitleProperties;

static std::string s_specialFolderName = "save";

/////////////// Lifecycle ///////////////

PVZDB::~PVZDB()
{
}

/////////////// Accessors ///////////////

bool PVZDB::IsInitialized() const
{
	return m_initialized;
}

RtDbTable* PVZDB::GetTable(TableIndex i_inTable)
{
	return RtDb::GetDb()->GetTable(i_inTable);
}

std::string PVZDB::GetTableName(TableIndex i_inTable)
{
	return getTableSchema(i_inTable).PrettyName;
}

void PVZDB::SetPackageLoaded(const TableIndex i_table, const bool i_value)
{
	getRuntimeInfo(i_table).PackageLoaded = i_value;
}

RtId PVZDB::GetIdByAlias(TableIndex i_inTable, RtName i_alias)
{
	return RtId(i_alias, getRuntimeInfo(i_inTable).TableName);
}

RtDbTable::Iterator PVZDB::GetObjectIteratorForTable(TableIndex i_inTable)
{
	RtDbTable* table = RtDb::GetDb()->GetTable(i_inTable);
	return RtDbTable::Iterator(table, table->GetSharedIteratorStorage());
}

/////////////// Logic ///////////////

bool PVZDB::isPredefinedTable(TableIndex i_tableIndex) const
{
	return (unsigned)i_tableIndex < TABLE_DYNAMIC_BEGIN;
}

bool PVZDB::isDynamicTable(TableIndex i_tableIndex) const
{
	return i_tableIndex >= TABLE_DYNAMIC_BEGIN;
}

bool PVZDB::isTableIndexValid(TableIndex i_tableIndex) const
{
	if (isPredefinedTable(i_tableIndex))
		return true;
	if (isDynamicTable(i_tableIndex) && i_tableIndex <= m_highestClaimedDynamicTableIndex)
		return std::find(m_freeDynamicTableIndices.begin(), m_freeDynamicTableIndices.end(), i_tableIndex) == m_freeDynamicTableIndices.end();
	return false;
}

PVZDB::TableSchema& PVZDB::getTableSchema(TableIndex i_tableIndex)
{
	if (isPredefinedTable(i_tableIndex))
		return m_PVZTableSchema[i_tableIndex];
	return m_dynamicTableSchema[i_tableIndex];
}

PVZDB::TableRuntimeInfo& PVZDB::getRuntimeInfo(TableIndex i_tableIndex)
{
	if (isPredefinedTable(i_tableIndex))
		return m_PVZTableRuntimeInfo[i_tableIndex];
	return m_dynamicTableRuntimeInfo[i_tableIndex];
}

void PVZDB::ReleaseDynamicTable(TableIndex i_tableIndex)
{
	m_freeDynamicTableIndices.push_back(i_tableIndex);
}

void PVZDB::ReleasePackageForTable(TableIndex i_table)
{
	TableRuntimeInfo& info = getRuntimeInfo(i_table);
	if (info.PackageLoaded)
	{
		RtDb::GetDb()->GetTable(i_table)->Reset(false);
		info.PackageLoaded = false;
	}
}

void PVZDB::ReleaseAllPackages()
{
	for (int i = 0; i < m_PVZTableSchema.size(); i++)
		ReleasePackageForTable(m_PVZTableSchema[i].Index);
}

void PVZDB::LoadDefaultPackageForTable(TableIndex i_table)
{
	const std::string& resource = getTableSchema(i_table).PackageResource;
	RtWeakPtr<GenericResFile> package = gResourceManager->GetResourceForStringIdT<GenericResFile>(resource, false);
	LoadPackageForTable(i_table, package);
}

void PVZDB::LoadAllPackages()
{
	int i = 0;
	while (i < m_PVZTableSchema.size())
	{
		TableSchema& schema = m_PVZTableSchema[i++];
		if (schema.PackageResource == "")
			continue;
		LoadDefaultPackageForTable(schema.Index);
	}
}

void PVZDB::LoadPackageForTable(TableIndex i_table, RtWeakPtr<GenericResFile> i_packageResource)
{
	TableSchema& schema = m_PVZTableSchema[i_table];
	TableRuntimeInfo& info = getRuntimeInfo(i_table);
	if (info.PackageLoaded)
		ReleasePackageForTable(i_table);

	RtDbTable* table = RtDb::GetDb()->GetTable(i_table);
	if (!table->LoadPackage(i_packageResource->GetFilePath(), true))
	{
		OutputDebugStrF("PVZDB::LoadPackageForTable - RtDbTable::LoadPackage Failure for Table (idx:%d, name:%s)", i_table, schema.PrettyName.c_str());
		return;
	}
	table->SetCurrentPackageName(schema.Name);
	info.PackageLoaded = true;
}

void PVZDB::RefreshPackageForTable(TableIndex i_table, RtWeakPtr<GenericResFile> i_packageResource)
{
	TableSchema& schema = m_PVZTableSchema[i_table];
	TableRuntimeInfo& info = getRuntimeInfo(i_table);
	if (info.PackageLoaded)
		ReleasePackageForTable(i_table);

	RtDbTable* table = RtDb::GetDb()->GetTable(i_table);
	if (!table->RefreshPackage(i_packageResource->GetFilePath(), true))
	{
		OutputDebugStrF("PVZDB::RefreshPackageForTable - RtDbTable::LoadPackage Failure for Table (idx:%d, name:%s)", i_table, schema.PrettyName.c_str());
		return;
	}
	table->SetCurrentPackageName(schema.Name);
	info.PackageLoaded = true;
}

bool PVZDB::LoadPackageForTableFromRTONFile(TableIndex i_table, const std::string& i_filename)
{
	Buffer fileBuffer;
	if (!i_filename.empty())
	{
		if (!gSexyAppBase->ReadBufferFromFile(i_filename, &fileBuffer, true))
			return false;
	}

	Buffer decodedBuffer;
	gSexyAppBase->mAntiHackDriver->DecodeBuffer(fileBuffer, decodedBuffer);
	RtSerialRtonReader reader(decodedBuffer.GetDataPtr(), decodedBuffer.GetDataLen());
	LoadPackageForTableFromBuffer(i_table, reader, false);
	return true;
}

bool PVZDB::LoadPackageForTableFromJson(TableIndex i_table, const std::string& i_json, bool i_stringUids)
{
	RtSerialBuffer buffer(NULL, 0);
	RtSerialRtonWriter writer(&buffer);
	std::string error;
	bool result = RtSerial::JsonToRton(i_json.c_str(), writer, error);
	if (!result)
	{
		OutputDebugStrF("Load Table From Json Error, Table ID : %d, Error : %s", i_table, error.c_str());
	}
	else
	{
		RtSerialRtonReader reader(&buffer);
		PVZDB::GetInstance().LoadPackageForTableFromBuffer(i_table, reader, i_stringUids);
	}
	return result;
}

void PVZDB::LoadPackageForTableFromBuffer(TableIndex i_table, RtSerialRtonReader& rtonReader, bool i_strictUids)
{
	TableSchema& schema = getTableSchema(i_table);
	TableRuntimeInfo& info = getRuntimeInfo(i_table);
	if (info.PackageLoaded)
		ReleasePackageForTable(i_table);

	RtDbTable* table = RtDb::GetDb()->GetTable(i_table);
	RtId::StaticSetImplicitTableIndex(table->GetTableIndex());
	RtId::StaticSetImplicitTableIndex(0xffffffff);
	RtSerialRtonSync sync(&rtonReader);
	if (!table->SerializeTable(&sync, ""))
	{
		OutputDebugStrF("PVZDB::LoadPackageForTableFromBuffer failed serialize data for table %ls.", schema.PrettyName.c_str());
		return;
	}
	table->SetCurrentPackageName(schema.Name);
	info.PackageLoaded = true;
}

bool PVZDB::LoadPackageForTableFromFile(TableIndex i_table, const std::string& i_filename, bool i_strictUids, const bool i_FileEncryption)
{
	Buffer fileBuffer;
	if (!i_filename.empty())
	{
		if (!gSexyAppBase->ReadBufferFromFile(i_filename, &fileBuffer, true))
		{
			OutputDebugStrF("PVZDB::LoadPackageForTableFromFile failed to open file for reading %s.", i_filename.c_str());
			return false;
		}
	}

	if (fileBuffer.GetDataLen() == 0)
	{
		OutputDebugStrF("PVZDB::LoadPackageForTableFromFile %s length = 0.", i_filename.c_str());
		return false;
	}

	Buffer decodedBuffer;
	uchar* data;
	uint32 length;
	if (i_FileEncryption)
	{
		gSexyAppBase->mAntiHackDriver->DecodeBuffer(fileBuffer, decodedBuffer);
		data = decodedBuffer.GetDataPtr();
		length = decodedBuffer.GetDataLen();
	}
	else
	{
		data = fileBuffer.GetDataPtr();
		length = fileBuffer.GetDataLen();
	}

	RtSerialRtonReader reader(data, length);
	LoadPackageForTableFromBuffer(i_table, reader, i_strictUids);
	RtDbTable* table = RtDb::GetDb()->GetTable(i_table);
	table->SetCurrentPackageName(RtName(StringToSexyString(i_filename)));
	table->SetFromLocalFile(true);
	return true;
}

bool PVZDB::SavePackageForTableToFile(PVZDB::TableIndex i_table, const std::string& i_filename, const bool i_asJSON, const bool i_FileEncryption)
{
	RtSerialRtonWriter writer;
	TableSchema& schema = getTableSchema(i_table);
	RtDbTable* table = RtDb::GetDb()->GetTable(i_table);
	bool saved = table->SavePackage(writer, i_filename, i_asJSON, i_FileEncryption);
	if (__builtin_expect(!saved, 1))
		OutputDebugStrF("PVZDB::SavePackageForTableToFile - RtDbTable::SavePackage failed for Table (idx:%d, name%s), to file %s", i_table, schema.PrettyName.c_str(), i_filename.c_str());
	else
		table->SetCurrentPackageName(schema.Name);
	return saved;
}

bool PVZDB::SavePackageFromNetJsonStringToFile(TableIndex i_table, const std::string& sNetJson, const std::string& i_filename, const bool i_asJson, const bool i_FileEncryption)
{
	RtDbTable* table = RtDb::GetDb()->GetTable(i_table);
	RtSerialBuffer buffer(NULL, 0);
	RtSerialRtonWriter writer(&buffer);
	std::string error;
	bool saved = RtSerial::JsonToRton(sNetJson.c_str(), writer, error);
	if (saved)
	{
		saved = false;
		if (!i_filename.empty())
		{
			std::string json;
			const uchar* data;
			int size;
			if (i_asJson)
			{
				RtSerial::RtonToJson(writer.GetBuffer()->GetDataPtr(), writer.GetBuffer()->GetDataSize(), json, true);
				data = (const uchar*)json.c_str();
				size = json.size();
			}
			else
			{
				data = writer.GetBuffer()->GetDataPtr();
				size = writer.GetBuffer()->GetDataSize();
			}

			Buffer encodedBuffer;
			if (i_FileEncryption)
			{
				Buffer plainBuffer;
				plainBuffer.SetData(data, size);
				gSexyAppBase->mAntiHackDriver->EncodeBuffer(plainBuffer, encodedBuffer);
				data = encodedBuffer.GetDataPtr();
				size = encodedBuffer.GetDataLen();
			}

			saved = gSexyAppBase->WriteBytesToFile(i_filename, data, size);
			if (saved)
			{
				RtName packageName(StringToWString(i_filename));
				table->SetCurrentPackageName(packageName);
			}
		}
	}
	return saved;
}

void PVZDB::Shutdown()
{
	releaseGameInfoObjects();
	ReleaseAllPackages();
	for (int i = 0; i < m_PVZTableSchema.size(); i++)
	{
		TableIndex index = m_PVZTableSchema[i].Index;
		RtDb::GetDb()->GetTable(index)->Reset(false);
	}
}

void PVZDB::releaseGameInfoObjects()
{
	RtDbTable* table = RtDb::GetDb()->GetTable(TABLE_GAME);
	if (table)
	{
		table->ReleaseId(table->GetIdForAlias(RtName(L"GameInfo")));
		table->ReleaseId(table->GetIdForAlias(RtName(L"Control")));
	}
}

void PVZDB::constructGameInfoObjects()
{
	RtDbTable* table = RtDb::GetDb()->GetTable(TABLE_GAME);
	RtId gameInfoId = table->AllocId(new PVZGameInfo(gLawnApp->mProdName, gLawnApp->mProductVersion, gLawnApp->mTimeLoaded), RtDbTable::ODM_Auto, true, NULL);
	RtWeakPtr<PVZGameInfo> gameInfo(gameInfoId);
	table->SetIdForAlias(RtName(L"GameInfo"), gameInfoId);

	RtId controlId = table->AllocId(new PVZRemoteControl(), RtDbTable::ODM_Auto, true, NULL);
	RtWeakPtr<PVZRemoteControl> control(controlId);
	table->SetIdForAlias(RtName(L"Control"), controlId);
}

void PVZDB::RunDeferredDeletions()
{
	for (int i = 0; i < m_PVZTableSchema.size(); i++)
	{
		if (m_PVZTableSchema[i].SerializableGameObjects)
			GetTable(m_PVZTableSchema[i].Index)->RunDeferredDeletions();
	}

	for (int index = TABLE_DYNAMIC_BEGIN; index <= m_highestClaimedDynamicTableIndex; index++)
	{
		if (isTableIndexValid((TableIndex)index))
			GetTable((TableIndex)index)->RunDeferredDeletions();
	}
}

void PVZDB::DestroyGameObjects()
{
	for (int i = 0; i < m_PVZTableSchema.size(); i++)
	{
		if (!m_PVZTableSchema[i].SerializableGameObjects)
			continue;
		for (RtDbTable::Iterator it = GetObjectIteratorForTable(m_PVZTableSchema[i].Index); it; ++it)
		{
			RtWeakPtr<GameObject> object(*it);
			GameObject* gameObject = object;
			if (gameObject)
				gameObject->CastChecked<GameObject>()->Destroy();
		}
	}
}

RtId PVZDB::FindFirstObjectByClass(TableIndex i_index, RtClass* i_class)
{
	RtDbTable::Iterator it = GetObjectIteratorForTable(i_index);
	for (; it; ++it)
	{
		RtId id = *it;
		if (RtDb::GetDb()->GetObjectForId(id)->IsA(i_class))
			return id;
	}
	return RtId();
}

void PVZDB::createTableForSchema(const TableSchema& i_schema) const
{
	RtDbTable::TableOptions options;
	options.mTableName = i_schema.Name;
	options.mDisplayName = i_schema.PrettyName;
	options.mIsFixedContent = i_schema.FixedContent;
	RtDb::GetDb()->CreateTable(i_schema.Index, &options)->SetCurrentPackageName(i_schema.Name);
}

void PVZDB::onGameObjectSerialized(GameObject* i_object)
{
	OnPostLoadGameState += MakeDelegate(*i_object, &GameObject::PostLoad);
}

void PVZDB::DebugPrintTableInfo(PVZDB::TableIndex i_table)
{
	if (!m_initialized)
	{
		OutputDebugStrF("*** PVZDB Tables not initialized! ***\n");
		return;
	}
	if (i_table < 0 || i_table >= TABLE_COUNT)
	{
		OutputDebugStrF("*** Table index %d out of bounds! ***\n", i_table);
		return;
	}
	RtDb::GetDb()->GetTable(i_table)->DebugPrintTableInfo();
}

void PVZDB::InitializeTables()
{
	m_PVZTableSchema.clear();
	m_PVZTableSchema.push_back(TableSchema(TABLE_SCRATCHSPACE, RtName(L"ScratchSpace"), "Scratch Space", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GAME, RtName(L"Game"), "Game System", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_VERSION, RtName(L"Version"), "Version", false, false, "RESFILE_PACKAGES_VERSION"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_MANIFEST, RtName(L"Manifest"), "Manifest", false, false, "RESFILE_PACKAGES_MANIFEST"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LIVECONFIG, RtName(L"LiveConfig"), "Live Config", false, false, "RESFILE_PACKAGES_LIVECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PROPERTYSHEETS, RtName(L"PropertySheets"), "Property Sheets", true, false, "RESFILE_PACKAGES_PROPERTYSHEETS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANTTYPES, RtName(L"PlantTypes"), "Plant Types", true, false, "RESFILE_PACKAGES_PLANTTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANTFAMILYPROPERTIES, RtName(L"PlantFamilyProperties"), "Plant Family Properties", true, false, "RESFILE_PACKAGES_PLANTFAMILYPROPERTIES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_POWERS, RtName(L"Powers"), "Powers", true, false, "RESFILE_PACKAGES_POWERS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ZOMBIETYPES, RtName(L"ZombieTypes"), "Zombie Types", true, false, "RESFILE_PACKAGES_ZOMBIETYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ZOMBIEACTIONS, RtName(L"ZombieActions"), "Zombie Actions", true, false, "RESFILE_PACKAGES_ZOMBIEACTIONS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CREATURETYPES, RtName(L"CreatureTypes"), "Creature Types", true, false, "RESFILE_PACKAGES_CREATURETYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PROJECTILETYPES, RtName(L"ProjectileTypes"), "Projectile Types", true, false, "RESFILE_PACKAGES_PROJECTILETYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GRIDITEMTYPES, RtName(L"GridItemTypes"), "Grid Item Types", true, false, "RESFILE_PACKAGES_GRIDITEMTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_EFFECTOBJECTTYPES, RtName(L"EffectObjectTypes"), "Effect Object Types", true, false, "RESFILE_PACKAGES_EFFECTOBJECTTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_COLLECTABLETYPES, RtName(L"CollectableTypes"), "Collectable Types", true, false, "RESFILE_PACKAGES_COLLECTABLETYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PRESENTTABLES, RtName(L"PresentTables"), "Present Table Types", true, false, "RESFILE_PACKAGES_PRESENTTABLES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PRESENTTYPES, RtName(L"PresentTypes"), "Present Types", true, false, "RESFILE_PACKAGES_PRESENTTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_UISHEETS, RtName(L"UISheets"), "UI Widget Sheets", true, false, "RESFILE_PACKAGES_UI_LAYOUT"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_NPCSHEETS, RtName(L"NPCDataSheets"), "NPC Data Sheets", true, false, "RESFILE_PACKAGES_NPCS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELMODULES, RtName(L"LevelModules"), "Level Modules", true, false, "RESFILE_PACKAGES_LEVELMODULES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_POWERUPTYPES, RtName(L"PowerupTypes"), "Powerup Types", true, false, "RESFILE_PACKAGES_POWERUPTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GAMEFEATURES, RtName(L"GameFeatures"), "Game Features", true, false, "RESFILE_PACKAGES_GAMEFEATURES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_TOOLPACKETS, RtName(L"ToolPackets"), "Tool Packets", true, false, "RESFILE_PACKAGES_TOOLPACKETS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_BONUSTYPES, RtName(L"BonusTypes"), "Bonus Types", true, false, "RESFILE_PACKAGES_BONUSTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_STREAMINGMUSIC, RtName(L"StreamingMusic"), "Streaming Music", true, false, "RESFILE_PACKAGES_STREAMINGWAVES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_MAGENTO, RtName(L"Magento"), "Magento", false, false, "RESFILE_PACKAGES_MAGENTO"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDMAPS, RtName(L"WorldMaps"), "World Maps", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDMAPLIST_NEW, RtName(L"WorldMapList_New"), "World Map List", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDMAPLIST_RIFT, RtName(L"WorldMapList_Rift"), "World Map List Rift", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDMAPLIST_PVZ1, RtName(L"WorldMapList_PVZ1"), "World Map List PVZ1", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDMAPLIST_UNCHARTED, RtName(L"WorldMapList_UNCHARTED"), "World Map List Uncharted", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDMAPLIST_CARDGAME, RtName(L"WorldMapList_CardGame"), "World Map List CardGame", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDMAPEDITORDATA, RtName(L"WorldMapList_PlantWars"), "World Map List PlantWars", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDRESOURCES, RtName(L"WorldMapEditorData"), "World Map Editor Data", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RESERVED_35, RtName(L"WorldResourcesDataSheets"), "World Resource Data Sheets", true, false, "RESFILE_PACKAGES_WORLDRESOURCES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_UIWIDGETS, RtName(L"UIWidgets"), "UI Widgets", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CURRENTLEVEL, RtName(L"CurrentLevel"), "Current Level Definition", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_BOARDSTATE, RtName(L"Board"), "Board Save State", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GAMEOBJECTS, RtName(L"GameObjects"), "Other Game Objects", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_BOARDENTITIES, RtName(L"BoardEntities"), "Other Board Entities", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ZOMBIES, RtName(L"Zombies"), "Zombies", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CREATURES, RtName(L"Creatures"), "Creatures", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PROJECTILES, RtName(L"Projectiles"), "Projectiles", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANTS, RtName(L"Plants"), "Plants", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANTGROUPS, RtName(L"TABLE_PLANTGROUPS"), "TABLE_PLANTGROUPS", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_COLLECTABLES, RtName(L"Collectables"), "Collectables", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GRIDITEMS, RtName(L"GridItems"), "Grid Items", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_EFFECTOBJECTS, RtName(L"EffectObjects"), "Effect Objects", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_EFFECTS, RtName(L"Effects"), "Standalone Effects", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_POPANIMRIGS, RtName(L"PopAnimRigs"), "PopAnimRigs", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_SUBSYSTEMS, RtName(L"GameSubSystems"), "Game SubSystems", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELMODULEINSTANCES, RtName(L"LevelModuleInstances"), "Active Level Modules", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WAVEACTIONINSTANCES, RtName(L"WaveActionInstances"), "Active Wave Actions", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_POWERUPINSTANCES, RtName(L"PowerupInstances"), "Powerup Instances", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLAYER_PROFILES, RtName(L"PlayerProfiles"), "Player profiles", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLAYER_INFO_DELTA, RtName(L"PlayerInfoDelta"), "Progression Data", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUI_FONTS, RtName(L"Fonts"), "Fonts", true, false, "RESFILE_PACKAGES_FONTS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUI_FONTS_ALIASES, RtName(L"Fonts_Aliases"), "Fonts_Aliases", true, false, "RESFILE_PACKAGES_FONTS_ALIASES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_SERVER_CONFIG, RtName(L"ServerConfig"), "Server Config", true, false, "RESFILE_PACKAGES_SERVERCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PURCHASE_CONFIG, RtName(L"PurchaseConfig"), "Purchase Config", true, false, "RESFILE_PACKAGES_PURCHASECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LOOTSAVEDATA, RtName(L"LootSaveData"), "Loot Save Data", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DROP_ITEM_GROUPS, RtName(L"DropItemGroups"), "Drop Item Groups", true, false, "RESFILE_PACKAGES_DROPITEMGROUPS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DROP_ITEMS, RtName(L"DropItems"), "Drop Items", true, false, "RESFILE_PACKAGES_DROPITEMS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CHALLENGE_DROP_ITEMS, RtName(L"ChallengeDropItems"), "Challenge Drop Items", true, false, "RESFILE_PACKAGES_CHALLENGEDROPITEMS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PROFILELOCALSAVEDATA, RtName(L"ProfileLocalSaveData"), "Profile Local Save Data", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DRAPERSAVEDATA, RtName(L"DraperSaveData"), "Draper Save Data", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_TLogCache, RtName(L"TLogCache"), "TLog Cache", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ACTIVITY_CONFIG, RtName(L"ActivityConfig"), "Activity Config", true, false, "RESFILE_PACKAGES_ACTIVITYCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GACHA_CONFIG, RtName(L"GachaConfig"), "Gacha Config", true, false, "RESFILE_PACKAGES_GACHACONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_SKILLTYPES, RtName(L"SkillTypes"), "Skill Types", true, false, "RESFILE_PACKAGES_SKILLTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DISPLAYACTIONS, RtName(L"DisplayActions"), "Display Actions", true, false, "RESFILE_PACKAGES_DISPLAYACTIONS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DISPLAYAVATARACTIONS, RtName(L"DisplayAvatarActions"), "Display Avatar Actions", true, false, "RESFILE_PACKAGES_DISPLAYAVATARACTIONS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANT_PIECE_LEVEL_DATA, RtName(L"PlantPieceLevelData"), "Plant Piece Level Data", true, false, "RESFILE_PACKAGES_PLANTPIECELEVELDATA"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_STORE_GIFT_CONFIG, RtName(L"StoreGiftConfig"), "Store Gift Config", true, false, "RESFILE_PACKAGES_STOREGIFTCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DAILY_REWARD_CONFIG, RtName(L"DailyRewardConfig"), "Daily Reward Config", true, false, "RESFILE_PACKAGES_DAILYREWARDCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_NETWORK_CACHE, RtName(L"NetworkCacheQueue"), "Network Cache Queue", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_TREASURE_CONFIG, RtName(L"TreasureConfig"), "Treasure Config", true, false, "RESFILE_PACKAGES_TREASURECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DANGERROOM_REWARD_CONFIG, RtName(L"DangerRoomLevelReward"), "danger room reward Data", true, false, "RESFILE_PACKAGES_DANGERROOMLEVELREWARD"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PEDTREASURE_CONFIG, RtName(L"TreasureConfig"), "PedTreasure Config", true, false, "RESFILE_PACKAGES_PEDTREASURECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_REDPACKET_REWARD, RtName(L"RedPacketReward"), "red packet reward Data", true, false, "RESFILE_PACKAGES_REDPACKETREWARD"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANT_TRIAL_CONFIG, RtName(L"PlantTrialConfig"), "plant trial Data", true, false, "RESFILE_PACKAGES_PLANTTRIALCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANTGIFTTYPES, RtName(L"PlantGiftTypes"), "PlantGift Types", true, false, "RESFILE_PACKAGES_PLANTGIFTTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RECHARGE_GIFT_CONFIG, RtName(L"RechargeGiftConfig"), "Recharge Gift Data", true, false, "RESFILE_PACKAGES_RECHARGEGIFTCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RECHARGE_REWARD_CONFIG, RtName(L"RechargeRewardConfig"), "Recharge Reward Data", true, false, "RESFILE_PACKAGES_RECHARGEREWARDCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CONSUMPTION_REWARD, RtName(L"ConsumptionReward"), "consumption reward Data", true, false, "RESFILE_PACKAGES_CONSUMPTIONREWARD"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANT_ADVENTURE_CONFIG, RtName(L"PlantAdventureConfigData"), "Plant Adventure Configs", true, false, "RESFILE_PACKAGES_PLANTADVENTURECONFIGDATA"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_UILAYOUT, RtName(L"UILayout"), "UILayout Definition", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DAILY_ACHIEVEMENT, RtName(L"DailyAchievement"), "Daily Achievement List", true, false, "RESFILE_PACKAGES_DAILYACHIEVEMENT"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELOFTHEDAY_CONFIG, RtName(L"LevelOfTheDayConfig"), "level of the day", true, false, "RESFILE_PACKAGES_LEVELOFTHEDAYCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_NATIONALDAYREWARD_CONFIG, RtName(L"NationalDayRewardConfig"), "national day", true, false, "RESFILE_PACKAGES_NATIONALDAYREWARDCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DANGERROOM_REWARD_LIST, RtName(L"DangerRoomRewardList"), "danger room reward list", true, false, "RESFILE_PACKAGES_DANGERROOMREWARDLIST"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PVP_OBJECTS, RtName(L"PVPObjects"), "pvp objects", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_TRAININGTYPES, RtName(L"TrainingTypes"), "Training Types", true, false, "RESFILE_PACKAGES_TRAININGTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_REBATE_REWARD, RtName(L"RebateRewardConfig"), "Rebate Reward Config", true, false, "RESFILE_PACKAGES_REBATEREWARDCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HARDLEVEL_CONFIG, RtName(L"HardLevelConfig"), "Hard Level Config", true, false, "RESFILE_PACKAGES_HARDLEVELCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_STAR_CONVERT_CONFIG, RtName(L"StarConvertConfigData"), "Star Convert Config", true, false, "RESFILE_PACKAGES_STARCONVERTCONFIGDATA"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ENDLEVEL_AWARD, RtName(L"EndLevelAward"), "End Level Award", true, false, "RESFILE_PACKAGES_ENDLEVELAWARD"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PVPSHOP_CONFIG, RtName(L"PVPShopConfigData"), "Pvp Shop Config", true, false, "RESFILE_PACKAGES_PVPSHOPCONFIGDATA"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PVP_UPGRADE, RtName(L"PVPUpgrade"), "PVPUpgrade", true, false, "RESFILE_PACKAGES_PVPUPGRADE"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LOSTNET_ACTIVITY_CONFIG, RtName(L"LostNetActivityConfigData"), "LostNetActivity Config", false, false, "RESFILE_PACKAGES_LOSTNETACTIVITYCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_COMPENSATED_AWARD, RtName(L"CompensatedAwardList"), "Compensated Award List", true, false, "RESFILE_PACKAGES_COMPENSATEDAWARDLIST"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_EASQUAREDCONFIG, RtName(L"EASquaredConfig"), "EASquared Config", false, false, "RESFILE_PACKAGES_EASQUARED_CONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ARMORTYPES, RtName(L"ArmorTypes"), "Armor Types", true, false, "RESFILE_PACKAGES_ARMORTYPES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_OFFER_BUNDLE_CONFIG, RtName(L"OfferBundleConfigData"), "Offer Bundle Config", true, false, "RESFILE_PACKAGES_OFFERBUNDLECONFIGDATA"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_WORLDCUP_CONFIG, RtName(L"WorldCupConfigData"), "WorldCup Config", true, false, "RESFILE_PACKAGES_WORLDCUPCONFIGDATA"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_AWARDCONFIG, RtName(L"AwardConfig"), "Award Config", false, false, "RESFILE_PACKAGES_AWARD_CONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_CONFIG, RtName(L"JoustConfig"), "Joust Config", false, false, "RESFILE_PACKAGES_JOUST_CONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_SCHEDULE, RtName(L"JoustSchedule"), "Joust Schedule", false, false, "RESFILE_PACKAGES_JOUST_SCHEDULE"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_LEVELS, RtName(L"JoustLevels"), "Joust Levels", false, false, "RESFILE_PACKAGES_JOUST_LEVELS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_LEADERBOARDS, RtName(L"JoustLeaderboards"), "Joust Leaderboards", false, false, "RESFILE_PACKAGES_JOUST_LEADERBOARDS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_CROWN_REWARDS, RtName(L"JoustCrownRewards"), "Joust Crown Rewards", false, false, "RESFILE_PACKAGES_JOUST_CROWNREWARDS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_PROGRESSIVE_REWARDS, RtName(L"JoustProgressiveRewards"), "Joust Progressive Rewards", false, false, "RESFILE_PACKAGES_JOUST_PROGRESSIVEREWARDS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_TOURNAMENT_REWARDS, RtName(L"JoustTournamentRewards"), "Joust Tournament Rewards", false, false, "RESFILE_PACKAGES_JOUST_TOURNAMENTREWARDS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RIFT_SCHEDULE, RtName(L"RiftSchedule"), "Rift Schedule", false, false, "RESFILE_PACKAGES_RIFT_SCHEDULE"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PERK_PROPERTIES, RtName(L"PerkProperties"), "Perk Properties", false, false, "RESFILE_PACKAGES_RIFT_PERKS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PERKS, RtName(L"Perks"), "Perks", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PERK_PROGRESSION, RtName(L"PerkProgression"), "Perk Progression", false, false, "RESFILE_PACKAGES_RIFT_PERK_PROGRESSION"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RIFT_EVENT_CONFIG, RtName(L"RiftEventConfig"), "Rift Event Config", false, false, "RESFILE_PACKAGES_RIFT_EVENT_CONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RIFT_SUB_EVENT_CONFIG, RtName(L"RiftSubEvents"), "Perk Sub Events", false, false, "RESFILE_PACKAGES_RIFT_SUB_EVENT"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RIFT_CONFIG, RtName(L"RiftConfig"), "Rift Config", false, false, "RESFILE_PACKAGES_RIFT_CONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RIFT_ZOMBOSS_REWARDS, RtName(L"RiftZombossRewards"), "Rift Zomboss Rewards", false, false, "RESFILE_PACKAGES_RIFT_ZOMBOSS_REWARDS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RIFT_LEVEL_UNLOCKS, RtName(L"RiftLevelUnlocks"), "Rift Level Unlocks", false, false, "RESFILE_PACKAGES_RIFT_LEVEL_UNLOCKS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RIFT_FIRST_CLEAR_REWARDS, RtName(L"RiftFirstClearRewards"), "Rift First Clear Rewards", false, false, "RESFILE_PACKAGES_RIFT_FIRST_CLEAR_REWARDS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_BOARDGRIDMAPS, RtName(L"BoardGridMaps"), "BoardGridMaps", true, false, "RESFILE_PACKAGES_BOARDGRIDMAPS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELMODULESDIFFICULTY, RtName(L"LevelModulesDifficulty"), "LevelModulesDifficulty", true, false, "RESFILE_PACKAGES_LEVELMODULESDIFFICULTY"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELMUTATORMODULES, RtName(L"LevelMutatorModules"), "LevelMutatorModules", true, false, "RESFILE_PACKAGES_LEVELMUTATORMODULES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELMUTATORTABLES, RtName(L"LevelMutatorTables"), "LevelMutatorTables", true, false, "RESFILE_PACKAGES_LEVELMUTATORTABLES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_MAIN_THEME_PROPERTIES, RtName(L"MainThemeProperties"), "Main Theme Properties", false, false, "RESFILE_PACKAGES_RIFT_MAIN_THEMES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_THEME_PROPERTIES, RtName(L"ThemeProperties"), "Theme Properties", false, false, "RESFILE_PACKAGES_RIFT_THEMES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_THEMES, RtName(L"Themes"), "Themes", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_AREA_MAIN_PROPERTIES, RtName(L"AreaMainProperties"), "Area Main Properties", false, false, "RESFILE_PACKAGES_NEW_PVP_AREA_MAIN"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_AREA_PROPERTIES, RtName(L"AreaProperties"), "Area Properties", false, false, "RESFILE_PACKAGES_NEW_PVP_AREAS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_AREAS, RtName(L"Areas"), "Areas", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ARTIFACT_PROPERTIES, RtName(L"ArtifactProperties"), "Artifact Properties", false, false, "RESFILE_PACKAGES_ARTIFACT"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ARTIFACT, RtName(L"Artifact"), "Artifact", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ARTIFACT_DISPLAY_ACTIONS, RtName(L"ArtifactDisplayActions"), "Artifact Display Actions", true, false, "RESFILE_PACKAGES_ARTIFACTDISPLAYACTIONS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ARTIFACT_CULTIVATION, RtName(L"ArtifactCultivation"), "Artifact Cultivation", true, false, "RESFILE_PACKAGES_ARTIFACTCULTIVATION"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ARTIFACTIMPROVEDPROPERTIES, RtName(L"ArtifactImprovedProperties"), "Artifact Improved Properties", true, false, "RESFILE_PACKAGES_ARTIFACTIMPROVEDPROPERTIES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PVZ1_CONFIG, RtName(L"PVZ1Config"), "pvz1 config", true, false, "RESFILE_PACKAGES_PVZ1_CONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CUSTOM_LEVEL_CONFIG, RtName(L"CustomLevelConfig"), "Custom Level Config", true, false, "RESFILE_PACKAGES_CUSTOMLEVELCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CUSTOM_LEVEL_DATA, RtName(L"CustomLevelData"), "Custom Level Data", true, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CARD_GAME_BOARD_CONFIG, RtName(L"CardGameBoardConfig"), "Card Game Board Config", true, false, "RESFILE_PACKAGES_CARDGAMEBOARDCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUICONFIG, RtName(L"HotUIConfig"), "HotUIConfig", true, false, "RESFILE_PACKAGES_HOTUICONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUI_WIDGETS, RtName(L"HotUIWidgets"), "Hot UI Widgets", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUI_COMPONENTS, RtName(L"HotUIComponents"), "Hot UI Components", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUI_PROPERTYSHEETS, RtName(L"HotUIPropertySheets"), "Hot UI Property Sheets", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUI_COLORS, RtName(L"Colors"), "Colors", true, false, "RESFILE_PACKAGES_COLORS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HOTUI_COLORS_ALIASES, RtName(L"Colors_Aliases"), "Colors_Aliases", true, false, "RESFILE_PACKAGES_COLORS_ALIASES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELSCORINGRULES, RtName(L"LevelScoringRules"), "LevelScoringRules", true, false, "RESFILE_PACKAGES_LEVELSCORINGRULES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_JOUST_PLANT_POWER_CONFIG, RtName(L"JoustPlantPowerConfigData"), "JoustPlantPower Config", true, false, "RESFILE_PACKAGES_JOUSTPLANTPOWERCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PROBABILITY_CONFIG, RtName(L"ProbabilityConfig"), "Probability Config", true, false, "RESFILE_PACKAGES_PROBABILITYCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_ARCADECONFIG, RtName(L"ArcadeConfig"), "Arcade Config", false, false, "RESFILE_PACKAGES_ARCADE_CONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_TRAVELLOG_CONFIG, RtName(L"TravelLog"), "TravelLog", false, false, "RESFILE_PACKAGES_TRAVELLOG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_TRAVELLOG_STATUS, RtName(L"TravelLogStatus"), "TravelLogStatus", false, false, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_DAVETREASURE_CONFIG, RtName(L"DaveTreasure"), "DaveTreasure", false, false, "RESFILE_PACKAGES_DAVETREASURE"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANTNEWAVATARS, RtName(L"PlantNewAvatars"), "Plant New Avatars", true, false, "RESFILE_PACKAGES_PLANTNEWAVATARS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RICHMAN_EVENT_CONFIG, RtName(L"RichManEventPropertySheets"), "Rich Man Event Property Sheets", true, false, "RESFILE_PACKAGES_RICHMANEVENTPROPERTYSHEETS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GENERALTASK_CONFIG, RtName(L"GeneralTask"), "GeneralTask", false, false, "RESFILE_PACKAGES_GENERALTASK"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVELEDITOR_CONFIG, RtName(L"LevelEditor"), "LevelEditor", false, false, "RESFILE_PACKAGES_LEVELEDITOR"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_COLLECTION_CONFIG, RtName(L"Collection"), "Collection", false, false, "RESFILE_PACKAGES_COLLECTION"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CARD_CONFIG, RtName(L"CardProperty"), "CardProperty", false, false, "RESFILE_PACKAGES_CARDPROPERTY"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CARD_OBJECTS, RtName(L"CardObjects"), "About Card Objects", false, true, ""));
	m_PVZTableSchema.push_back(TableSchema(TABLE_GENEENHANCEMENT_CONFIG, RtName(L"GeneEnhancementConfig"), "GeneEnhancementConfig", false, false, "RESFILE_PACKAGES_GENEENHANCEMENTCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_CTHULHU_CONFIG, RtName(L"CthulhuConfig"), "CthulhuConfig", false, false, "RESFILE_PACKAGES_CTHULHUCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVEL_MODIFIER_MODULE_COLLECTION_CONFIG, RtName(L"LevelModifierModuleCollection"), "LevelModifierModuleCollection", true, false, "RESFILE_PACKAGES_LEVELMODIFIERMODULECOLLECTION"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_LEVEL_MODIFIER_MODULE_CONFIG, RtName(L"LevelModifierModule"), "LevelModifierModule", true, false, "RESFILE_PACKAGES_LEVELMODIFIERMODULE"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RESISTENCE_CONFIG, RtName(L"ResistenceConfig"), "ResistenceConfig", true, false, "RESFILE_PACKAGES_RESISTENCECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_RESILIENCE_CONFIG, RtName(L"ResilienceConfig"), "ResilienceConfig", true, false, "RESFILE_PACKAGES_RESILIENCECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_UNCHARTED_BOOST_PROPERTIES, RtName(L"UnchartedBoostProperties"), "UnchartedBoostProperties", true, false, "RESFILE_PACKAGES_UNCHARTEDBOOSTPROPERTIES"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_HEROPLANT_CONFIG, RtName(L"HeroPlantConfig"), "Hero Plant Config", false, false, "RESFILE_PACKAGES_HEROPLANTCONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_AVATAR_EXCHANGE_CONFIG, RtName(L"AvatarExchangeConfig"), "Avatar Exchange Config", false, false, "RESFILE_PACKAGES_AVATAREXCHANGECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_PLANTWARS_ZOMBIE_TITLE_CONFIG, RtName(L"PlantWarsZombieTitleConfig"), "PlantWarsZombieTitleConfig", true, false, "RESFILE_PACKAGES_PLANTWARSZOMBIETITLECONFIG"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_MINIGAME_PERK_PROPERTIES, RtName(L"MiniGamePerkProperties"), "Mini Game Perk Properties", false, false, "RESFILE_PACKAGES_MINIGAME_PERKS"));
	m_PVZTableSchema.push_back(TableSchema(TABLE_MINIGAME_PERKS, RtName(L"MiniGamePerks"), "MiniGamePerks", false, true, ""));

	m_PVZTableRuntimeInfo.clear();
	m_PVZTableRuntimeInfo.resize(m_PVZTableSchema.size());
	for (int i = 0; i < m_PVZTableSchema.size(); i++)
	{
		TableSchema& schema = m_PVZTableSchema[i];
		RtDbTable::TableOptions options;
		options.mTableName = schema.Name;
		options.mDisplayName = schema.PrettyName;
		options.mIsFixedContent = schema.FixedContent;
		RtDbTable* table = RtDb::GetDb()->CreateTable(schema.Index, &options);
		table->SetCurrentPackageName(schema.Name);
		TableRuntimeInfo& info = m_PVZTableRuntimeInfo[i];
		info.TableIndex = table->GetTableIndex();
		info.TableName = table->GetTableOptions()->mTableName;
		m_PVZTableRuntimeInfo[i].PackageLoaded = false;
	}
	constructGameInfoObjects();
	m_initialized = true;
}

PVZDB::TableIndex PVZDB::ClaimDynamicTable(bool i_resetTable)
{
	TableIndex tableIndex;
	if (m_freeDynamicTableIndices.size() != 0)
	{
		tableIndex = m_freeDynamicTableIndices[m_freeDynamicTableIndices.size() - 1];
		m_freeDynamicTableIndices.pop_back();
		m_dynamicTableRuntimeInfo[tableIndex].PackageLoaded = false;
		if (i_resetTable)
		{
			RtDbTable* table = GetTable(tableIndex);
			table->Reset(false);
			table->Reset(true);
		}
	}
	else
	{
		tableIndex = (TableIndex)(m_highestClaimedDynamicTableIndex + 1);
		m_highestClaimedDynamicTableIndex = tableIndex;
		unsigned int dynamicNumber = tableIndex - TABLE_DYNAMIC_BEGIN;
		RtName name(StrFormat(L"_DYNAMIC%d_", dynamicNumber));
		std::string prettyName = StrFormat("<Dynamic #%d>", dynamicNumber);
		TableSchema& entry = m_dynamicTableSchema[tableIndex];
		entry = TableSchema(tableIndex, name, prettyName, false, false, "");
		TableSchema& schema = m_dynamicTableSchema[tableIndex];
		TableRuntimeInfo info;
		info.PackageLoaded = false;
		info.TableIndex = tableIndex;
		info.TableName = name;
		m_dynamicTableRuntimeInfo[tableIndex] = info;
		createTableForSchema(schema);
	}
	return tableIndex;
}

static int CompareRtIdsBySlot(const void* i_left, const void* i_right)
{
	uint32 left = ((const RtId*)i_left)->GetSlotIndex();
	uint32 right = ((const RtId*)i_right)->GetSlotIndex();
	if (left < right)
		return -1;
	return left != right;
}

void PVZDB::DebugPrintTableContents(PVZDB::TableIndex i_table)
{
	if (!m_initialized)
	{
		OutputDebugStrF("*** PVZDB Tables not initialized! ***\n");
		return;
	}
	if (i_table < 0 || i_table >= TABLE_COUNT)
	{
		OutputDebugStrF("*** Table index %d out of bounds! ***\n", i_table);
		return;
	}

	RtDbTable* table = RtDb::GetDb()->GetTable(i_table);
	RtDbTable::Iterator it = GetObjectIteratorForTable(i_table);
	std::vector<RtId> ids;
	for (; it; ++it)
	{
		RtId id = *it;
		ids.push_back(id);
	}

	qsort(&ids[0], ids.size(), sizeof(RtId), CompareRtIdsBySlot);
	OutputDebugStrF("==============================================\n");
	OutputDebugStrF("Slot\tRevision\tPointer\t\t\tClass\n");
	for (size_t i = 0; i < ids.size(); i++)
	{
		RtId& id = ids[i];
		RtObject* object = table->GetObjectForId(id);
		OutputDebugStrF("%d\t\t%d\t\t\t0x%08x\t\t%s\n", id.GetSlotIndex(), id.GetRevision(), object, object ? object->GetClass()->GetName() : "<NULL>");
		object->Cast<GameObject>();
	}
}

void PVZDB::VerifyGameObjectTablesAreEmpty()
{
	for (int i = 0; i < m_PVZTableSchema.size(); i++)
	{
		TableSchema& schema = m_PVZTableSchema[i];
		if (!schema.SerializableGameObjects)
			continue;
		if (__builtin_expect(!!(GetTable(schema.Index)->GetRtIdCount() == 0), 0))
			continue;

		std::string classes;
		for (RtDbTable::Iterator it = GetObjectIteratorForTable(schema.Index); it; ++it)
		{
			RtObject* object = RtDb::GetDb()->GetObjectForId(*it);
			std::string name = object ? object->GetClass()->GetName() : "##NULLPTR##";
			if (!classes.empty())
				classes += ", ";
			classes += name;
		}
		CrashTracking::Log(StrFormat("PVZDB::VerifyGameObjectTablesAreEmpty failed! There are %d object(s) (%s) remaining in table %d (%s)!", GetTable(schema.Index)->GetRtIdCount(), classes.c_str(), schema.Index, schema.PrettyName.c_str()));
	}
}

void PVZDB::SaveGameState(bool i_special)
{
	std::vector<std::pair<uint32, std::string>> files;
	uint32 totalBytes;
	for (size_t i = 0; i < m_PVZTableSchema.size(); i++)
	{
		const TableSchema& schema = m_PVZTableSchema[i];
		if (!schema.SerializableGameObjects)
			continue;

		std::string path = "";
		if (i_special)
			path = GetFolder(IFileDriver::PathType_NoBackup) + '/' + s_specialFolderName + '/';
		else
			path = GetFolder(IFileDriver::PathType_NoBackup);

		files.push_back(std::pair<uint32, std::string>(schema.Index, path + StrFormat("save_%s.rton", WStringToString(schema.Name.GetString()).c_str())));
	}

	RtDb::GetDb()->SavePackageGroupToFiles(files, false, &totalBytes);
	OutputDebugStrF("---- save complete, total bytes: %d\n", totalBytes);
}

void PVZDB::LoadGameState(bool i_special)
{
	std::vector<std::pair<uint32, std::string>> files;
	uint32 totalBytes;
	for (size_t i = 0; i < m_PVZTableSchema.size(); i++)
	{
		const TableSchema& schema = m_PVZTableSchema[i];
		if (!schema.SerializableGameObjects)
			continue;

		GetTable(schema.Index)->Reset(false);
		std::string path = "";
		if (i_special)
			path = GetFolder(IFileDriver::PathType_NoBackup) + '/' + s_specialFolderName + '/';
		else
			path = GetFolder(IFileDriver::PathType_NoBackup);

		files.push_back(std::pair<uint32, std::string>(schema.Index, path + StrFormat("save_%s.rton", WStringToString(schema.Name.GetString()).c_str())));
	}

	gMessageRouter->Subscribe(&Message::GameObjectSerializedIn, MakeDelegate(*this, &PVZDB::onGameObjectSerialized));
	RtDb::GetDb()->LoadPackageGroupFromFiles(files, &totalBytes);
	gMessageRouter->Unsubscribe(this);
	OutputDebugStrF("---- load complete, total bytes: %d\n", totalBytes);
	OutputDebugStrF("*** Notifying %d listeners...\n", OnPostLoadGameState.GetDelegateCount());
	OnPostLoadGameState();
	OnPostLoadGameState = Event0();
}

/////////////// Template instantiations ///////////////

template RtWeakPtr<BoardPropertySheet> PVZDB::FindObjectByAlias<BoardPropertySheet>(TableIndex, RtName);

template RtWeakPtr<ProjectilePropertySheet> PVZDB::FindObjectByAlias<ProjectilePropertySheet>(TableIndex, RtName);

template RtWeakPtr<LevelModifierModuleCollection> PVZDB::FindObjectByAlias<LevelModifierModuleCollection>(TableIndex, RtName);

template RtWeakPtr<PlantPropertySheet> PVZDB::FindObjectByAlias<PlantPropertySheet>(TableIndex, RtName);

template RtWeakPtr<NewPVPAreaProperties> PVZDB::FindObjectByAlias<NewPVPAreaProperties>(TableIndex, RtName);

template RtWeakPtr<CardGameBoardConfig> PVZDB::FindObjectByAlias<CardGameBoardConfig>(TableIndex, RtName);

template RtWeakPtr<CustomLevelConfig> PVZDB::FindObjectByAlias<CustomLevelConfig>(TableIndex, RtName);

template RtWeakPtr<PVZ1CopycatsModuleProperties> PVZDB::FindObjectByAlias<PVZ1CopycatsModuleProperties>(TableIndex, RtName);

template RtWeakPtr<HotUIConfig> PVZDB::FindObjectByAlias<HotUIConfig>(TableIndex, RtName);

template RtWeakPtr<ArcadePropertySheet> PVZDB::FindFirstObjectByClass<ArcadePropertySheet>(TableIndex);

template RtWeakPtr<PennyPerkProperties> PVZDB::FindObjectByAlias<PennyPerkProperties>(TableIndex, RtName);

template RtWeakPtr<RiftConfigSheet> PVZDB::FindObjectByAlias<RiftConfigSheet>(TableIndex, RtName);

template RtWeakPtr<PerkProgressionProperties> PVZDB::FindObjectByAlias<PerkProgressionProperties>(TableIndex, RtName);

template RtWeakPtr<RiftSubEventProperties> PVZDB::FindObjectByAlias<RiftSubEventProperties>(TableIndex, RtName);

template RtWeakPtr<RiftLevelUnlocksProperties> PVZDB::FindObjectByAlias<RiftLevelUnlocksProperties>(TableIndex, RtName);

template RtWeakPtr<RiftSchedule> PVZDB::FindObjectByAlias<RiftSchedule>(TableIndex, RtName);

template RtWeakPtr<RiftZombossRewards> PVZDB::FindObjectByAlias<RiftZombossRewards>(TableIndex, RtName);

template RtWeakPtr<PennyPerkShockwaveProjectileProperties> PVZDB::FindObjectByAlias<PennyPerkShockwaveProjectileProperties>(TableIndex, RtName);

template RtWeakPtr<RiftFirstClearRewards> PVZDB::FindObjectByAlias<RiftFirstClearRewards>(TableIndex, RtName);

template RtWeakPtr<RiftPropertySheet> PVZDB::FindObjectByAlias<RiftPropertySheet>(TableIndex, RtName);

template RtWeakPtr<RiftThemeProperties> PVZDB::FindObjectByAlias<RiftThemeProperties>(TableIndex, RtName);

template RtWeakPtr<TorchwoodProps> PVZDB::FindObjectByAlias<TorchwoodProps>(TableIndex, RtName);

template RtWeakPtr<ArtifactProperties> PVZDB::FindObjectByAlias<ArtifactProperties>(TableIndex, RtName);

template RtWeakPtr<PlantType> PVZDB::FindObjectByAlias<PlantType>(TableIndex, RtName);

template RtWeakPtr<EMPeaProps> PVZDB::FindObjectByAlias<EMPeaProps>(TableIndex, RtName);

template RtWeakPtr<JoustPropertySheet> PVZDB::FindObjectByAlias<JoustPropertySheet>(TableIndex, RtName);

template RtWeakPtr<JoustSchedule> PVZDB::FindObjectByAlias<JoustSchedule>(TableIndex, RtName);

template RtWeakPtr<JoustLeaderboardDefinition> PVZDB::FindObjectByAlias<JoustLeaderboardDefinition>(TableIndex, RtName);

template RtWeakPtr<JoustCrownRewardDefinition> PVZDB::FindObjectByAlias<JoustCrownRewardDefinition>(TableIndex, RtName);

template RtWeakPtr<JoustLevelSet> PVZDB::FindObjectByAlias<JoustLevelSet>(TableIndex, RtName);

template RtWeakPtr<JoustProgressiveRewardDefinition> PVZDB::FindObjectByAlias<JoustProgressiveRewardDefinition>(TableIndex, RtName);

template RtWeakPtr<JoustTournamentRewardDefinition> PVZDB::FindObjectByAlias<JoustTournamentRewardDefinition>(TableIndex, RtName);

template RtWeakPtr<MiniGamePerkProperties> PVZDB::FindObjectByAlias<MiniGamePerkProperties>(TableIndex, RtName);

template RtWeakPtr<PlantPediaConfig> PVZDB::FindObjectByAlias<PlantPediaConfig>(TableIndex, RtName);

template RtWeakPtr<GeneralPlantChipsExchangeConfig> PVZDB::FindObjectByAlias<GeneralPlantChipsExchangeConfig>(TableIndex, RtName);

template RtWeakPtr<ArtifactTimeProperties> PVZDB::FindObjectByAlias<ArtifactTimeProperties>(TableIndex, RtName);

template RtWeakPtr<ButtercupProps> PVZDB::FindObjectByAlias<ButtercupProps>(TableIndex, RtName);

template RtWeakPtr<CrownFlowerProps> PVZDB::FindObjectByAlias<CrownFlowerProps>(TableIndex, RtName);

template RtWeakPtr<ComponentWarmingRadiusGlobalProperties> PVZDB::FindObjectByAlias<ComponentWarmingRadiusGlobalProperties>(TableIndex, RtName);

template RtWeakPtr<ArmorPropertySheetUtils> PVZDB::FindObjectByAlias<ArmorPropertySheetUtils>(TableIndex, RtName);

template RtWeakPtr<RtWeakPtr<const NPCDataSheet>> PVZDB::FindObjectByAlias<RtWeakPtr<const NPCDataSheet>>(TableIndex, RtName);

template RtWeakPtr<GridItemType> PVZDB::FindObjectByAlias<GridItemType>(TableIndex, RtName);

template RtWeakPtr<FirecrackerFlowerProps> PVZDB::FindObjectByAlias<FirecrackerFlowerProps>(TableIndex, RtName);

template RtWeakPtr<GarlicProps> PVZDB::FindObjectByAlias<GarlicProps>(TableIndex, RtName);

template RtWeakPtr<PlantTypeIntensiveCarrot> PVZDB::FindObjectByAlias<PlantTypeIntensiveCarrot>(TableIndex, RtName);

template RtWeakPtr<GumnutProps> PVZDB::FindObjectByAlias<GumnutProps>(TableIndex, RtName);

template RtWeakPtr<PlantTristerixAphyllusProps> PVZDB::FindObjectByAlias<PlantTristerixAphyllusProps>(TableIndex, RtName);

template RtWeakPtr<TideEffectsProps> PVZDB::FindObjectByAlias<TideEffectsProps>(TableIndex, RtName);

template RtWeakPtr<const UIWidgetSheet> PVZDB::FindObjectByAlias<const UIWidgetSheet>(TableIndex, RtName);

template RtWeakPtr<WorldMapPropertySheet> PVZDB::FindObjectByAlias<WorldMapPropertySheet>(TableIndex, RtName);

template RtWeakPtr<ZombiePropertySheet> PVZDB::FindObjectByAlias<ZombiePropertySheet>(TableIndex, RtName);

template RtWeakPtr<ZombieTitleProperties> PVZDB::FindObjectByAlias<ZombieTitleProperties>(TableIndex, RtName);

template RtWeakPtr<ArmorPropertySheet> PVZDB::FindObjectByAlias<ArmorPropertySheet>(TableIndex, RtName);

template RtWeakPtr<ZombieResistenceConfig> PVZDB::FindObjectByAlias<ZombieResistenceConfig>(TableIndex, RtName);

template RtWeakPtr<MusicalJamProperties> PVZDB::FindObjectByAlias<MusicalJamProperties>(TableIndex, RtName);

template RtWeakPtr<WaveManagerProperties> PVZDB::FindObjectByAlias<WaveManagerProperties>(TableIndex, RtName);

template RtWeakPtr<EASquaredPropertySheet> PVZDB::FindObjectByAlias<EASquaredPropertySheet>(TableIndex, RtName);

template RtWeakPtr<ProbabilityConfig> PVZDB::FindObjectByAlias<ProbabilityConfig>(TableIndex, RtName);

template RtWeakPtr<PVZ1ModePropertySheet> PVZDB::FindObjectByAlias<PVZ1ModePropertySheet>(TableIndex, RtName);

template RtWeakPtr<DragonBruitProps> PVZDB::FindObjectByAlias<DragonBruitProps>(TableIndex, RtName);

template RtWeakPtr<DragonBabyBruitProps> PVZDB::FindObjectByAlias<DragonBabyBruitProps>(TableIndex, RtName);
