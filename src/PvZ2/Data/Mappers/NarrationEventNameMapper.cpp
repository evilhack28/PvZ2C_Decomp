//
//  NarrationEventNameMapper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//
/////////////// Lifecycle ///////////////

#include "PvZ/NameMapper.h"

static NarrationEventNameMapper& (*const s_keepGetInstance)() __attribute__((used)) = &NarrationEventNameMapper::GetInstance;

__asm__(".local __dso_handle\n.comm __dso_handle,8,8");

NarrationEventNameMapper::NarrationEventNameMapper()
{
    std::map<std::string, int> map;
    map["nar_pirate_worldmap_intro"] = 1;
    map["nar_egypt_worldmap_intro"] = 2;
    map["nar_almanac_intro"] = 3;
    map["nar_challenge_branch_intro"] = 4;
    map["nar_store_intro"] = 5;
    map["nar_cowboy_worldmap_intro"] = 6;
    map["nar_yeti_intro"] = 7;
    map["nar_stargate_intro"] = 8;
    map["nar_dgr_egypt"] = 9;
    map["nar_dgr_cowboy"] = 10;
    map["nar_dgr_pirate"] = 11;
    map["nar_egypt_star_intro"] = 12;
    map["nar_dgr_powerups"] = 13;
    map["nar_star_task_intro"] = 14;
    map["nar_sunbomb_tutorial"] = 15;
    map["nar_dgr_festival"] = 16;
    map["nar_vasebreaker_first_time_tutorial"] = 17;
    map["nar_dgr_festival_level_one"] = 18;
    map["nar_dgr_festival_level_two"] = 19;
    map["nar_dgr_festival_level_three"] = 20;
    map["nar_dgr_festival_level_four"] = 21;
    map["nar_worldmap_plantbox_intro"] = 22;
    map["nar_worldmap_plantgj_intro"] = 23;
    map["nar_dgr_festival_level_endless"] = 24;
    map["nar_map_pvp_intro"] = 25;
    map["nar_pvp_trainzb_intro"] = 26;
    map["nar_star_intro"] = 27;
    map["nar_star_touchwood"] = 28;
    map["nar_activity_levels_intro"] = 29;
    map["nar_activity_bosschallenge_intro"] = 30;
    m_map = map;
}
