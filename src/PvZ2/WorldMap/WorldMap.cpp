//
//  WorldMap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap.h"
#include "WorldMapPropertySheet.h"
#include "ReflectionBuilder.h"
#include "WorldMap_EventBar.h"
#include "AnimationControllerHelpers.h"
#include "BusyAnimationManager.h"
#include "LawnApp.h"
#include "AudioMgr.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "WorldData.h"
#include "WorldMapCamera.h"
#include "UniverseMap.h"
#include "EffectAnimRig_ZombossHologram.h"
#include "GameStateMgr.h"
#include "WorldMap_LuaButtonsDelegate.h"
#include "UIWidget.h"
#include "PrimeText/PrimeText.h"
#include "ProfileUtils.h"

namespace RiftUtils { bool IsZombossUnlocked(); }

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

void WorldMap::onExitState_Loading(WorldMapState i_toState)
{
}

void WorldMap::onExitState_Initializing(WorldMapState i_toState)
{
}

void WorldMap::onExitState_Ready(WorldMapState i_toState)
{
}

void WorldMap::onEnterState_WaitingToDie(WorldMapState i_fromState)
{
}

void WorldMap::onExitState_WaitingToDie(WorldMapState i_toState)
{
}

void WorldMap::onExitState_BackgroundInit(WorldMapState i_toState)
{
}

void WorldMap::initLoadingResourcesGroupList()
{
	initSpecialWorldResourcesGroupList();
}

void WorldMap::onEnterState_BackgroundLoading(WorldMapState i_fromState)
{
	StartLoad();
}

void WorldMap::PurgeWorldMapActions()
{
	m_actionsMgr.ClearActions();
}

void WorldMap::ForceTutorialToFinish()
{
	handleTutorialEnd(true);
}

void WorldMap::SetPreviousState(GameState state)
{
	m_previousState = state;
}

void WorldMap::SwitchToLottery()
{
	QueueForTransition(GAME_Lottery);
}

void WorldMap::SwitchToLevelUp()
{
	QueueForTransition(GAME_LevelUp);
}

void WorldMap::SwitchToPlantAvatar()
{
	QueueForTransition(GAME_PlantAvatar);
}

void WorldMap::SwitchToPlantFamily()
{
	QueueForTransition(GAME_PlantFamily);
}

void WorldMap::SwitchToArtifact()
{
	QueueForTransition(GAME_ArtifactCultivation);
}

void WorldMap::SwitchToPlantGeneEnhancement()
{
	QueueForTransition(GAME_PlantGeneEnhancement);
}

void WorldMap::SwitchToNostalgiaPVZGameView()
{
	QueueForTransition(GAME_NostalgiaPVZ);
}

void WorldMap::SwitchToCustomLevelView()
{
	QueueForTransition(GAME_CustomLevel);
}

void WorldMap::OnPathDestinationAnimationFinished(const std::string& i_animName)
{
	m_mapPathDestinationOverlayRigOwner = NULL;
}

WorldMapActionManager& WorldMap::GetActionsMgr()
{
	return m_actionsMgr;
}

void WorldMap::SetAdviceText(SexyString i_text, MessageStyle i_messageStyle)
{
	m_showAdvice->SetLabel(i_text, i_messageStyle);
}

void WorldMap::onAdEnded(const std::string& i_placementOrigin, int i_coinsEarned, int i_videosWatched)
{
	m_waitingForAd = false;
}

void WorldMap::SetupUnchartedBirthdayEventBar()
{
	WorldMap_EventBar::SetBannerTypeOverride(WorldMap_EventBar::EVENT_BAR_UNCHARTED_BIRTHDAY);
}

void WorldMap::updateStateMachine()
{
	m_stateMachine.UpdateState();
}

std::vector<MapPathGroup>& WorldMap::GetMapPathGroups()
{
	return m_mapPathGroups;
}

std::vector<PopAnimRig*>& WorldMap::GetPopAnimRigs()
{
	return m_popAnimRigs;
}

void WorldMap::SetMouseDownPos(const Sexy::Point& i_mousePoint)
{
	m_mouseDownPos = i_mousePoint;
}

const Sexy::Point& WorldMap::GetMouseDownPos()
{
	return m_mouseDownPos;
}

const Sexy::Point& WorldMap::GetStartingMouseDownPos()
{
	return m_startingMouseDownPos;
}

void WorldMap::SetBaseOffset(const Sexy::Point i_offset)
{
	m_baseOffset = i_offset;
}

