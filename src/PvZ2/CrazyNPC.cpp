//
//  CrazyNPC.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CrazyNPC.h"

void CrazyNPC::StopHolding()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CrazyNPC);

#include "CrazyNPC.h"
void CrazyNPC::Update()
{
	 CrazyNPC::updateStateMachine();
}
