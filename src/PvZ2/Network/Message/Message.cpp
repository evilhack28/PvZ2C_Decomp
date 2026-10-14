//
//  Message.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-06.
//

#include "Message.h"

/////////////// Message ///////////////

void Message::MsgError(int)
{
}

void Message::MsgErrorRequest(int, std::string const&)
{
}

void Message::ServerMsgError(std::string const&)
{
}

void Message::SyncPlayerInfoFinish(bool)
{
}

void Message::SyncPlantFinish(bool)
{
}

void Message::SyncAvatarFinish(bool)
{
}

void Message::UseGemFinish(bool)
{
}

void Message::BuyItemFinish(MsgResultInfo*, S2C_ICloud_GetConsumeGemInfo const*, S2C_PlayerInfo const*)
{
}

void Message::ProcessSignRewardResult(S2C_ICloud_DailySignInfo const*)
{
}

void Message::ChangePlantSuccess(std::string const&)
{
}

void Message::ChangeAvatarSuccess(std::string const&)
{
}

void Message::PlantLevelUpSuccess()
{
}

void Message::CompeleteTodayLanternRiddles(S2C_LanternRiddlesResult const&)
{
}

void Message::Verify2015NewTearCharge(bool)
{
}

void Message::GLLotteryResult(bool)
{
}

void Message::StoneLotteryReward(S2C_StoneLotteryReward const&)
{
}

void Message::GLDeliverySend(bool)
{
}

void Message::GL7DaysLoginReward(bool, S2C_7DaysLoginReward const*)
{
}

void Message::GL7DaysLoginSpringReward(bool, S2C_7DaysLoginSpringReward const*)
{
}

void Message::GLBuyPlantID(bool, int)
{
}

void Message::GLWorldCupBeginGame(bool)
{
}

void Message::GLBuyWorldCupTicket(bool)
{
}

void Message::GLUnlockWorldCupTeam(bool)
{
}

void Message::GLBuyZMatchTicket(bool)
{
}

void Message::CRChargeRewardPlantID(bool)
{
}

void Message::TGResultGot(bool)
{
}

void Message::SavePVPPlayerInfo(bool, int)
{
}

void Message::GetPVPPlayerInfo(bool, int)
{
}

void Message::PVPBattleEnding(bool, int)
{
}

void Message::EditPlayerPlant(bool, int)
{
}

void Message::BattleStart(bool, int)
{
}

void Message::ApplyData(int)
{
}

void Message::NotifyBoardInfoList(S2C_NoticeInfoList const*)
{
}

void Message::NotifyBoardInfoGetReward(S2C_NoticeInfoGet const*)
{
}

void Message::PVPLogin(bool)
{
}

void Message::PVPTrainingSellResult(bool)
{
}

void Message::PVPTrainingZombieChanged(bool)
{
}

void Message::PVPTrainingFinishGems(int)
{
}

void Message::PlaybackListRefresh(std::vector<unsigned long, std::allocator<unsigned long> > const&)
{
}

void Message::PlaybackDownloadResult(unsigned long, bool)
{
}

void Message::PVP_PingSuccess(bool)
{
}

void Message::NotifyAchievementConfigChanged()
{
}

void Message::NotifyAchievementReward(int, int)
{
}

void Message::NotifyPvpSubCoin(int, int)
{
}

void Message::PVPLabRefresh()
{
}

void Message::PVPCompensationReward(int, int, int)
{
}

void Message::BeginPVPUpgradeSuccess()
{
}

void Message::GetPVPCompleteUpgradeGemSuccess(int)
{
}

void Message::GetPVPCompletePVPUpgrade(S2C_PVPCompleteUpgradeData*)
{
}

void Message::GotActActivityStates(bool)
{
}

void Message::VerifiedSales(bool)
{
}

void Message::LevelofDayOpening(bool)
{
}

void Message::LeveloftheDayReward(bool)
{
}

void Message::GetChildrenDayReturn(ChildrenDayStates const*)
{
}

void Message::ComposePlant(bool)
{
}

void Message::NotifyRefreshActivityList(bool, std::set<int, std::less<int>, std::allocator<int> > const&)
{
}

void Message::NotifyRefreshActivityLevelEnd(int, S2C_VacationLevelEndData*)
{
}

void Message::NotifySummeryLottery(int, S2C_SummeryLotteryData const&)
{
}

void Message::NotifySummeryLottery2018(int, S2C_SummeryLotteryData2018 const&)
{
}

void Message::NotifyBossChallengeLevelEnd(int, S2C_BossChallengeLevelEndData const*)
{
}

void Message::NotifyMiniGameChallengeLevelEnd(int, S2C_MiniGameResult const*)
{
}

void Message::NotifyMiniGameRewardEnd(bool)
{
}

void Message::NotifyBossChallengeReward(int, S2C_BossChallengteReward const*)
{
}

void Message::NotifySkipDangerRoom(int, S2C_DangerRoomSkipLevel const*, S2C_PlayerInfo const*)
{
}

void Message::NotifyDangerRoomEnd(int, S2C_DangerRoomEndLevel const*)
{
}

void Message::NotifyStaticConfig(int, S2C_StaticConfig const*)
{
}

void Message::NotifyNewGachaDrawResult(bool)
{
}

void Message::NotifyDailySignWithTwResult(bool, S2C_DailySignWithTW const*)
{
}

void Message::NotifyChallengeReward(std::string const&)
{
}

void Message::NotifyCodeRewardResult(bool, S2C_CodeRewardResult const*)
{
}

void Message::NotifyWechatRewardResult(bool, S2C_WechatShareResult const*)
{
}

void Message::NotifyLimitLotteryReward(bool, S2C_LimitLotteryReward const*)
{
}

void Message::NotifyLimitLotteryBuyCrystalFinish(bool, S2C_LimitLotteryCrystalBuy const*)
{
}

void Message::NotifyLimitLotteryBuyCupShopFinish(bool, S2C_S2C_LimitLotteryCupShop const*)
{
}

void Message::NotifyUnlockNewAvatar(bool, int)
{
}

void Message::NotifyBillingReward(bool, S2C_BillingReward const*)
{
}

void Message::NotifyLevelupBook(bool)
{
}

void Message::NotifyEquipCollection(int, int)
{
}

void Message::NotifyPlatformGiftList(bool, S2C_PlatformGiftData const*)
{
}

void Message::NotifyBattleZRankListEffect(std::vector<int, std::allocator<int> > const&)
{
}

void Message::NotifyShopBuyFinish(bool, int)
{
}

void Message::NotifyShopBuyFinishDetails(bool, S2C_ShopItemPurchaseInfo const*)
{
}

void Message::NotifySecretAreaRewardDetails(bool, New_S2C_BuySecretAreaReward const*)
{
}

void Message::NotifySpringOutingConsumeAndReceive(bool, S2C_PiggyBankReward const*)
{
}

void Message::MsgBorrowFriendPlant(int)
{
}

void Message::FetchGameRank()
{
}

void Message::LoginiCloudServerFinish(bool)
{
}

void Message::UploadFirstTimeFinish(bool)
{
}

void Message::SyncProfileSummaryFinish(bool)
{
}

void Message::SyncProfileListFinish(bool)
{
}

void Message::SyncProfileToServerFinish(bool)
{
}

void Message::SyncProfileFromServerFinish(bool)
{
}

void Message::ValidateChargeFinish(bool)
{
}

void Message::GetConfigVersionFinish(bool)
{
}

void Message::DownloadMagentoFinish(bool)
{
}

void Message::AddFreeGemFinish(bool)
{
}

void Message::GetGachaInfo(S2C_GachaInfo*)
{
}

void Message::BuyPlantGiftSuccess()
{
}

void Message::FinishedInitDangerRoom(bool)
{
}

void Message::AcceptDangerRoomStart()
{
}

void Message::DangerRoomConfirmReward(bool, int, bool)
{
}

void Message::RequestDangerRoomFinish(bool, int)
{
}

void Message::LeafsCost(bool)
{
}

void Message::StartDangerRoomPlay(bool)
{
}

void Message::DangerRoomLifeCost(bool, bool)
{
}

void Message::DangerRoomNewLifeCost(bool)
{
}

void Message::DangerRoomScoreUpdated(bool)
{
}

void Message::GetDangerRoomBonus(bool)
{
}

void Message::GetDangerRoomSkippingBonus(bool)
{
}

void Message::GotExploreTeamStatus(bool)
{
}

void Message::OpenPlantAdventure(bool)
{
}

void Message::GotExplorePlantStatus(int, bool)
{
}

void Message::StartExplore(bool)
{
}

void Message::FreeExplore(int, bool)
{
}

void Message::StopExplore(int, int, bool)
{
}

void Message::GotExploreReward(bool)
{
}

void Message::GotExploreSurprise(bool)
{
}

void Message::NeedRecoverExplorePlant(int)
{
}

void Message::RecoverExplorePlant(bool)
{
}

void Message::GotChristmasLottery(bool, int, int)
{
}

void Message::GotChristmasProtect(bool)
{
}

void Message::GotChristmasAccessoryStat(bool)
{
}

void Message::RefreshChristmasAccessoryStat(bool)
{
}

void Message::ChristmasAccessoryBought(bool)
{
}

void Message::GotChristmasCheckRebate(S2C_ChristmasCheckRebate*)
{
}

void Message::GotChristmasRebate(S2C_ChristmasRebate*)
{
}

void Message::GotGoldenEggStat(bool)
{
}

void Message::RefreshGoldenEggStat(bool)
{
}

void Message::GoldenEggOpen(bool)
{
}

void Message::RefreshLanternUIState()
{
}

void Message::PendantGacha(bool)
{
}

void Message::Get2015NewTearChargeReward(bool, bool)
{
}

void Message::ProcessRedPackLeaderBoardInfo(S2C_ICloud_RedPackLeaderBoard const*)
{
}

void Message::RedPackLeaderBoardReward(S2C_ICloud_RedPackLeaderBoardReward const*)
{
}

void Message::ReceivedRankInfo(bool)
{
}

void Message::BirthdayRewardGot()
{
}

void Message::PinataRewardGot()
{
}

void Message::GotGemReturnState(bool)
{
}

void Message::GotGemReturnReward(bool)
{
}

void Message::ProcessDangerRoomLeaderBoardInfo(S2C_ICloud_DangerRoomLeaderBoard const*, bool)
{
}

void Message::NotifyUUIDInit(bool, std::string const&, std::string const&)
{
}

void Message::NotifyUUIDCheck(int, std::string const&)
{
}

void Message::NotifyUUIDBind(bool)
{
}

void Message::NotifyUUIDLogin(bool)
{
}

void Message::NotifyPurchaseInit(int, std::string const&, std::string const&)
{
}

void Message::NotifyPurchaseValidation(int, std::string const&, int)
{
}

void Message::NotifyLostPurchaseOrder(int, S2C_Purchase_LostPurchaseOrder const&)
{
}

void Message::RequestCharge(std::string const&, std::map<std::string, std::string, std::less<std::string >, std::allocator<std::pair<std::string const, std::string > > >*)
{
}

