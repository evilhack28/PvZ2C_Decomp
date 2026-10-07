//
//  PlantTypeVine.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//
#include "PlantTypeVine.h"
#include "PvZ/Board.h"
#include "PvZ/LawnApp.h"
#include "PvZ/PlantGroup.h"
#include "PvZ/EntityFinder.h"

/////////////// PlantTypeVine ///////////////

RT_CLASS_IMPLEMENT(PlantTypeVine);

PlantTypeVine::PlantTypeVine()
{
}

PlantTypeVine::~PlantTypeVine()
{
}

void PlantTypeVine::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeVine);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

	REFLECTION_CLASSBUILDER_END(PlantTypeVine);

}

bool PlantTypeVine::CanPlantOnPlant(Plant* plant) const
{
	Board* board = gLawnApp->m_board;
	PlantGroup* plantGroup;
	{
		Sexy::Point gridPosition(plant->m_column, plant->m_row);
		plantGroup = board->GetPlantGroupAt(gridPosition);
	}
	if (plantGroup != nullptr)
	{
		if (plantGroup->GetTopPlant()->GetType()->TypeName != TypeName && plant->GetMultiPlantGridLayer() == MULTI_PLANT_GRID_LAYER_MAIN)
		{
			return true;
		}
		if (plantGroup->GetTopPlant()->GetType()->TypeName == TypeName)
		{
			Plant* topPlant = plantGroup->GetTopPlant().operator->();
			return PlantType::CanPlantOnPlant(topPlant);
		}
	}
	return false;
}

void PlantTypeVine::GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const
{
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesAtGridSquare(entities, ENTITYTYPE_PLANT, i_gridPosition.mX, i_gridPosition.mY);
	if (entities.empty())
	{
		Plant* leftPlant = gLawnApp->m_board->GetPlantAt(i_gridPosition.mX - 1, i_gridPosition.mY, "");
		if (leftPlant != nullptr && "cobcannon" == leftPlant->GetType()->TypeName)
		{
			io_plantingReasons->push_back(PLANTING_VINE_CAN_NOT_PLANT_ON_COBCANNON);
		}
		else if (leftPlant != nullptr && "armorflame" == leftPlant->GetType()->TypeName)
		{
			io_plantingReasons->push_back(PLANTING_ONLY_ON_GRAVES);
		}
		else
		{
			io_plantingReasons->push_back(PLANTING_VINE_MUST_BE_ON_A_PLANT);
		}
	}
	else
	{
		if (gLawnApp->m_board->IsSky(i_gridPosition))
		{
			io_plantingReasons->push_back(PLANTING_NOT_IN_SKY);
		}
		Plant* plant = gLawnApp->m_board->GetPlantAt(i_gridPosition.mX, i_gridPosition.mY, "");
		if (plant != nullptr)
		{
			if ("cobcannon" == plant->GetType()->TypeName)
			{
				io_plantingReasons->push_back(PLANTING_VINE_CAN_NOT_PLANT_ON_COBCANNON);
				return;
			}
			if ("armorflame" == plant->GetType()->TypeName)
			{
				io_plantingReasons->push_back(PLANTING_ONLY_ON_GRAVES);
				return;
			}
			if ("smallcactus" == plant->GetType()->TypeName || "smallChestnut" == plant->GetType()->TypeName)
			{
				io_plantingReasons->push_back(PLANTING_VINE_MUST_BE_ON_A_PLANT);
				return;
			}
		}
		Plant* leftPlant = gLawnApp->m_board->GetPlantAt(i_gridPosition.mX - 1, i_gridPosition.mY, "");
		if (leftPlant != nullptr)
		{
			if ("cobcannon" == leftPlant->GetType()->TypeName)
			{
				io_plantingReasons->push_back(PLANTING_VINE_CAN_NOT_PLANT_ON_COBCANNON);
				return;
			}
			if ("armorflame" == leftPlant->GetType()->TypeName)
			{
				io_plantingReasons->push_back(PLANTING_ONLY_ON_GRAVES);
				return;
			}
		}
		if (plant != nullptr)
		{
			return;
		}
		io_plantingReasons->push_back(PLANTING_VINE_MUST_BE_ON_A_PLANT);
	}
}
