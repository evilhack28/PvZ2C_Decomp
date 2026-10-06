//
//  ParallaxCache.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "ParallaxCache.h"
#include "WorldMapPropertySheet.h"
#include "ScaledApp.h"
#include "LawnApp.h"

/////////////// Construction ///////////////

ParallaxCache::ParallaxCache()
	: m_numberOfForegroundLayers(0)
{
}

/////////////// Layers ///////////////

int ParallaxCache::layerIndexToInternalIndex(int i_layerIndex)
{
	return i_layerIndex + m_numberOfForegroundLayers;
}

int ParallaxCache::GetMinimumLayerIndex()
{
	return -m_numberOfForegroundLayers;
}

int ParallaxCache::GetMaximumLayerIndex()
{
	return (int)m_multipliers.size() - m_numberOfForegroundLayers - 1;
}

void ParallaxCache::expandStorageIfNeededForLayer(int i_layerIndex)
{
	if (i_layerIndex < 0 && -i_layerIndex > m_numberOfForegroundLayers)
	{
		int extra = -i_layerIndex - m_numberOfForegroundLayers;
		m_multipliers.insert(m_multipliers.begin(), extra, 0.0f);
		m_offsets.insert(m_offsets.begin(), extra, 0.0f);
		m_numberOfForegroundLayers = -i_layerIndex;
	}
	else
	{
		size_t needed = i_layerIndex + m_numberOfForegroundLayers + 1;
		if (m_multipliers.size() < needed)
		{
			m_multipliers.resize(needed);
			m_offsets.resize(needed);
		}
	}
}

/////////////// Multipliers ///////////////

void ParallaxCache::setMultiplier(int i_layerIndex, float i_speedMultiplier)
{
	expandStorageIfNeededForLayer(i_layerIndex);
	m_multipliers[layerIndexToInternalIndex(i_layerIndex)] = i_speedMultiplier;
}

float ParallaxCache::getMultiplier(int i_layerIndex)
{
	return m_multipliers[layerIndexToInternalIndex(i_layerIndex)];
}

void ParallaxCache::InitializeMultipliers(WorldMapPropertySheet& i_worldMapPropertySheet)
{
	setMultiplier(-4, i_worldMapPropertySheet.ParallaxSpeedLayerForeground4);
	setMultiplier(-3, i_worldMapPropertySheet.ParallaxSpeedLayerForeground3);
	setMultiplier(-2, i_worldMapPropertySheet.ParallaxSpeedLayerForeground2);
	setMultiplier(-1, i_worldMapPropertySheet.ParallaxSpeedLayerForeground1);
	setMultiplier(0, i_worldMapPropertySheet.ParallaxSpeedLayer0);
	setMultiplier(1, i_worldMapPropertySheet.ParallaxSpeedLayer1);
	setMultiplier(2, i_worldMapPropertySheet.ParallaxSpeedLayer2);
	setMultiplier(3, i_worldMapPropertySheet.ParallaxSpeedLayer3);
	setMultiplier(4, i_worldMapPropertySheet.ParallaxSpeedLayer4);
	setMultiplier(5, i_worldMapPropertySheet.ParallaxSpeedLayer5);
	setMultiplier(6, i_worldMapPropertySheet.ParallaxSpeedLayer6);
	setMultiplier(7, i_worldMapPropertySheet.ParallaxSpeedLayer7);
	setMultiplier(8, i_worldMapPropertySheet.ParallaxSpeedLayer8);
	setMultiplier(9, i_worldMapPropertySheet.ParallaxSpeedLayer9);
	setMultiplier(10, i_worldMapPropertySheet.ParallaxSpeedLayer10);
}

/////////////// Offsets ///////////////

void ParallaxCache::RecalculateOffsets(float i_cameraOffset)
{
	for (size_t i = 0; i < m_multipliers.size(); i++)
		m_offsets[i] = (1.0f - m_multipliers[i]) * i_cameraOffset;

	m_offsets[layerIndexToInternalIndex(10)] += (float)(gLawnApp->mScreenBounds.mWidth - S(800)) * 0.5f;
}

float ParallaxCache::GetOffsetForLayer(int i_layerIndex)
{
	return m_offsets[layerIndexToInternalIndex(i_layerIndex)];
}