void Message::ConfirmChildDayItem(std::vector<ChildrenDayItem, std::allocator<ChildrenDayItem> > const&)
{
}

void Message::MonthlyCardBought(bool)
{
}

void Message::MonthlyCardTrial()
{
}

void Message::FirstRechargePackageGot()
{
}

void Message::TotalRechargePackageGot(bool, S2C_ICloud_GetChargeRewardInfo const*)
{
}

void Message::NotifyAdsReward(S2C_ADSReward const&)
{
}

void Message::NotifyExchangeNewAvatar(bool, int)
{
}

void Message::AcFirstRechargeSuc(bool)
{
}

void Message::TravelLogWolrdChestFinish(bool, TravelLogRewardData*)
{
}

void Message::TravelLogIntegralChestFinish(bool, TravelLogRewardData*)
{
}

void Message::ExchangeComplete(bool)
{
}

void Message::PlantTrialPay(bool)
{
}

void Message::CommonBuryInterface(int, TrackInfo const&, bool)
{
}

void Message::FinishLimitGacha(int)
{
}

void Message::GetGachaUseGems(int, int)
{
}

void Message::AddPlantSalesUiReward(PlantSalesUiReward const&)
{
}

void Message::RechargeLogWithSalesUiReward2()
{
}

void Message::FestivalGameMode_CountChange(int, int)
{
}

void Message::FestivalGameMode_LeftBuyTimesChange(int, int, int)
{
}

void Message::OnBuyCarnivalBundle(int, int)
{
}

void Message::ArtifactLevelUp(bool, int)
{
}

void Message::ArtifactRankUp(bool, int)
{
}

void Message::DangerRoomBoostEnd()
{
}

void Message::FinishEndlessLevel(bool)
{
}

void Message::PlantLevelUpOK(std::string const&, int)
{
}

void Message::AvatarPiecesAdd(Sexy::RtWeakPtr<MagentoProductProps> const&, int)
{
}

void Message::ItemPurchaseInfo2(Sexy::RtWeakPtr<MagentoProductProps> const&, std::string const&, int)
{
}

void Message::OnSteadySuccess(int)
{
}

void Message::SteadyAccessory()
{
}

void Message::OnResetSuccess(int)
{
}

void Message::PlantTrialPaySuccess()
{
}

void Message::UnEquipArtifact(int)
{
}

void Message::EquipArtifact(int)
{
}

void Message::FinishPennyGacha(int, int)
{
}

void Message::FinishSecretGacha(int)
{
}

void Message::FinishGetPlayerinfo()
{
}

void Message::NationalDayChargeReward(std::string const&, std::vector<int, std::allocator<int> > const&)
{
}

void Message::PlantTransgenic(int)
{
}

void Message::AvatarTransgenic()
{
}

void Message::GemsRecharge(int)
{
}

void Message::NotifyPiggyBankRewardGot(bool)
{
}

void Message::OnSoldTargetAccessory(int)
{
}

void Message::RequestRank()
{
}

void Message::RequestACLog(S2C_ACLog&)
{
}

void Message::RechargeRewardCurrencyChanged(int)
{
}

void Message::EASquareReward(std::string const&, std::vector<S2C_BonusInfo, std::allocator<S2C_BonusInfo> > const&)
{
}

void Message::RechargeCurrencyChanged()
{
}

void Message::RechargeRewardGot(int, int, std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > > const&)
{
}

void Message::GameCenterAuthenticationChanged(bool)
{
}

void Message::StartPersistorLoad()
{
}

void Message::AppEnteredBackground()
{
}

void Message::AppLostFocus()
{
}

void Message::AppResumeFocus()
{
}

void Message::WechatShareSuccess()
{
}

void Message::WeChatShareFailed()
{
}

void Message::OrientationChanged()
{
}

void Message::NotifyExchangeFinish()
{
}

void Message::PlayerLogout()
{
}

void Message::GameEnd()
{
}

void Message::ClearFakeCurrency()
{
}

void Message::UpdateFakeCurrency()
{
}

void Message::ActivePopupUIClosed()
{
}

void Message::PersistorLoadComplete()
{
}

void Message::FetchVersionComplete()
{
}

void Message::RechargeCheckOnServerComplete()
{
}

void Message::Fake(int)
{
}

void Message::Faiicck()
{
}

void Message::Matikck()
{
}

void Message::OnLuaNotify(std::string const&)
{
}

void Message::AndroidSDKInit(int, int)
{
}

void Message::AutoTestPlantUIShow()
{
}

void Message::ActionLoginRewardEnd()
{
}

void Message::OpenUI(std::string const&)
{
}

void Message::SummerActivity(std::string const&)
{
}

void Message::StartGameOffLine()
{
}

void Message::PauseButtonPressed()
{
}

void Message::GameLoad(int)
{
}

void Message::ProfileSummarySelectResult(int)
{
}

void Message::EASquaredAdvertisementsWillOpen()
{
}

void Message::EASquaredAdvertisementsClosed()
{
}

void Message::EASquaredFlowEnded(std::string const&, int, int)
{
}

void Message::GameBegin()
{
}

void Message::RealGameStart()
{
}

void Message::Decompress(int)
{
}

void Message::GameWon()
{
}

void Message::GameLost()
{
}

void Message::ReadyForLawnItems()
{
}

void Message::LevelLoadComplete()
{
}

void Message::LevelStarting()
{
}

void Message::GameplayEnded()
{
}

void Message::LevelEnded()
{
}

void Message::MissionFinish()
{
}

void Message::SunClicked(CollectableSun*, int)
{
}

void Message::PlantfoodGrabbed(CollectablePlantfood*)
{
}

void Message::PlantfoodGrabbedWhenFull(CollectablePlantfood*)
{
}

void Message::CoinCurrencyFakeBanked(int)
{
}

void Message::GemCurrencyFakeBanked(int)
{
}

void Message::GemFakeSpawned(CollectableGemFake*)
{
}

void Message::CoinCurrencySpawned(CollectableCoin*)
{
}

void Message::PlantfoodSpawned(CollectablePlantfood*)
{
}

void Message::PlantUpgradeSpawned(CollectablePlantUpgrade*)
{
}

void Message::CoinSpawned(CollectableCoin*)
{
}

void Message::CoinFakeSpawned(CollectableCoinFake*)
{
}

void Message::SeedPacketPlanted(SeedPacket*)
{
}

void Message::ZombiePlanted(Zombie*)
{
}

void Message::GamePaused()
{
}

void Message::GameUnpaused()
{
}

void Message::PlantGrowthAndDecayPaused()
{
}

void Message::PlantGrowthAndDecayResumed()
{
}

void Message::CursorAdded(BaseCursor*)
{
}

void Message::PlantfoodCountChanged(int)
{
}

void Message::SunIsInsufficient()
{
}

void Message::SunSpawnedFromSky(CollectableSun*)
{
}

void Message::ProgressMeterSetPercentage(unsigned char)
{
}

void Message::SetNextWaveVisible(bool)
{
}

void Message::SunChanged(int)
{
}

void Message::SunBanked(int)
{
}

void Message::SunBankMax(bool)
{
}

void Message::SunSpent(int)
{
}

void Message::GatherPlantingRestrictions(Sexy::Point const&, PlantType const*, std::vector<PlantingReason, std::allocator<PlantingReason> >*)
{
}

void Message::GatherPlantlessPlantingRestrictions(Sexy::Point const&, std::vector<PlantingReason, std::allocator<PlantingReason> >*)
{
}

void Message::BlockGravestoneSpawning(Sexy::Point const&, bool*)
{
}

void Message::GatherPlantedPacketCount(std::string const&, int*)
{
}

void Message::ClearBoard()
{
}

void Message::GameplayWinConditionMet()
{
}

void Message::TakePlantWeapon(std::string const&)
{
}

void Message::EnableGridItems()
{
}

void Message::PlantAdded(Plant*)
{
}

void Message::NoticeTryUseArenaZombie(int, int)
{
}

void Message::PlantCreate(Plant*)
{
}

void Message::InitBoardArtifactManager()
{
}

void Message::InitBoardHeroPlantManager()
{
}

void Message::StartBoardFade()
{
}

void Message::PlantPlanted(Plant*)
{
}

void Message::GridItemPlanted(GridItem*)
{
}

void Message::ProgressMeterSetCurrentDisplayPercentage(unsigned char)
{
}

void Message::TutorialFunnelEvent(unsigned long)
{
}

void Message::GemCurrencyBanked(int)
{
}

void Message::SunAdd(int)
{
}

void Message::BossPowerWin(bool)
{
}

void Message::ReadyForFlameExtinguished()
{
}

void Message::ReadyForFuseLitEnd()
{
}

void Message::PlantBloverBlowAwayJetpackZombie()
{
}

void Message::FireSingleHandedRockets()
{
}

void Message::TakeImmediatePlantFood()
{
}

void Message::PlantCostChanged(Plant*, int)
{
}

void Message::PlantDieCostChanged(Plant*, int)
{
}

void Message::LastStandLevelInitializing()
{
}

void Message::LastStandLevelStarting()
{
}

void Message::NotifyPlantfoodRelease(Plant*)
{
}

void Message::PlantDestroyed(Plant*)
{
}

void Message::ZombieEnter(Zombie*)
{
}

void Message::CleanPoison(int, int, bool)
{
}

void Message::PlantBlow(Plant*)
{
}

void Message::PreSeedchooserFlowComplete()
{
}

void Message::GatherExtraChallenges(ProfileUtils::ChallengeStatusHolder*)
{
}

void Message::ReadyGoFinish()
{
}

void Message::PaidSunmoneyAtGridForPlant(int, int, int)
{
}

void Message::PlantMoving(Plant*, Sexy::Point&)
{
}

void Message::SunMoneyAdded(int)
{
}

void Message::AutoTestStartAllLevel()
{
}

void Message::ExecuteRenaiEvents()
{
}

void Message::StartBuff()
{
}

void Message::ZombieAddedToBoard(Zombie*)
{
}

void Message::ZombieDropLoot(Zombie*)
{
}

void Message::ZombieDestroyed(Zombie*)
{
}

void Message::ZombieDied(Zombie*, DamageInfo const*)
{
}

void Message::NextWaveButtonPressed()
{
}

void Message::CollectableTryToCollect(Collectable*)
{
}

void Message::CollectableCollectionFinished(Collectable*)
{
}

void Message::ChallengeFailed(Challenge*)
{
}

void Message::TreasureYetiTutorialFailed()
{
}

void Message::SpeedChangeButtonPressed(float)
{
}

void Message::NoticeZombieWarning(int, int, std::string const&)
{
}

void Message::ZombieWarningEffectStarted()
{
}

void Message::HugeWaveComing(bool, int)
{
}

void Message::WaveStarted(int, WaveType::WaveType, bool)
{
}

void Message::WaveStartCreatZombieEnd()
{
}

void Message::DangerRoomReady()
{
}

void Message::ArenaChangeSpeedButtonPressed(float)
{
}

void Message::StealChristmasProtect()
{
}

