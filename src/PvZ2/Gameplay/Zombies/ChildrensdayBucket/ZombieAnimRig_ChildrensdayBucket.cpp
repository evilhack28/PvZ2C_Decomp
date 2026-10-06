//
//  ZombieAnimRig_ChildrensdayBucket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Tutorial.h"

ZombieAnimRig_ChildrensdayBucket::ZombieAnimRig_ChildrensdayBucket()
{
}

ZombieAnimRig_ChildrensdayBucket::~ZombieAnimRig_ChildrensdayBucket()
{
}

const std::vector<std::string>& ZombieAnimRig_ChildrensdayBucket::getBucketLayerNames()
{
	static std::string sLayerNameArray[] = {
		"zombie_armor_bucket_norm",
		"zombie_armor_bucket_damage_01",
		"zombie_armor_bucket_damage_02",
	};
	static std::vector<std::string> sLayerNames(sLayerNameArray, sLayerNameArray + 3);
	return sLayerNames;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ChildrensdayBucket);

void ZombieAnimRig_ChildrensdayBucket::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ChildrensdayBucket);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ChildrensdayBasic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ChildrensdayBucket);
}
