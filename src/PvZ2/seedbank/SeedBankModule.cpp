//
//  SeedBankModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SeedBankModule.h"

SeedBankModule::SeedBankModule()
{
}

SeedBankModule::~SeedBankModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SeedBankModule);

void SeedBankModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SeedBankModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_resourcesLoaded);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, m_availableSeeds);
		REFLECTION_CLASSBUILDER_FIELD(SeedBankSelectionMethod, m_selectionMethod);
	REFLECTION_CLASSBUILDER_END(SeedBankModule);
}
