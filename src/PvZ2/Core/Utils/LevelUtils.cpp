//
//  LevelUtils.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LevelUtils.h"

/////////////// Lifecycle ///////////////

LevelUtils::~LevelUtils()
{
}

/////////////// Logic ///////////////

bool LevelUtils::DoesLevelExist(const std::string& i_levelName)
{
	return GetLevelInfo(i_levelName) != NULL;
}

LevelDefinitionPtr LevelUtils::loadLevelDefinitionFromResource(RtWeakPtr<GenericResFile> i_levelResource)
{
	UnloadLevelDefinition();
	PVZDB::GetInstance().LoadPackageForTable(PVZDB::TABLE_CURRENTLEVEL, i_levelResource);
	Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_CURRENTLEVEL);
	for (; it; ++it)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
		if (object && object->IsA<LevelDefinition>())
		{
			Sexy::RtWeakPtr<Sexy::RtObject> found = object;
			return found;
		}
	}
	return NULL;
}

void LevelUtils::UnloadLevelDefinition()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_CURRENTLEVEL); it; ++it)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
		if (object && object->IsA<GameObject>())
		{
			GameObject* gameObject = object->Cast<GameObject>();
			if (gameObject)
				gameObject->Destroy();
		}
	}
	PVZDB::GetInstance().GetTable(PVZDB::TABLE_CURRENTLEVEL)->Reset(false);
	PVZDB::GetInstance().GetTable(PVZDB::TABLE_CURRENTLEVEL)->Reset(true);
}
