//
//  SeedChooser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SeedChooser.h"
#include "LawnApp.h"
#include "Board.h"
#include "PlantTrialCardManager.h"
#include "NameMapper.h"
#include "StandardLevelIntro.h"
#include "Curve.h"
#include "ProfileMgr.h"
#include "PlayerInfoLocalSaveData.h"
#include "PVZ1ModeUtils.h"
#include "PVZ1ModePropertySheet.h"
#include "BusyAnimationManager.h"
#include "AudioMgr.h"
#include "TGALogMgr.h"
#include "Social/SocialMgr.h"
#include "SeedPacket_Tool.h"
#include "SeedBankModule.h"
#include "CustomLevelUtils.h"
#include "TodLib/TodStringFile.h"
#include "UIMessageBox.h"
#include "PVZ2UIDialog.h"
#include "ArtifactCultivationListView.h"
#include "NameMapper.h"
#include "UISpringFestivalActivity.h"
#include "UIEditor/StringHelper.h"
#include "HeroPlantUtils.h"
#include "UIHelper.h"
#include "PlantViewSubWidgets.h"
#include "PVZ2UIPlantCard.h"
#include "ReflectionBuilder.h"

static float UIScaleNum(float i_num)
{
	return gLawnApp->UIScaleNum(i_num);
}

static int UIScaleNum(int i_num)
{
	return gLawnApp->UIScaleNum(i_num);
}

static WEAKIMAGE(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD, "IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD");
static WEAKIMAGE(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD_PRESS, "IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD_PRESS");
static WEAKIMAGE(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_REMOVE, "IMAGE_UI_CHOOSER_FAVORITES_BUTTON_REMOVE");
static WEAKIMAGE(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_REMOVE_PRESS, "IMAGE_UI_CHOOSER_FAVORITES_BUTTON_REMOVE_PRESS");

static WEAKIMAGE(IMAGE_UI_CHOOSER_ACCESSORY_BUTTON, "IMAGE_UI_CHOOSER_ACCESSORY_BUTTON");
static WEAKIMAGE(IMAGE_UI_CHOOSER_ACCESSORY_BUTTON_PRESS, "IMAGE_UI_CHOOSER_ACCESSORY_BUTTON");

// BoardHelpers.h pulls in RiftUtils.h, which needs a header we do not have
namespace BoardHelpers
{
	int ApplyLevelOverride_RiftTimedToolSize();
}

namespace RiftUtils
{
	bool IsRiftTimedLevel();
}

static WEAKIMAGE(IMAGE_UI_PACKETS_EMPTY_PACKET, "IMAGE_UI_PACKETS_EMPTY_PACKET");

static SeedPacket* __attribute__((noinline)) PacketPassThrough(SeedPacket* i_packet) { return i_packet; }

static WEAKIMAGE(IMAGE_UI_DIALOG_ASSET_BG_GREEN_SHORT, "IMAGE_UI_DIALOG_ASSET_BG_GREEN_SHORT");
static WEAKIMAGE(IMAGE_UI_ARTIFACT_ITEMBG, "IMAGE_UI_ARTIFACT_ITEMBG");

static int sChooserColumns;
static int sChooserOffsetX;


static void MoveMatchesToFront(PlantTypeList& io_list, std::function<bool(PlantTypePtr)> i_predicate)
{
	std::vector<PlantTypePtr> matching;
	std::vector<PlantTypePtr> others;
	std::vector<PlantTypePtr>& plants = io_list.GetList();
	for (size_t i = 0; i < plants.size(); i++)
	{
		if (i_predicate(plants[i]))
			matching.push_back(plants[i]);
		else
			others.push_back(plants[i]);
	}
	plants.clear();
	for (size_t i = 0; i < matching.size(); i++)
		io_list.Add(matching[i]);
	for (size_t i = 0; i < others.size(); i++)
		io_list.Add(others[i]);
}

static Rect UIScaleNum(const Rect& i_rect)
{
	return gLawnApp->UIScaleNum(i_rect);
}

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(SeedChooser);

SeedChooser::SeedChooser()
{
	gLawnApp->LoadGroup("UI_Artifact");
	gLawnApp->LoadGroup("HeroPlant");
	Sexy::PrimeText::Instance()->ClearGlyphCache();
	m_chosenPacketCount = 0;
	m_chosenToolPacketCount = 0;
	uint8 slots = gLawnApp->m_board->GetSeedBankModule()->GetNumSlotsAvailableForChooser();
	m_scrollOffset = 0;
	m_imitaterChooserPacketIdx = -1;
	m_battleArrayType = (BattleArrayType)-1;
	m_BorrowFriendUserId = -1;
	m_BorrowButtonIndex = -1;
	m_chosenPacketCountMax = slots;
	m_requiredSelections = slots;
	m_shouldDrawArtifact = true;
	m_unk1A9 = true;
	m_hideChooser = false;
	m_seedBankProps = NULL;
	m_buttonReady = NULL;
	m_buttonReset = NULL;
	m_unk238 = NULL;
	m_buttonFavorite = NULL;
	m_buttonArtifact = NULL;
	m_buttonArtifactDetails = NULL;
	m_buttonBuyPlant = NULL;
	m_artifactWidget = NULL;
	m_artifactImage = NULL;
	m_unk228 = NULL;
	m_unk230 = NULL;
	m_heroPlantWidget = NULL;
	m_heroPlantImage = NULL;
	m_unk268 = NULL;
	m_bIsLoading = false;
	m_BorrowPlantId = 0;
	m_seedInfoWidget = NULL;
	m_toolTip = NULL;
	m_unk280 = false;
	m_previewDisplay = NULL;
	m_chooserPacketIndex = 0;
	m_hasSlideIn = false;
	m_unk290 = true;
	sChooserColumns = 5;
	sChooserOffsetX = 2;
	m_seedPacketType = L"UISeedBankPacket";
	m_specialSeedPacketType = L"UISeedBankRiftPacket";
	if (PVZ1ModeUtils::IsPlayingPVZ1Level())
	{
		PVZ1ModePropertySheet* properties = PVZ1ModePropertySheet::GetProperties();
		if (properties)
			m_pvz1Segmentation = properties->PvZ1PlantList.size();
	}
}

SeedChooser::~SeedChooser()
{
	gLawnApp->DeleteGroup("UI_Artifact");
	gLawnApp->DeleteGroup("HeroPlant");
	Sexy::PrimeText::Instance()->ClearGlyphCache();
	if (m_previewDisplay)
	{
		gLawnApp->mWidgetManager->RemoveWidget(m_previewDisplay);
		m_previewDisplay->RemoveAllWidgets(true, true);
		SAFE_DELETE(m_previewDisplay);
	}
	deleteChooserPackets();
	gMessageRouter->Unsubscribe(this);
	SAFE_DELETE(m_buttonReady);
	SAFE_DELETE(m_unk238);
	SAFE_DELETE(m_buttonReset);
	SAFE_DELETE(m_buttonFavorite);
	SAFE_DELETE(m_buttonArtifact);
	SAFE_DELETE(m_buttonArtifactDetails);
	SAFE_DELETE(m_buttonBuyPlant);
	SAFE_DELETE(m_unk228);
	SAFE_DELETE(m_unk230);
	SAFE_DELETE(m_unk268);
	SAFE_DELETE(m_seedInfoWidget);
	SAFE_DELETE(m_toolTip);
}

void SeedChooser::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SeedChooser);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(onPanBoardLeftFinished, onPanBoardLeftFinished);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(onPanBoardRightFinished, onPanBoardRightFinished);
	REFLECTION_CLASSBUILDER_END(SeedChooser);
}

