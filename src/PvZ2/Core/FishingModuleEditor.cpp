//
//  FishingModuleEditor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FishingModuleEditor.h"
#include "PvZ/ScaledApp.h"
#include "RedPacketRewardInfo.h"
#include "PvZ/LawnApp.h"
#include "PvZ/UIHelper.h"
#include "PvZ/Board.h"
#include "PvZ/LevelModuleManager.h"

static WEAKIMAGE(IMAGE_UI_STORE_BUTTON_PURPLE, "IMAGE_UI_STORE_BUTTON_PURPLE")
static WEAKIMAGE(IMAGE_UI_STORE_BUTTON_GREEN, "IMAGE_UI_STORE_BUTTON_GREEN")

__attribute__((noclone)) static int UIScaleNum(int i_num)
{
    return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void FishingModuleEditor::ScrollTargetReached(ScrollWidget* scrollWidget)
{
}

void FishingModuleEditor::ScrollTargetInterrupted(ScrollWidget* scrollWidget)
{
}

/////////////// ItemData ///////////////

FishingModuleEditor::ItemData::ItemData()
    : m_pBtn(NULL)
    , m_id(0)
{
}

/////////////// ItemPanel ///////////////

FishingModuleEditor::ItemPanel::ItemPanel()
    : m_IDGenerator(0)
{
}

FishingModuleEditor::ItemData* FishingModuleEditor::ItemPanel::GetItem(int id)
{
    if (m_mapItem.find(id) != m_mapItem.end())
        return &m_mapItem[id];
    return NULL;
}

void FishingModuleEditor::ItemPanel::SelectItem(int id)
{
    ItemData* item = GetItem(id);
    if (item)
    {
        if (!item->m_pBtn->IsRadioButtonSelected())
            item->m_pBtn->SetRadioButtonSelected();
    }
    if (m_pTab->IsRadioButtonSelected())
        return;
    m_pTab->SetRadioButtonSelected();
}

void FishingModuleEditor::ItemPanel::AddItem(ItemData& data)
{
    if (m_mapItem.find(data.m_id) != m_mapItem.end())
    {
        if (data.m_pBtn != NULL)
            delete data.m_pBtn;
        return;
    }
    if (data.m_id > m_IDGenerator)
        m_IDGenerator = data.m_id;
    data.m_pBtn->SetRadioStates(PVZ2UIImage(IMAGE_UI_STORE_BUTTON_PURPLE, PVZ2UIIMAGE_SINGLE_STRETCHED), PVZ2UIImage(IMAGE_UI_STORE_BUTTON_GREEN, PVZ2UIIMAGE_SINGLE_STRETCHED), false);
    data.m_pBtn->SetClipDisabled(false);
    data.m_pBtn->Resize(0, 0, UIScaleNum(130), UIScaleNum(30));
    m_pPanel->AddWidget(data.m_pBtn);

    std::vector<PVZ2UIButton*> buttons;
    std::vector<PVZ2UIButton*> linked;
    buttons.push_back(data.m_pBtn);
    WidgetList& widgets = m_pPanel->mWidgets;
    WidgetList::iterator it = widgets.begin();
    WidgetList::iterator end = widgets.end();
    for (; it != end; ++it)
    {
        PVZ2UIButton* button = (PVZ2UIButton*)*it;
        button->LinkRadioButtons(buttons);
        linked.push_back(button);
    }
    data.m_pBtn->LinkRadioButtons(linked);
    m_mapItem[data.m_id] = data;
}

void FishingModuleEditor::ItemPanel::RefreshIDGen(int baseID)
{
    int number = 0;
    std::string format = m_strPrefix + "%d";
    int maxNumber = 0;
    MapItemData::iterator it = m_mapItem.begin();
    MapItemData::iterator end = m_mapItem.end();
    for (; it != end; ++it)
    {
        PairItemData item = *it;
        if (sscanf(item.second.m_name.c_str(), format.c_str(), &number) == 1 && maxNumber < number)
            maxNumber = number;
    }
    m_IDGenerator = baseID + maxNumber;
}

void FishingModuleEditor::ItemPanel::RemoveItem(int id, bool bDelete)
{
    ItemData* item = GetItem(id);
    if (item != NULL)
    {
        if (bDelete)
        {
            m_pPanel->RemoveWidget(item->m_pBtn);
            if (item->m_pBtn != NULL)
                delete item->m_pBtn;
        }
        m_mapItem.erase(id);
    }
}

void FishingModuleEditor::ItemPanel::LayoutPanel()
{
    int y = 0;
    WidgetList& widgets = m_pPanel->mWidgets;
    WidgetList::iterator it = widgets.begin();
    WidgetList::iterator end = widgets.end();
    for (; it != end; ++it)
    {
        Sexy::Widget* widget = *it;
        widget->mY = y;
        widget->mX = 0;
        y += UIScaleNum(1) + widget->mHeight;
    }
    m_pPanel->mHeight = y;
    ((Sexy::ScrollWidget*)m_pPanel->mParent)->SetScrollMode(Sexy::ScrollWidget::SCROLL_VERTICAL);
}

FishingModuleEditor::ItemData* FishingModuleEditor::ItemPanel::GetSelectedItem()
{
    for (MapItemData::iterator it = m_mapItem.begin(); it != m_mapItem.end(); ++it)
    {
        if (it->second.m_pBtn->IsRadioButtonSelected())
            return &it->second;
    }
    return NULL;
}

void FishingModuleEditor::ItemPanel::InitData(ItemData& data, int baseID)
{
    data.m_id = m_IDGenerator + 1;
    data.m_name = Sexy::StrFormat("%s%d", m_strPrefix.c_str(), data.m_id - baseID);
}

/////////////// FishingModuleEditor ///////////////

std::string FishingModuleEditor::GetLayoutName()
{
    return "fishingeditor.json";
}

bool FishingModuleEditor::CheckSelectItem(int btnID)
{
    if (btnID >= 100 && btnID < 3000)
        m_iCurTab = 1;
    else if (btnID >= 3000 && btnID < 6000)
        m_iCurTab = 2;
    else
        return false;
    m_Tabs[m_iCurTab].SelectItem(btnID);
    RefreshDrawPoints();
    return false;
}

FishingProperties* FishingModuleEditor::GetProps()
{
    FishingProperties* props = NULL;
    for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_CURRENTLEVEL); it; ++it)
    {
        Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
        FishingProperties* found = ((Sexy::RtObject*)object)->Cast<FishingProperties>();
        if (found)
            props = found;
    }
    return props;
}

