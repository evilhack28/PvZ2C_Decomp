//
//  UniverseMap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "UniverseMap.h"
#include "ReflectionBuilder.h"
#include "UniverseMap.h"

/////////////// Accessors ///////////////

bool UniverseMap::GetHasEnteredUniverseFlag() const
{
	return m_hasEnteredUniverse;
}

bool UniverseMap::IsLoaded()
{
	return getState() != UM_Loading;
}

/////////////// Logic ///////////////

void UniverseMap::SlideInWorldBank()
{
}

void UniverseMap::onWorldPreviewButtonPressed()
{
}

void UniverseMap::initLoadingResourcesGroupList()
{
}

void UniverseMap::DrawOverlay(Graphics* i_g)
{
}

void UniverseMap::DrawMapLines(Graphics* i_g)
{
}

void UniverseMap::ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget)
{
}

void UniverseMap::onStargatePurchased(const MapEventItem* i_props)
{
	 UniverseMap::syncButtonStates();
}

void UniverseMap::ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget)
{
}

bool UniverseMap::NeedPlayTargetWorldRevealedAnim(const std::string& i_world)
{
	return false;
}

void UniverseMap::KeyChar(SexyChar i_char)
{
}

void UniverseMap::KeyDown(KeyCode i_key)
{
}

void UniverseMap::MouseMove(const int i_mouseX, const int i_mouseY)
{
}

UniverseMapState UniverseMap::getState() const
{
	return m_stateMachine.GetState();
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(UniverseMap);
