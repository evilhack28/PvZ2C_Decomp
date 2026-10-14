//
//  SingleColourFit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//

#include <EAText/internal/EATextSquishInternal.h>

#include <limits.h>

namespace EATextSquish
{
static const SingleColourLookup lookup_5_4[256] = {};
static const SingleColourLookup lookup_6_4[256] = {};

int FloatToInt(float a, int limit)
{
    int i = (int)(a + 0.5f);
    if (i < 0)
        i = 0;
    else if (i > limit)
        i = limit;
    return i;
}

/////////////// Lifecycle ///////////////

SingleColourFit::SingleColourFit(const ColorSet* colours)
    : ColourFit(colours)
{
    const Vec3* values = m_colours->GetPoints();
    m_colour[0] = (uint8_t)FloatToInt(255.0f * values->X(), 255);
    m_colour[1] = (uint8_t)FloatToInt(255.0f * values->Y(), 255);
    m_colour[2] = (uint8_t)FloatToInt(255.0f * values->Z(), 255);
    m_besterror = INT_MAX;
}

/////////////// Compression ///////////////

void SingleColourFit::Compress4(void* block)
{
    const SingleColourLookup* const lookups[] =
    {
        lookup_5_4,
        lookup_6_4,
        lookup_5_4
    };

    ComputeEndPoints(4, lookups);

    if (m_error < m_besterror)
    {
        uint8_t indices[16];
        m_colours->RemapIndices(&m_index, indices);
        WriteColourBlock4(m_start, m_end, indices, block);
        m_besterror = m_error;
    }
}

void SingleColourFit::ComputeEndPoints(int count, const SingleColourLookup* const* lookups)
{
    m_error = INT_MAX;
    for (int index = 0; index < count; ++index)
    {
        const SourceBlock* sources[3];
        int error = 0;
        for (int channel = 0; channel < 3; ++channel)
        {
            const SingleColourLookup* lookup = lookups[channel];
            int target = m_colour[channel];
            sources[channel] = lookup[target].sources + index;
            int diff = sources[channel]->error;
            error += diff * diff;
        }

        if (error < m_error)
        {
            m_start = Vec3((float)sources[0]->start * (1.0f / 31.0f),
                           (float)sources[1]->start * (1.0f / 63.0f),
                           (float)sources[2]->start * (1.0f / 31.0f));
            m_end = Vec3((float)sources[0]->end * (1.0f / 31.0f),
                         (float)sources[1]->end * (1.0f / 63.0f),
                         (float)sources[2]->end * (1.0f / 31.0f));
            m_index = (uint8_t)index;
            m_error = error;
        }
    }
}
}
