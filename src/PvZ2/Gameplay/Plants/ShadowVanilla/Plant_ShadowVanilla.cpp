//
//  Plant_ShadowVanilla.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ShadowVanilla.h"

PlantShadowvanilla::PlantShadowvanilla()
{
	_shadowChargeCount = 0;
	_isShadowStatus = 0;
}

PlantShadowvanilla::~PlantShadowvanilla()
{
}

PlantShadowVanillaProps::~PlantShadowVanillaProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantShadowvanilla);

void PlantShadowvanilla::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantShadowvanilla);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, _shadowChargeCount);
		REFLECTION_CLASSBUILDER_FIELD(bool, _isShadowStatus);
	REFLECTION_CLASSBUILDER_END(PlantShadowvanilla);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantShadowVanillaProps);

void PlantShadowVanillaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantShadowVanillaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, WhirlPoolRatios);
	REFLECTION_CLASSBUILDER_END(PlantShadowVanillaProps);
}

#include "PlantFramework.h"
void PlantShadowvanilla::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantShadowvanilla::CanApplyPlantfood()
{
	return true;
}

void PlantShadowvanilla::onAnimStoppedCallback(const std::string& i_arg)
{
}
