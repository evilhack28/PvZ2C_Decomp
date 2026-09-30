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

void WorldMap::EditorMouseUp(const int i_arg0, const int i_arg1, const int i_arg2)
{
}

void WorldMap::DrawEditorLabel(Graphics* i_arg0, const SexyString& i_arg1, const EditorInputArea& i_arg2)
{
}

void WorldMap::EditorMouseDown(const int i_arg0, const int i_arg1, const int i_arg2)
{
}

void WorldMap::EditorMouseMove(const int i_arg0, const int i_arg1)
{
}

void WorldMap::DrawEditorButton(Graphics* i_arg0, const Sexy::Rect& i_arg1, const SexyString& i_arg2, const bool i_arg3)
{
}

void WorldMap::LoadSandboxLevel(const std::string i_arg)
{
}

void WorldMap::EditorRemoveEvent(const MapEventItem* i_arg0, bool i_arg1)
{
}

void WorldMap::EditorRenameEvent(MapEventItem* i_arg0, const std::string& i_arg1)
{
}

void WorldMap::EditorRenameWorld(WorldData* i_arg0, const std::string i_arg1)
{
}

void WorldMap::EditorRemoveEvents(std::vector<MapEventItem*> i_arg0, bool i_arg1)
{
}

void WorldMap::DrawEditorTextField(Graphics* i_arg0, const SexyString& i_arg1, const EditorInputArea& i_arg2)
{
}

void WorldMap::EditorDecoupleEvent(const MapEventItem* i_arg)
{
}

void WorldMap::EditorHandleDialogInput(const int i_arg0, const int i_arg1)
{
}

void WorldMap::EditorHandleMenuBarInput(const int i_arg0, const int i_arg1)
{
}

bool WorldMap::shouldPlayWorldKeyTutorial(PlayerInfo* i_arg)
{
	return false;
}

void WorldMap::DoWorldMapPlantRewardDialog(PlantTypePtr i_arg)
{
}

void WorldMap::EditorSelectAllEventsInRect(const int& i_arg0, const int& i_arg1, const int& i_arg2, const int& i_arg3)
{
}

void WorldMap::StartWorldKeyRewardAnimation(ActionWorldKeyRewardAnimation* i_arg)
{
}

void WorldMap::testToClearUniverseTutorials(PlayerInfo* i_arg)
{
}

MapEventItem* WorldMap::EditorGetAnyMapEventAtLocation(const int& i_arg0, const int& i_arg1)
{
	return NULL;
}

MapEventItem* WorldMap::EditorGetMapEventItemAtLocation(const int& i_arg0, const int& i_arg1, const MapEventType& i_arg2)
{
	return NULL;
}

bool WorldMap::shouldPlayUniverseIntroTutorial(PlayerInfo* i_arg)
{
	return false;
}

MapEventItem* WorldMap::EditorGetAnyMapArtEventAtLocation(const int& i_arg0, const int& i_arg1)
{
	return NULL;
}

bool WorldMap::shouldPlayUnusableWorldKeyTutorial(PlayerInfo* i_arg)
{
	return false;
}

MapEventItem* WorldMap::EditorGetAnyMapEventAtLocationOnAnyMap(const int& i_arg0, const int& i_arg1)
{
	return NULL;
}

void WorldMap::newMap(const std::string& i_arg)
{
}

void WorldMap::KeyChar(SexyChar i_arg)
{
}

void WorldMap::KeyDown(KeyCode i_arg)
{
}

void WorldMap::saveMap(int i_arg)
{
}

void WorldMap::MouseMove(const int i_arg0, const int i_arg1)
{
}
