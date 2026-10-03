//
//  Feast.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//
#include "Feast.h"
#include "FeastInternal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

namespace FEAST
{

/////////////// Library client ///////////////

class CDefaultLibClient : public ILibClient
{
public:
	virtual void* LibMalloc(unsigned long inSize) { return malloc(inSize); }
	virtual void* LibRealloc(void* inPtr, unsigned long inNewSize) { return realloc(inPtr, inNewSize); }
	virtual void LibFree(void* inPtr) { free(inPtr); }
	virtual void LibError(const char* inErrorStr) { printf("%s", inErrorStr); exit(1); }
};

static CDefaultLibClient sDefaultClient;

static char sBuf[1024];

ILibClient* LIB_GetDefaultClient() { return &sDefaultClient; }

ILibClient*& LIB_GetClientRef()
{
	// .data keeps the guard first in .bss, as the differ expects
	static ILibClient* sClient __attribute__((section(".data"))) = LIB_GetDefaultClient();
	return sClient;
}

ILibClient* LIB_SetClient(ILibClient* inClient)
{
	ILibClient* prev = LIB_GetClientRef();
	if (inClient)
		LIB_GetClientRef() = inClient;
	else
	{
		ILibClient* d = LIB_GetDefaultClient();
		LIB_GetClientRef() = d;
	}
	return prev;
}

ILibClient* LIB_GetClient() { return LIB_GetClientRef(); }

float LIB_GetVersion() { return 1.04f; }

void* LIB_ClientMalloc(NDword inSize)
{
	ILibClient* c = LIB_GetClientRef();
	void* p = c->LibMalloc(inSize + sizeof(ILibClient*));
	*(ILibClient**)p = LIB_GetClientRef();
	return (char*)p + sizeof(ILibClient*);
}

void* LIB_ClientRealloc(void* inPtr, NDword inSize)
{
	ILibClient* c = ((ILibClient**)inPtr)[-1];
	void* p = c->LibRealloc((char*)inPtr - sizeof(ILibClient*), inSize + sizeof(ILibClient*));
	*(ILibClient**)p = c;
	return (char*)p + sizeof(ILibClient*);
}

void LIB_ClientFree(void* inPtr)
{
	if (inPtr)
	{
		ILibClient* c = ((ILibClient**)inPtr)[-1];
		c->LibFree((char*)inPtr - sizeof(ILibClient*));
	}
}

char* LIB_Va(const char*& inFmt, char* outBuf, ...)
{
	if (!inFmt)
		return 0;
	if (!outBuf)
		outBuf = sBuf;
	va_list args;
	va_start(args, outBuf);
	vsprintf(outBuf, inFmt, args);
	va_end(args);
	return outBuf;
}

void LIB_Errorf(const char* inFmt, ...)
{
	ILibClient* c = LIB_GetClientRef();
	c->LibError(LIB_Va(inFmt, 0));
}

/////////////// Parser / lexer internals ///////////////

class CPrsParser;

class CPrsParseState
{
public:
	unsigned long mField0;
	unsigned long* mItems;
	bool mFlag;

	static void* operator new(size_t, CPrsParser* inParser, size_t inCount);
};

class CPrsParseStateProd
{
public:
	unsigned long mField0;
	unsigned long mField8;
	unsigned long mField10;
	int mField18;

	static void* operator new(size_t, CPrsParser* inParser, size_t inCount);
};

class CPrsParser
{
public:
	char mPad[0x8010];
	CPrsParseState mStates[0x400];
	unsigned long mNumStates;
	CPrsParseStateProd mStateProds[0x4000];
	unsigned long mNumStateProds;

	static void* operator new(size_t inSize);
	static void operator delete(void* inPtr);
};

class CPrsParseProd
{
public:
	unsigned long mField0;
	unsigned long mLhs;
	unsigned long mCount;
	char mPad[0x20];
	unsigned long* mSyms;

	bool operator==(CPrsParseProd& inOther);
};

class CPrsASTNode
{
public:
	static unsigned long sNodeCount;
	static void* operator new(size_t inSize);
	static void operator delete(void* inPtr);
};

class CPrsCSTNode
{
public:
	static unsigned long sNodeCount;
	static void* operator new(size_t inSize);
	static void operator delete(void* inPtr);
};

class CLexLexer
{
public:
	static void* operator new(size_t inSize);
	static void operator delete(void* inPtr);
};

class CLexBitSet
{
public:
	unsigned char* mBits;

