"""Compile every real .cpp under src/, diff every function against the
library, print one number.

    py -3 tools/progress.py [FILTER] [--todo] [--report P] [--check P] [--cache]

`--cache` skips recompiling unchanged units and `--jobs` raises the worker
count; a full tree pass goes from ~5 min to ~30 s with both.

Per file, scope is: every method the game gives a class the file owns (has a
strong symbol for). Scaffold stubs get their scope from units.json.
"""

import argparse
import bisect
import concurrent.futures
import datetime
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from lib import asmdiff
import config
from lib import fastcc
from lib.pvzelf import Elf

_TTY = sys.stdout.isatty() and not os.environ.get('NO_COLOR')
GREEN, RED, YELLOW, GREY, BOLD, OFF = (
    ('\033[32m', '\033[31m', '\033[33m', '\033[90m', '\033[1m', '\033[0m')
    if _TTY else ('', '', '', '', '', ''))

_COMP = re.compile(r'(\d+)')
_CACHE = False
_PCH = False


def pretty(sym):
    """Mangled -> Name::method / Name::Name / Name::~Name, no demangler."""
    s = sym
    if s.startswith('_ZNK'):
        s = s[4:]
    elif s.startswith('_ZN'):
        s = s[3:]
    else:
        return sym
    parts, i = [], 0
    while i < len(s) and s[i].isdigit():
        m = _COMP.match(s, i)
        n = int(m.group(1))
        parts.append(s[m.end():m.end() + n])
        i = m.end() + n
    if not parts:
        return sym
    tail = s[i:i + 2]
    if tail[:1] == 'C':
        parts.append(parts[-1])
    elif tail[:1] == 'D':
        parts.append('~' + parts[-1])
    elif tail == 'aS':
        parts.append('operator=')
    return '::'.join(parts)


def sources():
    root = os.path.join(config.HERE, 'src')
    return sorted(p.replace(os.sep, '/')
                  for p in glob.glob(f'{root}/**/*.cpp', recursive=True))


STUB = 'stub'


def is_stub(source):
    """True if every non-blank line is a // comment (a scaffold placeholder)."""
    try:
        with open(source, encoding='utf-8', errors='replace') as f:
            for line in f:
                s = line.strip()
                if s and not s.startswith('//'):
                    return False
    except OSError:
        return False
    return True


def compile_one(source):
    if is_stub(source):
        return source, STUB, None
    obj, err = fastcc.compile_file(source, force=not _CACHE, pch=_PCH)
    if obj is None:
        errs = [l for l in err.splitlines() if ' error: ' in l]
        return source, None, errs[:8] or [err.strip()[:400]]
    return source, obj, None


# Dev classes whose names start lowercase (the uppercase test below would drop them).
_LOWERCASE_CLASSES = {
    'androidNetworkMsgProcess', 'talkingGame', 'mutationParkourProjectile', 'cactusBoostReShoot',
    'plantInfo', 'recordData', 'targetData', 'swallZombieData', 'stMiniGame_rankItemInfo',
    'stMiniGame_rank', 'stRewardInfo', 'stThirdAwardInfo', 'stActivity_iconInfo', 'stExPlantData',
    'stExperPlantInfo', 'stSpringRewardInfo', 'st_resultInfo', 'stAward', 'stFirstChargeAward',
    'stMiniGameAward_Bonus', 'stMiniGame_Bonus', 'stThirdAward',
}
_NAMESPACES = {'Sexy', 'std', 'EA', 'eastl', '__gnu_cxx', 'EATech', '__cxxabiv1'}


def _components(sym):
    """[(name, end_offset)] for the length-prefixed parts of _ZN..."""
    s = sym
    off = 4 if s.startswith('_ZNK') else 3 if s.startswith('_ZN') else 0
    if not off:
        return []
    out = []
    i = off
    while i < len(s) and s[i].isdigit():
        m = _COMP.match(s, i)
        n = int(m.group(1))
        out.append((s[m.end():m.end() + n], m.end() + n))
        i = m.end() + n
    return out


class Owner:
    __slots__ = ('zn', 'znk', 'toplevel')

    def __init__(self, zn, znk, toplevel):
        self.zn, self.znk, self.toplevel = zn, znk, toplevel

    @property
    def prefixes(self):
        return (self.zn, self.znk)


def owned_prefixes(sym):
    """Owner(_ZN.., _ZNK.., toplevel) for sym's class, or None if sym is not
    a plain class method (namespace, template instantiation, lib type)."""
    comps = _components(sym)
    if not comps:
        return None
    marker = sym[comps[-1][1]:comps[-1][1] + 1]
    class_comps = comps if marker in ('C', 'D') else comps[:-1]
    if not class_comps:
        return None
    cls = class_comps[-1][0]
    if len(cls) < 3 or not (cls[0].isupper() or cls in _LOWERCASE_CLASSES) or cls in _NAMESPACES:
        return None
    if marker == 'I':                          # template: ...Class I<args> E
        return None
    body = sym[3 if sym.startswith('_ZN') else 4:class_comps[-1][1]]
    toplevel = len(class_comps) == 1 or class_comps[0][0] not in _NAMESPACES
    return Owner(f'_ZN{body}', f'_ZNK{body}', toplevel)


def _range(sorted_names, prefix):
    lo = bisect.bisect_left(sorted_names, prefix)
    hi = bisect.bisect_left(sorted_names, prefix + '￿', lo)
    return sorted_names[lo:hi]


# Structs whose every method emits weak (no strong symbol to key on); named
# here so their file still gets a scope. `<len><name>` mangled form.
EXTRA_OWNED = {
    '_ZN12DefenderInfo', '_ZN18S2C_PVP_BigMapInfo', '_ZN20S2C_PVP_DefenderInfo',
    '_ZN21S2C_PVP_BigMapPVPInfo',
}


