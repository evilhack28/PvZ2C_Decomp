//
//  PneumaticSeedBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PneumaticSeedBank.h"

PneumaticSeedBank::~PneumaticSeedBank()
{
}

PneumaticSeedBankProperties::~PneumaticSeedBankProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PneumaticSeedBank);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PneumaticSeedBankProperties);

void PneumaticSeedBankProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PneumaticPlantEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantType);
	REFLECTION_CLASSBUILDER_END(PneumaticPlantEntry);

	REFLECTION_CLASSBUILDER_BEGIN(PneumaticDelayCondition);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxPackets);
		REFLECTION_CLASSBUILDER_FIELD(float, Delay);
	REFLECTION_CLASSBUILDER_END(PneumaticDelayCondition);

	REFLECTION_CLASSBUILDER_BEGIN(PneumaticSeedBankProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedBankProperties);

		REFLECTION_CLASSBUILDER_FIELD(bool, ManualPacketSpawning);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PneumaticPlantEntry>, InitialPlantList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PneumaticDelayCondition>, DelayConditions);
	REFLECTION_CLASSBUILDER_END(PneumaticSeedBankProperties);
}

#include "UIWidget.h"
void PneumaticSeedBank::onLevelStart()
{
	 UIWidget::updateState_Initializing();
}

void PneumaticSeedBank::unregisterForEvents()
{
}
