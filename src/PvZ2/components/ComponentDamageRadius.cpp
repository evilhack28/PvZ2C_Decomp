//
//  ComponentDamageRadius.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ComponentDamageRadius.h"

#include "ComponentRadiusBurst.h"
void ComponentDamageRadius::StartPulse()
{
	 ComponentRadiusBurst::calculateTimeForNextPropigate();
}

#include "ComponentRadiusBurst.h"
void ComponentDamageRadius::beginCoolDown()
{
	 ComponentRadiusBurst::pausePropagation();
}
