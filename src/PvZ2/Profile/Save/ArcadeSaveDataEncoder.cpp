//
//  ArcadeSaveDataEncoder.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "ArcadeSaveDataEncoder.h"
#include "PlayerInfo.h"
#include <algorithm>
#include <EAStdC/EAHashString.h>

/////////////// Helpers ///////////////

unsigned int composeEndlessProgress(unsigned short i_wave, unsigned short i_highest)
{
	return (i_wave << 16) | i_highest;
}

void decomposeEndlessProgress(const unsigned int& i_progress, unsigned short& o_wave, unsigned short& o_highest)
{
	o_highest = i_progress;
	o_wave = i_progress >> 16;
}

int composeVaseBreakerEndlessState(int i_sunAmount, int i_plantFoodCount)
{
	return ((i_plantFoodCount & 0xF) << 14) + (i_sunAmount & 0x3FFF);
}

void decomposeVaseBreakerEndlessState(const unsigned int& i_state, int& o_sunAmount, int& o_plantFoodCount)
{
	o_sunAmount = 0;
	o_sunAmount |= i_state & 0x3FFF;
	o_plantFoodCount = 0;
	o_plantFoodCount |= (i_state >> 14) & 0xF;
}

template <class T>
T& getOrAdd(unsigned int i_id, std::vector<T>& io_list)
{
	for (typename std::vector<T>::iterator it = io_list.begin(), end = io_list.end(); it != end; ++it)
	{
		if ((*it).IDHash == i_id)
			return *it;
	}
	T entry;
	entry.IDHash = i_id;
	io_list.push_back(entry);
	return io_list.back();
}

/////////////// Encoder ///////////////

NameHash ArcadeSaveDataEncoder::HashName(const std::string& i_name)
{
	return EA::StdC::FNV1(i_name.c_str(), i_name.length());
}

void ArcadeSaveDataEncoder::CompleteLevelInPack(const std::string& i_levelName, const std::string& i_packID, std::vector<ArcadePackProgress>& o_progress)
{
	ArcadePackProgress& pack = getOrAdd(HashName(i_packID), o_progress);
	getOrAdd(HashName(i_levelName), pack.LevelProgress).State = 1;
}

void ArcadeSaveDataEncoder::SetCurrentEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, int i_currentWave, std::vector<ArcadePackProgress>& o_progress)
{
	ArcadePackProgress& pack = getOrAdd(HashName(i_packID), o_progress);
	ArcadeLevelProgress& level = getOrAdd(HashName(i_levelName), pack.LevelProgress);
	unsigned short wave, highest;
	decomposeEndlessProgress(level.Progress, wave, highest);
	level.Progress = composeEndlessProgress(i_currentWave, highest);
}

void ArcadeSaveDataEncoder::SetCurrentEndlessLevelStateInPack(const std::string& i_levelName, const std::string& i_packID, int i_state, std::vector<ArcadePackProgress>& o_progress)
{
	ArcadePackProgress& pack = getOrAdd(HashName(i_packID), o_progress);
	getOrAdd(HashName(i_levelName), pack.LevelProgress).State = i_state;
}

void ArcadeSaveDataEncoder::SetCurrentVaseBreakerEndlessState(const std::string& i_levelName, const std::string& i_packID, int i_sunAmount, int i_plantFoodCount, std::vector<ArcadePackProgress>& o_progress)
{
	ArcadePackProgress& pack = getOrAdd(HashName(i_packID), o_progress);
	ArcadeLevelProgress& level = getOrAdd(HashName(i_levelName), pack.LevelProgress);
	level.State = composeVaseBreakerEndlessState(i_sunAmount, i_plantFoodCount);
}

void ArcadeSaveDataEncoder::UnlockPowerUpInCollection(const std::string& i_powerUpID, const std::string& i_collectionID, std::vector<PowerUpCollectionProgress>& o_progress)
{
	PowerUpCollectionProgress& collection = getOrAdd(HashName(i_collectionID), o_progress);
	getOrAdd(HashName(i_powerUpID), collection.UnlockedPowerups);
}

