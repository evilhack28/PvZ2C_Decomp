//
//  ObjectTypeDescriptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ObjectTypeDescriptor.h"

ObjectTypeDescriptor::ObjectTypeDescriptor(const ObjectTypeDescriptor& i_other)
	: RtObject(i_other), TypeName(i_other.TypeName)
{
}

ObjectTypeDescriptor::ObjectTypeDescriptor(ObjectTypeDescriptor&& i_other)
	: RtObject(i_other), TypeName(static_cast<std::string&&>(i_other.TypeName))
{
}

ObjectTypeDescriptor& ObjectTypeDescriptor::operator=(const ObjectTypeDescriptor& i_other)
{
	TypeName = i_other.TypeName;
	return *this;
}

ObjectTypeDescriptor::~ObjectTypeDescriptor()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ObjectTypeDescriptor);
