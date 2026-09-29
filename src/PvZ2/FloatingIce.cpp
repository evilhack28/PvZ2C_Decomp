//
//  FloatingIce.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FloatingIce.h"

FloatingIce::FloatingIce()
{
	m_sinked = 0;
	m_sinking = 0;
	m_needPlayCarryingAnim = 0;
	m_isCarryingDodoRider = 0;
}

FloatingIce::~FloatingIce()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FloatingIce);