void ArcadeSaveDataEncoder::SetHighestCompletedEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, int i_highestWave, std::vector<ArcadePackProgress>& o_progress)
{
	ArcadePackProgress& pack = getOrAdd(HashName(i_packID), o_progress);
	ArcadeLevelProgress& level = getOrAdd(HashName(i_levelName), pack.LevelProgress);
	unsigned short wave, highest;
	decomposeEndlessProgress(level.Progress, wave, highest);
	level.Progress = composeEndlessProgress(wave, i_highestWave);
}

bool ArcadeSaveDataEncoder::IsPowerUpUnlockedInCollection(const std::string& i_powerUpID, const std::string& i_collectionID, const std::vector<PowerUpCollectionProgress>& i_progress)
{
	unsigned int collectionHash = HashName(i_collectionID);
	unsigned int powerUpHash = HashName(i_powerUpID);
	for (std::vector<PowerUpCollectionProgress>::const_iterator it = i_progress.begin(), end = i_progress.end(); it != end; ++it)
	{
		PowerUpCollectionProgress collection = *it;
		if (collection.IDHash == collectionHash)
		{
			for (std::vector<PowerUpProgress>::iterator jt = collection.UnlockedPowerups.begin(), jend = collection.UnlockedPowerups.end(); jt != jend; ++jt)
			{
				PowerUpProgress powerUp = *jt;
				if (powerUp.IDHash == powerUpHash)
					return true;
			}
		}
	}
	return false;
}

bool ArcadeSaveDataEncoder::IsLevelCompletedInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress)
{
	unsigned int packHash = HashName(i_packID);
	unsigned int levelHash = HashName(i_levelName);
	for (std::vector<ArcadePackProgress>::const_iterator it = i_progress.begin(), end = i_progress.end(); it != end; ++it)
	{
		ArcadePackProgress pack = *it;
		if (pack.IDHash == packHash)
		{
			for (std::vector<ArcadeLevelProgress>::iterator jt = pack.LevelProgress.begin(), jend = pack.LevelProgress.end(); jt != jend; ++jt)
			{
				ArcadeLevelProgress level = *jt;
				if (level.IDHash == levelHash)
					return level.State == 1;
			}
		}
	}
	return false;
}

int ArcadeSaveDataEncoder::GetCurrentEndlessLevelStateInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress)
{
	unsigned int packHash = HashName(i_packID);
	unsigned int levelHash = HashName(i_levelName);
	for (std::vector<ArcadePackProgress>::const_iterator it = i_progress.begin(), end = i_progress.end(); it != end; ++it)
	{
		ArcadePackProgress pack = *it;
		if (pack.IDHash == packHash)
		{
			for (std::vector<ArcadeLevelProgress>::iterator jt = pack.LevelProgress.begin(), jend = pack.LevelProgress.end(); jt != jend; ++jt)
			{
				ArcadeLevelProgress level = *jt;
				if (level.IDHash == levelHash)
					return level.State;
			}
		}
	}
	return 0;
}

int ArcadeSaveDataEncoder::GetCurrentEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress)
{
	unsigned short wave, highest;
	unsigned int packHash = HashName(i_packID);
	unsigned int levelHash = HashName(i_levelName);
	for (std::vector<ArcadePackProgress>::const_iterator it = i_progress.begin(), end = i_progress.end(); it != end; ++it)
	{
		ArcadePackProgress pack = *it;
		if (pack.IDHash == packHash)
		{
			for (std::vector<ArcadeLevelProgress>::iterator jt = pack.LevelProgress.begin(), jend = pack.LevelProgress.end(); jt != jend; ++jt)
			{
				ArcadeLevelProgress level = *jt;
				if (level.IDHash == levelHash)
				{
					decomposeEndlessProgress(level.Progress, wave, highest);
					return wave;
				}
			}
		}
	}
	return 0;
}

