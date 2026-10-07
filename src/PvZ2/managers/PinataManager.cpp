//
//  PinataManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PinataManager.h"
#include "PvZ/ScaledApp.h"
#include "PvZ/LawnApp.h"
#include "PvZ/PlayerInfo.h"
#include "PvZ/ProfileMgr.h"
#include "PvZ/PopAnimRigHelper.h"

namespace Message
{
    void BirthdayZReward(int);
}

void PinataManager::rewardShown(const TheDayRewardItem* i_reward)
{
}

void PinataManager::onAnimationFinished(const std::string& i_animLabel)
{
}

PinataManager::PinataManager()
    : m_openedPinatas(0)
    , m_prizesRevealing(false)
    , m_pinataStyleChooser(NULL)
    , m_bOpenFinished(true)
{
}

PinataManager::~PinataManager()
{
    m_pinatas.clear();
}

std::vector<Pinata>& PinataManager::GetPinatas()
{
    return m_pinatas;
}

void PinataManager::SetPinataStyleChooser(PinataStyleChooser* i_chooser)
{
    m_pinataStyleChooser = i_chooser;
}

static __attribute__((noclone)) int UIScaleNum(int i_num)
{
    return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

bool PinataManager::IsLocationValid(const Sexy::Point& spt)
{
    std::vector<Pinata>::iterator it = m_pinatas.begin();
    std::vector<Pinata>::iterator end = m_pinatas.end();
    for (; it != end; ++it)
    {
        Pinata& p = *it;
        if (p.IsDropped())
        {
            int size = UIScaleNum(100);
            if (p.X <= spt.mX && spt.mX <= p.X + size && p.Y <= spt.mY && spt.mY <= p.Y + size)
                return !p.IsPopped();
        }
    }
    return false;
}

void PinataManager::onExplodeFinished(const std::string& i_animLabel)
{
    m_bOpenFinished = true;
    m_openedPinatas++;
    if (m_openedPinatas == LevelOfTheDayMgr::GetInstance().GetTotalRewardCount())
        m_onAllPinatasOpened();
}

void PinataManager::RevealAllPinataPrizes()
{
    m_prizesRevealing = true;
    if (!m_displayRewards.empty())
    {
        const TheDayRewardItem* reward = m_displayRewards.back();
        SelectUnPoppedPinataAtRandom()->RevealPrize(reward);
        m_displayRewards.pop_back();
    }
}

void PinataManager::InitRewardList()
{
    m_rewards.clear();
    std::vector<TheDayRewardItem>& pool = LevelOfTheDayMgr::GetInstance().GetTheDayRewardItemPool();
    std::vector<TheDayRewardItem>::iterator it = pool.begin();
    std::vector<TheDayRewardItem>::iterator end = pool.end();
    for (; it != end; ++it)
        m_rewards.push_back(&*it);
}

bool PinataManager::AreAllPrizesRevealed()
{
    bool result = m_prizesRevealing;
    if (result)
    {
        int revealed = 0;
        bool anyRevealing = false;
        std::vector<Pinata>::iterator it = m_pinatas.begin();
        std::vector<Pinata>::iterator end = m_pinatas.end();
        for (; it != end; ++it)
        {
            Pinata& p = *it;
            if (p.IsRevealed())
                revealed++;
            if (p.IsRevealing())
                anyRevealing = true;
        }
        if (revealed < 4)
            result = !(anyRevealing | (LevelOfTheDayMgr::GetInstance().GetTotalRewardCount() != revealed));
    }
    return result;
}

void PinataManager::GetPinatasToDraw(std::vector<Pinata*>& o_pinatasToDraw)
{
    std::vector<Pinata>::iterator it = m_pinatas.begin();
    std::vector<Pinata>::iterator end = m_pinatas.end();
    for (; it != end; ++it)
    {
        Pinata& p = *it;
        if (p.ShouldDraw)
            o_pinatasToDraw.push_back(&p);
    }
}

void PinataManager::DropPinatas(int i_numberOfPinatasToStartDropping)
{
    int dropped = 0;
    std::vector<Pinata>::iterator it = m_pinatas.begin();
    std::vector<Pinata>::iterator end = m_pinatas.end();
    for (; it != end; ++it)
    {
        Pinata& p = *it;
        if (!p.ShouldDraw && dropped < i_numberOfPinatasToStartDropping)
        {
            dropped++;
            p.ShouldDraw = true;
            p.StyleChooser = m_pinataStyleChooser;
            p.Drop();
        }
    }
}

Pinata* PinataManager::SelectUnPoppedPinataAtRandom()
{
    std::vector<Pinata*> unpopped;
    std::vector<Pinata>::iterator it = m_pinatas.begin();
    std::vector<Pinata>::iterator end = m_pinatas.end();
    for (; it != end; ++it)
    {
        Pinata& p = *it;
        if (!p.IsPopped())
            unpopped.push_back(&p);
    }
    std::random_shuffle(unpopped.begin(), unpopped.end());
    return unpopped[0];
}

PopAnimRigRectDrawer* PinataManager::createPinataPopAnimRigDrawer(std::string strPinataArt)
{
    PopAnimRig* rig;
    {
        CachedUIResourcePtr<Sexy::PopAnim> popAnim(strPinataArt.c_str());
        rig = PopAnimRig::CreateRigOutsideTable(popAnim, PopAnimRig::StaticGetClass());
    }
    rig->PlayAndContinue("idle", SELECT_RANDOM_INDEX_NOREPEAT);
    return new PopAnimRigRectDrawer(rig);
}

void PinataManager::RecvReward()
{
    if (m_rewards.empty())
        return;
    PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
    if (GetOpenedPinatasCount() == 0)
        profile->AddBirthZRecord(gLawnApp->GetRealBeijingTime());
    const TheDayRewardItem* reward = m_rewards.back();
    gMessageRouter->Post(&Message::BirthdayZReward, reward->eType);
    LevelOfTheDayRewardType type = reward->eType;
    if (type == THEDAYREWARDTYPE_COIN)
        profile->AddCoins(reward->iCount);
    else if (type == THEDAYREWARDTYPE_GEM)
        profile->AddGems(reward->iCount);
    else if (type == THEDAYREWARDTYPE_PLANT)
    {
        if (!profile->GetIsPlantUnlocked(reward->strItemName))
            profile->UnlockPlant(reward->strItemName);
        else
            profile->AddPlantPieceCount(reward->strItemName, 10);
    }
    else if (type == THEDAYREWARDTYPE_PLANTPIECE)
        profile->AddPlantPieceCount(reward->strItemName, reward->iCount);
    else if (type == THEDAYREWARDTYPE_AVATARPIECE)
        profile->AddAvatarPiecesCount(reward->strItemName, (PlantAvatarType)0, reward->iCount);
}

void PinataManager::SetupPinatas(int i_parentWidth, Sexy::Delegate0 i_onAllPinatasOpened)
{
    TheDayItem* item = LevelOfTheDayMgr::GetInstance().GetCurrentTheDayItem();
    if (item)
    {
        InitRewardList();
        m_onAllPinatasOpened = static_cast<Sexy::Delegate0&&>(i_onAllPinatasOpened);
        int cellW = UIScaleNum(140);
        int cellH = UIScaleNum(110);
        int stagger = UIScaleNum(35);
        int size = UIScaleNum(100);
        int baseX = (((cellW * -3 - size) - stagger) + i_parentWidth) / 2;
        int y = UIScaleNum(105);
        m_pinatas.resize(16);
        Pinata* p = &m_pinatas[0];
        int row = 0;
        do
        {
            row++;
            int odd = row & 1;
            int x = baseX + stagger * odd;
            int col = 0;
            do
            {
                p->X = x;
                p->Y = y;
                x += cellW;
                p->Drawer = createPinataPopAnimRigDrawer(item->strAnimPinataArt);
                p++;
                col++;
            } while (col != 4);
            y += cellH;
        } while (row != 4);
    }
}

const Pinata* PinataManager::PopPinata(const Sexy::Point& location)
{
    if (m_rewards.size() != 0)
    {
        std::vector<Pinata>::iterator it = m_pinatas.begin();
        std::vector<Pinata>::iterator end = m_pinatas.end();
        for (; it != end; ++it)
        {
            Pinata& p = *it;
            if (p.IsDropped())
            {
                int size = UIScaleNum(100);
                if (p.X <= location.mX && location.mX <= p.X + size && p.Y <= location.mY && location.mY <= p.Y + size)
                {
                    if (!p.IsPopped())
                    {
                        const TheDayRewardItem* reward = m_rewards.back();
                        m_rewards.pop_back();
                        p.Pop(Sexy::MakeDelegate(this, &PinataManager::onExplodeFinished), reward);
                        m_bOpenFinished = false;
                        rewardShown(reward);
                        return &p;
                    }
                    break;
                }
            }
        }
    }
    return NULL;
}
