//
//  talking_game.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//
#include "SexyAppFramework/Common.h"
#include "PvZ/TalkingGame/talking_game.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Lifecycle ///////////////

static std::string sTalkingGameHelperClass = "com/popcap/SexyAppFramework/TalkingGameHelper";

talkingGame::talkingGame()
	: isNewUser_(false)
	, env_(NULL)
	, clazz_(NULL)
{
	env_ = Android::Util::GetJNIEnv();
	if (env_ != NULL)
	{
		jclass localClass = env_->FindClass(sTalkingGameHelperClass.c_str());
		clazz_ = (jclass)env_->NewGlobalRef(localClass);
	}
}

/////////////// Reporting ///////////////

void talkingGame::setAccount() {}
void talkingGame::setGameServer() {}
void talkingGame::setLevel(int iLevel) {}
void talkingGame::onPay(const char* itemid, int cash, int gem, const char* type) {}
void talkingGame::onPayComplete(const char* payid) {}
void talkingGame::onUseGem(const char* itemName, int amount, int price) {}
void talkingGame::onUseItem(const char* itemName, int amount) {}
void talkingGame::beginLevel(const char* levelname) {}
void talkingGame::completeLevel(const char* levelname) {}
void talkingGame::failLevel(const char* levelname, const char* reason) {}
void talkingGame::onReward(int amount, const char* rewardid) {}
void talkingGame::getGold(const char* reason, int amount) {}
void talkingGame::useGold(const char* reason, int amount) {}
void talkingGame::stayPlayer(const char* pointname) {}
