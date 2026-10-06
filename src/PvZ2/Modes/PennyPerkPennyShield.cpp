//
//  PennyPerkPennyShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PennyPerkPennyShield.h"

PennyPerkPennyShield::PennyPerkPennyShield()
{
}

PennyPerkPennyShield::~PennyPerkPennyShield()
{
}

PennyPerkPennyShieldProperties::PennyPerkPennyShieldProperties()
{
}

PennyPerkPennyShieldProperties::~PennyPerkPennyShieldProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkPennyShield);

void PennyPerkPennyShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkPennyShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkTimedEffect);

	REFLECTION_CLASSBUILDER_END(PennyPerkPennyShield);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkPennyShieldProperties);

void PennyPerkPennyShieldProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkPennyShieldProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, TimesBetweenApplications);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<int>>, ShieldColumns);
	REFLECTION_CLASSBUILDER_END(PennyPerkPennyShieldProperties);
}

#include "PennyPerkPennyShield.h"
void PennyPerkPennyShield::onUpdate()
{
	 PennyPerkPennyShield::createShields();
}
