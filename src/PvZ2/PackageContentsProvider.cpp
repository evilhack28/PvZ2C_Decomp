//
//  PackageContentsProvider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PackageContentsProvider.h"

/////////////// PackageContentsProvider ///////////////

PackageContentsProvider::PackageContentsProvider(const std::string& i_defaultPackagePath, const std::string& i_overridePackagePath)
	: m_defaultPackagePath(i_defaultPackagePath)
	, m_overridePackagePath(i_overridePackagePath)
{
}

PackageContentsProvider::~PackageContentsProvider() = default;
