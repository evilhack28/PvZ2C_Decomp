//
//  EffectAnimRig_LinkedTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_LinkedTile.h"

EffectAnimRig_LinkedTile::EffectAnimRig_LinkedTile()
{
}

EffectAnimRig_LinkedTile::~EffectAnimRig_LinkedTile()
{
}

#include "EffectAnimRig_LinkedTile.h"
void EffectAnimRig_LinkedTile::onAnimStopped()
{
	 EffectAnimRig_LinkedTile::PlayIdle();
}
