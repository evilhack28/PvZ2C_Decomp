//
//  StoreGiftConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StoreGiftConfig.h"
#include "ProfileUtils.h"
#include "PlayerInfo.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

StoreGiftConfig::StoreGiftConfig()
{
}

StoreGiftConfig::~StoreGiftConfig()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(StoreGiftConfig);

void StoreGiftConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GiftPlantData);
	REFLECTION_CLASSBUILDER_END(GiftPlantData);

	REFLECTION_CLASSBUILDER_BEGIN(GiftPlantAvatarData);
	REFLECTION_CLASSBUILDER_END(GiftPlantAvatarData);

	REFLECTION_CLASSBUILDER_BEGIN(StoreGiftDataInfo);
	REFLECTION_CLASSBUILDER_END(StoreGiftDataInfo);

	REFLECTION_CLASSBUILDER_BEGIN(StoreGiftConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);
	REFLECTION_CLASSBUILDER_END(StoreGiftConfig);
}

/////////////// Accessors ///////////////

int StoreGiftConfig::GetGiftCoin(const std::string& sSku)
{
	for (size_t i = 0; i < m_StoreGiftDataArray.size();)
	{
		if (sSku == m_StoreGiftDataArray[i++].PropPtr.Get()->Sku)
			return m_StoreGiftDataArray[i - 1].iAddCoin;
	}
	return 0;
}

bool StoreGiftConfig::GetGiftPlantArray(const std::string& sSku, const std::vector<GiftPlantData>*& dataArray)
{
	for (size_t i = 0; i < m_StoreGiftDataArray.size(); i++)
	{
		if (sSku == m_StoreGiftDataArray[i].PropPtr.Get()->Sku && !m_StoreGiftDataArray[i].strGiftPlantArray.empty())
		{
			dataArray = &m_StoreGiftDataArray[i].strGiftPlantArray;
			return true;
		}
	}
	return false;
}

bool StoreGiftConfig::GetGiftAvatarPlantPieceArray(const std::string& sSku, const std::vector<GiftPlantAvatarData>*& dataArray)
{
	for (size_t i = 0; i < m_StoreGiftDataArray.size(); i++)
	{
		if (sSku == m_StoreGiftDataArray[i].PropPtr.Get()->Sku && !m_StoreGiftDataArray[i].strGiftAvatarPlantArray.empty())
		{
			dataArray = &m_StoreGiftDataArray[i].strGiftAvatarPlantArray;
			return true;
		}
	}
	return false;
}

bool StoreGiftConfig::GetGiftUnlockAvatarPlantArray(const std::string& sSku, const std::vector<std::string>*& dataArray)
{
	for (size_t i = 0; i < m_StoreGiftDataArray.size(); i++)
	{
		if (sSku == m_StoreGiftDataArray[i].PropPtr.Get()->Sku && !m_StoreGiftDataArray[i].sUnlockAvatarPlantArray.empty())
		{
			dataArray = &m_StoreGiftDataArray[i].sUnlockAvatarPlantArray;
			return true;
		}
	}
	return false;
}

bool StoreGiftConfig::GetGiftImage(const std::string& sSku, std::string& sImage)
{
	for (size_t i = 0; i < m_StoreGiftDataArray.size();)
	{
		if (sSku == m_StoreGiftDataArray[i++].PropPtr.Get()->Sku)
		{
			sImage = m_StoreGiftDataArray[i - 1].sImage;
			return true;
		}
	}
	return false;
}

/////////////// Logic ///////////////

bool StoreGiftConfig::ActiveGift(const std::string& sSku)
{
	PlayerInfo* playerInfo = ProfileUtils::Profile();
	bool found = false;
	for (size_t i = 0; i < m_StoreGiftDataArray.size();)
	{
		size_t index = i;
		found = sSku == m_StoreGiftDataArray[i++].PropPtr.Get()->Sku;
		if (found)
		{
		if (m_StoreGiftDataArray[index].iAddCoin > 0)
			playerInfo->AddCoins(m_StoreGiftDataArray[index].iAddCoin);

		if (!m_StoreGiftDataArray[index].strGiftPlantArray.empty())
		{
			for (size_t i = 0; i < m_StoreGiftDataArray[index].strGiftPlantArray.size(); i++)
			{
				GiftPlantData& plant = m_StoreGiftDataArray[index].strGiftPlantArray[i];
				playerInfo->AddPlantPieceCount(plant.sPlantName, plant.iPieceCount, true);
			}
		}

		if (!m_StoreGiftDataArray[index].strGiftAvatarPlantArray.empty())
		{
			for (size_t i = 0; i < m_StoreGiftDataArray[index].strGiftAvatarPlantArray.size(); i++)
			{
				GiftPlantAvatarData& avatar = m_StoreGiftDataArray[index].strGiftAvatarPlantArray[i];
				playerInfo->AddAvatarPiecesCount(avatar.sAvatarPlantName, E_AVATAR_NORMAL, avatar.iPieceCount, true);
			}
		}

		if (!m_StoreGiftDataArray[index].sUnlockAvatarPlantArray.empty())
		{
			for (size_t i = 0; i < m_StoreGiftDataArray[index].sUnlockAvatarPlantArray.size(); i++)
			{
				const std::string& name = m_StoreGiftDataArray[index].sUnlockAvatarPlantArray[i];
				if (playerInfo->IsPlantAvatarUnLocked(name, E_AVATAR_NORMAL, false))
				{
					playerInfo->AddAvatarPiecesCount(m_StoreGiftDataArray[index].sUnlockAvatarPlantArray[i], E_AVATAR_NORMAL, 15, false);
				}
				else
				{
					playerInfo->UnlockPlantAvatar(m_StoreGiftDataArray[index].sUnlockAvatarPlantArray[i], E_AVATAR_NORMAL);
					playerInfo->SetPlantAvatar(m_StoreGiftDataArray[index].sUnlockAvatarPlantArray[i], E_AVATAR_NORMAL);
				}
			}
		}
			break;
		}
	}
	return found;
}
