//
//  PlantNewAvatar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantNewAvatar.h"
#include "NameMapper.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PlantNewAvatar::~PlantNewAvatar()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlantNewAvatar);

void PlantNewAvatar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantNewAvatar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantBoost>, Boosts);

	REFLECTION_CLASSBUILDER_END(PlantNewAvatar);
}

/////////////// Accessors ///////////////

int PlantNewAvatar::GetNewAvatarID()
{
	return PlantNewAvatarMapper::GetInstance().GetIdForName(NewAvatarName);
}

int PlantNewAvatar::GetNewAvatarPieceID()
{
	return PlantNewAvatarPieceMapper::GetInstance().GetIdForName(NewAvatarName);
}