/////////////// Accessors ///////////////

void SeedChooser::SetSeedPacketType(const RtName seedPacketType)
{
	m_seedPacketType = seedPacketType;
}

void SeedChooser::SetSpecialSeedPacketType(const RtName seedPacketType)
{
	m_specialSeedPacketType = seedPacketType;
}

void SeedChooser::InitRecordPacket(RtWeakPtr<SeedPacket> i_seedPacket, RtWeakPtr<SeedPacket> i_recordPacket)
{
}

/////////////// States ///////////////

void SeedChooser::onEnterState_Initializing(WidgetState i_prevState)
{
	gMessageRouter->Subscribe(Message::FreeplantingCheatEnabled, Sexy::MakeDelegate(*this, &SeedChooser::onCheatEnabled));
	gMessageRouter->Subscribe(Message::FreeplantingCheatDisabled, Sexy::MakeDelegate(*this, &SeedChooser::onCheatDisabled));
	gMessageRouter->Subscribe(Message::ItemPurchasedFromStore, Sexy::MakeDelegate(*this, &SeedChooser::onItemPurchasedFromStore));
	gMessageRouter->Subscribe(Message::DangerRoomReady, Sexy::MakeDelegate(*this, &SeedChooser::onDangerRoomInit));
	gMessageRouter->Subscribe(Message::ViewBoardOrZombiesButtonPressed, Sexy::MakeDelegate(*this, &SeedChooser::onViewBoardOrZombiesButtonPressed));
	gMessageRouter->Subscribe(Message::MsgError, Sexy::MakeDelegate(*this, &SeedChooser::onMsgError));
	gMessageRouter->Subscribe(Message::MsgBorrowFriendPlant, Sexy::MakeDelegate(*this, &SeedChooser::onMsgBorrowFriendPlant));
	gMessageRouter->Subscribe(Message::NoticeAccessoryUIClose, Sexy::MakeDelegate(*this, &SeedChooser::onPlantAccessoryActionComplete));
	gMessageRouter->Subscribe(Message::OrientationChanged, Sexy::MakeDelegate(*this, &SeedChooser::OnOrientationChanged));
	if (m_unk290)
	{
		m_seedPacketArea = UIScaleNum(Rect(19, 273, 501, 248));
		m_tabFrameRect = UIScaleNum(Rect(98, 57, 525, 540));
	}
	else
	{
		m_seedPacketArea = UIScaleNum(Rect(37, 273, 415, 233));
		m_tabFrameRect = UIScaleNum(Rect(103, 62, 473, 530));
	}
	m_tabFrameContentsRect = m_tabFrameRect;
	UIWidget::GetWidgetBySheetName("UIViewBoardOrZombies")->SetVisible(false);
}

void SeedChooser::updateState_Ready()
{
	if (__builtin_expect(!!(m_seedInfoWidget && !m_purchaseProps.IsValid()), 1))
	{
		delete m_seedInfoWidget;
		m_seedInfoWidget = nullptr;
	}
	if (__builtin_expect(!!(m_previewDisplay), 1))
		m_previewDisplay->ManualUpdate();
	if (m_buttonReady && !m_buttonReady->mDisabled)
	{
		bool isDown = IsPressed();
		if (!isDown)
		{
			m_buttonReady->mIsDown = isDown;
			m_buttonReady->mIsOver = isDown;
		}
	}
	if (m_buttonReset && !m_buttonReset->mDisabled)
	{
		bool isDown = IsPressed();
		if (!isDown)
		{
			m_buttonReset->mIsDown = isDown;
			m_buttonReset->mIsOver = isDown;
		}
	}
	if (m_unk268 && !m_unk268->mDisabled)
	{
		bool isDown = IsPressed();
		if (!isDown)
		{
			m_unk268->mIsDown = isDown;
			m_unk268->mIsOver = isDown;
		}
	}
	for (int i = 0; i < m_chosenPacketCountMax; i++)
	{
		ChooserPacketData& packet = m_bankPackets[i];
		if (packet.State != PS_Moving)
			continue;
		if (packet.MovingEndTime > PVZ_T())
		{
			packet.Position.x = CurveLerp<float>(packet.MovingStartTime, packet.MovingEndTime, PVZ_T(), packet.MovePositionStart.x, packet.MovePositionEnd.x, CURVE_EASE_OUT);
			packet.Position.y = CurveLerp<float>(packet.MovingStartTime, packet.MovingEndTime, PVZ_T(), packet.MovePositionStart.y, packet.MovePositionEnd.y, CURVE_EASE_OUT);
		}
		else
		{
			calcPacketPositionInBank(packet.SeedBankIndex, packet.Position);
			packet.State = PS_InBank;
			onLandInBank(packet);
		}
		packet.AttachedSeedPacket->SetPositionOffset(SexyVector2(packet.Position.x, packet.Position.y));
	}
}

void SeedChooser::updateState_Initializing()
{
	if (gLawnApp->m_board->GetSeedBank()->GetChildCount() != 0)
	{
		m_imageBankPacketEmpty = IMAGE_UI_PACKETS_EMPTY_PACKET;
		rebuildValidPlantTypeList();
		initButtons();
		for (int i = 0; i != m_chooserPackets.size(); i++)
		{
			if (m_chooserPackets[i].State != PS_Blacklisted)
			{
				setSeedPreview(m_chooserPackets[i]);
				break;
			}
		}
		initPlantFromRecord();
		const int toolSize = BoardHelpers::ApplyLevelOverride_RiftTimedToolSize();
		if (m_buttonReady)
			m_buttonReady->mDisabled = m_chosenPacketCount + toolSize != m_requiredSelections;
		setState(WS_Ready);
	}
}

void SeedChooser::onEnterState_Ready(WidgetState i_prevState)
{
}

void SeedChooser::onExitState_Initializing(WidgetState i_nextState)
{
}

void SeedChooser::onExitState_Ready(WidgetState i_nextState)
{
}

/////////////// Cheats ///////////////

void SeedChooser::onCheatEnabled()
{
	rebuildValidPlantTypeList();
}

void SeedChooser::onCheatDisabled()
{
	rebuildValidPlantTypeList();
}

void SeedChooser::onDangerRoomInit()
{
}

void SeedChooser::onNarrationFinished()
{
}

void SeedChooser::onBuyPlantButtonPressed()
{
}

bool SeedChooser::isFavoritesFeatureToggleEnabled()
{
	return true;
}

bool SeedChooser::checkForZombieTouch(const int i_mouseX, const int i_mouseY)
{
	return false;
}

void SeedChooser::onViewBoardOrZombiesButtonPressed()
{
	 SeedChooser::toggleHideChooser();
}

/////////////// Buttons ///////////////

void SeedChooser::ButtonPress(const int i_buttonID)
{
	if (i_buttonID == 0)
		SetVisible(false);
}

void SeedChooser::onRepickButtonPressed()
{
	gLawnApp->KillPVZ2Dialog();
}

void SeedChooser::onPlayButtonPressed()
{
	gLawnApp->KillPVZ2Dialog();
	sendBorrowRequestBeforeFinalize();
}

void SeedChooser::onPanBoardRightFinished()
{
	gLawnApp->m_board->PopAnimationMgr();
	SlideIn();
}