void FishingModuleEditor::RefreshDrawPoints()
{
    m_drawPoints.clear();
    m_drawCenter = Sexy::SexyVector2();
    if (m_Tabs.find(m_iCurTab) != m_Tabs.end())
    {
        ItemData* item = m_Tabs[m_iCurTab].GetSelectedItem();
        if (item != NULL)
        {
            m_drawPoints = item->m_Points;
            m_drawCenter = m_Tabs[m_iCurTab].m_center;
        }
    }
}

void FishingModuleEditor::DeletePoint()
{
    if (m_Tabs.find(m_iCurTab) == m_Tabs.end())
        return;
    ItemData* item = m_Tabs[m_iCurTab].GetSelectedItem();
    if (item == NULL)
        return;
    if (item->m_Points.size() < 2)
    {
        m_Tabs[m_iCurTab].RemoveItem(item->m_id, true);
        m_Tabs[m_iCurTab].LayoutPanel();
    }
    else
        item->m_Points.pop_back();
    RefreshDrawPoints();
}

void FishingModuleEditor::MouseDown(int x, int y, int theBtnNum, int theClickCount)
{
    if (m_Tabs.find(m_iCurTab) == m_Tabs.end())
        return;
    ItemData* item = m_Tabs[m_iCurTab].GetSelectedItem();
    if (item == NULL)
        return;
    Sexy::SexyVector2 point = Sexy::SexyVector2((float)x, (float)y) - m_Tabs[m_iCurTab].m_center;
    item->m_Points.push_back(point);
    RefreshDrawPoints();
}

FishingModuleEditor::FishingModuleEditor()
    : m_iCurTab(-1)
    , m_DefaultZombieType(NULL)
{
    FishingModule* module = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<FishingModule>();
    if (module)
        module->SetFishingState(FishingState_Editor);
}

FishingModuleEditor::~FishingModuleEditor()
{
    FishingModule* module = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<FishingModule>();
    if (module)
        module->SetFishingState(FishingState_Normal);
}

