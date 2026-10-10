//
//  Reflection.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 & vi_i_guess on 2026-10-10.
//

#include "SexyAppFramework/Common.h"

#include "Reflection.h"

RT_CLASS_IMPLEMENT(Reflection::RSymbol);
RT_CLASS_IMPLEMENT_ABSTRACT(Reflection::RType);
RT_CLASS_IMPLEMENT(Reflection::RSimpleType);
RT_CLASS_IMPLEMENT(Reflection::RReferenceType);
RT_CLASS_IMPLEMENT(Reflection::RFunctionType);
RT_CLASS_IMPLEMENT(Reflection::RCustomType);
RT_CLASS_IMPLEMENT_ABSTRACT(Reflection::RNamedType);
RT_CLASS_IMPLEMENT(Reflection::RUnknownNamedType);
RT_CLASS_IMPLEMENT(Reflection::RClass);
RT_CLASS_IMPLEMENT(Reflection::RClassRef);
RT_CLASS_IMPLEMENT(Reflection::REnumMember);
RT_CLASS_IMPLEMENT(Reflection::REnum);
RT_CLASS_IMPLEMENT(Reflection::REnumRef);
RT_CLASS_IMPLEMENT(Reflection::RClassMember);
RT_CLASS_IMPLEMENT(Reflection::RField);
RT_CLASS_IMPLEMENT(Reflection::RProperty);
RT_CLASS_IMPLEMENT(Reflection::RMethod);
RT_CLASS_IMPLEMENT(Reflection::REvent);
RT_CLASS_IMPLEMENT(Reflection::RAncestor);
RT_CLASS_IMPLEMENT(Reflection::RAttribute);