# Header-only classes every includer emits: only their own file owns them, or each includer counts them again.
OWNED_BY = {
    '_ZN4Sexy8RtSerial10JsonParser13ConvertToRton': 'RtSerial.cpp', '_ZN4Sexy8RtSerial10JsonParser11InitGrammar': 'RtSerial.cpp',
    '_ZZN4Sexy8RtSerial10JsonParser11InitGrammar': 'RtSerial.cpp', '_ZZN4Sexy8RtSerial10JsonParser11ExecuteTree': 'RtSerial.cpp',
    '_ZN4Sexy8SexyMath': 'CurvedVal.cpp',
    '_ZN4Sexy21NullAchievementDriver': 'IAchievementDriver.cpp',
    '_ZN4Sexy17IResStreamsDriver12TaskResource': 'BaseResStreamsDriver.cpp', '_ZN4Sexy17IResStreamsDriver4Task': 'NetworkMsgProcess.cpp',
    '_ZN4Sexy15IPurchaseDriver7Product': 'MagentoService.cpp',
    '_ZN4Sexy4RtId': 'RtId.cpp',
    '_ZN4Sexy18RtSerialRtonWriter': 'RtSerialRtonWriter.cpp',
    '_ZN11JamListener': 'JamListener.cpp', '_ZN4Sexy17IResStreamsDriver': 'IResStreamsDriver.cpp', '_ZNK4Sexy17IResStreamsDriver': 'IResStreamsDriver.cpp',
    '_ZN4Sexy20BaseResStreamsDriver': 'BaseResStreamsDriver.cpp',
    # header-only classes, owned by the real file that uses them
    '_ZN18New_S2C_RedPackSth': 'CommonUIManager.cpp',
    '_ZN15New_S2C_Lottery': 'ActivityManager.cpp',
    '_ZN5Board17SpawnZombieParams': 'Board.cpp',
    '_ZN5Board14MissionEndItem': 'Board.cpp',
    '_ZN17GridItemTrackInfo': 'Board.cpp',
    '_ZN4Sexy8RtSerial10JsonParser11FeastClient': 'RtSerial.cpp',
    '_ZN4Sexy8RtSerial10JsonParser': 'RtSerial.cpp',
    '_ZN8TimeLine7Updater': 'LinkedTilePropagationInfo.cpp',
    '_ZN8TimeLine': 'LinkedTilePropagationInfo.cpp',
    '_ZN13TimeLineEvent': 'LinkedTilePropagationInfo.cpp',
    '_ZN18GridItemRecordInfo': 'PVZ1KlotskiModule.cpp',
    '_ZN4Sexy23AndroidRenderDeviceES20': 'AndroidGL20RenderEffect.cpp',
    '_ZN4Sexy11GLTexHolder': 'AndroidGL20RenderEffect.cpp',
    '_ZN11UUIDCreator': 'PlayerIdentityService.cpp',
    '_ZN11open_vcdiff26VCDiffStreamingEncoderImpl': 'VCDiffStreamingEncoder.cpp',
    '_ZN12EATextSquish4Vec3': 'Zombie.cpp',
    '_ZN12EATextSquish6Sym3x3': 'EATextSquish.cpp',
    '_ZN4Sexy15ResourceManager11PreLoadTask': 'ResourceManager.cpp',
    '_ZN4Sexy15ResourceManager15GetImageOptions': 'PopAnim.cpp',
    '_ZN4Sexy24PrimeTextExtraParameters': 'PrimeAllocator.cpp',
    '_ZN4Sexy12PAObjectInst': 'PopAnimRig.cpp',
    '_ZN4Sexy11PAObjectDef': 'PopAnimRig.cpp',
    '_ZN4Sexy7PAImage': 'PopAnimRig.cpp',
    '_ZN4Sexy7PAFrame': 'PopAnimRig.cpp',
    '_ZN4Sexy9PACommand': 'PopAnimRig.cpp',
    '_ZN4Sexy15SexyMathHermite6SPoint': 'CurvedVal.cpp',
    '_ZN4Sexy15SexyMathHermite': 'CurvedVal.cpp',
    '_ZN4Sexy9CurvedVal16CurveCacheRecord': 'CurvedVal.cpp',
    '_ZN4Sexy20ScrollWidgetListener': 'NetworkMsgProcess.cpp',
    '_ZN4Sexy14ButtonListener': 'RechargeRewardDisplayer.cpp',
    '_ZN4Sexy22AndroidHttpTransaction20ReceivedDataCallback': 'AndroidHttpTransaction.cpp',
    '_ZN4Sexy23AndroidGL20RenderEffect9ParamData': 'AndroidGL20RenderEffect.cpp',
    '_ZN4Sexy23AndroidGL20RenderEffect15ParamCollection': 'AndroidGL20RenderEffect.cpp',
    '_ZN4Sexy17AndroidGL20Vertex': 'Zombie.cpp',
    '_ZN4Sexy12SexyVertex2D': 'Zombie.cpp',
    '_ZN4Sexy17AndroidFileSearch': 'AndroidAsyncIOFile.cpp',
    '_ZN4Sexy17IResStreamsDriver4Task': 'NetworkMsgProcess.cpp',
    '_ZN4Sexy17AndroidDecodeTask': 'NetworkMsgProcess.cpp',
    '_ZN14DTouchListener': 'DTouchEventDispatcher.cpp',
    '_ZN19RichmanGameSaveData': 'PlayerInfo.cpp',
    '_ZN26RichmanBattleEventSaveData': 'PlayerInfo.cpp',
    '_ZN15RichmanItemInfo': 'PlayerInfo.cpp',
    '_ZN17HeroPlantSaveInfo': 'Board.cpp',
    '_ZN30DangerRoomSpecialOfferSaveData': 'PlayerInfo.cpp',
    '_ZN23ArtifactCameraSubSystem11CaptureSave': 'ArtifactCameraSubSystem.cpp',
    '_ZN11PlantAvatar': 'PVZTypes.cpp',
    '_ZN14IDataPersistor': 'NetworkMsgProcess.cpp',
    '_ZN21TGAExchangeAvatarData': 'NetworkMsgProcess.cpp',
    '_ZN14ICloudListener': 'NetworkMsgProcess.cpp',
    '_ZN20ICloudWrapperFactory': 'DataPersistorObjectsFactory.cpp',
    '_ZN13ICloudWrapper': 'PlayerIdentityService.cpp',
    '_ZN10RiftStatus': 'RiftUtils.cpp',
    '_ZN8ImageLib12ErrorHandler': 'ImageLib.cpp',
    '_ZN23GeneralTaskStateManager': 'ActivityManager.cpp',
    '_ZN14WorldMapEditor': 'NetworkMsgProcess.cpp',
    '_ZN13PowerupRecord': 'PlayerInfo.cpp',
    '_ZN35GridItemZombieMirrorQueenMirrorUnit': 'GameObject.cpp',
    '_ZN32GridItemCardGameZombieActionData': 'GridItemCardGameZombie.cpp',
    '_ZN27GridItemPlacementProperties': 'InitialGridItemPlacer.cpp',
    '_ZN17GridItemLevelStat': 'GridItemRailcart.cpp',
    '_ZN33GridItemCardGameTowerGenerateData': 'StateMachineTableBuilder.cpp',
    '_ZNK12LawnKeyField': 'PlayerInfo.cpp',
    '_ZN12LawnKeyField': 'PlayerInfo.cpp',
    '_ZN9ScaledApp': 'LawnDialog.cpp',
    '_ZN14RunnableAction': 'NetworkMsgProcess.cpp',
    '_ZNK10Renderable': 'BeachStage.cpp',
    '_ZN10Renderable': 'BeachStage.cpp',
    '_ZN12ActionRunner': 'NetworkMsgProcess.cpp',
    '_ZNK4Sexy18PopTransformMatrix': 'PopAnim.cpp',
    '_ZN4Sexy18PopTransformMatrix': 'PopAnim.cpp',
    '_ZN4Sexy10PopAnimDef': 'PopAnim.cpp',
    '_ZN4Sexy11PAObjectPos': 'PopAnim.cpp',
    '_ZN19TGAClearProfileData': 'androidNetworkMsgProcess.cpp',
    '_ZN24ProfileConversionResults11LevelChange': 'PlayerInfo.cpp',
    '_ZN24ProfileConversionResults': 'PlayerInfo.cpp',
    '_ZN18PlantNewAvatarInfo': 'PlayerInfo.cpp',
    '_ZN21PlantAvatarPiecesInfo': 'PlayerInfo.cpp',
    '_ZN15PlantAvatarInfo': 'PlayerInfo.cpp',
    '_ZN19GiftPlantAvatarData': 'StoreGiftConfig.cpp',
    '_ZN19AccessoryAvatarInfo': 'PlantAccessoryPropertySheet.cpp',
    '_ZN27ACLOG_PlantAvatarPiecesInfo': 'androidNetworkMsgProcess.cpp',
    '_ZN21ACLOG_PlantAvatarInfo': 'androidNetworkMsgProcess.cpp',
    '_ZN14New_S2C_Reward': 'New_S2C_GiftBoxReward.cpp',
    '_ZN14FakeHttpDriver': 'LawnApp.cpp',
    '_ZN17GridItemPoolEntry': 'SpawnGravestonesWaveAction.cpp',
    '_ZN22GridItemConditionEntry': 'GridItemAction.cpp',
    '_ZN8AutoLock': 'NetworkMsgProcess.cpp',
    '_ZN17LootEntrySaveData': 'LootSaveData.cpp',
    '_ZN10AwardEntry': 'AwardDiffSet.cpp',
    '_ZN10BoostValue': 'UnchartedBoostMgr.cpp',
    '_ZN10BoxContent': 'PVZVersion.cpp',
    '_ZN10BundleInfo': 'OfferBundleConfig.cpp',
    '_ZN10BundleItem': 'RechargeBundleConfig.cpp',
    '_ZN10CannonData': 'FishingProperties.cpp',
    '_ZN10CardUIInfo': 'Card.cpp',
    '_ZN10ChargeInfo': 'ZombieBumperCar.cpp',
    '_ZN10Chickening': 'Zombie_Chicken_Subsystem.cpp',
    '_ZN10CommonData': 'Artifact.cpp',
    '_ZN10CustomWave': 'CustomLevelMgr.cpp',
    '_ZN10DragonInfo': 'ArtifactDragonSubsystem.cpp',
    '_ZN10EggContent': 'PVZVersion.cpp',
    '_ZN10FriendInfo': 'SocialInfo.cpp',
    '_ZN10GiftBundle': 'ActivityCollectionUIFutureGiftBox.cpp',
    '_ZN10IdNameInfo': 'LawnApp.cpp',
    '_ZN10MapArtAnim': 'MapEditor.cpp',
    '_ZN10PirateLane': 'CannonMinigame.cpp',
    '_ZN10PlantBoost': 'PlantFamilyMgr.cpp',
    '_ZN10PlantCache': 'ZombieAirbubble.cpp',
    '_ZN10PoisonInfo': 'ConvallariaChemistProjectile.cpp',
    '_ZN10PoolResult': 'DailyAchievementInfo.cpp',
    '_ZN10PotionData': 'ZombiePotionAction.cpp',
    '_ZN10PresetCard': 'CardGameModule.cpp',
    '_ZN10PullZombie': 'ZombiePull_SubSystem.cpp',
    '_ZN10RandRecord': 'EffectAnimRig_EndLevelBox.cpp',
    '_ZN10Reflection11RCustomType15IStdManipulator': 'Reflection.cpp',
    '_ZN10Reflection17IRefSymbolBuilder': 'Reflection.cpp',
    '_ZN10Reflection20CRefAttributeVariant': 'Reflection.cpp',
    '_ZN10Reflection23CRefManualSymbolBuilder': 'Reflection.cpp',
    '_ZN10Reflection6RClass13CPreAttribute': 'Reflection.cpp',
    '_ZN10RenderItem': 'RenderQueue.cpp',
    '_ZN10RewardItem': 'ItemButton.cpp',
    '_ZN10ScreenInfo': 'ShareDriverMgr.cpp',
    '_ZN10ShopBundle': 'FutureGiftBoxData.cpp',
    '_ZN10SortedKern': 'FontData.cpp',
    '_ZN10SteadyNeed': 'PlantAccessoryPropertySheet.cpp',
    '_ZN10TDRoadData': 'TowerDefendModule.cpp',
    '_ZN10TGABagData': 'TGALogMgr.cpp',
    '_ZN10TheDayItem': 'LevelOfTheDayConfigInfo.cpp',
    '_ZN10UBoostInfo': 'Plant.cpp',
    '_ZN10ValueRange': 'DangerRoomLevelDesignerHelpers.cpp',
    '_ZN10WormRecord': 'WormHoleSubsystem.cpp',
    '_ZN10ZombieGift': 'AssetsManagerEx.cpp',
    '_ZN10ZombieInfo': 'PVZVersion.cpp',
    '_ZN10ZombieMove': 'OrchidMageSubsystem.cpp',
    '_ZN10recordData': 'AssetsManagerEx.cpp',
    '_ZN10targetData': 'AquaVinePFProjectile.cpp',
    '_ZN11BagItemData': 'gnu_cxxFunctions.cpp',
    '_ZN11BesiegeGrid': 'BesiegeProperties.cpp',
    '_ZN11BlownZombie': 'ZombieBlower_SubSystem.cpp',
    '_ZN11ConvertItem': 'StarConvertObject.cpp',
    '_ZN11DefaultWave': 'CustomLevelMgr.cpp',
    '_ZN11DropImpInfo': 'DropShipEffectAnim.cpp',
    '_ZN11DungeonInfo': 'PlayerInfo.cpp',
    '_ZN11EmptyDialog': 'NewPVPBattlePassLotteryPanel.cpp',
    '_ZN11EventConfig': 'RichManUIMgr.cpp',
    '_ZN11EventReward': 'RichManUIMgr.cpp',
    '_ZN11FanCardData': 'DangerRoomStatScreen.cpp',
    '_ZN11FileWrapper': 'RSBPatcher.cpp',
    '_ZN11FishingPath': 'FishingModuleEditor.cpp',
    '_ZN11GachaReward': 'AssetsManagerEx.cpp',
    '_ZN11GameSetInfo': 'StatueMazeModule.cpp',
    '_ZN11IMEDelegate': 'DTextField.cpp',
    '_ZN11LogItemInfo': 'AssetsManagerEx.cpp',
    '_ZN11LotteryCard': 'LotteryUI.cpp',
    '_ZN11LotteryInfo': 'NetworkWebCallLottery.cpp',
    '_ZN11MapListNode': 'WorldMapUtils.cpp',
    '_ZN11MissionInfo': 'PlayerInfo.cpp',
    '_ZN11NextPopData': 'AccountRemove.cpp',
    '_ZN11PVPZoneData': 'PVPMapUI.cpp',
    '_ZN11PakFileDesc': 'PakInterface.cpp',
    '_ZN11PaymentInfo': 'PurchaseBroker.cpp',
    '_ZN11PieceConfig': 'EventUIPropertySheet.cpp',
    '_ZN11PlantAction': 'Plant_IcyCurrant.cpp',
    '_ZN11PoolContent': 'PVZVersion.cpp',
    '_ZN11PvpShopInfo': 'PlayerInfo.cpp',
    '_ZN11RateOfRares': 'TransGenosisUI.cpp',
    '_ZN11RisedZombie': 'ArtifactUFOSubSystem.cpp',
    '_ZN11S2C_Profile': 'S2C_ICloud_GetProfile.cpp',
    '_ZN11SalesObject': 'PlayerInfo.cpp',
    '_ZN11SpeedFactor': 'ArtifactShieldProperties.cpp',
    '_ZN11TGAArborDay': 'TGALogMgr.cpp',
    '_ZN11TGAFoolData': 'TGALogMgr.cpp',
    '_ZN11TitleStatus': 'Zombie.cpp',
    '_ZN11WarningData': 'Board.cpp',
    '_ZN11WidgetRects': 'WidgetDebugPosition.cpp',
    '_ZN11WorldReward': 'RebateRewardConfig.cpp',
    '_ZN11ZSEntryList': 'SimpleZombieSpawner.cpp',
    '_ZN11ZombieDance': 'Zombie_Piano_Subsystem.cpp',
    '_ZN11_NetWorkMsg': 'NetworkMsgProcess.cpp',
    '_ZN11open_vcdiff15RollingHashUtil': 'open_vcdiff.cpp',
    '_ZN11open_vcdiff18DeltaWindowSection': 'VCDiffDeltaFileWindow.cpp',
    '_ZN11open_vcdiff21OutputStringInterface': 'open_vcdiff.cpp',
    '_ZN11open_vcdiff24CodeTableWriterInterface': 'VCDiffCodeTableWriter.cpp',
    '_ZN11open_vcdiff9BlockHash5Match': 'BlockHash.cpp',
    '_ZN12ADServerInfo': 'ADManager.cpp',
    '_ZN12ArtifactData': 'ArtifactMgr.cpp',
    '_ZN12ArtifactInfo': 'PlayerInfo.cpp',
    '_ZN12BirthZRecord': 'PVZVersion.cpp',
    '_ZN12BlendSrcData': 'PopAnim.cpp',
    '_ZN12BundleDetail': 'RechargeBundleUI.cpp',
    '_ZN12BuyOfferInfo': 'NetworkBuyOfferInfo.cpp',
    '_ZN12CheckRsbInfo': 'AssetsManagerEx.cpp',
    '_ZN12ComboBracket': 'CannonMinigameModule.cpp',
    '_ZN12DNodeCreator': 'DTransformNodeCreator.cpp',
    '_ZN12DRefAutoLock': 'DRef.cpp',
    '_ZN12DStringBlock': 'DString.cpp',
    '_ZN12DefenderInfo': 'PVPDatas.cpp',
    '_ZN12DownloadPath': 'AssetsManagerEx.cpp',
    '_ZN12DownloadUnit': 'AssetsManagerEx.cpp',
    '_ZN12ELevelConfig': 'PVZVersion.cpp',
    '_ZN12EditorButton': 'MapEditor.cpp',
    '_ZN12EndLevelData': 'RiftNetworkMgr.cpp',
    '_ZN12EntityFinder17BoardEntitySorter': 'EntityFinder.cpp',
    '_ZN12EntityTarget': 'Plant_Flamelady.cpp',
    '_ZN12EventMetrics': 'Message.cpp',
    '_ZN12GameItemInfo': 'GameResourceUtil.cpp',
    '_ZN12GameRankInfo': 'UITourismOctober.cpp',
    '_ZN12GameRankItem': 'UITourismOctober.cpp',
    '_ZN12JVMDataCache': 'RuntimeSymbols.cpp',
    '_ZN12LegendReward': 'NetworkLeaderboardInfo.cpp',
    '_ZN12LogCacheInfo': 'AssetsManagerEx.cpp',
    '_ZN12LotteryBonus': 'AdsLotteryPanel.cpp',
    '_ZN12MapPathGroup': 'TimeTravelSelEntranceUI.cpp',
    '_ZN12MatrixPusher': 'Board.cpp',
    '_ZN12MiniGameData': 'MiniGameCollectionUtils.cpp',
    '_ZN12ModuleConfig': 'CustomLevelConfig.cpp',
    '_ZN12MutatorTable': 'LevelMutatorModule.cpp',
    '_ZN12NewYearGoods': 'NewYearGoodsData.cpp',
    '_ZN12PVPSeedPlant': 'PVZVersion.cpp',
    '_ZN12PVPSeedSkill': 'PVZVersion.cpp',
    '_ZN12PVZ2UIDialog12DialogConfig': 'PVZ2UIDialog.cpp',
    '_ZN12PlantMetrics': 'PVZVersion.cpp',
    '_ZN12PlantRequire': 'AdventureTeamEditorUI.cpp',
    '_ZN12PlantTrialCD': 'PlayerInfo.cpp',
    '_ZN12PlantfoodGet': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN12ProfileUtils21ChallengeStatusHolder': 'BoardHelpers.cpp',
    '_ZN12PurchaseInfo': 'PlayerInfo.cpp',
    '_ZN12RailCartInfo': 'CustomLevelMgr.cpp',
    '_ZN12RailcartRail': 'RailcartProperties.cpp',
    '_ZN12RechargeInfo': 'MetricsCollector.cpp',
    '_ZN12RenderDataEx': 'SeedPacketUtils.cpp',
    '_ZN12RiftPerkData': 'PennyPerkMgr.cpp',
    '_ZN12S2C_ItemInfo': 'S2C_CurrencyInfo.cpp',
    '_ZN12S2C_UserInfo': 'S2C_ICloud_GetPlayerInfo.cpp',
    '_ZN12ServerItemID': 'ServerPlantID.cpp',
    '_ZN12SexyAllocMap': 'SexyAppBase.cpp',
    '_ZN12ShieldRecord': 'GridItemZombieBuffTileShield.cpp',
    '_ZN12SnowBallData': 'WaveActionSnowBall.cpp',
    '_ZN12StarRateInfo': 'StarRateProps.cpp',
    '_ZN12SunOwnerLink': 'ZombieRaSubsystem.cpp',
    '_ZN12SurpriseInfo': 'PlantAdventureConfig.cpp',
    '_ZN12TGAAppLaunch': 'TGALogMgr.cpp',
    '_ZN12TGACrackData': 'TGALogMgr.cpp',
    '_ZN12TGAGoldenEgg': 'TGALogMgr.cpp',
    '_ZN12TGAPlantData': 'TGALogMgr.cpp',
    '_ZN12TodAllocator': 'GlobalFunctions.cpp',
    '_ZN12TossedZombie': 'ZombieTosser_SubSystem.cpp',
    '_ZN12TreasurePool': 'LMMessageRouter.cpp',
    '_ZN12TrialLogData': 'AssetsManagerEx.cpp',
    '_ZN12TutorialCard': 'CardGameModule.cpp',
    '_ZN12WaveWindInfo': 'HeianWindModule.cpp',
    '_ZN12WorldCupInfo': 'PlayerInfo.cpp',
    '_ZN12ZombieRecord': 'MetricsCollector.cpp',
    '_ZN12ZombossStage': 'ZombieZombossMech.cpp',
    '_ZN12fastdelegate15DelegateMemento': 'Typesetter.cpp',
    '_ZN12stRewardInfo': 'ChagreDoubleFesivalConfig.cpp',
    '_ZN12stThirdAward': 'UIChagreDouble.cpp',
    '_ZN13BlockedZombie': 'MorningGloryPFProjectile.cpp',
    '_ZN13BundleDisplay': 'PlayerInfo.cpp',
    '_ZN13ChallengeInfo': 'LevelUtils.cpp',
    '_ZN13ConsoleAction': 'CommandConsole.cpp',
    '_ZN13ConvertObject': 'StarConvertObject.cpp',
    '_ZN13CustomSegment': 'TGALogMgr.cpp',
    '_ZN13DTimerManager13DTimerElement': 'DTimerManager.cpp',
    '_ZN13DaveClubBonus': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN13DiscountPlant': 'ActivityConfig.cpp',
    '_ZN13DropGroupNode': 'ActivityDropGroup.cpp',
    '_ZN13EventUIConfig': 'EventUIPropertySheet.cpp',
    '_ZN13FShopItemData': 'FShopItemContent.cpp',
    '_ZN13FishingModule10ZombieInfo': 'FishingModule.cpp',
    '_ZN13FogMovingData': 'FairyTaleFogSubSystem.cpp',
    '_ZN13GachaItemInfo': 'GachaMgr.cpp',
    '_ZN13GachaRewardUI': 'GachaUI.cpp',
    '_ZN13GiftPlantData': 'AssetsManagerEx.cpp',
    '_ZN13GoldenEggData': 'ActivityConfig.cpp',
    '_ZN13GoldenEggInfo': 'PlayerInfo.cpp',
    '_ZN13GridItemspear12AttackMatrix': 'GridItemspear.cpp',
    '_ZN13HardAwardItem': 'EffectAnimRig_EndLevelBox.cpp',
    '_ZN13HardLevelData': 'HardLevelConfig.cpp',
    '_ZN13HintBonusInfo': 'HintUI.cpp',
    '_ZN13LevelLostInfo': 'PlayerInfo.cpp',
    '_ZN13LocalAuthInfo': 'AuthMgr.cpp',
    '_ZN13MapRenderItem': 'WorldMap.cpp',
    '_ZN13MessageRouter16AddRemoveRequest': 'MessageRouter.cpp',
    '_ZN13MistImageInfo': 'NewPVPAreaMist.cpp',
    '_ZN13PVPSeedZombie': 'PVZVersion.cpp',
    '_ZN13PVPZombieData': 'PVPManager.cpp',
    '_ZN13PieceDropData': 'ActivityConfig.cpp',
    '_ZN13PlacementInfo': 'CustomLevelMgr.cpp',
    '_ZN13PlantAddition': 'Plant.cpp',
    '_ZN13PlantGeneInfo': 'PlayerInfo.cpp',
    '_ZN13PlantGiftData': 'ActivityConfig.cpp',
    '_ZN13PlantPowerSet': 'JoustPlantPowerConfig.cpp',
    '_ZN13PlaybackBrief': 'PlaybackData.cpp',
    '_ZN13PoisonGumInfo': 'GumPoisonSubsystem.cpp',
    '_ZN13PresentDetail': 'NewerPresentMgr.cpp',
    '_ZN13PresentRecord': 'Board.cpp',
    '_ZN13RayEntityData': 'Plant_HocusCrocus.cpp',
    '_ZN13RedPacketData': 'NetworkRedPacketReward.cpp',
    '_ZN13RewardContent': 'DailyAchievement.cpp',
    '_ZN13RiftAwardInfo': 'AdaptorRiftLevelSetup.cpp',
    '_ZN13RiftBonusInfo': 'AdaptorRiftLevelSetup.cpp',
    '_ZN13S2C_BonusInfo': 'PurchaseBroker.cpp',
    '_ZN13S2C_DailySign': 'S2C_ICloud_SignReward.cpp',
    '_ZN13S2C_GachaInfo': 'S2C_ICloud_GetGachaInfo.cpp',
    '_ZN13StabbedZombie': 'ZombieStabber_SubSystem.cpp',
    '_ZN13StatementData': 'BattleStatementUI.cpp',
    '_ZN13StatueMazeSet': 'CustomLevelMgr.cpp',
    '_ZN13TGANewPVPData': 'AdaptorNewPVPEntryScreen.cpp',
    '_ZN13TGAOnlineData': 'TGALogMgr.cpp',
    '_ZN13TagColorValue': 'CardGameBoardConfig.cpp',
    '_ZN13WaveEventData': 'Wave.cpp',
    '_ZN13WorldMapAsset': 'WorldMap.cpp',
    '_ZN13WorldPackInfo': 'PlayerInfo.cpp',
    '_ZN13ZombieWarning': 'PlayerInfo.cpp',
    '_ZN13stExPlantData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN13st_resultInfo': 'SoccerGameWinOutro.cpp',
    '_ZN14AccessoryPiece': 'NetworkProfileMgr.cpp',
    '_ZN14AkInitSettings': 'WwiseInteractiveAudioDriver.cpp',
    '_ZN14AnimCountCache': 'PopAnimRig.cpp',
    '_ZN14ArenaPlantInfo': 'ArenaInfo.cpp',
    '_ZN14AwardDiffEntry': 'AwardDiffSet.cpp',
    '_ZN14BeeTargetEntry': 'PlantMaybeeSubSystem.cpp',
    '_ZN14BossFightBonus': 'PVZVersion.cpp',
    '_ZN14BuffShieldData': 'BuffShieldSubsystem.cpp',
    '_ZN14BundleTypeList': 'RechargeBundleConfig.cpp',
    '_ZN14BundleUIDetail': 'RechargeBundleUI.cpp',
    '_ZN14CAkFileHelpers': 'SexyIOHookBlocking.cpp',
    '_ZN14CardBuffObject': 'CardBuffTracker.cpp',
    '_ZN14CollectedPiece': 'Board.cpp',
    '_ZN14CollectionInfo': 'PlayerInfo.cpp',
    '_ZN14ConsoleContext': 'CommandConsole.cpp',
    '_ZN14CursorAnimData': 'CardTargetCursor.cpp',
    '_ZN14CustomRailInfo': 'CustomLevelMgr.cpp',
    '_ZN14CustomWaveData': 'CustomLevelMgr.cpp',
    '_ZN14CustomWaveWind': 'CustomLevelMgr.cpp',
    '_ZN14DActionManager12DActionDelay': 'DActionManager.cpp',
    '_ZN14DActionManager14DActionElement': 'DActionManager.cpp',
    '_ZN14DailySignBonus': 'DailySignActivityScrollPanel.cpp',
    '_ZN14DamageBalancer': 'Zombie.cpp',
    '_ZN14DistFromSorter': 'ZombieSpawnActionDefinition.cpp',
    '_ZN14DynamicPadding': 'HotUIWidget.cpp',
    '_ZN14EntityWormData': 'WormHoleSubsystem.cpp',
    '_ZN14EntrySortValue': 'AdaptorSeedPacketEntry.cpp',
    '_ZN14GAME_ITEM_INFO': 'NetworkMsgProcess.cpp',
    '_ZN14GachaPriceInfo': 'LawnApp.cpp',
    '_ZN14GameMatrixInfo': 'StatueMazeModule.cpp',
    '_ZN14GemRequestInfo': 'S2C_SubGemRequest.cpp',
    '_ZN14IceShroomProps11AdvanceInfo': 'IceShroomProps.cpp',
    '_ZN14IceShroomProps21IceShroomGrowthStates': 'Plant_IceShroom.cpp',
    '_ZN14InvitationInfo': 'InvitationData.cpp',
    '_ZN14InvitationTask': 'UIInvitationMgr.cpp',
    '_ZN14JoustBonusInfo': 'JoustUtils.cpp',
    '_ZN14LevelScoreItem': 'UITourismOctober.cpp',
    '_ZN14LootTableEntry': 'LootHelpers.cpp',
    '_ZN14LotteryHistory': 'UITourismOctober.cpp',
    '_ZN14MatchPlantData': 'UITourismOctober.cpp',
    '_ZN14NFSLinkageTask': 'NFSLinkageData.cpp',
    '_ZN14NameMapperBase': 'NameMapperBase.cpp',
    '_ZN14PlantAttribute': 'Plant.cpp',
    '_ZN14PlantCacheData': 'NewPVPGameSubsystem.cpp',
    '_ZN14PlantLevelStat': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN14PlantNameArray': 'ActivityConfig.cpp',
    '_ZN14PlantPowerData': 'JoustGameModule.cpp',
    '_ZN14PlantStarLevel': 'PlayerInfo.cpp',
    '_ZN14PlayerFlagInfo': 'UITourismOctober.cpp',
    '_ZN14PowerTileEntry': 'CustomLevelElementsTemplate.cpp',
    '_ZN14PushZombieData': 'HeianTornado.cpp',
    '_ZN14RandZombieInfo': 'RandZombieProperties.cpp',
    '_ZN14RecallItemInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN14RechargeReward': 'RechargeRewardConfig.cpp',
    '_ZN14RedPackContent': 'RedPacketRewardInfo.cpp',
    '_ZN14RedeemRewardUI7KeyInfo': 'PVZVersion.cpp',
    '_ZN14ResilienceInfo': 'Zombie.cpp',
    '_ZN14RewardItemData': 'AssetsManagerEx.cpp',
    '_ZN14RiftBossReward': 'NetworkMainEntryInfo.cpp',
    '_ZN14RiftPlayerData': 'AdaptorRiftLeaderBoardScreen.cpp',
    '_ZN14S2C_NoticeInfo': 'BoardDlg.cpp',
    '_ZN14S2C_ProfileMD5': 'S2C_ICloud_GetProfileMD5.cpp',
    '_ZN14S2C_RedPackSth': 'S2C_RedPackReward.cpp',
    '_ZN14SeedPacketInfo': 'AdaptorSeedPacketEntry.cpp',
    '_ZN14SunshroomProps21SunshroomGrowthStates': 'PVZVersion.cpp',
    '_ZN14SupplymentInfo': 'NewPVPAreaMist.cpp',
    '_ZN14TGAFightZodiac': 'TGALogMgr.cpp',
    '_ZN14TGALuckBagData': 'PlayerInfo.cpp',
    '_ZN14TGAPigBankData': 'TGALogMgr.cpp',
    '_ZN14TGARichManData': 'RichManUIMgr.cpp',
    '_ZN14TGASecretGacha': 'TGALogMgr.cpp',
    '_ZN14TGASecretStore': 'TGALogMgr.cpp',
    '_ZN14TestDragonInfo': 'TestDragon.cpp',
    '_ZN14TitleIconState': 'Zombie.cpp',
    '_ZN14TreasureReward': 'LMMessageRouter.cpp',
    '_ZN14TutorialEntity': 'PVZVersion.cpp',
    '_ZN14ZMatchShopData': 'ZShopItemWidget.cpp',
    '_ZN14ZombieDropData': 'HeianSmokeBomb.cpp',
    '_ZN14ZombiePushInfo': 'PlantShadowShroomSubSystem.cpp',
    '_ZN14ZombieSpawnLoc': 'IntroCinema.cpp',
    '_ZN14ZombieSwapData': 'AssetsManagerEx.cpp',
    '_ZN14ZombieTentData': 'WaveActionZombieTent.cpp',
    '_ZN15AccessoryUIInfo': 'PlantAccessoryMgr.cpp',
    '_ZN15AchievementInfo': 'AndroidAchievementDriverMgr.cpp',
    '_ZN15AchievementItem': 'DailyAchievement.cpp',
    '_ZN15AdventurePlants': 'PlayerInfo.cpp',
    '_ZN15AkChannelConfig': 'WwiseInteractiveAudioDriver.cpp',
    '_ZN15AndroidAppEvent': 'AndroidAppDriver.cpp',
    '_ZN15BarrageWaveInfo': 'Effect_Barrage.cpp',
    '_ZN15CardPreviewInfo': 'CardPreview.cpp',
    '_ZN15ChooserItemData': 'UINewPVPSeedChooser.cpp',
    '_ZN15ColorDataVector': 'MonthlyCardMgr.cpp',
    '_ZN15CountdownAdvice': 'PlayerInfo.cpp',
    '_ZN15CurrentDrawInfo': 'GachaMgr.cpp',
    '_ZN15CustomWaveEvent': 'CustomLevelMgr.cpp',
    '_ZN15DailyAwardBonus': 'ChristmasAwardActivityScrollPanel.cpp',
    '_ZN15DailyRewardData': 'PVZVersion.cpp',
    '_ZN15DropOutItemData': 'PVZVersion.cpp',
    '_ZN15DynamicSizeData': 'HotUIWidget.cpp',
    '_ZN15EliteModuleBase': 'ZombieEliteModule.cpp',
    '_ZN15EntityCondition': 'GridItem.cpp',
    '_ZN15EnvironmentAnim': 'PVZVersion.cpp',
    '_ZN15EventZombieData': 'EventZombieWaveData.cpp',
    '_ZN15FireCrackerData': 'NewYearFireCrackerWaveAction.cpp',
    '_ZN15GachaRewardItem': 'ActiveChristmasLotteryTab.cpp',
    '_ZN15GameplayMetrics': 'MetricsCollector.cpp',
    '_ZN15GarlicStateInfo': 'Plant_Garlic.cpp',
    '_ZN15GeneralSaleProp': 'ActivityConfig.cpp',
    '_ZN15GeneratorValues': 'ZombieElecShieldGenerator.cpp',
    '_ZN15HeianWindRecord': 'ArtifactWind.cpp',
    '_ZN15HeroPlantTalent': 'HeroPlantFramework.cpp',
    '_ZN15IWeightedOption': 'WeightedOptionStubForRt.cpp',
    '_ZN15LinkedTileEntry': 'FutureStage.cpp',
    '_ZN15LogGameItemData': 'MetricsCollector.cpp',
    '_ZN15LogPurchaseInfo': 'MetricsCollector.cpp',
    '_ZN15LotteryItemInfo': 'LotteryItem.cpp',
    '_ZN15MapTutorialInfo': 'WorldMap.cpp',
    '_ZN15NetworkItemInfo': 'PlayerInfo.cpp',
    '_ZN15NewPVPGameEvent': 'NewPVPGameData.cpp',
    '_ZN15NewPVPSmallDuan': 'UINewPVPDuanPlane.cpp',
    '_ZN15NinjaProperties': 'MomotaroRiderModule.cpp',
    '_ZN15PVPCurrencyData': 'PVPManager.cpp',
    '_ZN15PVZManifestFile': 'PVZManifest.cpp',
    '_ZN15PerkJuggledData': 'PennyPerkJuggled.cpp',
    '_ZN15PlantBundleData': 'PlantBundleContent.cpp',
    '_ZN15PlantFamilyInfo': 'PlantFamilyMgr.cpp',
    '_ZN15PlantPieceLevel': 'PlantPieceLevelData.cpp',
    '_ZN15PlantShieldData': 'ArtifactShield.cpp',
    '_ZN15PostProcessItem': 'PostProcessOverlayWidget.cpp',
    '_ZN15RelocationEvent': 'BeghouledModule.cpp',
    '_ZN15RemovePredicate': 'AnimationMgr.cpp',
    '_ZN15RiftPostEndPlay': 'RiftOutro.cpp',
    '_ZN15SecretAwardInfo': 'SecretStoreUtils.cpp',
    '_ZN15SecretGachaItem': 'NetworkSecretGachaInfo.cpp',
    '_ZN15ServerSalesInfo': 'PlayerInfo.cpp',
    '_ZN15SpawnItemRecord': 'PVZVersion.cpp',
    '_ZN15SpecialIconData': 'TutorialEffectMgr.cpp',
    '_ZN15SpecialWaveData': 'CustomLevelChallengeSingleHandedTemplate.cpp',
    '_ZN15StringComponent': 'PVPMapDialog.cpp',
    '_ZN15SwallowHoleItem': 'ShadowpeashooterBlackHole.cpp',
    '_ZN15TGACardGameData': 'TGALogMgr.cpp',
    '_ZN15TGACarnivalData': 'UICarnival.cpp',
    '_ZN15TGACustomVoting': 'TGALogMgr.cpp',
    '_ZN15TGAGroupBuyData': 'TGALogMgr.cpp',
    '_ZN15TGALogJoustData': 'AdaptorJoustScreen.cpp',
    '_ZN15TGAMysteryStore': 'TGALogMgr.cpp',
    '_ZN15TGAPVZ1ModeData': 'PVZ1ModeUtils.cpp',
    '_ZN15TGATenYearsData': 'TGALogMgr.cpp',
    '_ZN15TGAToyNightData': 'TGALogMgr.cpp',
    '_ZN15TGATutorialData': 'TGALogMgr.cpp',
    '_ZN15TGAccessoryData': 'TGALogMgr.cpp',
    '_ZN15TitleScreenLogo': 'TitleScreen.cpp',
    '_ZN15TotalRewardData': 'PVZVersion.cpp',
    '_ZN15TowerDefendRoad': 'UITourismOctober.cpp',
    '_ZN15TowerDefendTree': 'CustomLevelMgr.cpp',
    '_ZN15TowerDefendWave': 'CustomChallenge.cpp',
    '_ZN15TriRepGenerator10PointGroup': 'PopLoc.cpp',
    '_ZN15TriRepGenerator10PointGroup8BarGroup': 'PopLoc.cpp',
    '_ZN15TriRepGenerator10PointGroup8BarGroup3Bar': 'PopLoc.cpp',
    '_ZN15TriRepGenerator12CoverageGrid': 'PopLoc.cpp',
    '_ZN15TriRepGenerator7SpanRow': 'MemoryImage.cpp',
    '_ZN15TriRepGenerator7SpanRow4Span': 'MemoryImage.cpp',
    '_ZN15TriRepGenerator7SpanSet': 'MemoryImage.cpp',
    '_ZN15TrialCardConfig': 'TrialCardManager.cpp',
    '_ZN15UIImageDrawInfo': 'HotUIImage.cpp',
    '_ZN15WaveEventConfig': 'CustomLevelConfig.cpp',
    '_ZN15WaveManagerInfo': 'LevelUtils.cpp',
    '_ZN15WidgetComponent': 'PVPMapDialog.cpp',
    '_ZN15ZombieCacheData': 'NewPVPGameSubsystem.cpp',
    '_ZN15ZombieLevelStat': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN15ZombieSkillData': 'ZombieSkill.cpp',
    '_ZN15ZombieSkillInfo': 'PVZVersion.cpp',
    '_ZN15ZombieStarLevel': 'PlayerInfo.cpp',
    '_ZN15ZombieToxicosis': 'PrimalRafflesiaSubsystem.cpp',
    '_ZN15_ccBezierConfig': 'HorsebeanPlane.cpp',
    '_ZN15stMiniGame_rank': 'UIMiniGameRule.cpp',
    '_ZN15swallZombieData': 'ArtifactHydraulicSubSystem.cpp',
    '_ZN16ActivityDateData': 'ActivityConfig.cpp',
    '_ZN16AkOutputSettings': 'WwiseInteractiveAudioDriver.cpp',
    '_ZN16AnchorDescriptor': 'HotUIWidget.cpp',
    '_ZN16ArborPresentData': 'ArborDayBundleWidget.cpp',
    '_ZN16BarkPropertyData': 'ActivityConfig.cpp',
    '_ZN16BattleOrderAward': 'BattleOrderItemWidget.cpp',
    '_ZN16BronzeProperties10ModuleData': 'BronzeProperties.cpp',
    '_ZN16BronzeProperties15ItemDescription': 'UITourismOctober.cpp',
    '_ZN16CallofWishReward': 'CallofWishTrainItem.cpp',
    '_ZN16CardGameCardInfo': 'Action_CardGameCardSelectCheck.cpp',
    '_ZN16CartInstanceInfo': 'PurchaseBroker.cpp',
    '_ZN16ConstraintConfig': 'CustomLevelShopData.cpp',
    '_ZN16CurrentSalesInfo': 'PlayerInfo.cpp',
    '_ZN16CustomWaveZombie': 'CustomLevelMgr.cpp',
    '_ZN16DamageWithWeight': 'ComponentLinearBurst.cpp',
    '_ZN16DisplayPlantInfo': 'PVZVersion.cpp',
    '_ZN16Effect_PlayFrame10FrameRange': 'PVZVersion.cpp',
    '_ZN16EventBoardConfig': 'EventUIPropertySheet.cpp',
    '_ZN16EventTimesRecord': 'PlayerInfo.cpp',
    '_ZN16FShopContentData': 'FestivalShopContent.cpp',
    '_ZN16FestivalShopItem': 'PlayerInfo.cpp',
    '_ZN16FileVersionEntry': 'PVZVersionNetworkManager.cpp',
    '_ZN16GridItemFireWall16DamageZombieInfo': 'GridItemFireWall.cpp',
    '_ZN16GridItemHydraFog9PlantData': 'GridItemHydraFog.cpp',
    '_ZN16HeroPlantGradeUp': 'HeroPlantFramework.cpp',
    '_ZN16HesitationBuffer': 'TodDebug.cpp',
    '_ZN16LeagueFrameRange': 'RiftConfigSheet.cpp',
    '_ZN16LevelUpPriceData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN16MapNarrativeInfo': 'WorldMap.cpp',
    '_ZN16MiniGamePerkBuff': 'MiniGamePerkMgr.cpp',
    '_ZN16MiniGamePerkData': 'MiniGamePerkMgr.cpp',
    '_ZN16MoleNonSpawnData': 'WhackAMoleIntro.cpp',
    '_ZN16MutatorGridEntry': 'LevelMutatorModuleInserter.cpp',
    '_ZN16NameEffectStruct': 'PVPManager.cpp',
    '_ZN16NationalShopItem': 'PlayerInfo.cpp',
    '_ZN16NewPVPPlayerInfo': 'NewPVPMainEntry.cpp',
    '_ZN16PVZ2UIButtonPart': 'PVZ2UIButton.cpp',
    '_ZN16PacketRenderData': 'HotUISeedPacket.cpp',
    '_ZN16PakInterfaceBase': 'PakInterface.cpp',
    '_ZN16PlanetMeteorInfo': 'Plant_MeteorFlower.cpp',
    '_ZN16PlantBagItemData': 'RechargeProgress.cpp',
    '_ZN16PlantDetailsInfo': 'Plant.cpp',
    '_ZN16PlantPieceRecord': 'PlayerInfo.cpp',
    '_ZN16PooyanBossBarage': 'PooyanProperties.cpp',
    '_ZN16RailcartLocation': 'RailcartProperties.cpp',
    '_ZN16RandomRewardData': 'PVZVersion.cpp',
    '_ZN16RankRewardEntity': 'PVZVersion.cpp',
    '_ZN16RebateRewardItem': 'S2C_ChristmasRebate.cpp',
    '_ZN16RechargeUIConfig': 'AssetsManagerEx.cpp',
    '_ZN16ResilienceEntity': 'PVZVersion.cpp',
    '_ZN16RunningSkillInfo': 'RunningSubwayModule.cpp',
    '_ZN16S2C_ArtifactInfo': 'S2C_ICloud_GetPlayerInfo.cpp',
    '_ZN16S2C_Explore_Team': 'androidNetworkMsgProcess.cpp',
    '_ZN16S2C_NewGachaInfo': 'S2C_ICloud_DoNewGacha.cpp',
    '_ZN16S2C_PVP_RankInfo': 'PvpRankDlg.cpp',
    '_ZN16S2C_WechatReward': 'ChristmasChargeManager.cpp',
    '_ZN16ShowZombieTitles': 'PlantWarsZombieDetails.cpp',
    '_ZN16SingleHandedWave': 'CustomChallenge.cpp',
    '_ZN16SingleScreenFade': 'Effect_ScreenFade.cpp',
    '_ZN16SingleWeaponData': 'CustomLevelChallengeSingleHandedTemplate.cpp',
    '_ZN16SpecialOfferInfo': 'PlantSpecialOfferUI.cpp',
    '_ZN16StatueMazeMatrix': 'CustomLevelMgr.cpp',
    '_ZN16StephaniaHitInfo': 'StephaniaSubsystem.cpp',
    '_ZN16TGAAccountRemove': 'TGALogMgr.cpp',
    '_ZN16TGAGrowthPackage': 'TGALogMgr.cpp',
    '_ZN16TGAPlantWarsData': 'TGALogMgr.cpp',
    '_ZN16TGAUnchartedData': 'NewRecallBillingRewardManager.cpp',
    '_ZN16TipsPropertyData': 'ActivityConfig.cpp',
    '_ZN16TreasureYetiInfo': 'PlayerInfo.cpp',
    '_ZN16TutorialCardInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN16UpdateRewardData': 'PVZVersion.cpp',
    '_ZN16WalkingOutZombie': 'ZombieWalkOutSubSystem.cpp',
    '_ZN16WechatRewardData': 'WechatRewardInfo.cpp',
    '_ZN16WorldDungeonInfo': 'DungeonWidget.cpp',
    '_ZN16ZombieFlatulence': 'Plant_Chilibean_Subsystem.cpp',
    '_ZN16ZombieStunEffect': 'PlantFumeshroomSubSystem.cpp',
    '_ZN16ZombieWarpRecord': 'PlantHocusCrocusSubSystem.cpp',
    '_ZN16stExperPlantInfo': 'SpringChargeManager.cpp',
    '_ZN16stMiniGame_Bonus': 'UIMiniGameRule.cpp',
    '_ZN16stThirdAwardInfo': 'ChagreDoubleFesivalConfig.cpp',
    '_ZN17ADRewardBonusInfo': 'ADRewardData.cpp',
    '_ZN17AchievementConfig': 'NetworkMsgProcess.cpp',
    '_ZN17ActiveSalesObject': 'ActiveSalesConfig.cpp',
    '_ZN17ArmrackProperties11ArmrackData': 'ArmrackProperties.cpp',
    '_ZN17ArmrackProperties8ItemData': 'ArmrackProperties.cpp',
    '_ZN17ArtifactBoostInfo': 'PlayerInfo.cpp',
    '_ZN17ArtifactStageData': 'Artifact.cpp',
    '_ZN17BarrelDescription': 'BarrelWaveAction.cpp',
    '_ZN17BattleOrderBundle': 'UIBattleOrderBundle.cpp',
    '_ZN17BoardPanLocations': 'Board.cpp',
    '_ZN17CardAttributeData': 'CardObject.cpp',
    '_ZN17CardGameLevelData': 'UICardGameRewardScrollPanel.cpp',
    '_ZN17CardGameWorldData': 'UICardGameRewardScrollPanel.cpp',
    '_ZN17ChallengeItemData': 'PVZVersion.cpp',
    '_ZN17ChargeDegreeRange': 'ZombieBumperCar.cpp',
    '_ZN17ChildrenDayStates': 'S2C_ActActitityStates.cpp',
    '_ZN17ChooserPacketData': 'UnchartedSeedChooser.cpp',
    '_ZN17CurrentHealthData': 'NewPVPGameSubsystem.cpp',
    '_ZN17CustomLevelParams': 'CustomLevelMgr.cpp',
    '_ZN17CustomPreviewData': 'CustomLevelMgr.cpp',
    '_ZN17DefaultWaveConfig': 'CustomLevelMgr.cpp',
    '_ZN17DisplayActionInfo': 'PlantDisplayBoard.cpp',
    '_ZN17DisplayZombieInfo': 'PVZVersion.cpp',
    '_ZN17DrZomibeLevelData': 'WaveManagerModule.cpp',
    '_ZN17DuplicatableProps': 'PowerPropsDuplicator.cpp',
    '_ZN17EASquaredNullImpl': 'EASquared_Android.cpp',
    '_ZN17ExpPlantLoginData': 'SpringChargeManager.cpp',
    '_ZN17FestivalEntryData': 'RechargeWelfareUI.cpp',
    '_ZN17FishingZombieInfo': 'FishingModuleEditor.cpp',
    '_ZN17FlagWaveSetupData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN17GravityZombieData': 'ArtifactGravitySubSystem.cpp',
    '_ZN17InitialPlantEntry': 'CustomLevelChallengeEvilDaveTemplate.cpp',
    '_ZN17InvitationLottery': 'InvitationData.cpp',
    '_ZN17LevelOfTheDayInfo': 'S2C_ActActitityStates.cpp',
    '_ZN17LogSunUpgradeInfo': 'NewPVPMgr.cpp',
    '_ZN17MiniGameLevelData': 'MiniGameCollectionNetworkMgr.cpp',
    '_ZN17NetworkBundleData': 'PlantBundleInfo.cpp',
    '_ZN17NoticeContentData': 'ActivityConfig.cpp',
    '_ZN17OfflineNoticeInfo': 'OfflineBoardMgr.cpp',
    '_ZN17PVPZoneServerData': 'PVPManager.cpp',
    '_ZN17PVZ2UIAwardScreen11ScreenEntry': 'PVZ2UIAwardScreen.cpp',
    '_ZN17PVZ2UIAwardScreen17AwardScreenConfig': 'PVZ2UIAwardScreen.cpp',
    '_ZN17PVZ2UIAwardScreen25RewardObjectDisplayConfig': 'PVZ2UIAwardScreen.cpp',
    '_ZN17PaymentBundleInfo': 'NewRecallBillingRewardManager.cpp',
    '_ZN17PaymentResultInfo': 'LawnApp.cpp',
    '_ZN17PlantBoostTracker': 'TrueDamageAppendBoostTracker.cpp',
    '_ZN17PlantCustomLayers': 'PlantAnimRig.cpp',
    '_ZN17PlantGiftBaseData': 'PVZVersion.cpp',
    '_ZN17PlantTargetParams': 'Plant_Fishhookgrass.cpp',
    '_ZN17PlantWarsNodeData': 'PlantWarsLevelTempData.cpp',
    '_ZN17PlayerAddressInfo': 'GeilivableLotteryConfig.cpp',
    '_ZN17PlayerStorageData': 'PlayerInfo.cpp',
    '_ZN17PooyanShooterData': 'PooyanShooterChooseUI.cpp',
    '_ZN17PresentTableEntry': 'PVZVersion.cpp',
    '_ZN17ProgressBarDoodad': 'PVZ2UIProgressBar.cpp',
    '_ZN17RedPackAnimStatus': 'RedPackOpenUI.cpp',
    '_ZN17RedPackClosedData': 'ActivityConfig.cpp',
    '_ZN17RewardElementInfo': 'PVZVersion.cpp',
    '_ZN17S2C_Explore_Plant': 'S2C_ExplorerPlantStatus.cpp',
    '_ZN17S2C_PlantListInfo': 'PlayerInfo.cpp',
    '_ZN17SSpringRewardInfo': 'ActivityConfig.cpp',
    '_ZN17ScrollBarBarkData': 'ActivityConfig.cpp',
    '_ZN17SecretStoreBundle': 'SecretStoreMgr.cpp',
    '_ZN17SignRewardContent': 'PlayerInfo.cpp',
    '_ZN17SpringSalesStates': 'S2C_ActActitityStates.cpp',
    '_ZN17StoreGiftDataInfo': 'StoreGiftConfig.cpp',
    '_ZN17TGAAdsLotteryData': 'TGALogMgr.cpp',
    '_ZN17TGACallofWishDraw': 'TGALogMgr.cpp',
    '_ZN17TGACallofWishGift': 'TGALogMgr.cpp',
    '_ZN17TGACallofWishTask': 'TGALogMgr.cpp',
    '_ZN17TGACornucopiaData': 'TGALogMgr.cpp',
    '_ZN17TGAGiftReturnData': 'TGALogMgr.cpp',
    '_ZN17TGAInvitationData': 'TGALogMgr.cpp',
    '_ZN17TGALogEndlessData': 'DangerRoomManager.cpp',
    '_ZN17TGALuckyChestData': 'TGALogMgr.cpp',
    '_ZN17TGANFSLinkageData': 'TGALogMgr.cpp',
    '_ZN17TGANewPVPPlusData': 'TGALogMgr.cpp',
    '_ZN17TGAPlantPediaData': 'TGALogMgr.cpp',
    '_ZN17ThemeDisabledInfo': 'gnu_cxxFunctions.cpp',
    '_ZN17ValidatePlantData': 'RiftValidateMgr.cpp',
    '_ZN17VaseConfiguration': 'VaseBreakerModule.cpp',
    '_ZN17VersionUpdateInfo': 'PVZVersion.cpp',
    '_ZN17WidgetHotSwapData': 'HotUIManager.cpp',
    '_ZN17WorldGateLevelKey': 'Board.cpp',
    '_ZN17WorldSpecificKeys': 'PVZVersion.cpp',
    '_ZN17ZombieExplodeInfo': 'PrimalRafflesiaSubsystem.cpp',
    '_ZN17ZombieJuggledData': 'Zombie.cpp',
    '_ZN17ZombieWarningInfo': 'LevelDefinition.cpp',
    '_ZN17ZombossBladeStage': 'ZombieZombossBlade.cpp',
    '_ZN18ACLOG_MaterialInfo': 'S2C_ACLog.cpp',
    '_ZN18AdProviderNullImpl': 'Unclassified.cpp',
    '_ZN18AdaptorBoardConfig': 'AdaptorRichManEvent.cpp',
    '_ZN18AdaptorEventConfig': 'gnu_cxxFunctions.cpp',
    '_ZN18AdventureBonusInfo': 'DungeonWidget.cpp',
    '_ZN18ArenaPlantInfoData': 'ArenaPlantModule.cpp',
    '_ZN18BirthdayRewardData': 'BirthdayRewardContent.cpp',
    '_ZN18CServerTimeHandler': 'CServerTimeHandler_Store.cpp',
    '_ZN18CarnivalBundleData': 'CarnivalBundle.cpp',
    '_ZN18CarnivalRewardData': 'CarnivalTotalRewardItem.cpp',
    '_ZN18ChallengeGroupData': 'CustomLevelMgr.cpp',
    '_ZN18ChallengeRewardDlg10RewardInfo': 'ChallengeRewardDlg.cpp',
    '_ZN18CommonActivateData': 'ActivityConfig.cpp',
    '_ZN18ConveyorPlantEntry': 'ConveyorSeedBank.cpp',
    '_ZN18CornucopiaRankData': 'UICornucopia.cpp',
    '_ZN18CustomConveyorData': 'PVZVersion.cpp',
    '_ZN18CustomSeedBankData': 'CustomLevelMgr.cpp',
    '_ZN18DActionBaseCreator': 'DActionCreator.cpp',
    '_ZN18DangerRoomLifeData': 'PlayerInfo.cpp',
    '_ZN18DangerRoomRankData': 'UITourismOctober.cpp',
    '_ZN18DynamicLayoutState': 'HotUIWidget.cpp',
    '_ZN18DynamicResizeState': 'HotUIWidget.cpp',
    '_ZN18EventUIEntryConfig': 'EventUIPropertySheet.cpp',
    '_ZN18EvilDavePlantEntry': 'UITourismOctober.cpp',
    '_ZN18GoldenEggProbility': 'ActivityConfig.cpp',
    '_ZN18LawnStringFileInfo': 'LawnStringUpdater.cpp',
    '_ZN18LogActionCountInfo': 'NewPVPMgr.cpp',
    '_ZN18LuckyChestTaskInfo': 'PlayerInfo.cpp',
    '_ZN18MiniGameBufferData': 'MiniGameCollectionMainEntryData.cpp',
    '_ZN18MiniGameRewardData': 'MiniGameCollectionMainEntryData.cpp',
    '_ZN18MysteryCrystalDrop': 'ActivityConfig.cpp',
    '_ZN18NDLoginRewardBonus': 'DailySignRewardView.cpp',
    '_ZN18NetworkPaymentInfo': 'PurchaseBroker.cpp',
    '_ZN18NetworkfthCostData': 'FestivalEventUI.cpp',
    '_ZN18NewPVPCPULevelInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN18NewPVPTaskDataInfo': 'NewPVPBattlePassData.cpp',
    '_ZN18NewPVPTutorialInfo': 'NewPVPPropertySheet.cpp',
    '_ZN18NewPVPZombieConfig': 'NewPVPMainEntry.cpp',
    '_ZN18PlantAccessoryInfo': 'PlayerInfo.cpp',
    '_ZN18PlantAdventureInfo': 'PlayerInfo.cpp',
    '_ZN18PlantAttributeInfo': 'gnu_cxxFunctions.cpp',
    '_ZN18PlantFoodSetupData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN18PlantSalesUiReward': 'NetworkMsgProcess.cpp',
    '_ZN18PlantWarsLevelData': 'PlantWarsNetworkMgr.cpp',
    '_ZN18PlantWarsWorldData': 'PlantWarsUtils.cpp',
    '_ZN18PlantfoodOwnerLink': 'PlantfoodCaptureSubSystem.cpp',
    '_ZN18PlaybackZombieData': 'PVZVersion.cpp',
    '_ZN18PuzzleRotateConfig': 'PuzzleRotatePanel.cpp',
    '_ZN18PvPRankMonthReward': 'S2C_PVP_Login.cpp',
    '_ZN18PvpPlantLostRecord': 'MetricsCollector.cpp',
    '_ZN18RebateSingleRecord': 'AssetsManagerEx.cpp',
    '_ZN18RechargeRewardData': 'NDRechargeRewardContent.cpp',
    '_ZN18RedPackActivedData': 'ActivityConfig.cpp',
    '_ZN18RedPackDisplayData': 'RedPackDisplayContent.cpp',
    '_ZN18RiftDifficultyInfo': 'AdaptorRiftLevelSetup.cpp',
    '_ZN18RiverEntitySpawner': 'RiverEntitiesManager.cpp',
    '_ZN18S2C_PVP_ZombieData': 'S2C_PVP_TrainingInfos.cpp',
    '_ZN18S2C_PlantLevelInfo': 'S2C_PlantLevel.cpp',
    '_ZN18S2C_RedPackContent': 'S2C_ICloud_RedPackLeaderBoardReward.cpp',
    '_ZN18S2C_RedPack_Public': 'RedPackUI.cpp',
    '_ZN18SchoolBusZombieDes': 'UITourismOctober.cpp',
    '_ZN18SecretBundleDetail': 'SecretStoreMgr.cpp',
    '_ZN18SecretStoreContent': 'SecretStoreMgr.cpp',
    '_ZN18TGABattleOrderData': 'TGALogMgr.cpp',
    '_ZN18TGACallofWishDaily': 'TGALogMgr.cpp',
    '_ZN18TGACallofWishLimit': 'TGALogMgr.cpp',
    '_ZN18TGACallofWishTrain': 'TGALogMgr.cpp',
    '_ZN18TGACustomLevelData': 'UICustomLevelLevelDetail.cpp',
    '_ZN18TGADaveKitchenData': 'TGALogMgr.cpp',
    '_ZN18TGALogMinigameData': 'TGALogMgr.cpp',
    '_ZN18TGALogPurchaseData': 'TGALogMgr.cpp',
    '_ZN18TGAPVZ1Achievement': 'TGALogMgr.cpp',
    '_ZN18TGAPartyAssistData': 'TGALogMgr.cpp',
    '_ZN18TGAVaseBreakerData': 'TGALogMgr.cpp',
    '_ZN18TGAWishingPoolData': 'TGALogMgr.cpp',
    '_ZN18ThunderDescription': 'ThunderWaveAction.cpp',
    '_ZN18TinyCheatPlantInfo': 'S2C_DangerRoomCheatingInfo.cpp',
    '_ZN18TossedBezeirZombie': 'ZombieBezeirTosserSubSystem.cpp',
    '_ZN18TransportingZombie': 'HatMushroomTransportSubSystem.cpp',
    '_ZN18VanSpawnZombieData': 'PVZVersion.cpp',
    '_ZN18WatergunBeamParams': 'ArtifactWatergun.cpp',
    '_ZN18ZombiePirateParrot10PlantCache': 'ZombiePirateParrot.cpp',
    '_ZN18ZombieSpawnerEntry': 'PVZVersion.cpp',
    '_ZN18ZombieSummonPacket': 'SummonZombieEffect.cpp',
    '_ZN18ZombossQigongStage': 'ZombieZombossQigong.cpp',
    '_ZN18stFirstChargeAward': 'FirstChargeAwardConfig.cpp',
    '_ZN18stSpringRewardInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN19AnimationDetailInfo': 'WorldResourcesData.cpp',
    '_ZN19ArtifactRankUpPrice': 'UITourismOctober.cpp',
    '_ZN19ArtifactThunderData': 'ArtifactLightning.cpp',
    '_ZN19BattleOrderRankData': 'UITourismOctober.cpp',
    '_ZN19BeghouledUpgradeMap': 'AssetsManagerEx.cpp',
    '_ZN19BoardEntityBuffInfo': 'BoardEntity.cpp',
    '_ZN19BundlePushCondition': 'RechargeBundleConfig.cpp',
    '_ZN19CarnivalBundleExtra': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN19CustomChallengeData': 'CustomChallenge.cpp',
    '_ZN19CustomLevelElements': 'CustomLevelMgr.cpp',
    '_ZN19CustomPowerTileInfo': 'CustomLevelMgr.cpp',
    '_ZN19DangerRoomLevelData': 'DangerRoomPropertySheet.cpp',
    '_ZN19DangerRoomPlantInfo': 'DangerRoomInfo.cpp',
    '_ZN19DangerRoomTitleData': 'DangerRoomPropertySheet.cpp',
    '_ZN19DaveKitchenTaskInfo': 'DaveKitchenTaskWidget.cpp',
    '_ZN19EntitySearch_Lambda': 'MeleePlantTargeter.cpp',
    '_ZN19ExpPlantLoginConfig': 'SpringChargeManager.cpp',
    '_ZN19FishingModuleEditor8ItemData': 'FishingModuleEditor.cpp',
    '_ZN19GrowthPackageReward': 'GrowthPackageData.cpp',
    '_ZN19HeroPlantGradeRange': 'HeroPlantFramework.cpp',
    '_ZN19HotUISeedPacketList13SeedPacketRow': 'HotUISeedPacketList.cpp',
    '_ZN19JoustTournamentData': 'NetworkDashboardInfo.cpp',
    '_ZN19KongmingLanternData': 'WaveActionKongmingLanternProps.cpp',
    '_ZN19LevelEditorCardInfo': 'LevelEditorSeedChooser.cpp',
    '_ZN19MagentoProductProps9TierPrice': 'MagentoService.cpp',
    '_ZN19MarqueeViewItemData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN19MeteorLauncherEntry': 'Plant_MeteorFlower.cpp',
    '_ZN19MoldColonyChallenge9BoundMold': 'MoldColonyChallenge.cpp',
    '_ZN19NetMiniGamePerkData': 'MiniGamePerkMgr.cpp',
    '_ZN19NetworkCacheObjects': 'UITourismOctober.cpp',
    '_ZN19NullHttpTransaction': 'Dialog.cpp',
    '_ZN19PacketInterpolation': 'PneumaticSeedBank.cpp',
    '_ZN19PlantConditionEntry': 'PlantGroup.cpp',
    '_ZN19PlantSpecialTagInfo': 'UINewPlantView_SkillDisplay.cpp',
    '_ZN19PlayerTrialCardInfo': 'UIBag.cpp',
    '_ZN19PneumaticPlantEntry': 'PneumaticSeedBank.cpp',
    '_ZN19ProtectedPlantEntry': 'PVZVersion.cpp',
    '_ZN19PurchasedBundleInfo': 'RedeemRewardUI.cpp',
    '_ZN19PushPlantGroupProps': 'SpeakerProjectile.cpp',
    '_ZN19ReconstructionLevel': 'PVZVersion.cpp',
    '_ZN19RiftLeaderboardData': 'AdaptorRiftLeaderBoardScreen.cpp',
    '_ZN19RiftLevelDefinition': 'RiftLevelUnlocksProperties.cpp',
    '_ZN19RiftLocalPlayerData': 'AdaptorRiftLeaderBoardScreen.cpp',
    '_ZN19RiftProjectileTimer': 'ZombieBumperCar.cpp',
    '_ZN19S2C_AvatarLevelInfo': 'S2C_AvatarLevel.cpp',
    '_ZN19S2C_NewGachaKeyInfo': 'S2C_ICloud_DoSecretGacha.cpp',
    '_ZN19S2C_PlantFamilyAttr': 'PlayerInfo.cpp',
    '_ZN19S2C_PlantFamilyInfo': 'PlayerInfo.cpp',
    '_ZN19StreamingMusicGroup': 'StreamingMusicList.cpp',
    '_ZN19SummerFireworksData': 'SummerFireworksWaveAction.cpp',
    '_ZN19TGADiscountShopData': 'TGALogMgr.cpp',
    '_ZN19TGALevelPackageData': 'TGALogMgr.cpp',
    '_ZN19TGALimitedGachaData': 'TGALogMgr.cpp',
    '_ZN19TGALogPlantDecorate': 'TGALogMgr.cpp',
    '_ZN19TGALogTravelLogData': 'TGALogMgr.cpp',
    '_ZN19TGAMinorLotteryData': 'TGALogMgr.cpp',
    '_ZN19TGANewYearGoodsData': 'TGALogMgr.cpp',
    '_ZN19TGAPennyGiftBoxData': 'TGALogMgr.cpp',
    '_ZN19TGAPennyPursuitData': 'NewRecallBillingRewardManager.cpp',
    '_ZN19TGAPlayerReturnData': 'TGALogMgr.cpp',
    '_ZN19TGAPlayerSurveyData': 'UIPlayerSurvey.cpp',
    '_ZN19TGAScrollbannerData': 'TGALogMgr.cpp',
    '_ZN19TodStringListFormat': 'TodCommon.cpp',
    '_ZN19TowerDefendRoadInfo': 'UITourismOctober.cpp',
    '_ZN19TowerDefendTreeInfo': 'UITourismOctober.cpp',
    '_ZN19TowerDefendWaveData': 'CustomChallenge.cpp',
    '_ZN19WidgetAnimationData': 'AdaptorJoustTourneyResultsScreen.cpp',
    '_ZN19WorldCompletionData': 'PlayerInfo.cpp',
    '_ZN19ZombieConditionInfo': 'DamageInfo.cpp',
    '_ZN19ZombieLootApplicant': 'WaveManager.cpp',
    '_ZN19ZombieReachLineData': 'Board.cpp',
    '_ZN19ZombossExplosiveImp': 'ZombieZombossExplosive.cpp',
    '_ZN19ZombossRandomAction': 'ZombieZombossBlade.cpp',
    '_ZN19ZombossStageScoring': 'ZombieZombossMech.cpp',
    '_ZN19stActivity_iconInfo': 'WorldMapActivityBtnTurnChangeManager.cpp',
    '_ZN20ACLOG_AccessoryPiece': 'PVZVersion.cpp',
    '_ZN20ACLOG_PlantStarLevel': 'S2C_ACLog.cpp',
    '_ZN20AccessoryPieceUIInfo': 'AccessoryScrollPanel.cpp',
    '_ZN20ActiveSalesPriceList': 'ActiveSalesConfig.cpp',
    '_ZN20AdventureBonusResult': 'PlantAdventureConfig.cpp',
    '_ZN20AndroidGotFocusEvent': 'AndroidAppDriver.cpp',
    '_ZN20ArtifactLevelUpPrice': 'UITourismOctober.cpp',
    '_ZN20BattleArrayComponent': 'PlayerInfo.cpp',
    '_ZN20BuffedProjectileData': 'gnu_cxxFunctions.cpp',
    '_ZN20BundleQueueCondition': 'PlayerInfo.cpp',
    '_ZN20CannonMinigameModule15TargetListEntry': 'CannonMinigameModule.cpp',
    '_ZN20CardGameRewardDetail': 'CardGameRewardMgr.cpp',
    '_ZN20CardTargetCursorAnim': 'CardTargetCursor.cpp',
    '_ZN20ChristmasLotteryData': 'ActivityConfig.cpp',
    '_ZN20ChristmasProtectData': 'ActivityConfig.cpp',
    '_ZN20ChristmasProtectInfo': 'FestivalManager.cpp',
    '_ZN20CommonRewardItemData': 'UINewPVPShop.cpp',
    '_ZN20ComponentHotSwapData': 'HotUIFile.cpp',
    '_ZN20CursorAnimEffectData': 'CardTargetCursorEffect.cpp',
    '_ZN20CustomChallengeMolds': 'CustomChallenge.cpp',
    '_ZN20CustomLevelEncourage': 'CustomLevelMgr.cpp',
    '_ZN20CustomLevelWorldInfo': 'CustomLevelMgr.cpp',
    '_ZN20EnergyGridProperties14EnergyGridData': 'EnergyGridProperties.cpp',
    '_ZN20EnergyGridProperties14ItemDataEnergy': 'EnergyGridProperties.cpp',
    '_ZN20FrostWindDescription': 'FrostWindWaveAction.cpp',
    '_ZN20GeneSequenceShopItem': 'PlantGeneSequenceShopItem.cpp',
    '_ZN20GiftFoReturnSignInfo': 'GiftFoReturnSignWidget.cpp',
    '_ZN20GiftFoReturnTaskInfo': 'GiftFoReturnTaskWidget.cpp',
    '_ZN20GlobalAnimCountCache': 'PopAnimRig.cpp',
    '_ZN20GriditemBarrelParams': 'GridItemCardGameZombieBarrel.cpp',
    '_ZN20HowToPlayScreenEntry': 'HowToPlayScreenData.cpp',
    '_ZN20InvitationPlayerInfo': 'InvitationData.cpp',
    '_ZN20JoustLeaderboardData': 'AdaptorJoustScreen.cpp',
    '_ZN20JoustPlayerPlantData': 'LevelReplayData.cpp',
    '_ZN20LevelBasedSelectInfo': 'LevelBasedModifierModuleMgr.cpp',
    '_ZN20LevelEditorCardPlant': 'LevelEditorGroundSetting.cpp',
    '_ZN20LimitLotteryItemInfo': 'LimitLotteryItem.cpp',
    '_ZN20NetworkRewardContent': 'New_S2C_VaseBreakerReward.cpp',
    '_ZN20NewPVPCPUCountObject': 'NewPVPPropertySheet.cpp',
    '_ZN20NewPVPSunUpgradeInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN20NewPVPZombieRareInfo': 'gnu_cxxFunctions.cpp',
    '_ZN20ObstacleNonSpawnData': 'WorldCupConfig.cpp',
    '_ZN20OppoNewerDailyReward': 'OfferBundleConfig.cpp',
    '_ZN20PVZ1ModeShopItemData': 'PVZ1ModeShopData.cpp',
    '_ZN20PartyAssistBonusInfo': 'PartyAssistBonusWidget.cpp',
    '_ZN20PennyGiftBoxGrowData': 'PenntGiftBoxItem.cpp',
    '_ZN20PlantAdventureStates': 'PlayerInfo.cpp',
    '_ZN20PlantEquipAvatarInfo': 'PlayerInfo.cpp',
    '_ZN20PlantGeneEssenceInfo': 'PlayerInfo.cpp',
    '_ZN20RappellingZombieInfo': 'ZombossRobotRappellingSubSystem.cpp',
    '_ZN20ResilienceDamageInfo': 'DamageInfo.cpp',
    '_ZN20RichmanTileEventBase': 'RichmanTileEvent_MoveForward.cpp',
    '_ZN20RiftDifficultyReward': 'NetworkMainEntryInfo.cpp',
    '_ZN20RiftTimedSunDropData': 'gnu_cxxFunctions.cpp',
    '_ZN20S2C_DailySignContent': 'UnchartedModeNetworkMgr.cpp',
    '_ZN20S2C_PVP_DefenderInfo': 'PVPDatas.cpp',
    '_ZN20S2C_PlantPendantInfo': 'S2C_ICloud_ExchangePendant.cpp',
    '_ZN20S2C_SalesLevelUpInfo': 'S2C_SalesStates.cpp',
    '_ZN20S2C_ScrollBannerData': 'S2C_ScrollBannerNetworkData.cpp',
    '_ZN20SchoolBusDescription': 'SchoolBusWaveAction.cpp',
    '_ZN20ScoreDisplayModifier': 'LevelScoringSubsystem.cpp',
    '_ZN20ShakeInDamagePercent': 'SkyCityStage.cpp',
    '_ZN20ShareRewardBonusInfo': 'ShareRewardData.cpp',
    '_ZN20SingleHandedWaveData': 'CustomChallenge.cpp',
    '_ZN20SpewingZombieTracker': 'PlantSunBeanSubSystem.cpp',
    '_ZN20StoneLotteryItemInfo': 'StoneLotteryItem.cpp',
    '_ZN20TGAAutumnHarvestData': 'TGALogMgr.cpp',
    '_ZN20TGABossChallengeData': 'BossChallenge.cpp',
    '_ZN20TGACustomLevelADData': 'TGALogMgr.cpp',
    '_ZN20TGADailySignActivity': 'TGALogMgr.cpp',
    '_ZN20TGALimitedSummonData': 'TGALogMgr.cpp',
    '_ZN20TGANewRecallBankData': 'TGALogMgr.cpp',
    '_ZN20TGANewRecallSignData': 'TGALogMgr.cpp',
    '_ZN20TentZombieTranStruct': 'AssetsManagerEx.cpp',
    '_ZN20VaseBreakerVaseEntry': 'UITourismOctober.cpp',
    '_ZN20WeeklyGameModesCount': 'ActivityConfig.cpp',
    '_ZN20WhackZombieWaveProps': 'WhackZombieWaveActionProps.cpp',
    '_ZN20WidgetFactoryManager': 'LawnApp.cpp',
    '_ZN20WishingPoolGrandInfo': 'WishingPoolData.cpp',
    '_ZN20WorldMapActionCaches12ActionCached': 'PVZVersion.cpp',
    '_ZN20ZombieConditionEntry': 'DamageInfoProps.cpp',
    '_ZN20ZombieSummonPoolItem': 'ZombossLastStandMinigameModule.cpp',
    '_ZN20_EpicQuestRewardInfo': 'AwardsGranter.cpp',
    '_ZN21AndroidLostFocusEvent': 'AndroidAppDriver.cpp',
    '_ZN21ArtifactPresentDetail': 'ArtifactPresentMgr.cpp',
    '_ZN21AssetsManagerManifest5Asset': 'AssetsManagerManifest.cpp',
    '_ZN21AssetsManagerManifest9AssetDiff': 'AssetsManagerManifest.cpp',
    '_ZN21BaseDecompressionTask': 'BaseResStreamsDriver.cpp',
    '_ZN21BossFightActivateData': 'ActivityConfig.cpp',
    '_ZN21CZombieSummonDataPool': 'ZombossLastStandMinigameModule.cpp',
    '_ZN21ConvertProjectileNode': 'ComponentProjectileConverter.cpp',
    '_ZN21CthulhuDangerroomInfo': 'CthulhuEyeballEasyButton.cpp',
    '_ZN21CustomWaveEventPortal': 'CustomLevelMgr.cpp',
    '_ZN21DailyRechargeCurrency': 'PlayerInfo.cpp',
    '_ZN21DangerRoomRewardItems': 'DangerRoomRewardList.cpp',
    '_ZN21DanggerRoomWaveConfig': 'DangerRoomJitteredWaveGenerator.cpp',
    '_ZN21EggRechargeBundleData': 'RenaissanceChallengeBundleWidget.cpp',
    '_ZN21FinalWarningPointData': 'Board.cpp',
    '_ZN21FishingZombieInitData': 'FishingProperties.cpp',
    '_ZN21GachaActivityItemInfo': 'GachaActivityInfo.cpp',
    '_ZN21GeilivableLotteryInfo': 'PlayerInfo.cpp',
    '_ZN21HotUISeedPacketConfig': 'HotUISeedPacket.cpp',
    '_ZN21LimitGroupBuyItemInfo': 'UILimitGroupBuy.cpp',
    '_ZN21LimitedSummonGrowData': 'LimitedSummonData.cpp',
    '_ZN21LotteryResultIconInfo': 'PVZ2UILotteryResult.cpp',
    '_ZN21MonthlyCardCommonData': 'MonthlyCardMgr.cpp',
    '_ZN21NationalDayRewardItem': 'NatinalDayRewardMgr.cpp',
    '_ZN21NetworkPresentContent': 'NewerPresentMgr.cpp',
    '_ZN21NewPVPBattlePassAward': 'NewPVPBattlePassItemWidget.cpp',
    '_ZN21NewPVPCurrentCPUPlant': 'NewPVPGameSubsystem.cpp',
    '_ZN21NewPVPCurrentLevelCPU': 'NewPVPGameSubsystem.cpp',
    '_ZN21NewPVPDuanRewardsData': 'UINewPVPDuanPlane.cpp',
    '_ZN21NewPVPPlantPacketInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN21NewPVPPlayerPlantData': 'NewPVPGameData.cpp',
    '_ZN21NewPVPZombieLevelInfo': 'NewPVPSeedBank.cpp',
    '_ZN21NewPVPZombiePieceInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN21NewPVPZombieSkillData': 'NewPVPGameSubsystem.cpp',
    '_ZN21NewPVPZombieSkillInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN21NewRecallBundleReward': 'NewRecallBundleItem.cpp',
    '_ZN21PerkProgressionReward': 'PVZVersion.cpp',
    '_ZN21PlantAdventureLogInfo': 'Message.cpp',
    '_ZN21PlantFamilyBoostValue': 'PlantFamilyMgr.cpp',
    '_ZN21PlantReducedRangeData': 'RiftThemeReduceRange.cpp',
    '_ZN21PlayerTrialStatusInfo': 'TrialCardManager.cpp',
    '_ZN21PvZ1LevelCompleteInfo': 'PVZ1ModeUtils.cpp',
    '_ZN21RenaiModuleProperties10StatueInfo': 'RenaiModule.cpp',
    '_ZN21RhubarbarianLeapProps': 'Plant_Rhubarbarian.cpp',
    '_ZN21RunningPlayerInitInfo': 'RunningSubwayModuleProperties.cpp',
    '_ZN21S2C_AchieveConfigInfo': 'S2C_DailyAchievementConfig.cpp',
    '_ZN21S2C_Arena_Ending_Data': 'S2C_PVP_Ending.cpp',
    '_ZN21S2C_ArtifactBoostInfo': 'INetworkData.cpp',
    '_ZN21S2C_DangerRoomContent': 'S2C_UploadDangerRoomRank.cpp',
    '_ZN21S2C_DangerRoom_Public': 'AssetsManagerEx.cpp',
    '_ZN21SharkMinionParameters': 'SharkMinion.cpp',
    '_ZN21SingleHandedPlantInfo': 'UITourismOctober.cpp',
    '_ZN21SmokeManholeSpawnInfo': 'DangerRoomSteamDesigner.cpp',
    '_ZN21SparkingZombieTracker': 'Plant_Electricitea_Subsystem.cpp',
    '_ZN21SpecialGameLevelGroup': 'ActivityConfig.cpp',
    '_ZN21SpecialProjectileInfo': 'PrimalRafflesiaSubsystem.cpp',
    '_ZN21SteamZombiePortalInfo': 'ZombossSteamTrainSpawnActionHandler.cpp',
    '_ZN21StephaniaMinorHitInfo': 'StephaniaSubsystem.cpp',
    '_ZN21TGAConsumeReceiveData': 'TGALogMgr.cpp',
    '_ZN21TGADragonTreasureData': 'TGALogMgr.cpp',
    '_ZN21TGALimitedLotteryData': 'TGALogMgr.cpp',
    '_ZN21TGALuckyChestShopData': 'TGALogMgr.cpp',
    '_ZN21TGAPennyClassroomData': 'TGALogMgr.cpp',
    '_ZN21TGARechargeBundleData': 'RechargeRewardContent.cpp',
    '_ZN21TGATourismOctoberData': 'TGALogMgr.cpp',
    '_ZN21TGArtifactCultivation': 'TGALogMgr.cpp',
    '_ZN21TargetProbabilityItem': 'SquashProps.cpp',
    '_ZN21TowerDefendWaveZombie': 'PVZVersion.cpp',
    '_ZN21ToyNightGachaRewardUI': 'ToyNightGachaUI.cpp',
    '_ZN21ValidatePlantAttackCD': 'RiftValidateMgr.cpp',
    '_ZN21VaseContentProperties': 'CustomLevelChallengeVaseBreakerTemplate.cpp',
    '_ZN21WishingPoolBubbleInfo': 'UIWishingPool.cpp',
    '_ZN21WorldLevelPackageData': 'WorldLevelPackageManager.cpp',
    '_ZN21WorldLevelPackageItem': 'UIWorldLevelPackageDetail.cpp',
    '_ZN21ZombieCamelCollection': 'Zombie_Camel_Subsystem.cpp',
    '_ZN21ZombossExplosiveStage': 'ZombieZombossExplosive.cpp',
    '_ZN21stMiniGameAward_Bonus': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN22ACLOG_PlantPieceRecord': 'S2C_ACLog.cpp',
    '_ZN22AchievementContentInfo': 'DailyAchievement.cpp',
    '_ZN22AnimationSequenceEntry': 'AnimationSequence.cpp',
    '_ZN22ArenaPlantPositionData': 'PlayerPlantData.cpp',
    '_ZN22ArtifactBoostValueInfo': 'ArtifactImprovedPropertySheet.cpp',
    '_ZN22BaseReadIntoBufferTask': 'BaseResStreamsDriver.cpp',
    '_ZN22CardGameLevelBonusData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN22CardGameStarRewardData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN22CardTargetCursorConfig': 'CardType.cpp',
    '_ZN22ChristmasAccessoryData': 'ActivityConfig.cpp',
    '_ZN22ChristmasAccessoryInfo': 'PlayerInfo.cpp',
    '_ZN22ConsumptionActivedData': 'ActivityConfig.cpp',
    '_ZN22ConsumptionActivedItem': 'UITourismOctober.cpp',
    '_ZN22ConveyorSpeedCondition': 'CustomLevelSeedBankTemplate.cpp',
    '_ZN22CornucopiaShopItemData': 'CornucopiaMgr.cpp',
    '_ZN22CustomLevelWorldParams': 'CustomLevelMgr.cpp',
    '_ZN22CustomWaveEventDinoRun': 'CustomLevelMgr.cpp',
    '_ZN22DailyAchievementRecord': 'PlayerInfo.cpp',
    '_ZN22DangerRoomBuyOfferInfo': 'NetworkDangerRoomBuyOfferInfo.cpp',
    '_ZN22DangerRoomDropTypeInfo': 'UITourismOctober.cpp',
    '_ZN22DangerRoomNewPlantInfo': 'DangerRoomModule.cpp',
    '_ZN22DarkWizardTargetSorter': 'ZombieDarkWizard.cpp',
    '_ZN22DeltaWorldMapEventInfo': 'DeltaPlayerProfileInfo.cpp',
    '_ZN22FirstRechargeAwardData': 'PVZVersion.cpp',
    '_ZN22HolidayEventBannerData': 'HolidayEventProperties.cpp',
    '_ZN22JoustPlayerLoadoutData': 'LevelReplayData.cpp',
    '_ZN22JuggledProjectileTimer': 'Plant_Stephania.cpp',
    '_ZN22LevelBasedModifierInfo': 'LevelModifierModuleCollection.cpp',
    '_ZN22LevelDefinitionForTask': 'Board.cpp',
    '_ZN22LinkedTileInstanceData': 'FutureStage.cpp',
    '_ZN22NetworkShopContentData': 'CShopTabUI.cpp',
    '_ZN22Network_PlayerSyncData': 'NewPVPMgr.cpp',
    '_ZN22NewPVPBattlePassBundle': 'UINewPVPBattlePassBundle.cpp',
    '_ZN22NewPVPZombiePacketInfo': 'NewPVPSeedBank.cpp',
    '_ZN22NewPVPZombiePlayerInfo': 'NewPVPSaveBattleInfoData.cpp',
    '_ZN22NewRecallBankDayReward': 'NewRecallBankLine.cpp',
    '_ZN22PVZ1ModeLevelBonusData': 'PVZ1ModeMainEntryData.cpp',
    '_ZN22PackMemberFunctionBase': 'NetworkMsgProcess.cpp',
    '_ZN22PennyGiftBoxConfigData': 'PennyGiftBoxData.cpp',
    '_ZN22PlantWarsLevelTeamData': 'LocalProfileSaveData.cpp',
    '_ZN22PlantWarsWorldTeamData': 'LocalProfileSaveData.cpp',
    '_ZN22PlayerSurveyStringData': 'AssetsManagerEx.cpp',
    '_ZN22PredefinedLoadoutEntry': 'PVZVersion.cpp',
    '_ZN22ProtectedGridItemEntry': 'PVZVersion.cpp',
    '_ZN22RedPackLeaderBoardInfo': 'RedPackUI.cpp',
    '_ZN22S2C_CodeRewardPlantNum': 'MetricsCollector.cpp',
    '_ZN22S2C_Occupy_Ending_Data': 'S2C_PVP_Ending.cpp',
    '_ZN22S2C_PVP_BigMapMainInfo': 'NetworkData.cpp',
    '_ZN22S2C_PlayerGetGachaInfo': 'S2C_GachaDetailMsg.cpp',
    '_ZN22S2C_PlayerGetRedPacket': 'AssetsManagerEx.cpp',
    '_ZN22SecretAreaRewardDetail': 'SecretAreaRewardMgr.cpp',
    '_ZN22SecretAwardDisplayInfo': 'SecretStoreMgr.cpp',
    '_ZN22SingleHandedWaveZombie': 'PVZVersion.cpp',
    '_ZN22SpringLoginRewardBonus': 'S2C_7DaysLoginSpringReward.cpp',
    '_ZN22StormZombieInstruction': 'StormZombieSpawner.cpp',
    '_ZN22TGAArtifactPresentData': 'TGALogMgr.cpp',
    '_ZN22TGADailyRechargeReward': 'TGALogMgr.cpp',
    '_ZN22TGAGeneEnhancementData': 'TGALogMgr.cpp',
    '_ZN22TGALogDaveTreasureData': 'TGALogMgr.cpp',
    '_ZN22TGALogPlantLevelupData': 'TGALogMgr.cpp',
    '_ZN22TGALogTransGenosisData': 'NetworkMsgProcess.cpp',
    '_ZN22TGANewRecallBundleData': 'TGALogMgr.cpp',
    '_ZN22TGANoviceSevenDaysData': 'TGALogMgr.cpp',
    '_ZN22TidalChangeDescription': 'TidalChangeWaveAction.cpp',
    '_ZN22TourismOctoberTaskDate': 'TourismOctoberData.cpp',
    '_ZN22UnchartedModeBoostData': 'UnchartedModeNetworkMgr.cpp',
    '_ZN22UnchartedModeLevelData': 'UnchartedModeNetworkMgr.cpp',
    '_ZN22UnchartedModeWorldData': 'UnchartedModeNetworkMgr.cpp',
    '_ZN22ValidateDamageInfoData': 'RiftValidateMgr.cpp',
    '_ZN22ValidateToolPacketData': 'ValidateGamePlayData.cpp',
    '_ZN22ValidateZombieInfoData': 'RiftValidateMgr.cpp',
    '_ZN22WizardCrucibleDescribe': 'InitialGridItemWizardCrucible.cpp',
    '_ZN22WorldResourceLoadState': 'WorldMap.cpp',
    '_ZN22ZombieConditionsStruct': 'Zombie.cpp',
    '_ZN22ZombieCreatedCacheData': 'NewPVPGameSubsystem.cpp',
    '_ZN22ZombieResistenceConfig19ResistenceValueInfo': 'ZombieResistenceConfig.cpp',
    '_ZN23ArtifactCameraSubSystem16PlantCaptureInfo': 'UITourismOctober.cpp',
    '_ZN23BurdockBatter_SubSystem18EnhancedProjectile': 'BurdockBatter_SubSystem.cpp',
    '_ZN23ChristmasAccessoryBonus': 'ActivityConfig.cpp',
    '_ZN23CustomChallengeEvilDave': 'CustomChallenge.cpp',
    '_ZN23CustomLevelEndBonusInfo': 'CustomNetworkEndPlayData.cpp',
    '_ZN23DangerRoomActivatedData': 'ActivityConfig.cpp',
    '_ZN23DangerRoomHighScoreInfo': 'PVZVersion.cpp',
    '_ZN23DiscountShopContentData': 'DiscountShopContentWidget.cpp',
    '_ZN23EnableWidgetInputAction': 'MiniGameDialogAdaptor.cpp',
    '_ZN23EntitySearch_InGridRows': 'EntityFinder.cpp',
    '_ZN23GriditemBarrelZombieDes': 'UITourismOctober.cpp',
    '_ZN23GriditemSchoolBusParams': 'SchoolBusWaveAction.cpp',
    '_ZN23LevelofTheDayActiveInfo': 'PlayerInfo.cpp',
    '_ZN23NationalDayActivityDate': 'NationalDayRewardConfigInfo.cpp',
    '_ZN23NetworkFShopContentData': 'NetworkFShopInfo.cpp',
    '_ZN23Network_NewPVPDuanState': 'NewPVPMainEntry.cpp',
    '_ZN23Network_NewPVPSmallDuan': 'UINewPVPDuan.cpp',
    '_ZN23NewPVPGridItemPlacement': 'PVZVersion.cpp',
    '_ZN23NewPVPGuideDoorLocation': 'NewPVPAreaGuideDoor.cpp',
    '_ZN23NewPVPTutorialPlantInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN23NewPVPZombieLevelUpData': 'NewPVPPropertySheet.cpp',
    '_ZN23NewPVPZombieUpgradeData': 'NewPVPGameSubsystem.cpp',
    '_ZN23NewPVPZombieUpgradeInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN23PTriggerZombieAddParams5Param': 'UITourismOctober.cpp',
    '_ZN23PlantFamilyDisplayValue': 'PlantFamilyMgr.cpp',
    '_ZN23PlantWarsStarRewardData': 'PlantWarsUtils.cpp',
    '_ZN23PneumaticDelayCondition': 'PneumaticSeedBank.cpp',
    '_ZN23ReconstructionComponent': 'PVZVersion.cpp',
    '_ZN23RedPacketRankRewardInfo': 'RedPacketRewardInfo.cpp',
    '_ZN23RiftLevelDifficultyData': 'AdaptorDifficultyModifierFullScrollWidget.cpp',
    '_ZN23RiftWidgetAnimationData': 'AdaptorRiftTourneyResultsScreen.cpp',
    '_ZN23S2C_PlayerGetAvatarInfo': 'S2C_GachaDetailMsg.cpp',
    '_ZN23ServerLevelOfTheDayInfo': 'PlayerInfo.cpp',
    '_ZN23SpringBossActivatedData': 'ActivityConfig.cpp',
    '_ZN23SpringGiftActivatedData': 'ActivityConfig.cpp',
    '_ZN23StarLevelConditionEntry': 'Projectile.cpp',
    '_ZN23StoreGiftsActivatedData': 'ActivityConfig.cpp',
    '_ZN23TGAAccumulatedLoginData': 'TGALogMgr.cpp',
    '_ZN23TGACustomLevelShareData': 'TGALogMgr.cpp',
    '_ZN23TGAFirstRechargeNewData': 'TGALogMgr.cpp',
    '_ZN23TGAHappyVaseBreakerData': 'UIHappyVaseBreaker.cpp',
    '_ZN23TGALogPennyTreasureData': 'TGALogMgr.cpp',
    '_ZN23TGAOneYuanRedPacketData': 'TGALogMgr.cpp',
    '_ZN23TGATreasurePavilionData': 'TGALogMgr.cpp',
    '_ZN23ZombossPostStageScoring': 'ZombieZombossMech.cpp',
    '_ZN23stMiniGame_rankItemInfo': 'MiniGameRankItemConfig.cpp',
    '_ZN24AdaptorMultiPurchaseItem27MultiPurchaseItemVisibility': 'AdaptorMultiPurchaseItem.cpp',
    '_ZN24ArtifactPlantDisplayInfo': 'PVZVersion.cpp',
    '_ZN24CardGameEndPlayParamData': 'CardGameOutro.cpp',
    '_ZN24CurrentArtifactBoostInfo': 'ArtifactMgr.cpp',
    '_ZN24CustomChallengeLastStand': 'CustomChallenge.cpp',
    '_ZN24CustomLevelShopItemDData': 'CustomLevelShopData.cpp',
    '_ZN24CustomNetworkPreviewData': 'CustomLevelItemWidget.cpp',
    '_ZN24CustomWaveEventBlackHole': 'CustomLevelMgr.cpp',
    '_ZN24CustomWaveEventFrostWind': 'CustomLevelMgr.cpp',
    '_ZN24CustomWaveEventSandStorm': 'CustomLevelMgr.cpp',
    '_ZN24DangerRoomTrainingRecord': 'PVZVersion.cpp',
    '_ZN24DisableWidgetInputAction': 'MiniGameDialogAdaptor.cpp',
    '_ZN24EntitySearch_InRectangle': 'EntityFinder.cpp',
    '_ZN24EntitySearch_TouchingRay': 'EntityFinder.cpp',
    '_ZN24FestivalPlantRandomIndex': 'PlayerInfo.cpp',
    '_ZN24GravestoneForceSpawnData': 'PVZVersion.cpp',
    '_ZN24HydrocotyledrummerParams': 'Plant_HydrocotyleDrummer.cpp',
    '_ZN24ManholePipelineSpawnInfo': 'DangerRoomSteamDesigner.cpp',
    '_ZN24NationalRewardFromServer': 'NetworkMsgProcess.cpp',
    '_ZN24NetworkArtifactBoostData': 'ArtifactImprovedPropertySheet.cpp',
    '_ZN24NetworkFestivalEntryData': 'NetworkFestivalEntryInfo.cpp',
    '_ZN24NewPVPBattlePassRankData': 'UITourismOctober.cpp',
    '_ZN24NewPVPTrainingPacketInfo': 'AdaptorNewPVPTrainingEntry.cpp',
    '_ZN24PVZ1ModeEndPlayParamData': 'PVZ1ModeOutro.cpp',
    '_ZN24PartyAssistWishBonusInfo': 'PartyAssistMgr.cpp',
    '_ZN24PennyGiftBoxRankItemData': 'PVZVersion.cpp',
    '_ZN24PineappleProjectileTimer': 'Plant_Pineapple.cpp',
    '_ZN24PlantAdventureRewardInfo': 'MetricsCollector.cpp',
    '_ZN24PlantNewAvatarPiecesInfo': 'PlayerInfo.cpp',
    '_ZN24PlantPlacementProperties': 'CustomLevelElementsTemplate.cpp',
    '_ZN24PlantWarsLeaderBoardData': 'PlantWarsUtils.cpp',
    '_ZN24RiftPerkDisplayEntryData': 'AdaptorRiftPerkProgressionDisplayEntry.cpp',
    '_ZN24RtReflectionDelegateBase': 'GameObject.cpp',
    '_ZN24S2C_FightZodiacStateInfo': 'FightZodiacData.cpp',
    '_ZN24S2C_TimeLevelNodeContent': 'S2C_TimeLevelNodeList.cpp',
    '_ZN24StingerLocationStateData': 'PVZVersion.cpp',
    '_ZN24TGAFestivalRedPacketData': 'TGALogMgr.cpp',
    '_ZN24TGALogRechargeRewardData': 'TGALogMgr.cpp',
    '_ZN24TGAPlantSpecialOfferData': 'TGALogMgr.cpp',
    '_ZN24TGARechargeDailySignData': 'TGALogMgr.cpp',
    '_ZN24TopHUDLayoutHelperParams': 'JoustLandingScreenTopHUD.cpp',
    '_ZN24TourismOctoberPlayerData': 'UITourismOctober.cpp',
    '_ZN24TourismOctoberPlayerInfo': 'UITourismOctober.cpp',
    '_ZN24ToyNightRewardPlayerData': 'PVZVersion.cpp',
    '_ZN24WorldEventCompletionData': 'PlayerInfo.cpp',
    '_ZN24ZombieCarnieDoveArtifact11ZombieCache': 'ZombieCarnieDoveArtifact.cpp',
    '_ZN24ZombieLaneChangingRecord': 'ZombieLaneChangingSubsystem.cpp',
    '_ZN24_ElectricCurrantLocation': 'ElectricCurrantFence.cpp',
    '_ZN25ArtifactDisplayActionInfo': 'ArtifactDisplayBoard.cpp',
    '_ZN25ArtifactZombieDisplayInfo': 'PVZVersion.cpp',
    '_ZN25BaseReadWithoutBufferTask': 'BaseResStreamsDriver.cpp',
    '_ZN25ChallengeDropOutItemGroup': 'ChallengeDropOutItems.cpp',
    '_ZN25ComponentLinearBurstProps': 'ComponentLinearBurst.cpp',
    '_ZN25ComponentRadiusBurstProps': 'ComponentWarmingRadius.cpp',
    '_ZN25ConvertProjectileNameNode': 'ComponentProjectileConverterProps.cpp',
    '_ZN25CustomChallengeStatueMaze': 'CustomChallenge.cpp',
    '_ZN25CustomNetworkAppraiseData': 'UITourismOctober.cpp',
    '_ZN25CustomWaveEventSpiderRain': 'CustomLevelMgr.cpp',
    '_ZN25DynamicZombiesInstruction': 'WaveManagerModule.cpp',
    '_ZN25ElectricCircleDescription': 'Plant_Mangosteen.cpp',
    '_ZN25EntitySearch_MatchesClass': 'EntityFinder.cpp',
    '_ZN25EntitySearch_WithinRadius': 'EntityFinder.cpp',
    '_ZN25JoustAPIPostCompleteMatch': 'JoustUtils.cpp',
    '_ZN25JoustHowToPlayScreenEntry': 'AssetsManagerEx.cpp',
    '_ZN25JoustTournamentDefinition': 'JoustSchedule.cpp',
    '_ZN25LaternRiddleDisplayConfig': 'RedPacketRewardInfo.cpp',
    '_ZN25LevelEditorDiableCardItem': 'LevelEditorDisablePlant.cpp',
    '_ZN25LimitedSummonRankItemData': 'PVZVersion.cpp',
    '_ZN25NetworkRedPackDisplayData': 'NetworkRedPackDisplayInfo.cpp',
    '_ZN25NetworkfthShopContentData': 'NetworkfthShopInfo.cpp',
    '_ZN25PlantWarsEndPlayParamData': 'PlantWarsUtils.cpp',
    '_ZN25RiftLeaderboardRewardInfo': 'RiftUtils.cpp',
    '_ZN25S2C_LoadPlayerProfileData': 'S2C_LoadPlayerProfile.cpp',
    '_ZN25S2C_PVP_PreGardenRankInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN25SeedRainContentProperties': 'SeedRainModule.cpp',
    '_ZN25SpartanBambooMatrixSystem11PlantMatrix': 'SpartanBambooMatrixSystem.cpp',
    '_ZN25StoredDangerRoomEventData': 'PlayerInfo.cpp',
    '_ZN25TGAMiniGameCollectionData': 'TGALogMgr.cpp',
    '_ZN25TGAMonthlyCardSpecialData': 'TGALogMgr.cpp',
    '_ZN25TimelineActionRunnerEvent': 'TimelineActionRunner.cpp',
    '_ZN25UnchartedBirthdayTaskInfo': 'CallofWishTrainItem.cpp',
    '_ZN25UnchartedModePlantNumData': 'PVZ2UnchartedModeResultScreen.cpp',
    '_ZN25WalkPixelsPerSecondHelper': 'GlobalFunctions.cpp',
    '_ZN25ZombiePlacementProperties': 'CustomLevelElementsTemplate.cpp',
    '_ZN26AdvertisementWatchTimeInfo': 'PlayerInfo.cpp',
    '_ZN26ArcadePropertySheetHelpers10ArcadeMode': 'ArcadePropertySheet.cpp',
    '_ZN26ArcadePropertySheetHelpers11ArcadeLevel': 'ArcadePropertySheetHelpers.cpp',
    '_ZN26ArcadePropertySheetHelpers12ArcadeReward': 'ArcadePropertySheetHelpers.cpp',
    '_ZN26ArcadePropertySheetHelpers12UnlockSource': 'ArcadePropertySheet.cpp',
    '_ZN26ArcadePropertySheetHelpers15ArcadeLevelPack': 'ArcadePropertySheetHelpers.cpp',
    '_ZN26ArcadePropertySheetHelpers15PowerUpMetaData': 'ArcadePropertySheetHelpers.cpp',
    '_ZN26ArcadePropertySheetHelpers17PowerUpCollection': 'ArcadePropertySheet.cpp',
    '_ZN26ArcadePropertySheetHelpers18ArcadeEndlessLevel': 'ArcadePropertySheet.cpp',
    '_ZN26ArtifactGashaponAffectInfo': 'ArtifactGashaponSubSystem.cpp',
    '_ZN26CardGameZombieGenerateData': 'CardGameModule.cpp',
    '_ZN26ComponentDamageRadiusProps': 'Plant_PhatBeet.cpp',
    '_ZN26ConveyorAddSeedInstruction': 'ModifyConveyorWaveAction.cpp',
    '_ZN26ConveyorDropDelayCondition': 'ConveyorSeedBank.cpp',
    '_ZN26CustomChallengeTowerDefend': 'CustomChallenge.cpp',
    '_ZN26CustomChallengeVaseBreaker': 'CustomChallenge.cpp',
    '_ZN26DangerRoomSpecialOfferInfo': 'DangerRoomSpecialOfferUI.cpp',
    '_ZN26EffectObject_GardenerGrass6SawDes': 'Plant_GardenerGrass.cpp',
    '_ZN26EffectObject_GardenerGrass8ShakeDes': 'EffectObject_GardenerGrass.cpp',
    '_ZN26ElectricExplodeDescription': 'MangosteenElectricCircle.cpp',
    '_ZN26EntitySearch_InGridSquares': 'EntityFinder.cpp',
    '_ZN26EntitySearch_TouchingPoint': 'EntityFinder.cpp',
    '_ZN26FairyTaleWitchTargetSorter': 'ZombieFairyTaleWitch.cpp',
    '_ZN26GarlicAffectedZombieRecord': 'Plant_Garlic.cpp',
    '_ZN26GiftFoReturnTaskRewardInfo': 'GiftFoReturnData.cpp',
    '_ZN26JoustLeaderboardRewardInfo': 'JoustUtils.cpp',
    '_ZN26LevelModuleDifficultyEntry': 'gnu_cxxFunctions.cpp',
    '_ZN26LevelScoringPlantBonusTier': 'LevelScoringModuleProperties.cpp',
    '_ZN26MonthlyCardSpecialItemData': 'MonthlyCardSpecialData.cpp',
    '_ZN26NetworkArtifactBoostConfig': 'Network_ArtifactImprovedPropertySheet.cpp',
    '_ZN26Network_NewPVPShopItemData': 'UINewPVPShop.cpp',
    '_ZN26NewPVPAddZombieMessageData': 'NewPVPGameSubsystem.cpp',
    '_ZN26RechargeDailySignDayReward': 'RechargeDailySignActivityManager.cpp',
    '_ZN26SoundWaveCircleDescription': 'Plant_HeavenDatura.cpp',
    '_ZN26StatueMazeModuleProperties10MatrixInfo': 'StatueMazeModule.cpp',
    '_ZN26StatueMazeModuleProperties7SetInfo': 'CustomLevelChallengeStatueMazeTemplate.cpp',
    '_ZN26TGAAnniversaryTreasureData': 'TGALogMgr.cpp',
    '_ZN26TGANewplayerCollectionData': 'TGALogMgr.cpp',
    '_ZN26TreasurePavilionRewardInfo': 'PlayerInfo.cpp',
    '_ZN26ZombiePumpkinScarecrowBird10PlantCache': 'ZombiePumpkinScarecrowBird.cpp',
    '_ZN26_AlarmSagittifoliaLocation': 'AlarmSagittifoliaFence.cpp',
    '_ZN27ActivityCollectionContainer': 'ActivityCollectionUIFutureGiftBox.cpp',
    '_ZN27AdvertisementWatchCountInfo': 'PlayerInfo.cpp',
    '_ZN27AndroidAppStartFromUrlEvent': 'AndroidAppDriver.cpp',
    '_ZN27ArtifactPrismTowerSubSystem17LaserShooterProps': 'ArtifactPrismTower.cpp',
    '_ZN27AutumnHarvestLotteryHistory': 'UITourismOctober.cpp',
    '_ZN27ComponentWarmingRadiusProps': 'ComponentWarmingRadius.cpp',
    '_ZN27CornucopiaBubbleHarvestData': 'CornucopiaData.cpp',
    '_ZN27CustomChallengeSingleHanded': 'CustomChallenge.cpp',
    '_ZN27CustomWaveEventRaidingParty': 'CustomLevelMgr.cpp',
    '_ZN27CustomWaveEventSummonZombie': 'CustomLevelMgr.cpp',
    '_ZN27ElectriciteaBurstProperties': 'Plant_Electricitea.cpp',
    '_ZN27EntitySearch_TouchingCircle': 'EntityFinder.cpp',
    '_ZN27EntitySearch_WithinRadius2D': 'EntityFinder.cpp',
    '_ZN27FirstRechargeExtraBonusData': 'FirstRechargeExtraManager.cpp',
    '_ZN27LanternRiddlesActivatedData': 'ActivityConfig.cpp',
    '_ZN27NewPVPGameEventPositionData': 'NewPVPGameData.cpp',
    '_ZN27NewPVPZombiePacketLevelInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN27PropertyAnimatorCurveParams': 'HotUIPropertyAnimator.cpp',
    '_ZN27RechargeRewardContentConfig': 'RechargeRewardConfig.cpp',
    '_ZN27RiftAPIResponseLeagueChange': 'RiftNetworkMgr.cpp',
    '_ZN27S2C_PlayerGetGachaGroupInfo': 'S2C_GachaDetailMsg.cpp',
    '_ZN27SpecialGameLevelRefreshData': 'ActivityConfig.cpp',
    '_ZN27TGAAnniversaryNurturingData': 'TGALogMgr.cpp',
    '_ZN27TGARenaissanceChallengeData': 'TGALogMgr.cpp',
    '_ZN27TowerDefendPlantUpgradeInfo': 'CustomLevelChallengeTowerDefendTemplate.cpp',
    '_ZN27TowerDefendPlantUpgradeTree': 'BesiegeModule.cpp',
    '_ZN27UnchartedModeLevelBonusData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN27UnchartedModeStarRewardData': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN27ZombossRobotSpawnZombieInfo': 'ZombossRobotSpawnNormalZombieActionHandler.cpp',
    '_ZN28AdaptorSeedPacketEntryConfig': 'AdaptorSeedPacketEntry.cpp',
    '_ZN28AlarmSagittifoliaFenceSystem11DelayAction': 'AlarmSagittifoliaFenceSystem.cpp',
    '_ZN28ArtifactMeteorProjectileInfo': 'ArtifactMeteorProjectile.cpp',
    '_ZN28ArtifactVaseConfigProperties': 'ArtifactVase.cpp',
    '_ZN28AutumnHarvestLotteryItemData': 'AutumnHarvestNetworkData.cpp',
    '_ZN28CustomWaveEventParachuteRain': 'CustomLevelMgr.cpp',
    '_ZN28EliminatePlacementProperties': 'EliminateProperties.cpp',
    '_ZN28HappyVaseBreakerSpecialLevel': 'HappyVaseBreakerTaskPassSpecialData.cpp',
    '_ZN28LimitedSummonRankPriviewData': 'LimitedSummonData.cpp',
    '_ZN28NetworkCardGameRewardContent': 'NetworkCardGameReward.cpp',
    '_ZN28Network_NewPVPSunUpgradeInfo': 'Network_NewPVPPropertySheet.cpp',
    '_ZN28NewPVPZombieLevelUpValueData': 'NewPVPMgr.cpp',
    '_ZN28PVZCachedNetworkTableManager': 'PVZCachedNetworkTable.cpp',
    '_ZN28PlantWarsLeaderBoardLineData': 'PlantWarsUtils.cpp',
    '_ZN28StarChallengePlantBeforeLine9BoundMold': 'StarChallengePlantBeforeLine.cpp',
    '_ZN28StorePlantGiftsActivatedData': 'ActivityConfig.cpp',
    '_ZN29AdaptorRichManEventListConfig': 'AdaptorRichManEventList.cpp',
    '_ZN29AssetsManagerDelegateProtocol': 'ConfigUpdateMgr.cpp',
    '_ZN29AutumnHarvestRewardPlayerData': 'PVZVersion.cpp',
    '_ZN29ComponentConditionRadiusProps': 'ComponentConditionRadius.cpp',
    '_ZN29ConveyorRemoveSeedInstruction': 'ModifyConveyorWaveAction.cpp',
    '_ZN29DailyAchievementActivatedData': 'ActivityConfig.cpp',
    '_ZN29LevelEditorCardPlantInterface': 'LevelEditorGroundSetting.cpp',
    '_ZN29NetworkArtifactPresentContent': 'ArtifactPresentMgr.cpp',
    '_ZN29Network_NewPVPPlantPacketInfo': 'Network_NewPVPPropertySheet.cpp',
    '_ZN29Network_NewPVPZombieLevelInfo': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN29Network_NewPVPZombieSkillInfo': 'Network_NewPVPPropertySheet.cpp',
    '_ZN29NoviceSevenDaysIntegralReward': 'GlobalFunctions.cpp',
    '_ZN29PVZ1ModeLevelBonusNetworkData': 'PVZ1ModeMainEntryData.cpp',
    '_ZN29PlantWarsLeaderBoardBonusData': 'PlantWarsUtils.cpp',
    '_ZN29RandomJitteredWaveInstruction': 'RandomJitteredWaveConfig.cpp',
    '_ZN29TGADangerRoomSpecialOfferData': 'TGALogMgr.cpp',
    '_ZN29ZombossRobotAirDropZombieInfo': 'ZombossRobotAirDropZombieActionHandler.cpp',
    '_ZN2AK12IAkStreamMgr': 'WwiseInteractiveAudioDriver.cpp',
    '_ZN2AK9StreamMgr17IAkIOHookBlocking': 'CAkDefaultIOHookBlocking.cpp',
    '_ZN2AK9StreamMgr17IAkLowLevelIOHook': 'CAkDefaultIOHookBlocking.cpp',
    '_ZN2AK9StreamMgr23IAkFileLocationResolver': 'CAkDefaultIOHookBlocking.cpp',
    '_ZN2EA2IO10AutoJNIEnv': 'File.cpp',
    '_ZN2EA2IO13EntryFindData': 'IO.cpp',
    '_ZN2EA2IO17DirectoryIterator5Entry': 'DirectoryIterator.cpp',
    '_ZN2EA2IO4Path11PathString8': 'File.cpp',
    '_ZN2EA2IO4Path11PathStringW': 'Directory.cpp',
    '_ZN2EA2IO4Path12PathString16': 'IO.cpp',
    '_ZN2EA2IO4Path12PathString32': 'Path.cpp',
    '_ZN2EA2IO7IStream': 'FileStream.cpp',
    '_ZN2EA4StdC10ScanfLocal10CharBitmap': 'ScanfLocal.cpp',
    '_ZN2EA4StdC10ScanfLocal10FormatData': 'ScanfLocal.cpp',
    '_ZN2EA4StdC10ScanfLocal11DoubleValue': 'ScanfLocal.cpp',
    '_ZN2EA4StdC10ScanfLocal14SscanfContext8': 'StdC.cpp',
    '_ZN2EA4StdC10ScanfLocal15SscanfContext16': 'StdC.cpp',
    '_ZN2EA4StdC10ScanfLocal15SscanfContext32': 'StdC.cpp',
    '_ZN2EA4StdC12SprintfLocal10FormatData': 'SprintfLocal.cpp',
    '_ZN2EA4StdC12SprintfLocal10WriteInfo8': 'SprintfLocal.cpp',
    '_ZN2EA4StdC12SprintfLocal16SnprintfContext8': 'StdC.cpp',
    '_ZN2EA4StdC12SprintfLocal17SnprintfContext16': 'StdC.cpp',
    '_ZN2EA4StdC12SprintfLocal17SnprintfContext32': 'StdC.cpp',
    '_ZN2EA4Text10GlyphCache9GlyphInfo': 'GlyphCache.cpp',
    '_ZN2EA4Text10Typesetter7RunInfo': 'Typesetter.cpp',
    '_ZN2EA4Text11FontMetrics': 'Text.cpp',
    '_ZN2EA4Text12OTFTagStruct': 'Text.cpp',
    '_ZN2EA4Text12StyleManager11TextStyleEx': 'StyleManager.cpp',
    '_ZN2EA4Text13FeatureLookup': 'Text.cpp',
    '_ZN2EA4Text15FontDescription': 'FaceSource.cpp',
    '_ZN2EA4Text15TextRunIterator': 'Layout.cpp',
    '_ZN2EA4Text15TextureIterator': 'GlyphCache.cpp',
    '_ZN2EA4Text16BaselineIterator': 'Bezier2DIterator.cpp',
    '_ZN2EA4Text16LayoutScratchpad': 'Text.cpp',
    '_ZN2EA4Text18CoreAllocatorStack': 'Text.cpp',
    '_ZN2EA4Text19FontServerDestroyer': 'Text.cpp',
    '_ZN2EA4Text19PolygonFontInternal': 'PolygonFont.cpp',
    '_ZN2EA4Text22OTFTableDirectoryEntry': 'OTF.cpp',
    '_ZN2EA4Text7Effects': 'EffectsProcessor.cpp',
    '_ZN2EA4Text7TextRun': 'Text.cpp',
    '_ZN2EA4Text9Rectangle': 'Text.cpp',
    '_ZN2EA6Thread10ThreadTime': 'mutex.cpp',
    '_ZN2EA6Thread18EAThreadGlobalVars': 'Thread.cpp',
    '_ZN2EA6Thread9AutoFutex': 'FontServer.cpp',
    '_ZN2EA9Allocator22EAIOEASTLCoreAllocator': 'DriveInfo32.cpp',
    '_ZN2EA9Allocator27EAIOPathStringCoreAllocator': 'IO.cpp',
    '_ZN2KV': 'MetricsCollector.cpp',
    '_ZN2UI4UDim': 'StringHelper.cpp',
    '_ZN30ActivityRechargePlantPieceData': 'ActivityConfig.cpp',
    '_ZN30AdaptorNewPVPEntryScreenConfig': 'AdaptorNewPVPPlayerInfoScreen.cpp',
    '_ZN30AdaptorRichManEventEntryConfig': 'AdaptorRichManEventEntry.cpp',
    '_ZN30AdaptorRiftResultsScreenParams': 'RiftOutro.cpp',
    '_ZN30ArtifactDinosaurHornProperties14TypeToSpawnDes': 'Effect_DinoRun_For_Artifact_Dinosaur_horn.cpp',
    '_ZN30ComponentDamageTossRadiusProps': 'ComponentDamageTossRadius.cpp',
    '_ZN30CurrentSelectedPlantPacketInfo': 'AdaptorNewPVPEntryScreen.cpp',
    '_ZN30DangerRoomLevelDesignerHelpers12FlagWavePool': 'DangerRoomLevelDesignerHelpers.cpp',
    '_ZN30EntitySearch_MatchesZombieType': 'EntityFinder.cpp',
    '_ZN30EntitySearch_TouchingRectangle': 'EntityFinder.cpp',
    '_ZN30JoustWinStreakDisplayEntryData': 'AdaptorJoustWinStreakDisplayEntry.cpp',
    '_ZN30MagicMirrorTeleportationObject': 'MagicMirrorTeleportationArraySubSystem.cpp',
    '_ZN30NetworkSecretAreaRewardContent': 'NetworkSecretAreaReward.cpp',
    '_ZN30Network_NewPVPZombiePacketInfo': 'Network_NewPVPPropertySheet.cpp',
    '_ZN30NewPVPBattlePassPrivilegeAward': 'NewPVPBattlePassData.cpp',
    '_ZN30RiftZombossRewardDifficultySet': 'RiftZombossRewards.cpp',
    '_ZN30WorldMapActivityPieceLevelData': 'PVZVersion.cpp',
    '_ZN30ZombieGargantuarProjectilePair': 'ZombieGargantuar.cpp',
    '_ZN31AdaptorJoustResultsScreenParams': 'AdaptorJoustResultsScreen.cpp',
    '_ZN31GridItemZombieMirrorQueenMirror16CopyZombieParams': 'GridItemZombieMirrorQueenMirror.cpp',
    '_ZN31Network_NewPVPZombieLevelUpData': 'NewPVPMgr.cpp',
    '_ZN31Network_NewPVPZombieUpgradeInfo': 'Network_NewPVPPropertySheet.cpp',
    '_ZN31PennyGiftBoxRankPriviewItemData': 'PenntGiftBoxItem.cpp',
    '_ZN31PlantFamilyOptionalDisplayValue': 'AssetsManagerEx.cpp',
    '_ZN31SpawnZombiesJitteredInstruction': 'WaveHelpers.cpp',
    '_ZN31UnchartedModeFestivalRewardData': 'UnchartedFestivalRewardItemWidget.cpp',
    '_ZN32AdaptorNewPVPTrainingEntryConfig': 'AdaptorNewPVPTrainingScreen.cpp',
    '_ZN32AdaptorRiftZombossProgressParams': 'AdaptorRiftZombossProgress.cpp',
    '_ZN32AndroidAppOrientationChangeEvent': 'AndroidAppDriver.cpp',
    '_ZN32ICloudRequestSTDCallbackFunction': 'StorePanelUI.cpp',
    '_ZN32LimitedSummonRankPriviewItemData': 'LimitedSummonData.cpp',
    '_ZN32NewPVPZombieLevelUpPropertySheet': 'NewPVPPropertySheet.cpp',
    '_ZN33AdaptorNewPVPMatchingScreenConfig': 'AdaptorNewPVPMatchingScreen.cpp',
    '_ZN33AdaptorRiftLeaderboardEntryConfig': 'AdaptorRiftLeaderboardEntry.cpp',
    '_ZN33ContentDownloaderDelegateProtocol': 'AssetsManagerEx.cpp',
    '_ZN33ICloudRequestCallbackFunctionBase': 'NetworkMsgProcess.cpp',
    '_ZN33MagicMirrorTeleportationArrayData': 'WaveActionMagicMirrorTeleportationArray.cpp',
    '_ZN33MiniGamePerkZombieGlobalStuckData': 'MiniGamePerkMgr.cpp',
    '_ZN33PVZ2UnchartedModeEndPlayParamData': 'ZombiesAteYourBrainsOutro.cpp',
    '_ZN34AdaptorJoustLeaderboardEntryConfig': 'AdaptorJoustLeaderboardConfig.cpp',
    '_ZN34MagicMirrorTeleportationArrayData2': 'WaveActionMagicMirrorTeleportationArrayProps2.cpp',
    '_ZN34MiniGameCollectionEndPlayParamData': 'MiniGameCollectionOutro.cpp',
    '_ZN34UnchartedWorldAnniversaryBonusInfo': 'PlayerInfo.cpp',
    '_ZN35AdaptorRiftPerkProgressScreenParams': 'AdaptorRiftPerkProgressScreen.cpp',
    '_ZN35DangerRoomSpecialOfferExtraItemData': 'DangerRoomSpecialOfferExtraManager.cpp',
    '_ZN35S2C_PlayerInfoCheatingCheckItemData': 'PlayerInfo.cpp',
    '_ZN36AdaptorJoustMatchLoadingScreenConfig': 'AdaptorJoustMatchLoadingScreen.cpp',
    '_ZN36Network_NewPVPZombieLevelUpValueData': 'NewPVPMgr.cpp',
    '_ZN36VaseBreakerEndlessEntityAndCountPair': 'PVZVersion.cpp',
    '_ZN37AdaptorRiftTourneyResultsScreenParams': 'AdaptorRiftTourneyResultsScreen.cpp',
    '_ZN37VaseBreakerEndlessStarZombiePlantPair': 'VaseBreakerEndlessProperties.cpp',
    '_ZN38AdaptorJoustTourneyResultsScreenParams': 'AdaptorJoustTourneyResultsScreen.cpp',
    '_ZN38AndroidApplicationDidBecomeActiveEvent': 'AndroidAppDriver.cpp',
    '_ZN39AndroidApplicationWillResignActiveEvent': 'AndroidAppDriver.cpp',
    '_ZN3Lua10StackClean': 'LMMessageRouter.cpp',
    '_ZN3Lua12DownloadInfo': 'LMMessageRouter.cpp',
    '_ZN3UFO7RiseDes': 'ArtifactUFO.cpp',
    '_ZN41AndroidApplicationDidEnterBackgroundEvent': 'AndroidAppDriver.cpp',
    '_ZN43AndroidApplicationWillBecomeForegroundEvent': 'AndroidAppDriver.cpp',
    '_ZN4EBox': 'EffectAnimRig_EndLevelBox.cpp',
    '_ZN4Sexy10FileWriter': 'RSBPatchGenerator.cpp',
    '_ZN4Sexy10Graphics3D': 'Graphics.cpp',
    '_ZN4Sexy10Graphics3D11LightColors': 'Graphics3D.cpp',
    '_ZN4Sexy10ModalFlags': 'WidgetContainer.cpp',
    '_ZN4Sexy10PILayerDef': 'PILayer.cpp',
    '_ZN4Sexy10RedeemInfo': 'TWPurchaseAdapter.cpp',
    '_ZN4Sexy10ResGenInfo': 'ResGenInfo.cpp',
    '_ZN4Sexy10ShaderInfo': 'AndroidGL20RenderEffect.cpp',
    '_ZN4Sexy10ShaderInfo12ShaderLayout': 'AndroidGL20RenderEffect.cpp',
    '_ZN4Sexy11CompiledMap4Node': 'CompiledMap.cpp',
    '_ZN4Sexy11DeviceImage19CachedImageDrawInfo': 'DeviceImage.cpp',
    '_ZN4Sexy11GLMeshPiece': 'SexyFunctions.cpp',
    '_ZN4Sexy11IFileSearch': 'PakInterface.cpp',
    '_ZN4Sexy11MemoryImage6TriRep3Tri': 'MemoryImage.cpp',
    '_ZN4Sexy11MemoryImage6TriRep5Level6Region': 'DeviceImage.cpp',
    '_ZN4Sexy11PIDeflector': 'PIEffect.cpp',
    '_ZN4Sexy11PIEffectDef': 'PIEffect.cpp',
    '_ZN4Sexy11ProductInfo': 'PurchaseBroker.cpp',
    '_ZN4Sexy11RtNameTable5Entry': 'RtNameTable.cpp',
    '_ZN4Sexy12DelegateBase': 'PlantAnimRig_Chomper.cpp',
    '_ZN4Sexy12EditListener': 'EditWidget.cpp',
    '_ZN4Sexy12MeshListener': 'AndroidGraphicsDriver.cpp',
    '_ZN4Sexy12PreModalInfo': 'WidgetManager.cpp',
    '_ZN4Sexy12RenderDevice': 'MemoryImage.cpp',
    '_ZN4Sexy12ScrollWidget7Overlay': 'ScrollWidget.cpp',
    '_ZN4Sexy13IHttpListener': 'NetworkServiceManager.cpp',
    '_ZN4Sexy13PIEmitterBase': 'PIEffect.cpp',
    '_ZN4Sexy13PIParticleDef': 'PIEffect.cpp',
    '_ZN4Sexy13RenderCommand': 'ImageFont.cpp',
    '_ZN4Sexy13RenderSurface': 'Pool.cpp',
    '_ZN4Sexy13ScrollSnapper': 'UniverseMapScrollSnapper.cpp',
    '_ZN4Sexy14AutoModalFlags': 'WidgetContainer.cpp',
    '_ZN4Sexy14CharToCharFunc': 'SexyAppBase.cpp',
    '_ZN4Sexy14DialogListener': 'SexyAppBase.cpp',
    '_ZN4Sexy14FileSearchInfo': 'PakInterface.cpp',
    '_ZN4Sexy14HRenderContext': 'MemoryImage.cpp',
    '_ZN4Sexy14MetricsManager6Report': 'MetricsManager.cpp',
    '_ZN4Sexy14PIInterpolator': 'PIEffect.cpp',
    '_ZN4Sexy14PIValuePoint2D': 'PIEffect.cpp',
    '_ZN4Sexy14RenderDevice3D': 'Graphics3D.cpp',
    '_ZN4Sexy14RtSerialBuffer': 'RtSerialRtonReader.cpp',
    '_ZN4Sexy14ScrollListener': 'ScrollbarWidget.cpp',
    '_ZN4Sexy14SliderListener': 'HotUIAdaptor.cpp',
    '_ZN4Sexy15ActiveFontLayer': 'ImageFont.cpp',
    '_ZN4Sexy15BaseGPUResource': 'BaseResStreamsDriver.cpp',
    '_ZN4Sexy15CharToWCharFunc': 'SexyAppBase.cpp',
    '_ZN4Sexy15IGraphicsDriver': 'AndroidGraphicsDriver.cpp',
    '_ZN4Sexy15IPaymentMonitor': 'PurchaseBroker.cpp',
    '_ZN4Sexy15PIParticleGroup': 'PIEffect.cpp',
    '_ZN4Sexy15PopAnimListener': 'PopAnimRig.cpp',
    '_ZN4Sexy16AndroidAppDriver22CallbackInstanceEquals': 'AndroidAppDriver.cpp',
    '_ZN4Sexy16BaseDiskResource': 'BaseResStreamsDriver.cpp',
    '_ZN4Sexy16BaseTaskResource': 'BaseResStreamsDriver.cpp',
    '_ZN4Sexy16CheckboxListener': 'NewOptionsDialog.cpp',
    '_ZN4Sexy16IHttpTransaction': 'NetworkServiceManager.cpp',
    '_ZN4Sexy16ISaveGameContext': 'FilesystemSaveGameContext.cpp',
    '_ZN4Sexy16NullRenderDevice': 'SexyAppBase.cpp',
    '_ZN4Sexy16RenderEffectPass': 'AndroidGL20RenderEffect.cpp',
    '_ZN4Sexy17AsyncThreadedTask': 'AsyncCreateFileOfSizeTask.cpp',
    '_ZN4Sexy17CharDataHashEntry': 'CharDataHashTable.cpp',
    '_ZN4Sexy17GraphicsAutoState': 'Board.cpp',
    '_ZN4Sexy17PIEmitterInstance': 'PIEffect.cpp',
    '_ZN4Sexy18BaseBufferResource': 'BaseResStreamsDriver.cpp',
    '_ZN4Sexy18PIParticleInstance': 'PIEffect.cpp',
    '_ZN4Sexy18RenderStateManager10StateValue': 'State.cpp',
    '_ZN4Sexy18RenderStateManager7Context12JournalEntry': 'State.cpp',
    '_ZN4Sexy18ResStreamsUnpacker9GroupInfo': 'ResStreamsUnpacker.cpp',
    '_ZN4Sexy18SharedRenderTarget4Pool5Entry': 'RtNameTable.cpp',
    '_ZN4Sexy19AsyncMainThreadTask': 'AsyncResumeRequestErrorTask.cpp',
    '_ZN4Sexy19ProxyWidgetListener': 'ScrollWidget.cpp',
    '_ZN4Sexy19ResourceManagerInfo': 'ResourceManager.cpp',
    '_ZN4Sexy20NonCopyableNamespace16NonCopyableClass': 'SexyAppBase.cpp',
    '_ZN4Sexy20NotificationListener': 'NotificationManagerGame.cpp',
    '_ZN4Sexy20PIEmitterInstanceDef': 'PIEffect.cpp',
    '_ZN4Sexy20ProfileEventListener': 'ProfileManager.cpp',
    '_ZN4Sexy21GLExtraRenderDataInfo': 'SexyFunctions.cpp',
    '_ZN4Sexy21NetworkServiceManager4Slot': 'NetworkServiceManager.cpp',
    '_ZN4Sexy21NetworkServiceRequest': 'NetworkServiceManager.cpp',
    '_ZN4Sexy21PIFreeEmitterInstance': 'PIEffect.cpp',
    '_ZN4Sexy21PIParticleDefInstance': 'PIEffect.cpp',
    '_ZN4Sexy21RenderEffectAutoState': 'PopAnimRig.cpp',
    '_ZN4Sexy21RenderEffectTechnique': 'AndroidGL20RenderEffect.cpp',
    '_ZN4Sexy22INetworkStatusListener': 'AndroidHttpDriver.cpp',
    '_ZN4Sexy22LeaderboardReadContext': 'Leaderboard.cpp',
    '_ZN4Sexy22NetworkServiceListener': 'ContentDownloader.cpp',
    '_ZN4Sexy27DummyNetworkServiceListener': 'NetworkServiceManager.cpp',
    '_ZN4Sexy28BaseDecompressThreadResource': 'BaseResStreamsDriver.cpp',
    '_ZN4Sexy33IInteractiveAudioCallbackListener': 'JamListener.cpp',
    '_ZN4Sexy5HWBRK': 'AndroidDiagDriver.cpp',
    '_ZN4Sexy5IFile': 'AndroidAsyncIOFile.cpp',
    '_ZN4Sexy5Image19CachedAtlasUVResult': 'Image.cpp',
    '_ZN4Sexy5Image22CachedImageAtlasUVInfo': 'Image.cpp',
    '_ZN4Sexy5Touch': 'AndroidAppDriver.cpp',
    '_ZN4Sexy6Event0': 'PVZDB.cpp',
    '_ZN4Sexy7PIForce': 'PIEffect.cpp',
    '_ZN4Sexy7PIValue': 'PIEffect.cpp',
    '_ZN4Sexy8AutoCrit': 'ResumableRequestInfo.cpp',
    '_ZN4Sexy8CritSect': 'RSBPatcher.cpp',
    '_ZN4Sexy8FlagsMod': 'WidgetManager.cpp',
    '_ZN4Sexy9Condition': 'AndroidDiagDriver.cpp',
    '_ZN4Sexy9Delegate0': 'Board.cpp',
    '_ZN4Sexy9EventBase': 'PVZDB.cpp',
    '_ZN4Sexy9GLContext': 'OpenGLIdRegistry.cpp',
    '_ZN4Sexy9PIBlocker': 'PIEffect.cpp',
    '_ZN4Sexy9PIEmitter': 'PIEffect.cpp',
    '_ZN4Sexy9PITexture': 'PIEffect.cpp',
    '_ZN4Sexy9PerfTimer': 'GlobalFunctions.cpp',
    '_ZN4Sexy9RtDbTable4Slot': 'RtDbTable.cpp',
    '_ZN5EItem': 'PVZVersion.cpp',
    '_ZN5FEAST10CLexBitSet': 'Feast.cpp',
    '_ZN5FEAST10CLibClient': 'Feast.cpp',
    '_ZN5FEAST10CPrsParser': 'Feast.cpp',
    '_ZN5FEAST11CLexNfaExpr': 'ILexLexer.cpp',
    '_ZN5FEAST11CLexNfaNode': 'ILexLexer.cpp',
    '_ZN5FEAST11CPrsASTNode': 'Feast.cpp',
    '_ZN5FEAST12CLexDfaTable': 'ILexLexer.cpp',
    '_ZN5FEAST13CPrsParseProd': 'Feast.cpp',
    '_ZN5FEAST13CPrsParseRule': 'IPrsParser.cpp',
    '_ZN5FEAST14CPrsParseState': 'Feast.cpp',
    '_ZN5FEAST16CLexDfaPartition': 'ILexLexer.cpp',
    '_ZN5FEAST19CLexDfaPartitionSet': 'Feast.cpp',
    '_ZN5FEAST8IPrsNode': 'Feast.cpp',
    '_ZN5FEAST9CDatArray': 'Feast.cpp',
    '_ZN5FEAST9CLexLexer': 'Feast.cpp',
    '_ZN5PVZDB11TableSchema': 'PVZDB.cpp',
    '_ZN5PVZDB16TableRuntimeInfo': 'PVZDB.cpp',
    '_ZN5eastl10fixed_pool': 'Widget.cpp',
    '_ZN5eastl12ListNodeBase': 'eastlFunctions.cpp',
    '_ZN6DColor': 'DTransformNode.cpp',
    '_ZN6SunGet': 'ZombieDevilsAlienGargantuar.cpp',
    '_ZN6Toggle': 'PVZRemoteControl.cpp',
    '_ZN7DMatrix': 'DTransformNode.cpp',
    '_ZN7MapPath': 'TimeTravelSelEntranceUI.cpp',
    '_ZN7SexyURL10KeyedValue': 'SexyURL.cpp',
    '_ZN7SexyURL5Range': 'SexyURL.cpp',
    '_ZN7TagData': 'CardGameBoardConfig.cpp',
    '_ZN7stAward': 'UIChagreDouble.cpp',
    '_ZN8AreaData': 'NewPVPMgr.cpp',
    '_ZN8AuthInfo': 'SocialMgr.cpp',
    '_ZN8AwardSet': 'GeneralAwardSet.cpp',
    '_ZN8BaseTask': 'BaseResStreamsDriver.cpp',
    '_ZN8CardInfo': 'PlayerInfo.cpp',
    '_ZN8DIniItem': 'DIniField.cpp',
    '_ZN8DropInfo': 'Board.cpp',
    '_ZN8ESection': 'EndLevelAward.cpp',
    '_ZN8GachaGet': 'AssetsManagerEx.cpp',
    '_ZN8HintAnim': 'PVZVersion.cpp',
    '_ZN8HintWord': 'HintUI.cpp',
    '_ZN8IconData': 'PVZ2UIStarLevelUp.cpp',
    '_ZN8ImageLib12BufferSource': 'ImageLib.cpp',
    '_ZN8LevelGem': 'UITourismOctober.cpp',
    '_ZN8LoginRet': 'WGPlatform.cpp',
    '_ZN8PathInfo': 'TestDragon.cpp',
    '_ZN8PerkData': 'PennyPerkMgr.cpp',
    '_ZN8RailInfo': 'CustomLevelMgr.cpp',
    '_ZN8ShareRet': 'WGPlatform.cpp',
    '_ZN8TipsData': 'ActivityConfig.cpp',
    '_ZN8TokenRet': 'UITourismOctober.cpp',
    '_ZN8WindInfo': 'HeianWindModule.cpp',
    '_ZN9AwardInfo': 'LevelReplayData.cpp',
    '_ZN9BossLevel': 'AssetsManagerEx.cpp',
    '_ZN9CListItem': 'CListPoolItem.cpp',
    '_ZN9DotStruct': 'PlantPhatBeetDotSystem.cpp',
    '_ZN9FinalPool': 'AchievementContent.cpp',
    '_ZN9HintImage': 'HintUI.cpp',
    '_ZN9LevelInfo': 'LevelUtils.cpp',
    '_ZN9LineEntry': 'LineBatcher.cpp',
    '_ZN9LootStats': 'Board.cpp',
    '_ZN9Lv5Switch': 'LocalProfileSaveData.cpp',
    '_ZN9OutroInfo': 'OutroManager.cpp',
    '_ZN9PFTrigger': 'IntroCinema.cpp',
    '_ZN9PFindData': 'PakInterface.cpp',
    '_ZN9PakRecord': 'PakInterface.cpp',
    '_ZN9PlantInfo': 'LMMessageRouter.cpp',
    '_ZN9PlayerSet': 'WorldCupConfig.cpp',
    '_ZN9PowerNode': 'PowerSet.cpp',
    '_ZN9SelectBox': 'TransGenosisUI.cpp',
    '_ZN9ShareInfo': 'SocialMgr.cpp',
    '_ZN9SheepInfo': 'ZombieDarkWizard.cpp',
    '_ZN9StoreData': 'UIMysteryStore.cpp',
    '_ZN9TGABundle': 'RechargeRewardContent.cpp',
    '_ZN9TextEntry': 'TextBatcher.cpp',
    '_ZN9ThemeData': 'RiftThemeMgr.cpp',
    '_ZN9TopicItem': 'ActiveConsumptionTab.cpp',
    '_ZN9TrackInfo': 'NetworkMsgProcess.cpp',
    '_ZN9TrialData': 'PlantTrialConfig.cpp',
    '_ZN9UIMetrics11UIEventInfo': 'UIMetrics.cpp',
    '_ZN9WakeupRet': 'WGPlatform.cpp',
    '_ZN9WatchInfo': 'PVZVersion.cpp',
    '_ZN9WidgetImg': 'PVPMapUI.cpp',
    '_ZN9plantInfo': 'ZombieBungee.cpp',
    '_ZNK10ValueRange': 'DangerRoomLevelDesignerHelpers.cpp',
    '_ZNK17EASquaredNullImpl': 'EASquared_Android.cpp',
    '_ZNK20RichmanTileEventBase': 'RichmanTileEvent_MoveForward.cpp',
    '_ZNK4Sexy12DelegateBase': 'PlantAnimRig_Chomper.cpp',
    '_ZNK4Sexy13RtWeakPtrBase': 'PowerupVaseBreakerMove.cpp',
    '_ZNK4Sexy14HRenderContext': 'MemoryImage.cpp',
    '_ZNK4Sexy14RtMixedPtrBase': 'PopAnim.cpp',
    '_ZNK4Sexy14RtSerialBuffer': 'RtSerialRtonReader.cpp',
    '_ZNK4Sexy15RtSerialRtonKey': 'RtDbTable.cpp',
    '_ZNK4Sexy16NullRenderDevice': 'SexyAppBase.cpp',
    '_ZNK4Sexy18RtSerialRtonReader': 'RtSerialRtonReader.cpp',
    '_ZNK4Sexy18RtSerializeContext': 'RtObject.cpp',
    '_ZNK4Sexy6Event0': 'PVZDB.cpp',
    '_ZNK4Sexy6RtName': 'PVZDB.cpp',
    '_ZNK4Sexy9Delegate0': 'Board.cpp',
    '_ZNK6DColor': 'DTransformNode.cpp',
    '_ZNK8DIniItem': 'DIniField.cpp',
    '_ZNK8IntRange': 'DropShipEffectAnim.cpp',
    '_ZN11SnapHandler': 'UniverseMap.cpp',
    '_ZN20NullRsbPatchListener': 'PVZRemoteControl.cpp',
    '_ZN21CSelectChangedHandler': 'CListUI.cpp',
    '_ZN2EA4Text5Point': 'PrimeTypeface.cpp',
    '_ZN2UI12PageListener': 'TrainingCampZombieDlg.cpp',
    '_ZN2UI13RadioListener': 'OfflineBoard.cpp',
    '_ZN2UI18TabControlListener': 'ActiveSummery.cpp',
    '_ZN4Sexy11SexyVector2': 'FishingModuleEditor.cpp',
    '_ZN4Sexy11SexyVector2dVEf': 'FishingModuleEditor.cpp',
    '_ZN4Sexy11SexyVector2eqERKS0_': 'FishingModuleEditor.cpp',
    '_ZN4Sexy11SexyVector2mIERKS0_': 'FishingModuleEditor.cpp',
    '_ZN4Sexy11SexyVector2mLEf': 'FishingModuleEditor.cpp',
    '_ZN4Sexy11SexyVector2neERKS0_': 'FishingModuleEditor.cpp',
    '_ZN4Sexy11SexyVector2pLERKS0_': 'FishingModuleEditor.cpp',
    '_ZN4Sexy11SexyVector3': 'Board.cpp',
    '_ZN4Sexy11SexyVector3aSERKS0_': 'Board.cpp',
    '_ZN4Sexy11SexyVector3dVEf': 'Board.cpp',
    '_ZN4Sexy11SexyVector3mIERKS0_': 'Board.cpp',
    '_ZN4Sexy11SexyVector3mLEf': 'Board.cpp',
    '_ZN4Sexy11SexyVector3pLERKS0_': 'Board.cpp',
    '_ZN4Sexy11SexyVector4': 'Board.cpp',
    '_ZN4Sexy12SimpleMatrix': 'WorldMap_Minimap.cpp',
    '_ZN4Sexy13RtWeakPtrBase': 'PowerupVaseBreakerMove.cpp',
    '_ZN4Sexy14RtMixedPtrBase': 'PopAnim.cpp',
    '_ZN4Sexy15RtInvokeVariant': 'Reflection.cpp',
    '_ZN4Sexy15RtSerialCommand': 'Reflection.cpp',
    '_ZN4Sexy15RtSerialRtonKey': 'RtDbTable.cpp',
    '_ZN4Sexy16RtSerialRtonSync': 'ActionSubSystem.cpp',
    '_ZN4Sexy18MTAutoDisallowRand': 'SexyAppBase.cpp',
    '_ZN4Sexy18ResStreamsLoadDesc': 'ResStreamsManager.cpp',
    '_ZN4Sexy18RtSerialRtonReader11ReaderScope': 'RtSerialRtonReader.cpp',
    '_ZN4Sexy18RtSerialRtonReader3Key': 'AnimRigLayerSet.cpp',
    '_ZN4Sexy18RtSerializeContext': 'RtObject.cpp',
    '_ZN4Sexy29InteractiveSoundManagerConfig': 'AudioMgr.cpp',
    '_ZN4Sexy5Point': 'SkyCityStage.cpp',
    '_ZN4Sexy6FPoint': 'Bezier.cpp',
    '_ZN4Sexy6RtName': 'PVZDB.cpp',
    '_ZN4Sexy8SexyRay2': 'EntityFinder.cpp',
    '_ZN4Sexy9RtDbTable12TableOptions': 'PVZDB.cpp',
    '_ZN9_PacketId10InitCommonEv': 'PurchaseBroker.cpp',
    '_ZN9_PacketIdC1Ev': 'PurchaseBroker.cpp',
    '_ZN9_PacketIdC2Ev': 'PurchaseBroker.cpp',
    '_ZN9_PacketIdD1Ev': 'PurchaseBroker.cpp',
    '_ZN9_PacketIdD2Ev': 'PurchaseBroker.cpp',
    '_ZNK4Sexy11SexyVector2': 'FishingModuleEditor.cpp',
    '_ZNK4Sexy11SexyVector2dvEf': 'FishingModuleEditor.cpp',
    '_ZNK4Sexy11SexyVector2miERKS0_': 'FishingModuleEditor.cpp',
    '_ZNK4Sexy11SexyVector2mlEf': 'FishingModuleEditor.cpp',
    '_ZNK4Sexy11SexyVector2ngEv': 'FishingModuleEditor.cpp',
    '_ZNK4Sexy11SexyVector2plERKS0_': 'FishingModuleEditor.cpp',
    '_ZNK4Sexy11SexyVector3': 'Board.cpp',
    '_ZNK4Sexy11SexyVector3dvERKS0_': 'Board.cpp',
    '_ZNK4Sexy11SexyVector3dvEf': 'Board.cpp',
    '_ZNK4Sexy11SexyVector3miERKS0_': 'Board.cpp',
    '_ZNK4Sexy11SexyVector3mlERKS0_': 'Board.cpp',
    '_ZNK4Sexy11SexyVector3mlEf': 'Board.cpp',
    '_ZNK4Sexy11SexyVector3ngEv': 'Board.cpp',
    '_ZNK4Sexy11SexyVector3plERKS0_': 'Board.cpp',
}