void Message::LevelEndForTask(LevelDefinitionForTask*)
{
}

void Message::TutorialFTUE(int)
{
}

void Message::CheckBossFightRate(bool)
{
}

void Message::GetDangerRoomLootReward(int, int, std::vector<PlantInfo, std::allocator<PlantInfo> >&)
{
}

void Message::BirthdayZFinish(bool)
{
}

void Message::NotifyLoadingLevelFinished()
{
}

void Message::CoinCurrencyChanged(int)
{
}

void Message::StarCurrencyChanged(int)
{
}

void Message::LeafCurrencyChanged(int)
{
}

void Message::ItemPurchasedFromStore(MagentoProductProps*)
{
}

void Message::CloseCurrentGemProductNotice(std::string const&)
{
}

void Message::CoinsPurchasedFromStore(int)
{
}

void Message::KeygatePurchasedFromStore(MagentoProductProps*)
{
}

void Message::StargatePurchasedFromStore(MagentoProductProps*)
{
}

void Message::CartInstanceEvent(MagentoProductProps*)
{
}

void Message::KeyCurrencyChanged()
{
}

void Message::GemCurrencyChanged(int)
{
}

void Message::GemCurrencyAdd(int)
{
}

void Message::PlantUnlocked(std::string const&)
{
}

void Message::BuyNewerPresent()
{
}

void Message::CardPlayBuyFinish()
{
}

void Message::FestivalGameModeCountChange()
{
}

void Message::GemReturnSuccess()
{
}

void Message::BuyItemPaySuccess()
{
}

void Message::PlantGiftPaymentSuccess()
{
}

void Message::NotifyPowerupUsesChanged(PowerupRecord*)
{
}

void Message::MaterialChanged()
{
}

void Message::RiftIDChanged(unsigned long)
{
}

void Message::ChangeNewRareAvatar(int, int, bool)
{
}

void Message::StarCompleted(std::string const&)
{
}

void Message::GemsPurchasedFromStore(int)
{
}

void Message::ZmatchTicketChanged(int)
{
}

void Message::ZmatchTicketAdd(int)
{
}

void Message::ZmatchTicketPurchasedFromStore(int)
{
}

void Message::BombUnlocked()
{
}

void Message::GetCoinsFromPlantBag()
{
}

void Message::RechargeBundlePurchased(int)
{
}

void Message::RechargeBundleBeforePurchased(int)
{
}

void Message::ServerTimeReceived()
{
}

void Message::LuaNotifyGeneral(std::string const&)
{
}

void Message::RechargeBundleShowed()
{
}

void Message::PennyTechChanged(int)
{
}

void Message::PennyFuelCurrencyChanged(int, bool, int)
{
}

void Message::ItemLogin()
{
}

void Message::ObtainStar(int)
{
}

void Message::PlayerStarFlow(int)
{
}

void Message::CoinUse(int, std::string const&)
{
}

void Message::RefreshStarConvert()
{
}

void Message::UnlockPlantAvatar()
{
}

void Message::ObtainAvatarPieces(int)
{
}

void Message::ObtainGeneSequence(int)
{
}

void Message::ObtainGeneEssence(int)
{
}

void Message::ObtainPlantChips(int)
{
}

void Message::ObtainAccessoryPieces(int, int)
{
}

void Message::BeforeChangeMaterialNumber(int, int)
{
}

void Message::PlantFamilyRefresh()
{
}

void Message::PlantLevelUp(std::string const&, int)
{
}

void Message::GetFreeGems(std::string const&, int)
{
}

void Message::GetRechargeGems(int, int)
{
}

void Message::RechargeLogWithSalesUiReward(Sexy::RtWeakPtr<MagentoProductProps> const&)
{
}

void Message::RechargeLog(Sexy::RtWeakPtr<MagentoProductProps> const&)
{
}

void Message::NotifyBundlePurchased(int, std::vector<PaymentBundleInfo, std::allocator<PaymentBundleInfo> > const&)
{
}

void Message::SetUpSalesBought()
{
}

void Message::ShowNextRechargeNode()
{
}

void Message::GachaInitFinished()
{
}

void Message::CoinStoreClose()
{
}

void Message::GachaTutorialFinished()
{
}

void Message::JoinActivity(std::string const&)
{
}

void Message::EventPurchase(EventMetrics*, int)
{
}

void Message::ChangeStoreDisplayerButton()
{
}

void Message::RedPackPurchased(int)
{
}

void Message::ItemExChange(Sexy::RtWeakPtr<MagentoProductProps> const&, int, int)
{
}

void Message::PlantUnlockFragment(Sexy::RtWeakPtr<MagentoProductProps> const&, int)
{
}

void Message::BlackPackageCharge(std::string const&)
{
}

void Message::ItemPurchase(Sexy::RtWeakPtr<MagentoProductProps> const&, int)
{
}

void Message::NotifySyncActivityData(bool)
{
}

void Message::ReflashStoreGiftUI()
{
}

void Message::RefreshStorePlantGift()
{
}

void Message::TmallClick()
{
}

void Message::PlantPackageBuy(PlantPackage*)
{
}

void Message::NotifyADWatchFinish(int)
{
}

void Message::MissionGemsUse(Sexy::RtWeakPtr<MagentoProductProps> const&, bool, int)
{
}

void Message::FinishCheckAccount(bool)
{
}

void Message::NotifyShareSaveFinished()
{
}

void Message::NotifyShareRewardFinished()
{
}

void Message::NotifyShareSaveBegin()
{
}

void Message::NotifyPlantPacketSelected(bool, int, bool, bool)
{
}

void Message::NotifyPlantFavouriteChange(bool, int)
{
}

void Message::NotifyClickPlant(int)
{
}

void Message::NewPlantView_PlantLevelUp(int)
{
}

void Message::NewPlantView_SwitchAvatar(int)
{
}

void Message::NewPlantView_SwitchAccessory(int)
{
}

void Message::NewPlantView_UnlockAvatar(int)
{
}

void Message::NewPlantView_NotifyAvatarPackageClose()
{
}

void Message::NotifySpeedChanged(float)
{
}

void Message::NotifyCoinCollected()
{
}

void Message::NotifyGotHit()
{
}

void Message::NotifyPlayerKilled()
{
}

void Message::RunningPlayerDied()
{
}

void Message::NotifyStartRunning()
{
}

void Message::NotifyJumpOnBoard()
{
}

void Message::NotifyJumpOffBoard()
{
}

void Message::NotifyActivateSkill()
{
}

void Message::PlantFoodEnd(Plant*)
{
}

void Message::BarSetPercentage(float)
{
}

void Message::ZombieHypnotized(Zombie*)
{
}

void Message::NotifyCloseDialog()
{
}

void Message::WishingPoolLottery()
{
}

void Message::BuyWishingPool(int)
{
}

void Message::GargantuarDefeated(ZombieGargantuar*)
{
}

void Message::ZombieDropHead(Zombie*)
{
}

void Message::BuyPlantCultivate(int)
{
}

void Message::UpdateGiftFoReturnSignDays(int)
{
}

void Message::BuyGiftFoReturn(int)
{
}

void Message::BuyDaveKitchen(int)
{
}

void Message::BuyDragonTreasure(int)
{
}

void Message::BuyTreasurePavilion(int)
{
}

void Message::NotifyReachMaxInterval()
{
}

void Message::NotifyZombieCacheDatasChanged(std::vector<ZombieCacheData, std::allocator<ZombieCacheData> > const&)
{
}

void Message::NotifyTurnChanged(int)
{
}

void Message::NotifyHealthEmpty(bool)
{
}

void Message::NotifyZombieUpgradeUnlocked(int)
{
}

void Message::NotifyUpgradePlant(Plant*)
{
}

void Message::NotifySunAddIncrease()
{
}

void Message::NotifyGameplayStarted()
{
}

void Message::NotifyTriggerUpgradeSkill(float)
{
}

void Message::NotifyFPSReachLimit()
{
}

void Message::NotifyTraingingPacketSelected(bool, int, bool)
{
}

void Message::RefreshTaskTips()
{
}

void Message::RefreshRankNotice()
{
}

void Message::NotifyTutorialStep(int)
{
}

void Message::NewPVPNetworkResponseReceived(int, int)
{
}

void Message::UILoadFinish()
{
}

void Message::NewPVPNetworkIssueDecision(int, int)
{
}

void Message::WavesNotify(int)
{
}

void Message::PlantDied(Plant*)
{
}

void Message::BarTakeDamage(int, float)
{
}

void Message::BarSetPercentage(int, float)
{
}

void Message::NewPVPDamageOpponentBases(float)
{
}

void Message::NewPVPFirstBlood()
{
}

void Message::PlantDestory(Plant*)
{
}

void Message::StreetLampSheep(Plant*)
{
}

void Message::StreetLampApplyFood()
{
}

void Message::StreetLampEndFoodEffect()
{
}

void Message::NewPVPAddPlant(int, int)
{
}

void Message::NewPVPUpgradeSun()
{
}

void Message::NewPVPEndDuan(int)
{
}

void Message::NewPVPPassLevel(bool, bool, int)
{
}

void Message::NewPVPAddZombie(NewPVPAddZombieMessageData*)
{
}

void Message::ZombieCloseToHouse(Zombie*)
{
}

void Message::NewPVPCompleteTask(int)
{
}

void Message::NotifyProjectileCreated(Projectile*)
{
}

void Message::NotifyGridItemPlaceOnBoard(GridItemAnimation*)
{
}

void Message::NotifyPopAnimCreated(Effect_PopAnim*)
{
}

void Message::CursorDestroyed(BaseCursor*)
{
}

void Message::PlantShoveled(Plant*)
{
}

void Message::NotifyChooserItemClicked(Message::UINewPVPSeedChooserItem*)
{
}

void Message::NewPVPBattlePassBuyPrivilege(std::vector<S2C_BonusInfo, std::allocator<S2C_BonusInfo> > const&)
{
}

void Message::NewPVPBattlePassBuyBundle(int)
{
}

void Message::NewPVPBattlePassExtrarewards(std::vector<S2C_BonusInfo, std::allocator<S2C_BonusInfo> > const&, int)
{
}

void Message::NewPVPShopBuyChest(int, std::vector<S2C_BonusInfo, std::allocator<S2C_BonusInfo> >&)
{
}

void Message::ResultClosed()
{
}

void Message::CardGameRewardClose()
{
}

void Message::NotifyCardGameRewardDetails(bool, New_S2C_BuyCardGameReward const*)
{
}

void Message::CardGamePickCardStart(int)
{
}

void Message::CardGameNetworkResponseReceived(int, int)
{
}

void Message::AfterPlayerActionStart()
{
}

void Message::BeforePlayerDiscard_ForCardObject()
{
}

void Message::CardGameIntroStart()
{
}

void Message::CardGamePlayerActionStart()
{
}

void Message::CardGamePlayerDiscardStart()
{
}

void Message::NotifyDrawCardsActionDone()
{
}

void Message::NotifyPlayCardsActionDone()
{
}

void Message::NotifyCardSelectDone()
{
}

void Message::NotifyCardTutorial(bool)
{
}

