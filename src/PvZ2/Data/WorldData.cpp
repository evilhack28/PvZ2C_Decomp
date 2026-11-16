//
//  WorldData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldData.h"
#include "WorldMapUtils.h"
#include "PopAnimRig.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

WorldData::~WorldData()
{
}

/////////////// Accessors ///////////////

SexyString WorldData::GetLocalizedWorldName() const
{
    return WorldMapUtils::GetLocalizedWorldName(m_worldName);
}

/////////////// Logic ///////////////

const MapEventItem* WorldData::FindEventByEventId(int i_id) const
{
    std::vector<MapEventItem>::const_iterator it = m_eventList.begin();
    std::vector<MapEventItem>::const_iterator end = m_eventList.end();
    for (; it != end; ++it)
    {
        const MapEventItem* event = &*it;
        if (event->m_eventId == i_id)
            return event;
    }
    return nullptr;
}

void WorldData::DeletePopAnimRigData()
{
    for (size_t i = 0; i < m_worldPopAnimRigs.size(); i++)
    {
        if (m_worldPopAnimRigs[i] != nullptr)
        {
            delete m_worldPopAnimRigs[i];
            m_worldPopAnimRigs[i] = nullptr;
        }
    }
    m_worldPopAnimRigs.clear();

    for (size_t i = 0; i < m_worldArtPieces.size(); i++)
    {
        if (m_worldArtPieces[i].PopAnimRigPtr != nullptr)
        {
            delete m_worldArtPieces[i].PopAnimRigPtr;
            m_worldArtPieces[i].PopAnimRigPtr = nullptr;
        }
    }

    for (size_t i = 0; i < m_mapPieces.size(); i++)
    {
        if (m_mapPieces[i].GetWorldPopanimID() != -1)
            m_mapPieces[i].SetWorldPopanimID(-1);
    }

    for (size_t i = 0; i < m_eventList.size(); i++)
    {
        if (m_eventList[i].GetWorldPopanimID() != -1)
            m_eventList[i].SetWorldPopanimID(-1);
    }
}

uint16 WorldData::GetNextEventId()
{
    uint16 maxId = 0;
    int i = 0;
    while (i < m_eventList.size())
    {
        uint16 eventId = m_eventList[i++].GetEventId();
        maxId = std::max(eventId, maxId);
    }
    return maxId + 1;
}

int WorldData::CountMainSpineLevels()
{
    int count = 0;
    while (true)
    {
        std::string dataName = Sexy::StrFormat("%s%d", m_worldName.c_str(), count + 1);
        if (!FindEventOfTypeByDataName(MAPEVENT_LEVEL_ENTRANCE, dataName))
            break;
        count++;
    }
    return count;
}

MapEventItem* WorldData::FindEventOfTypeByName(MapEventType i_eventType, const std::string& i_eventName)
{
    std::vector<MapEventItem>::iterator it = m_eventList.begin();
    std::vector<MapEventItem>::iterator end = m_eventList.end();
    if (i_eventType != MAPEVENT_NONE)
    {
        for (; it != end; ++it)
        {
            MapEventItem* event = &*it;
            if (event->GetEventType() == i_eventType && event->GetName() == i_eventName)
                return event;
        }
    }
    else
    {
        for (; it != end; ++it)
        {
            MapEventItem* event = &*it;
            if (event->GetName() == i_eventName)
                return event;
        }
    }
    return nullptr;
}

MapEventItem* WorldData::FindEventOfTypeByDataName(MapEventType i_eventType, const std::string& i_dataName)
{
    std::vector<MapEventItem>::iterator it = m_eventList.begin();
    std::vector<MapEventItem>::iterator end = m_eventList.end();
    if (i_eventType != MAPEVENT_NONE)
    {
        for (; it != end; ++it)
        {
            MapEventItem* event = &*it;
            if (event->GetEventType() == i_eventType && event->GetDataString() == i_dataName)
                return event;
        }
    }
    else
    {
        for (; it != end; ++it)
        {
            MapEventItem* event = &*it;
            if (event->GetDataString() == i_dataName)
                return event;
        }
    }
    return nullptr;
}

MapEventItem* WorldData::FindEvent(const std::function<bool (const MapEventItem*)>& i_acceptanceFunc)
{
    std::vector<MapEventItem>::iterator it = m_eventList.begin();
    std::vector<MapEventItem>::iterator end = m_eventList.end();
    for (; it != end; ++it)
    {
        MapEventItem* event = &*it;
        if (i_acceptanceFunc(event))
            return event;
    }
    return nullptr;
}

MapEventItem* WorldData::FindEventByName(const std::string& i_eventName)
{
    return FindEventOfTypeByName(MAPEVENT_NONE, i_eventName);
}

MapEventItem* WorldData::FindEventByDataName(const std::string& i_dataName)
{
    return FindEventOfTypeByDataName(MAPEVENT_NONE, i_dataName);
}

