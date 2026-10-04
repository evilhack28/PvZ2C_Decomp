//
//  ArcadeProgressDatabase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "ArcadeProgressDatabase.h"
#include "ArcadePropertySheet.h"
#include "ArcadeSaveDataEncoder.h"
#include "PlayerInfo.h"
#include "GameFeatureType.h"
#include "TodCommon.h"
#include "ProfileUtils.h"

/////////////// Construction ///////////////

ArcadeProgressDatabase::ArcadeProgressDatabase(PlayerInfo* i_profile, const ArcadePropertySheet* i_arcadeProps)
{
	m_profile = i_profile;
	m_arcadeProps = i_arcadeProps;
}

ArcadeProgressDatabase ArcadeProgressDatabase::Instance()
{
	return ArcadeProgressDatabase(ProfileUtils::Profile(), ArcadePropertySheet::Get());
}

/////////////// Command ///////////////

void ArcadeProgressDatabase::CompleteLevel(const std::string& i_levelName)
{
	std::vector<ArcadePackProgress> progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	ArcadeSaveDataEncoder::CompleteLevelInPack(i_levelName, packID, progress);
	m_profile->SetArcadeProgress(progress);
}

void ArcadeProgressDatabase::CheatUncompleteLevel(const std::string& i_levelName)
{
	std::vector<ArcadePackProgress> progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	ArcadeSaveDataEncoder::CheatUncompleteLevelInPack(i_levelName, packID, progress);
	m_profile->SetArcadeProgress(progress);
}

void ArcadeProgressDatabase::UnlockPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID)
{
	std::vector<PowerUpCollectionProgress> progress = m_profile->GetPowerUpProgress();
	ArcadeSaveDataEncoder::UnlockPowerUpInCollection(i_powerUpID, i_collectionID, progress);
	m_profile->SetPowerUpProgress(progress);
	const ArcadePropertySheetHelpers::PowerUpMetaData& meta = m_arcadeProps->GetPowerUpCollectionByID(i_collectionID).GetPowerUpByID(i_powerUpID);
	GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(meta.GameFeature);
	m_profile->UnlockGameFeature(feature->Feature);
}

void ArcadeProgressDatabase::CheatLockPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID)
{
	std::vector<PowerUpCollectionProgress> progress = m_profile->GetPowerUpProgress();
	ArcadeSaveDataEncoder::CheatLockPowerUpInCollection(i_powerUpID, i_collectionID, progress);
	m_profile->SetPowerUpProgress(progress);
	const ArcadePropertySheetHelpers::PowerUpMetaData& meta = m_arcadeProps->GetPowerUpCollectionByID(i_collectionID).GetPowerUpByID(i_powerUpID);
	GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(meta.GameFeature);
	m_profile->SetGameFeatureUnlockState(feature->Feature, false);
}

void ArcadeProgressDatabase::CompleteCurrentEndlessWave(const std::string& i_levelName)
{
	std::vector<ArcadePackProgress> progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	int current = GetCurrentEndlessWave(i_levelName);
	int highestCompleted = GetHighestCompletedEndlessWave(i_levelName);
	int highest = std::max(current, highestCompleted);
	ArcadeSaveDataEncoder::SetCurrentEndlessWaveInPack(i_levelName, packID, current + 1, progress);
	ArcadeSaveDataEncoder::SetHighestCompletedEndlessWaveInPack(i_levelName, packID, highest, progress);
	m_profile->SetArcadeProgress(progress);
}

void ArcadeProgressDatabase::ResetCurrentEndlessWave(const std::string& i_levelName)
{
	std::vector<ArcadePackProgress> progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	ArcadeSaveDataEncoder::SetCurrentEndlessWaveInPack(i_levelName, packID, 0, progress);
	m_profile->SetArcadeProgress(progress);
}

void ArcadeProgressDatabase::SetCurrentVaseBreakerEndlessState(const std::string& i_levelName, int i_sunAmount, int i_plantFoodCount)
{
	int sun = ClampInt(i_sunAmount, 0, 9999);
	int plantFood = ClampInt(i_plantFoodCount, 0, 15);
	std::vector<ArcadePackProgress> progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	ArcadeSaveDataEncoder::SetCurrentVaseBreakerEndlessState(i_levelName, packID, sun, plantFood, progress);
	m_profile->SetArcadeProgress(progress);
}

/////////////// Query ///////////////

bool ArcadeProgressDatabase::IsPowerUpUnlocked(const std::string& i_powerUpID, const std::string& i_collectionID) const
{
	return ArcadeSaveDataEncoder::IsPowerUpUnlockedInCollection(i_powerUpID, i_collectionID, m_profile->GetPowerUpProgress());
}