	CLexBitSet& operator+=(unsigned long inBit);
	CLexBitSet& operator-=(unsigned long inBit);
};

class CLexDfaAcceptItem
{
public:
	unsigned long mField0;
	unsigned long mField8;
	unsigned long mField10;
	unsigned char mFlag;

	bool operator==(const CLexDfaAcceptItem& inOther);
	CLexDfaAcceptItem& operator=(const CLexDfaAcceptItem& inOther);
};

struct CLexDfaPartition
{
	char mData[0x2020];
};

class CLexDfaPartitionSet
{
public:
	CLexDfaPartition mParts[1];

	CLexDfaPartition& operator[](int inIndex);
};


void* CPrsParseState::operator new(size_t, CPrsParser* inParser, size_t inCount)
{
	if (inParser->mNumStates >= 0x400)
		LIB_Errorf("CPrsParseState: Too many states");
	CPrsParseState* state = &inParser->mStates[inParser->mNumStates++];
	state->mField0 = 0;
	state->mItems = LIB_Malloc(unsigned long, inCount);
	memset(state->mItems, 0, inCount * sizeof(unsigned long));
	state->mFlag = false;
	return state;
}

void* CPrsParseStateProd::operator new(size_t, CPrsParser* inParser, size_t)
{
	if (inParser->mNumStateProds >= 0x4000)
		LIB_Errorf("CPrsParseStateProd: Too many state kernel productions");
	CPrsParseStateProd* prod = &inParser->mStateProds[inParser->mNumStateProds++];
	prod->mField0 = 0;
	prod->mField8 = 0;
	prod->mField18 = 0;
	prod->mField10 = 0;
	return prod;
}

void* CPrsParser::operator new(size_t inSize) { return LIB_ClientMalloc(inSize); }
void CPrsParser::operator delete(void* inPtr) { LIB_ClientFree(inPtr); }
void* CLexLexer::operator new(size_t inSize) { return LIB_ClientMalloc(inSize); }
void CLexLexer::operator delete(void* inPtr) { LIB_ClientFree(inPtr); }

void* CPrsASTNode::operator new(size_t inSize)
{
	sNodeCount++;
	return LIB_ClientMalloc(inSize);
}

void CPrsASTNode::operator delete(void* inPtr)
{
	sNodeCount--;
	LIB_ClientFree(inPtr);
}

void* CPrsCSTNode::operator new(size_t inSize)
{
	sNodeCount++;
	return LIB_ClientMalloc(inSize);
}

void CPrsCSTNode::operator delete(void* inPtr)
{
	sNodeCount--;
	LIB_ClientFree(inPtr);
}

bool CPrsParseProd::operator==(CPrsParseProd& inOther)
{
	bool result = false;
	if (mLhs == inOther.mLhs)
	{
		unsigned long n = mCount < inOther.mCount ? mCount : inOther.mCount;
		result = true;
		for (unsigned long i = 0; i < n; i++)
		{
			if (mSyms[i] != inOther.mSyms[i])
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

CLexBitSet& CLexBitSet::operator+=(unsigned long inBit)
{
	mBits[inBit >> 3] |= (1 << (inBit & 7));
	return *this;
}

CLexBitSet& CLexBitSet::operator-=(unsigned long inBit)
{
	mBits[inBit >> 3] &= ~(1 << (inBit & 7));
	return *this;
}

bool CLexDfaAcceptItem::operator==(const CLexDfaAcceptItem& inOther)
{
	return mField0 == inOther.mField0 && mField8 == inOther.mField8 &&
		mField10 == inOther.mField10 && mFlag == inOther.mFlag;
}

CLexDfaAcceptItem& CLexDfaAcceptItem::operator=(const CLexDfaAcceptItem& inOther)
{

	mField0 = inOther.mField0;
	mField8 = inOther.mField8;
	mField10 = inOther.mField10;
	mFlag = inOther.mFlag;
	return *this;
}

CLexDfaPartition& CLexDfaPartitionSet::operator[](int inIndex) { return mParts[inIndex]; }

}
