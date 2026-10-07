//
//  AndroidWechat_Platform.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AndroidWechat_Platform.h"
#include "GameEventMgr.h"

/////////////// Lifecycle ///////////////

AndroidWechatPlatform::AndroidWechatPlatform()
{
	AndroidWechatAPPIDS.clear();
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_91, "wxf05305d1aa9c64cd"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_91_HD, "wx8fb5628205b8f35f"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_360, "wxa0afbafd159c65a8"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_4399, "wxf835cc099e8b978f"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_360_HD, "wxebbb131e118d5215"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_4399_HD, "wxe60c401b43e8be10"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_MOBILE_MM, "wxdbecc4dfd73fddc3"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_MOBILE_MM_HD, "wxe552c7c10a8141ef"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_NDUO, "wx4d1724ecb2d2166f"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_NDUO_HD, "wxdbd4e680ec802e3d"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_OPPO, "wxcc5b70dbaa173c33"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_OPPO_HD, "wx20802592da3d8716"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_UC, "wx8cad4736049ac63a"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_UC_HD, "wxafc825b03e37a20a"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_UNICOM, "wxb0bedebda1b96e96"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_UNICOM_HD, "wxf446a92c0b70455b"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_ANZHI, "wx65a3b47823ca88e9"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_ANZHI_HD, "wx65f999699e6f17f8"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_BAIDU_DUOKU, "wxeb3731537ef52548"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_BAIDU_DUOKU_HD, "wxcdeb154bab9a5573"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_POPCAP, "wx2b48a02fea4174bf"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_POPCAP_HD, "wx4ea72cc2339f65f2"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_BUBUGAO, "wxb55bb6a9505b8512"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_BUBUGAO_HD, "wx835e09e2d6ae58ef"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_DANGLE, "wx871ece62e8b6c40b"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_DANGLE_HD, "wx53529ebe57947207"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_TELECOM, "wx84e69fe584fde2b9"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_TELECOM_HD, "wx59ca4b84f6e97c26"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_HUAWEI, "wx247f6bb403851c5f"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_HUAWEI_HD, "wx735ef08342313354"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_JINLI, "wxc6d83b979b071860"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_JINLI_HD, "wxf90fcb02630ed235"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_LENOVO, "wx297004413e29f161"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_LENOVO_HD, "wx79e510db5b1d80ea"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_SHOUGOU, "wxaecc220b9c1f53fe"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_SHOUGOU_HD, "wx369a974114817b25"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_TIANYIDA, "wxb10813686e1c0e54"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_TIANYIDA_HD, "wx68f36b1d3fcb9603"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_WANDOULABS, "wx41acd8d522d3dcff"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_WANDOULABS_HD, "wxe7b3743898669029"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_XIAOMI, "wx74ae2e46f5fc3711"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_XIAOMI_HD, "wxa4b1a14c2816ebf8"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_MOBILE, "wx8a604cd46c19c88b"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_CHINA_MOBILE_HD, "wx5f4fcd926c86e752"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_YINGYONGHUI, "wx1757821dfd467473"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_YINGYONGHUI_HD, "wxefe808fd19674cbb"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_YOUKU, "wxe6bd7e259fd329d5"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_YOUKU_HD, "wx7735eca47d673eed"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_MAOPAOTANG, "wxb8849537bc3075d1"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_JJ_HD, "wxf90636efd850cf06"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_LESHI_HD, "wx5d4c1280a43515e2"));
	AndroidWechatAPPIDS.insert(std::make_pair(PLATFORM_PPZHUSHOU_HD, "wxa2078eaa4866bc8d"));
}

AndroidWechatPlatform::~AndroidWechatPlatform()
{
}

/////////////// Accessors ///////////////

bool AndroidWechatPlatform::IsWeChatInstalled()
{
	return false;
}

/////////////// Logic ///////////////

namespace Message {
void WechatShareSuccess();
void WeChatShareFailed();
}

void AndroidWechatPlatform::Initialize()
{
}

void AndroidWechatPlatform::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
}

void AndroidWechatPlatform::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
}

void AndroidWechatPlatform::DoShare(const std::string& i_url, bool toTimeLine)
{
}

void AndroidWechatPlatform::ShareHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	if (resultCode == 0)
		gMessageRouter->Post(&Message::WechatShareSuccess);
	else
		gMessageRouter->Post(&Message::WeChatShareFailed);
}