std::string ArcadeProgressDatabase::getSaveDataPackIDForLevelID(const std::string& i_levelID) const
{
	if (m_arcadeProps->IsLevelEndless(i_levelID))
		return m_arcadeProps->GetModeByLevelID(i_levelID).ID;
	return m_arcadeProps->GetLevelPackByLevelID(i_levelID).ID;
}

bool ArcadeProgressDatabase::IsLevelComplete(const std::string& i_levelName) const
{
	const std::vector<ArcadePackProgress>& progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	return ArcadeSaveDataEncoder::IsLevelCompletedInPack(i_levelName, packID, progress);
}

int ArcadeProgressDatabase::GetCurrentEndlessWave(const std::string& i_levelName) const
{
	const std::vector<ArcadePackProgress>& progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	return ArcadeSaveDataEncoder::GetCurrentEndlessWaveInPack(i_levelName, packID, progress);
}

int ArcadeProgressDatabase::GetHighestCompletedEndlessWave(const std::string& i_levelName) const
{
	const std::vector<ArcadePackProgress>& progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	return ArcadeSaveDataEncoder::GetHighestCompletedEndlessWaveInPack(i_levelName, packID, progress);
}

void ArcadeProgressDatabase::GetCurrentVaseBreakerEndlessState(const std::string& i_levelName, int& o_sunAmount, int& o_plantFoodCount) const
{
	const std::vector<ArcadePackProgress>& progress = m_profile->GetArcadeProgress();
	std::string packID = getSaveDataPackIDForLevelID(i_levelName);
	ArcadeSaveDataEncoder::GetCurrentVaseBreakerEndlessState(i_levelName, packID, o_sunAmount, o_plantFoodCount, progress);
}

bool ArcadeProgressDatabase::IsLevelUnlocked(const std::string& i_levelName) const
{
	if (m_arcadeProps->IsLevelEndless(i_levelName))
	{
		ArcadePropertySheetHelpers::ArcadeMode mode = m_arcadeProps->GetModeByLevelID(i_levelName);
		return IsPackComplete(mode.UnlockEndlessAfter);
	}
	ArcadePropertySheetHelpers::ArcadeLevelPack pack = m_arcadeProps->GetLevelPackByLevelID(i_levelName);
	int i = 0;
	for (; i != pack.Levels.size(); i++)
	{
		if (pack.Levels[i].ID == i_levelName)
			break;
	}
	if (i == pack.Levels.size())
		return false;
	bool unlocked = IsPackComplete(pack.UnlockAfter);
	for (int j = i - 1; j >= 0 && unlocked; j--)
		unlocked = IsLevelComplete(pack.Levels[j].ID);
	return unlocked;
}

bool ArcadeProgressDatabase::IsPackComplete(const std::string& i_packID) const
{
	if (i_packID.empty())
		return true;
	ArcadePropertySheetHelpers::ArcadeLevelPack pack = m_arcadeProps->GetLevelPackByID(i_packID);
	for (ArcadePropertySheetHelpers::ArcadeLevel level : pack.Levels)
	{
		if (!IsLevelComplete(level.ID))
			return false;
	}
	return true;
}

int ArcadeProgressDatabase::GetHighestCompletedPackLevel(const std::string& i_packID) const
{
	if (i_packID.empty())
		return 1;
	int count = 0;
	ArcadePropertySheetHelpers::ArcadeLevelPack pack = m_arcadeProps->GetLevelPackByID(i_packID);
	for (ArcadePropertySheetHelpers::ArcadeLevel level : pack.Levels)
	{
		if (!IsLevelComplete(level.ID))
			return count;
		count++;
	}
	return count;
}

bool ArcadeProgressDatabase::IsAnyLevelComplete() const
{
	const std::vector<ArcadePackProgress>& progress = m_profile->GetArcadeProgress();
	std::vector<ArcadePackProgress>::const_iterator it = progress.begin();
	std::vector<ArcadePackProgress>::const_iterator end = progress.end();
	bool found;
	while ((found = (it != end)))
	{
		if (!(*it).LevelProgress.empty())
			break;
		++it;
	}
	return found;
}

bool ArcadeProgressDatabase::AreAllPowerUpsUnlockedInCollection(const std::string& i_collectionID) const
{
	const ArcadePropertySheetHelpers::PowerUpCollection& collection = m_arcadeProps->GetPowerUpCollectionByID(i_collectionID);
	std::vector<ArcadePropertySheetHelpers::PowerUpMetaData>::const_iterator it = collection.PowerUps.begin();
	std::vector<ArcadePropertySheetHelpers::PowerUpMetaData>::const_iterator end = collection.PowerUps.end();
	for (; it != end; ++it)
	{
		if (!IsPowerUpUnlocked((*it).ID, i_collectionID))
			return false;
	}
	return true;
}