void SeedChooser::drawHeroPlant(Sexy::Graphics* i_graphics, const Point& i_position) const
{
	Draw3SliceImage(i_graphics, Rect(UIScaleNum(20) + i_position.mX, UIScaleNum(15) + i_position.mY, UIScaleNum(100), UIScaleNum(130)), IMAGE_UI_DIALOG_ASSET_BG_GREEN_SHORT);
	WriteWordInRect(i_graphics, TodStringTranslate(L"[HERO]"), Rect(UIScaleNum(20) + i_position.mX, UIScaleNum(17) + i_position.mY, UIScaleNum(95), UIScaleNum(30)), PrimeText_Game::Typeface_FZShaoEr_24_Outline->Typeface(), Color(Color::White), DS_ALIGN_CENTER_VERTICAL_MIDDLE, true);
	Rect frameRect(UIScaleNum(34) + i_position.mX, UIScaleNum(60) + i_position.mY, UIScaleNum(70), UIScaleNum(70));
	Draw9SliceImage(i_graphics, Rect(frameRect), IMAGE_UI_ARTIFACT_ITEMBG);
	if (m_heroPlantImage)
		DrawAdaptiveImage(i_graphics, Rect(frameRect.mX + UIScaleNum(7), UIScaleNum(7) + frameRect.mY, frameRect.mWidth - UIScaleNum(14), frameRect.mHeight - UIScaleNum(14)), m_heroPlantImage);
	drawTranslatedWidget(i_graphics, m_unk228);
	drawTranslatedWidget(i_graphics, m_unk230);
}

void SeedChooser::drawFavoriteButton(Sexy::Graphics* i_graphics) const
{
	drawTranslatedWidget(i_graphics, m_buttonFavorite);
}

void SeedChooser::drawAccessoryButton(Sexy::Graphics* i_graphics) const
{
	drawTranslatedWidget(i_graphics, m_buttonArtifact);
}

bool SeedChooser::isPlantTypeATrialPlant(const PlantType* i_plantType) const
{
	int plantId = PlantNameMapperServerID::GetInstance().GetIdForName(i_plantType->TypeName);
	return TrialCardManager::GetInstancePtr()->IsTrialingPlant(plantId);
}

/////////////// Packets ///////////////

int SeedChooser::findImitaterChooserPacketIndex() const
{
	for (int i = 0; i < (int)m_chooserPackets.size(); i++)
	{
		if (m_chooserPackets[i].IsImitaterPacket)
			return i;
	}
	return -1;
}

void SeedChooser::onPlantAccessoryActionComplete()
{
	if (m_chooserPacketIndex < m_chooserPackets.size())
		setSeedPreview(m_chooserPackets[m_chooserPacketIndex]);
}

int SeedChooser::findPlantTypeChooserPacketIndex(const std::string& i_plantTypeName)
{
	for (int i = 0; i < (int)m_chooserPackets.size(); i++)
	{
		if (m_chooserPackets[i].AttachedSeedPacket.IsValid())
		{
			PlantTypePtr plantType = m_chooserPackets[i].AttachedSeedPacket->GetPlantType();
			if (plantType.IsValid() && plantType->TypeName == i_plantTypeName)
			{
				if (CustomLevelUtils::IsCustomLevel() && i_plantTypeName == "minigame_imitater")
				{
					ChooserPacketData& packet = m_chooserPackets[i];
					if (packet.State != 7)
						continue;
					packet.State = (PacketState)8;
				}
				return i;
			}
		}
	}
	return -1;
}

void SeedChooser::deleteChooserPackets()
{
	m_imitaterChooserPacketIdx = -1;
	for (int i = 0; i < (int)m_chooserPackets.size(); i++)
	{
		if (m_chooserPackets[i].AttachedSeedPacket)
			m_chooserPackets[i].AttachedSeedPacket->Destroy();
	}
	for (int i = 0; i < (int)m_bankPackets.size(); i++)
	{
		if (m_bankPackets[i].AttachedSeedPacket)
			m_bankPackets[i].AttachedSeedPacket->Destroy();
	}
	m_chooserPackets.clear();
	m_bankPackets.clear();
}

void SeedChooser::reindexBankPackets()
{
	ChooserPacketVector::iterator it = m_bankPackets.begin();
	ChooserPacketVector::iterator end = m_bankPackets.end();
	for (; it != end; ++it)
	{
		ChooserPacketData& packet = *it;
		if (packet.State != PS_Empty)
		{
			if (packet.AttachedSeedPacket.IsValid() && packet.AttachedSeedPacket->GetPlantType().IsValid())
			{
				PlantTypePtr plantType = packet.AttachedSeedPacket->GetPlantType();
				std::string plantTypeName = plantType->TypeName;
				if (packet.IsImitaterPacket)
					plantTypeName += "imitater";
				packet.SeedTypeIndex = findPlantTypeChooserPacketIndex(plantTypeName);
			}
		}
	}
}

void SeedChooser::updateImitaterChooserPacketState()
{
	int imitaterIndex = findImitaterChooserPacketIndex();
	if (imitaterIndex >= 0)
	{
		ChooserPacketData* packet = &m_chooserPackets[imitaterIndex];
		if (packet->State != PS_Purchasable)
		{
			PacketState state;
			bool disabled;
			bool canUse = m_chosenPacketCount != 0;
			for (int i = 0; i < m_chosenPacketCount; i++)
			{
				if (m_bankPackets[i].IsImitaterPacket)
					canUse = false;
			}
			if (canUse)
			{
				disabled = m_bankPackets[m_chosenPacketCount - 1].AttachedSeedPacket->GetPlantType().IsValid();
				packet = &m_chooserPackets[imitaterIndex];
				state = !disabled ? PS_InChooser : PS_Empty;
			}
			else
			{
				disabled = true;
				state = PS_Empty;
			}
			packet->State = state;
			packet->AttachedSeedPacket->SetDisabled(disabled);
		}
	}
}

/////////////// Favorites ///////////////

bool SeedChooser::isPlantTypeAFavorite(const PlantType* i_plantType) const
{
	std::vector<std::string>& favorites = LocalProfileSaveData::GetSeedChooserFavorites(ProfileMgr::GetInstance().GetCurrentProfile());
	return std::find(favorites.begin(), favorites.end(), i_plantType->TypeName) != favorites.end();
}

void SeedChooser::createAccessoryButton()
{
	Rect infoCardRect = calcInfoCardRect();
	((Image*)IMAGE_UI_CHOOSER_ACCESSORY_BUTTON)->GetWidth();
	int offsetX = UIScaleNum(10);
	int offsetY = UIScaleNum(12);
	int x = offsetX + infoCardRect.mX + UIScaleNum(50);
	int y = offsetY + infoCardRect.mY;
	PVZ2UIButton* button = new PVZ2UIButton(107, this, SexyString(L""), Color(Color::White));
	button->SetDialogStates(PVZ2UIImage(IMAGE_UI_CHOOSER_ACCESSORY_BUTTON, PVZ2UIIMAGE_SINGLE), PVZ2UIImage(IMAGE_UI_CHOOSER_ACCESSORY_BUTTON_PRESS, PVZ2UIIMAGE_SINGLE));
	button->SetContentsRect(Rect(0, 0, ((Image*)IMAGE_UI_CHOOSER_ACCESSORY_BUTTON)->GetWidth(), ((Image*)IMAGE_UI_CHOOSER_ACCESSORY_BUTTON)->GetHeight()));
	button->mX = x;
	button->mY = y;
	button->mWidth = ((Image*)IMAGE_UI_CHOOSER_ACCESSORY_BUTTON)->GetWidth();
	button->mHeight = ((Image*)IMAGE_UI_CHOOSER_ACCESSORY_BUTTON)->GetHeight();
	m_buttonArtifact = button;
}

