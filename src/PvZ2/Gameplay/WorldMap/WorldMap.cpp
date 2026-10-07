//
//  WorldMap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap.h"
#include "WorldMapPropertySheet.h"

void WorldMap::onYetiSpawned()
{
}

void WorldMap::saveMapManifest()
{
}

void WorldMap::calculateCameraY()
{
}

void WorldMap::onNewVersionFound()
{
}

bool WorldMap::IsYetiBadgeVisible()
{
	return false;
}

float WorldMap::GetSpeedFactorNodeReveal()
{
	return 1.0f;
}

void WorldMap::onGoToEventButtonPressed()
{
}

void WorldMap::EditorEditCurrentMapEvent()
{
}

void WorldMap::EndWorldKeyRewardAnimation()
{
}

void WorldMap::EditorFinalizeEditCurrentMapEvent()
{
}

void WorldMap::onActivateStarGateAnimationFinished()
{
}

void WorldMap::onFinalizeStarGateAnimationFinished()
{
}

void WorldMap::queueQuestToastFeatureItemQuickStore()
{
}

void WorldMap::EditorMouseUp(const int i_mouseX, const int i_mouseY, const int i_clickCount)
{
}

void WorldMap::DrawEditorLabel(Graphics* i_g, const SexyString& i_labelText, const EditorInputArea& i_labelArea)
{
}

void WorldMap::EditorMouseDown(const int i_mouseX, const int i_mouseY, const int i_clickCount)
{
}

void WorldMap::EditorMouseMove(const int i_mouseX, const int i_mouseY)
{
}

void WorldMap::DrawEditorButton(Graphics* i_g, const Sexy::Rect& i_rect, const SexyString& i_label, const bool i_isDown)
{
}

void WorldMap::LoadSandboxLevel(const std::string i_levelname)
{
}

void WorldMap::EditorRemoveEvent(const MapEventItem* i_removeEvent, bool i_decoupleEvent)
{
}

void WorldMap::EditorRenameEvent(MapEventItem* i_event, const std::string& i_newName)
{
}

void WorldMap::EditorRenameWorld(WorldData* i_worldData, const std::string i_newWorldName)
{
}

void WorldMap::EditorRemoveEvents(std::vector<MapEventItem*> i_eventsToRemove, bool i_decoupleEvent)
{
}

void WorldMap::DrawEditorTextField(Graphics* i_g, const SexyString& i_labelText, const EditorInputArea& i_labelArea)
{
}

void WorldMap::EditorDecoupleEvent(const MapEventItem* i_removeEvent)
{
}

void WorldMap::EditorHandleDialogInput(const int i_mouseX, const int i_mouseY)
{
}

void WorldMap::EditorHandleMenuBarInput(const int i_mouseX, const int i_mouseY)
{
}

bool WorldMap::shouldPlayWorldKeyTutorial(PlayerInfo* i_playerInfo)
{
	return false;
}

void WorldMap::DoWorldMapPlantRewardDialog(PlantTypePtr i_awardedPlant)
{
}

void WorldMap::EditorSelectAllEventsInRect(const int& i_startX, const int& i_startY, const int& i_endX, const int& i_endY)
{
}

void WorldMap::StartWorldKeyRewardAnimation(ActionWorldKeyRewardAnimation* i_animationAction)
{
}

void WorldMap::testToClearUniverseTutorials(PlayerInfo* i_playerInfo)
{
}

MapEventItem* WorldMap::EditorGetAnyMapEventAtLocation(const int& i_mouseX, const int& i_mouseY)
{
	return NULL;
}

MapEventItem* WorldMap::EditorGetMapEventItemAtLocation(const int& i_mouseX, const int& i_mouseY, const MapEventType& i_eventType)
{
	return NULL;
}

bool WorldMap::shouldPlayUniverseIntroTutorial(PlayerInfo* i_playerInfo)
{
	return false;
}

MapEventItem* WorldMap::EditorGetAnyMapArtEventAtLocation(const int& i_mouseX, const int& i_mouseY)
{
	return NULL;
}

bool WorldMap::shouldPlayUnusableWorldKeyTutorial(PlayerInfo* i_playerInfo)
{
	return false;
}

MapEventItem* WorldMap::EditorGetAnyMapEventAtLocationOnAnyMap(const int& i_mouseX, const int& i_mouseY)
{
	return NULL;
}

void WorldMap::newMap(const std::string& i_worldName)
{
}

void WorldMap::KeyChar(SexyChar i_char)
{
}

void WorldMap::KeyDown(KeyCode i_key)
{
}

void WorldMap::saveMap(int i_filter)
{
}

void WorldMap::MouseMove(const int i_mouseX, const int i_mouseY)
{
}
