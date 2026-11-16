//
//  ArcadePropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ArcadePropertySheet.h"
#include "ReflectionBuilder.h"

namespace ArcadePropertySheetHelpers
{
	static bool operator==(const ArcadeLevel& i_a, const ArcadeLevel& i_b)
	{
		return i_a.ID == i_b.ID;
	}
}

template <typename T> bool ContainsID(const std::vector<T>& i_items, const std::string& i_id);

template <typename T> const T& GetByID(const std::vector<T>& i_items, const std::string& i_id);

template <typename It, typename T> static It FindValue(It i_first, It i_last, const T& i_value)
{
	T value = i_value;
	return std::find(i_first, i_last, value);
}

/////////////// Lifecycle ///////////////

ArcadePropertySheet::~ArcadePropertySheet()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArcadePropertySheet);

void ArcadePropertySheet::StaticClassInit()
{
	using namespace ArcadePropertySheetHelpers;

	REFLECTION_ENUMBUILDER_BEGIN(ArcadeRewardType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(None, None);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(GiftBox, GiftBox);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(PowerUp, PowerUp);
	REFLECTION_ENUMBUILDER_END(ArcadeRewardType);

	REFLECTION_CLASSBUILDER_BEGIN(ArcadeReward);
		REFLECTION_CLASSBUILDER_FIELD(ArcadeRewardType, Type);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ID);
	REFLECTION_CLASSBUILDER_END(ArcadeReward);

	REFLECTION_CLASSBUILDER_BEGIN(ArcadeLevel);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ID);
	REFLECTION_CLASSBUILDER_END(ArcadeLevel);

	REFLECTION_CLASSBUILDER_BEGIN(ArcadeEndlessLevel);
		REFLECTION_CLASSBUILDER_FIELD(ArcadeLevel, Level);
		REFLECTION_CLASSBUILDER_FIELD(std::string, RewardPowerUp);
		REFLECTION_CLASSBUILDER_FIELD(int, RewardPowerUpAfterWave);
	REFLECTION_CLASSBUILDER_END(ArcadeEndlessLevel);

	REFLECTION_CLASSBUILDER_BEGIN(ArcadeLevelPack);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ID);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, Toggles);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PackNameLocalizationKey);
		REFLECTION_CLASSBUILDER_FIELD(std::string, LayoutFile);
		REFLECTION_CLASSBUILDER_FIELD(std::string, BackdropImage);
		REFLECTION_CLASSBUILDER_FIELD(std::string, UnlockAfter);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ArcadeLevel>, Levels);
		REFLECTION_CLASSBUILDER_FIELD(ArcadeReward, Reward);
	REFLECTION_CLASSBUILDER_END(ArcadeLevelPack);

	REFLECTION_CLASSBUILDER_BEGIN(ArcadeMode);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ID);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ModeNameLocalizationKey);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PowerUpCollectionID);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ArcadeMenuImage);
		REFLECTION_CLASSBUILDER_FIELD(bool, DisplayInArcadeMenu);
		REFLECTION_CLASSBUILDER_FIELD(ArcadeEndlessLevel, EndlessLevel);
		REFLECTION_CLASSBUILDER_FIELD(std::string, UnlockEndlessAfter);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ArcadeLevelPack>, LevelPacks);
	REFLECTION_CLASSBUILDER_END(ArcadeMode);

	REFLECTION_CLASSBUILDER_BEGIN(PowerUpMetaData);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ID);
		REFLECTION_CLASSBUILDER_FIELD(std::string, UpImage);
		REFLECTION_CLASSBUILDER_FIELD(std::string, DownImage);
		REFLECTION_CLASSBUILDER_FIELD(std::string, GameFeature);
		REFLECTION_CLASSBUILDER_FIELD(std::string, NameLocalizationKey);
		REFLECTION_CLASSBUILDER_FIELD(std::string, DescriptionLocalizationKey);
		REFLECTION_CLASSBUILDER_FIELD(std::string, UnlockHintLocalizationKey);
	REFLECTION_CLASSBUILDER_END(PowerUpMetaData);

	REFLECTION_CLASSBUILDER_BEGIN(PowerUpCollection);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ID);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PowerUpMetaData>, PowerUps);
	REFLECTION_CLASSBUILDER_END(PowerUpCollection);

	REFLECTION_CLASSBUILDER_BEGIN(ArcadePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ArcadeMode>, ArcadeModes);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PowerUpCollection>, PowerUpCollections);
	REFLECTION_CLASSBUILDER_END(ArcadePropertySheet);
}

/////////////// Accessors ///////////////

const ArcadePropertySheetHelpers::ArcadeMode& ArcadePropertySheet::GetModeByID(const std::string& i_modeID) const
{
	return GetByID(ArcadeModes, i_modeID);
}