void WorldMap::KillTutorialInput()
{
	m_tutorialRequiresEventInput = NULL;
	m_tutorialRequiresNavInput = false;
	m_tutorialRequiresPopupInput = false;
}

void WorldMap::PlayRandomZombossTaunts()
{
	m_zombossNextTauntTime = 1.0f;
}

void WorldMap::onEnterState_Ready(WorldMapState i_fromState)
{
	mVisible = true;
}

void WorldMap::cleanUpCurrentEditEvent()
{
	m_editorCurrentEditEvent.SetParentEventPtr(NULL);
}

void WorldMap::onAdBeginShowing()
{
	m_waitingForAd = true;
}

void WorldMap::ResetCameraVelocity()
{
	m_cameraVelocity.x = 0.0f;
	m_cameraVelocity.y = 0.0f;
}

void WorldMap::CalculateMinMaxZoomForWorld(WorldData* i_world)
{
	m_cameraZoomMax = 1.0f;
	m_cameraZoomMin = 1.0f;
}

bool WorldMap::isTutorialDeprecated(MapTutorialState i_tutorial)
{
	return i_tutorial >= TUTORIAL_ALMANAC_INTRO_1 && i_tutorial <= TUTORIAL_COUNT;
}

void WorldMap::onYetiFUEDialogYesButton()
{
	gLawnApp->KillPVZ2Dialog();
}

void WorldMap::onExitState_BackgroundLoading(WorldMapState i_toState)
{
	gLawnApp->m_busyManager->StopBusyIcon();
}

WorldMapState WorldMap::getState() const
{
	return m_stateMachine.GetState();
}

void WorldMap::QueueForTransition(const GameState i_gameState)
{
	if (!m_quitWhenResourcesLoad)
	{
		m_queuedGameState = i_gameState;
		m_quitWhenResourcesLoad = true;
	}
}

void WorldMap::onGateCancelButtonPressed()
{
	m_interactingEvent = NULL;
	if (m_tutorialRequiresPopupInput)
	{
		handleTutorialEnd();
	}
}

void WorldMap::OnUnlockAllLevels()
{
	updateMapEventsArt();
}

bool WorldMap::IsActionQueued()
{
	return m_actionsMgr.Size() != 0;
}

PopAnimRig* WorldMap::GetPopAnimRigByID(const int16 i_popAnimID)
{
	return m_popAnimRigs[i_popAnimID];
}

void WorldMap::onWorldMapShown()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_World_Map_Events", NULL);
}

void WorldMap::onServerTimeReceived()
{
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	if (profile)
	{
		profile->RefreshEvent();
	}
}

bool WorldMap::IsInState(uint32 i_state) const
{
	return m_stateMachine.GetState() == i_state;
}

const bool WorldMap::IsUserInputEnabled()
{
	return m_tutorialScrollTimeStart == PVZ_EOT() && m_userInputEnabled;
}

const bool WorldMap::IsValidStateForInput()
{
	return m_tutorialScrollTimeStart == PVZ_EOT() && IsInState(WM_Ready);
}

bool WorldMap::CanBeClosed()
{
	if (!m_quitWhenResourcesLoad && !m_waitingForLevel && IsInState(WM_Ready))
	{
		return true;
	}
	return false;
}

bool WorldMap::IsLoaded()
{
	return getState() != WM_Loading && getState() != WM_BackgroundLoading;
}

void WorldMap::StopActions()
{
	WorldMap* worldMap = gLawnApp->GetWorldMap();
	if (worldMap)
	{
		worldMap->GetActionsMgr().StopActions();
	}
}

void WorldMap::DrawZombossHologram(Graphics* i_g, WorldMapCamera* i_camera, float i_posX, float i_posY)
{
	if (m_zombossHologramVisible)
	{
		i_camera->DrawPopAnimRig(m_zombossHologram, i_posX, i_posY, 1.0f, 1.0f, 0.0f);
	}
}

void WorldMap::cleanupZombossSoundRTPC()
{
	AudioMgr::GetInstancePtr()->UnregisterForAudio(m_zombossSoundID);
}

void WorldMap::remapWorldMapEvents()
{
	WorldMapUtils::GetWorldDataForEdit()->RemapWorldMapEvents();
	prepEditedWorld();
}

void WorldMap::refreshMapPathGroups()
{
	rebuildMapPathGroups(GetCurrentWorld());
}

void WorldMap::onRiftOverAcknowledged()
{
	gLawnApp->KillPVZ2Dialog();
	gGameStateMgr->ShowRiftMap();
}

