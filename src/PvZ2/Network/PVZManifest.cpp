//
//  PVZManifest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "PVZManifest.h"

PVZManifest::PVZManifest()
{
}

PVZManifest::~PVZManifest()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZManifest);

void PVZManifest::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZManifestFile);
		REFLECTION_CLASSBUILDER_FIELD(uint32, size_byte);
	REFLECTION_CLASSBUILDER_END(PVZManifestFile);

	REFLECTION_CLASSBUILDER_BEGIN(PVZManifest);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, url);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PVZManifestFile>, files_res);
		REFLECTION_CLASSBUILDER_FIELD(PVZManifestFile, file_apk);
	REFLECTION_CLASSBUILDER_END(PVZManifest);
}