void SeedChooser::initializeSeedPacket(SeedPacket* seedPacket, const PacketState i_packetState, const MagentoProductPropsPtr i_productProps, bool i_special)
{
	uint8 special = i_special;
	if (!seedPacket)
		return;

	seedPacket->SetParentWidget(this);
	seedPacket->SetInputPriority(-1);
	seedPacket->SetOnDisplay(true);
	seedPacket->SetManuallyDrawn(true);
	if (!special)
	{
		if (m_seedBankProps->GlobalLevel != -1)
		{
			if (seedPacket->GetPlantType())
			{
				PlantTypePtr plantType = seedPacket->GetPlantType();
				seedPacket->SetPlantAvatarAndLevel(std::min(plantType->GetProps()->MaxLevel, m_seedBankProps->GlobalLevel), -1);
			}
		}
	}
	if ((unsigned int)special < (unsigned int)RiftUtils::IsRiftTimedLevel())
	{
		if (seedPacket->GetPlantType())
			seedPacket->SetPlantAvatarAndLevel(1, -1);
	}

	m_chooserPackets.push_back(ChooserPacketData());
	ChooserPacketData& packetData = m_chooserPackets.back();
	memset(&packetData, 0, sizeof(ChooserPacketData));
	int index = (int)m_chooserPackets.size() - 1;
	OutputDebugStrF("change list id : initializeSeedPacket index= %d", index);
	packetData.AttachedSeedPacket = seedPacket->GetPtr();
	if (special)
	{
		calcPacketPositionInChooser(index, packetData.Position);
		packetData.SeedTypeIndex = index;
		float time = PVZ_EOT();
		packetData.SeedBankIndex = 0;
		packetData.MovePositionStart = packetData.Position;
		packetData.MovePositionEnd = packetData.Position;
		packetData.IsImitaterPacket = false;
		packetData.State = i_packetState;
		packetData.MovingStartTime = time;
		packetData.MovingEndTime = time;
		packetData.ProductProps = i_productProps;
	}
	else
	{
		packetData.AttachedSeedPacket->setIsNeedShowExpTip(true);
		calcPacketPositionInChooser(index, packetData.Position);
		packetData.SeedTypeIndex = index;
		float time = PVZ_EOT();
		packetData.MovePositionStart = packetData.Position;
		packetData.MovePositionEnd = packetData.Position;
		packetData.SeedBankIndex = 0;
		packetData.IsImitaterPacket = false;
		packetData.MovingStartTime = time;
		packetData.MovingEndTime = time;
		ObjectTypeDescriptorPtr seedType = seedPacket->GetSeedType();
		packetData.State = isBlacklisted(seedType->TypeName) ? PS_Blacklisted : i_packetState;
		packetData.ProductProps = i_productProps;
		if (packetData.State != PS_NotEnough && packetData.State != PS_Blacklisted)
			m_requiredSelections++;
		PlantTypePtr plantType = seedPacket->GetPlantType();
		seedPacket->SetFavorite(isPlantTypeAFavorite(plantType.operator->()));
		if (plantType.IsValid() && plantType->TypeName == "imitater")
		{
			m_imitaterChooserPacketIdx = index;
			if (packetData.State != PS_Blacklisted && packetData.State != PS_Purchasable)
				packetData.State = PS_Empty;
			packetData.IsImitaterPacket = true;
		}
	}
}

void SeedChooser::updateFavoriteButton()
{
	if (m_buttonFavorite)
	{
		if (isCurrentPlantFavorite())
			m_buttonFavorite->SetDialogStates(PVZ2UIImage(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_REMOVE, PVZ2UIIMAGE_SINGLE), PVZ2UIImage(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_REMOVE_PRESS, PVZ2UIIMAGE_SINGLE));
		else
			m_buttonFavorite->SetDialogStates(PVZ2UIImage(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD, PVZ2UIIMAGE_SINGLE), PVZ2UIImage(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD_PRESS, PVZ2UIIMAGE_SINGLE));
	}
}

void SeedChooser::createFavoriteButton()
{
	Rect infoCardRect = calcInfoCardRect();
	((Image*)IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD)->GetWidth();
	int offsetX = UIScaleNum(10);
	int offsetY = UIScaleNum(12);
	int x = offsetX + infoCardRect.mX;
	int y = offsetY + infoCardRect.mY;
	PVZ2UIButton* button = new PVZ2UIButton(107, this, SexyString(L""), Color(Color::White));
	button->SetDialogStates(PVZ2UIImage(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD, PVZ2UIIMAGE_SINGLE), PVZ2UIImage(IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD_PRESS, PVZ2UIIMAGE_SINGLE));
	button->SetContentsRect(Rect(0, 0, ((Image*)IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD)->GetWidth(), ((Image*)IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD)->GetHeight()));
	button->mX = x;
	button->mY = y;
	button->mWidth = ((Image*)IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD)->GetWidth();
	button->mHeight = ((Image*)IMAGE_UI_CHOOSER_FAVORITES_BUTTON_ADD)->GetHeight();
	m_buttonFavorite = button;
	updateFavoriteButton();
}

void SeedChooser::togglePlantFavorite()
{
	const PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
	if (!m_selectedPacket)
		return;
	{
		if (__builtin_expect(!!(!(m_selectedPacket->IsA<SeedPacket_ToolRift>())), 1))
		{
			std::string typeName = m_selectedPacket->GetPlantType()->TypeName;
			bool isFavorite = isCurrentPlantFavorite();
			if (__builtin_expect(isFavorite, 0))
				LocalProfileSaveData::RemoveSeedChooserFavorite(playerInfo, typeName);
			else
				LocalProfileSaveData::AddSeedChooserFavorite(playerInfo, typeName);

			int index = findPlantTypeChooserPacketIndex(typeName);
			if (index != -1)
			{
				SeedPacketPtr packet = m_chooserPackets[index].AttachedSeedPacket;
				packet->SetFavorite(!isFavorite);
			}

			updateFavoriteButton();
			updateFavoriteSorting();
		}
	}
}

bool SeedChooser::isPlantTypeAPvZ1Plant(const PlantType* i_plantType) const
{
	std::vector<std::string> plantList;
	PVZ1ModeUtils::GetPvZ1PlantList(plantList);
	return std::find(plantList.begin(), plantList.end(), i_plantType->TypeName) != plantList.end();
}

/////////////// Widgets ///////////////

void SeedChooser::drawTranslatedWidget(Sexy::Graphics* i_graphics, Widget* i_widget) const
{
	if (i_widget)
	{
		GraphicsAutoState autoState(i_graphics);
		i_graphics->Translate(i_widget->mX, i_widget->mY);
		i_widget->Draw(i_graphics);
	}
}

void SeedChooser::CloseSeedChooserArtifactSelectWidget()
{
	if (m_artifactWidget)
	{
		gLawnApp->mWidgetManager->RemoveWidget(m_artifactWidget);
		gLawnApp->mWidgetManager->RemoveBaseModal(m_artifactWidget);
		gLawnApp->SafeDeleteWidget(m_artifactWidget);
		m_artifactWidget = nullptr;
	}
}

void SeedChooser::CloseSeedChooserHeroPlantSelectWidget()
{
	if (m_heroPlantWidget)
	{
		gLawnApp->mWidgetManager->RemoveWidget(m_heroPlantWidget);
		gLawnApp->mWidgetManager->RemoveBaseModal(m_heroPlantWidget);
		gLawnApp->SafeDeleteWidget(m_heroPlantWidget);
		m_heroPlantWidget = nullptr;
	}
}