void WorldMap::SetupRiftEventBar()
{
	WorldMap_EventBar::GetBannerTypeOverride();
	WorldMap_EventBar::SetBannerTypeOverride(RiftUtils::IsZombossUnlocked() ? WorldMap_EventBar::EVENT_BAR_RIFT_ZOMBOSS_READY : WorldMap_EventBar::EVENT_BAR_RIFT);
}

void WorldMap::loadMap(const std::string& i_worldName)
{
	setupMap();
	gatherRequiredResourcesFromMapEvents();
}

void WorldMap::PlayZombossSound(const std::string& i_sampleName)
{
	AudioMgr::GetInstancePtr()->SendEventThrottled(i_sampleName, 0.0f, m_zombossSoundID);
}

void WorldMap::QueueForLoadLevel(const std::string& i_levelName, const LevelSource i_levelSource)
{
	m_quitWhenResourcesLoad = true;
	m_queueLevelToLoad = i_levelName;
	m_queueLevelSource = i_levelSource;
}

void WorldMap::initializeToUniverseMap()
{
	m_universeMap->SetVisible(true);
	m_actionsMgr.SetRequiresInit(true);
}

void WorldMap::updateState_BackgroundInit()
{
	if (PVZ_T() >= m_stateEnterTime)
	{
		setState(WM_Ready);
	}
}

void WorldMap::setupMap()
{
	remapWorldMapEvents();
	initLoadedWorldResources();
	updateMapEventsArt();
}

void WorldMap::onEnterState_Loading(WorldMapState i_fromState)
{
	gLawnApp->m_busyManager->StartBusyIcon();
	gatherRequiredResourcesFromMapEvents();
	StartLoad();
}

void WorldMap::DoRewardUpgradeDialog(MapEventItem* i_event)
{
	if (m_tutorialRequiresEventInput)
	{
		m_tutorialRequiresEventInput = NULL;
		handleTutorialEnd();
	}
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	m_queuedMapPathEvent = i_event;
}

void WorldMap::PrepForLoading()
{
	if (getState() == WorldMapState_INVALID)
	{
		initLoadingResourcesGroupList();
		setState(WM_Loading);
	}
}

void WorldMap::setCurrentMapEventItem(MapEventItem* i_item)
{
	if (m_editorCurrentMapEventItem)
	{
		m_editorCurrentMapEventItem->m_isSelected = false;
	}
	m_editorCurrentMapEventItem = i_item;
	EditorClearSelectionGroup();
	if (m_editorCurrentMapEventItem)
	{
		m_editorCurrentMapEventItem->m_isSelected = true;
		m_editorSelectionGroup.push_back(m_editorCurrentMapEventItem);
	}
}

void WorldMap::EditorClearSelectionGroup()
{
	for (size_t i = 0; i < m_editorSelectionGroup.size(); i++)
	{
		m_editorSelectionGroup[i]->m_isSelected = false;
	}
	m_editorSelectionGroup.clear();
}

void WorldMap::TouchesCanceled()
{
	WorldMap_LuaButtonsDelegate::TouchesCanceled();
	m_currentTouchIdent = 0;
	UIWidget::ProcessedMouseUp(-100, -100, 0);
	if (m_zooming && m_zoomBounceStartTime == PVZ_EOT())
	{
		m_zoomBounceStartTime = PVZ_T();
		m_zoomBounceStartScale = m_cameraZoom;
	}
}

void WorldMap::onAppEnteredBackground()
{
	if (m_zooming || m_zoomBounceStartTime != PVZ_EOT())
	{
		m_zooming = true;
		m_zoomBounceStartTime = PVZ_T() - 0.2f;
		updateZoomBounce();
	}
}

void WorldMap::updateState_Loading()
{
	if (!hasRequiredResources())
	{
		gGameStateMgr->ShowLogoScreen();
		return;
	}
	if (checkLoadComplete())
	{
		CompleteLoad();
	}
}

void WorldMap::CenterOnMapEvent(const std::string& i_mapEventName, const bool i_preventScroll)
{
	if (i_mapEventName.empty())
	{
		return;
	}
	MapEventItem* mapEventItem = WorldMapUtils::GetWorldData()->FindEventByName(i_mapEventName);
	if (mapEventItem)
	{
		CenterOnMapEvent(mapEventItem, i_preventScroll);
		updateMapEventsArt();
	}
}

void WorldMap::RemovedFromManager(Sexy::WidgetManager* i_widgetManager)
{
	Widget::RemovedFromManager(i_widgetManager);
	if (m_universeMap)
	{
		gLawnApp->mWidgetManager->RemoveWidget(m_universeMap);
		gLawnApp->SafeDeleteWidget(m_universeMap);
		m_universeMap = NULL;
	}
}

