//
//  HotUITableView.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUITableView.h"

HotUITableView::HotUITableView()
{
	m_originalHeight = -1;
}

HotUITableViewProperties::~HotUITableViewProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUITableView);

void HotUITableView::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUITableView);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUILayoutList);

	REFLECTION_CLASSBUILDER_END(HotUITableView);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUITableViewProperties);

void HotUITableViewProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUITableViewProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUILayoutListProperties);

		REFLECTION_CLASSBUILDER_FIELD(DynamicSizeData, SpaceBetweenRows);
	REFLECTION_CLASSBUILDER_END(HotUITableViewProperties);
}
