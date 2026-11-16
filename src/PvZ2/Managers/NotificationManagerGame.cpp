//
//  NotificationManagerGame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-10.
//

#include "NotificationManagerGame.h"

#include <ctime>

#include "ProfileMgr.h"
#include "StructuredData.h"

static const std::string sPushUserName("pvz2-client");
static const std::string sPushPassword("t4P04R3KaZqAJAQ");
static const std::string sPushEndpoint("https://push-dev-almost.pt.popcap.com.cn/push/1.0/");

/////////////// Lifecycle ///////////////

NotificationManagerGame::NotificationManagerGame()
{
	Init();
}

NotificationManagerGame::~NotificationManagerGame()
{
}

/////////////// Setup ///////////////

void NotificationManagerGame::Init()
{
	Sexy::NotificationManager* manager = Sexy::NotificationManager::SharedNotificationManagerOptional();
	if (manager != NULL)
	{
		manager->SetProviderAuth(sPushUserName, sPushPassword);
		manager->SetProviderEndpoint(sPushEndpoint);
	}
	AddListener(this);
}

void NotificationManagerGame::Register()
{
	Sexy::NotificationManager* manager = Sexy::NotificationManager::SharedNotificationManagerOptional();
	if (manager != NULL)
		manager->RegisterForRemoteNotifications();
}

void NotificationManagerGame::AddListener(NotificationListener* listener)
{
	Sexy::NotificationManager* manager = Sexy::NotificationManager::SharedNotificationManagerOptional();
	if (manager != NULL)
		manager->AddNotificationListener(listener);
}

/////////////// Accessors ///////////////

const std::string NotificationManagerGame::GetCurrentEndpoint()
{
	return Sexy::NotificationManager::SharedNotificationManagerRequired()->ProviderEndpoint();
}

/////////////// Callbacks ///////////////

void NotificationManagerGame::DidRegisterForRemoteNotifications(const std::string& deviceToken)
{
	Sexy::NotificationManager* manager = Sexy::NotificationManager::SharedNotificationManagerOptional();
	if (manager != NULL)
		manager->UpdateTokenRegistration(ProfileMgr::GetInstance().GetAccountName());
}

void NotificationManagerGame::DidReceiveRemoteNotification(const Sexy::StructuredData* userInfo)
{
}

void NotificationManagerGame::DidReceiveLocalNotification(const Sexy::StructuredData* userInfo)
{
}

void NotificationManagerGame::DidFailToRegisterForRemoteNotificationsWithError(const Sexy::StructuredData* userInfo)
{
}

/////////////// Test ///////////////

void NotificationManagerGame::TestPushNotification(const std::string& message, const std::string& recipient_id)
{
	if (recipient_id.size() == 0)
		return;

	Sexy::StructuredData payload;
	payload.BeginObject();
	payload.BeginObject("aps");
	payload.AddString("alert", message.c_str());
	payload.AddString("sound", "default");
	payload.EndObject();
	payload.EndObject();

	Sexy::NotificationManager* manager = Sexy::NotificationManager::SharedNotificationManagerOptional();
	if (manager != NULL)
		manager->SendRemoteNotification(recipient_id.c_str(), time(NULL) + 86400, &payload);
}
