//
//  StreamingMusicList.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "StreamingMusicList.h"

StreamingMusicList::~StreamingMusicList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StreamingMusicList);

void StreamingMusicList::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StreamingMusicGroup);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, fileIds);
	REFLECTION_CLASSBUILDER_END(StreamingMusicGroup);

	REFLECTION_CLASSBUILDER_BEGIN(StreamingMusicList);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<StreamingMusicGroup>, groups);
	REFLECTION_CLASSBUILDER_END(StreamingMusicList);
}
