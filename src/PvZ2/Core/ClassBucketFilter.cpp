//
//  ClassBucketFilter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ClassBucketFilter.h"
#include "BoardEntity.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ClassBucketFilter::ClassBucketFilter()
{
}

ClassBucketFilter::~ClassBucketFilter()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ClassBucketFilter);

void ClassBucketFilter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ClassBucketFilter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<ClassRestrictionSet>, Buckets);

	REFLECTION_CLASSBUILDER_END(ClassBucketFilter);
}

/////////////// Logic ///////////////

int ClassBucketFilter::size()
{
	return (int) Buckets.size();
}

int ClassBucketFilter::GetBucket(const BoardEntity* gameObject)
{
	int bucket = 0;
	for (auto& restrictionSet : Buckets)
	{
		if (restrictionSet.IsIncluded(gameObject))
			break;
		bucket++;
	}
	return bucket;
}

std::vector<std::vector<BoardEntityPtr>> ClassBucketFilter::FilterToBuckets(const std::vector<BoardEntityPtr>& i_incomingList)
{
	std::vector<std::vector<BoardEntityPtr>> buckets;
	buckets.reserve(Buckets.size() + 1);
	for (int i = 0; i < Buckets.size() + 1; i++)
		buckets.push_back(std::vector<BoardEntityPtr>());

	for (int i = 0; i < i_incomingList.size(); i++)
		buckets[GetBucket(i_incomingList[i].operator->())].push_back(i_incomingList[i]);

	return buckets;
}

std::vector<BoardEntityPtr> ClassBucketFilter::FilterToList(const std::vector<BoardEntityPtr>& i_incomingList, bool i_shuffleBuckets)
{
	std::vector<std::vector<BoardEntityPtr>> buckets = FilterToBuckets(i_incomingList);
	if (i_shuffleBuckets)
	{
		for (auto& bucket : buckets)
			std::random_shuffle(bucket.begin(), bucket.end());
	}

	std::vector<BoardEntityPtr> result;
	result.reserve(i_incomingList.size());
	for (auto& bucket : buckets)
	{
		for (auto& entity : bucket)
			result.push_back(entity);
	}
	return result;
}
