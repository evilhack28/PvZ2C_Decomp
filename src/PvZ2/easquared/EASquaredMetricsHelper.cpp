//
//  EASquaredMetricsHelper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "EASquaredMetricsHelper.h"

#include "LawnApp.h"
#include "UniverseMap.h"
#include "WorldMap.h"

using namespace Sexy;

/////////////// EASquaredMetricsHelper ///////////////

namespace EASquaredMetricsHelper {

const std::string GetButtonSource()
{
	WorldMap* worldMap = gLawnApp->GetWorldMap();
	if (worldMap == NULL)
		return "EA2Unknown";
	if (worldMap->m_universeMap->mVisible)
		return "EA2Universe";
	return "EA2World";
}

}
