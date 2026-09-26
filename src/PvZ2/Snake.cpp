//
//  Snake.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SnakeModule.h"

SnakeProperties::~SnakeProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SnakeProperties);

void SnakeProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SnakeProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_FIELD(int, SnakeDamage);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, HPCurWave);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<GridItemPlacementProperties>, BlockPlacements);

	REFLECTION_CLASSBUILDER_END(SnakeProperties);
}

void SnakeProperties::GatherResourceRequirements(std::set<std::string>& i_arg) const
{
}