void SeedChooser::ShowSeedChooserArtifactSelectWidget()
{
	if (m_artifactWidget)
		return;

	m_artifactWidget = new SeedChooserArtifactSelectWidget();
	m_artifactWidget->SetSeedChooser(this);
	m_artifactWidget->InitView();
	gLawnApp->mWidgetManager->AddWidget(m_artifactWidget);
	gLawnApp->mWidgetManager->BringToFront(m_artifactWidget);
	gLawnApp->PushOverlaysToTop();
	gLawnApp->mWidgetManager->AddBaseModal(m_artifactWidget);
	gLawnApp->mWidgetManager->SetFocus(m_artifactWidget);
}

void SeedChooser::ShowSeedChooserHeroPlantSelectWidget()
{
	if (m_heroPlantWidget)
		return;

	m_heroPlantWidget = new SeedChooserHeroPlantSelectWidget();
	m_heroPlantWidget->SetSeedChooser(this);
	m_heroPlantWidget->InitView();
	gLawnApp->mWidgetManager->AddWidget(m_heroPlantWidget);
	gLawnApp->mWidgetManager->BringToFront(m_heroPlantWidget);
	gLawnApp->PushOverlaysToTop();
	gLawnApp->mWidgetManager->AddBaseModal(m_heroPlantWidget);
	gLawnApp->mWidgetManager->SetFocus(m_heroPlantWidget);
}

Rect SeedChooser::calcInfoCardRect()
{
	Rect rect;
	rect = m_tabFrameRect;
	rect.mX = UIScaleNum(18.0f) + rect.mX;
	rect.mY = UIScaleNum(15.0f) + rect.mY;
	rect.mWidth = rect.mWidth - UIScaleNum(36.0f);
	rect.mHeight = UIScaleNum(188);
	return rect;
}

/////////////// Panning ///////////////

void SeedChooser::panBoardLeft()
{
	SlideOut();
	Board* board = gLawnApp->m_board;
	board->PushAnimationMgr();
	AnimationMgr* animationMgr = board->m_animationMgr;
	animationMgr->ResetTime();
	pvztime_t time = animationMgr->GetTime();
	int posStart, posEnd;
	StandardLevelIntro::GetPanLocations(StandardLevelIntro::PAN_ZOMBIES_TO_GAME_START, posStart, posEnd);
	pvztime_t endTime;
	animationMgr->Add(MoveBoard::Create(1.5f, posStart, posEnd, 0, 0, CURVE_EASE_IN_OUT), time + 0.2f, endTime);
	animationMgr->Add(TimeEvent::Create(GetPtr(), "onPanBoardLeftFinished"), endTime);
	UIWidget::GetWidgetBySheetName("UIViewBoardOrZombies")->SetClickable(false);
}

void SeedChooser::panBoardRight()
{
	Board* board = gLawnApp->m_board;
	board->PushAnimationMgr();
	AnimationMgr* animationMgr = board->m_animationMgr;
	animationMgr->ResetTime();
	pvztime_t time = animationMgr->GetTime();
	int posStart, posEnd;
	StandardLevelIntro::GetPanLocations(StandardLevelIntro::PAN_GAME_START_TO_ZOMBIES, posStart, posEnd);
	pvztime_t endTime;
	animationMgr->Add(MoveBoard::Create(1.5f, posStart, posEnd, 0, 0, CURVE_EASE_IN_OUT), time + 0.2f, endTime);
	animationMgr->Add(TimeEvent::Create(GetPtr(), "onPanBoardRightFinished"), endTime);
	UIWidget::GetWidgetBySheetName("UIViewBoardOrZombies")->SetClickable(false);
}

void SeedChooser::onPanBoardLeftFinished()
{
	gLawnApp->m_board->PopAnimationMgr();
	UIWidget::GetWidgetBySheetName("UIViewBoardOrZombies")->SetClickable(true);
}

void SeedChooser::toggleHideChooser()
{
	UIWidget::GetWidgetBySheetName("UIViewBoardOrZombies")->SetClickable(false);
	m_toolTip->m_visible = false;
	if (IsVisible())
		panBoardLeft();
	else
		panBoardRight();
}

/////////////// Purchases ///////////////

void SeedChooser::OnServerGemCallBack(bool i_Success)
{
	if (i_Success)
	{
		gMessageRouter->Post(Message::PlantUnlockFragment, m_purchaseProps, 0);
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		gMessageRouter->Post(Message::ItemPurchaseInfo2, m_purchaseProps, "PvE_Mission|" + playerInfo->GetCurrentLevel(), 0);
		playerInfo->HandlePurchase(m_purchaseProps->Sku, std::vector<PaymentBundleInfo>());
	}
}

/////////////// Borrow ///////////////

void SeedChooser::sendBorrowRequestBeforeFinalize()
{
	if (m_BorrowFriendUserId == -1)
	{
		finalizeSelection();
		return;
	}
	if (m_bIsLoading)
		return;
	m_bIsLoading = true;
	gLawnApp->m_busyManager->StartBusyIcon();
}

void SeedChooser::OnGameStartAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason)
{
	DString level(ProfileMgr::GetInstance().GetCurrentProfile()->GetCurrentLevel());
	if (i_reason == EASquaredAdFinishedReason::Completed)
		TGALogMgr::GetInstance().LogAD("2", level.c_str(), 2, "", "");
	else
		TGALogMgr::GetInstance().LogAD("4", level.c_str(), 2, "", "");
}

void SeedChooser::onItemPurchasedFromStore(MagentoProductProps* i_props)
{
	for (int i = 0; i < m_chooserPackets.size(); i++)
	{
		if (i_props == (MagentoProductProps*)m_chooserPackets[i].ProductProps)
		{
			ChooserPacketData& packet = m_chooserPackets[i];
			packet.State = PS_InChooser;
			packet.ProductProps = MagentoProductPropsPtr(nullptr);
			m_purchaseProps = MagentoProductPropsPtr(nullptr);
			m_chooserPackets[i].AttachedSeedPacket->SetPurchasable(false);
			if (m_chosenPacketCount == 0 && m_chooserPackets[i].IsImitaterPacket)
				m_chooserPackets[i].State = PS_Empty;
			gAudioMgr->SendEvent("Play_UI_Menu_Buy_Plant_Confirm");
			setSeedPreview(m_chooserPackets[i]);
			return;
		}
	}
}

void SeedChooser::onMsgBorrowFriendPlant(int32 i_userid)
{
	if (m_bIsLoading)
	{
		m_bIsLoading = false;
		gLawnApp->m_busyManager->StopBusyIcon();
	}
	if (i_userid > 0)
	{
		SocialMgr::GetInstance().GetSocialInfo()->AddBorrowedPlantList(i_userid);
		if (m_BorrowPlantId > 0)
			gLawnApp->m_board->m_FriendPlantName = PlantNameMapper::GetInstance().GetNameForId(m_BorrowPlantId);
		finalizeSelection();
	}
	else
	{
		m_BorrowFriendUserId = -1;
		m_BorrowPlantId = 0;
		gLawnApp->m_board->m_FriendPlantName = "";
		m_BorrowButtonIndex = -1;
	}
}

void SeedChooser::onMsgError(int i_errorId)
{
	if (m_bIsLoading)
	{
		m_bIsLoading = false;
		gLawnApp->m_busyManager->StopBusyIcon();
	}
	m_BorrowPlantId = 0;
	m_BorrowFriendUserId = -1;
}

/////////////// Selection ///////////////

