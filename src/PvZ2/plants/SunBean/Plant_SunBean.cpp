//
//  Plant_SunBean.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SunBean.h"

PlantSunBean::PlantSunBean()
{
}

PlantSunBean::~PlantSunBean()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSunBean);

void PlantSunBean::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSunBean);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isSuperSized);

	REFLECTION_CLASSBUILDER_END(PlantSunBean);
}
