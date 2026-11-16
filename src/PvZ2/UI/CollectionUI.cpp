//
//  CollectionUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectionUI.h"

void CollectionUI::unregisterForEvents()
{
}

CollectionUI::~CollectionUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectionUI);

void CollectionUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectionUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_hasCollection);
	REFLECTION_CLASSBUILDER_FIELD(int, m_rare);

	REFLECTION_CLASSBUILDER_END(CollectionUI);
}
