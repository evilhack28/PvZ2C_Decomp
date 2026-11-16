//
//  HotUIJoustCrownCollectionEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIJoustCrownCollectionEffect.h"

HotUIJoustCrownCollectionEffect::HotUIJoustCrownCollectionEffect()
{
}

HotUIJoustCrownCollectionEffect::~HotUIJoustCrownCollectionEffect()
{
}

HotUIJoustCrownCollectionEffectProperties::HotUIJoustCrownCollectionEffectProperties()
{
}

HotUIJoustCrownCollectionEffectProperties::~HotUIJoustCrownCollectionEffectProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIJoustCrownCollectionEffect);

void HotUIJoustCrownCollectionEffect::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIJoustCrownCollectionEffect);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIJoustCrownCollectionEffect);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIJoustCrownCollectionEffectProperties);

void HotUIJoustCrownCollectionEffectProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIJoustCrownCollectionEffectProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::string, CrownImage);
		REFLECTION_CLASSBUILDER_FIELD(CurveType, TweenCurve);
	REFLECTION_CLASSBUILDER_END(HotUIJoustCrownCollectionEffectProperties);
}
