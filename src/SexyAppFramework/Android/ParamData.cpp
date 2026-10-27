//
//  ParamData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGL20RenderEffect.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

__attribute__((used)) static void EmitParamData()
{
	AndroidGL20RenderEffect::ParamData data;
}

/////////////// Logic ///////////////

void AndroidGL20RenderEffect::ParamData::SetValue(const float* inFloatData, uint inFloatCount)
{
	mFloatData.resize(inFloatCount);
	memcpy(&mFloatData[0], inFloatData, inFloatCount * sizeof(float));
	while (mFloatData.size() & 3)
		mFloatData.push_back(0.f);
}
