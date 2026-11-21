// SexyAppFramework/Base/BaseResource.cpp
//
// AUTHOR
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceTypes.h"
#include "SexyAppFramework/RtDb.h"

using namespace Sexy;

RT_CLASS_IMPLEMENT(BaseResource);

/////////////// Reflection ///////////////

BaseResource::EResourceRegistrationType BaseResource::GetRegistrationType()
{
	EResourceRegistrationType type = RRT_Unregistered;
	RtId id = GetRtId();
	switch (id.GetTableIndex())
	{
	case RtDb::SYSTEMTABLE_ResourceInstances:
		type = RRT_Normal;
		break;
	case RtDb::SYSTEMTABLE_ResourceInstancesHidden:
		type = RRT_Hidden;
		break;
	case RtDb::SYSTEMTABLE_ResourceInstancesUngrouped:
		type = RRT_Ungrouped;
		break;
	}
	return type;
}

static RtId GetResourceRtId(RtObject* inObject)
{
	BaseResource* resource = inObject->Cast<BaseResource>();
	if (resource)
		return resource->GetRtId();
	return RtId();
}

void BaseResource::StaticClassInit()
{
	RtIdProtocol* protocol = new RtIdProtocol;
	protocol->SetDelegate(MakeDelegate(&GetResourceRtId));
	StaticGetClass()->AddProtocol(protocol);
}
