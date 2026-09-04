//
//  PropertySheetBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/ReflectionBuilder.h"

#include "PropertySheetBase.h"

/////////////// PropertySheetBase ///////////////

RT_CLASS_IMPLEMENT(PropertySheetBase);

void PropertySheetBase::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PropertySheetBase);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_END(PropertySheetBase);
}
