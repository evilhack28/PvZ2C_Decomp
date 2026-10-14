//
//  Image.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//
/////////////// ImageLib::Image ///////////////

#include "ImageLib/ImageLib.h"
#include <string.h>

namespace ImageLib
{

Image::Image()
{
    mWidth = 0;
    mHeight = 0;
    mBits = NULL;
    mOriginalSizeBytes = 0;
}

Image::Image(Image* theImage)
{
    mWidth = theImage->mWidth;
    mHeight = theImage->mHeight;
    mBits = new uint32[mWidth * mHeight];
    memcpy(mBits, theImage->GetBits(), mWidth * mHeight * 4);
    mOriginalSizeBytes = theImage->mOriginalSizeBytes;
}

Image::~Image()
{
    delete[] mBits;
}

int Image::GetWidth()
{
    return mWidth;
}

int Image::GetHeight()
{
    return mHeight;
}

uint32* Image::GetBits()
{
    return mBits;
}

}
