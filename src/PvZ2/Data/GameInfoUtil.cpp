//
//  GameInfoUtil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//
#include "SexyAppFramework/Common.h"
#include "PvZ/GameCommon.h"
#include "PvZ/UIEditor/UIRewardFrame.h"
#include "PvZ/GameInfoUtil.h"
#include "PvZ/TodLib/TodStringFile.h"
#include "PvZ/PlantAccessoryMgr.h"
#include "PvZ/PlantType.h"
#include "PvZ/ObjectTypeDirectory.h"
#include "PvZ/NameMapper.h"
#include "PvZ/UIEditor/StringHelper.h"

bool GameInfoUtil::GetRareByAccessaryName(std::string name, int& rare)
{
    AccessoryUIInfo info = PlantAccessoryMgr::GetInstance().GetAccessoryUIInfo(name);
    rare = info.Quality + 1;
    return true;
}

bool GameInfoUtil::GetRareByPlantName(std::string name, int& rare)
{
    bool found = false;
    RtWeakPtr<const PlantType> type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(name);
    if (type.IsValid())
    {
        found = true;
        rare = type->Rare;
    }
    return found;
}

SexyString GameInfoUtil::GetDescriptionById(int id)
{
    if (id == COINS_ID)
        return TodStringTranslate(_S("[COIN_STORE]"));
    if (id == GEMS_ID)
        return TodStringTranslate(_S("[GEM_STORE]"));
    {
        GameItemInfo info;
        if (GetItemInfoById(id, info))
            return info._name;
    }
    return SexyString(_S(""));
}

bool GameInfoUtil::GetItemInfoById(int id, GameItemInfo& info)
{
    GAME_ITEM_INFO item = GetGameItemInfo(id, FIND_ITEM_SET_ALL, 0);
    if (item.m_nId == 0)
        return false;

    std::string name;
    int rare;
    switch (item.m_nTypeSet)
    {
    case FIND_ITEM_SET_PLANT:
        name = PlantNameMapperServerID::GetInstance().GetNameForId(id);
        GetRareByPlantName(name, rare);
        info._rewardType = UIRewardFrame::Reward_Plant;
        break;
    case FIND_ITEM_SET_PLANT_CHIP:
        name = PlantChipNameMapperServerID::GetInstance().GetNameForId(id);
        GetRareByPlantName(name, rare);
        info._rewardType = UIRewardFrame::Reward_Plant_Piece;
        break;
    case FIND_ITEM_SET_AVATAR:
        name = AvatarNameMapperServerID::GetInstance().GetNameForId(id);
        GetRareByPlantName(name, rare);
        info._rewardType = UIRewardFrame::Reward_Avatar_Piece;
        break;
    case FIND_ITEM_SET_AVATAR_CHIP:
        name = AvatarChipNameMapperServerID::GetInstance().GetNameForId(id);
        GetRareByPlantName(name, rare);
        info._rewardType = UIRewardFrame::Reward_Avatar_Piece;
        break;
    case FIND_ITEM_SET_ACCESSORY:
        name = PlantAccessoryInfoMapper::GetInstance().GetNameForId(id);
        GetRareByAccessaryName(name, rare);
        info._rewardType = UIRewardFrame::Reward_Others;
        break;
    case FIND_ITEM_SET_ACCESSORY_CHIP:
        name = PlantAccessoryPieceMapper::GetInstance().GetNameForId(id);
        GetRareByAccessaryName(name, rare);
        info._rewardType = UIRewardFrame::Reward_Others;
        break;
    default:
        name = "";
        rare = 0;
        info._rewardType = UIRewardFrame::Reward_Others;
        break;
    }
    Image* img = StringHelper::ToImage(item.m_strImageId, false);
    if (item.m_nTypeSet == FIND_ITEM_SET_PLANT_CHIP)
        info._name = Sexy::StringToSexyString(item.m_strTypeName);
    else
        info._name = item.m_xstrName;
    info._type = item.m_nTypeSet;
    info._rare = rare;
    info._img = img;
    return true;
}
