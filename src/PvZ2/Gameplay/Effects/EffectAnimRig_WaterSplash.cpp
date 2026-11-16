//
//  EffectAnimRig_WaterSplash.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_WaterSplash.h"
#include "BoardConstants.h"
#include "ScaledApp.h"

/////////////// EffectAnimRig_WaterSplash ///////////////

RT_CLASS_IMPLEMENT(EffectAnimRig_WaterSplash);

void EffectAnimRig_WaterSplash::onPopAnimInitialized()
{
	PopAnimRig::onPopAnimInitialized();
}

void EffectAnimRig_WaterSplash::onPreDraw(Graphics* i_g)
{
	i_g->SetClipRect(S(BoardConstants::GRIDSQUARE_WIDTH() * 5 + 200), 0, i_g->mDestImage->mWidth, S(800));
}

void EffectAnimRig_WaterSplash::onPostDraw(Graphics* i_g)
{
	i_g->ClearClipRect();
}
