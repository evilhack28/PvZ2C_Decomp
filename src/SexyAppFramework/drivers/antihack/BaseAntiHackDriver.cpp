//
//  BaseAntiHackDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/antihack/BaseAntiHackDriver.h"
#include "SexyAppFramework/Buffer.h"
#include "SexyAppFramework/Crypt/Rijndael.h"
#include "SexyAppFramework/Crypt/SexyMD5.h"
#include <stdlib.h>
#include <string.h>

using namespace Sexy;

namespace Sexy
{
const char* pkey = "com_popcap_pvz2_magento_product_2013_05_05";
}

/////////////// Lifecycle ///////////////

BaseAntiHackDriver::BaseAntiHackDriver()
{
	mSalt = "Zomb1esd0ntlik3Passw0rd5";
}

BaseAntiHackDriver::~BaseAntiHackDriver()
{
}

/////////////// Accessors ///////////////

bool BaseAntiHackDriver::IsPackageHacked()
{
	return false;
}

/////////////// Encryption ///////////////

void BaseAntiHackDriver::GenerateKeyIV(const char* pKey, std::string& strKey, std::string& strIV)
{
	MD5 md5;
	md5.update(pKey, strlen(pKey));
	strKey = md5.toString();
	strIV = strKey.substr(4, 28);
}

void BaseAntiHackDriver::EncodeBuffer(Buffer& inBuffer, Buffer& outBuffer)
{
	int dataLen = inBuffer.GetDataLen();
	char padding[24] = {0};
	int blockCount = dataLen / 24;
	if (dataLen % 24 != 0)
		blockCount++;
	int encodedLen = blockCount * 24;

	char* data = (char*)malloc(encodedLen);
	memcpy(data, inBuffer.GetDataPtr(), inBuffer.GetDataLen());
	memcpy(data + inBuffer.GetDataLen(), padding, encodedLen - inBuffer.GetDataLen());

	std::string key;
	std::string iv;
	GenerateKeyIV(pkey, key, iv);

	outBuffer.Clear();
	outBuffer.Resize(encodedLen + 2);
	outBuffer.GetDataPtr()[0] = 0x10;
	outBuffer.GetDataPtr()[1] = 0;

	CRijndael rijndael;
	rijndael.MakeKey(key.c_str(), iv.c_str(), 32, 24);
	rijndael.Encrypt(data, (char*)outBuffer.GetDataPtr() + 2, encodedLen, CRijndael::CBC);
	free(data);
}

void BaseAntiHackDriver::DecodeBuffer(Buffer& inBuffer, Buffer& outBuffer)
{
	uchar version = inBuffer.GetDataPtr()[0];
	uchar reserved = inBuffer.GetDataPtr()[1];
	if ((version >> 4) != 1)
		return;

	std::string key;
	std::string iv;
	GenerateKeyIV(pkey, key, iv);

	CRijndael rijndael;
	rijndael.MakeKey(key.c_str(), iv.c_str(), 32, 24);

	int dataLen = inBuffer.GetDataLen() - 2;
	outBuffer.Clear();
	outBuffer.Resize(dataLen);

	int blockCount = dataLen / 24;
	if (dataLen % 24 != 0)
		blockCount++;
	rijndael.Decrypt((char*)inBuffer.GetDataPtr() + 2, (char*)outBuffer.GetDataPtr(), blockCount * 24, CRijndael::CBC);
}
