//
//  PlantNameMapperServerID.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//

#include "PvZ/NameMapper.h"
#include "PvZ/PlantType.h"

__asm__(".local __dso_handle\n.comm __dso_handle,8,8");

static PlantNameMapperServerID& (*const s_keepGetInstance)() __attribute__((used)) = &PlantNameMapperServerID::GetInstance;

/////////////// Lifecycle ///////////////

PlantNameMapperServerID::PlantNameMapperServerID()
{
    std::map<std::string, int> idMap;
    idMap["peashooter"] = 1001;
    idMap["sunflower"] = 1002;
    idMap["wallnut"] = 1003;
    idMap["potatomine"] = 1004;
    idMap["cabbagepult"] = 1005;
    idMap["iceburg"] = 1006;
    idMap["bloomerang"] = 1007;
    idMap["twinsunflower"] = 1008;
    idMap["bonkchoy"] = 1009;
    idMap["springbean"] = 1010;
    idMap["spikeweed"] = 1011;
    idMap["snapdragon"] = 1012;
    idMap["powerlily"] = 1013;
    idMap["squash"] = 1014;
    idMap["chilibean"] = 1015;
    idMap["splitpea"] = 1016;
    idMap["jalapeno"] = 1017;
    idMap["gravebuster"] = 1018;
    idMap["snowpea"] = 1019;
    idMap["torchwood"] = 1020;
    idMap["kernelpult"] = 1021;
    idMap["lightningreed"] = 1022;
    idMap["coconutcannon"] = 1023;
    idMap["melonpult"] = 1024;
    idMap["peapod"] = 1025;
    idMap["imitater"] = 1026;
    idMap["repeater"] = 1027;
    idMap["spikerock"] = 1028;
    idMap["tallnut"] = 1029;
    idMap["threepeater"] = 1030;
    idMap["wintermelon"] = 1031;
    idMap["cherry_bomb"] = 1032;
    idMap["peach"] = 1033;
    idMap["firegourd"] = 1034;
    idMap["turnip"] = 1035;
    idMap["bamboo"] = 1036;
    idMap["magnifyinggrass"] = 1037;
    idMap["laser_bean"] = 1039;
    idMap["starfruit"] = 1040;
    idMap["blover"] = 1041;
    idMap["empea"] = 1042;
    idMap["citron"] = 1043;
    idMap["holonut"] = 1044;
    idMap["powerplant"] = 1045;
    idMap["smallcherry"] = 1046;
    idMap["carrotlauncher"] = 1047;
    idMap["carrotmissile"] = 1048;
    idMap["puffshroom"] = 1049;
    idMap["fumeshroom"] = 1050;
    idMap["hypnoshroom"] = 1051;
    idMap["sunshroom"] = 1052;
    idMap["sunbean"] = 1053;
    idMap["peanut"] = 1054;
    idMap["magnetshroom"] = 1055;
    idMap["streetlamp"] = 1056;
    idMap["coffeebean"] = 1057;
    idMap["iceshroom"] = 1058;
    idMap["fireshroom"] = 1059;
    idMap["oakshooter"] = 1060;
    idMap["dandelion"] = 1061;
    idMap["broccoli"] = 1062;
    idMap["pamegranate"] = 1063;
    idMap["lilypad"] = 1064;
    idMap["bowlingbulb"] = 1065;
    idMap["tanglekelp"] = 1066;
    idMap["banana"] = 1067;
    idMap["guacodile"] = 1068;
    idMap["homingthistle"] = 1069;
    idMap["chomper"] = 1070;
    idMap["lemon"] = 1071;
    idMap["ghostpepper"] = 1072;
    idMap["sweetpotato"] = 1073;
    idMap["cracker"] = 1074;
    idMap["lotusshower"] = 1075;
    idMap["sapfling"] = 1076;
    idMap["hurrikale"] = 1077;
    idMap["firepeashooter"] = 1078;
    idMap["hotpotato"] = 1079;
    idMap["pepperpult"] = 1080;
    idMap["chardguard"] = 1081;
    idMap["stunion"] = 1082;
    idMap["xshot"] = 1083;
    idMap["rafflesia"] = 1084;
    idMap["acorn"] = 1085;
    idMap["chestnut"] = 1086;
    idMap["smallChestnut"] = 1087;
    idMap["sugarcane"] = 1088;
    idMap["doublesamara"] = 1089;
    idMap["anthurium"] = 1090;
    idMap["asparagus"] = 1091;
    idMap["saucer"] = 1092;
    idMap["horsebean"] = 1093;
    idMap["groundcherry"] = 1094;
    idMap["pineapple"] = 1095;
    idMap["bashopult"] = 1096;
    idMap["magicshroom"] = 1097;
    idMap["roseswordman"] = 1098;
    idMap["electricblueberry"] = 1099;
    idMap["greenturnip"] = 111001;
    idMap["birthsunflower"] = 111002;
    idMap["endurian"] = 111003;
    idMap["pumpkinwitch"] = 111004;
    idMap["goldleaf"] = 111006;
    idMap["akee"] = 111008;
    idMap["redstinger"] = 111009;
    idMap["stallia"] = 111010;
    idMap["lavaguava"] = 111011;
    idMap["toadstool"] = 111012;
    idMap["cottonyeti"] = 111013;
    idMap["jackfruit"] = 111014;
    idMap["agave"] = 111015;
    idMap["kiwifruit"] = 111016;
    idMap["wintersweet"] = 111017;
    idMap["dragonfruit"] = 111018;
    idMap["pinkstarfruit"] = 111019;
    idMap["matchflower"] = 111020;
    idMap["flamelady"] = 111021;
    idMap["gatlingpea"] = 111022;
    idMap["phatbeet"] = 111023;
    idMap["thymewarp"] = 111024;
    idMap["celerystalker"] = 111025;
    idMap["sporeshroom"] = 111026;
    idMap["garlic"] = 111027;
    idMap["intensivecarrot"] = 111028;
    idMap["cactus"] = 111029;
    idMap["nekotail"] = 111030;
    idMap["morningglory"] = 111031;
    idMap["grapeshot"] = 111032;
    idMap["coldsnapdragon"] = 111033;
    idMap["shrinkingviolet"] = 111034;
    idMap["primalpeashooter"] = 111035;
    idMap["primalwallnut"] = 111036;
    idMap["perfumeshroom"] = 111037;
    idMap["primalsunflower"] = 111038;
    idMap["primalpotatomine"] = 111039;
    idMap["dragonroar"] = 111040;
    idMap["bramble"] = 111041;
    idMap["primalrafflesia"] = 111042;
    idMap["dragoncane"] = 111043;
    idMap["cobcannon"] = 111044;
    idMap["applemortar"] = 111045;
    idMap["witchhazel"] = 111046;
    idMap["escaperoot"] = 111047;
    idMap["electriccurrant"] = 111048;
    idMap["whitemelon"] = 111049;
    idMap["caulipower"] = 111050;
    idMap["shadowshroom"] = 111051;
    idMap["moonflower"] = 111052;
    idMap["explodeonut"] = 111053;
    idMap["nightshade"] = 111054;
    idMap["dusklobber"] = 111055;
    idMap["bloominghearts"] = 111056;
    idMap["smallexplodeonut"] = 111057;
    idMap["grimrose"] = 111058;
    idMap["wasabiwhip"] = 111060;
    idMap["parsnip"] = 111061;
    idMap["missiletoe"] = 111062;
    idMap["kiwibeast"] = 111063;
    idMap["goldbloom"] = 111064;
    idMap["flattenedshroom"] = 111065;
    idMap["lotusshooter"] = 111066;
    idMap["convallariachemist"] = 111067;
    idMap["passionflower"] = 111068;
    idMap["vanilla"] = 111069;
    idMap["mulberry"] = 111070;
    idMap["electricpeashooter"] = 111071;
    idMap["icycurrant"] = 111072;
    idMap["hotdate"] = 111073;
    idMap["tuliptrumpeter"] = 111074;
    idMap["eggplantninja"] = 111075;
    idMap["plantain"] = 111076;
    idMap["pinecone"] = 111079;
    idMap["narcissusshooter"] = 111078;
    idMap["smallcactus"] = 111080;
    idMap["alarmsagittifolia"] = 111081;
    idMap["hollyknight"] = 111082;
    idMap["hollybarrierleaf"] = 111083;
    idMap["shadowpeashooter"] = 111084;
    idMap["snappea"] = 111085;
    idMap["monotropa"] = 111086;
    idMap["slingpea"] = 111087;
    idMap["thundersnapdragon"] = 111088;
    idMap["aloes"] = 111089;
    idMap["bearberry"] = 111090;
    idMap["waxgourd"] = 111091;
    idMap["electricitea"] = 200000;
    idMap["imppear"] = 200001;
    idMap["pomegranatejeweler"] = 200002;
    idMap["olive"] = 200003;
    idMap["egretflower"] = 200004;
    idMap["strawburst"] = 200005;
    idMap["poisonpeashooter"] = 200006;
    idMap["elaeocarpus"] = 200007;
    idMap["dartichoke"] = 200008;
    idMap["eleocurling"] = 200009;
    idMap["pokra"] = 200010;
    idMap["hydrocotyledrummer"] = 200011;
    idMap["ultomato"] = 200012;
    idMap["shadowvanilla"] = 200014;
    idMap["tupistrastalker"] = 200013;
    idMap["bromelblade"] = 200015;
    idMap["stephania"] = 200016;
    idMap["icelotus"] = 200017;
    idMap["dendrobiumguard"] = 200018;
    idMap["cypripedium"] = 200019;
    idMap["gumnut"] = 200020;
    idMap["olivepit"] = 200021;
    idMap["boophonegeisha"] = 200022;
    idMap["stickybombrice"] = 200023;
    idMap["nukelauncher"] = 200024;
    idMap["headbutterlettuce"] = 200025;
    idMap["dazeychain"] = 200026;
    idMap["boomflower"] = 200027;
    idMap["beercoconut"] = 200028;
    idMap["clawgloriosa"] = 200029;
    idMap["flowerpot"] = 200030;
    idMap["impatiensshooter"] = 200031;
    idMap["turkeypult"] = 200032;
    idMap["hammerflower"] = 200033;
    idMap["mangosteen"] = 200034;
    idMap["fishhookgrass"] = 200035;
    idMap["bitpeashooter"] = 200036;
    idMap["tigerstool"] = 200038;
    idMap["inferno"] = 200037;
    idMap["draftodil"] = 200039;
    idMap["magicbeans"] = 200040;
    idMap["gardenergrass"] = 200041;
    idMap["frog"] = 200042;
    idMap["heathseeker"] = 200043;
    idMap["ents"] = 200044;
    idMap["hatmushroom"] = 200045;
    idMap["hocuscrocus"] = 200046;
    idMap["springprincess"] = 200047;
    idMap["riflebamboo"] = 200048;
    idMap["byttneriameteorhammer"] = 200049;
    idMap["buttercup"] = 200050;
    idMap["crownflower"] = 200051;
    idMap["zoybeanpod"] = 200052;
    idMap["orchidmage"] = 200053;
    idMap["jackolantern"] = 200054;
    idMap["beanchemist"] = 200055;
    idMap["jewelrabbit"] = 200056;
    idMap["lancerhoya"] = 200057;
    idMap["burdockbatter"] = 200058;
    idMap["vamporcini"] = 200059;
    idMap["pumpkin"] = 200060;
    idMap["geraniifencer"] = 200061;
    idMap["deodarcedar"] = 200062;
    idMap["powervine"] = 200063;
    idMap["sarracenia"] = 200064;
    idMap["meteorflower"] = 200065;
    idMap["mandrake"] = 200066;
    idMap["cthulhuactinia"] = 200067;
    idMap["devilsflower"] = 200068;
    idMap["hoyacordata"] = 200069;
    idMap["peavine"] = 200070;
    idMap["maybee"] = 200071;
    idMap["rapeflower"] = 200072;
    idMap["dracaena"] = 200073;
    idMap["spartanbamboo"] = 200074;
    idMap["shinevine"] = 200075;
    idMap["happyleek"] = 200076;
    idMap["nightcap"] = 200077;
    idMap["pyrevine"] = 200078;
    idMap["gluttonydragon"] = 200079;
    idMap["waterrabbit"] = 200080;
    idMap["armorflame"] = 200081;
    idMap["heliconiagunner"] = 200082;
    idMap["electricpeel"] = 200083;
    idMap["wizardthorns"] = 200084;
    idMap["chainsawburmannii"] = 200085;
    idMap["tristerixaphyllus"] = 200086;
    idMap["minigame_imitater"] = 200087;
    idMap["dragonbruit"] = 200088;
    idMap["dragonbabybruit"] = 200089;
    idMap["gloomvine"] = 200090;
    idMap["eagleclaw"] = 200091;
    idMap["heavendatura"] = 200092;
    idMap["firecrackerflower"] = 200093;
    idMap["twinshoneysuckle"] = 200094;
    idMap["rhubarbarian"] = 200095;
    idMap["aquavine"] = 200096;
    idMap["winterrambutan"] = 200097;
    idMap["wiregelsemium"] = 200098;
    m_map = idMap;
    CreateMD5Check();
}

/////////////// Lookup ///////////////

int PlantNameMapperServerID::GetIdForType(PlantTypePtr i_plantType)
{
    return GetIdForName(std::string(i_plantType->TypeName));
}

int PlantNameMapperServerID::GetIdForType(const PlantType* i_plantType)
{
    return GetIdForName(std::string(i_plantType->TypeName));
}

PlantTypePtr PlantNameMapperServerID::GetTypeForID(int i_plantID)
{
    std::string name = GetNameForId(i_plantID);
    return ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(name);
}

bool PlantNameMapperServerID::IsIDValid(int i_id)
{
    return (i_id >= 1001 && i_id <= 1100) || (i_id >= 111001 && i_id <= 112000);
}
