//
//  GridItemHydrocotyledrummerEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HydrocotyleDrummer.h"

GridItemHydrocotyledrummerEffectProps::GridItemHydrocotyledrummerEffectProps()
{
}

GridItemHydrocotyledrummerEffectProps::~GridItemHydrocotyledrummerEffectProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHydrocotyledrummerEffect);

void GridItemHydrocotyledrummerEffect::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHydrocotyledrummerEffect);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(float, m_healRatio);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_animNamePrefix);
	REFLECTION_CLASSBUILDER_END(GridItemHydrocotyledrummerEffect);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHydrocotyledrummerEffectProps);

void GridItemHydrocotyledrummerEffectProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHydrocotyledrummerEffectProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemHydrocotyledrummerEffectProps);
}

#include "GridItem.h"
void GridItemHydrocotyledrummerEffect::KillGridItem()
{
	 GridItem::KillGridItem();
}