const ArcadePropertySheetHelpers::PowerUpCollection& ArcadePropertySheet::GetPowerUpCollectionByID(const std::string& i_collectionID) const
{
	return GetByID(PowerUpCollections, i_collectionID);
}

bool ArcadePropertySheet::HasPowerUpCollection(const std::string& i_collectionID) const
{
	return ContainsID(PowerUpCollections, i_collectionID);
}

bool ArcadePropertySheet::IsLevelEndless(const std::string& i_levelID) const
{
	ArcadePropertySheetHelpers::ArcadeMode mode = GetModeByLevelID(i_levelID);
	return i_levelID == mode.EndlessLevel.Level.ID;
}

const ArcadePropertySheetHelpers::PowerUpCollection& ArcadePropertySheet::GetPowerUpCollectionByModeID(const std::string& i_modeID) const
{
	ArcadePropertySheetHelpers::ArcadeMode mode = GetModeByID(i_modeID);
	return GetPowerUpCollectionByID(mode.PowerUpCollectionID);
}

const ArcadePropertySheetHelpers::PowerUpCollection& ArcadePropertySheet::GetPowerUpCollectionByLevelPackID(const std::string& i_levelPackID) const
{
	ArcadePropertySheetHelpers::ArcadeMode mode = GetModeByLevelPackID(i_levelPackID);
	return GetPowerUpCollectionByID(mode.PowerUpCollectionID);
}

const ArcadePropertySheetHelpers::PowerUpCollection& ArcadePropertySheet::GetPowerUpCollectionByLevelID(const std::string& i_levelID) const
{
	ArcadePropertySheetHelpers::ArcadeMode mode = GetModeByLevelID(i_levelID);
	return GetPowerUpCollectionByID(mode.PowerUpCollectionID);
}

/////////////// Logic ///////////////

bool ArcadePropertySheet::HasLevel(const std::string& i_levelID) const
{
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	for (; it != end; ++it)
	{
		if ((*it).ContainsLevelID(i_levelID))
			break;
	}
}

bool ArcadePropertySheet::HasNextLevelInPack(const std::string& i_levelID) const
{
	bool hasNext = false;
	if (!IsLevelEndless(i_levelID))
	{
		ArcadePropertySheetHelpers::ArcadeLevelPack pack = GetLevelPackByLevelID(i_levelID);
		hasNext = !pack.IsLevelLastInPack(i_levelID);
	}
	return hasNext;
}

const ArcadePropertySheetHelpers::ArcadeLevel& ArcadePropertySheet::GetNextLevelInPack(const std::string& i_levelID) const
{
	const ArcadePropertySheetHelpers::ArcadeLevelPack& pack = GetLevelPackByLevelID(i_levelID);
	std::vector<ArcadePropertySheetHelpers::ArcadeLevel>::const_iterator first = pack.Levels.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeLevel>::const_iterator last = pack.Levels.end();
	std::vector<ArcadePropertySheetHelpers::ArcadeLevel>::const_iterator it = FindValue(first, last, ArcadePropertySheetHelpers::ArcadeLevel{ i_levelID });
	return *(it + 1);
}

const ArcadePropertySheetHelpers::ArcadeMode& ArcadePropertySheet::GetModeByLevelID(const std::string& i_levelID) const
{
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	while (it != end)
	{
		const ArcadePropertySheetHelpers::ArcadeMode& mode = *it;
		if (mode.ContainsLevelID(i_levelID))
			return mode;
		++it;
	}
	static ArcadePropertySheetHelpers::ArcadeMode defaultMode;
	return defaultMode;
}

const ArcadePropertySheetHelpers::ArcadeLevelPack& ArcadePropertySheet::GetLevelPackByLevelID(const std::string& i_levelID) const
{
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	while (it != end)
	{
		const ArcadePropertySheetHelpers::ArcadeMode& mode = *it;
		if (mode.ContainsLevelID(i_levelID))
			return mode.GetLevelPackByLevelID(i_levelID);
		++it;
	}
	static ArcadePropertySheetHelpers::ArcadeLevelPack defaultPack;
	return defaultPack;
}

const ArcadePropertySheetHelpers::ArcadeLevel& ArcadePropertySheet::GetLevelByID(const std::string& i_levelID) const
{
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	while (it != end)
	{
		const ArcadePropertySheetHelpers::ArcadeMode& mode = *it;
		if (mode.ContainsLevelID(i_levelID))
			return mode.GetLevelByID(i_levelID);
		++it;
	}
	static ArcadePropertySheetHelpers::ArcadeLevel defaultLevel;
	return defaultLevel;
}

