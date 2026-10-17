#!/usr/bin/env python3
"""layout.py -- maps a source stem or old-layout path to its studio-style folder under src/PvZ2/."""

import re

GROUPS = ('Core', 'Gameplay', 'Modes', 'UI', 'Network', 'Social', 'Meta',
          'Profile', 'Services', 'Data', 'Managers', 'Tools', 'Debug')

_SUBDIR = {
    'PVP': 'Modes/PVP', 'DNode': 'UI/DNode', 'UIEditor': 'Tools/UIEditor',
    'TodLib': 'Core/TodLib', 'iCloud': 'Network/iCloud', 'wechat': 'Network/wechat',
    'NoticeBoard': 'Network/NoticeBoard', 'logServer': 'Network/Logging/logServer',
    'LogCollector': 'Network/Logging/LogCollector',
    'net': 'Network',
}

_ENTITY = {'plants': 'Gameplay/Plants', 'zombies': 'Gameplay/Zombies'}

# (regex on file stem, folder); first hit wins
_RULES = [
    (r'^(Plant|Zombie|Creature)(Type|AnimRig|Framework|Action|ConditionTracker|Group|Utils)?$', 'Gameplay/Entities'),
    (r'^Plant', 'Gameplay/Plants'),
    (r'^(Zomboss|Zombie)', 'Gameplay/Zombies'),
    (r'^GridItem|^GridSquare|^Gravestone|^ManholePipeline|^RiverEntity', 'Gameplay/GridItems'),
    (r'^Effect|^StandaloneEffect|^ScoreEffect|^PopAnimEffect|^Lightning|^NewLightning|^StarLightning|^Fuse$|^FloatingIce|^ToadstoolGas|^SpeedChange', 'Gameplay/Effects'),
    (r'Powerup|PowerUp|^PowerSet|^PowerTile', 'Gameplay/Powerups'),
    (r'Projectile$|Missile$|^Cannon|^Bomb$|^Flying|^DandelionBomb|^NewRayEntity|^RayEntity|^PooyanShooter|^Snake$|^SharkMinion|^AgaveSwordLight|^BladeKee|^HorsebeanPlane|^Momotaro|^RichMan|^RiverCrossing|^SkatingGuacodile|^StarvingChomper|^HighTideSign|^Armor$|^Shield$|^DamageInfo|^DamageLifetime|^TargetInfo|^MeleePlantTargeter|^BossAircraft|^BronzeDeadWinCon|^JamApplier|^JamStage|^Eliminate', 'Gameplay/Combat'),
    (r'WaveAction|^Wave|^SimpleZombieSpawner|SpawnerZ|ZombieSpawner|^Initial(Plant|Zombie|GridItem)', 'Gameplay/Waves'),
    (r'^Collectable|Bank$|^CoinBank|^SunProducer', 'Gameplay/Collectables'),
    (r'^Seed|^ConveyorSeedBank|^PneumaticSeedBank', 'Gameplay/SeedBank'),
    (r'^WorldMap|^UniverseMap|^WorldData|^UniverseWorldInfo|^UniverseUnlockGate|^MapEventItem|^StarLevelWorldMapEvent|^DefaultWorldMapEditor', 'Gameplay/WorldMap'),
    (r'^Intro|Tutorial|Outro|^PuzzleTip|^QuickJump|^FadeOut|^VictoryOutro|^StandardLevelIntro|^PowerTileIntro', 'Gameplay/Tutorials'),
    (r'Stage$|^MiniBoard|^OfflineBoard|^Board|^Lawn|^ModularBoardEntity|^Artifact(DisplayBoard|SkateBoard)', 'Gameplay/Board'),
    (r'^Level|^CustomLevel', 'Gameplay/Level'),
    (r'Module$', 'Gameplay/Modules'),
    (r'^Component', 'Gameplay/Components'),
    (r'Subsystem$|SubSystem$', 'Gameplay/Subsystems'),
    (r'Cursor$', 'Gameplay/Cursors'),
    (r'^Rift|^AdaptorRift|^Joust|^AdaptorJoust|^Arena|^NewPVP|^NewerPVP|^PVPMap|^PvpMap|^PVP', 'Modes/PVP'),
    (r'DangerRoom', 'Modes/DangerRoom'),
    (r'^StarChallenge|Challenge$|^Challenge|^BossChallenge', 'Modes/Challenges'),
    (r'Minigame$|^MiniGame', 'Modes/Minigames'),
    (r'^Card|^PVZ1|^PVZ2Uncharted|^EASquared|^Dino|^Penny|^Beghouled|^Crazy', 'Modes'),
    (r'^TwoYear|^Present|^Festival|^SpringGift|^Christmas|^NationalDay|^LanternRiddles|^IceYear|^Active|^StarConvert|^HeroPlant', 'Meta/Events'),
    (r'^Achievement|^DailyAchievement|^NewAchievement|^INewAchievement|^Daily|^Leaderboard|Lottery|^Gacha|^RedPacket|Reward|^Award|^Consumption|^ZMatch|^TravelLog|^GeneralTask|^DaveTask|^PinataStyle|^Collection$|^Probability|^GuessRatio|^GameCenter|^IShare', 'Meta'),
    (r'^PlayerInfo|^UserInfo|^UserPrefs|^Profile|^PlayerList|^PlayerIdentity|^Draper|SaveData|^SaveGame|^MergePlayer|^OfflineData|DataPersistor|^IDataPersistor|^Arcade(Save|Progress)', 'Profile'),
    (r'^PVZ(Cached|Package|Remote|Version|Recharge)|^ICloud|Wechat|WeChat|^TGALog', 'Network'),
    (r'^HotUI', 'UI/HotUI'),
    (r'^Adaptor|Adaptor$', 'UI/Adaptors'),
    (r'UI$|^UI|^PVZ2UI|^PVZUI|Widget|Dialog|Dlg$|Screen|Drawer|ListView|Button|Popup|HUD|Panel|View|Bar$|Meter|Cell|Slider|TextEntry|Overlay|Tab$|Toast|Tooltip|^MainMenu|^StoreUI|^ComboBox|^ScrollingCounter|^IViewContainer|^DailySignPage|^TopHUD|^ZMatchShop|^PlantDisplay|^GachaItem|^RewardImage|^PlantPieceCompletion|^PrimeText|^PlantHeadshot|^PlantNewAvatar', 'UI'),
    (r'^Ad[A-Z]|^SuperSonic|^Install|^Metrics|^Connectivity|^Network|^FakeHttp|^PackageContents|^Assets|^PVZManifest|^PvZ2NetworkService|^NotificationManager|^Message$|^MagentoService|^PurchaseBroker|^ContentDownloader|^OnlineData|^ToolPackets|^RvsChecker|^AccountRemove|^StreamingMusic', 'Network'),
    (r'NameMapper|Mapper$', 'Data/Mappers'),
    (r'Mgr$|Manager$', 'Managers'),
    (r'Config$|PropertySheet$|Props$|^PVZDB|^PVZTypes|^GameFeatureType|^GameInfoUtil|^PVZGameInfo|^ObjectTypeDescriptor', 'Data'),
    (r'^Cheat|Cheats$|^AutoTest|^CommandConsole|^Console|^DebugLog|^CrazyOlafTest', 'Debug'),
]
_RULES = [(re.compile(r), f) for r, f in _RULES]


def folder_for(stem):
    """Studio folder (under src/PvZ2/) for a flat file stem, 'Core' when nothing matches."""
    for rx, f in _RULES:
        if rx.search(stem):
            return f
    return 'Core'


def studio(path):
    """Old-layout repo path -> studio-layout path; paths outside src/PvZ2 and already-moved paths pass through."""
    parts = path.split('/')
    if parts[:2] != ['src', 'PvZ2'] or len(parts) < 3 or parts[2] in GROUPS:
        return path
    if parts[2] in _ENTITY:
        return '/'.join(['src', 'PvZ2', _ENTITY[parts[2]]] + parts[3:])
    if len(parts) > 3:
        head = _SUBDIR.get(parts[2])
        if head:
            return '/'.join(['src', 'PvZ2', head] + parts[3:])
    if len(parts) == 3:
        return f'src/PvZ2/{folder_for(parts[2][:-4])}/{parts[2]}'
    return path