int ArcadeSaveDataEncoder::GetHighestCompletedEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress)
{
	unsigned short wave, highest;
	unsigned int packHash = HashName(i_packID);
	unsigned int levelHash = HashName(i_levelName);
	for (std::vector<ArcadePackProgress>::const_iterator it = i_progress.begin(), end = i_progress.end(); it != end; ++it)
	{
		ArcadePackProgress pack = *it;
		if (pack.IDHash == packHash)
		{
			for (std::vector<ArcadeLevelProgress>::iterator jt = pack.LevelProgress.begin(), jend = pack.LevelProgress.end(); jt != jend; ++jt)
			{
				ArcadeLevelProgress level = *jt;
				if (level.IDHash == levelHash)
				{
					decomposeEndlessProgress(level.Progress, wave, highest);
					return highest;
				}
			}
		}
	}
	return 0;
}

void ArcadeSaveDataEncoder::CheatUncompleteLevelInPack(const std::string& i_levelName, const std::string& i_packID, std::vector<ArcadePackProgress>& o_progress)
{
	ArcadePackProgress& pack = getOrAdd(HashName(i_packID), o_progress);
	unsigned int levelHash = HashName(i_levelName);
	std::vector<ArcadeLevelProgress>::iterator last = std::remove_if(pack.LevelProgress.begin(), pack.LevelProgress.end(), [=](const ArcadeLevelProgress& i_level) { return i_level.IDHash == levelHash; });
	pack.LevelProgress.erase(last, pack.LevelProgress.end());
	ArcadePackProgress packCopy = pack;
	std::vector<ArcadePackProgress>::iterator packLast = std::remove_if(o_progress.begin(), o_progress.end(), [=](const ArcadePackProgress& i_pack) { return i_pack.IDHash == packCopy.IDHash; });
	o_progress.erase(packLast, o_progress.end());
}

void ArcadeSaveDataEncoder::CheatLockPowerUpInCollection(const std::string& i_powerUpID, const std::string& i_collectionID, std::vector<PowerUpCollectionProgress>& o_progress)
{
	PowerUpCollectionProgress& collection = getOrAdd(HashName(i_collectionID), o_progress);
	unsigned int powerUpHash = HashName(i_powerUpID);
	std::vector<PowerUpProgress>::iterator last = std::remove_if(collection.UnlockedPowerups.begin(), collection.UnlockedPowerups.end(), [=](const PowerUpProgress& i_powerUp) { return i_powerUp.IDHash == powerUpHash; });
	collection.UnlockedPowerups.erase(last, collection.UnlockedPowerups.end());
	PowerUpCollectionProgress collectionCopy = collection;
	std::vector<PowerUpCollectionProgress>::iterator collectionLast = std::remove_if(o_progress.begin(), o_progress.end(), [=](const PowerUpCollectionProgress& i_collection) { return i_collection.IDHash == collectionCopy.IDHash; });
	o_progress.erase(collectionLast, o_progress.end());
}

void ArcadeSaveDataEncoder::GetCurrentVaseBreakerEndlessState(const std::string& i_levelName, const std::string& i_packID, int& o_sunAmount, int& o_plantFoodCount, const std::vector<ArcadePackProgress>& i_progress)
{
	unsigned int packHash = HashName(i_packID);
	unsigned int levelHash = HashName(i_levelName);
	for (std::vector<ArcadePackProgress>::const_iterator it = i_progress.begin(), end = i_progress.end(); it != end; ++it)
	{
		ArcadePackProgress pack = *it;
		if (pack.IDHash == packHash)
		{
			for (std::vector<ArcadeLevelProgress>::iterator jt = pack.LevelProgress.begin(), jend = pack.LevelProgress.end(); jt != jend; ++jt)
			{
				ArcadeLevelProgress level = *jt;
				if (level.IDHash == levelHash)
				{
					decomposeVaseBreakerEndlessState(level.State, o_sunAmount, o_plantFoodCount);
					return;
				}
			}
		}
	}
	o_plantFoodCount = 0;
	o_sunAmount = 0;
}
