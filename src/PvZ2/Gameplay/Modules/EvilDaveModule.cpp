//
//  EvilDaveModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EvilDaveModule.h"

EvilDaveModule::EvilDaveModule()
{
	m_checkCondition = 0;
}

EvilDaveModule::~EvilDaveModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EvilDaveModule);

void EvilDaveModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EvilDaveModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_checkCondition);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<UIWidget>, m_plantCountUI);
	REFLECTION_CLASSBUILDER_END(EvilDaveModule);
}