void Message::CustomLevelNetworkResponseReceived(int, int)
{
}

void Message::CustomLevelNetworkIssueDecision(int, int)
{
}

void Message::CustomLevelTutorialSeedBankCreated()
{
}

void Message::CustomLevelTutorialSeedPacketCreated()
{
}

void Message::CustomLevelTutorialSurfaceCreated()
{
}

void Message::CustomLevelTutorialZombieModuleCreated()
{
}

void Message::CustomLevelTutorialZombieSelectedListCreated()
{
}

void Message::CustomLevelTutorialRedoDrag()
{
}

void Message::CustomLevelTutorialFinishDrag()
{
}

void Message::CustomLevelTutorialCloseContainer()
{
}

void Message::CustomLevelTutorialRedoDragWaveEvent()
{
}

void Message::CustomLevelTutorialFinishDragWaveEvent()
{
}

void Message::CustomLevelTutorialFinishCloseEvent()
{
}

void Message::CustomLevelTutorialCloseEditor()
{
}

void Message::EvaluateCustomLevel(bool)
{
}

void Message::PublishCustomLevel()
{
}

void Message::CustomLevelMainMenuRefresh(int)
{
}

void Message::CustomLevelShowRefreshButton(bool)
{
}

void Message::CustomLevelPlayCoinChanged(int)
{
}

void Message::CustomLevelCreateCoinChanged(int)
{
}

void Message::CustomLevelCreateLevelRefresh(bool)
{
}

void Message::CloseMainMenuDialog()
{
}

void Message::SelectTab(int)
{
}

void Message::SwitchToMainMenu(bool)
{
}

void Message::ModifyLevelName(std::string const&)
{
}

void Message::BeforePlayerDiscard()
{
}

void Message::NotifyTutorialWormHoleEnd()
{
}

void Message::NotifyPVZ1HowToPlayClose()
{
}

void Message::PlantKillZombie(std::string const&)
{
}

void Message::NotifyProjectileCollideEntity(Projectile*, BoardEntity*)
{
}

void Message::PlantCombos(Plant*)
{
}

void Message::ChildRemovedSmoothlyFromVerticalList()
{
}

void Message::WhitelistingChanged()
{
}

void Message::NotifyAwardScreenClosed()
{
}

void Message::ZombieConditionApplied(Zombie*, int, float)
{
}

void Message::ZombieBurnedToAsh(Zombie*)
{
}

void Message::ZombieElectrified(Zombie*)
{
}

void Message::NotifyCleanPoison()
{
}

void Message::NotifySlip()
{
}

void Message::NotifyEnterManhole()
{
}

void Message::NotifyKillPlant()
{
}

void Message::NotifyHitPlant()
{
}

void Message::NotifySelfExplodeJalapeno()
{
}

void Message::NotifySelfExplodeExplodenut()
{
}

void Message::GridItemDestroyed(std::string const&)
{
}

void Message::RiftNetworkResponseReceived(int, int)
{
}

void Message::WorldMapWorldLoaded()
{
}

void Message::WorldMapLoadComplete()
{
}

void Message::BossRiftEnterLootPhase()
{
}

void Message::SecurityGourdsPurchased(int)
{
}

void Message::NotifyRiftPostEndPlay()
{
}

void Message::RiftEndOfMatch(bool)
{
}

void Message::RiftTimedEventGamePlaySend()
{
}

void Message::WorldMapEventBarImpression(std::string const&, std::string const&, int)
{
}

void Message::InitializingModuleManagerForLevelDefinition(Sexy::RtWeakPtr<LevelDefinition>&)
{
}

void Message::RiftNarrativeComplete()
{
}

void Message::PerkSelected(std::string&, bool, Sexy::Point&)
{
}

void Message::PerkDeselected(std::string&)
{
}

void Message::PerkScreenCreated(AdaptorPerkSelectionDialog*)
{
}

void Message::PerksFinalized()
{
}

void Message::PerksPurchased(int, std::string const&, char const*)
{
}

void Message::RiftLevelPerkActivation(PennyPerk*)
{
}

void Message::BoardTimerStarted()
{
}

void Message::BossSetPhaseCount(int)
{
}

void Message::BossProgressMeterStageCountdown()
{
}

void Message::BossShowProgressMeter()
{
}

void Message::BossSetCurrentPhase(int, int)
{
}

void Message::ZombieKnockedBackByPlayer(KnockbackReason)
{
}

void Message::PreWaveInitialization(WaveManagerProperties*)
{
}

void Message::RiftNetworkIssueDecision(int, int)
{
}

void Message::SettlePennyLevel()
{
}

void Message::ObtainPennySignal(int)
{
}

void Message::ConsumeFuel(int)
{
}

void Message::ZombieReachLine(Zombie*)
{
}

void Message::OnGridItemGravestoneCoinOnDestructionKilled(GridItemGravestoneCoinOnDestruction*)
{
}

void Message::ZombieConditionPrepare(Zombie*, int*, float*)
{
}

void Message::ZombieDamageTaken(Zombie*, DamageInfo const&)
{
}

void Message::NotifyToolPlantLevelUp()
{
}

void Message::SeedChooserSelectionFinalized()
{
}

void Message::RiftTimedEventTimerStarted()
{
}

void Message::RiftTimedEventTimerNotify()
{
}

void Message::ToolAppliedPlantfood(PlantGroup*)
{
}

void Message::ZombieDamageTakenRaw(Zombie*, DamageInfo const&)
{
}

void Message::NotifyToolPacketUsed(std::string const&, int, int)
{
}

void Message::ArtifactTrigger()
{
}

void Message::NotifyArtifactToolUsed()
{
}

void Message::NotifyArtifactButtonDepress(int)
{
}

void Message::GetArtifactBoosts(int, int)
{
}

void Message::NotifyRiftTimedUsedMax()
{
}

void Message::NotifyMeteorCursor(int, int)
{
}

void Message::NotifyAcidCursor(int, int)
{
}

void Message::NotifyArtifactGravityCursor(int, int)
{
}

void Message::NotifyArtifactHydraulicCursor(int, int)
{
}

void Message::NotifyAcidZombieDie(Zombie*)
{
}

void Message::NotifyAcidReturn(int, int, bool)
{
}

void Message::NotifyAcidChanged(int, int)
{
}

void Message::MidasTouchSpecialDied(Zombie*)
{
}

void Message::AddMusicalSuccessedCount(int)
{
}

void Message::NotifyWidenDragon()
{
}

void Message::NotifySwarmSwitchState(int)
{
}

void Message::NotifySwarmSwitchShootType(float)
{
}

void Message::NotifySwarmFireProjectile(BoardEntity*, int)
{
}

void Message::NotifySwarmFireProjectileFinish()
{
}

void Message::NotifySwarmStartShoot()
{
}

void Message::NotifyHoloStart()
{
}

void Message::NotifyHoloEnd()
{
}

void Message::NotifyHoloCooldown()
{
}

void Message::ArtifactIdle()
{
}

void Message::ArtifactClearBoard()
{
}

void Message::ArtifactCooldown()
{
}

void Message::ZombieReaddedToBoard(Zombie*)
{
}

void Message::ZombieEnterBoardX(Zombie*)
{
}

void Message::ZombieConditionTimeAppend(Zombie*, int, float*, bool)
{
}

void Message::ZombieConditionEnded(Zombie*, int)
{
}

void Message::CthulhuAbsorbDark(Plant*)
{
}

void Message::VaseArtifactProducePlantCard(std::string const&)
{
}

void Message::ActionComplete()
{
}

void Message::ArtifactDisplayBoardUpdate()
{
}

void Message::NotifyShieldBlock(int)
{
}

void Message::SelectArtifact(int)
{
}

void Message::ArtifactBless(bool)
{
}

void Message::ArtifactDisplayLevelSelect(int)
{
}

void Message::ArtifactDisplaySelectButton(int)
{
}

void Message::ArtifactPrismTowerActivate()
{
}

void Message::ArtifactPrismTowerDeActivate()
{
}

void Message::RefreshGeneEnhancement()
{
}

void Message::GeneLevelUpSuccess(int, int)
{
}

void Message::BuyGeneFactor(int)
{
}

void Message::NewPlantView_NotifyAccessorySelectContent(std::string const&)
{
}

void Message::DisplaySelectButton(int)
{
}

void Message::UIUnchartedSelectTab(int)
{
}

void Message::PVZ1ModeNetworkResponseReceived(int, int)
{
}

void Message::ScoreChallengeCompleted()
{
}

void Message::ReplayScoreUpdated(int, float)
{
}

void Message::ScoreCalculated(int, std::string const&, float)
{
}

void Message::ScoreUpdated(int, float)
{
}

void Message::ZombieBleedingOut(Zombie*, DamageInfo const*)
{
}

void Message::ZombieDropArmor(Zombie*, long)
{
}

void Message::PlantSmashedToDeath(Plant*)
{
}

void Message::PlantDamageTaken(Plant*, DamageInfo&)
{
}

void Message::GravestoneDestroyed(GridItemGravestone*)
{
}

void Message::ZombossStageEnding(Zombie*, int)
{
}

void Message::JoustLossDecision(bool, bool, int)
{
}

void Message::HideTopHUD()
{
}

void Message::ShowTopHUD()
{
}

void Message::JoustNetworkResponseReceived(int, int)
{
}

void Message::JoustNetworkIssueDecision(int, int)
{
}

void Message::JoustShowingFUEInAdventureScreen(bool)
{
}

void Message::JoustNarrativeComplete()
{
}

void Message::JoustTournamentEndRewarded()
{
}

void Message::BattleVictory(int, int)
{
}

void Message::BattleSettlement(int, int, std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > > const&)
{
}

void Message::JoustStartOfMatch()
{
}

void Message::JoustEndOfMatch(int)
{
}

void Message::BattleZ(std::vector<int, std::allocator<int> > const&, std::vector<int, std::allocator<int> > const&, std::vector<int, std::allocator<int> > const&)
{
}

void Message::NotifyUseButtonClicked(int)
{
}

void Message::NotifyBowlingRefill(std::vector<std::string, std::allocator<std::string > > const&, float)
{
}

void Message::NotifyRefreshCard(float)
{
}

void Message::NotifyTimeBack(int)
{
}

void Message::NotifyXRay(float)
{
}

void Message::RambutanDestroy(BoardEntity*)
{
}

void Message::RambutanReturn(BoardEntity*, bool)
{
}

void Message::IceboundEnd(Zombie*)
{
}

void Message::WireGelsemiumSelected()
{
}

void Message::WireGelsemiumLaunched()
{
}

void Message::WireGelsemiumTappedOnCooldown()
{
}

void Message::TideTransitionComplete(TideModule const*)
{
}

void Message::SelectMiniGame(int)
{
}

void Message::ObtainedReward(int)
{
}

void Message::OnBuyToyNight(int)
{
}

void Message::ReceivedPlantPediaReward(int)
{
}

void Message::NotifySetDice()
{
}

void Message::NotifyBoardSetup()
{
}

void Message::NotifyMovingFinish(bool)
{
}

