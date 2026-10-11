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

/////////////// Accessors ///////////////

int AttachedEffectManager::Count()
{
	return m_nodes.size();
}

AttachedGameObjectNode& AttachedEffectManager::at(int i_index)
{
	return m_nodes[i_index];
}

AttachedGameObjectNode& AttachedEffectManager::add(const std::string& i_name)
{
	AttachedEffect effect(i_name);
	m_nodes.push_back(effect);
	return m_nodes[m_nodes.size() - 1];
}

void AttachedEffectManager::Clear()
{
	for (AttachedEffect effect : m_nodes)
		effect.Destroy();
	m_nodes.clear();
}

void AttachedEffectManager::remove(int i_index)
{
	m_nodes[i_index].Destroy();
	m_nodes.erase(m_nodes.begin() + i_index);
}

int AttachedEffectManager::indexOf(const std::string& i_name) const
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i].GetName() == i_name)
			return i;
	}
	return -1;
}

void AttachedEffectManager::update(float i_dt)
{
	for (int i = (int)m_nodes.size() - 1; i >= 0; i--)
	{
		m_nodes[i].Update(i_dt);
		if (!m_nodes[i].IsValid())
			m_nodes.erase(m_nodes.begin() + i);
	}
}

void AttachedEffectManager::UpdateDynamicScaleForAllEffects(float i_scale, const std::vector<std::string>& i_filters)
{
	for (int i = (int)m_nodes.size() - 1; i >= 0; i--)
	{
		std::string name = m_nodes[i].GetName();
		if (std::find(i_filters.begin(), i_filters.end(), name) == i_filters.end())
			m_nodes[i].UpdateDynamicScale(i_scale);
	}
}
