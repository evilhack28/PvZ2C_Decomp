//
//  AutoInitResourceGen3.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AutoInitResourceGen3::AutoInitResourceGen3(const std::string& theResourceManifestFileName, const ResGenInfo& theInfo)
{
	if (ResourceManagerInfo::sInstance == NULL)
		ResourceManagerInfo::sInstance = new ResourceManagerInfo();

	std::string aFileName = theResourceManifestFileName;
	int n = (int)aFileName.length();
	for (int i = 0; i < n; i++)
	{
		if (aFileName[i] == '\\')
			aFileName[i] = '/';
	}

	ResourceManagerInfo::sInstance->mResGenInfoMap[aFileName] = theInfo;
}
