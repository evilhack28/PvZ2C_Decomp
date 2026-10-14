//
//  PVZ1InfoUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZ1InfoUI.h"

void PVZ1InfoUI::initLoadingResourcesGroupList()
{
}

PVZ1InfoUI::PVZ1InfoUI()
{
}

PVZ1InfoUI::~PVZ1InfoUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ1InfoUI);

void PVZ1InfoUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1InfoUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(PVZ1InfoUI);
}
