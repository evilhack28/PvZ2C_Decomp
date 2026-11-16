//
//  IWechat_Platform.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "AndroidWechat_Platform.h"
#include "Social/IWechat_Platform.h"

/////////////// IWechatPlatform ///////////////

IWechatPlatform::IWechatPlatform()
{
}

IWechatPlatform* IWechatPlatform::CreateWechatPlatform()
{
	return new AndroidWechatPlatform();
}
