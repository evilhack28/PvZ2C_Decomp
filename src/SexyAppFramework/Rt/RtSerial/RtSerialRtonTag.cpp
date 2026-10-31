//
//  RtSerialRtonTag.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtSerial.h"

using namespace Sexy;

/////////////// Tags ///////////////

bool RtSerialRtonTag::IsKnownTag(int i_tag)
{
	switch (i_tag)
	{
	case BoolFalse:
	case BoolTrue:
	case AtomicThis:
	case Int8Fixed:
	case Int8Zero:
	case UInt8Fixed:
	case UInt8Zero:
	case Int16Fixed:
	case Int16Zero:
	case UInt16Fixed:
	case UInt16Zero:
	case Int32Fixed:
	case Int32Zero:
	case Float:
	case FloatZero:
	case Int32VarU:
	case Int32VarS:
	case UInt32Fixed:
	case UInt32Zero:
	case UInt32VarU:
	case Int64Fixed:
	case Int64Zero:
	case Double:
	case DoubleZero:
	case Int64VarU:
	case Int64VarS:
	case UInt64Fixed:
	case UInt64Zero:
	case UInt64VarU:
	case AnsiString:
	case UTF8String:
	case RtId:
	case RtIdNull:
	case Object:
	case Array:
	case BinaryBlob:
	case TrackedAnsiStringNew:
	case TrackedAnsiStringExisting:
	case TrackedUTF8StringNew:
	case TrackedUTF8StringExisting:
	case MarkerArrayTypeVarying:
	case MarkerArrayEnd:
	case MarkerObjectEnd:
	case MemStringNew:
	case MemStringExisting:
	case MemWStringNew:
	case MemWStringExisting:
	case MemKeyStringNew:
	case MemKeyStringExisting:
	case MemKeyWStringNew:
	case MemKeyWStringExisting:
	case MemObject:
	case MemArray:
	case MemRtId:
	case MemBinaryBlob:
	case MemBool:
		return true;
	default:
		return i_tag >= ApplicationTagFirst && i_tag <= ApplicationTagLast;
	}
}
