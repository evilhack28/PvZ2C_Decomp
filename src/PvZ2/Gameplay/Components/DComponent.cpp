//
//  DComponent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "DNode/DComponent.h"

/////////////// DComponent ///////////////

DComponent::~DComponent()
{
}

void DComponent::setEnabled(bool enabled)
{
	m_bEnabled = enabled;
}

const std::string& DComponent::getName() const
{
	return m_name;
}

void DComponent::setName(const std::string& name)
{
	m_name = name;
}

void DComponent::setOwner(DTransformNode* owner)
{
	m_pOwner = owner;
}

void DComponent::onUpdate()
{
}

void DComponent::onAdd()
{
}

void DComponent::onRemove()
{
}
