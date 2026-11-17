//
//  PlantWarsLevelTempData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"

#include "PlantWars.h"

/////////////// Lifecycle ///////////////

PlantWarsLevelTempData::PlantWarsLevelTempData()
{
	m_nodes.clear();
	FillData();
}

void PlantWarsLevelTempData::FillData()
{
	PlantWarsNodeData node;
	m_nodes.push_back(node);
	m_nodes.push_back(node);
}

/////////////// Accessors ///////////////

std::string PlantWarsLevelTempData::GetNodePlantPacket(int i_node, int i_index)
{
	return m_nodes[i_node].battleArray[i_index];
}

std::vector<std::string> PlantWarsLevelTempData::GetNodePlantPackets(int i_node)
{
	return m_nodes[i_node].battleArray;
}

void PlantWarsLevelTempData::SetLevelTime(int i_node, float i_time)
{
	m_nodes[i_node].lt = i_time;
}

float PlantWarsLevelTempData::GetLevelTime(int i_node)
{
	return m_nodes[i_node].lt;
}

/////////////// Plants ///////////////

void PlantWarsLevelTempData::AddNode(int i_node, std::string i_plant)
{
	m_nodes[i_node].battleArray.push_back(i_plant);
}

void PlantWarsLevelTempData::Assign(int i_node, std::vector<std::string> i_plants)
{
	m_nodes[i_node].battleArray.assign(i_plants.begin(), i_plants.end());
}

void PlantWarsLevelTempData::ClearNode(int i_node)
{
	m_nodes[i_node].battleArray.clear();
}
