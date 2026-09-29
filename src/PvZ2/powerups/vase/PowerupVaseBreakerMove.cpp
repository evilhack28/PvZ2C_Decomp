//
//  PowerupVaseBreakerMove.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"

PowerupVaseBreakerMove::PowerupVaseBreakerMove()
{
	m_dragging = 0;
	m_movingQueuedVase = 0;
}

PowerupVaseBreakerMove::~PowerupVaseBreakerMove()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupVaseBreakerMove);

void PowerupVaseBreakerMove::Draw(Sexy::Graphics* i_arg)
{
}