bool WorldData::ContainsEvent(const MapEventItem* i_event)
{
    return FindEventByName(i_event->GetName()) != nullptr;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(WorldData);

void WorldData::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(MapEventType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, MAPEVENT_NONE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(level, MAPEVENT_LEVEL_ENTRANCE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plantbox, MAPEVENT_REWARD_PLANT_BOX);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plant, MAPEVENT_REWARD_PLANT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(upgrade, MAPEVENT_REWARD_UPGRADE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(powerup, MAPEVENT_REWARD_POWERUP);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(star_gate, MAPEVENT_STAR_GATE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(key_gate, MAPEVENT_KEY_GATE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(path_node, MAPEVENT_PATH_NODE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(island, MAPEVENT_ISLAND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(doodad, MAPEVENT_DOODAD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(giftbox, MAPEVENT_REWARD_GIFT_BOX);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(custom_art, MAPEVENT_CUSTOM_ART);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvp_house, MAPEVENT_PVP_HOUSE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvp_house_achieve, MAPEVENT_PVP_HOUSE_ACHIEVE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvp_cloud, MAPEVENT_PVP_CLOUD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvp_cloud_price, MAPEVENT_PVP_CLOUD_PRICE);
	REFLECTION_ENUMBUILDER_END(MapEventType);

	REFLECTION_ENUMBUILDER_BEGIN(MapEventSubType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, EVENT_SUBTYPE_NONE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(normal, EVENT_SUBTYPE_NORMAL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(timed, EVENT_SUBTYPE_TIMED);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(laststand, EVENT_SUBTYPE_LASTSTAND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(minigame, EVENT_SUBTYPE_MINIGAME);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(arena, EVENT_SUBTYPE_ARENA);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(conveyor, EVENT_SUBTYPE_CONVEYOR);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(zomboss, EVENT_SUBTYPE_ZOMBOSS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvz1_normal, EVENT_SUBTYPE_PVZ1_NORMAL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvz1_conveyor, EVENT_SUBTYPE_PVZ1_CONVEYOR);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvz1_laststand, EVENT_SUBTYPE_PVZ1_LASTSTAND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvz1_elite, EVENT_SUBTYPE_PVZ1_ELITE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvz1_zomboss, EVENT_SUBTYPE_PVZ1_ZOMBOSS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(rift_timed, EVENT_SUBTYPE_RIFT_TIMED);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plantwars, (MapEventSubType)14);
	REFLECTION_ENUMBUILDER_END(MapEventSubType);

	REFLECTION_ENUMBUILDER_BEGIN(MapTutorialState);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, TUTORIAL_NONE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(map_intro, TUTORIAL_MAP_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(challenge_intro, TUTORIAL_CHALLENGE_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(almanac_intro, TUTORIAL_ALMANAC_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(daily_sign, TUTORIAL_NEW_DAILY_SIGN);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(continue_egypt, TUTORIAL_CONTINUE_EGYPT_3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(store_intro, TUTORIAL_STORE_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(quest_intro, TUTORIAL_QUEST_INTRO);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(star_intro, TUTORIAL_STAR_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(star_touchwood, TUTORIAL_STAR_TOUCHWOOD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(gacha_intro, TUTORIAL_GACHA_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(gacha_intro2, TUTORIAL_GACHA_INTRO_2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(continue_egypt6, TUTORIAL_CONTINUE_EGYPT_6);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(travellog_intro, TUTORIAL_TRAVELLOG);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(continue_egypt8, TUTORIAL_CONTINUE_EGYPT_8);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(accessory_intro, TUTORIAL_ACCESSORY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(gacha_intro3, TUTORIAL_GACHA_INTRO_3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(levelup_intro, TUTORIAL_LEVEL_UP_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(hard_level_intro, TUTORIAL_HARD_LEVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(first_recharge_intro, TUTORIAL_FIRST_RECHARGE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plantfamily_intro, TUTORIAL_PLANTFAMILY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(new_challenge_intro, TUTORIAL_CHALLENGE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(joust_intro, TUTORIAL_JOUST);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(danger_room_intro, TUTORIAL_DANGERROOM_INTRO_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(crystal_store_intro, TUTORIAL_CRYSTAL_STORE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(galaxy_intro, TUTORIAL_GALAXY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plantadventure_intro, TUTORIAL_PLANTADVENTURE_INTRO);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvp_intro, TUTORIAL_MAP_PVP_INTRO);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(transgenosis_intro, TUTORIAL_TRANSGENOSIS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(rift_intro, TUTORIAL_RIFT_WORLD_OPEN);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvz1_intro, TUTORIAL_PVZ1_WORLD_OPEN);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(daily_sigh, TUTORIAL_DAILY_SIGN);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(danger_room_intro_2, TUTORIAL_DANGERROOM_INTRO_2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(artifact_intro, TUTORIAL_ARTIFACT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(custom_level_intro, TUTORIAL_CUSTOM_LEVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(custom_creator, TUTORIAL_CUSTOM_LEVEL_CREATOR);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(custom_play, TUTORIAL_CUSTOM_LEVEL_PLAY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(penny_classroom_intro, TUTORIAL_PENNY_CLASSROOM);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pvz2_uncharted_mode_intro, TUTORIAL_PVZ2_UNCHARTED_MODE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(card_game, TUTORIAL_CARD_GAME);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(card_game_play, TUTORIAL_CARD_GAME_PLAY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(card_game_play_new, TUTORIAL_CARD_GAME_PLAY_NEW);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(gene_enhancement, TUTORIAL_GENEENHANCEMENT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(newpvp, TUTORIAL_NEWPVP);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(gene_enhancement_new, TUTORIAL_GENEENHANCEMENT_NEW);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(special_uncharted_event, TUTORIAL_SPECIAL_UNCHARTED_EVENT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(anniversary_uncharted_event, TUTORIAL_SPECIAL_UNCHARTED_ANNIVERSARY_EVENT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(anniversary_halloween_uncharted_event, TUTORIAL_SPECIAL_UNCHARTED_ANNIVERSARY_HALLOWEEN_EVENT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(iceage_uncharted_event, TUTORIAL_SPECIAL_UNCHARTED_ICEAGE_EVENT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(spring_festival_2024_uncharted_event, TUTORIAL_SPECIAL_UNCHARTED_SPRING_FESTIVAL_2024_EVENT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(arborday_uncharted_event, TUTORIAL_EX_COUNT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(childrensday_uncharted_event, (MapTutorialState)77);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(zombie_resilience, (MapTutorialState)78);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(minigame_copycats, (MapTutorialState)79);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(needforspeed_202406_uncharted_event, (MapTutorialState)80);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plantwars, (MapTutorialState)82);
	REFLECTION_ENUMBUILDER_END(MapTutorialState);

	REFLECTION_ENUMBUILDER_BEGIN(LevelNodeType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(normal, NORMAL_LEVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(minigame, MINIGAME_LEVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(miniboss, MINIBOSS_LEVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boss, BOSS_LEVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(nonfinalboss, NONFINAL_BOSS_LEVEL);
	REFLECTION_ENUMBUILDER_END(LevelNodeType);

	REFLECTION_ENUMBUILDER_BEGIN(WorldMapEventStatus);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(undiscovered, EVENTSTATUS_UNDISCOVERED);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(locked, EVENTSTATUS_LOCKED);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(unlocked, EVENTSTATUS_UNLOCKED);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(cleared, EVENTSTATUS_CLEARED);
	REFLECTION_ENUMBUILDER_END(WorldMapEventStatus);

	REFLECTION_CLASSBUILDER_BEGIN(MapEventItem);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_position);
		REFLECTION_CLASSBUILDER_FIELD(uint16, m_imageID);
		REFLECTION_CLASSBUILDER_FIELD(MapEventType, m_eventType);
		REFLECTION_CLASSBUILDER_FIELD(MapEventSubType, m_eventSubType);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_name);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_toggleName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_dataString);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_unlockedFrom);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_visibleFrom);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_parentEvent);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_displayText);
		REFLECTION_CLASSBUILDER_FIELD(uint32, m_cost);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_autoVisible);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_completedNarrationID);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_unlockedNarrationID);
		REFLECTION_CLASSBUILDER_FIELD(MapTutorialState, m_worldMapTutorial);
		REFLECTION_CLASSBUILDER_FIELD(WorldMapEventStatus, m_worldMapTutorialVisibleWhen);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isArtFlipped);
		REFLECTION_CLASSBUILDER_FIELD(LevelNodeType, m_levelNodeType);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isChallengeType);
		REFLECTION_CLASSBUILDER_FIELD(int8, m_drawLayer);
		REFLECTION_CLASSBUILDER_FIELD(int16, m_rotationAngle);
		REFLECTION_CLASSBUILDER_FIELD(float, m_rotationRate);
		REFLECTION_CLASSBUILDER_FIELD(float, m_scaleX);
		REFLECTION_CLASSBUILDER_FIELD(float, m_scaleY);
		REFLECTION_CLASSBUILDER_FIELD(int8, m_parallaxLayer);
		REFLECTION_CLASSBUILDER_FIELD(uint16, m_eventId);
		REFLECTION_CLASSBUILDER_FIELD(int8, m_filter);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_inheritAssetFilter);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_zombossNodePopAnimStr);
	REFLECTION_CLASSBUILDER_END(MapEventItem);

	REFLECTION_CLASSBUILDER_BEGIN(WorldData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(std::vector<MapEventItem>, m_mapPieces);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<MapEventItem>, m_eventList);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_worldName);
		REFLECTION_CLASSBUILDER_FIELD(uint64, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(uint16, m_resGroupID);
		REFLECTION_CLASSBUILDER_FIELD(Rect, m_boundingRect);
		REFLECTION_CLASSBUILDER_FIELD(uint8, m_worldId);
		REFLECTION_CLASSBUILDER_FIELD(uint8, m_version);
	REFLECTION_CLASSBUILDER_END(WorldData);
}
