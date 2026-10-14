//
//  Sym3x3.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//

#include <EAText/internal/EATextSquishInternal.h>

namespace EATextSquish
{
/////////////// Lifecycle ///////////////

Sym3x3::Sym3x3(float s)
{
    for (int i = 0; i < 6; ++i)
        m_x[i] = s;
}
}
