//
//  ColourFit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//

#include <EAText/internal/EATextSquishInternal.h>

namespace EATextSquish
{
/////////////// Lifecycle ///////////////

ColourFit::ColourFit(const ColorSet* colours)
    : m_colours(colours)
{
}

ColourFit::~ColourFit()
{
}

/////////////// Compression ///////////////

void ColourFit::Compress(void* block)
{
    Compress4(block);
}
}