bool FishingModuleEditor::OnCreate()
{
    UISingletonDialog<FishingModuleEditor>::OnCreate();

    Sexy::Widget* zombieBack = GetWidget("ZombieBack");
    zombieBack->mClip = true;
    int top = UIScaleNum(5);
    Sexy::Rect rect(top, top, zombieBack->mWidth - UIScaleNum(10), zombieBack->mHeight - top);
    PVZ2UIScrollingWidget* zombieScroll = new PVZ2UIScrollingWidget(this);
    zombieScroll->Resize(rect);
    zombieScroll->SetScrollMode(Sexy::ScrollWidget::SCROLL_VERTICAL);
    zombieBack->AddWidget(zombieScroll);
    m_Tabs[1].m_pPanel = new Sexy::Widget();
    m_Tabs[1].m_pPanel->Resize(0, 0, rect.mWidth, rect.mHeight);
    zombieScroll->AddWidget(m_Tabs[1].m_pPanel);

    Sexy::Widget* pathBack = GetWidget("PathBack");
    pathBack->mClip = true;
    PVZ2UIScrollingWidget* pathScroll = new PVZ2UIScrollingWidget(this);
    pathScroll->Resize(rect);
    pathScroll->SetScrollMode(Sexy::ScrollWidget::SCROLL_VERTICAL);
    pathBack->AddWidget(pathScroll);
    m_Tabs[2].m_pPanel = new Sexy::Widget();
    m_Tabs[2].m_pPanel->Resize(0, 0, rect.mWidth, rect.mHeight);
    pathScroll->AddWidget(m_Tabs[2].m_pPanel);

    m_iCurTab = 1;
    std::vector<PVZ2UIButton*> tabs;
    PVZ2UIButton* zombieTab = InitButton("Tab_1", 1);
    PVZ2UIButton* pathTab = InitButton("Tab_2", 2);
    tabs.push_back(zombieTab);
    tabs.push_back(pathTab);

    zombieTab->SetRadioStates(PVZ2UIImage(IMAGE_UI_STORE_BUTTON_PURPLE, PVZ2UIIMAGE_SINGLE_STRETCHED), PVZ2UIImage(IMAGE_UI_STORE_BUTTON_GREEN, PVZ2UIIMAGE_SINGLE_STRETCHED), true);
    zombieTab->LinkRadioButtons(tabs);
    m_Tabs[1].m_pTab = zombieTab;
    m_Tabs[1].m_center = Sexy::SexyVector2((float)(gLawnApp->mWidth / 2), (float)(gLawnApp->mHeight / 2));
    m_Tabs[1].m_IDGenerator = 100;

    pathTab->SetRadioStates(PVZ2UIImage(IMAGE_UI_STORE_BUTTON_PURPLE, PVZ2UIIMAGE_SINGLE_STRETCHED), PVZ2UIImage(IMAGE_UI_STORE_BUTTON_GREEN, PVZ2UIIMAGE_SINGLE_STRETCHED), false);
    pathTab->LinkRadioButtons(tabs);
    m_Tabs[2].m_pTab = pathTab;
    m_Tabs[2].m_center = Sexy::SexyVector2((float)(gLawnApp->mWidth - 20), (float)(gLawnApp->mHeight / 2));
    m_Tabs[2].m_IDGenerator = 3000;

    InitButton("BtnSave", 3);
    InitButton("BtnShowHide", 4);
    InitButton("BtnNew", 5);
    InitButton("BtnDel", 6);
    InitButton("BtnView", 7);
    LoadProperty();
    return true;
}

PVZ2UIButton* FishingModuleEditor::InitButton(const std::string& name, int id)
{
    PVZ2UIButton* button = GetWidget<PVZ2UIButton>(name);
    PVZ2UIImage normal = button->GetImageNormal();
    PVZ2UIImage down = button->GetImageDown();
    normal.m_imageType = PVZ2UIIMAGE_SINGLE_STRETCHED;
    down.m_imageType = PVZ2UIIMAGE_SINGLE_STRETCHED;
    button->SetDialogStates(normal, down);
    button->SetFont(PrimeText_Game::Typeface_FZCuYuan_18->Typeface());
    button->mId = id;
    button->mButtonListener = this;
    return button;
}

void FishingModuleEditor::NewItem()
{
    if (m_Tabs.find(m_iCurTab) == m_Tabs.end())
        return;
    ItemData data;
    m_Tabs[m_iCurTab].InitData(data, m_iCurTab == 1 ? 100 : 3000);
    data.m_pBtn = new PVZ2UIButton(data.m_id, this, Sexy::StringToSexyString(data.m_name), Sexy::Color(Sexy::Color::White));
    data.m_pBtn->SetFont(PrimeText_Game::Typeface_FZCuYuan_18->Typeface());
    data.m_Points.push_back(Sexy::SexyVector2());
    m_Tabs[m_iCurTab].AddItem(data);
    m_Tabs[m_iCurTab].LayoutPanel();
    m_Tabs[m_iCurTab].SelectItem(data.m_id);
    RefreshDrawPoints();
}

