//
//  ConveyorSeedBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ConveyorSeedBank.h"
#include "SeedBankModule.h"

ConveyorSeedBankProperties::~ConveyorSeedBankProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ConveyorSeedBankProperties);

void ConveyorSeedBankProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ConveyorPlantEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantType);
	REFLECTION_CLASSBUILDER_END(ConveyorPlantEntry);

	REFLECTION_CLASSBUILDER_BEGIN(ConveyorSpeedCondition);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxPackets);
		REFLECTION_CLASSBUILDER_FIELD(float, Speed);
	REFLECTION_CLASSBUILDER_END(ConveyorSpeedCondition);

	REFLECTION_CLASSBUILDER_BEGIN(ConveyorDropDelayCondition);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxPackets);
		REFLECTION_CLASSBUILDER_FIELD(float, Delay);
	REFLECTION_CLASSBUILDER_END(ConveyorDropDelayCondition);

	REFLECTION_CLASSBUILDER_BEGIN(ConveyorSeedBankProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedBankProperties);

		REFLECTION_CLASSBUILDER_FIELD(bool, ManualPacketSpawning);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ConveyorPlantEntry>, InitialPlantList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ConveyorDropDelayCondition>, DropDelayConditions);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ConveyorSpeedCondition>, SpeedConditions);
	REFLECTION_CLASSBUILDER_END(ConveyorSeedBankProperties);
}

void ConveyorSeedBank::onRemoveSeed(const class ConveyorRemoveSeedInstruction & i_instruction)
{
}

void ConveyorSeedBank::setPacketPositions()
{
}

#include "ConveyorSeedBank.h"
void ConveyorSeedBank::PickAndAddSeedFromSeedPool()
{
	 ConveyorSeedBank::pickAndAddSeedFromSeedPool();
}

void ConveyorSeedBank::initLoadingResourcesGroupList()
{
}