void Message::RichmanDiceShopBuyFinish(int)
{
}

void Message::TileEvent_MoveForward_Index_Post(int)
{
}

void Message::TileEvent_MoveBackward_Index_Post(int)
{
}

void Message::TileEvent_Start_Post()
{
}

void Message::TileEvent_Reward_Post()
{
}

void Message::TileEvent_GuessGame_Post(int, int)
{
}

void Message::TileEvent_ThrowAgain(int, int)
{
}

void Message::TileEvent_MiniGame_Post()
{
}

void Message::TileEvent_BossBattle_Post()
{
}

void Message::TileEvent_WorldLevel_Post()
{
}

void Message::RichMan_RollDice()
{
}

void Message::NotifyDiceRoll()
{
}

void Message::BlockPipleline(PlantFlattenedshroom*)
{
}

void Message::UnblockPipleline(PlantFlattenedshroom*)
{
}

void Message::SmokeEnd()
{
}

void Message::SmokeDiffusion(GridItemSmokeManhole*)
{
}

void Message::BlockSmokeManhole(PlantFlattenedshroom*)
{
}

void Message::UnblockSmokeManhole(PlantFlattenedshroom*)
{
}

void Message::AbsorbSmoke(PlantLotusshooter*)
{
}

void Message::HurrikaleWind(int)
{
}

void Message::PlantBloverWind()
{
}

void Message::ExplorerTorchExtinguished(Zombie*)
{
}

void Message::PlantPlantfooded(Plant*)
{
}

void Message::PlantUpgraded(Plant*, int)
{
}

void Message::PlantTrialBuy(int, std::string const&)
{
}

void Message::LimitLotteryBuyCoin(int, int)
{
}

void Message::CheckGameCenterFinished(bool)
{
}

void Message::GetGameCenterUrlFinished(std::string const&)
{
}

void Message::ZombieConfusion(Zombie*)
{
}

void Message::PlantFire()
{
}

void Message::ZombieTossEnd(Zombie*)
{
}

void Message::ZMatchShopItemBuyFinish(int, int)
{
}

void Message::BattleBuyTimes(std::string const&, int, int)
{
}

void Message::BattleShop(int, int)
{
}

void Message::PopAllButtonsState()
{
}

void Message::NotifyStoneBonusClosed()
{
}

void Message::StartStoneLottery()
{
}

void Message::FinishStoneLottery()
{
}

void Message::GLLotteryReward(int, int, std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > > const&)
{
}

void Message::NationalDayStoneLottery(int, int)
{
}

void Message::Jump(int, int)
{
}

void Message::NameAuthenticationSuc(bool)
{
}

void Message::GetOppoDailyReward()
{
}

void Message::GetOppoRechargeReward()
{
}

void Message::DoubleFestivalRechargeReward(int, std::vector<int, std::allocator<int> > const&, std::vector<int, std::allocator<int> > const&)
{
}

void Message::NotifyLeft30Seconds()
{
}

void Message::PlantDiedBy(Plant*, bool)
{
}

void Message::NotifyGameBegin()
{
}

void Message::ZombieGentleManDrop(Zombie*)
{
}

void Message::updateBuyPlantButton()
{
}

void Message::NotifyPurchasedSpecialOffer()
{
}

void Message::NotifyBackFromRift()
{
}

void Message::NationalDayDailyReward(int, std::vector<int, std::allocator<int> > const&)
{
}

void Message::UpdateSumDays(int)
{
}

void Message::DoubleFestivalDailyReward(int, std::vector<int, std::allocator<int> > const&, std::vector<int, std::allocator<int> >&)
{
}

void Message::NotifyInputEnable(bool)
{
}

void Message::GLLimitLotteryResult(bool)
{
}

void Message::StartLimitLottery()
{
}

void Message::NotifyLimitBonusClosed()
{
}

void Message::FinishLottery()
{
}

void Message::DoubleFestivalLotteryDraw(std::vector<int, std::allocator<int> > const&, std::vector<int, std::allocator<int> > const&, std::vector<int, std::allocator<int> > const&)
{
}

void Message::LimitLotteryExchange(std::vector<int, std::allocator<int> > const&)
{
}

void Message::RefreshLimitedSummonRank(int)
{
}

void Message::BuyLimitedSummon(int)
{
}

void Message::BuyNewYearGoods(int)
{
}

void Message::BuyCarnivalPacket(int)
{
}

void Message::ExchangeGeneralPlantChips(int, int)
{
}

void Message::NotifySelectBoxSelected(int)
{
}

void Message::NotifySelectBoxIsCorrect(bool)
{
}

void Message::ShowRewardFinish()
{
}

void Message::BuyLionDanceGacha(int)
{
}

void Message::FightZodiac_UseFirework(int, bool)
{
}

void Message::CollectIntegralTaskFinish()
{
}

void Message::UpdateCallofWishTask()
{
}

void Message::CallWishTimes(int)
{
}

void Message::BuyCallofWish(int)
{
}

void Message::RefreshSomeTasksData()
{
}

void Message::RewardStart()
{
}

void Message::RewardEnd()
{
}

void Message::ReBuildTasks()
{
}

void Message::ObtainIntegral(int)
{
}

void Message::FinishTravelogDailyTask()
{
}

void Message::FinishTravelogSpecialTask()
{
}

void Message::FinishTravelogWorildTask()
{
}

void Message::SaveTaskState()
{
}

void Message::DeleteTask(int)
{
}

void Message::ObtainDaveTreasureIntegral(int)
{
}

void Message::FinishPlantAdventure(int)
{
}

void Message::ExtinguishFire()
{
}

void Message::SetDailyGemsRecharge(int)
{
}

void Message::SetGemsRecharge(int)
{
}

void Message::PlantLevelUp()
{
}

void Message::SetPvPLabLevel(int, int)
{
}

void Message::SetDangerRoomMaxLevel(int)
{
}

void Message::PVPBuyShopObject()
{
}

void Message::BuySecretStore()
{
}

void Message::GenericObtainIntegral(int, int)
{
}

void Message::PvZ1FinishLevel(int, bool)
{
}

void Message::MagnetShroomPullHelm(Plant*, BoardEntity*)
{
}

void Message::PlantHypnoZombie(Plant*, Zombie*)
{
}

void Message::ShieldArtifactKillZombie(Zombie*)
{
}

void Message::HappyVaseBreaker_BreakVase()
{
}

void Message::FestivalGoldenEgg_BreakEgg()
{
}

void Message::WinBossChallenge()
{
}

void Message::BuyRealSecretStore()
{
}

void Message::RecruitNum()
{
}

void Message::RecruitStarNum()
{
}

void Message::ObatinPrivilege()
{
}

void Message::ObatinPennyPrivilege()
{
}

void Message::ObtainPennyGuideIntegral(int)
{
}

void Message::SunProducedByPlant(CollectableSun*)
{
}

void Message::BreakVaseStartOrEnd(bool)
{
}

void Message::BuyGoldenEgg(int)
{
}

void Message::BuyArborDayKettle(int)
{
}

void Message::BuyBattleOrderPrivilege()
{
}

void Message::BuyBattleOrderBundle(int)
{
}

void Message::BuyGrowthPackage(int)
{
}

void Message::AnniversaryTreasureVaseEnd()
{
}

void Message::NewRecallSelect(int, int)
{
}

void Message::BundleBuySuccess(int)
{
}

void Message::BuyRenaiEgg(int)
{
}

void Message::BuyIOSCukePacket()
{
}

void Message::BuyFutureGiftBox(int)
{
}

void Message::BuyPennyGiftBox(int)
{
}

void Message::BuyAutumnHarvest(int)
{
}

void Message::BuyLuckyChestBox()
{
}

void Message::NFSLinkageTaskReward()
{
}

void Message::NFSLinkageAvatarReward()
{
}

void Message::LuckyChestTaskReward()
{
}

void Message::PlantWarsStarTask()
{
}

void Message::PurchaseWorld(MapEventItem const*)
{
}

void Message::NotifyUnchartedBirthdayFinished(bool)
{
}

void Message::LuckyChestTaskCompleted(int)
{
}

void Message::ActiveNewYearFinish(int, std::string const&)
{
}

void Message::PinataParty(std::string const&)
{
}

void Message::ZombieLaneChangeEnded(Zombie*)
{
}

void Message::NotifyWhackGameBegin()
{
}

void Message::NotifyRandMole()
{
}

void Message::NotifyWhackGameEnd()
{
}

void Message::PropTouch(int)
{
}

void Message::AwardGiven(int, char const*, int)
{
}

void Message::EpicQuestRewarded(_EpicQuestRewardInfo const*)
{
}

void Message::MusicBeatReceived()
{
}

void Message::MusicBarReceived()
{
}

void Message::UUIDDialogClosed()
{
}

void Message::PowerupWarning(BasePowerup*)
{
}

void Message::AircraftSeparateDone(int)
{
}

void Message::AircraftDisconnect(int)
{
}

void Message::BoardRegionResized(BoardRegion*)
{
}

void Message::DoEntangleZombie(Zombie*)
{
}

void Message::BombTriggered(Bomb*)
{
}

void Message::BeghouledProgressMeterSetWinCount(int)
{
}

void Message::BeghouledProgressMeterSetMatchCount(int)
{
}

void Message::BeghouledPlantUpgraded(std::string&)
{
}

void Message::BeghouledClearGridLocation(int, int)
{
}

void Message::BeghouledShufflePowerup()
{
}

void Message::ObjectiveFailed(Challenge*)
{
}

void Message::ChallengeModuleGameplayEnded()
{
}

void Message::ZombieNudgeEnd(Zombie*)
{
}

void Message::GrimroseSwallowedZombie(Zombie*)
{
}

void Message::ParsnipProjectileDestoryed(ParsnipUltraProjectile*)
{
}

void Message::PlantConvertedToProjectile(Plant*)
{
}

void Message::MissileToeSelected()
{
}

void Message::MissileToeLaunched()
{
}

void Message::MissileToeTappedOnCooldown()
{
}

void Message::UpdateAlarmSagittifoliaIdle(Sexy::Point const&, Sexy::Point const&, bool)
{
}

void Message::RailcartMoved(GridItemRailcart*)
{
}

void Message::MechanismPlankMoved(GridItemMechanismPlank*)
{
}

void Message::NotifySteamTrainMoving()
{
}

void Message::FreezeZombossRobot(GameObject*, float)
{
}

void Message::NewspaperBurned()
{
}

void Message::CheatActivated(std::string const&)
{
}

void Message::CheatSystemInvalidated()
{
}

void Message::CollectableExpired(Collectable*)
{
}

void Message::CollectableCollectionStarted(Collectable*)
{
}

void Message::CollectableTryToInstantUse(Collectable*)
{
}

void Message::CollectableFinishCollect()
{
}

void Message::CollectableHitGround(Collectable*)
{
}

void Message::CollectableSeedRainFinished(CollectableSeedRain*)
{
}

void Message::ConveyorPickingSeed()
{
}

void Message::ConveyorAddSeed(ConveyorAddSeedInstruction const&)
{
}

