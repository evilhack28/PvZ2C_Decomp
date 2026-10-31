//
//  RtId.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtId.h"
#include "SexyAppFramework/RtSerial.h"
#include "SexyAppFramework/RtDb.h"

using namespace Sexy;

uint32 RtId::sImplicitTableIndex = 0xffffffff;

void RtId::StaticSetImplicitTableIndex(uint32 inTableIndex)
{
	sImplicitTableIndex = inTableIndex;
}

uint32 RtId::StaticGetImplicitTableIndex()
{
	return sImplicitTableIndex;
}

void RtId::Serialize(RtSerialBuffer* inBuffer)
{
	if (inBuffer->IsReading())
	{
		int8 type = inBuffer->ReadInt8Fixed();
		switch (type)
		{
		case 0:
			*this = RtId();
			break;
		case 1:
		case 2:
		{
			std::wstring packageName;
			RtDbTable* table;
			if (type == 1)
			{
				table = RtDb::GetDb()->GetTable(sImplicitTableIndex);
				packageName = L".";
			}
			else
			{
				inBuffer->ReadUTF8String(packageName);
				table = RtDb::GetDb()->GetTable(RtName(packageName));
			}
			uint32 slot = inBuffer->ReadInt32VarU();
			uint32 revision = inBuffer->ReadInt32VarU();
			uint32 dbTime = inBuffer->ReadInt32Fixed();
			Uid uid(slot, revision, dbTime);
			if (!table || !uid)
				*this = RtId();
			else
				*this = table->GetIdForUid(uid);
			break;
		}
		case 3:
		{
			std::wstring packageName;
			std::wstring aliasName;
			inBuffer->ReadUTF8String(packageName);
			inBuffer->ReadUTF8String(aliasName);
			if (packageName == L".")
			{
				RtDbTable* table = RtDb::GetDb()->GetTable(sImplicitTableIndex);
				*this = RtId(RtName(aliasName), table->GetCurrentPackageName());
			}
			else
			{
				RtName package(packageName);
				RtName alias(aliasName);
				*this = RtId(alias, package);
			}
			break;
		}
		}
		return;
	}
	if (__builtin_expect(!GetValue(), 0))
	{
		inBuffer->WriteInt8Fixed(0);
	}
	else if (!IsNamed())
	{
		if (!RtDb::GetDb()->GetObjectForId(*this))
			inBuffer->WriteInt8Fixed(0);
		else
		{
			uint32 tableIndex = GetTableIndex();
			if (tableIndex == sImplicitTableIndex && !RtDb::GetDb()->GetTable(tableIndex)->HasCurrentPackage())
				inBuffer->WriteInt8Fixed(1);
			else
			{
				inBuffer->WriteInt8Fixed(2);
				inBuffer->WriteUTF8String(RtDb::GetDb()->GetTable(tableIndex)->GetCurrentPackageName().GetString());
			}
			Uid uid = RtDb::GetDb()->GetUidForId(*this);
			inBuffer->WriteInt32VarU(uid.mSlot);
			inBuffer->WriteInt32VarU(uid.mRevision);
			inBuffer->WriteInt32Fixed(uid.mDbTime);
		}
	}
	else
	{
		RtName packageName(GetPackageNameIndex());
		RtName aliasName(GetAliasNameIndex());
		inBuffer->WriteInt8Fixed(3);
		inBuffer->WriteUTF8String(packageName.GetString());
		inBuffer->WriteUTF8String(aliasName.GetString());
	}
}

bool RtId::IsRtIdString(const std::string& inStr)
{
	if (__builtin_expect(!!(inStr.size() > 5 && !(inStr.substr(0, 5) != "RTID(")), 0))
		return inStr[inStr.size() - 1] == ')';
	return false;
}

bool RtId::IsRtIdString(const std::wstring& inStr)
{
	if (__builtin_expect(!!(inStr.size() > 5 && !(inStr.substr(0, 5) != L"RTID(")), 0))
		return inStr[inStr.size() - 1] == L')';
	return false;
}

void RtId::ToString(std::string& outStr, bool inMemoryOnly) const
{
	if (!GetValue())
	{
		outStr = "RTID(0)";
		return;
	}
	if (!IsNamed())
	{
		if (!inMemoryOnly)
		{
			const wchar_t* packageName = L".";
			if (GetTableIndex() != sImplicitTableIndex)
				packageName = RtDb::GetDb()->GetTable(GetTableIndex())->GetCurrentPackageName().GetString();
			Uid uid = RtDb::GetDb()->GetUidForId(*this);
			outStr = StrFormat("RTID(%d.%d.%08x@%s)", uid.mRevision, uid.mSlot, uid.mDbTime, SexyStringToString(packageName).c_str());
		}
		else
		{
			if (GetTableIndex() == sImplicitTableIndex)
				outStr = StrFormat("RTID(:%d.%d)", GetSlotIndex(), GetRevision());
			else
				outStr = StrFormat("RTID(:%d.%d@%d)", GetSlotIndex(), GetRevision(), GetTableIndex());
		}
	}
	else
	{
		RtName packageName(GetPackageNameIndex());
		RtName aliasName(GetAliasNameIndex());
		outStr = StrFormat("RTID(%s@%s)", SexyStringToString(aliasName.GetString()).c_str(), SexyStringToString(packageName.GetString()).c_str());
	}
}

