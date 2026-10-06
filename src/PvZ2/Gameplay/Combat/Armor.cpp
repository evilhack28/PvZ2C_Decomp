//
//  Armor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Armor.h"
#include "Zombie.h"
#include "PopAnimRig.h"
#include "PopAnimRigHelper.h"
#include "ZombieParticle.h"
#include "ZombiePropertySheet.h"
#include "GameEventMgr.h"
#include "DamageInfo.h"
#include "TodLib/TodCommon.h"

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

const ArmorPropertySheet* Armor::getProps() const
{
	if (!m_cachedPropertySheet)
	{
		m_cachedPropertySheet = m_propertySheetPtr.Get();
	}
	return m_cachedPropertySheet;
}

std::string Armor::GetArmorType() const
{
	return getProps()->ArmorType;
}

ArmorTypeFlags Armor::GetArmorFlags() const
{
	return m_armorFlagsOverride == ARMOR_None ? getProps()->ArmorFlags : m_armorFlagsOverride;
}

bool Armor::IsDecorativePassthrough()
{
	return TestFlag(getProps()->ArmorFlags, ARMOR_PASSDAMAGE);
}

void Armor::onPostLoad()
{
	m_cachedPropertySheet = m_propertySheetPtr.Get();
}

void Armor::DestroyArmor()
{
	m_destroyed = true;
	updateDamageState();
}

void Armor::ReinitializeFromPropertySheet()
{
	SetPropertySheet(m_propertySheetPtr);
}

void Armor::SetPropertySheet(ArmorPropertySheetPtr i_propertySheetPtr)
{
	m_propertySheetPtr = i_propertySheetPtr;
	m_cachedPropertySheet = m_propertySheetPtr.Get();
	m_maxHealth = m_health = getProps()->BaseHealth;
}

Armor::Armor()
	: m_propertySheetPtr(nullptr)
	, m_ownerZombiePtr(nullptr)
	, m_health(0.0f)
	, m_maxHealth(0.0f)
	, m_damageState(-1)
	, m_destroyed(false)
	, m_armorFlagsOverride(ARMOR_None)
{
}

Armor::~Armor()
{
	m_cachedPropertySheet = nullptr;
}

void Armor::InitializeArmor(ArmorPropertySheetPtr i_propertySheet, RtWeakPtr<Zombie> i_owner)
{
	m_ownerZombiePtr = i_owner;
	SetPropertySheet(i_propertySheet);
	updateDamageState();
}

void Armor::updateDamageState()
{
	int newState;
	if (TestFlag(getProps()->ArmorFlags, ARMOR_DAMAGEABLE))
	{
		newState = -1;
		if (!m_destroyed)
		{
			newState = 0;
			for (size_t i = 0; i < getProps()->ArmorLayerHealth.size(); i++)
			{
				if (m_health < getProps()->ArmorLayerHealth[i])
				{
					newState++;
				}
			}
		}
	}
	else
	{
		newState = 0;
	}
	if (m_destroyed)
	{
		newState = -1;
	}
	if (m_damageState != newState)
	{
		m_damageState = newState;
		for (int i = 0; (size_t)i < getProps()->ArmorLayers.size(); i++)
		{
			m_ownerZombiePtr->GetAnimRig()->SetLayerVisibility(getProps()->ArmorLayers[(size_t)i], m_damageState == i);
		}
	}
}

ZombieParticle* Armor::DropArmor(DamageTypeFlags i_damageFlags)
{
	ZombieParticle* particle;
	if (m_destroyed)
	{
		return nullptr;
	}
	const ArmorPropertySheet* props = getProps();
	bool metallic = TestFlag(props->ArmorFlags, ARMOR_METALLIC);
	m_ownerZombiePtr->PlayPositionalSound(props->DropSoundEvent, 0.1f);
	if (TestFlag(props->ArmorFlags, ARMOR_DROPPABLE))
	{
		std::string name("", std::allocator<char>());
		if (props->ParticleLayerOverride.size() != 0)
		{
			name = props->ParticleLayerOverride[m_damageState];
		}
		if (name.empty() && props->ArmorLayers.size() > (size_t)m_damageState)
		{
			name = props->ArmorLayers[m_damageState];
		}
		if (!name.empty())
		{
			particle = SpawnZombieParticle(m_ownerZombiePtr.Get(), props->ArmorLayers, name);
			if (particle)
			{
				particle->SetAttribute(ZOMBIEPARTICLEATTRIBUTE_Helm, true);
				particle->SetAttribute(ZOMBIEPARTICLEATTRIBUTE_Metal, metallic);
				if (m_ownerZombiePtr->HasCondition(ZCONDITION_Shrunken))
				{
					particle->SetScale(m_ownerZombiePtr->GetProps()->ShrunkenScale);
				}
			}
			gMessageRouter->Broadcast(Message::ZombieDropArmor, m_ownerZombiePtr.Get(), i_damageFlags);
		}
		else
		{
			particle = nullptr;
		}
	}
	else
	{
		particle = nullptr;
	}
	m_destroyed = true;
	m_ownerZombiePtr->onArmorDropped(getProps()->ArmorType);
	updateDamageState();
	return particle;
}

DamageInfo Armor::TakeDamage(const DamageInfo& i_damageInfo)
{
	if (m_destroyed)
	{
		return i_damageInfo;
	}
	DamageInfo result;
	result = m_ownerZombiePtr->onArmorDamageTaken(i_damageInfo, getProps()->ArmorType);
	if (TestFlag(result.Flags, (DamageTypeFlags)8))
	{
		return result;
	}
	if (TestFlag(result.Flags, (DamageTypeFlags)0x10))
	{
		SetFlag(result.Flags, (DamageTypeFlags)0x10, false);
		return result;
	}
	onTakeDamage(result);
	if (EA_UNLIKELY(!TestFlag(result.Flags, (DamageTypeFlags)0x10000) && (!result.Instigator || !result.Instigator->IsA<Zombie>()) && !getProps()->ImpactSoundEvent.empty()))
	{
		m_ownerZombiePtr->PlayPositionalSound(getProps()->ImpactSoundEvent, 0.1f);
		m_ownerZombiePtr->SetHasPlayedImpactSound(true);
	}
	if (TestFlag(result.Flags, (DamageTypeFlags)2))
	{
		m_health = 0.0f;
	}
	float before = m_health;
	float amount = i_damageInfo.Amount;
	if (!TestFlag(getProps()->ArmorFlags, (ArmorTypeFlags)0x80))
	{
		m_health -= result.Amount;
	}
	result = i_damageInfo;
	if (!TestFlag(getProps()->ArmorFlags, (ArmorTypeFlags)8))
	{
		result.Amount = ClampFloat(amount - before, 0.0f, i_damageInfo.Amount);
	}
	if (m_health <= 0.0f)
	{
		DropArmor(i_damageInfo.Flags);
		m_destroyed = true;
	}
	updateDamageState();
	return result;
}

