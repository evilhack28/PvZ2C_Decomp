//
//  Vec3.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//

#include <EAText/internal/EATextSquishInternal.h>

namespace EATextSquish
{
/////////////// Lifecycle ///////////////

Vec3::Vec3(float s)
{
    m_x = s;
    m_y = s;
    m_z = s;
}

Vec3::Vec3(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
}
