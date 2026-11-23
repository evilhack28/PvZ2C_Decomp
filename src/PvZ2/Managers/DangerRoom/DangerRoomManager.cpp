//
//  DangerRoomManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include "DangerRoomManager.h"

/////////////// Accessors ///////////////

void DangerRoomManager::SetMedal(int i_value)
{
	m_record.m_medal = i_value;
}

void DangerRoomManager::SetCurrentLevel(int i_value)
{
	m_record.m_level = i_value;
}

int DangerRoomManager::GetCurrentLevel() const
{
	return m_record.m_level;
}

int DangerRoomManager::GetNextLevel() const
{
	return GetCurrentLevel() + 1;
}

void DangerRoomManager::SetMaxLevel(int i_value)
{
	m_record.m_maxLevel = i_value;
}

int DangerRoomManager::GetMaxLevel() const
{
	return m_record.m_maxLevel;
}

void DangerRoomManager::SetMaxLastWeekLevel(int i_value)
{
	m_record.m_maxLastWeekLevel = i_value;
}

int DangerRoomManager::GetMaxLastWeekLevel() const
{
	return m_record.m_maxLastWeekLevel;
}

void DangerRoomManager::SetPlantFoodBuyCount(int count)
{
	m_record.m_plantfoodBuyCount = count;
}

int DangerRoomManager::GetPlantFoodBuyCount()
{
	return m_record.m_plantfoodBuyCount;
}

const std::vector<int>& DangerRoomManager::GetPlantFoodPrice()
{
	return m_plantfoodPrice;
}

void DangerRoomManager::SetArtifactLeftTimes(int count)
{
	m_record.m_artifactLeftTimes = count;
}

int DangerRoomManager::GetArtifactLeftTimes()
{
	return m_record.m_artifactLeftTimes;
}

void DangerRoomManager::SetArtifactMaxTimes(int count)
{
	m_record.m_artifactMaxTimes = count;
}

int DangerRoomManager::GetArtifactMaxTimes()
{
	return m_record.m_artifactMaxTimes;
}

int DangerRoomManager::GetArtifactUsedTimes()
{
	return m_record.m_artifactMaxTimes - m_record.m_artifactLeftTimes;
}

const DangerRoomPropertySheet* DangerRoomManager::GetProps()
{
	return m_props;
}
