//
//  FeastClient.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtSerialJsonParser.h"
#include <stdlib.h>

using namespace Sexy::RtSerial;

/////////////// Allocation ///////////////

void* JsonParser::FeastClient::LibMalloc(unsigned long inSize)
{
	void* ptr = malloc(inSize);
	if (!ptr)
		LibError("Out of memory");
	return ptr;
}

void* JsonParser::FeastClient::LibRealloc(void* inPtr, unsigned long inNewSize)
{
	void* ptr = realloc(inPtr, inNewSize);
	if (!ptr)
		LibError("Out of memory");
	return ptr;
}

void JsonParser::FeastClient::LibFree(void* inPtr)
{
	if (inPtr)
		free(inPtr);
}

/////////////// Errors ///////////////

void JsonParser::FeastClient::LibError(const char* inErrorStr)
{
	Sexy::OutputDebugStrF("FEAST Error: %s\n", inErrorStr);
}