void Message::ConveyorRemoveSeed(ConveyorRemoveSeedInstruction const&)
{
}

void Message::NewWaveStarting(int, WaveDefinition const*)
{
}

void Message::PowerupDeactivated(BasePowerup*)
{
}

void Message::LevelRewardDropped()
{
}

void Message::ViewBoardOrZombiesButtonPressed()
{
}

void Message::NPCFinishedEntering(CrazyNPC*)
{
}

void Message::NPCFinishedExiting(CrazyNPC*)
{
}

void Message::NPCSpawnFakeCoins()
{
}

void Message::NPCDrawed(Sexy::Graphics*)
{
}

void Message::BattleStatementUIMouseDown()
{
}

void Message::DangerRoomSkipLevel(int)
{
}

void Message::DangerRoomLevelEnded(DangerRoomInfo const&)
{
}

void Message::MowerTriggered(LawnMower*)
{
}

void Message::MowerInitialized(LawnMower*)
{
}

void Message::LaunchCuke(bool, int, int)
{
}

void Message::DangerRoomCardPurchased(int)
{
}

void Message::DangerRoomHighScoreChanged()
{
}

void Message::WorldMapMapPathEnded()
{
}

void Message::WorldMapSwitchedWorlds(WorldData*)
{
}

void Message::ActiveProtectFinish(int, int)
{
}

void Message::FireGourdIsHit(PlantFireGourd*)
{
}

void Message::BeachWaveChangeColor(bool)
{
}

void Message::ThunderStart()
{
}

void Message::ThunderEnd()
{
}

void Message::AirshipSetPercentage(float)
{
}

void Message::SkyCannonUsed()
{
}

void Message::SkyCannonTouchOutside()
{
}

void Message::SkyCannonPressed()
{
}

void Message::AirshipTakeDamage(float)
{
}

void Message::ProgressMeterSetFlagCount(int)
{
}

void Message::ReviveSucceed()
{
}

void Message::ReviveClose()
{
}

void Message::StartGameButtonPressed()
{
}

void Message::SetMoonWaveNum(int)
{
}

void Message::SetTotalWaveCount(int)
{
}

void Message::NotifyRenaiTileState(bool)
{
}

void Message::NotifyRollerDestroy(GridItemRenaiRoller*)
{
}

void Message::NotifyStatueFinishCarve(GridItemRenaiStatue*)
{
}

void Message::NotifyStatueReveal()
{
}

void Message::NotifyStatueEnable(bool)
{
}

void Message::NotifyStatueBreak()
{
}

void Message::NotifyStatueDestroy(GridItemMazeStatue*)
{
}

void Message::NotifyStatueHit(float, float)
{
}

void Message::SmokeBombExploded(HeianSmokeBomb*)
{
}

void Message::GameObjectSerializedIn(GameObject*)
{
}

void Message::PlantTrialDialogClosed()
{
}

void Message::ForceReloadData()
{
}

void Message::MissionStart(std::string const&, std::string const&, int)
{
}

void Message::Toturi(int, int)
{
}

void Message::ToolAppliedPlantfoodToGridItem(GridItem*)
{
}

void Message::PowerTilePlaced(GridItem*)
{
}

void Message::CardGameStaffChange(CardGameGridItemStaff*)
{
}

void Message::EliminateShieldDestroyed(int)
{
}

void Message::EliminateOnce()
{
}

void Message::FlowerPotDied(GridItemFlowerPot*)
{
}

void Message::NotifyColorChanged()
{
}

void Message::NotifyTutorialReward()
{
}

void Message::RedPacketRewardGot(int, int, std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > > const&)
{
}

void Message::DangerRoomSelectResultClosed()
{
}

void Message::DangerRoomSelectScreenClosed()
{
}

void Message::DangerRoomSelectListSaved()
{
}

void Message::NotifyFreeItemGot(std::string const&)
{
}

void Message::HardLevelRewardClosed()
{
}

void Message::TimeEnergyTrigger(int)
{
}

void Message::DisplayLevelSelect(int)
{
}

void Message::ArtifactPresentClose()
{
}

void Message::SecretAreaRewardClose()
{
}

void Message::PlantTouch(Sexy::Point const&)
{
}

void Message::PlantUpgradeTouch(Sexy::Point const&)
{
}

void Message::NotifySecretGachaChangePlant(int)
{
}

void Message::NotifyTutorialResponse()
{
}

void Message::NotifyTutorialResponseInner()
{
}

void Message::NotifyDrawFinish()
{
}

void Message::GridItemDestroyedEntity(GridItem*)
{
}

void Message::GravestoneCreated(GridItemGravestone*)
{
}

void Message::PowerTileRemoved(GridItem*)
{
}

void Message::BrainDie(GridItemBrain*)
{
}

void Message::GridItemPlantConditionTargetKilled(GridItem*)
{
}

void Message::PuddleSpawned(BoardEntity*)
{
}

void Message::PlantPlaced(Plant*)
{
}

void Message::ChristmasProtectDestroy()
{
}

void Message::JammableGridItemAddedToBoard(GridItemJammable*)
{
}

void Message::AccountIdChanged()
{
}

void Message::OakArrowManualReload()
{
}

void Message::OakArrowAutoReload()
{
}

void Message::OakArrowTouch(int)
{
}

void Message::SnakeHandleTouchState(int)
{
}

void Message::SnakeRunOutBorderWorning()
{
}

void Message::EliminateBlocked(int, int)
{
}

void Message::BossProgressMeterUnlimited(bool)
{
}

void Message::BossSetAbsoluteFillPercentage(float)
{
}

void Message::AutoTestConfirmStartMiniGame()
{
}

void Message::ZombossIntroDone()
{
}

void Message::MowerDie(LawnMower*)
{
}

void Message::MowerCreated(LawnMower*)
{
}

void Message::MowerReset(LawnMower*)
{
}

void Message::ZombieMowed(LawnMower*)
{
}

void Message::MowerLaunched(LawnMower*)
{
}

void Message::BuyItemOK(int)
{
}

void Message::BuyItemCancel(int)
{
}

void Message::GameCharge(std::string const&, std::string const&, std::string const&)
{
}

void Message::ModuleManagerInitializedForLevelDefinition(Sexy::RtWeakPtr<LevelDefinition>&)
{
}

void Message::LoadingModuleForProps(Sexy::RtWeakPtr<LevelModuleProperties const>&)
{
}

void Message::StartButtonPressed()
{
}

void Message::MainMenuLoaded()
{
}

void Message::ProfileSelected()
{
}

void Message::GameStart()
{
}

void Message::CheckRedeemFinished(bool)
{
}

void Message::ProfileCreated(Sexy::RtWeakPtr<PlayerInfo> const&)
{
}

void Message::ProfileAboutToBeDeleted(Sexy::RtWeakPtr<PlayerInfo> const&)
{
}

void Message::IfengfengClick()
{
}

void Message::ProfileIconPictureTaken(PlayerInfo const*, Sexy::MemoryImage*)
{
}

void Message::ProfileListChanged()
{
}

void Message::LoginComplete()
{
}

void Message::NetworkProfileSyncFinish(bool)
{
}

void Message::FinishUnsyncItems()
{
}

void Message::GameReady()
{
}

void Message::BindAskForMerge(Sexy::StructuredData const*)
{
}

void Message::UpdateAccountId(Sexy::StructuredData const*)
{
}

void Message::LineUnlock(MapEventItem const*, std::string&, int)
{
}

void Message::ToturiIgnore(int)
{
}

void Message::GateUnLock(MapEventItem const*, std::string const&, int)
{
}

void Message::PlantUnLockByStar(int, std::string const&)
{
}

void Message::MissionUnlock(std::string const&)
{
}

void Message::Gift(std::string const&, int)
{
}

void Message::Recharge(std::string const&, int, int)
{
}

void Message::ItemCoinPurchase(Sexy::RtWeakPtr<MagentoProductProps> const&)
{
}

void Message::SNSFlow()
{
}

void Message::WishItem(std::string const&)
{
}

void Message::NewerBagPay(int, int)
{
}

void Message::CheckUpdateClick()
{
}

void Message::MissionDiamondUse(int, std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > > const&)
{
}

void Message::FiveYearsRushthrough(std::vector<int, std::allocator<int> > const&)
{
}

void Message::FiveYearsCosmobonus(std::vector<int, std::allocator<int> > const&)
{
}

void Message::FiveYearsExchange(std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > > const&, int)
{
}

void Message::LimitLotteryDraw(std::vector<int, std::allocator<int> > const&, std::vector<int, std::allocator<int> > const&)
{
}

void Message::GetGachaReward(int)
{
}

void Message::GetLimitedGachaReward(int, bool)
{
}

void Message::GetNewGachaReward(int)
{
}

void Message::GemCompensation(int)
{
}

void Message::RechargeBundleLog(std::string const&, int, std::string const&)
{
}

void Message::TGCraft(int, std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > > const&)
{
}

void Message::TGTutorial(int)
{
}

void Message::DailySignReward(int, int)
{
}

void Message::StartNewVersionGame()
{
}

void Message::GameLoadStart()
{
}

void Message::GameLoadEnd(std::string const&)
{
}

void Message::NewAccountRegister()
{
}

void Message::LimitedSalesBought(int, int)
{
}

void Message::LoginRewardInfo(int, int, int)
{
}

void Message::FestivalEntrance(int, int, std::string const&)
{
}

void Message::WorldMapUnLock(int, std::string const&, int)
{
}

void Message::GoldCanOpen(TreasurePool const*, std::vector<TreasureReward const*, std::allocator<TreasureReward const*> >&)
{
}

void Message::DangerRoomFinish(std::vector<PlantInfo, std::allocator<PlantInfo> >&, int, int)
{
}

void Message::DangerRoomWaveFinish(int, int)
{
}

void Message::DangerRoomWaveStart(int, int)
{
}

void Message::DangerRoomAwardGet(int)
{
}

void Message::MissionGemUse(std::string const&, int, int)
{
}

void Message::ChargePay(std::string const&, int)
{
}

void Message::GetReward(std::string const&, std::string const&)
{
}

void Message::RedPackOpen(int)
{
}

void Message::SpecificGoodsObtain(std::string const&, int)
{
}

void Message::RiddlesCorrectPercent(int)
{
}

void Message::RiddlesParticipate()
{
}

void Message::InValidAccount()
{
}

void Message::DLCRecord(int)
{
}

void Message::ChargeReward(std::string const&)
{
}

void Message::GemsCostReward(int)
{
}

void Message::LanternReward(int)
{
}

void Message::BuyTimeMetrics(std::vector<LogCacheInfo, std::allocator<LogCacheInfo> >&)
{
}

void Message::ChooseUpdateResult(int)
{
}

void Message::DownloadUpdateVersion(int)
{
}

void Message::InstallUpdateVersion(int)
{
}

void Message::GetUpdateReward()
{
}

void Message::DailyAchievement(int, int)
{
}

void Message::DangerRoomReward(int)
{
}

void Message::NationalDayConsumeDimondsInLottery(std::string const&, int)
{
}

