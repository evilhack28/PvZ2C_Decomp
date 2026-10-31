//
//  RtDb.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtDb.h"
#include "SexyAppFramework/RtSerial.h"
#include "SexyAppFramework/Buffer.h"
#include "SexyAppFramework/SexyTime.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IAntiHackDriver.h"
#include <algorithm>

using namespace Sexy;

static RtDb* sDb = NULL;

/////////////// Lifecycle ///////////////

RtDb* RtDb::GetDb()
{
	if (sDb)
		return sDb;
	sDb = new RtDb();
	sRtDb = sDb;
	return sDb;
}

RtDb::RtDb()
{
	mCreationTimeStamp = SexyTime();
}

RtDb::~RtDb()
{
	for (TableVector::iterator it = mSystemTables.begin(); it != mSystemTables.end(); ++it)
		delete *it;
	for (TableVector::iterator it = mUserTables.begin(); it != mUserTables.end(); ++it)
		delete *it;
	mSystemTables.clear();
	mUserTables.clear();
}

/////////////// Tables ///////////////

RtDbTable* RtDb::GetTable(uint32 inTableIndex) const
{
	const TableVector* tables;
	if (inTableIndex & RtId::kSystemTableStart)
	{
		tables = &mSystemTables;
		inTableIndex &= ~RtId::kSystemTableStart;
	}
	else
		tables = &mUserTables;
	if (inTableIndex < (uint32)tables->size())
		return (*tables)[inTableIndex];
	return NULL;
}

bool RtDb::InternalRemoveTable(uint32 inTableIndex)
{
	TableVector* tables;
	if (inTableIndex & RtId::kSystemTableStart)
	{
		tables = &mSystemTables;
		inTableIndex &= ~RtId::kSystemTableStart;
	}
	else
		tables = &mUserTables;
	if (inTableIndex >= (uint32)tables->size())
		return false;
	(*tables)[inTableIndex] = NULL;
	return true;
}

RtDbTable* RtDb::GetTable(const RtName& inName) const
{
	NameToTableIndexMap::const_iterator it = mNameToTableIndexMap.find(inName.GetIndex());
	if (it != mNameToTableIndexMap.end())
		return GetTable(it->second);
	return NULL;
}

RtId RtDb::ResolveNamedId(const RtId& inId) const
{
	if (!inId)
		return inId;
	if (!inId.IsNamed())
		return inId;
	RtName packageName(inId.GetPackageNameIndex());
	RtDbTable* table = GetTable(packageName);
	if (!table)
		return RtId();
	RtName aliasName(inId.GetAliasNameIndex());
	return table->GetIdForAlias(aliasName);
}

RtDbTable* RtDb::CreateTable(uint32 inTableIndex, const RtDbTable::TableOptions* inOptions)
{
	RtDbTable* table = GetTable(inTableIndex);
	if (table)
		return table;
	TableVector* tables;
	uint32 index;
	if (inTableIndex & RtId::kSystemTableStart)
	{
		tables = &mSystemTables;
		index = inTableIndex & ~RtId::kSystemTableStart;
	}
	else
	{
		tables = &mUserTables;
		index = inTableIndex;
	}
	uint32 size = (uint32)tables->size();
	if (index >= size)
	{
		uint32 newSize = index + 16;
		tables->reserve(newSize);
		tables->resize(newSize);
		for (uint32 i = size; i < newSize; ++i)
			(*tables)[i] = NULL;
	}
	table = new RtDbTable(inTableIndex, inOptions);
	(*tables)[index] = table;
	table->OnTableUnloadingEvent += MakeDelegate(*GetDb(), &RtDb::OnTableUnloadingEvent);
	table->OnTableUnloadedEvent += MakeDelegate(*GetDb(), &RtDb::OnTableUnloadedEvent);
	table->OnTableLoadingEvent += MakeDelegate(*GetDb(), &RtDb::OnTableLoadingEvent);
	table->OnTableLoadedEvent += MakeDelegate(*GetDb(), &RtDb::OnTableLoadedEvent);
	return table;
}

/////////////// Deletion ///////////////

void RtDb::RunDeferredDeletions(uint32 inTableIndex) const
{
	if (inTableIndex == 0xffffffff)
	{
		for (TableVector::const_iterator it = mSystemTables.begin(); it != mSystemTables.end(); ++it)
		{
			if (*it)
				(*it)->RunDeferredDeletions();
		}
		for (TableVector::const_iterator it = mUserTables.begin(); it != mUserTables.end(); ++it)
		{
			if (*it)
				(*it)->RunDeferredDeletions();
		}
	}
	else
	{
		RtDbTable* table = GetTable(inTableIndex);
		if (table)
			table->RunDeferredDeletions();
	}
}

/////////////// Packages ///////////////

bool RtDb::LoadPackageFromFile(uint32 inTableIndex, const std::string& inFilename)
{
	std::vector<TableFilenamePair> packageGroup;
	packageGroup.push_back(TableFilenamePair(inTableIndex, inFilename));
	return LoadPackageGroupFromFiles(packageGroup);
}

bool RtDb::SavePackageToFile(uint32 inTableIndex, const std::string& inFilename, bool inAsJson)
{
	std::vector<TableFilenamePair> packageGroup;
	packageGroup.push_back(TableFilenamePair(inTableIndex, inFilename));
	return SavePackageGroupToFiles(packageGroup, inAsJson);
}

bool RtDb::WriteRtonTableSummary(RtSerialBuffer* inBuffer) const
{
	uint32 tableCount = 0;
	for (TableVector::const_iterator it = mUserTables.begin(); it != mUserTables.end(); ++it)
	{
		if (*it)
			tableCount++;
	}
	for (TableVector::const_iterator it = mSystemTables.begin(); it != mSystemTables.end(); ++it)
	{
		if (*it)
			tableCount++;
	}

	RtSerialRtonWriter writer(inBuffer);
	writer.BeginDocumentObject();
	writer.WriteInt32VarU("version", 1);
	writer.BeginArray("tables", tableCount, RtSerialRtonTag::Object);
	for (TableVector::const_iterator it = mUserTables.begin(); it != mUserTables.end(); ++it)
	{
		RtDbTable* table = *it;
		if (table)
		{
			writer.BeginObject(NULL);
			table->WriteTableRtonKeys(writer);
			writer.EndObject();
		}
	}
	for (TableVector::const_iterator it = mSystemTables.begin(); it != mSystemTables.end(); ++it)
	{
		RtDbTable* table = *it;
		if (table)
		{
			writer.BeginObject(NULL);
			table->WriteTableRtonKeys(writer);
			writer.EndObject();
		}
	}
	writer.EndArray();
	writer.EndDocumentObject();
	return true;
}
