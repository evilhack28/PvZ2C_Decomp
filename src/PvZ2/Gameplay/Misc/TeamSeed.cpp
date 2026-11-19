//
//  TeamSeed.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "AdventureTeamEditorUI.h"
#include "NameMapper.h"
#include "PlantType.h"

void TeamSeed::InitView()
{
}

int TeamSeed::GetPlantId()
{
	return PlantNameMapper::GetInstance().GetIdForName(m_plantType->TypeName);
}
