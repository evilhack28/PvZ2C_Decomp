//
//  Collectable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Collectable.h"
#include "CollectableType.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Collectable);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableType);

void CollectableType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, Dimensions);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, RenderOffset);
	REFLECTION_CLASSBUILDER_END(CollectableType);
}
