#define private public
#define protected public
#include "Plant.h"
#include "BoardEntity.h"
#include "PlantFramework.h"

#include <cstddef>

#define SHOW(cls, member) \
	char probe_##cls##_##member[offsetof(cls, member)] = {};
#define SIZE(cls) \
	char size_##cls[sizeof(cls)] = {};

SIZE(BoardEntity)
SIZE(Plant)
SIZE(PlantFramework)

SHOW(Plant, m_state)
SHOW(Plant, m_row)
SHOW(Plant, m_column)


SHOW(Plant, m_baseScale)
SHOW(Plant, m_PlantHealth)
SHOW(Plant, m_initialLaunchInterval)
SHOW(PlantFramework, m_plant)
SHOW(PlantFramework, m_callCancelPlantfood)
