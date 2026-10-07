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
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)15, "wxf05305d1aa9c64cd"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)67, "wx8fb5628205b8f35f"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)29, "wxa0afbafd159c65a8"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)39, "wxf835cc099e8b978f"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)81, "wxebbb131e118d5215"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)91, "wxe60c401b43e8be10"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)5, "wxdbecc4dfd73fddc3"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)11, "wxe552c7c10a8141ef"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)48, "wx4d1724ecb2d2166f"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)100, "wxdbd4e680ec802e3d"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)37, "wxcc5b70dbaa173c33"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)89, "wx20802592da3d8716"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)20, "wx8cad4736049ac63a"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)72, "wxafc825b03e37a20a"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)2, "wxb0bedebda1b96e96"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)8, "wxf446a92c0b70455b"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)19, "wx65a3b47823ca88e9"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)71, "wx65f999699e6f17f8"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)16, "wxeb3731537ef52548"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)68, "wxcdeb154bab9a5573"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)41, "wx2b48a02fea4174bf"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)93, "wx4ea72cc2339f65f2"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)51, "wxb55bb6a9505b8512"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)103, "wx835e09e2d6ae58ef"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)26, "wx871ece62e8b6c40b"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)78, "wx53529ebe57947207"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)4, "wx84e69fe584fde2b9"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)165, "wx59ca4b84f6e97c26"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)38, "wx247f6bb403851c5f"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)90, "wx735ef08342313354"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)27, "wxc6d83b979b071860"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)79, "wxf90fcb02630ed235"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)33, "wx297004413e29f161"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)85, "wx79e510db5b1d80ea"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)25, "wxaecc220b9c1f53fe"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)77, "wx369a974114817b25"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)50, "wxb10813686e1c0e54"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)102, "wx68f36b1d3fcb9603"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)21, "wx41acd8d522d3dcff"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)73, "wxe7b3743898669029"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)22, "wx74ae2e46f5fc3711"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)74, "wxa4b1a14c2816ebf8"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)1, "wx8a604cd46c19c88b"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)6, "wx5f4fcd926c86e752"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)23, "wx1757821dfd467473"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)75, "wxefe808fd19674cbb"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)47, "wxe6bd7e259fd329d5"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)99, "wx7735eca47d673eed"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)28, "wxb8849537bc3075d1"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)108, "wxf90636efd850cf06"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)109, "wx5d4c1280a43515e2"));
	AndroidWechatAPPIDS.insert(std::make_pair((PlatformType)110, "wxa2078eaa4866bc8d"));
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
