//
//  ConstraintNameMapper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//
/////////////// Lifecycle ///////////////

#include "PvZ/NameMapper.h"

static ConstraintNameMapper& (*const s_keepGetInstance)() __attribute__((used)) = &ConstraintNameMapper::GetInstance;

__asm__(".local __dso_handle\n.comm __dso_handle,8,8");

ConstraintNameMapper::ConstraintNameMapper()
{
    std::map<std::string, int> map;
    map["bonus_diamond_1"] = 2701;
    map["bonus_diamond_2"] = 2702;
    map["bonus_diamond_3"] = 2703;
    map["bonus_diamond_4"] = 2704;
    m_map = map;
}
