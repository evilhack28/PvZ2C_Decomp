//
//  SaveGameMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SaveGameMgr.h"
#include "LawnApp.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "Board.h"

std::string GetFolder(Sexy::IFileDriver::PathType thePathType);

static std::string s_saveFileName = "save.rton";
static std::string s_specialFolderName = "save";

/////////////// Lifecycle ///////////////

SaveGameMgr::SaveGameMgr()
{
}

SaveGameMgr::~SaveGameMgr()
{
}

/////////////// Save location ///////////////

std::string SaveGameMgr::getSaveLocationFor(const std::string& i_fileName, bool i_special) const
{
	std::string folder = "";
	if (i_special)
		folder = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + '/' + s_specialFolderName + '/';
	else
		folder = GetFolder(Sexy::IFileDriver::PathType_NoBackup);
	return folder + i_fileName;
}

bool SaveGameMgr::DoesSaveGameExist(bool i_special)
{
	return Sexy::FileExists(getSaveLocationFor(s_saveFileName, i_special), NULL);
}

void SaveGameMgr::ClearSaveGame(bool i_special)
{
	if (DoesSaveGameExist(i_special))
		gLawnApp->EraseFile(getSaveLocationFor(s_saveFileName, i_special));
}

/////////////// Header ///////////////

SaveGameHeader SaveGameMgr::generateHeaderForCurrentProfile()
{
	SaveGameHeader header;
	header.AppVersion = Version::App();
	header.RSBVersion = Version::LoadedRSB();
	header.PlayerID = ProfileMgr::GetInstance().GetAccountName();
	header.IsFullRSB = true;
	if (ProfileMgr::GetInstance().HasValidProfile())
	{
		header.PlayerIndex = ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileIndex();
		header.ProfileVersion = ProfileMgr::GetInstance().GetCurrentProfile()->GetVersion();
	}
	if (gLawnApp->m_board != NULL)
	{
		header.LevelName = gLawnApp->m_board->GetLevel();
		header.HardMode = gLawnApp->m_board->GetLevelIsHard();
		gLawnApp->m_board->GetGameplayResourceGroups(header.ResourceGroups);
	}
	return header;
}

/////////////// Save and load ///////////////

bool SaveGameMgr::IsSaveGameValidForCurrentPlayerID(bool i_special)
{
	bool valid = DoesSaveGameExist(i_special);
	if (valid)
	{
		SaveGameHeader header;
		if (!loadSaveGameHeader(header, i_special))
			valid = false;
		else if (ProfileMgr::GetInstance().GetAccountName() != header.PlayerID)
			valid = false;
		else
		{
			PlayerInfoPtr profile = ProfileMgr::GetInstance().FindProfileByIndex(header.PlayerIndex);
			valid = profile.IsValid();
			if (valid)
				valid = generateHeaderForCurrentProfile().VersionCheck(header);
		}
	}
	return valid;
}

bool SaveGameMgr::CanLoadGame(bool i_special)
{
	return IsSaveGameValidForCurrentPlayerID(i_special);
}

bool SaveGameMgr::TrySaveGame(bool i_special)
{
	bool result = false;
	if (ProfileMgr::GetInstance().HasValidProfile())
	{
		if (gGameStateMgr->GetState() == GAME_Game)
		{
			if (gLawnApp->m_board != NULL)
			{
				result = gLawnApp->m_board->CanSaveGameState();
				if (result)
				{
					SaveGameHeader header = generateHeaderForCurrentProfile();
					bool saved = saveSaveGameHeader(header, i_special);
					if (!saved)
					{
						result = saved;
						ClearSaveGame(i_special);
					}
					else
						gLawnApp->m_board->SaveGameState(i_special);
				}
			}
		}
	}
	return result;
}

bool SaveGameMgr::TryLoadGame(bool i_special)
{
	bool loaded = IsSaveGameValidForCurrentPlayerID(i_special);
	if (loaded)
	{
		SaveGameHeader header;
		if (!loadSaveGameHeader(header, i_special))
			loaded = false;
		else
		{
			PlayerInfoPtr profile = ProfileMgr::GetInstance().FindProfileByIndex(header.PlayerIndex);
			ProfileMgr::GetInstance().SetCurrentProfile(profile->AM_GetName());
			gGameStateMgr->setCurrentLevelIsHardMode(header.HardMode);
			gGameStateMgr->StartLevelFromSave(header.LevelName, GAMETRANSITION_None, GAMETRANSITION_None);
		}
	}
	return loaded;
}

bool SaveGameMgr::GetResourceGroupsRequiredForLoad(std::vector<std::string>& o_resourceGroups, bool i_special)
{
	bool valid = IsSaveGameValidForCurrentPlayerID(i_special);
	if (valid)
	{
		SaveGameHeader header;
		if (!loadSaveGameHeader(header, i_special))
			valid = false;
		else
			o_resourceGroups.insert(o_resourceGroups.begin(), header.ResourceGroups.begin(), header.ResourceGroups.end());
	}
	return valid;
}

bool SaveGameMgr::loadSaveGameHeader(SaveGameHeader& o_header, bool i_special)
{
	bool loaded = false;
	PVZDB::GetInstance().LoadPackageForTableFromFile(PVZDB::TABLE_SCRATCHSPACE, getSaveLocationFor(s_saveFileName, i_special), false, true);
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_SCRATCHSPACE); it; ++it)
	{
		RtObject* object = Sexy::RtDb::GetDb()->GetObjectForId(*it);
		if (object != NULL && object->IsA<SaveGameHeader>())
		{
			loaded = true;
			o_header = *object->CastChecked<SaveGameHeader>();
		}
	}
	PVZDB::GetInstance().GetTable(PVZDB::TABLE_SCRATCHSPACE)->Reset(false);
	PVZDB::GetInstance().GetTable(PVZDB::TABLE_SCRATCHSPACE)->Reset(true);
	return loaded;
}

bool SaveGameMgr::saveSaveGameHeader(const SaveGameHeader& i_header, bool i_special)
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_SCRATCHSPACE);
	table->Reset(false);
	table->Reset(true);
	SaveGameHeader* header = new SaveGameHeader();
	*header = i_header;
	table->AllocId(header, Sexy::RtDbTable::ODM_Auto, true, NULL);
	PVZDB::GetInstance().SavePackageForTableToFile(PVZDB::TABLE_SCRATCHSPACE, getSaveLocationFor(s_saveFileName, i_special), false, true);
	table->Reset(false);
	table->Reset(true);
	return true;
}