# File -> classes it defines one strong method of but belongs to another file.
NOT_OWNED = {
    'UltraAndroid.cpp': {'_ZN5Ultra'},
    'GetImageOptions.cpp': {'_ZN4Sexy15ResourceManager'},
}


# File -> nested-class symbol prefixes that live in their own files.
NESTED_ELSEWHERE = {
    'RtId.cpp': ('_ZN4Sexy4RtId3Uid', '_ZNK4Sexy4RtId3Uid', '_ZN4Sexy4RtId9OfflineId', '_ZNK4Sexy4RtId9OfflineId'),
    'AndroidGL20RenderEffect.cpp': ('_ZN4Sexy23AndroidGL20RenderEffect15ParamCollection',
                                    '_ZN4Sexy23AndroidGL20RenderEffect9ParamData'),
    'IResStreamsDriver.cpp': ('_ZN4Sexy17IResStreamsDriver4Task', '_ZN4Sexy17IResStreamsDriver12TaskResource'),
    'RtSerialRtonReader.cpp': ('_ZN4Sexy18RtSerialRtonReader3Key',),
}


def analyse(source, obj, game, game_syms, game_names, manifest_unit=None):
    """-> rows [(state, same, total, bytes, label)]. state: ok / near / todo.

    Scope = every game method of a class this file owns (has a strong symbol
    for, or is in EXTRA_OWNED). A stub's scope comes from units.json.
    """
    if obj == STUB:
        funcs = (manifest_unit or {}).get('funcs', [])
        rows = [('todo', 0, 0, size, pretty(sym)) for sym, size in funcs]
        rows.sort(key=lambda r: (-r[3], r[4]))
        return rows

    ours = Elf(obj)
    strong, defined = set(), set()
    for n, v, s, sh, t, b in ours.symbols_full():
        if sh and t == 2 and s:
            defined.add(n)
            if b == 1:               # STB_GLOBAL
                strong.add(n)

    by_class = {}   # Owner.zn -> [Owner, our syms, our strong syms]
    for n in defined:
        o = owned_prefixes(n)
        if not o:
            continue
        slot = by_class.setdefault(o.zn, [o, [], []])
        slot[1].append(n)
        if n in strong:
            slot[2].append(n)

    scope = {}
    for zn, (o, mine, mine_strong) in by_class.items():
        owned = bool(mine_strong) or zn in EXTRA_OWNED or OWNED_BY.get(zn) == os.path.basename(source)
        if zn in OWNED_BY and OWNED_BY[zn] != os.path.basename(source):
            continue
        if zn in NOT_OWNED.get(os.path.basename(source), ()):
            continue
        if not owned:
            continue
        for name in _range(game_names, o.zn) + _range(game_names, o.znk):
            scope[name] = game_syms[name][1]
    for name in generated():
        scope.pop(name, None)
    for name in list(scope):
        if name.startswith(NESTED_ELSEWHERE.get(os.path.basename(source), ())) and name in game_syms and not name.endswith('aSEOS1_'):
            del scope[name]
    our_funcs = defined

    rows = []
    for sym, size in scope.items():
        if sym not in our_funcs:
            rows.append(('todo', 0, 0, size, pretty(sym)))
            continue
        th = asmdiff.listing(game, sym)
        mn = asmdiff.listing(ours, sym)
        if th is None or mn is None:
            rows.append(('todo', 0, 0, size, pretty(sym)))
            continue
        same, tot, _ = asmdiff.compare(th, mn)
        ok = same == tot and len(th) == len(mn)
        rows.append(('ok' if ok else 'near', same, tot, size, pretty(sym)))
    rows.sort(key=lambda r: (r[0] == 'ok', r[0] == 'near', -r[3], r[4]))
    return rows


