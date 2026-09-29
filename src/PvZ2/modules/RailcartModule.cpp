//
//  RailcartModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RailcartModule.h"

RailcartModule::~RailcartModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RailcartModule);

#include "RailcartModule.h"
void RailcartModule::onPostLoad()
{
	 RailcartModule::parseRailImages();
}