void FishingModuleEditor::Draw(Sexy::Graphics* i_g)
{
    for (size_t i = 0; i < m_drawPoints.size(); i++)
    {
        Sexy::Rect rect;
        rect.mX = (int)(m_drawCenter.x + m_drawPoints[i].x);
        rect.mY = (int)(m_drawCenter.y + m_drawPoints[i].y);
        rect.mWidth = 10;
        rect.mHeight = 10;
        i_g->FillRect(rect);
        SexyString label = Sexy::StrFormat(L"%d(%d,%d)", i, (int)m_drawPoints[i].x, (int)m_drawPoints[i].y);
        Sexy::Rect labelRect(rect.mX - 10, rect.mY - 20, 200, 20);
        WriteWordInRect(i_g, label, labelRect, PrimeText_Game::Typeface_FZCuYuan_18->Typeface(), Sexy::Color(Sexy::Color::Red), DS_ALIGN_LEFT, true);
    }
}

void FishingModuleEditor::SetZombieGroup(FishingZombieGroup& group, std::vector<SexyVector2>& points)
{
    int n = 0;
    while ((size_t)n != group.Zombies.size() && (size_t)n != points.size())
    {
        group.Zombies[n].Offset = points[n];
        n++;
    }
    int used = n;
    size_t i = n;
    for (; i < points.size();)
    {
        FishingZombieInfo info;
        info.Type = m_DefaultZombieType;
        info.Offset = points[i++];
        info.Scale = 0.5f;
        group.Zombies.push_back(info);
        used++;
    }
    if (i < group.Zombies.size())
        group.Zombies.erase(group.Zombies.begin() + used, group.Zombies.end());
}

void FishingModuleEditor::ButtonDepress(int i_id)
{
    if (CheckSelectItem(i_id))
        return;
    switch (i_id)
    {
    case 1:
    case 2:
        m_iCurTab = i_id;
        RefreshDrawPoints();
        break;
    case 3:
        SaveProperty();
        break;
    case 4:
    {
        Sexy::Widget* zombieBack = GetWidget("ZombieBack");
        bool visible = !zombieBack->mVisible;
        zombieBack->mVisible = visible;
        GetWidget("PathBack")->mVisible = visible;
        GetWidget<PVZ2UIButton>("BtnShowHide")->mLabel = visible ? L"Hide" : L"Show";
        break;
    }
    case 5:
        NewItem();
        break;
    case 6:
        DeletePoint();
        break;
    case 7:
    {
        ItemData* zombieItem = m_Tabs[1].GetSelectedItem();
        ItemData* pathItem = m_Tabs[2].GetSelectedItem();
        if (zombieItem && pathItem)
        {
            FishingZombieGroup group;
            group.GroupName = zombieItem->m_name;
            SetZombieGroup(group, zombieItem->m_Points);
            FishingPath path;
            path.PathType = pathItem->m_name;
            path.PathPoints = pathItem->m_Points;
            FishingModule* module = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<FishingModule>();
            if (module)
                {
                Sexy::Point start = module->GetRandomStartPos();
                module->SpawnZombieGroup(start, &group, &path);
            }
        }
        break;
    }
    }
}

void FishingModuleEditor::LoadProperty()
{
    m_DefaultZombieType = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("skycity");
    FishingProperties* props = GetProps();
    if (!props)
        return;
    ItemPanel& groupPanel = m_Tabs[1];
    int id = 100;
    for (std::vector<FishingZombieGroup>::iterator it = props->ZombieGroups.begin(), end = props->ZombieGroups.end(); it != end; ++it)
    {
        FishingZombieGroup group = *it;
        ItemData data;
        data.m_name = group.GroupName;
        data.m_id = id;
        data.m_pBtn = new PVZ2UIButton(data.m_id, this, Sexy::StringToSexyString(data.m_name), Sexy::Color(Sexy::Color::White));
        data.m_pBtn->SetFont(PrimeText_Game::Typeface_FZCuYuan_18->Typeface());
        data.m_pBtn->mWidgetName = data.m_name;
        std::vector<FishingZombieInfo>::iterator zit = group.Zombies.begin();
        std::vector<FishingZombieInfo>::iterator zend = group.Zombies.end();
        for (; zit != zend; ++zit)
        {
            FishingZombieInfo info = *zit;
            data.m_Points.push_back(info.Offset);
        }
        id++;
        groupPanel.AddItem(data);
    }
    groupPanel.m_strPrefix = "group";
    groupPanel.LayoutPanel();
    groupPanel.RefreshIDGen(100);

    ItemPanel& pathPanel = m_Tabs[2];
    id = 3000;
    std::vector<FishingPath>::iterator pit = props->Paths.begin();
    std::vector<FishingPath>::iterator pend = props->Paths.end();
    for (; pit != pend; ++pit)
    {
        FishingPath path = *pit;
        ItemData data;
        data.m_name = path.PathType;
        data.m_id = id;
        data.m_pBtn = new PVZ2UIButton(data.m_id, this, Sexy::StringToSexyString(data.m_name), Sexy::Color(Sexy::Color::White));
        data.m_pBtn->SetFont(PrimeText_Game::Typeface_FZCuYuan_18->Typeface());
        data.m_pBtn->mWidgetName = data.m_name;
        data.m_Points = path.PathPoints;
        pathPanel.AddItem(data);
        id++;
    }
    pathPanel.m_strPrefix = "path";
    pathPanel.LayoutPanel();
    pathPanel.RefreshIDGen(3000);
}