_GAME = None
_GENERATED = None


def generated():
    """Compiler-made template instantiations, left out of every file's scope."""
    global _GENERATED
    if _GENERATED is None:
        path = os.path.join(config.HERE, 'units.json')
        _GENERATED = frozenset(json.load(open(path)).get('generated', ())) if os.path.exists(path) else frozenset()
    return _GENERATED


def _game():
    """The reference library, parsed once per process."""
    global _GAME
    if _GAME is None:
        g = Elf(config.TARGET_LIB)
        syms = {}
        for n, v, s, sh, t in g.symbols():
            if t == 2 and sh and s:
                syms.setdefault(n, (v, s))
        _GAME = (g, syms, sorted(syms))
    return _GAME


_ROWS_DIR = os.path.join(config.BUILD, 'rows-cache')
_CODE = [os.path.abspath(__file__)] + [os.path.join(os.path.dirname(os.path.abspath(__file__)), 'lib', f)
                                       for f in ('asmdiff.py', 'pvzelf.py')]


def _rows_key(source, obj, manifest_unit):
    """Hash of everything analyse() reads: the object bytes, its owner rules, the game and the differ itself."""
    import hashlib
    h = hashlib.sha1()
    lib = os.stat(config.TARGET_LIB)
    h.update(repr((os.path.basename(source), manifest_unit, len(generated()), lib.st_size, lib.st_mtime_ns)).encode())
    for f in _CODE:
        h.update(open(f, 'rb').read())
    h.update(open(obj, 'rb').read() if obj != STUB else b'stub')
    return h.hexdigest()