void Message::Charge10Reward(int, int)
{
}

void Message::OldUserBackReward(int)
{
}

void Message::WechatShare()
{
}

void Message::BirthdayZReward(int)
{
}

void Message::PlantAdventure(int, PlantAdventureLogInfo const&)
{
}

void Message::DailyAccessoryBonusFinish(int)
{
}

void Message::AndroidSDKLogin(int, int)
{
}

void Message::RechargeForCukePackage(Sexy::RtWeakPtr<MagentoProductProps> const&)
{
}

void Message::CodeReward(std::string const&, std::string const&, std::vector<S2C_CodeRewardPlantNum, std::allocator<S2C_CodeRewardPlantNum> > const&)
{
}

void Message::IOSGemsReturn(int)
{
}

void Message::AndroidSDKQueryOrder(std::string const&, int)
{
}

void Message::SunProducedByShovel(int)
{
}

void Message::PlantfoodPurchased(std::string const&, int, int)
{
}

void Message::PowerupActivated(BasePowerup*, int, int)
{
}

void Message::PowerupEquipped(std::string const&)
{
}

void Message::TreasureYetiSpawned()
{
}

void Message::FirstTreasureYetiSpawned()
{
}

void Message::TreasureYetiDefeated()
{
}

void Message::LoginRewardCollection(int)
{
}

void Message::EASquaredOpened(std::string const&)
{
}

void Message::ZombieInOcean(Zombie*)
{
}

void Message::PooyanShooterTakeDamage()
{
}

void Message::PlantAttacked(Plant*, int, int)
{
}

void Message::PlantFoodStart()
{
}

void Message::PlantIcecubed(Plant*)
{
}

void Message::PlantFrost(Plant*)
{
}

void Message::PlantTryUseFood(Plant*)
{
}

void Message::PlantConditionApplied(Plant*, int)
{
}

void Message::PlantConditionEnded(Plant*, int)
{
}

void Message::PlantRevertedByCondition(Plant*, int, int)
{
}

void Message::PlantChallengeDied(Plant*)
{
}

void Message::PlantAbsorbed(Sexy::Point const&, float)
{
}

void Message::PlantFlickOffByProtectorShield(Plant*)
{
}

void Message::PlantfoodUsed(std::string const&)
{
}

void Message::PlantOnceBoostAttack(Plant*)
{
}

void Message::ZombieFlicked(Zombie*)
{
}

void Message::CanApplyPlantfood(PlantGroup*, bool*)
{
}

void Message::ApplySoccerPlantfood(PlantGroup*)
{
}

void Message::CheckBuySunManually(bool*)
{
}

void Message::PlantfoodButtonPrimed()
{
}

void Message::SunProductionTriggered(BoardEntity*)
{
}

void Message::BarbarianDestroy(Plant*)
{
}

void Message::BarbarianPlantfoodEnd(Plant*)
{
}

void Message::IceYearMonsterMoveOver(BoardEntity*)
{
}

void Message::CarMoveStarted(CarGridItem*)
{
}

void Message::CarMoveEnd()
{
}

void Message::CanMoveFlag(bool, CarGridItem*)
{
}

void Message::PlayerWin()
{
}

void Message::AccessorySaleComplete()
{
}

void Message::NotifyWhenChanged(PlantFramework*, int)
{
}

void Message::HolonutWillDie()
{
}

void Message::GridItemFireCracker(bool)
{
}

void Message::GridItemSummerFireworks(bool)
{
}

void Message::BreakFireBallOnScreen()
{
}

void Message::CopycatsSpawn(Sexy::Point const&, int)
{
}

void Message::RowMissWalrus(int)
{
}

void Message::ColMissWalrus(int)
{
}

void Message::BreakIceBallInGridRect(Sexy::TRect<int>&)
{
}

void Message::PlantFoodByGroundCherry()
{
}

void Message::MissileDropped(CarrotMissile*)
{
}

void Message::ZombieLaneChangeStarted(Zombie*)
{
}

void Message::AcornProjectileDestoryed(AcornProjectile*)
{
}

void Message::MagicCardReturn(Plant*, int)
{
}

void Message::PowerupTacticalCukeExplod()
{
}

void Message::LauncherLaunched()
{
}

void Message::LauncherSelected()
{
}

void Message::CobcannonSelected()
{
}

void Message::CobcannonLaunched()
{
}

void Message::CobcannonTappedOnCooldown()
{
}

void Message::ZombiePlantified(Zombie*)
{
}

void Message::DailyAchievementReceived(int, int)
{
}

void Message::TangleKelpSwallowedZombie(Zombie*)
{
}

void Message::BananaSelected()
{
}

void Message::BananaLaunched()
{
}

void Message::BananaTappedOnCooldown()
{
}

void Message::LilyPadDied(GridItemLilyPad*)
{
}

void Message::PuffshroomGotPlantfood(Sexy::Point const&)
{
}

void Message::MissTarget()
{
}

void Message::OakShootTouch(Sexy::Point const&)
{
}

void Message::OakArrowHitted(int, int)
{
}

void Message::OakHeadShoot(Sexy::SexyVector3 const&)
{
}

void Message::HorseBeanPlaneTurnBack(Plant*, int)
{
}

void Message::OnOliveOilDestroy(GridItemOliveOil*)
{
}

void Message::ZombieHelmDamageTaken(Zombie*, DamageInfo const&)
{
}

void Message::LauncherTappedOnCooldown()
{
}

void Message::HeroPlantGradeUp(Plant*, int)
{
}

void Message::HeroPlantTalenLevelUp(Plant*, int)
{
}

void Message::CloseIntroWidget()
{
}

void Message::AddPlantToTeam(int)
{
}

void Message::RemovePlantFromTeam(int)
{
}

void Message::ConfirmStartAdventure(bool)
{
}

void Message::TutorialClicked()
{
}

void Message::TutorialBtnPressed(int)
{
}

void Message::AdventureStart(int, bool, bool)
{
}

void Message::RefreshAdventureEditorAll()
{
}

void Message::AdventureFinished(int, bool, bool)
{
}

void Message::ExploreSurpriseBoxOpend()
{
}

void Message::RefreshAdventureEditor()
{
}

void Message::PowerupSelected(BasePowerup*)
{
}

void Message::PowerupDeselected(BasePowerup*)
{
}

void Message::ZombiePinched(Zombie*)
{
}

void Message::ShowCukeConfirm(bool)
{
}

void Message::OakArrowAdd()
{
}

void Message::NotifyPurchaseResult(bool, std::string const&, int)
{
}

void Message::NotifyRetreiveLostOrderEnd()
{
}

void Message::TideChanged(TideModule const*)
{
}

void Message::NextAvatar()
{
}

void Message::NoticeStorePlantGiftView()
{
}

void Message::NotifyFinishMotion()
{
}

void Message::TutorialFinish()
{
}

void Message::LevelUpTutorialFinishFirstStep()
{
}

void Message::RefreshCardData()
{
}

void Message::ChangeRareFilterState(int, bool)
{
}

void Message::ScrollReInitView(int)
{
}

void Message::RefreshCurrentList()
{
}

void Message::RefreshSkillButtonRender()
{
}

void Message::AutoTestPlantLevelUpOver()
{
}

void Message::AutoTestPlantUnLock()
{
}

void Message::AutoTestPlantSelected()
{
}

void Message::RefreshAvatarCardData()
{
}

void Message::SelectAvatarItem(PlantAvatarPackageItem*)
{
}

void Message::RefreshAvatarItemData()
{
}

void Message::EquipAvatar(int)
{
}

void Message::ResortSwitchButtons()
{
}

void Message::SelectTinyIcon()
{
}

void Message::SelectItemAvatar()
{
}

void Message::PatchRefresh()
{
}

void Message::NotifyPackageViewClose()
{
}

void Message::NoticeAccessoryUIClose()
{
}

void Message::RefreshOtherLevelButtons(int)
{
}

void Message::CardPlayClose()
{
}

void Message::RefreshCurrentPlantList()
{
}

void Message::FreeplantingCheatEnabled()
{
}

void Message::FreeplantingCheatDisabled()
{
}

void Message::CheatPauseEnd()
{
}

void Message::SeedChooserReady()
{
}

void Message::CheatChildrenDayNextItem()
{
}

void Message::changeAutoTestStartLevel(std::string const&)
{
}

void Message::changePlantsVsZombiesStartWorld(std::string const&)
{
}

void Message::changeAutoTestStartUnlockLevel(std::string const&)
{
}

void Message::AutoTestShowOverWinUINotify()
{
}

void Message::AutoTestShowOverLoseUINotify()
{
}

void Message::AutoTestCloseOverUINotify()
{
}

void Message::AutoTestLevelWinFinishNotify()
{
}

void Message::AutoTestLevelLoseFinishNotify()
{
}

void Message::AutoTestShowWorldPreview()
{
}

void Message::AutoTestEnterWorldMap()
{
}

void Message::AutoTestUpdateLevelUnlockState()
{
}

void Message::AutoTestClosePreviewDialog()
{
}

void Message::UniverseMapReady()
{
}

void Message::PooyanReady()
{
}

void Message::PackageContentsChanged(std::string const&)
{
}

void Message::PatchEvent(std::string const&, int)
{
}

void Message::ContentDownloaderFinished()
{
}

void Message::NewVersionFound()
{
}

void Message::SelectSeedChooserArtifactSelectWidget(int)
{
}

void Message::SelectSeedChooserHeroPlantSelectWidget(int)
{
}

void Message::NotifyToolPlantLevelUpMax(ToolPacketData*)
{
}

void Message::NotifyToolPlantfoodMax(ToolPacketData*)
{
}

void Message::SeedPacketTypeChanged(SeedPacket*)
{
}

void Message::ZombieSeedPacketSelected(SeedPacket*)
{
}

void Message::UseShovel()
{
}

void Message::HugeWave()
{
}

void Message::IntroNarrativeStarted()
{
}

void Message::AddAnimationEvent(AnimationMgr*, float*)
{
}

void Message::ZombieBlown(Zombie*)
{
}

void Message::ZombieEnterSandstorm(Zombie*)
{
}

void Message::ZombieExitSandstorm(Zombie*)
{
}

void Message::ZombieSpawnedByTent(Zombie*)
{
}

void Message::OnZombiePowderKill(Zombie*)
{
}

void Message::StarLevelChallengeStart()
{
}

void Message::StarLevelChallengeCancel()
{
}

void Message::TriggerTimeOver()
{
}

void Message::NotifyTutorialEffectEnd(int)
{
}

void Message::NotifyTutorialCheck(bool)
{
}

void Message::PopUIState()
{
}

void Message::UIEvent(UIMetrics::UIEventInfo&)
{
}

void Message::UniverseMapOpened()
{
}

void Message::TreasureYetiRemoved()
{
}

void Message::PurchaseDialogClosed()
{
}

void Message::OutroNarrativeStarted()
{
}

void Message::OnEndLevelShow()
{
}

void Message::NotifyDangerRoomReward(int, int, int)
{
}

void Message::NotifyArenaFinish()
{
}