void SeedChooser::AutoSelectSeedsAndFinalize()
{
	for (int i = 0; i < (int)m_chooserPackets.size(); i++)
	{
		if (m_chosenPacketCount == m_requiredSelections)
			break;
		ChooserPacketData& packet = m_chooserPackets[i];
		if (packet.State == PS_Blacklisted || packet.State == PS_NotEnough || packet.State != PS_InChooser)
		{
			setSeedPreview(packet);
		}
		else
		{
			m_chooserPacketIndex = i;
			startMovingPacket(packet);
		}
	}
	sendBorrowRequestBeforeFinalize();
}

void SeedChooser::onSlideOutFinished()
{
	if (gLawnApp->m_board->GetSeedBank()->IsVisible())
	{
		gLawnApp->m_board->OnSeedChooserDone();
		UIWidget* powerupHolder = UIWidget::GetWidgetBySheetName("UIPowerupHolder");
		if (powerupHolder)
			powerupHolder->ClearPositionOffsetOverride();
	}
}

void SeedChooser::initLoadingResourcesGroupList()
{
	addToLoadingResourcesGroupList("UI_SeedChooser");
	addToLoadingResourcesGroupList("UI_Card_Plant_BG");
}

void SeedChooser::touchAccessoryButton()
{
	if (!m_selectedPacket)
		return;
	if (!m_selectedPacket->IsA<SeedPacket_ToolRift>())
	{
		std::string plantName = m_selectedPacket->GetPlantType()->TypeName;
		UINewPlantView_AccessoryPackage::ShowDialog()->InitView(plantName);
	}
}

void SeedChooser::showBuyPlantUI()
{
	UISpringBuyPlant* dialog = UISpringBuyPlant::ShowDialog();
	if (m_selectedPacket)
	{
		if (!m_selectedPacket->IsA<SeedPacket_ToolRift>())
		{
			int plantId = PlantNameMapperServerID::GetInstance().GetIdForType(m_selectedPacket->GetPlantType());
			dialog->setPlantID(plantId);
			dialog->initUI();
		}
	}
}

bool SeedChooser::isCurPlantAlreadyBuy()
{
	bool result = false;
	if (m_selectedPacket)
	{
		if (__builtin_expect(!!(!m_selectedPacket->IsA<SeedPacket_ToolRift>()), 1))
		{
			PlantTypePtr plantType = m_selectedPacket->GetPlantType();
			int plantId = PlantNameMapperServerID::GetInstance().GetIdForType(plantType);
			result = SpringChargeManager::GetInstancePtr()->isPlantAlreadyBuy(plantId);
		}
	}
	return result;
}

bool SeedChooser::isCurPlantExp()
{
	bool result = false;
	if (m_selectedPacket)
	{
		if (__builtin_expect(!!(!m_selectedPacket->IsA<SeedPacket_ToolRift>()), 1))
		{
			PlantTypePtr plantType = m_selectedPacket->GetPlantType();
			int plantId = PlantNameMapperServerID::GetInstance().GetIdForType(plantType);
			result = ProfileMgr::GetInstance().GetCurrentProfile()->getIsExperiencePlantById(plantId);
		}
	}
	return result;
}

void SeedChooser::refreshCurrentHeroPlant()
{
	int heroPlantId = HeroPlantUtils::GetCurrentHeroPlant();
	if (PlantNameMapperServerID::GetInstance().ContainsId(heroPlantId))
	{
		m_heroPlantImage = StringHelper::ToImage("IMAGE_UI_HEROPLANT_BUTTON_" + StringToUpper(PlantNameMapperServerID::GetInstance().GetNameForId(heroPlantId)), false);
	}
}

void SeedChooser::addToolToChooserPackets(const std::string& i_typeName)
{
	SeedPacket_Tool* toolPacket = UIWidget::CreateWidget(m_specialSeedPacketType, true)->CastChecked<SeedPacket_Tool>();
	toolPacket->SetToolType(i_typeName);
	toolPacket->SetAlwaysPlantable(false);
	toolPacket->SetVisible(false);
	initializeSeedPacket(toolPacket, PS_InChooser, MagentoProductPropsPtr(nullptr), true);
}

/////////////// Layout ///////////////

void SeedChooser::calcPacketPositionInBank(const int i_index, SexyVector2& io_position)
{
	SeedPacketPtr packet = gLawnApp->m_board->GetSeedBank()->GetPacket(i_index);
	Rect rect = packet->GetDrawRect();
	io_position.x = (float)rect.mX;
	io_position.y = (float)rect.mY;
	if (gLawnApp->IsFullScreen())
	{
		if (gLawnApp->GetUIOrientation() == gLawnApp->FullScreenUIOrientationLeft())
			io_position.x -= (float)gLawnApp->CalcFullScreenOffset();
	}
}

void SeedChooser::calcPacketPositionInChooser(const int i_index, SexyVector2& io_position)
{
	int packetWidth = m_chooserPackets[0].AttachedSeedPacket->GetWidth();
	int packetHeight = m_chooserPackets[0].AttachedSeedPacket->GetHeight();
	int spacing = (m_seedPacketArea.mWidth - packetWidth * sChooserColumns) / (sChooserColumns + 1);
	int index = i_index;
	if (PVZ1ModeUtils::IsPlayingPVZ1Level() && index >= m_pvz1Segmentation)
		index = (sChooserColumns - m_pvz1Segmentation % sChooserColumns) % sChooserColumns + i_index;
	int row = index / sChooserColumns;
	int column = index % sChooserColumns;
	io_position.y = (float)(spacing + (packetHeight + spacing) * row);
	io_position.x = (float)(spacing + (packetWidth + spacing) * column + sChooserOffsetX);
	if (PVZ1ModeUtils::IsPlayingPVZ1Level() && i_index >= m_pvz1Segmentation)
		io_position.y += (float)packetHeight * (1.0f / 3.0f);
}

PlantTypeList SeedChooser::createSortedPlantList()
{
	ProfileMgr::GetInstance().GetCurrentProfile();
	PlantTypeList plantList;
	bool favoritesEnabled = isFavoritesFeatureToggleEnabled();
	bool isPvZ1Level = PVZ1ModeUtils::IsPlayingPVZ1Level();
	for (ObjectTypeDirectoryIterator<PlantType> it; it; ++it)
	{
		PlantTypePtr plantType = *it;
		plantType.operator->();
		plantList.Add(plantType);
	}
	if (favoritesEnabled)
		MoveMatchesToFront(plantList, [this](PlantTypePtr i_plantType) { return isPlantTypeAFavorite(i_plantType.Get()); });
	MoveMatchesToFront(plantList, [](PlantTypePtr i_plantType) { return TrialCardManager::GetInstancePtr()->IsTrialingPlant(PlantNameMapperServerID::GetInstance().GetIdForName(i_plantType->TypeName)); });
	if (isPvZ1Level)
		MoveMatchesToFront(plantList, [this](PlantTypePtr i_plantType) { return isPlantTypeAPvZ1Plant(i_plantType.Get()); });
	return plantList;
}

