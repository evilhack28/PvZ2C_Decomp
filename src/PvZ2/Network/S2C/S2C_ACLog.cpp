//
//  S2C_ACLog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "gameNetWork/ACNetworkData.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "ReflectionBuilder.h"

uint32 S2C_ACLog::m_logIndex = 0;

/////////////// Lifecycle ///////////////

S2C_ACLog::S2C_ACLog()
{
	m_id = m_logIndex++;
	m_gems = 0;
	m_rmb = 0;
}

/////////////// Accessors ///////////////

void S2C_ACLog::SetGems(GemCurrency gems)
{
	m_gems = gems;
}

void S2C_ACLog::SetPurchaseMoney(float rmb)
{
	m_rmb = rmb;
}

void S2C_ACLog::RefreshLogIndex()
{
	m_logIndex = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile()->GetACLogIndex();
}

/////////////// Logic ///////////////

void S2C_ACLog::SetUnlockPlant(int plantId)
{
	m_unlockedPlants.push_back(plantId);
}

void S2C_ACLog::SetPlantLevel(int plantId, int level)
{
	ACLOG_PlantStarLevel record;
	record.iCurrentPlantId = plantId;
	record.iCurrentLevel = level;
	m_plantStarLevelArray.push_back(record);
}

void S2C_ACLog::SetPlantPieces(int plantId, int pieces)
{
	ACLOG_PlantPieceRecord record;
	record.PlantId = plantId;
	record.PieceCount = pieces;
	m_plantPieceRecords.push_back(record);
}

void S2C_ACLog::SetMaterial(int i_id, int i_num)
{
	ACLOG_MaterialInfo info;
	info.id = i_id;
	info.count = i_num;
	m_materialList.push_back(info);
}

void S2C_ACLog::SetAccessoryPieces(const std::string& type, int pieces)
{
	ACLOG_AccessoryPiece piece;
	piece.Type = type;
	piece.PieceCount = pieces;
	m_accessoryPieces.push_back(piece);
}

void S2C_ACLog::SetPlantAvatar(int plantId, PlantAvatarType avatar)
{
	ACLOG_PlantAvatarInfo info;
	info.iPlantID = plantId;
	info.eAvatar = avatar;
	for (size_t i = 0; i < info.vecAvatarUnlocked.size(); i++)
	{
		if (avatar == (int)i)
			info.vecAvatarUnlocked[i] = 1;
		else
			info.vecAvatarUnlocked[i] = 0;
	}
	m_listPlantAvatarsAvatarInfo.push_back(info);
}

void S2C_ACLog::SetPlantAvatarPieces(int plantId, PlantAvatarType avatar, int pieces)
{
	ACLOG_PlantAvatarPiecesInfo info;
	info.iPlantID = plantId;
	for (size_t i = 0; i < info.vecAvatarPiecesCount.size(); i++)
	{
		if (avatar == (int)i)
			info.vecAvatarPiecesCount[i] = pieces;
		else
			info.vecAvatarPiecesCount[i] = 0;
	}
	m_listPlantAvatarPiecesInfo.push_back(info);
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ACLog);

void S2C_ACLog::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ACLOG_PlantPieceRecord);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, PlantId, pi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, PieceCount, pc);
	REFLECTION_CLASSBUILDER_END(ACLOG_PlantPieceRecord);

	REFLECTION_CLASSBUILDER_BEGIN(ACLOG_PlantStarLevel);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iCurrentPlantId, icpi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iCurrentLevel, icl);
	REFLECTION_CLASSBUILDER_END(ACLOG_PlantStarLevel);

	REFLECTION_ENUMBUILDER_BEGIN(PlantAvatarType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, (PlantAvatarType)-1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(normal, (PlantAvatarType)0);
	REFLECTION_ENUMBUILDER_END(PlantAvatarType);

	REFLECTION_CLASSBUILDER_BEGIN(ACLOG_PlantAvatarInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iPlantID, paipid);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(PlantAvatarType, eAvatar, avt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<uint8>, vecAvatarUnlocked, vaulok);
	REFLECTION_CLASSBUILDER_END(ACLOG_PlantAvatarInfo);

	REFLECTION_CLASSBUILDER_BEGIN(ACLOG_PlantAvatarPiecesInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iPlantID, papipid);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, vecAvatarPiecesCount, vapc);
	REFLECTION_CLASSBUILDER_END(ACLOG_PlantAvatarPiecesInfo);

	REFLECTION_CLASSBUILDER_BEGIN(ACLOG_AccessoryPiece);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, Type, acpt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, PieceCount, acpc);
	REFLECTION_CLASSBUILDER_END(ACLOG_AccessoryPiece);

	REFLECTION_CLASSBUILDER_BEGIN(ACLOG_MaterialInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, id, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME_UNSAFE(int32, count, count);
	REFLECTION_CLASSBUILDER_END(ACLOG_MaterialInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_ACLog);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint32, m_id, acli);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, m_rmb, y);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(GemCurrency, m_gems, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, m_unlockedPlants, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ACLOG_PlantStarLevel>, m_plantStarLevelArray, psla);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ACLOG_PlantPieceRecord>, m_plantPieceRecords, ppr);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ACLOG_PlantAvatarInfo>, m_listPlantAvatarsAvatarInfo, ulokpa);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ACLOG_PlantAvatarPiecesInfo>, m_listPlantAvatarPiecesInfo, lpapi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ACLOG_AccessoryPiece>, m_accessoryPieces, asp);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ACLOG_MaterialInfo>, m_materialList, mtrl);
	REFLECTION_CLASSBUILDER_END(S2C_ACLog);
}
