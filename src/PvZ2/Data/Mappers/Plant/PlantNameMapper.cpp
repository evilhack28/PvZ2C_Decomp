//
//  PlantNameMapper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//
/////////////// Lifecycle ///////////////

#include "PvZ/NameMapper.h"
#include "PvZ/PlantType.h"

static PlantNameMapper& (*const s_keepGetInstance)() __attribute__((used)) = &PlantNameMapper::GetInstance;

__asm__(".local __dso_handle\n.comm __dso_handle,8,8");

PlantNameMapper::PlantNameMapper()
{
    std::map<std::string, int> map;
    map["sunflower"] = 1;
    map["peashooter"] = 2;
    map["wallnut"] = 3;
    map["tallnut"] = 4;
    map["bonkchoy"] = 5;
    map["cabbagepult"] = 6;
    map["melonpult"] = 7;
    map["cherry_bomb"] = 8;
    map["coconutcannon"] = 9;
    map["gravebuster"] = 10;
    map["iceburg"] = 11;
    map["laser_bean"] = 12;
    map["potatomine"] = 13;
    map["repeater"] = 14;
    map["snapdragon"] = 15;
    map["spikeweed"] = 16;
    map["threepeater"] = 17;
    map["torchwood"] = 18;
    map["kernelpult"] = 19;
    map["springbean"] = 20;
    map["snowpea"] = 21;
    map["chilibean"] = 22;
    map["splitpea"] = 23;
    map["lightningreed"] = 24;
    map["peapod"] = 25;
    map["magnifyinggrass"] = 26;
    map["bloomerang"] = 27;
    map["holonut"] = 28;
    map["empea"] = 29;
    map["blover"] = 30;
    map["starfruit"] = 31;
    map["imitater"] = 32;
    map["jalapeno"] = 33;
    map["wintermelon"] = 34;
    map["twinsunflower"] = 35;
    map["spikerock"] = 37;
    map["powerlily"] = 38;
    map["squash"] = 39;
    map["citron"] = 40;
    map["powerplant"] = 41;
    map["turnip"] = 42;
    map["peach"] = 43;
    map["firegourd"] = 44;
    map["bamboo"] = 45;
    map["smallcherry"] = 46;
    map["carrotlauncher"] = 47;
    map["carrotmissile"] = 48;
    map["dandelion"] = 49;
    map["broccoli"] = 50;
    map["puffshroom"] = 51;
    map["fumeshroom"] = 52;
    map["hypnoshroom"] = 53;
    map["sunshroom"] = 54;
    map["sunbean"] = 55;
    map["peanut"] = 56;
    map["magnetshroom"] = 57;
    map["streetlamp"] = 58;
    map["coffeebean"] = 59;
    map["iceshroom"] = 60;
    map["fireshroom"] = 61;
    map["oakshooter"] = 62;
    map["pamegranate"] = 63;
    map["chomper"] = 64;
    map["sweetpotato"] = 65;
    map["tanglekelp"] = 66;
    map["banana"] = 67;
    map["guacodile"] = 68;
    map["homingthistle"] = 69;
    map["lilypad"] = 70;
    map["lemon"] = 71;
    map["ghostpepper"] = 72;
    map["bowlingbulb"] = 73;
    map["cracker"] = 74;
    map["lotusshower"] = 75;
    map["sapfling"] = 76;
    map["hurrikale"] = 77;
    map["firepeashooter"] = 78;
    map["hotpotato"] = 79;
    map["pepperpult"] = 80;
    map["chardguard"] = 81;
    map["stunion"] = 82;
    map["rafflesia"] = 83;
    map["acorn"] = 84;
    map["doublesamara"] = 85;
    map["anthurium"] = 86;
    map["asparagus"] = 87;
    map["saucer"] = 88;
    map["horsebean"] = 89;
    map["groundcherry"] = 90;
    map["pineapple"] = 91;
    map["goldleaf"] = 93;
    map["akee"] = 95;
    map["redstinger"] = 96;
    map["stallia"] = 97;
    map["lavaguava"] = 98;
    map["toadstool"] = 99;
    map["jackfruit"] = 100;
    map["phatbeet"] = 101;
    map["thymewarp"] = 102;
    map["celerystalker"] = 103;
    map["sporeshroom"] = 104;
    map["garlic"] = 105;
    map["intensivecarrot"] = 106;
    map["morningglory"] = 107;
    map["cactus"] = 108;
    map["primalpeashooter"] = 109;
    map["primalwallnut"] = 110;
    map["perfumeshroom"] = 111;
    map["primalsunflower"] = 112;
    map["primalpotatomine"] = 113;
    map["dragonroar"] = 114;
    map["bramble"] = 115;
    map["caulipower"] = 116;
    map["shadowshroom"] = 117;
    map["moonflower"] = 118;
    map["explodeonut"] = 119;
    map["nightshade"] = 120;
    map["dusklobber"] = 121;
    map["bloominghearts"] = 122;
    map["smallexplodeonut"] = 123;
    map["grimrose"] = 124;
    map["goldbloom"] = 125;
    map["flattenedshroom"] = 126;
    map["lotusshooter"] = 127;
    map["convallariachemist"] = 128;
    map["passionflower"] = 129;
    map["vanilla"] = 130;
    map["mulberry"] = 131;
    map["chestnut"] = 300;
    map["smallChestnut"] = 301;
    map["xshot"] = 302;
    map["sugarcane"] = 303;
    map["bashopult"] = 304;
    map["magicshroom"] = 305;
    map["roseswordman"] = 306;
    map["electricblueberry"] = 307;
    map["birthsunflower"] = 308;
    map["greenturnip"] = 309;
    map["endurian"] = 310;
    map["pumpkinwitch"] = 311;
    map["cottonyeti"] = 312;
    map["agave"] = 313;
    map["kiwifruit"] = 314;
    map["wintersweet"] = 315;
    map["dragonfruit"] = 316;
    map["pinkstarfruit"] = 317;
    map["matchflower"] = 318;
    map["flamelady"] = 319;
    map["gatlingpea"] = 320;
    map["nekotail"] = 321;
    map["grapeshot"] = 322;
    map["coldsnapdragon"] = 323;
    map["shrinkingviolet"] = 324;
    map["primalrafflesia"] = 325;
    map["dragoncane"] = 326;
    map["cobcannon"] = 327;
    map["applemortar"] = 328;
    map["witchhazel"] = 329;
    map["escaperoot"] = 330;
    map["electriccurrant"] = 331;
    map["whitemelon"] = 332;
    map["wasabiwhip"] = 333;
    map["parsnip"] = 334;
    map["missiletoe"] = 335;
    map["kiwibeast"] = 336;
    map["hotdate"] = 337;
    map["electricpeashooter"] = 338;
    map["icycurrant"] = 339;
    map["tuliptrumpeter"] = 340;
    map["eggplantninja"] = 341;
    map["plantain"] = 342;
    map["pinecone"] = 345;
    map["narcissusshooter"] = 344;
    map["smallcactus"] = 346;
    map["alarmsagittifolia"] = 347;
    map["hollyknight"] = 348;
    map["hollybarrierleaf"] = 349;
    map["shadowpeashooter"] = 350;
    map["snappea"] = 351;
    map["monotropa"] = 352;
    map["slingpea"] = 353;
    map["thundersnapdragon"] = 354;
    map["aloes"] = 355;
    map["bearberry"] = 356;
    map["waxgourd"] = 357;
    map["electricitea"] = 358;
    map["imppear"] = 359;
    map["pomegranatejeweler"] = 360;
    map["olive"] = 361;
    map["egretflower"] = 362;
    map["strawburst"] = 363;
    map["poisonpeashooter"] = 364;
    map["elaeocarpus"] = 365;
    map["dartichoke"] = 366;
    map["eleocurling"] = 367;
    map["pokra"] = 368;
    map["hydrocotyledrummer"] = 369;
    map["ultomato"] = 370;
    map["shadowvanilla"] = 372;
    map["tupistrastalker"] = 371;
    map["bromelblade"] = 373;
    map["stephania"] = 374;
    map["icelotus"] = 375;
    map["dendrobiumguard"] = 376;
    map["cypripedium"] = 377;
    map["gumnut"] = 378;
    map["olivepit"] = 379;
    map["boophonegeisha"] = 380;
    map["stickybombrice"] = 381;
    map["nukelauncher"] = 382;
    map["headbutterlettuce"] = 383;
    map["dazeychain"] = 384;
    map["boomflower"] = 385;
    map["beercoconut"] = 386;
    map["clawgloriosa"] = 387;
    map["flowerpot"] = 388;
    map["impatiensshooter"] = 389;
    map["turkeypult"] = 390;
    map["hammerflower"] = 391;
    map["mangosteen"] = 392;
    map["fishhookgrass"] = 393;
    map["bitpeashooter"] = 394;
    map["tigerstool"] = 396;
    map["inferno"] = 395;
    map["draftodil"] = 397;
    map["magicbeans"] = 398;
    map["gardenergrass"] = 399;
    map["frog"] = 400;
    map["heathseeker"] = 401;
    map["ents"] = 402;
    map["hatmushroom"] = 403;
    map["hocuscrocus"] = 404;
    map["springprincess"] = 405;
    map["riflebamboo"] = 406;
    map["byttneriameteorhammer"] = 407;
    map["buttercup"] = 408;
    map["crownflower"] = 409;
    map["zoybeanpod"] = 410;
    map["orchidmage"] = 411;
    map["jackolantern"] = 412;
    map["beanchemist"] = 413;
    map["jewelrabbit"] = 414;
    map["lancerhoya"] = 415;
    map["burdockbatter"] = 416;
    map["vamporcini"] = 417;
    map["pumpkin"] = 418;
    map["geraniifencer"] = 419;
    map["deodarcedar"] = 420;
    map["powervine"] = 421;
    map["sarracenia"] = 422;
    map["meteorflower"] = 423;
    map["mandrake"] = 424;
    map["cthulhuactinia"] = 425;
    map["devilsflower"] = 426;
    map["hoyacordata"] = 427;
    map["peavine"] = 428;
    map["maybee"] = 429;
    map["rapeflower"] = 430;
    map["dracaena"] = 431;
    map["spartanbamboo"] = 432;
    map["shinevine"] = 433;
    map["happyleek"] = 434;
    map["nightcap"] = 435;
    map["pyrevine"] = 436;
    map["gluttonydragon"] = 437;
    map["waterrabbit"] = 438;
    map["armorflame"] = 439;
    map["heliconiagunner"] = 440;
    map["electricpeel"] = 441;
    map["wizardthorns"] = 442;
    map["chainsawburmannii"] = 443;
    map["tristerixaphyllus"] = 444;
    map["minigame_imitater"] = 445;
    map["dragonbruit"] = 446;
    map["dragonbabybruit"] = 447;
    map["gloomvine"] = 448;
    map["eagleclaw"] = 449;
    map["heavendatura"] = 450;
    map["firecrackerflower"] = 451;
    map["twinshoneysuckle"] = 452;
    map["rhubarbarian"] = 453;
    map["aquavine"] = 454;
    map["winterrambutan"] = 455;
    map["wiregelsemium"] = 456;
    m_map = map;
    CreateMD5Check();
}

/////////////// Lookup ///////////////

int PlantNameMapper::GetIdForType(PlantTypePtr i_plantType)
{
    return GetIdForName(std::string(i_plantType->TypeName));
}

int PlantNameMapper::GetIdForType(const PlantType* i_plantType)
{
    return GetIdForName(std::string(i_plantType->TypeName));
}

PlantTypePtr PlantNameMapper::GetTypeForID(int i_plantID)
{
    std::string name = GetNameForId(i_plantID);
    return ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(name);
}

bool PlantNameMapper::IsIDValid(int i_id)
{
    return i_id > 0 && i_id < 1000;
}