void SeedChooser::refreshCurrentArtifact()
{
	PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
	int artifactId = playerInfo->GetCurrentArtifact();
	if (ArtifactMapper::GetInstance().ContainsId(artifactId))
	{
		ArtifactInfo info = playerInfo->GetArtifactInfoByID(artifactId);
		std::string artifactName = ArtifactMapper::GetInstance().GetNameForId(info.ArtifactID);
		m_artifactImage = StringHelper::ToImage("IMAGE_UI_ARTIFACT_" + Sexy::StringToUpper(artifactName));
		m_artifactLevel = info.Level;
		m_artifactRank = info.Rank;
	}
	else
	{
		m_artifactLevel = 0;
		m_artifactRank = 0;
		m_artifactImage = NULL;
	}
	if (playerInfo->GetActiveTutorial() == TUTORIAL_ARTIFACT)
	{
		m_artifactImage = StringHelper::ToImage("IMAGE_UI_ARTIFACT_ARTIFACT_WIND");
		m_artifactLevel = 30;
		m_artifactRank = 4;
	}
	if (playerInfo->GetCurrentLevel().find("Artifact_Demo_", 0) != std::string::npos)
	{
		m_artifactImage = StringHelper::ToImage("IMAGE_UI_ARTIFACT_ARTIFACT_" + Sexy::StringToUpper(playerInfo->GetCurrentLevel().substr(14)));
		m_artifactLevel = 30;
		m_artifactRank = 4;
	}
}

void SeedChooser::finalizeSelection()
{
	SeedBankNew* seedBank = gLawnApp->m_board->GetSeedBank();
	seedBank->SetNumPackets(m_requiredSelections, true);
	std::vector<int> plantIds;
	PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
	for (int i = 0; i < seedBank->GetPacketCount(); i++)
	{
		SeedPacketPtr packet = seedBank->GetPacket(i);
		SeedPacket* packetPtr = packet.operator->();
		if (!packetPtr || !packetPtr->Cast<SeedPacket_ToolRift>())
		{
			packet->setIsNeedShowExpTip(true);
			PlantTypePtr plantType = m_chooserPackets[m_bankPackets[i].SeedTypeIndex].AttachedSeedPacket->GetPlantType();
			int level = m_chooserPackets[m_bankPackets[i].SeedTypeIndex].AttachedSeedPacket->GetPlantLevel();
			if (m_bankPackets[i].IsImitaterPacket)
			{
				packet->SetIsImitater(true);
				packet->SetPlantType(m_bankPackets[i].AttachedSeedPacket->GetPlantType());
			}
			else if (m_bankPackets[i].SeedTypeIndex >= 0)
				packet->SetPlantType(plantType);
			packet->SetPlantAvatarAndLevel(level, -1);
			int plantId = PlantNameMapper::GetInstance().GetIdForName(plantType->TypeName);
			plantIds.push_back(plantId);
		}
		else
		{
			SeedPacket_Tool* tool = (SeedPacket_Tool*)PacketPassThrough(packetPtr);
			tool->SetToolType(m_bankPackets[i].AttachedSeedPacket->GetContentsTypeName());
			tool->SetAlwaysPlantable(false);
		}
	}
	playerInfo->SetBattleArrayRecord(m_battleArrayType, plantIds);
	SlideOut();
	seedBank->SetVisible(true);
	UIWidget::GetWidgetBySheetName("UIViewBoardOrZombies")->SetVisible(false);
	gMessageRouter->Broadcast(Message::SeedChooserSelectionFinalized);
}

