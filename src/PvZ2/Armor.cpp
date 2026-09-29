//
//  Armor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Armor.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Armor);

void Armor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Armor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ArmorPropertySheet>, m_propertySheetPtr);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_ownerZombiePtr);
		REFLECTION_CLASSBUILDER_FIELD(int, m_damageState);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_destroyed);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_armorFlagsOverride);
	REFLECTION_CLASSBUILDER_END(Armor);
}

void Armor::onTakeDamage(const DamageInfo& i_arg)
{
}

void Armor::onArmorDropped(std::string i_arg)
{
}
