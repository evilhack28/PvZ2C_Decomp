//
//  ParamCollection.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGL20RenderEffect.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidGL20RenderEffect::ParamCollection::ParamCollection()
{
}

AndroidGL20RenderEffect::ParamCollection::~ParamCollection()
{
}

/////////////// Logic ///////////////

AndroidGL20RenderEffect::ParamData* AndroidGL20RenderEffect::ParamCollection::GetParamNamed(const std::string& inName, bool inAllowCreate)
{
	ParamMap::iterator it = mParamMap.find(inName);
	if (it != mParamMap.end())
		return &it->second;

	if (inAllowCreate)
	{
		mParamMap[inName] = ParamData();
		return GetParamNamed(inName, false);
	}
	else
	{
		return false;
	}
}
