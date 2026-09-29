//
//  ZombiePVPChickenFarmer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPChickenFarmer.h"

ZombiePVPChickenFarmerProps::ZombiePVPChickenFarmerProps()
{
}

ZombiePVPChickenFarmerProps::~ZombiePVPChickenFarmerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPChickenFarmer);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPChickenFarmerProps);

void ZombiePVPChickenFarmerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPChickenFarmerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieChickenFarmerProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ActiveChickenTypeName);
	REFLECTION_CLASSBUILDER_END(ZombiePVPChickenFarmerProps);
}
