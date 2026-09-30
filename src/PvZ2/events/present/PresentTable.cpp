//
//  PresentTable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PresentTable.h"

PresentTable::~PresentTable()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PresentTable);

void PresentTable::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PresentTableEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PresentType);
		REFLECTION_CLASSBUILDER_FIELD(int, Weight);
	REFLECTION_CLASSBUILDER_END(PresentTableEntry);

	REFLECTION_CLASSBUILDER_BEGIN(PresentTable);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

		REFLECTION_CLASSBUILDER_FIELD(bool, Shiny);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PresentTableEntry>, Entries);
	REFLECTION_CLASSBUILDER_END(PresentTable);
}
