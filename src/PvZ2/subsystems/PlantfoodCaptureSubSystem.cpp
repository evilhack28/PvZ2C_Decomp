//
//  PlantfoodCaptureSubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantfoodCaptureSubSystem.h"

PlantfoodCaptureSubSystem::PlantfoodCaptureSubSystem()
{
}

PlantfoodCaptureSubSystem::~PlantfoodCaptureSubSystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantfoodCaptureSubSystem);

void PlantfoodCaptureSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantfoodOwnerLink);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, Owner);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<CollectablePlantfood>, Plantfood);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, TimeGrabbed);
	REFLECTION_CLASSBUILDER_END(PlantfoodOwnerLink);

	REFLECTION_CLASSBUILDER_BEGIN(PlantfoodCaptureSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_owners);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantfoodOwnerLink>, m_plantfoodLinks);
	REFLECTION_CLASSBUILDER_END(PlantfoodCaptureSubSystem);
}