void FishingModuleEditor::SaveProperty()
{
    const std::string& level = gLawnApp->m_board->GetLevel();
    FishingProperties* props = GetProps();
    if (!props)
        return;

    struct GroupNamed
    {
        const std::string& m_name;
        bool operator()(const FishingZombieGroup& i_group) const { return i_group.GroupName == m_name; }
    };
    struct PathNamed
    {
        const std::string& m_name;
        bool operator()(const FishingPath& i_path) const { return i_path.PathType == m_name; }
    };
    struct ItemNamed
    {
        const std::string& m_name;
        bool operator()(const std::pair<const int, ItemData>& i_item) const { return i_item.second.m_name == m_name; }
    };

    ItemPanel& groupTab = m_Tabs[1];
    std::string name;
    std::vector<FishingZombieGroup> newGroups;
    MapItemData& groupItems = groupTab.m_mapItem;
    for (MapItemData::iterator it = groupItems.begin(), end = groupItems.end(); it != end; ++it)
    {
        PairItemData item = *it;
        name = item.second.m_name;
        std::vector<FishingZombieGroup>::iterator found = std::find_if(props->ZombieGroups.begin(), props->ZombieGroups.end(), GroupNamed{name});
        if (found != props->ZombieGroups.end())
            SetZombieGroup(*found, item.second.m_Points);
        else
        {
            FishingZombieGroup group;
            group.GroupName = item.second.m_name;
            SetZombieGroup(group, item.second.m_Points);
            newGroups.push_back(group);
        }
    }
    for (std::vector<FishingZombieGroup>::iterator it = props->ZombieGroups.begin(); it != props->ZombieGroups.end();)
    {
        name = it->GroupName;
        if (std::find_if(groupItems.begin(), groupItems.end(), ItemNamed{name}) == groupItems.end())
            it = props->ZombieGroups.erase(it);
        else
            ++it;
    }
    props->ZombieGroups.insert(props->ZombieGroups.end(), newGroups.begin(), newGroups.end());

    ItemPanel& pathTab = m_Tabs[2];
    std::vector<FishingPath> newPaths;
    MapItemData& pathItems = pathTab.m_mapItem;
    for (MapItemData::iterator it = pathItems.begin(), end = pathItems.end(); it != end; ++it)
    {
        PairItemData item = *it;
        name = item.second.m_name;
        std::vector<FishingPath>::iterator found = std::find_if(props->Paths.begin(), props->Paths.end(), PathNamed{name});
        if (found != props->Paths.end())
            found->PathPoints = item.second.m_Points;
        else
        {
            FishingPath path;
            path.PathType = item.second.m_name;
            path.PathPoints = item.second.m_Points;
            newPaths.push_back(path);
        }
    }
    for (std::vector<FishingPath>::iterator it = props->Paths.begin(); it != props->Paths.end();)
    {
        name = it->PathType;
        if (std::find_if(pathItems.begin(), pathItems.end(), ItemNamed{name}) == pathItems.end())
            it = props->Paths.erase(it);
        else
            ++it;
    }
    props->Paths.insert(props->Paths.end(), newPaths.begin(), newPaths.end());

    std::string path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + Sexy::StrFormat("properties\\%s_fishing.json", level.c_str());
    PVZDB::GetInstance().SavePackageForTableToFile(PVZDB::TABLE_CURRENTLEVEL, path, true, false);
}
