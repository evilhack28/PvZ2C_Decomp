//
//  ModularBoardEntity.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ModularBoardEntity.h"
#include "ReflectionBuilder.h"
#include "ResourceHelpers.h"
#include "TimeMgr.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(ModularBoardEntity);
void ModularBoardEntity::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ModularBoardEntity);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;
	REFLECTION_CLASSBUILDER_END(ModularBoardEntity);
}

ModularBoardEntity::ModularBoardEntity()
{
}

ModularBoardEntity::~ModularBoardEntity()
{
	clearAttachedEffects();
}

void ModularBoardEntity::onDestroy()
{
	ModularBoardEntity::clearAttachedEffects();
}

void ModularBoardEntity::onUpdate()
{
	updateOverlayEffects();
}

/////////////// Effects ///////////////

AttachedEffect& ModularBoardEntity::AddAttachedEffect(const char* iEffectName, const char* iPanAnimName, const char* iAnimName, const SexyVector3& iOffset, int iRenderLayerOffset, bool iPlayOnce, bool iDisableDynamicScaling)
{
	AttachedEffect& effect = static_cast<AttachedEffect&>(m_attachedEffects.FindOrCreate(iEffectName));
	effect.InitializeWithAnimation(GetPAMByName(iPanAnimName).Get());
	if (!iPlayOnce)
		effect.PlayAnimLooped(iAnimName);
	else
		effect.PlayAnimAndDestroy(iAnimName);
	effect.Attach(this, iOffset, iRenderLayerOffset);
	effect.m_disableDynamicScaling = iDisableDynamicScaling;
	onEffectAttached(effect, iDisableDynamicScaling);
	return effect;
}

void ModularBoardEntity::RemoveAttachedEffect(const char* i_entityName)
{
	m_attachedEffects.Remove(i_entityName);
}

void ModularBoardEntity::DetachAttachedEffect(const char* i_entityName)
{
	AttachedEffect* effect = GetAttachedEffect(i_entityName);
	if (effect->IsValid())
		effect->Detach();
}

AttachedEffect* ModularBoardEntity::GetAttachedEffect(const std::string& i_entityName)
{
	if (m_attachedEffects.Contains(i_entityName))
		return static_cast<AttachedEffect*>(&m_attachedEffects.FindOrCreate(i_entityName));
	return NULL;
}

void ModularBoardEntity::clearAttachedEffects()
{
	m_attachedEffects.Clear();
}

void ModularBoardEntity::onEffectAttached(AttachedEffect& i_effect, bool i_disableDynamicScaling)
{
}

void ModularBoardEntity::updateOverlayEffects()
{
	m_attachedEffects.Update(PVZ_Dt());
}
