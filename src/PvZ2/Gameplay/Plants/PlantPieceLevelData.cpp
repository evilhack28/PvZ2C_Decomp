//
//  PlantPieceLevelData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantPieceLevelData.h"

PlantPieceLevelData::PlantPieceLevelData()
{
}

PlantPieceLevelData::~PlantPieceLevelData()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPieceLevelData);

void PlantPieceLevelData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPieceLevel);
	REFLECTION_CLASSBUILDER_END(PlantPieceLevel);

	REFLECTION_CLASSBUILDER_BEGIN(PlantPieceLevelData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<PlantPieceLevel>, m_PlantPieceLevelDataArray, PlantPieceLevelDataArray);
	REFLECTION_CLASSBUILDER_END(PlantPieceLevelData);
}

const std::vector<PlantPieceLevel> & PlantPieceLevelData::GetData()
{
	return m_PlantPieceLevelDataArray;
}
