//
//  TextureRestitchBuffer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "TextureRestitchBuffer.h"

/////////////// TextureRestitchBuffer ///////////////

TextureRestitchBuffer::TextureRestitchBuffer()
{
	textureInProgress = false;
	isInitialized = false;
	textureBufferSize = 0;
	textureBuffer = NULL;
}

TextureRestitchBuffer::~TextureRestitchBuffer()
{
	freeBuffer();
}

void TextureRestitchBuffer::Initialize(uint bufferSize)
{
	if (!isInitialized || textureBufferSize < bufferSize)
	{
		allocBuffer(bufferSize);
	}
	isInitialized = true;
	Clear(false);
}

void TextureRestitchBuffer::allocBuffer(uint bufferSize)
{
	freeBuffer();
	textureBuffer = new uchar[bufferSize];
	textureBufferSize = bufferSize;
}

void TextureRestitchBuffer::freeBuffer()
{
	if (textureBuffer)
	{
		delete[] textureBuffer;
	}
	textureBuffer = NULL;
	textureBufferSize = 0;
}

void TextureRestitchBuffer::Clear(bool i_okToClearBuffer)
{
	bytesInBuffer = 0;
	textureInProgress = false;
	if (i_okToClearBuffer)
	{
		freeBuffer();
	}
}

void TextureRestitchBuffer::Add(int textureID, const uchar* buffer, int bytesToAdd)
{
	int bytesToCopy = bytesToAdd;
	if (bytesInBuffer + bytesToAdd > textureBufferSize)
	{
		bytesToCopy = textureBufferSize - bytesInBuffer;
	}
	memcpy(textureBuffer + bytesInBuffer, buffer, bytesToCopy);
	textureIDInProgress = textureID;
	textureInProgress = true;
	bytesInBuffer += bytesToCopy;
}
