//
//  PopAnimRigHelper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/PopAnim.h"

using namespace Sexy;

void getTransform(const PASpriteDef* i_spriteDef, PAFrame* i_frame, int i_index, PATransform* o_transform)
{
	*o_transform = i_spriteDef->mObjectPosVector[i_frame->mFrameObjectPosIndexVector[i_index]].mTransform;
}