const ArcadePropertySheetHelpers::ArcadeMode& ArcadePropertySheet::GetModeByLevelPackID(const std::string& i_levelPackID) const
{
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	while (it != end)
	{
		const ArcadePropertySheetHelpers::ArcadeMode& mode = *it;
		if (mode.ContainsLevelPackID(i_levelPackID))
			return mode;
		++it;
	}
	static ArcadePropertySheetHelpers::ArcadeMode defaultMode;
	return defaultMode;
}

const ArcadePropertySheetHelpers::ArcadeLevelPack& ArcadePropertySheet::GetLevelPackByID(const std::string& i_packID) const
{
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	while (it != end)
	{
		const ArcadePropertySheetHelpers::ArcadeMode& mode = *it;
		if (mode.ContainsLevelPackID(i_packID))
			return mode.GetLevelPackByID(i_packID);
		++it;
	}
	static ArcadePropertySheetHelpers::ArcadeLevelPack defaultPack;
	return defaultPack;
}

bool ArcadePropertySheet::HasPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID) const
{
	bool hasPowerUp = HasPowerUpCollection(i_collectionID);
	if (hasPowerUp)
	{
		ArcadePropertySheetHelpers::PowerUpCollection collection = GetPowerUpCollectionByID(i_collectionID);
		hasPowerUp = collection.ContainsPowerUpID(i_powerUpID);
	}
	return hasPowerUp;
}

const ArcadePropertySheet* ArcadePropertySheet::Get()
{
	return PVZDB::GetInstance().FindFirstObjectByClass<ArcadePropertySheet>(PVZDB::TABLE_ARCADECONFIG).Get();
}

void ArcadePropertySheet::ForEachLevel(std::function<void(const ArcadePropertySheetHelpers::ArcadeLevel&)> i_function) const
{
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	for (; it != end; ++it)
	{
		(*it).ForEachLevel(i_function);
	}
}

const std::vector<std::string> ArcadePropertySheet::GetUniqueArcadePowerUpTypeNames() const
{
	std::vector<std::string> names;
	std::vector<ArcadePropertySheetHelpers::PowerUpCollection>::const_iterator collection = PowerUpCollections.begin();
	std::vector<ArcadePropertySheetHelpers::PowerUpCollection>::const_iterator collectionEnd = PowerUpCollections.end();
	for (; collection != collectionEnd; ++collection)
	{
		const ArcadePropertySheetHelpers::PowerUpCollection& current = *collection;
		std::vector<ArcadePropertySheetHelpers::PowerUpMetaData>::const_iterator powerUp = current.PowerUps.begin();
		std::vector<ArcadePropertySheetHelpers::PowerUpMetaData>::const_iterator powerUpEnd = current.PowerUps.end();
		for (; powerUp != powerUpEnd; ++powerUp)
		{
			const std::string& id = (*powerUp).ID;
			if (names.end() == std::find(names.begin(), names.end(), id))
				names.push_back(id);
		}
	}
	return names;
}

const std::vector<ArcadePropertySheetHelpers::UnlockSource> ArcadePropertySheet::GetUnlockSourcesForPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID) const
{
	std::vector<ArcadePropertySheetHelpers::UnlockSource> sources;
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator it = ArcadeModes.begin();
	std::vector<ArcadePropertySheetHelpers::ArcadeMode>::const_iterator end = ArcadeModes.end();
	for (; it != end; ++it)
	{
		const ArcadePropertySheetHelpers::ArcadeMode& mode = *it;
		if (mode.PowerUpCollectionID == i_collectionID)
		{
			if (mode.EndlessLevel.RewardPowerUp == i_powerUpID)
			{
				ArcadePropertySheetHelpers::UnlockSource source(ArcadePropertySheetHelpers::EndlessLevel, mode.EndlessLevel.Level.ID, mode.EndlessLevel.RewardPowerUpAfterWave);
				sources.push_back(source);
			}

			std::vector<ArcadePropertySheetHelpers::ArcadeLevelPack> levelPacks = mode.GetLevelPacks();
			std::vector<ArcadePropertySheetHelpers::ArcadeLevelPack>::iterator pack = levelPacks.begin();
			std::vector<ArcadePropertySheetHelpers::ArcadeLevelPack>::iterator packEnd = levelPacks.end();
			while (pack != packEnd)
			{
				const ArcadePropertySheetHelpers::ArcadeLevelPack& levelPack = *pack;
				if (levelPack.Reward.Type == ArcadePropertySheetHelpers::PowerUp && levelPack.Reward.ID == i_powerUpID)
				{
					ArcadePropertySheetHelpers::UnlockSource source(ArcadePropertySheetHelpers::LevelPack, levelPack.ID, levelPack.Levels.size());
					sources.push_back(source);
				}
				++pack;
			}
		}
	}
	return sources;
}
