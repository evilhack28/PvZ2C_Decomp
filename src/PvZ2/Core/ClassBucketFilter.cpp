//
//  ClassBucketFilter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ClassBucketFilter.h"

ClassBucketFilter::ClassBucketFilter()
{
}

ClassBucketFilter::~ClassBucketFilter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ClassBucketFilter);

void ClassBucketFilter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ClassBucketFilter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<ClassRestrictionSet>, Buckets);

	REFLECTION_CLASSBUILDER_END(ClassBucketFilter);
}
