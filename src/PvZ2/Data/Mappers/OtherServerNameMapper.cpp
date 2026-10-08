//
//  OtherServerNameMapper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//
/////////////// Lifecycle ///////////////

#include "PvZ/NameMapper.h"

__asm__(".local __dso_handle\n.comm __dso_handle,8,8");

OtherServerNameMapper::OtherServerNameMapper()
{
    std::map<std::string, int> map;
    m_map = map;
}