namespace Reflection
{

/////////////// CRefManualSymbolBuilder (declaration) ///////////////

class CRefManualSymbolBuilder
: public IRefManualSymbolBuilder
{
protected:
	CRefSymbolDb* mSymbolDb;
	std::map<RClass*, FClassBuilderCallback> mClassCallbacks;
	std::map<uint32, RSimpleType*> mSimpleTypes;
	std::map<RType*, RReferenceType*> mReferenceTypes;
	std::map<uint64, RFunctionType*> mFunctionTypes;
	std::map<uint64, RCustomType*> mCustomTypes;
	std::map<RClass*, RClassRef*> mClassRefs;
	std::map<REnum*, REnumRef*> mEnumRefs;

public:
	CRefManualSymbolBuilder(CRefSymbolDb* inSymbolDb);
	~CRefManualSymbolBuilder();

	virtual void BuilderDestroy() override;
	virtual void BuildClass(RClass* inClass) override;
	virtual void BuildEnum(REnum* inEnum) override {}

	virtual void AddClass(const std::string& inName, FClassBuilderCallback inCallback, uint32 inInstanceSize, uint32 inVtblSize = 0) override;
	virtual void AddEnum(const std::string& inName, const std::vector<DEnumMemberPair>& inMembers, bool inMembersAreFlags) override;

	virtual RSimpleType* GetSimpleType(RSimpleType::ESimpleTypeCategory inCategory, uint32 inSize) override;
	virtual RReferenceType* GetReferenceType(RReferenceType::EReferenceTypeCategory inCategory, RType* inInnerType, uint32 inArrayItemCount = 0) override;
	virtual RFunctionType* GetFunctionType(RFunctionType::ECallType inCallType, RType* inThisType, RType* inReturnType, const std::vector<RType*>& inArgTypes) override;
	virtual RCustomType* GetCustomType(RCustomType::ECustomTypeCategory inCategory, RType* inInnerType, RCustomType::IStdManipulator* inManipulator = 0) override;
	virtual RNamedType* GetNamedType(const std::string& inName) override;

	virtual RAncestor* BuildAncestor(RClass* inClass, RClass* inAncestorClass, uint32 inOffset) override;
	virtual RField* BuildField(RClass* inClass, const std::string& inName, uint32 inOffset, RType* inType) override;
	virtual RProperty* BuildProperty(RClass* inClass, const std::string& inName, RType* inType, RMethod* inGetter, RMethod* inSetter) override;
	virtual RMethod* BuildMethod(RClass* inClass, const std::string& inName, DelegateBase* inDelegate, RFunctionType* inType, bool inIsSerialCommand = false) override;
	virtual REvent* BuildEvent(RClass* inClass, const std::string& inName, uint32 inOffset, RFunctionType* inType, bool inIsSerialCommand = false) override;

	virtual RAttribute* BuildAttribute(const std::string& inName, const CRefAttributeVariant& inValue) override;

	void InitCommonTypes();
};

/////////////// CRefNamedSymbolCollection ///////////////

CRefNamedSymbolCollection::CRefNamedSymbolCollection()
: mNoDeleteSymbols(false)
{
}

CRefNamedSymbolCollection::~CRefNamedSymbolCollection()
{
	if (!mNoDeleteSymbols)
	{
		uint32 count = (uint32)mSymbols.size();
		for (uint32 i = 0; i < count; i++)
			delete mSymbols[i];
	}
}

/////////////// RSymbol ///////////////

static RtId GetSymbolRtId(RtObject* inObject)
{
	RSymbol* symbol = inObject->Cast<RSymbol>();
	if (symbol)
		return symbol->GetRtId();
	return RtId();
}

void RSymbol::StaticClassInit()
{
	RtIdProtocol* protocol = new RtIdProtocol;
	protocol->SetDelegate(MakeDelegate(&GetSymbolRtId));
	StaticGetClass()->AddProtocol(protocol);
}

RSymbol::RSymbol()
{
	RtDbTable* table = RtDb::GetDb()->GetTable(RtDb::SYSTEMTABLE_ReflectionSymbols);
	if (!table)
	{
		RtDbTable::TableOptions options;
		options.mTableName = L"System.ReflectionSymbols";
		options.mDisplayName = "System.ReflectionSymbols";
		options.mIsFixedContent = true;
		table = RtDb::GetDb()->CreateTable(RtDb::SYSTEMTABLE_ReflectionSymbols, &options);
	}
	mRtId = table->AllocId(this, RtDbTable::ODM_Never, true, NULL);
}

RSymbol::~RSymbol()
{
	RtDb::GetDb()->GetTable(RtDb::SYSTEMTABLE_ReflectionSymbols)->ReleaseId(mRtId);
}

/////////////// RType ///////////////

bool RType::InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const
{
	bool isWriting = inSync->IsWriting();
	if (isWriting)
		inSync->GetWriter()->WriteString(inKey, "???RType::InstanceRtonSync???", false);
	return isWriting;
}

/////////////// RSimpleType ///////////////

bool RSimpleType::TypeEquals(RType* inType, bool inCheckConst, bool inExactMatch) const
{
	if (!inType || inType->GetTypeCategory() != TC_Simple)
		return false;

	RSimpleType* other = static_cast<RSimpleType*>(inType);
	if (GetSize() != other->GetSize())
		return false;
	if (inCheckConst && GetIsConst() != other->GetIsConst())
		return false;
	return GetSimpleTypeCategory() == other->GetSimpleTypeCategory();
}

std::string RSimpleType::TypeToString(bool inCheckConst) const
{
	std::string result;
	if (inCheckConst && GetIsConst())
		result = "const ";

	ESimpleTypeCategory category = GetSimpleTypeCategory();
	switch (category)
	{
	case STC_Ellipsis:
		result += "...";
		break;
	case STC_Void:
		result += "void";
		break;
	case STC_Bool:
		result += "bool";
		break;
	case STC_AChar:
		result += "char";
		break;
	case STC_WChar:
		result += "wchar_t";
		break;
	case STC_SInt:
	case STC_UInt:
	{
		if (category == STC_UInt)
			result += "unsigned ";
		uint32 size = GetSize();
		switch (size)
		{
		case 1:
			result += "char";
			break;
		case 2:
			result += "short";
			break;
		case 4:
			result += "long";
			break;
		case 8:
			result += "__int64";
			break;
		default:
			result += StrFormat("FIXME_UNKINT%d", size);
			break;
		}
		break;
	}
	case STC_Float:
	{
		uint32 size = GetSize();
		switch (size)
		{
		case 4:
			result += "float";
			break;
		case 8:
			result += "double";
			break;
		default:
			result += StrFormat("FIXME_UNKFLT%d", size);
			break;
		}
		break;
	}
	case STC_HResult:
		result += "HRESULT";
		break;
	default:
		result += StrFormat("FIXME_UNK%d", GetSize());
		break;
	}
	return result;
}

std::string RSimpleType::InstanceToString(const void* inInstancePtr, bool inUseHex) const
{
	std::string result;
	switch (GetSimpleTypeCategory())
	{
	case STC_Ellipsis:
		result += "...";
		break;
	case STC_Void:
		result += "void";
		break;
	case STC_Bool:
		result += *(const bool*)inInstancePtr ? "true" : "false";
		break;
	case STC_AChar:
		result += StrFormat("%c", *(const char*)inInstancePtr);
		break;
	case STC_WChar:
		result += StrFormat("%C", *(const wchar_t*)inInstancePtr);
		break;
	case STC_SInt:
		if (inUseHex)
		{
			switch (GetSize())
			{
			case 1:
				result += StrFormat("0x%02x", *(const int8*)inInstancePtr);
				break;
			case 2:
				result += StrFormat("0x%04x", *(const int16*)inInstancePtr);
				break;
			case 4:
				result += StrFormat("0x%08x", *(const long*)inInstancePtr);
				break;
			case 8:
				result += StrFormat("0x%016I64x", *(const int64*)inInstancePtr);
				break;
			default:
				result += StrFormat("?STC_SInt%d?", GetSize());
				break;
			}
		}
		else
		{
			switch (GetSize())
			{
			case 1:
				result += StrFormat("%d", *(const int8*)inInstancePtr);
				break;
			case 2:
				result += StrFormat("%d", *(const int16*)inInstancePtr);
				break;
			case 4:
				result += StrFormat("%d", *(const long*)inInstancePtr);
				break;
			case 8:
				result += StrFormat("%li", *(const int64*)inInstancePtr);
				break;
			default:
				result += StrFormat("?STC_SInt%d?", GetSize());
				break;
			}
		}
		break;
	case STC_UInt:
		if (inUseHex)
		{
			switch (GetSize())
			{
			case 1:
				result += StrFormat("0x%02x", *(const uint8*)inInstancePtr);
				break;
			case 2:
				result += StrFormat("0x%04x", *(const uint16*)inInstancePtr);
				break;
			case 4:
				result += StrFormat("0x%08x", *(const uint32*)inInstancePtr);
				break;
			case 8:
				result += StrFormat("0x%016I64x", *(const uint64*)inInstancePtr);
				break;
			default:
				result += StrFormat("?STC_UInt%d?", GetSize());
				break;
			}
		}
		else
		{
			switch (GetSize())
			{
			case 1:
				result += StrFormat("%d", *(const uint8*)inInstancePtr);
				break;
			case 2:
				result += StrFormat("%d", *(const uint16*)inInstancePtr);
				break;
			case 4:
				result += StrFormat("%d", *(const uint32*)inInstancePtr);
				break;
			case 8:
				result += StrFormat("%li", *(const uint64*)inInstancePtr);
				break;
			default:
				result += StrFormat("?STC_UInt%d?", GetSize());
				break;
			}
		}
		break;
	case STC_Float:
		switch (GetSize())
		{
		case 4:
			result += StrFormat("%f", *(const float*)inInstancePtr);
			break;
		case 8:
			result += StrFormat("%f", *(const double*)inInstancePtr);
			break;
		default:
			result += StrFormat("?STC_Float%d?", GetSize());
			break;
		}
		break;
	case STC_HResult:
		result += StrFormat("0x%08x", *(const uint32*)inInstancePtr);
		break;
	default:
		result += "?STC_Unknown?";
		break;
	}
	return result;
}

bool RSimpleType::InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const
{
	if (inSync->IsWriting())
	{
		RtSerialRtonWriter* writer = inSync->GetWriter();
		switch (GetSimpleTypeCategory())
		{
		case STC_Ellipsis:
			writer->WriteString(inKey, "...");
			break;
		case STC_Void:
			writer->WriteString(inKey, "void");
			break;
		case STC_Bool:
			writer->WriteBool(inKey, *(bool*)inInstancePtr);
			break;
		case STC_AChar:
			writer->WriteUInt32(inKey, *(uint8*)inInstancePtr);
			break;
		case STC_WChar:
			writer->WriteUInt32(inKey, *(wchar_t*)inInstancePtr);
			break;
		case STC_SInt:
			switch (GetSize())
			{
			case 1:
				writer->WriteInt8Fixed(inKey, *(int8*)inInstancePtr);
				break;
			case 2:
				writer->WriteInt16Fixed(inKey, *(int16*)inInstancePtr);
				break;
			case 4:
				writer->WriteInt32(inKey, *(int32*)inInstancePtr);
				break;
			case 8:
				writer->WriteInt64(inKey, *(int64*)inInstancePtr);
				break;
			default:
				writer->WriteString(inKey, StrFormat("?STC_SInt%d?", GetSize()));
				break;
			}
			break;
		case STC_UInt:
			switch (GetSize())
			{
			case 1:
				writer->WriteUInt8Fixed(inKey, *(uint8*)inInstancePtr);
				break;
			case 2:
				writer->WriteUInt16Fixed(inKey, *(uint16*)inInstancePtr);
				break;
			case 4:
				writer->WriteUInt32(inKey, *(uint32*)inInstancePtr);
				break;
			case 8:
				writer->WriteUInt64(inKey, *(uint64*)inInstancePtr);
				break;
			default:
				writer->WriteString(inKey, StrFormat("?STC_UInt%d?", GetSize()));
				break;
			}
			break;
		case STC_Float:
			switch (GetSize())
			{
			case 4:
				writer->WriteFloat(inKey, *(float*)inInstancePtr);
				break;
			case 8:
				writer->WriteDouble(inKey, *(double*)inInstancePtr);
				break;
			default:
				writer->WriteString(inKey, StrFormat("?STC_Float%d?", GetSize()));
				break;
			}
			break;
		case STC_HResult:
			writer->WriteUInt32(inKey, *(uint32*)inInstancePtr);
			break;
		default:
			writer->WriteString(inKey, "?STC_Unknown?");
			break;
		}
		return true;
	}
	else
	{
		RtSerialRtonReader* reader = inSync->GetReader();
		switch (GetSimpleTypeCategory())
		{
		case STC_Bool:
			*(bool*)inInstancePtr = reader->ReadBool(inKey);
			return true;
		case STC_AChar:
			*(uint8*)inInstancePtr = reader->ReadUInt32(inKey);
			return true;
		case STC_WChar:
			*(wchar_t*)inInstancePtr = reader->ReadUInt32(inKey);
			return true;
		case STC_SInt:
			switch (GetSize())
			{
			case 1:
				*(int8*)inInstancePtr = reader->ReadInt32(inKey);
				return true;
			case 2:
				*(int16*)inInstancePtr = reader->ReadInt32(inKey);
				return true;
			case 4:
				*(int32*)inInstancePtr = reader->ReadInt32(inKey);
				return true;
			case 8:
				*(int64*)inInstancePtr = reader->ReadInt64(inKey);
				return true;
			}
			break;
		case STC_UInt:
			switch (GetSize())
			{
			case 1:
				*(uint8*)inInstancePtr = reader->ReadUInt32(inKey);
				return true;
			case 2:
				*(uint16*)inInstancePtr = reader->ReadUInt32(inKey);
				return true;
			case 4:
				*(uint32*)inInstancePtr = reader->ReadUInt32(inKey);
				return true;
			case 8:
				*(uint64*)inInstancePtr = reader->ReadUInt64(inKey);
				return true;
			}
			break;
		case STC_Float:
			switch (GetSize())
			{
			case 4:
				*(float*)inInstancePtr = reader->ReadFloat(inKey);
				return true;
			case 8:
				*(double*)inInstancePtr = reader->ReadDouble(inKey);
				return true;
			}
			break;
		case STC_HResult:
			*(uint32*)inInstancePtr = reader->ReadUInt32(inKey);
			return true;
		}
	}
	return false;
}

/////////////// RReferenceType ///////////////

bool RReferenceType::TypeEquals(RType* inType, bool inCheckConst, bool inExactMatch) const
{
	if (!inType || inType->GetTypeCategory() != TC_Reference)
		return false;

	RReferenceType* other = static_cast<RReferenceType*>(inType);
	if (GetSize() != other->GetSize())
		return false;
	if (inCheckConst && GetIsConst() != other->GetIsConst())
		return false;
	if (GetReferenceTypeCategory() != other->GetReferenceTypeCategory())
		return false;
	if (!GetInnerType()->TypeEquals(other->GetInnerType(), inCheckConst, inExactMatch))
		return false;
	if (GetReferenceTypeCategory() == RTC_Array)
		return GetArrayItemCount() == other->GetArrayItemCount();
	return true;
}

std::string RReferenceType::TypeToString(bool inCheckConst) const
{
	std::string result;
	result += GetInnerType() ? GetInnerType()->TypeToString(inCheckConst) : std::string("FIXME_REFTYPE_NULLINNERTYPE");

	if (inCheckConst && GetIsConst())
		result += " const ";

	switch (GetReferenceTypeCategory())
	{
	case RTC_Ampersand:
		result += "&";
		break;
	case RTC_Pointer:
		result += "*";
		break;
	case RTC_Array:
		result += "[";
		if (GetArrayItemCount())
			result += StrFormat("%d", GetArrayItemCount());
		result += "]";
		break;
	default:
		result += "FIXME_UNKREF";
		break;
	}
	return result;
}

bool RReferenceType::InstanceNavigatePath(void*& ioInstancePtr, std::string& ioPath, RType*& outType) const
{
	if (GetReferenceTypeCategory() != RTC_Array)
		return false;

	int32 itemCount = GetArrayItemCount();
	if (ioPath.empty() || ioPath[0] != '[')
		return false;

	std::string indexStr = ioPath.substr(1);
	size_t closePos = indexStr.find(']');
	if (closePos == std::string::npos)
		return false;

	indexStr = indexStr.substr(0, closePos);
	int32 index = atoi(indexStr.c_str());
	if (index < 0 || itemCount <= index)
		return false;

	RType* innerType = GetInnerType();
	ioInstancePtr = (uint8*)ioInstancePtr + innerType->GetSize() * index;
	ioPath = ioPath.substr(closePos + 2);
	outType = innerType;
	if (ioPath.empty())
		return true;

	if (ioPath[0] == '.')
		ioPath = ioPath.substr(1);
	return outType->InstanceNavigatePath(ioInstancePtr, ioPath, outType);
}

std::string RReferenceType::InstanceToString(const void* inInstancePtr, uint32 inArrayStart, uint32 inArrayCount) const
{
	std::string result;
	RType* innerType = GetInnerType();
	uint32 innerSize = innerType->GetSize();
	const uint8* elementPtr;
	int32 count = 1;
	bool addedNoShowPointers;

	if (GetReferenceTypeCategory() == RTC_Array)
	{
		result += "[";
		count = std::min<int32>(inArrayCount, GetArrayItemCount() - inArrayStart);
		addedNoShowPointers = !CRefSymbolDb::HasStringFlags(CRefSymbolDb::STRINGF_NoShowPointers);
		CRefSymbolDb::AddStringFlags(CRefSymbolDb::STRINGF_NoShowPointers);
		elementPtr = (const uint8*)inInstancePtr + innerSize * inArrayStart;
	}
	else
	{
		elementPtr = *(const uint8**)inInstancePtr;
		if (!elementPtr)
			return "NULL";
		if (GetReferenceTypeCategory() == RTC_Pointer)
		{
			if (!CRefSymbolDb::HasStringFlags(CRefSymbolDb::STRINGF_NoShowPointers))
				result += StrFormat("0x%p -> ", elementPtr);
			else
				result += "(&)";
		}
	}

	for (int32 i = 0; i < count; i++)
	{
		if (i > 0)
			result += ", ";

		if (innerType->GetTypeCategory() == TC_Simple)
		{
			switch (static_cast<RSimpleType*>(innerType)->GetSimpleTypeCategory())
			{
			case RSimpleType::STC_AChar:
				result += StrFormat("\"%s\"", elementPtr);
				break;
			case RSimpleType::STC_WChar:
				result += StrFormat("\"%ls\"", elementPtr);
				break;
			default:
				result += innerType->InstanceToString(elementPtr);
				break;
			}
		}
		else if (innerType->GetTypeCategory() == TC_Reference && static_cast<RReferenceType*>(innerType)->GetReferenceTypeCategory() == RTC_Array)
			result += static_cast<RReferenceType*>(innerType)->InstanceToString(elementPtr, 0, 1);
		else
			result += innerType->InstanceToString(elementPtr);
		elementPtr += innerSize;
	}

	if (GetReferenceTypeCategory() == RTC_Array)
	{
		if ((int32)inArrayCount < (int32)(GetArrayItemCount() - inArrayStart))
			result += ", ...";
		result += "]";
		if (addedNoShowPointers)
			CRefSymbolDb::RemoveStringFlags(CRefSymbolDb::STRINGF_NoShowPointers);
	}
	return result;
}

bool RReferenceType::InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const
{
	RType* innerType = GetInnerType();
	uint32 innerSize = innerType->GetSize();
	if (inSync->IsWriting())
	{
		RtSerialRtonWriter* writer = inSync->GetWriter();
		uint8* elementPtr = (uint8*)inInstancePtr;
		if (GetReferenceTypeCategory() != RTC_Array)
		{
			elementPtr = *(uint8**)inInstancePtr;
			if (!elementPtr)
				return false;
		}

		if (innerType->GetTypeCategory() == TC_Simple)
		{
			switch (static_cast<RSimpleType*>(innerType)->GetSimpleTypeCategory())
			{
			case RSimpleType::STC_AChar:
				writer->WriteString(inKey, (const char*)elementPtr);
				return true;
			case RSimpleType::STC_WChar:
				writer->WriteUTF8String(inKey, (const wchar_t*)elementPtr);
				return true;
			}
		}

		if (GetReferenceTypeCategory() != RTC_Array)
			return false;

		int32 count = GetArrayItemCount();
		writer->BeginArray(inKey, count);
		for (int32 i = 0; i < count; i++)
		{
			innerType->InstanceRtonSync(elementPtr, inSync, RtSerialRtonKey(NULL));
			elementPtr += innerSize;
		}
		writer->EndArray();
		return true;
	}
	else
	{
		RtSerialRtonReader* reader = inSync->GetReader();
		if (GetReferenceTypeCategory() != RTC_Array)
			return false;

		uint8* elementPtr = (uint8*)inInstancePtr;
		uint32 count = GetArrayItemCount();
		if (innerType->GetTypeCategory() == TC_Simple)
		{
			switch (static_cast<RSimpleType*>(innerType)->GetSimpleTypeCategory())
			{
			case RSimpleType::STC_AChar:
			{
				std::string str = reader->ReadString(inKey);
				strncpy((char*)elementPtr, str.c_str(), count);
				return true;
			}
			case RSimpleType::STC_WChar:
			{
				std::wstring str = reader->ReadWString(inKey);
				wcsncpy((wchar_t*)elementPtr, str.c_str(), count);
				return true;
			}
			}
		}

		uint32 readCount = 0;
		reader->BeginArray(inKey, readCount);
		count = std::min(count, readCount);
		for (uint32 i = 0; i < count; i++)
		{
			innerType->InstanceRtonSync(elementPtr, inSync, RtSerialRtonKey(NULL));
			elementPtr += innerSize;
		}
		reader->EndArray();
		return true;
	}
}

void* RReferenceType::GetArrayElement(const void* inInstancePtr, int32 inElementIndex) const
{
	if (GetReferenceTypeCategory() == RTC_Array)
	{
		uint32 elementSize = GetInnerType()->GetSize();
		if (inElementIndex >= 0 && (uint32)inElementIndex <= elementSize - 1)
			return (uint8*)inInstancePtr + elementSize * inElementIndex;
	}
	return NULL;
}

/////////////// RFunctionType ///////////////

bool RFunctionType::TypeEquals(RType* inType, bool inCheckConst, bool inExactMatch) const
{
	if (!inType || inType->GetTypeCategory() != TC_Function)
		return false;

	RFunctionType* other = static_cast<RFunctionType*>(inType);
	if (inCheckConst && GetIsConst() != other->GetIsConst())
		return false;
	if (GetCallType() != other->GetCallType())
		return false;
	if (!GetReturnType()->TypeEquals(other->GetReturnType(), inCheckConst, inExactMatch))
		return false;

	uint32 argCount = GetArgTypeCount();
	if (argCount != other->GetArgTypeCount())
		return false;
	for (uint32 i = 0; i < argCount; i++)
	{
		if (!GetArgTypeIndexed(i)->TypeEquals(other->GetArgTypeIndexed(i)))
			return false;
	}

	if (inExactMatch)
	{
		if (GetThisAdjust() != other->GetThisAdjust())
			return false;
		if (GetThisType())
			return GetThisType()->TypeEquals(other->GetThisType(), inCheckConst, true);
		return other->GetThisType() == NULL;
	}
	return true;
}

std::string RFunctionType::TypeToString(bool inCheckConst) const
{
	std::string result;
	if (GetThisAdjust())
		result += StrFormat("thisadj(%d) ", GetThisAdjust());
	if (inCheckConst && GetIsConst())
		result += "const ";

	if (GetThisType())
		result += StrFormat("method<%s, ", GetThisType()->TypeToString(inCheckConst).c_str());
	else
		result += "function<";

	result += GetReturnType() ? GetReturnType()->TypeToString(inCheckConst) : std::string("FIXME_FUNCTYPE_NULLRETTYPE");
	result += ", ";

	switch (GetCallType())
	{
	case CT_ThisCall:
		result += "thiscall";
		break;
	case CT_Cdecl:
		result += "cdecl";
		break;
	case CT_StdCall:
		result += "stdcall";
		break;
	case CT_FastCall:
		result += "fastcall";
		break;
	case CT_SysCall:
		result += "syscall";
		break;
	case CT_Delegate:
		result += "delegate";
		break;
	default:
		result += "FIXME_FUNCTYPE_UNKCALLTYPE";
		break;
	}

	result += ">(";
	for (uint32 i = 0; i < GetArgTypeCount(); i++)
	{
		if (i)
			result += ", ";
		RType* argType = GetArgTypeIndexed(i);
		result += argType ? argType->TypeToString(inCheckConst) : std::string("FIXME_FUNCTYPE_NULLARGTYPE");
	}
	result += ")";
	return result;
}

/////////////// RCustomType ///////////////

bool RCustomType::TypeEquals(RType* inType, bool inCheckConst, bool inExactMatch) const
{
	if (!inType || inType->GetTypeCategory() != TC_Custom)
		return false;

	RCustomType* other = static_cast<RCustomType*>(inType);
	if (GetSize() != other->GetSize())
		return false;
	if (inCheckConst && GetIsConst() != other->GetIsConst())
		return false;
	if (GetCustomTypeCategory() != other->GetCustomTypeCategory())
		return false;
	return GetInnerType()->TypeEquals(other->GetInnerType(), inCheckConst, inExactMatch);
}

std::string RCustomType::TypeToString(bool inCheckConst) const
{
	std::string result;
	RType* innerType = GetInnerType();
	result += innerType ? innerType->TypeToString(inCheckConst) : std::string("FIXME_REFTYPE_NULLINNERTYPE");

	if (inCheckConst && GetIsConst())
		result += " const ";

	switch (GetCustomTypeCategory())
	{
	case CTC_StdString:
		result += "std::string";
		break;
	case CTC_StdWString:
		result += "std::wstring";
		break;
	case CTC_StdVector:
		result += "std::vector<";
		result += innerType ? innerType->TypeToString(inCheckConst) : std::string("FIXME_CUSTOMTYPE_STDVECTOR_NULLINNERTYPE");
		result += ">";
		break;
	case CTC_WeakRtId:
		if (innerType)
			result += "RtWeakPtr<" + innerType->TypeToString(inCheckConst) + ">";
		else
			result += "RtId";
		break;
	case CTC_StrongRtId:
		result += "RtStrongPtr<";
		result += innerType ? innerType->TypeToString(inCheckConst) : std::string("RtObject");
		result += ">";
		break;
	default:
		result += "FIXME_UNKCUSTOM";
		break;
	}
	return result;
}

std::string RCustomType::InstanceToString(const void* inInstancePtr) const
{
	std::string result;
	RType* innerType = GetInnerType();
	switch (GetCustomTypeCategory())
	{
	case CTC_StdString:
		result += "\"";
		result += *(const std::string*)inInstancePtr;
		result += "\"";
		break;
	case CTC_StdWString:
		result += "\"";
		result += WStringToString(*(const std::wstring*)inInstancePtr);
		result += "\"";
		break;
	case CTC_StdVector:
	{
		IStdManipulator* manipulator = GetManipulator();
		if (manipulator)
		{
			result += "(std::vector<";
			result += innerType ? innerType->TypeToString(false) : std::string("FIXME_CUSTOMTYPE_STDVECTOR_NULLINNERTYPE");
			result += ">)";
			result += StrFormat("(count = %d)", manipulator->GetCount(inInstancePtr));
		}
		else
		{
			result += "(std::vector<";
			result += innerType ? innerType->TypeToString(false) : std::string("FIXME_CUSTOMTYPE_STDVECTOR_NULLINNERTYPE");
			result += ">)";
		}
		break;
	}
	case CTC_StdDeque:
	{
		IStdManipulator* manipulator = GetManipulator();
		if (manipulator)
		{
			result += "(std::deque<";
			result += innerType ? innerType->TypeToString(false) : std::string("FIXME_CUSTOMTYPE_STDDEQUE_NULLINNERTYPE");
			result += ">)";
			result += StrFormat("(count = %d)", manipulator->GetCount(inInstancePtr));
		}
		else
		{
			result += "(std::deque<";
			result += innerType ? innerType->TypeToString(false) : std::string("FIXME_CUSTOMTYPE_STDDEQUE_NULLINNERTYPE");
			result += ">)";
		}
		break;
	}
	case CTC_StdMap:
	{
		IStdManipulator* manipulator = GetManipulator();
		result += "(std::map<std::string,";
		result += innerType ? innerType->TypeToString(false) : std::string("FIXME_CUSTOMTYPE_STDMAP_NULLINNERTYPE");
		result += ">)";
		result += StrFormat("(count = %d)", manipulator->GetCount(inInstancePtr));
		break;
	}
	case CTC_StdSet:
	{
		IStdManipulator* manipulator = GetManipulator();
		result += "(std::set<";
		result += innerType ? innerType->TypeToString(false) : std::string("FIXME_CUSTOMTYPE_STDMAP_NULLINNERTYPE");
		result += ">)";
		result += StrFormat("(count = %d)", manipulator->GetCount(inInstancePtr));
		break;
	}
	case CTC_WeakRtId:
	case CTC_StrongRtId:
	case CTC_EmbeddedObject:
	{
		RtId id(*(const RtId*)inInstancePtr);
		std::string idStr;
		id.ToString(idStr);
		result += idStr;
		break;
	}
	default:
		result += "FIXME_UNKCUSTOM";
		break;
	}
	return result;
}

bool RCustomType::InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const
{
	RType* innerType = GetInnerType();
	if (inSync->IsWriting())
	{
		RtSerialRtonWriter* writer = inSync->GetWriter();
		switch (GetCustomTypeCategory())
		{
		case CTC_StdVector:
		case CTC_StdDeque:
		case CTC_StdMap:
		case CTC_StdSet:
		case CTC_EmbeddedObject:
			GetManipulator()->InstanceRtonSync(inInstancePtr, inSync, inKey, innerType);
			return true;
		case CTC_StdString:
			writer->WriteString(inKey, *(std::string*)inInstancePtr);
			return true;
		case CTC_StdWString:
			writer->WriteUTF8String(inKey, *(std::wstring*)inInstancePtr);
			return true;
		case CTC_WeakRtId:
		case CTC_StrongRtId:
			writer->WriteRtId(inKey, *(RtId*)inInstancePtr);
			return true;
		default:
			return false;
		}
	}
	else
	{
		RtSerialRtonReader* reader = inSync->GetReader();
		switch (GetCustomTypeCategory())
		{
		case CTC_StdVector:
		case CTC_StdDeque:
		case CTC_StdMap:
		case CTC_StdSet:
		case CTC_EmbeddedObject:
			GetManipulator()->InstanceRtonSync(inInstancePtr, inSync, inKey, innerType);
			return true;
		case CTC_StdString:
			*(std::string*)inInstancePtr = reader->ReadString(inKey);
			return true;
		case CTC_StdWString:
			*(std::wstring*)inInstancePtr = reader->ReadWString(inKey);
			return true;
		case CTC_WeakRtId:
		case CTC_StrongRtId:
			*(RtId*)inInstancePtr = reader->ReadRtId(inKey);
			return true;
		default:
			return false;
		}
	}
}

/////////////// RNamedType ///////////////

bool RNamedType::TypeEquals(RType* inType, bool inCheckConst, bool inExactMatch) const
{
	if (!inType || !(inType->GetTypeCategory() & TC_Named_MASK))
		return false;

	RNamedType* other = static_cast<RNamedType*>(inType);
	if (GetSize() != other->GetSize())
		return false;
	if (inCheckConst && GetIsConst() != other->GetIsConst())
		return false;
	return strcmp(GetName(), other->GetName()) == 0;
}

std::string RNamedType::TypeToString(bool inCheckConst) const
{
	std::string result;
	if (inCheckConst && GetIsConst())
		result = "const ";

	const char* name = GetName();
	if (name && name[0])
		result += name;
	else
		result += "FIXME_NAMEDTYPE_NONAME";
	return result;
}

std::string RNamedType::InstanceToString(const void* inInstancePtr) const
{
	return StrFormat("(%s)", GetName());
}

bool RNamedType::InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const
{
	bool isWriting = inSync->IsWriting();
	if (isWriting)
		inSync->GetWriter()->WriteString(inKey, StrFormat("(%s)", GetName()), true);
	return isWriting;
}

/////////////// RClass ///////////////

RClass::RClass()
: mClassBoundRtClass(NULL)
{
	mAllFields.SetNoDeleteSymbols(true);
	mAllProperties.SetNoDeleteSymbols(true);
	mAllMethods.SetNoDeleteSymbols(true);
	mAllAttributes.SetNoDeleteSymbols(true);
}

void RClass::LoadClass()
{
	mSymbolDb->mBuilder->BuildClass(this);
}

bool RClass::CheckFieldNameValid(const std::string& inName)
{
	return true;
}

RClass* RClass::GetPrimaryAncestor() const
{
	const TRefNamedSymbolCollection<RAncestor>* ancestors = GetAncestors();
	uint32 count = ancestors->GetCount();
	if (!count)
		return NULL;

	for (uint32 i = 0; i < count; i++)
	{
		RAncestor* ancestor = ancestors->GetIndexed(i);
		if (!ancestor->GetOffset())
			return ancestor->GetRClass();
	}
	return ancestors->GetIndexed(0)->GetRClass();
}

std::string RClass::InstanceToString(const void* inInstancePtr) const
{
	RAttribute* attribute = GetAttributes(true)->GetNamed("ToStringMethod");
	std::string methodName = attribute ? attribute->GetValue()->GetString() : "";
	RMethod* method = methodName.empty() ? NULL : GetMethods(true)->GetNamed(methodName);
	if (!method)
		return "";

	RFunctionType* methodType = (RFunctionType*)method->GetType();
	char buffer[256];
	std::vector<CRefInvokeVariant> args;
	CRefInvokeVariant returnValue;
	uint32 argCount = methodType->GetArgTypeCount();
	if (argCount == 3)
	{
		args.push_back(CRefInvokeVariant(inInstancePtr));
		inInstancePtr = NULL;
	}
	if (argCount == 2 || argCount == 3)
	{
		args.push_back(CRefInvokeVariant((const void*)buffer));
		args.push_back(CRefInvokeVariant((uint32)sizeof(buffer)));
	}
	if (method->Invoke(&returnValue, (void*)inInstancePtr, args))
		return std::string(buffer);
	return StrFormat("(%s)", GetName());
}

/////////////// REnum ///////////////

void REnum::LoadEnum()
{
	mSymbolDb->mBuilder->BuildEnum(this);
}

/////////////// RField ///////////////

std::string RField::InstanceToString(const void* inInstancePtr) const
{
	return GetType()->InstanceToString((const uint8*)inInstancePtr + GetFieldOffset());
}

bool RField::InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const
{
	return GetType()->InstanceRtonSync((uint8*)inInstancePtr + GetFieldOffset(), inSync, inKey);
}

/////////////// CRefManualSymbolBuilder ///////////////

CRefManualSymbolBuilder::CRefManualSymbolBuilder(CRefSymbolDb* inSymbolDb)
: mSymbolDb(inSymbolDb)
{
}

CRefManualSymbolBuilder::~CRefManualSymbolBuilder()
{
}

void CRefManualSymbolBuilder::BuilderDestroy()
{
	delete this;
}

void CRefManualSymbolBuilder::BuildClass(RClass* inClass)
{
	if (inClass->mClassFlags & RClass::CF_Loaded)
		return;
	inClass->mClassFlags = RClass::CF_Loaded;

	FClassBuilderCallback callback = mClassCallbacks[inClass];
	if (callback)
		callback(this, inClass);

	inClass->ResolveVirtualBases();

	for (int32 i = 0; i < (int32)inClass->mMethods.GetCount(); i++)
	{
		RMethod* method = inClass->mMethods.GetIndexed(i);
		if (method->mMethodDelegate)
			method->mMethodFlags |= ((RFunctionType*)method->GetType())->GetThisType() ? RMethod::MF_CanInvokeInstance : RMethod::MF_CanInvokeStatic;
	}

	std::vector<RClass*> ancestors;
	for (RClass* ancestor = inClass; ancestor; ancestor = ancestor->GetPrimaryAncestor())
		ancestors.insert(ancestors.begin(), ancestor);

	for (int32 i = 0; i < (int32)ancestors.size(); i++)
	{
		const TRefNamedSymbolCollection<RField>* fields = ancestors[i]->GetFields(false);
		uint32 count = fields->GetCount();
		for (uint32 j = 0; j < count; j++)
		{
			RField* field = fields->GetIndexed(j);
			inClass->mAllFields.AddSymbol(field->GetName(), field);
		}
	}

	for (int32 i = (int32)ancestors.size() - 1; i >= 0; i--)
	{
		RClass* ancestor = ancestors[i];

		const TRefNamedSymbolCollection<RMethod>* methods = ancestor->GetMethods(false);
		uint32 methodCount = methods->GetCount();
		for (uint32 j = 0; j < methodCount; j++)
		{
			RMethod* method = methods->GetIndexed(j);
			if (!inClass->mAllMethods.AddSymbol(method->GetName(), method))
			{
				inClass->mAllMethods.AddSymbol("", method);
				method->mMethodFlags |= RMethod::MF_Shadowed;
			}
		}

		const TRefNamedSymbolCollection<RProperty>* properties = ancestor->GetProperties(false);
		uint32 propertyCount = properties->GetCount();
		for (uint32 j = 0; j < propertyCount; j++)
		{
			RProperty* property = properties->GetIndexed(j);
			if (!inClass->mAllProperties.AddSymbol(property->GetName(), property))
			{
				inClass->mAllProperties.AddSymbol("", property);
				property->mPropertyFlags |= RProperty::PF_Shadowed;
			}
		}

		const TRefNamedSymbolCollection<RAttribute>* attributes = ancestor->GetAttributes(false);
		uint32 attributeCount = attributes->GetCount();
		for (uint32 j = 0; j < attributeCount; j++)
		{
			RAttribute* attribute = attributes->GetIndexed(j);
			inClass->mAllAttributes.AddSymbol(attribute->GetName(), attribute);
		}
	}
}

void CRefManualSymbolBuilder::AddClass(const std::string& inName, FClassBuilderCallback inCallback, uint32 inInstanceSize, uint32 inVtblSize)
{
	RClass* rclass = new RClass;
	mSymbolDb->mClasses.AddSymbol(inName, rclass);
	rclass->mTypeFlags = 0;
	rclass->mTypeSize = inInstanceSize;
	rclass->mTypeThisAdjust = 0;
	rclass->mName = inName;
	rclass->mSymbolDb = mSymbolDb;
	rclass->mClassDbIndex = mSymbolDb->GetClasses()->GetCount() - 1;
	rclass->mVtblSize = inVtblSize;
	rclass->mClassFlags = 0;
	rclass->mTypeDbIndex = mSymbolDb->GetTypes()->GetCount();
	mSymbolDb->mTypes.AddSymbol(inName, rclass);
	mClassCallbacks[rclass] = inCallback;
}

void CRefManualSymbolBuilder::AddEnum(const std::string& inName, const std::vector<DEnumMemberPair>& inMembers, bool inMembersAreFlags)
{
	REnum* renum = new REnum();
	mSymbolDb->mEnums.AddSymbol(inName, renum);
	renum->mTypeFlags = 0;
	renum->mTypeSize = 4;
	renum->mTypeThisAdjust = 0;
	renum->mName = inName;
	renum->mSymbolDb = mSymbolDb;
	renum->mEnumDbIndex = mSymbolDb->GetEnums()->GetCount() - 1;
	renum->mEnumFlags = REnum::EF_Loaded;
	if (inMembersAreFlags)
		renum->mEnumFlags |= REnum::EF_MembersAreFlags;

	int32 count = (int32)inMembers.size();
	for (int32 i = 0; i < count; i++)
	{
		REnumMember* member = new REnumMember;
		member->mMemberName = inMembers[i].first;
		member->mMemberValue = inMembers[i].second;
		member->mMemberOuter = renum;
		member->mEnumMemberFlags = 0;
		renum->mMembers.AddSymbol(member->mMemberName, member);
	}

	renum->mTypeDbIndex = mSymbolDb->GetTypes()->GetCount();
	mSymbolDb->mTypes.AddSymbol(inName, renum);
}

RSimpleType* CRefManualSymbolBuilder::GetSimpleType(RSimpleType::ESimpleTypeCategory inCategory, uint32 inSize)
{
	uint32 key = inCategory | (inSize << 16);
	std::map<uint32, RSimpleType*>::iterator it = mSimpleTypes.find(key);
	if (it != mSimpleTypes.end())
		return it->second;

	RSimpleType* type = new RSimpleType;
	type->mTypeDbIndex = mSymbolDb->GetTypes()->GetCount();
	type->mTypeFlags = 0;
	type->mTypeSize = inSize;
	type->mTypeThisAdjust = 0;
	type->mSimpleTypeCategory = inCategory;
	mSimpleTypes[key] = type;
	mSymbolDb->mTypes.AddSymbol("", type);
	return type;
}

RReferenceType* CRefManualSymbolBuilder::GetReferenceType(RReferenceType::EReferenceTypeCategory inCategory, RType* inInnerType, uint32 inArrayItemCount)
{
	if (inCategory == RReferenceType::RTC_Pointer)
	{
		std::map<RType*, RReferenceType*>::iterator it = mReferenceTypes.find(inInnerType);
		if (it != mReferenceTypes.end())
			return it->second;
	}

	RReferenceType* type = new RReferenceType;
	type->mTypeDbIndex = mSymbolDb->GetTypes()->GetCount();
	type->mTypeFlags = 0;
	type->mTypeSize = inCategory == RReferenceType::RTC_Array ? inInnerType->mTypeSize * inArrayItemCount : 8;
	type->mTypeThisAdjust = 0;
	type->mReferenceTypeCategory = inCategory;
	type->mInnerType.mPtr = inInnerType;
	type->mArrayItemCount = inCategory == RReferenceType::RTC_Array ? inArrayItemCount : 1;
	if (inCategory == RReferenceType::RTC_Pointer)
		mReferenceTypes[inInnerType] = type;
	mSymbolDb->mTypes.AddSymbol("", type);
	return type;
}

RFunctionType* CRefManualSymbolBuilder::GetFunctionType(RFunctionType::ECallType inCallType, RType* inThisType, RType* inReturnType, const std::vector<RType*>& inArgTypes)
{
	bool cacheable = false;
	uint64 key;
	size_t argCount = inArgTypes.size();
	if (argCount <= 2)
	{
		RType* arg0 = argCount ? inArgTypes[0] : NULL;
		RType* arg1 = argCount == 2 ? inArgTypes[1] : NULL;
		if ((!inThisType || inThisType->mTypeDbIndex <= 0xFFFE)
			&& (!inReturnType || inReturnType->mTypeDbIndex <= 0xFFFE)
			&& (!arg0 || arg0->mTypeDbIndex <= 0xFFFE)
			&& (!arg1 || arg1->mTypeDbIndex <= 0xFFFE))
		{
			key = ((uint64)(inThisType ? inThisType->mTypeDbIndex : 0xFFFF) << 48)
				| ((uint64)(inReturnType ? inReturnType->mTypeDbIndex : 0xFFFF) << 32)
				| ((uint64)(arg0 ? arg0->mTypeDbIndex : 0xFFFF) << 16)
				| (uint64)(arg1 ? arg1->mTypeDbIndex : 0xFFFF);
			cacheable = true;
			std::map<uint64, RFunctionType*>::iterator it = mFunctionTypes.find(key);
			if (it != mFunctionTypes.end())
				return it->second;
		}
	}

	RFunctionType* type = new RFunctionType;
	type->mTypeDbIndex = mSymbolDb->GetTypes()->GetCount();
	type->mThisType.mPtr = inThisType;
	type->mReturnType.mPtr = inReturnType;
	type->mTypeFlags = 0;
	type->mTypeSize = 8;
	type->mTypeThisAdjust = 0;
	type->mCallType = inCallType;
	type->mArgTypes.resize((int32)inArgTypes.size());
	for (int32 i = 0; i < (int32)inArgTypes.size(); i++)
		type->mArgTypes[i].mPtr = inArgTypes[i];

	if (cacheable)
		mFunctionTypes[key] = type;
	mSymbolDb->mTypes.AddSymbol("", type);
	return type;
}

RCustomType* CRefManualSymbolBuilder::GetCustomType(RCustomType::ECustomTypeCategory inCategory, RType* inInnerType, RCustomType::IStdManipulator* inManipulator)
{
	uint64 key = (uint64)(inInnerType ? inInnerType->mTypeDbIndex : 0xFFFFFFFF) | ((uint64)inCategory << 32);
	std::map<uint64, RCustomType*>::iterator it = mCustomTypes.find(key);
	if (it != mCustomTypes.end())
		return it->second;

	RCustomType* type = new RCustomType;
	type->mTypeDbIndex = mSymbolDb->GetTypes()->GetCount();
	type->mTypeFlags = 0;
	switch (inCategory)
	{
	case RCustomType::CTC_StdString:
	case RCustomType::CTC_StdWString:
	case RCustomType::CTC_WeakRtId:
	case RCustomType::CTC_StrongRtId:
	case RCustomType::CTC_EmbeddedObject:
		type->mTypeSize = 8;
		break;
	case RCustomType::CTC_StdVector:
		type->mTypeSize = 24;
		break;
	case RCustomType::CTC_StdDeque:
		type->mTypeSize = 80;
		break;
	case RCustomType::CTC_StdMap:
	case RCustomType::CTC_StdSet:
		type->mTypeSize = 48;
		break;
	default:
		type->mTypeSize = 0;
		break;
	}
	type->mTypeThisAdjust = 0;
	type->mCustomTypeCategory = inCategory;
	type->mInnerType.mPtr = inInnerType;
	type->mManipulator = inManipulator;
	mCustomTypes[key] = type;
	mSymbolDb->mTypes.AddSymbol("", type);
	return type;
}

RNamedType* CRefManualSymbolBuilder::GetNamedType(const std::string& inName)
{
	RNamedType* type;
	RClass* rclass = mSymbolDb->mClasses.GetNamed(inName, false);
	if (rclass)
	{
		std::map<RClass*, RClassRef*>::iterator it = mClassRefs.find(rclass);
		if (it != mClassRefs.end())
			return it->second;

		RClassRef* classRef = new RClassRef;
		classRef->mName = inName;
		classRef->mClass = rclass;
		classRef->mTypeSize = rclass->GetSize();
		mClassRefs[rclass] = classRef;
		type = classRef;
	}
	else
	{
		REnum* renum = mSymbolDb->mEnums.GetNamed(inName, false);
		if (renum)
		{
			std::map<REnum*, REnumRef*>::iterator it = mEnumRefs.find(renum);
			if (it != mEnumRefs.end())
				return it->second;

			REnumRef* enumRef = new REnumRef;
			enumRef->mName = inName;
			enumRef->mEnum = renum;
			enumRef->mTypeSize = renum->GetSize();
			mEnumRefs[renum] = enumRef;
			type = enumRef;
		}
		else
		{
			type = new RUnknownNamedType;
			type->mName = inName;
			type->mTypeSize = 0;
		}
	}

	type->mTypeDbIndex = mSymbolDb->GetTypes()->GetCount();
	type->mTypeFlags = 0;
	type->mTypeThisAdjust = 0;
	mSymbolDb->mTypes.AddSymbol("", type);
	return type;
}

RAncestor* CRefManualSymbolBuilder::BuildAncestor(RClass* inClass, RClass* inAncestorClass, uint32 inOffset)
{
	RAncestor* ancestor = new RAncestor;
	ancestor->mMemberName = inAncestorClass->GetName();
	ancestor->mMemberAccess = RClassMember::MA_Public;
	ancestor->mMemberOuter = inClass;
	ancestor->mAncestorFlags = 0;
	ancestor->mOffset = inOffset;
	ancestor->mAncestorClass = inAncestorClass;
	inClass->mAncestors.AddSymbol(ancestor->mMemberName, ancestor);
	return ancestor;
}

RField* CRefManualSymbolBuilder::BuildField(RClass* inClass, const std::string& inName, uint32 inOffset, RType* inType)
{
	RField* field = new RField;
	field->mMemberName = inName;
	field->mMemberAccess = RClassMember::MA_Public;
	field->mMemberOuter = inClass;
	field->mFieldOffset = inOffset;
	field->mFieldType.mPtr = inType;
	field->mFieldFlags = 0;
	inClass->mFields.AddSymbol(field->mMemberName, field);
	return field;
}

RProperty* CRefManualSymbolBuilder::BuildProperty(RClass* inClass, const std::string& inName, RType* inType, RMethod* inGetter, RMethod* inSetter)
{
	RProperty* property = new RProperty;
	property->mMemberName = inName;
	property->mMemberAccess = RClassMember::MA_Public;
	property->mMemberOuter = inClass;
	property->mPropertyType.mPtr = inType;
	property->mPropertyFlags = 0;
	property->mPropertyGetterMethod = inGetter;
	property->mPropertySetterMethod = inSetter;
	inClass->mProperties.AddSymbol(property->mMemberName, property);
	return property;
}

RMethod* CRefManualSymbolBuilder::BuildMethod(RClass* inClass, const std::string& inName, DelegateBase* inDelegate, RFunctionType* inType, bool inIsSerialCommand)
{
	RMethod* method = new RMethod;
	method->mMemberName = inName;
	method->mMemberAccess = RClassMember::MA_Public;
	method->mMemberOuter = inClass;
	method->mMethodFlags = inIsSerialCommand ? RMethod::MF_CanInvokeSerialCommand : 0;
	method->mVtblOffset = (uint32)-1;
	method->mRVA = 0;
	method->mMethodType.mPtr = inType;
	method->mMethodDelegate = inDelegate;
	method->mVirtualBase = NULL;
	method->mMethodInvokePtr = NULL;
	inClass->mMethods.AddSymbol(method->mMemberName, method);
	return method;
}

REvent* CRefManualSymbolBuilder::BuildEvent(RClass* inClass, const std::string& inName, uint32 inOffset, RFunctionType* inType, bool inIsSerialCommand)
{
	REvent* event = new REvent;
	event->mMemberName = inName;
	event->mEventFlags = inIsSerialCommand ? REvent::EF_SerialCommand : 0;
	event->mMemberAccess = RClassMember::MA_Public;
	event->mEventOffset = inOffset;
	event->mMemberOuter = inClass;
	event->mEventType.mPtr = inType;
	inClass->mEvents.AddSymbol(event->mMemberName, event);
	return event;
}

RAttribute* CRefManualSymbolBuilder::BuildAttribute(const std::string& inName, const CRefAttributeVariant& inValue)
{
	RAttribute* attribute = new RAttribute;
	attribute->mName = inName;
	attribute->mMethod = NULL;
	attribute->mValue = inValue;
	return attribute;
}

/////////////// CRefAttributeVariant ///////////////

CRefAttributeVariant& CRefAttributeVariant::operator=(const CRefAttributeVariant& inOther) = default;

bool CRefAttributeVariant::GetBool() const
{
	switch (mType)
	{
	case VT_Bool:
		return mUInt32 != 0;
	case VT_UInt32:
		return mUInt32 != 0;
	case VT_SInt32:
		return mSInt32 != 0;
	case VT_Float:
		return mFloat != 0.0f;
	case VT_UInt64:
		return mUInt64 != 0;
	case VT_SInt64:
		return mSInt64 != 0;
	case VT_RtId:
		return mUInt64 != 0;
	case VT_Double:
		return mDouble != 0.0;
	case VT_String:
		return mString == "1" || mString == "true";
	case VT_WString:
		return mWString == L"1" || mWString == L"true";
	}
	return false;
}

std::string CRefAttributeVariant::GetString() const
{
	switch (mType)
	{
	case VT_Bool:
		return mUInt32 ? "true" : "false";
	case VT_UInt32:
		return StrFormat("%d", mUInt32);
	case VT_SInt32:
		return StrFormat("%d", mSInt32);
	case VT_Float:
		return StrFormat("%f", mFloat);
	case VT_UInt64:
		return StrFormat("%li", mUInt64);
	case VT_SInt64:
		return StrFormat("%li", mSInt64);
	case VT_Double:
		return StrFormat("%f", mDouble);
	case VT_String:
		return mString;
	case VT_WString:
		return WStringToString(mWString);
	case VT_RtId:
	{
		RtId id(mUInt64);
		std::string str;
		id.ToString(str);
		return str;
	}
	}
	return "";
}

std::wstring CRefAttributeVariant::GetWString() const
{
	switch (mType)
	{
	case VT_Bool:
		return mUInt32 ? L"true" : L"false";
	case VT_UInt32:
		return StrFormat(L"%d", mUInt32);
	case VT_SInt32:
		return StrFormat(L"%d", mSInt32);
	case VT_Float:
		return StrFormat(L"%f", mFloat);
	case VT_UInt64:
		return StrFormat(L"%li", mUInt64);
	case VT_SInt64:
		return StrFormat(L"%li", mSInt64);
	case VT_Double:
		return StrFormat(L"%f", mDouble);
	case VT_String:
		return StringToWString(mString);
	case VT_WString:
		return mWString;
	case VT_RtId:
	{
		RtId id(mUInt64);
		std::wstring str;
		id.ToString(str);
		return str;
	}
	}
	return L"";
}

RtId CRefAttributeVariant::GetRtId() const
{
	switch (mType)
	{
	case VT_Bool:
		return RtId();
	case VT_UInt32:
		return RtId();
	case VT_SInt32:
		return RtId();
	case VT_Float:
		return RtId();
	case VT_UInt64:
		return RtId(mUInt64);
	case VT_SInt64:
		return RtId(mUInt64);
	case VT_Double:
		return RtId();
	case VT_String:
		return RtId::StaticParse(mString);
	case VT_WString:
		return RtId::StaticParse(mWString);
	case VT_RtId:
		return RtId(mUInt64);
	}
	return RtId();
}

uint32 CRefAttributeVariant::GetUInt32() const
{
	switch (mType)
	{
	case VT_Bool:
		return (uint32)mUInt32;
	case VT_UInt32:
		return (uint32)mUInt32;
	case VT_SInt32:
		return (uint32)mSInt32;
	case VT_Float:
		return (uint32)mFloat;
	case VT_UInt64:
		return (uint32)mUInt64;
	case VT_SInt64:
		return (uint32)mSInt64;
	case VT_Double:
		return (uint32)mDouble;
	case VT_String:
		return (uint32)atoi(mString.c_str());
	case VT_WString:
		return (uint32)_wtoi(mWString.c_str());
	case VT_RtId:
		return (uint32)mUInt64;
	}
	return 0;
}

int32 CRefAttributeVariant::GetSInt32() const
{
	switch (mType)
	{
	case VT_Bool:
		return (int32)mUInt32;
	case VT_UInt32:
		return (int32)mUInt32;
	case VT_SInt32:
		return (int32)mSInt32;
	case VT_Float:
		return (int32)mFloat;
	case VT_UInt64:
		return (int32)mUInt64;
	case VT_SInt64:
		return (int32)mSInt64;
	case VT_Double:
		return (int32)mDouble;
	case VT_String:
		return (int32)atoi(mString.c_str());
	case VT_WString:
		return (int32)_wtoi(mWString.c_str());
	case VT_RtId:
		return (int32)mUInt64;
	}
	return 0;
}

uint64 CRefAttributeVariant::GetUInt64() const
{
	switch (mType)
	{
	case VT_Bool:
		return (uint64)mUInt32;
	case VT_UInt32:
		return (uint64)mUInt32;
	case VT_SInt32:
		return (uint64)mSInt32;
	case VT_Float:
		return (uint64)mFloat;
	case VT_UInt64:
		return (uint64)mUInt64;
	case VT_SInt64:
		return (uint64)mSInt64;
	case VT_Double:
		return (uint64)mDouble;
	case VT_String:
		return (uint64)atoi(mString.c_str());
	case VT_WString:
		return (uint64)_wtoi(mWString.c_str());
	case VT_RtId:
		return (uint64)mUInt64;
	}
	return 0;
}

int64 CRefAttributeVariant::GetSInt64() const
{
	switch (mType)
	{
	case VT_Bool:
		return (int64)mUInt32;
	case VT_UInt32:
		return (int64)mUInt32;
	case VT_SInt32:
		return (int64)mSInt32;
	case VT_Float:
		return (int64)mFloat;
	case VT_UInt64:
		return (int64)mUInt64;
	case VT_SInt64:
		return (int64)mSInt64;
	case VT_Double:
		return (int64)mDouble;
	case VT_String:
		return (int64)atoi(mString.c_str());
	case VT_WString:
		return (int64)_wtoi(mWString.c_str());
	case VT_RtId:
		return (int64)mUInt64;
	}
	return 0;
}

float CRefAttributeVariant::GetFloat() const
{
	switch (mType)
	{
	case VT_Bool:
		return (float)mUInt32;
	case VT_UInt32:
		return (float)mUInt32;
	case VT_SInt32:
		return (float)mSInt32;
	case VT_Float:
		return (float)mFloat;
	case VT_UInt64:
		return (float)mUInt64;
	case VT_SInt64:
		return (float)mSInt64;
	case VT_Double:
		return (float)mDouble;
	case VT_String:
		return (float)atof(mString.c_str());
	case VT_WString:
		return (float)_wtof(mWString.c_str());
	case VT_RtId:
		return (float)mUInt64;
	}
	return 0.0f;
}

double CRefAttributeVariant::GetDouble() const
{
	switch (mType)
	{
	case VT_Bool:
		return (double)mUInt32;
	case VT_UInt32:
		return (double)mUInt32;
	case VT_SInt32:
		return (double)mSInt32;
	case VT_Float:
		return (double)mFloat;
	case VT_UInt64:
		return (double)mUInt64;
	case VT_SInt64:
		return (double)mSInt64;
	case VT_Double:
		return (double)mDouble;
	case VT_String:
		return (double)atof(mString.c_str());
	case VT_WString:
		return (double)_wtof(mWString.c_str());
	case VT_RtId:
		return (double)mUInt64;
	}
	return 0.0;
}

}
