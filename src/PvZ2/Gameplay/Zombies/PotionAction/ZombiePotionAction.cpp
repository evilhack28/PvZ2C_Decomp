//
//  ZombiePotionAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePotionAction.h"

ZombiePotionAction::ZombiePotionAction()
{
}

ZombiePotionAction::~ZombiePotionAction()
{
}

ZombiePotionActionProps::~ZombiePotionActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePotionAction);

void ZombiePotionAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePotionAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(ZombiePotionAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePotionActionProps);

void ZombiePotionActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PotionData);
		REFLECTION_CLASSBUILDER_FIELD(Point, Location);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Type);
	REFLECTION_CLASSBUILDER_END(PotionData);

	REFLECTION_CLASSBUILDER_BEGIN(ZombiePotionActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<PotionData>, Potions);
	REFLECTION_CLASSBUILDER_END(ZombiePotionActionProps);
}

void ZombiePotionAction::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void ZombiePotionAction::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