void SeedChooser::VerifyAndSelectSeeds()
{
	std::vector<PlantTypePtr> seedList;
	int nonPvZ1Count = 0;
	for (int i = 0; i < m_requiredSelections; i++)
	{
		seedList.push_back(m_bankPackets[i].AttachedSeedPacket->GetPlantType());
		if (PVZ1ModeUtils::IsPlayingPVZ1Level())
		{
			if (!isPlantTypeAPvZ1Plant(m_bankPackets[i].AttachedSeedPacket->GetPlantType()))
				nonPvZ1Count++;
		}
	}
	if (PVZ1ModeUtils::IsPlayingPVZ1Level() && PVZ1ModeUtils::IsHardMode() && nonPvZ1Count > 2)
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(500), UIScaleNum(240));
		dialog->SetHeaderLabel(TodStringTranslate(L"[SEED_CHOOSER_WARNING_TITLE]"));
		dialog->SetFooterLabel(TodStringTranslate(L"[PVZ1MODE_HARDMODE_SELECT_PLANT_TIPS]"));
		dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &SeedChooser::onRepickButtonPressed)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
		dialog->SetBackgroundDarken(true, 0.5f);
		return;
	}
	SexyString warnings = gLawnApp->m_board->GetSeedChooserWarnings(seedList);
	bool noWarnings = warnings.empty();
	if (!noWarnings)
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(500), UIScaleNum(240));
		dialog->SetHeaderLabel(TodStringTranslate(L"[SEED_CHOOSER_WARNING_TITLE]"));
		dialog->SetFooterLabel(warnings);
		dialog->AddButton(SexyString(L"[REPICK_BUTTON]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &SeedChooser::onRepickButtonPressed)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
		dialog->AddButton(SexyString(L"[START_GAME_BUTTON]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &SeedChooser::onPlayButtonPressed)), (PVZ2UIDialog::DialogButtonType)noWarnings);
		dialog->SetBackgroundDarken(true, 0.5f);
	}
	else
		sendBorrowRequestBeforeFinalize();
}

void SeedChooser::OnOrientationChanged()
{
	int offset = 0;
	if (gLawnApp->IsFullScreen())
		offset = gLawnApp->CalcFullScreenOffset();
	if (m_buttonReady)
	{
		if (gLawnApp->GetUIOrientation() == gLawnApp->FullScreenUIOrientationLeft())
			m_buttonReady->Resize(m_buttonReady->mX + offset, m_buttonReady->mY, m_buttonReady->mWidth, m_buttonReady->mHeight);
		else if (gLawnApp->GetUIOrientation() == gLawnApp->FullScreenUIOrientationRight())
			m_buttonReady->Resize(m_buttonReady->mX - offset, m_buttonReady->mY, m_buttonReady->mWidth, m_buttonReady->mHeight);
	}
}

bool SeedChooser::IsMouseOver(const int i_mouseX, const int i_mouseY)
{
	if (!UIWidget::IsMouseOver(i_mouseX, i_mouseY))
		return false;

	UIWidget* viewButton = UIWidget::GetWidgetBySheetName("UIViewBoardOrZombies");
	if (viewButton->IsVisible() && viewButton->IsMouseOver(i_mouseX, i_mouseY))
		return false;

	Rect rect = GetDrawRect();
	rect.mY += m_tabFrameRect.mY;
	return rect.Contains(i_mouseX, i_mouseY);
}

/////////////// Properties ///////////////

void SeedChooser::SetSeedBankProperties(const SeedBankProperties* i_propertySheet)
{
	m_seedBankProps = i_propertySheet;
	if (m_seedBankProps && !m_seedBankProps->SeedPacketType.empty())
	{
		RtName seedPacketType(StringToWString(m_seedBankProps->SeedPacketType));
		SetSeedPacketType(seedPacketType);
		RtName specialSeedPacketType(StringToWString(m_seedBankProps->SpecialSeedPacketType));
		SetSpecialSeedPacketType(specialSeedPacketType);
	}
}

void SeedChooser::getBattleArrayType()
{
	std::string levelName = gLawnApp->m_board->GetLevel();
	if (levelName.find("festival_lv1") != std::string::npos)
		m_battleArrayType = BattleArrayType_GargantuarCrisis;
	else if (levelName.find("festival_lv2") != std::string::npos)
		m_battleArrayType = BattleArrayType_CrazyYeti;
	else if (levelName.find("festival_lv3") != std::string::npos)
		m_battleArrayType = BattleArrayType_DevilInvade;
	else
		m_battleArrayType = BattleArrayType_Normal;
}

void SeedChooser::setPlantPreview(PlantTypePtr i_plantTypePtr)
{
	ChooserPacketVector::iterator it = m_chooserPackets.begin();
	ChooserPacketVector::iterator end = m_chooserPackets.end();
	for (; it != end; ++it)
	{
		ChooserPacketData& packet = *it;
		if (packet.AttachedSeedPacket->GetPlantType() == i_plantTypePtr)
		{
			setSeedPreview(packet);
			return;
		}
	}
}

bool SeedChooser::isCurrentPlantFavorite() const
{
	std::vector<std::string>& favorites = LocalProfileSaveData::GetSeedChooserFavorites(ProfileMgr::GetInstance().GetCurrentProfile());
	if (!m_selectedPacket)
		return false;
	if (__builtin_expect(!!(!(m_selectedPacket->IsA<SeedPacket_ToolRift>())), 1))
		return std::find(favorites.begin(), favorites.end(), m_selectedPacket->GetPlantType()->TypeName) != favorites.end();
	return false;
}

/////////////// Artifacts and hero plants ///////////////

void SeedChooser::toggleSelectArtifact()
{
	std::vector<ArtifactInfo> artifactList = ProfileMgr::GetInstance().GetCurrentProfile()->GetUnlockedArtifactList();
	if (!artifactList.empty())
	{
		ShowSeedChooserArtifactSelectWidget();
	}
	else
	{
		UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
		if (box)
		{
			box->SetShowType(UIMessageBox::Type_ShowCancel);
			SexyString title = TodStringTranslate(L"[REVIVE_TIP]");
			SexyString message = TodStringTranslate(L"[ARTIFACT_NO_ARTIFACT]");
			SexyString ok = TodStringTranslate(L"[BUTTON_OK]");
			box->SetMessage(message, title);
			box->SetBackground(StringHelper::ToImage("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_GREEN", false));
			box->GetButtonCancel()->mLabel = ok;
		}
	}
}

void SeedChooser::ShowArtifactDetails()
{
	int artifactId = ProfileMgr::GetInstance().GetCurrentProfile()->GetCurrentArtifact();
	if (!(!ArtifactMapper::GetInstance().ContainsId(artifactId)))
	{
		UISingletonDialog<UIArtifactBoostDetails>::ShowDialog()->InitView(artifactId);
	}
	else
	{
		UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
		if (box)
		{
			box->SetShowType(UIMessageBox::Type_ShowCancel);
			SexyString title = TodStringTranslate(L"[REVIVE_TIP]");
			SexyString message = TodStringTranslate(L"[ARTIFACT_NO_DETAILS]");
			SexyString ok = TodStringTranslate(L"[BUTTON_OK]");
			box->SetMessage(message, title);
			box->SetBackground(StringHelper::ToImage("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_GREEN", false));
			box->GetButtonCancel()->mLabel = ok;
		}
	}
}

void SeedChooser::toggleSelectHeroPlant()
{
	std::vector<int> heroPlantList = HeroPlantUtils::GetPlayerHeroPlantList();
	if (!heroPlantList.empty())
	{
		ShowSeedChooserHeroPlantSelectWidget();
	}
	else
	{
		UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
		if (box)
		{
			box->SetShowType(UIMessageBox::Type_ShowCancel);
			SexyString title = TodStringTranslate(L"[REVIVE_TIP]");
			SexyString message = TodStringTranslate(L"[HEROPLANT_NO_HEROPLANT]");
			SexyString ok = TodStringTranslate(L"[BUTTON_OK]");
			box->SetMessage(message, title);
			box->SetBackground(StringHelper::ToImage("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_GREEN", false));
			box->GetButtonCancel()->mLabel = ok;
		}
	}
}

void SeedChooser::ShowHeroPlantDetails()
{
	int heroPlantId = HeroPlantUtils::GetCurrentHeroPlant();
	if (!PlantNameMapperServerID::GetInstance().ContainsId(heroPlantId))
	{
		UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
		if (box)
		{
			box->SetShowType(UIMessageBox::Type_ShowCancel);
			SexyString title = TodStringTranslate(L"[REVIVE_TIP]");
			SexyString message = TodStringTranslate(L"[HEROPLANT_NO_DETAILS]");
			SexyString ok = TodStringTranslate(L"[BUTTON_OK]");
			box->SetMessage(message, title);
			box->SetBackground(StringHelper::ToImage("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_GREEN", false));
			box->GetButtonCancel()->mLabel = ok;
		}
	}
}

/////////////// Selection queries ///////////////

void SeedChooser::GetSelectedPlantTypes(std::vector<PlantTypePtr>& o_plantTypes)
{
	o_plantTypes.clear();
	ChooserPacketVector::iterator it = m_bankPackets.begin();
	ChooserPacketVector::iterator end = m_bankPackets.end();
	for (; it != end; ++it)
	{
		ChooserPacketData packet = *it;
		if (packet.AttachedSeedPacket && (packet.State == PS_Moving || packet.State == PS_InBank))
		{
			PlantTypePtr plantType;
			if (packet.IsImitaterPacket)
			{
				plantType = gPlantTypeMgr->GetTypeFromTypeName("imitater");
				if (plantType.IsValid())
					o_plantTypes.push_back(plantType);
			}
			else
			{
				plantType = packet.AttachedSeedPacket->GetPlantType();
				if (plantType.IsValid())
					o_plantTypes.push_back(plantType);
			}
		}
	}
}

void SeedChooser::OverrideValidPlants(const std::vector<int>& i_plantTypeIds)
{
	deleteChooserPackets();
	m_requiredSelections = 0;
	for (PlantTypeIter it; it; ++it)
	{
		PlantTypePtr plantTypePtr = *it;
		const PlantType* plantType = plantTypePtr;
		if (plantType == NULL || !plantType->Enabled)
			continue;
		int plantId = PlantNameMapper::GetInstance().GetIdForName(plantType->TypeName);
		for (size_t i = 0; i < i_plantTypeIds.size(); i++)
		{
			if (plantId == i_plantTypeIds[i])
			{
				SeedPacket* seedPacket = UIWidget::CreateWidget(m_seedPacketType, true)->CastChecked<SeedPacket>();
				seedPacket->SetPlantType(plantTypePtr);
				initializeSeedPacket(seedPacket, PS_InChooser, MagentoProductPropsPtr(), false);
				break;
			}
		}
	}
	initChooserPackets();
	m_chooserPacketIndex = 0;
	setSeedPreview(m_chooserPackets[0]);
}

void SeedChooser::ForceSelection(const std::string& i_type)
{
	for (size_t i = 0; i < m_chooserPackets.size(); i++)
	{
		if (m_chooserPackets[i].AttachedSeedPacket)
		{
			if (m_chooserPackets[i].AttachedSeedPacket->GetContentsTypeName() == i_type)
			{
				if (!CustomLevelUtils::IsCustomLevel() || !(i_type == "minigame_imitater"))
				{
					startMovingPacket(m_chooserPackets[i]);
					return;
				}
				ChooserPacketData& packet = m_chooserPackets[i];
				if (packet.State == 8)
				{
					packet.State = (PacketState)0;
					startMovingPacket(packet);
					return;
				}
			}
		}
	}
	for (size_t i = 0; i < m_bankPackets.size(); i++)
	{
		if (m_bankPackets[i].AttachedSeedPacket)
		{
			if (m_bankPackets[i].AttachedSeedPacket->GetContentsTypeName() == i_type)
			{
				startMovingPacket(m_bankPackets[i]);
				return;
			}
		}
	}
}
