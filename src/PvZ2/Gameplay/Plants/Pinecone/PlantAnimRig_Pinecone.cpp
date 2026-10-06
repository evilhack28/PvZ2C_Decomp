//
//  PlantAnimRig_Pinecone.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Pinecone.h"

PlantAnimRig_Pinecone::~PlantAnimRig_Pinecone()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Pinecone);

void PlantAnimRig_Pinecone::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Pinecone);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_elec);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Pinecone);
}