void Message::FlagWaveTriggered(int)
{
}

void Message::FinalWave()
{
}

void Message::WaveEnded(int, WaveType::WaveType, bool)
{
}

void Message::SandstormSpawned(Zombie*)
{
}

void Message::SandstormDestroyed(Zombie*)
{
}

void Message::WorldMapTutorialFinished()
{
}

void Message::WorldMapMapPathStarted()
{
}

void Message::NotifyLoadedWorldResources()
{
}

void Message::PushUIStateAndDisableAll()
{
}

void Message::CheckValidChooseDialog()
{
}

void Message::KillChooseDialog(UIWidget*)
{
}

void Message::CheckMapChooseDialog()
{
}

void Message::ShowScrollBanner(bool)
{
}

void Message::ShowScrollBannerSwitch()
{
}

void Message::LevelPackageSelectRewardItem(int)
{
}

void Message::ZombieRiseFromGround(Zombie*)
{
}

void Message::ZombieStuckIntoGround(Zombie*)
{
}

void Message::ZombieEndWillPath(Zombie*)
{
}

void Message::ZombieCloseToBottomLine(Zombie*)
{
}

void Message::ZombieResilienceEnterBreak(Zombie*)
{
}

void Message::ZombiePlaybackAddParams(Zombie*, int)
{
}

void Message::CheckInvisibleZombie(Zombie*)
{
}

void Message::ZombieTossed(Zombie*)
{
}

void Message::BossFlashDamage()
{
}

void Message::BossSetPhasePercentage(float)
{
}

void Message::BossShowFillSpark(bool)
{
}

void Message::BossChangePhase()
{
}

void Message::takeFreezingWind()
{
}

void Message::takeSpawnShield()
{
}

void Message::zombossMechTakeDamage(std::string const&)
{
}

void Message::ZombieIceAgeChiefSpwanWind(int)
{
}

void Message::PooyanIntroHandleTouch()
{
}

void Message::SpawnPooyanShooter()
{
}

void Message::PooyanShooterKilled()
{
}

void Message::PooyanShooterChoosed()
{
}

void Message::ShovelTutorial()
{
}

void Message::PlantUpgrade()
{
}

void Message::ShoveledBesiegeBox()
{
}

void Message::FishingTutorial_CheckTouch(Sexy::Touch const&, bool*)
{
}

void Message::SkyCannonTypeSelected(int)
{
}

void Message::FishingEnergyNeedReset()
{
}

void Message::GridItemTentSpawned(GridItem*)
{
}

void Message::RestoreOriginalJam()
{
}

void Message::OverrideJamsWith(std::string const&)
{
}

void Message::SendWaveNotificationEvents(std::vector<std::string, std::allocator<std::string > > const&)
{
}

void Message::ToggleOverrideSet(std::string const&, bool)
{
}

void Message::NoticeMainUI(AccessoryContent*)
{
}

void Message::NotifyTutorialSelectContent(std::string const&)
{
}

void Message::VaseBroken(GridItemVase*)
{
}

void Message::VaseBreakerEndlessWaveComplete()
{
}

void Message::CollectableSpawnedFromVase(Collectable*)
{
}

void Message::LevelOfTheDayReplayPurchased(int, std::string const&)
{
}

void Message::ConsumptionRewardStat(bool)
{
}

void Message::GetConsumptionReward(bool)
{
}

void Message::PlantPieceCompletionClosed()
{
}

void Message::SnakeAdd()
{
}

void Message::SnakeHeadHitBody()
{
}

void Message::SnakeHitBlock()
{
}

void Message::SnakeRunOutBorder()
{
}

void Message::SnakeSlowDown()
{
}

void Message::BundleBuy(std::string const&)
{
}

void Message::EliminateColorDisappear(int, int)
{
}

void Message::EliminateFenceDestroyed(int, int, int)
{
}

void Message::RiverEntityCloseToEdge(RiverEntity*)
{
}

void Message::SpawnRiverEntity(RiverEntity*)
{
}

void Message::DodoRiderGoWithFloatingIce(float)
{
}

void Message::DodoriderJumpIntoRiver()
{
}

void Message::DodoRiderRunOutBorderWorning()
{
}

void Message::DodoriderKilled(bool)
{
}

void Message::DodoRiderDiedForIntro()
{
}

void Message::RiverCrossingHandleTouch(int)
{
}

void Message::DodoRiderDied()
{
}

void Message::DodoRiderLanding()
{
}

void Message::PlayFloatingIceCarryingAnim()
{
}

void Message::SpawnDodoRider(bool)
{
}

void Message::DodoRiderDying()
{
}

void Message::StarvingChomperEatDodorider(StarvingChomper*)
{
}

void Message::TryKillRider()
{
}

void Message::SocialLogout()
{
}

void Message::SocialLogin(int)
{
}

void Message::TotalLoginRewardReceived(int)
{
}

void Message::ProcessLoginRewardResult(int)
{
}

void Message::DailySignRewardReceived(int)
{
}

void Message::GetCurrentDailyReward()
{
}

void Message::SalesBought()
{
}

void Message::NotifyStarConverted(bool)
{
}

void Message::NotifyStarConvertBoxClosed()
{
}

void Message::NotifyLevelSelected(int)
{
}

void Message::PVPSkillBombRocketExploded(PVPSkillBombRocket*)
{
}

void Message::PVPSkillUsed(Zombie*, int)
{
}

void Message::PVPSkillEnergyChanged(int)
{
}

void Message::PVPBattleStart()
{
}

void Message::NotifyBattleEndingNetworkError()
{
}

void Message::NotifyPlantfoodUsed(Plant*)
{
}

void Message::ArenaEndingButtonPressed()
{
}

void Message::NotifyPreviewModeBegin()
{
}

void Message::PVPCurrencyChanged()
{
}

void Message::NotifyAddOtherUserZbList(long)
{
}

void Message::TrainingItemReduceClicked(TrainingItemWidget*)
{
}

void Message::PvpShopRefreshed()
{
}

void Message::PvpShopBuyFinish(int)
{
}

void Message::NotifyLostBrain(int)
{
}

void Message::ArenaPVPButtonPressed()
{
}

void Message::TriggerStartTimerOver()
{
}

void Message::ArenaOccupyButtonPressed()
{
}

void Message::ArenaStartPVPButtonPressed()
{
}

void Message::ArenaOccupyQuitButtonPressed()
{
}

void Message::ChangePlayerCooldownEnd()
{
}

void Message::NotifySwitchPlant(Plant*, int, int)
{
}

void Message::BoardStageChange(std::string const&)
{
}

void Message::ChangeSeedBankGlobalLevel(int)
{
}

void Message::SetVaseNumber(int)
{
}

void Message::UpdateCurrentTotalNumber()
{
}

void Message::AddCurrentTotalNumber(int)
{
}

void Message::DecCurrentTotalNumber(int)
{
}

void Message::SetSelectPlantOrZombie(bool)
{
}

void Message::NotifyBonusClosed()
{
}

void Message::StartLottery()
{
}

void Message::EASquaredEnabledChanged()
{
}

void Message::EASquaredBeginShowAd()
{
}

void Message::EASquaredButtonTracking(std::string const&, int, std::string const&)
{
}

void Message::EASquaredAdsAvailableChanged()
{
}

void Message::NotifyAuthResult(bool)
{
}

void Message::NotifyAuthPaymentResult(bool)
{
}

void Message::FinishItemAdd()
{
}

void Message::NotifyPurchasedDangerRoomSpecialOffer()
{
}

void Message::NotifyTutorialState(int)
{
}

void Message::TileEvent_Start()
{
}

void Message::TileEvent_Reward()
{
}

void Message::TileEvent_MiniGame()
{
}

void Message::TileEvent_BossBattle()
{
}

void Message::TileEvent_WorldLevel()
{
}

void Message::TileEvent_GuessGame()
{
}

void Message::TileEvent_ThrowAgain_Post(int, int)
{
}

void Message::TileEvent_MoveForward(int)
{
}

void Message::TileEvent_MoveForward_Index(int)
{
}

void Message::TileEvent_MoveBackward(int)
{
}

void Message::TileEvent_MoveBackward_Index(int)
{
}

void Message::TileEvent_MoveForward_Post(int)
{
}

void Message::TileEvent_MoveBackward_Post(int)
{
}

void Message::PVZ1ModeNetworkIssueDecision(int, int)
{
}

void Message::NotifyEnterMagicMirror()
{
}

void Message::NotifyEnterMagicMirror2()
{
}

void Message::CthulhuActiniaTentacleDragStart(Plant*)
{
}

void Message::CthulhuActiniaTentacleDragOver(Plant*)
{
}

void Message::CthulhuActiniaTentacleAttackOver(Plant*)
{
}

void Message::CthulhuActiniaPlantfood(Plant*)
{
}

void Message::DevilsParasiteTurnBack(Plant*, bool, bool)
{
}

void Message::ObtainedPlantWarsLeaderBoardBonus(int, int)
{
}

void Message::ObtainedPlantWarsStarReward(int, int)
{
}

void Message::SelectSeedCard(std::string const&)
{
}

void Message::AddSeedCardToTeamPanel(std::string const&)
{
}

void Message::RemoveSeedCardForTeamPanel(std::string const&)
{
}

void Message::SelectZombieCard(PlantWarsSeedCard*)
{
}

void Message::FirstRechargeButtonSelect(int)
{
}

void Message::ArtifactPrepare()
{
}

void Message::UpdatePVZ1ModeSelectLevelBonus(int, int)
{
}

void Message::UpdateSelectChallenge(int, bool)
{
}

void Message::NotifyNewPvPHowToPlayClose()
{
}

void Message::NotifyUnchartedHowToPlayClose()
{
}

void Message::NotifyPlantWarsHowToPlayClose()
{
}

void Message::NotifyUpdateTrainingWidget()
{
}

void Message::SelectChallenge(int, int, bool)
{
}

void Message::CardGameIntroEnd()
{
}

void Message::CardGamePickCardEnd()
{
}

void Message::CardGamePlayerActoinEnd()
{
}

void Message::CardGamePlayerDiscardEnd()
{
}

void Message::CardGameEnemyActionStart()
{
}

void Message::CardGameEnemyActionEnd()
{
}

void Message::CardGameRoundFinishStart()
{
}

void Message::CardGameRoundFinishEnd()
{
}

void Message::CardGameResultStart()
{
}

void Message::CardGameResultEnd()
{
}

void Message::CornucopiaBubbleGenerate()
{
}

void Message::NewTreasureBuyBundle(int)
{
}

void Message::NewTreasureBuyPrivilege()
{
}

void Message::RefreshPennyGiftBoxRank(int)
{
}

void Message::NFSLinkage7DaysLoginReward(bool, S2C_7DaysLoginReward const*)
{
}

void Message::ModifyRewardItem(int, int, int)
{
}

void Message::ToxicWaterNotifyCleanPoison()
{
}

void Message::DownloaderCompleted(std::string const&)
{
}

void Message::DownloaderCompletedAll()
{
}

void Message::DownloaderError()
{
}
