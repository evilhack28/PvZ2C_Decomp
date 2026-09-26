//
//  HotUITableViewCell.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUITableViewCell.h"

HotUITableViewCell::~HotUITableViewCell()
{
}

HotUITableViewCellProperties::~HotUITableViewCellProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUITableViewCell);

void HotUITableViewCell::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUITableViewCell);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIButton);

	REFLECTION_CLASSBUILDER_END(HotUITableViewCell);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUITableViewCellProperties);

void HotUITableViewCellProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUITableViewCellProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIButtonProperties);

	REFLECTION_CLASSBUILDER_END(HotUITableViewCellProperties);
}
