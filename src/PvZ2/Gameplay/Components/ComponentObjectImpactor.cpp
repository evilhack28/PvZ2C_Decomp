//
//  ComponentObjectImpactor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ComponentObjectImpactor.h"

ComponentObjectImpactor::ComponentObjectImpactor()
{
}

ComponentObjectImpactor::~ComponentObjectImpactor()
{
}

ComponentObjectImpactorProps::~ComponentObjectImpactorProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentObjectImpactor);

void ComponentObjectImpactor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentObjectImpactor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ComponentBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_PopAnim> >, m_affectedEffects);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<class Projectile> >, m_affectedProjectiles);
		REFLECTION_CLASSBUILDER_FIELD(ComponentObjectImpactorProps, m_props);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_disabled);
	REFLECTION_CLASSBUILDER_END(ComponentObjectImpactor);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentObjectImpactorProps);

void ComponentObjectImpactorProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentObjectImpactorProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_END(ComponentObjectImpactorProps);
}
