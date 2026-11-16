//
//  CustomLevelDataCreator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelDataCreator.h"

CustomLevelDataCreator::CustomLevelDataCreator()
{
	m_currentLevelIndex = 0;
}

CustomLevelDataCreator::~CustomLevelDataCreator()
{
}

const std::vector<CustomLevelWorldParams>& CustomLevelDataCreator::GetLevelDatas()
{
}

#include "CustomLevelDataCreator.h"
bool CustomLevelDataCreator::Load()
{
	return CustomLevelDataCreator::LoadLevelDatas();
}
