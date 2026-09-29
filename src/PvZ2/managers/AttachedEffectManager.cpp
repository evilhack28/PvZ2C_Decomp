//
//  AttachedEffectManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AttachedEffectManager.h"

AttachedEffectManager::AttachedEffectManager()
{
}

AttachedEffectManager::~AttachedEffectManager()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AttachedEffectManager);

void AttachedEffectManager::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AttachedEffectManager);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObjectDictionary);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<AttachedEffect>, m_nodes);
	REFLECTION_CLASSBUILDER_END(AttachedEffectManager);
}
