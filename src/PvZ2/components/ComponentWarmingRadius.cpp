//
//  ComponentWarmingRadius.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ComponentWarmingRadius.h"

#include "ComponentRadiusBurst.h"
void ComponentWarmingRadius::beginCoolDown()
{
	 ComponentRadiusBurst::calculateTimeForNextPropigate();
}
