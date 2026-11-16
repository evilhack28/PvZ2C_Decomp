//
//  CollectableAvatarPieceType.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "CollectableSpring.h"

CollectableAvatarPieceType::~CollectableAvatarPieceType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableAvatarPieceType);

void CollectableAvatarPieceType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableAvatarPieceType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_ENUMBUILDER_BEGIN(PlantAvatarType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, E_AVATAR_NONE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(normal, E_AVATAR_NORMAL);
	REFLECTION_ENUMBUILDER_END(PlantAvatarType);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantName);
		REFLECTION_CLASSBUILDER_FIELD(PlantAvatarType, AvatarType);
	REFLECTION_CLASSBUILDER_END(CollectableAvatarPieceType);
}
