//
//  AndroidFileSearch.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/file/android/AndroidAsyncIOFileDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidFileSearch::AndroidFileSearch(std::string const & pattern, std::string const & path, DIR * dir)
{
	mPattern = pattern;
	mPath = path;
	mDir = dir;
}

AndroidFileSearch::~AndroidFileSearch()
{
}
