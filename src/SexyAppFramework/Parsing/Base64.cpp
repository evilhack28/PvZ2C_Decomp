//
//  Base64.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/Base64.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

Base64::Base64()
{
    SetMode(STANDARD);
}

Base64::Base64(Mode mode)
{
    SetMode(mode);
}

/////////////// Accessors ///////////////

size_t Base64::SizeForEncodeBuffer(size_t inputLength) const
{
    return (inputLength + 2) / 3 * 4;
}

size_t Base64::SizeForDecodeBuffer(size_t inputLength) const
{
    return (inputLength + 3) / 4 * 3;
}

/////////////// Encoding ///////////////

void Base64::Encode(Buffer* outputBuffer, const uchar* input, size_t inputLength)
{
    outputBuffer->Resize(SizeForEncodeBuffer(inputLength));
    Encode(outputBuffer->GetDataPtr(), input, inputLength);
}

void Base64::Encode(Buffer* outputBuffer, const Buffer* inputBuffer)
{
    Encode(outputBuffer, inputBuffer->GetDataPtr(), inputBuffer->GetDataLen());
}

/////////////// Decoding ///////////////

void Base64::Decode(Buffer* outputBuffer, const uchar* input, size_t inputLength)
{
    outputBuffer->Resize(SizeForEncodeBuffer(inputLength));
    Decode(outputBuffer->GetDataPtr(), input, inputLength);
}

void Base64::Decode(Buffer* outputBuffer, const Buffer* inputBuffer)
{
    Decode(outputBuffer, inputBuffer->GetDataPtr(), inputBuffer->GetDataLen());
}
