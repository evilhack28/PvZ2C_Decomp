//
//  GridItemWisp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_JackOLantern.h"

GridItemWisp::~GridItemWisp()
{
}

GridItemWispProps::~GridItemWispProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWisp);

void GridItemWisp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemWisp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_avatar);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraDPS);
	REFLECTION_CLASSBUILDER_END(GridItemWisp);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWispProps);

void GridItemWispProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemWispProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
		REFLECTION_CLASSBUILDER_FIELD(float, Damage);
	REFLECTION_CLASSBUILDER_END(GridItemWispProps);
}