void WorldMap::showZenGardenReminder(const SexyString& i_adviceText, const std::string& i_narrationEventId)
{
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	if (!profile->GetNarrationEventCompleted(i_narrationEventId))
	{
		profile->CompleteNarrationEvent(i_narrationEventId);
		m_showAdvice->SetLabel(i_adviceText, MESSAGE_STYLE_WORLDMAP_WINNI);
		m_tutorialTimeEnd = PVZ_T() + 5.0f;
	}
	m_tutorialState = TUTORIAL_NONE;
}

void WorldMap::TouchBegan(const Sexy::Touch& i_touch)
{
	WorldMap_LuaButtonsDelegate::TouchBegan(i_touch, mX, mY);
	if (!IsUserInputEnabled() || !IsValidStateForInput())
	{
		m_currentTouchIdent = 0;
		return;
	}
	if (m_currentTouchIdent == 0)
	{
		m_currentTouchIdent = i_touch.ident;
		handleTouchBegan(i_touch.location.mX, i_touch.location.mY);
	}
}

void WorldMap::SetStartingMouseDownPos(const Sexy::Point& i_mousePoint)
{
	m_startingMouseDownPos = i_mousePoint;
	m_mouseStationaryCount = 0;
	SetMouseDownPos(i_mousePoint);
	SetIsPressed(true);
	SetIsDragging(false);
	SetIsScrollLockedHorizontal(false);
	SetIsScrollLockedVertical(false);
}

void WorldMap::ZoomOutNoAnimation()
{
	ZoomOut();
	m_zooming = true;
	m_zoomBounceStartTime = PVZ_T() - 0.2f;
	updateZoomBounce();
	m_hasSavedStartLocation = false;
}

void WorldMap::PlacePathDestinationAnimationOnEvent(PopAnimRig* i_animation, MapEventItem* i_eventItem)
{
	if (m_mapPathDestinationOverlayRig)
	{
		delete m_mapPathDestinationOverlayRig;
	}
	m_mapPathDestinationOverlayRig = i_animation;
	m_mapPathDestinationOverlayRigOwner = i_eventItem;
}

void WorldMap::OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta)
{
	if (!IsUserInputEnabled() || !IsValidStateForInput())
	{
		m_currentTouchIdent = 0;
	}
}

void WorldMap::onStartPVZ1Level(const std::string& i_levelName)
{
	Sexy::PrimeText::Instance()->ClearGlyphCache();
	gGameStateMgr->setCurrentLevelIsHardMode(false);
	SwitchToGameLevel(i_levelName, LEVELSOURCE_WorldMap, false);
}

void WorldMap::CancelTutorial(MapTutorialState i_tutorialName)
{
	m_tutorialState = TUTORIAL_NONE;
	ProfileUtils::Profile()->SetActiveTutorial(TUTORIAL_NONE);
	if (i_tutorialName == TUTORIAL_DANGERROOM_INTRO_2 || i_tutorialName == TUTORIAL_JOUST)
	{
		popUIState();
	}
}

void WorldMap::updateState_BackgroundLoading()
{
	StartLoad();
	if (checkLoadComplete())
	{
		CompleteLoad();
	}
	else
	{
		updateState_Ready();
	}
}

void WorldMap::onEnterState_BackgroundInit(WorldMapState i_fromState)
{
	initLoadedWorldResources();
	m_actionsMgr.QueueAllInitActions();
	if (Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile()->GetLastWorldMapZoomLevel() < 0.99f)
	{
		ZoomOutNoAnimation();
	}
}

void WorldMap::DrawPopanimRig(Graphics* i_g, WorldMapCamera* i_camera, const int16 i_popAnimID, float i_posX, float i_posY, float i_scaleX, float i_scaleY, float i_rotation)
{
	i_camera->DrawPopAnimRig(m_popAnimRigs[i_popAnimID], i_posX, i_posY, i_scaleX, i_scaleY, i_rotation);
}

void WorldMap::DrawWorldPopanimRig(Graphics* i_g, WorldMapCamera* i_camera, const int16 i_worldPopAnimID, WorldData* i_worldData, float i_posX, float i_posY, float i_scaleX, float i_scaleY, float i_rotation)
{
	i_camera->DrawPopAnimRig(i_worldData->m_worldPopAnimRigs[i_worldPopAnimID], i_posX, i_posY, i_scaleX, i_scaleY, i_rotation);
}

RT_CLASS_IMPLEMENT(WorldMap);
