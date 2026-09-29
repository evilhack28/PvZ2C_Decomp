//
//  WorldMap_LuaButtonsDelegate.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_LuaButtonsDelegate.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_LuaButtonsDelegate);

void WorldMap_LuaButtonsDelegate::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_LuaButtonsDelegate);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_LuaButtonsDelegate);
}

void WorldMap_LuaButtonsDelegate::OnMouseUp(const int i_arg0, const int i_arg1)
{
}