void RtId::ToString(std::wstring& outStr, bool inMemoryOnly) const
{
	if (!GetValue())
	{
		outStr = L"RTID(0)";
		return;
	}
	if (!IsNamed())
	{
		if (!inMemoryOnly)
		{
			const wchar_t* packageName = L".";
			if (GetTableIndex() != sImplicitTableIndex)
				packageName = RtDb::GetDb()->GetTable(GetTableIndex())->GetCurrentPackageName().GetString();
			Uid uid = RtDb::GetDb()->GetUidForId(*this);
			outStr = StrFormat(L"RTID(%d.%d.%08x@%ls)", uid.mRevision, uid.mSlot, uid.mDbTime, SexyStringToString(packageName).c_str());
		}
		else
		{
			if (GetTableIndex() == sImplicitTableIndex)
				outStr = StrFormat(L"RTID(:%d.%d)", GetSlotIndex(), GetRevision());
			else
				outStr = StrFormat(L"RTID(:%d.%d@%d)", GetSlotIndex(), GetRevision(), GetTableIndex());
		}
	}
	else
	{
		RtName packageName(GetPackageNameIndex());
		RtName aliasName(GetAliasNameIndex());
		outStr = StrFormat(L"RTID(%ls@%ls)", aliasName.GetString(), packageName.GetString());
	}
}

RtId RtId::StaticParse(const std::string& inStr)
{
	if (inStr.size() <= 5)
		return RtId();
	if (inStr.substr(0, 5) != "RTID(")
		return RtId();
	std::string body = inStr.substr(5);
	if (body[body.size() - 1] != ')')
		return RtId();
	body = body.substr(0, body.size() - 1);
	if (body == "0")
		return RtId();
	size_t at = body.find('@');
	if (at == std::string::npos)
		return RtId();
	std::string uidStr = body.substr(0, at);
	std::string packageStr = body.substr(at + 1);
	if (uidStr.empty() || packageStr.empty())
		return RtId();
	RtDbTable* table;
	if (packageStr == ".")
		table = RtDb::GetDb()->GetTable(sImplicitTableIndex);
	else
	{
		std::wstring packageW = StringToWString(packageStr);
		table = RtDb::GetDb()->GetTable(packageW);
	}
	if ((uint32)(uidStr[0] - '0') < 10)
	{
		size_t pos = uidStr.find('.');
		if (pos == std::string::npos)
			return RtId();
		std::string first = uidStr.substr(0, pos);
		uidStr = uidStr.substr(pos + 1);
		pos = uidStr.find('.');
		if (pos == std::string::npos)
			return RtId();
		std::string second = uidStr.substr(0, pos);
		uidStr = uidStr.substr(pos + 1);
		int slot = atoi(second.c_str());
		int revision = atoi(first.c_str());
		int32 dbTime = 0;
		uidStr = std::string("0x") + uidStr;
		StringToInt(uidStr, &dbTime);
		Uid uid(slot, revision, dbTime);
		if (!table || !uid)
			return RtId();
		RtId id = table->GetIdForUid(uid);
		return id;
	}
	RtName aliasName(StringToWString(uidStr));
	RtName packageName(StringToWString(packageStr));
	RtId id(aliasName, packageName);
	return id;
}

RtId RtId::StaticParse(const std::wstring& inStr)
{
	if (inStr.size() <= 5)
		return RtId();
	if (inStr.substr(0, 5) != L"RTID(")
		return RtId();
	std::wstring body = inStr.substr(5);
	if (body[body.size() - 1] != L')')
		return RtId();
	body = body.substr(0, body.size() - 1);
	if (body == L"0")
		return RtId();
	size_t at = body.find(L'@');
	if (at == std::wstring::npos)
		return RtId();
	std::wstring uidStr = body.substr(0, at);
	std::wstring packageStr = body.substr(at + 1);
	if (uidStr.empty() || packageStr.empty())
		return RtId();
	RtDbTable* table;
	if (packageStr == L".")
		table = RtDb::GetDb()->GetTable(sImplicitTableIndex);
	else
	{
		std::wstring packageW = packageStr;
		table = RtDb::GetDb()->GetTable(packageW);
	}
	if ((uint32)(uidStr[0] - L'0') < 10)
	{
		size_t pos = uidStr.find(L'.');
		if (pos == std::wstring::npos)
			return RtId();
		std::wstring first = uidStr.substr(0, pos);
		uidStr = uidStr.substr(pos + 1);
		pos = uidStr.find(L'.');
		if (pos == std::wstring::npos)
			return RtId();
		std::wstring second = uidStr.substr(0, pos);
		uidStr = uidStr.substr(pos + 1);
		int slot = _wtoi(second.c_str());
		int revision = _wtoi(first.c_str());
		int32 dbTime = 0;
		uidStr = std::wstring(L"0x") + uidStr;
		StringToInt(uidStr, &dbTime);
		Uid uid(slot, revision, dbTime);
		if (!table || !uid)
			return RtId();
		RtId id = table->GetIdForUid(uid);
		return id;
	}
	RtName aliasName(uidStr);
	RtName packageName(packageStr);
	RtId id(aliasName, packageName);
	return id;
}
