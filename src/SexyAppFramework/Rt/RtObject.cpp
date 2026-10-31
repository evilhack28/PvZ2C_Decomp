//
//  RtObject.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtObject.h"
#include "SexyAppFramework/RtSerial.h"
#include "SexyAppFramework/Reflection.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

RtObject::RtObject()
{
}

RtObject::RtObject(const RtObject&) = default;

RtObject::~RtObject()
{
}

void RtObject::Delete()
{
	delete this;
}

/////////////// Class ///////////////

RtClass* RtObject::sClass = RtObject::StaticGetClass();

RtClass* RtObject::GetClass() const
{
	return StaticGetClass();
}

RtClass* RtObject::StaticGetClass()
{
	if (!sClass)
	{
		sClass = RtClass::StaticNew();
		sClass->ClassInit("RtObject", NULL, (RtObject*(*)())StaticNew);
	}
	return sClass;
}

RtObject* RtObject::StaticNew()
{
	return 0;
}

bool RtObject::IsAbstract() const
{
	return true;
}

bool RtObject::IsA(const RtClass* inClass) const
{
	return GetClass()->IsDerivedFrom(inClass);
}

/////////////// Serialization ///////////////

bool RtObject::Serialize(const RtSerializeContext& inContext)
{
	Reflection::RClass* rclass = GetClass()->GetBoundReflectionClass(true);
	if (rclass)
		return rclass->InstanceRtonSync(this, inContext.GetSync(), inContext.GetKey(), inContext.GetMemberWildcards());
	return false;
}

bool RtObject::SerializeJsonToObj(const std::string& i_json, const std::string& i_key)
{
	RtSerialBuffer buffer;
	RtSerialRtonWriter writer(&buffer);
	std::string error;
	if (!RtSerial::JsonToRton(i_json.c_str(), writer, error))
		return false;
	RtSerialRtonReader reader(&buffer);
	RtSerialRtonSync sync(&reader);
	RtSerialRtonReader* syncReader = sync.GetReader();
	syncReader->BeginDocumentObject();
	bool result = Serialize(RtSerializeContext(&sync, i_key));
	syncReader->EndDocumentObject();
	return result;
}

bool RtObject::SerializeObjToJson(std::string& i_json, const std::string& i_key)
{
	bool result = false;
	RtSerialBuffer buffer;
	RtSerialRtonWriter writer(&buffer);
	RtSerialRtonSync sync(&writer);
	writer.BeginDocumentObject();
	bool serialized = Serialize(RtSerializeContext(&sync, i_key));
	writer.EndDocumentObject();
	if (serialized)
		result = RtSerial::RtonToJson(writer.GetBuffer()->GetDataPtr(), writer.GetBuffer()->GetDataSize(), i_json, false);
	return result;
}