def _rows_for(job):
    """analyse() in a worker: the reference ELF cannot be pickled, so rebuild it. Reused while its inputs are byte-identical."""
    source, obj, rel, manifest_unit = job
    path = os.path.join(_ROWS_DIR, _rows_key(source, obj, manifest_unit) + '.json')
    try:
        return source, [tuple(r) for r in json.load(open(path, encoding='utf-8'))]
    except (OSError, ValueError):
        pass
    game, game_syms, game_names = _game()
    rows = analyse(source, obj, game, game_syms, game_names, manifest_unit)
    os.makedirs(_ROWS_DIR, exist_ok=True)
    tmp = f'{path}.{os.getpid()}'
    json.dump(rows, open(tmp, 'w', encoding='utf-8'))
    os.replace(tmp, path)
    return source, rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('filter', nargs='?', help='only files whose path contains this')
    ap.add_argument('--todo', action='store_true', help='hide matched functions')
    ap.add_argument('--report', metavar='PATH',
                    help='write a splat-schema progress report (measures + units)')
    ap.add_argument('--check', metavar='PATH', help='compare to a baseline report, exit 1 on regression')
    ap.add_argument('--jobs', type=int, default=min(8, (os.cpu_count() or 4)))
    ap.add_argument('--quiet', action='store_true', help='totals only')
    ap.add_argument('--all', action='store_true',
                    help='list functions for every unit, scaffold stubs included')
    ap.add_argument('--cache', action='store_true', default=True,
                    help='skip recompiling a file whose sources are older than its object')
    ap.add_argument('--no-cache', dest='cache', action='store_false',
                    help='recompile every unit from scratch')
    args = ap.parse_args()

    global _CACHE, _PCH
    _CACHE = args.cache
    files = [s for s in sources() if not args.filter or args.filter.lower() in s.lower()]
    # a look at a few files uses wd.py's precompiled headers; the tree check keeps the stock compiler
    _PCH = bool(args.filter) and len(files) <= 3 and not args.check
    if not files:
        print('no source files')
        return 0

    manifest = {'units': {}, 'unplaced': {}}
    mpath = os.path.join(config.HERE, 'units.json')
    if os.path.exists(mpath):
        manifest = json.load(open(mpath))

    game, game_syms, game_names = _game()

    objs, fails = {}, {}
    # biggest objects first, so one slow file does not run alone at the end
    cost = lambda s: os.path.getsize(fastcc.object_path(s)) if os.path.exists(fastcc.object_path(s)) else 1 << 40
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        for source, obj, errs in ex.map(compile_one, sorted(files, key=cost, reverse=True)):
            if obj:
                objs[source] = obj
            else:
                fails[source] = errs

    # analyse is pure Python (capstone + diffing) and holds the GIL, so it
    # needs processes, not the threads the compile step uses.
    todo = [(s, objs[s], os.path.relpath(s, config.HERE).replace(os.sep, '/'),
             manifest['units'].get(os.path.relpath(s, config.HERE).replace(os.sep, '/')))
            for s in files if s not in fails]
    analysed = {}
    if len(todo) > 1 and args.jobs > 1:
        with concurrent.futures.ProcessPoolExecutor(max_workers=args.jobs) as ex:
            for source, rows in ex.map(_rows_for, todo):
                analysed[source] = rows
    else:
        for job in todo:
            source, rows = _rows_for(job)
            analysed[source] = rows

    units = []
    t_ok = t_near = t_todo = 0
    b_ok = b_all = 0

    for source in files:
        rel = os.path.relpath(source, config.HERE).replace(os.sep, '/')
        if source in fails:
            print(f'{RED}COMPILE FAILED{OFF}  {rel}')
            for e in fails[source]:
                print(f'    {e}')
            units.append({'name': rel, 'error': fails[source],
                          'total_code': 0, 'matched_code': 0, 'matched_code_percent': 0.0,
                          'total_functions': 0, 'matched_functions': 0,
                          'matched_functions_percent': 0.0, 'fuzzy_match_percent': 0.0,
                          'functions': []})
            continue

        rows = analysed[source]
        n_ok = sum(1 for r in rows if r[0] == 'ok')
        n_near = sum(1 for r in rows if r[0] == 'near')
        n_todo = sum(1 for r in rows if r[0] == 'todo')
        bo = sum(r[3] for r in rows if r[0] == 'ok')
        allb = sum(r[3] for r in rows)
        fuzzy = sum(size * (1.0 if state == 'ok' else (same / tot if tot else 0.0))
                    for state, same, tot, size, _ in rows)

        t_ok += n_ok; t_near += n_near; t_todo += n_todo
        b_ok += bo; b_all += allb

        pct = 100.0 * bo / allb if allb else 0.0
        stub = objs[source] is STUB
        tag = f'{GREY}stub{OFF} ' if stub else ''
        if args.quiet:
            pass
        elif not rows:
            print(f'{GREY}    -   {n_ok}/{len(rows):<4d} fn  (unmapped)      {tag}{rel}{OFF}')
        else:
            colour = GREEN if pct == 100 else (GREY if not n_ok else YELLOW)
            print(f'{colour}{pct:5.1f}%{OFF}  {n_ok}/{len(rows):<4d} fn  {bo}/{allb} B   '
                  f'{tag}{BOLD}{rel}{OFF}')

        u = {
            'name': rel,
            'total_code': allb, 'matched_code': bo,
            'matched_code_percent': round(pct, 2),
            'total_functions': len(rows), 'matched_functions': n_ok,
            'matched_functions_percent': round(100.0 * n_ok / len(rows), 2) if rows else 0.0,
            'fuzzy_match_percent': round(100.0 * fuzzy / allb, 2) if allb else 0.0,
        }
        u['functions'] = [
            {'name': label, 'size': size, 'matched': state == 'ok',
             'fuzzy_match_percent': round(100.0 * same / tot, 2) if tot else 0.0}
            for state, same, tot, size, label in sorted(rows, key=lambda r: (-r[3], r[4]))]
        units.append(u)

        if not args.quiet and (args.all or args.filter or n_ok or n_near):
            for state, same, tot, size, label in rows:
                if state == 'ok' and args.todo:
                    continue
                if state == 'ok':
                    print(f'     {GREEN}OK  {OFF} {size:5d} B  {label}')
                elif state == 'near':
                    print(f'     {YELLOW}{same:3d}/{tot:<4d}{OFF}{size:5d} B  {label}')
                else:
                    print(f'     {GREY}--   {size:5d} B  {label}{OFF}')

    pct = 100.0 * b_ok / b_all if b_all else 0.0
    n_fn = t_ok + t_near + t_todo
    total_fuzzy = sum(u['fuzzy_match_percent'] * u['total_code'] for u in units)

    started = [u for u in units if u['matched_functions']]
    s_ok = sum(u['matched_code'] for u in started)
    s_all = sum(u['total_code'] for u in started)
    unplaced = manifest.get('unplaced', {})

    report = {
        'generated': datetime.datetime.now(datetime.timezone.utc).isoformat(timespec='seconds'),
        'measures': {
            'total_functions': n_fn, 'matched_functions': t_ok,
            'matched_functions_percent': round(100.0 * t_ok / n_fn, 2) if n_fn else 0.0,
            'total_code': b_all, 'matched_code': b_ok,
            'matched_code_percent': round(pct, 2),
            'fuzzy_match_percent': round(total_fuzzy / b_all, 2) if b_all else 0.0,
            'started_units': len(started), 'total_units': len(units),
            'started_code': s_all, 'started_matched_code': s_ok,
            'started_percent': round(100.0 * s_ok / s_all, 2) if s_all else 0.0,
            'unplaced_functions': unplaced.get('functions', 0),
            'unplaced_code': unplaced.get('code', 0),
            'compile_failures': len(fails),
        },
        'units': units,
    }

    print()
    print(f'{BOLD}started  {s_ok}/{s_all} B  '
          f'{100.0 * s_ok / s_all if s_all else 0:.1f}%   in {len(started)}/{len(units)} units{OFF}')
    print(f'{BOLD}overall  {b_ok}/{b_all} B  {pct:.2f}%   '
          f'({t_ok}/{n_fn} functions placed'
          + (f', {unplaced["functions"]} unplaced' if unplaced.get('functions') else '')
          + f'){OFF}'
          + (f'   {RED}{len(fails)} compile failure(s){OFF}' if fails else ''))

    if args.report:
        with open(args.report, 'w') as f:
            json.dump(report, f, indent=2)
        print(f'wrote {args.report}')

    rc = 1 if fails else 0
    if args.check:
        base = json.load(open(args.check))
        rc = max(rc, regressions(base, report, args.check))
    return rc


def regressions(base, now, baseline_path):
    """Nonzero if any unit matches fewer bytes than the baseline."""
    was = {u['name']: u for u in base.get('units', [])}
    bad = 0
    for u in now['units']:
        b = was.get(u['name'])
        if b is None:
            continue
        if u.get('error') or u['matched_code'] < b.get('matched_code', 0):
            print(f'{RED}REGRESSION{OFF}  {u["name"]}: '
                  f'{b.get("matched_code", 0)} -> {u["matched_code"]} bytes matched')
            bad = 1
    for name in set(was) - {u['name'] for u in now['units']}:
        print(f'{RED}REGRESSION{OFF}  {name}: unit gone from the tree')
        bad = 1
    if not bad:
        print(f'{GREEN}no regressions against {os.path.basename(baseline_path)}{OFF}')
    return bad


if __name__ == '__main__':
    raise SystemExit(main())
