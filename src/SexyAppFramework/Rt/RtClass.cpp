//
//  RtClass.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "RtObject.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RtClass);

/////////////// Registry ///////////////

unsigned long RtClass::StaticGetClassCount()
{
	return StaticGetClassVectorRef().size();
}

RtClass* RtClass::StaticGetClassIndexed(unsigned long inIndex)
{
	return StaticGetClassVectorRef()[inIndex];
}

/////////////// Hierarchy ///////////////

bool RtClass::IsDerivedFrom(const RtClass* inClass) const
{
	if (!inClass)
		return false;
	for (const RtClass* cls = this; cls; cls = cls->GetSuper())
	{
		if (cls == inClass)
			return true;
	}
	return false;
}

RtClass* RtClass::StaticGetClassNamed(const char* inClassName)
{
	std::string name(inClassName);
	DMapStringToClass::iterator it = StaticGetClassMapRef().find(name);
	if (it == StaticGetClassMapRef().end())
		return NULL;
	return it->second;
}

void RtClass::ClassInit(const char* inName, RtClass* inSuper, RtObject* (*inNewFunc)())
{
	mClassName = inName;
	mClassSuper = inSuper;
	mClassNewFunc = inNewFunc;
	StaticGetClassVectorRef().push_back(this);
	std::string name(inName);
	StaticGetClassMapRef()[name] = this;
}

/////////////// Lifecycle ///////////////

void RtClass::StaticCleanup()
{
	for (DVectorClass::iterator it = StaticGetClassVectorRef().begin(); it != StaticGetClassVectorRef().end(); ++it)
		delete *it;
}

RtClass::~RtClass()
{
	RtDbTable* table = RtDb::GetDb()->GetTable(RtDb::SYSTEMTABLE_RtClasses);
	if (table)
		table->ReleaseId(mClassRtId);
	int count = mClassProtocolVector.size();
	for (int i = 0; i < count; i++)
		delete mClassProtocolVector[i];
}

RtClass::RtClass()
: mClassName(NULL)
, mClassSuper(NULL)
, mClassNewFunc(NULL)
, mClassReflectionClass(NULL)
{
	RtDbTable* table = RtDb::GetDb()->GetTable(RtDb::SYSTEMTABLE_RtClasses);
	if (!table)
	{
		RtDbTable::TableOptions options;
		options.mTableName = L"System.RtClasses";
		options.mDisplayName = "System.RtClasses";
		options.mIsFixedContent = true;
		table = RtDb::GetDb()->CreateTable(RtDb::SYSTEMTABLE_RtClasses, &options);
	}
	mClassRtId = table->AllocId(this, RtDbTable::ODM_Never);
}
