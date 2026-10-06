//
//  RiftSeedBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RiftSeedBank.h"
#include "SeedBankModule.h"

RiftSeedBankProperties::~RiftSeedBankProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftSeedBank);

void RiftSeedBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftSeedBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedBankNew);

	REFLECTION_CLASSBUILDER_END(RiftSeedBank);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftSeedBankProperties);

void RiftSeedBankProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftSeedBankProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedBankProperties);

	REFLECTION_CLASSBUILDER_END(RiftSeedBankProperties);
}
