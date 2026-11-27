//
//  RSBPatchGenerator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "open_vcdiff/google/vcencoder.h"

using namespace Sexy;


/////////////// Lifecycle ///////////////

RSBPatchGenerator::RSBPatchGenerator(SexyAppBase* inApp)
{
    mApp = inApp;
}


/////////////// Patch ///////////////

uint8* RSBPatchGenerator::CreateBinaryDiffData(uint8* inBaseData, uint32 inBaseDataByteCount, uint8* inTargetData, uint32 inTargetDataByteCount, uint32& outBinaryDiffDataByteCount)
{
	uint32 aBaseDataByteCount = inBaseData ? inBaseDataByteCount : 0;
	outBinaryDiffDataByteCount = 0;
	std::string aDiffData;
	open_vcdiff::VCDiffEncoder aEncoder((const char*)inBaseData, aBaseDataByteCount);
	aEncoder.SetFormatFlags(open_vcdiff::VCD_FORMAT_INTERLEAVED);
	aEncoder.Encode((const char*)inTargetData, inTargetDataByteCount, &aDiffData);
	if (aDiffData.empty())
		return NULL;

	outBinaryDiffDataByteCount = aDiffData.size();
	uint8* aData = new uint8[outBinaryDiffDataByteCount];
	memcpy(aData, aDiffData.data(), outBinaryDiffDataByteCount);
	return aData;
}
