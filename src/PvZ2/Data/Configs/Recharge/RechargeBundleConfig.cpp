//
//  RechargeBundleConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RechargeBundleConfig.h"

#include <algorithm>
#include "ProfileMgr.h"

/////////////// Lifecycle ///////////////

RechargeBundleConfig::RechargeBundleConfig()
{
	bundleRefreshTime = (decltype(bundleRefreshTime))3600;
}

RechargeBundleConfig::~RechargeBundleConfig()
{
}

#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(RechargeBundleConfig);

void RechargeBundleConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BundlePushCondition);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, condition, t);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, levelName, w);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, refreshTime, rt);
	REFLECTION_CLASSBUILDER_END(BundlePushCondition);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_BonusInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, objectId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, quantity, q);
	REFLECTION_CLASSBUILDER_END(S2C_BonusInfo);

	REFLECTION_CLASSBUILDER_BEGIN(BundleItem);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, priceLimit, pl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, timesToBuy, tl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, objectId, id);
	REFLECTION_CLASSBUILDER_END(BundleItem);

	REFLECTION_CLASSBUILDER_BEGIN(BundleDetail);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, objectId, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, price, pri);
		REFLECTION_CLASSBUILDER_FIELD(int, discount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, title, t);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, description, des);
		REFLECTION_CLASSBUILDER_FIELD(std::string, type);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, itemList, il);
	REFLECTION_CLASSBUILDER_END(BundleDetail);

	REFLECTION_CLASSBUILDER_BEGIN(BundleTypeList);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, bundleTypeId, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(BundlePushCondition, pushCondition, dis);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, typeDescription, n);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<BundleItem>, bundleList, l);
	REFLECTION_CLASSBUILDER_END(BundleTypeList);

	REFLECTION_CLASSBUILDER_BEGIN(RechargeBundleConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, bundleRefreshTime, gft);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<BundleDetail>, bundleDetail, pd);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<BundleTypeList>, bundleList, pa);
	REFLECTION_CLASSBUILDER_END(RechargeBundleConfig);

}

/////////////// Accessors ///////////////

bool RechargeBundleConfig::IsBundleListSingleton(int bundleTypeId)
{
	return true;
}

/////////////// Lookup ///////////////

static bool operator==(const BundleTypeList& i_list, const int& i_id)
{
	return i_list.bundleTypeId == i_id;
}

static bool operator==(const BundleItem& i_item, const int& i_id)
{
	return i_item.objectId == i_id;
}

BundleItem* RechargeBundleConfig::getBundleById(int bundleTypeId, int objectId)
{
	std::vector<BundleTypeList>::iterator type = std::find(bundleList.begin(), bundleList.end(), bundleTypeId);
	if (type == bundleList.end())
		return nullptr;
	std::vector<BundleItem>::iterator item = std::find(type->bundleList.begin(), type->bundleList.end(), objectId);
	if (item == type->bundleList.end())
		return nullptr;
	return &*item;
}

int RechargeBundleConfig::getBundleListBuyTimes(int bundleTypeId, int objectId)
{
	BundleItem* item = getBundleById(bundleTypeId, objectId);
	return item ? item->timesToBuy : 0;
}

static bool operator==(const BundleDetail& i_detail, const int& i_id)
{
	return i_detail.objectId == i_id;
}

BundleDetail* RechargeBundleConfig::getBundleDetailById(int objectId)
{
	std::vector<BundleDetail>::iterator detail = std::find(bundleDetail.begin(), bundleDetail.end(), objectId);
	if (detail == bundleDetail.end())
		return nullptr;
	return &*detail;
}

int RechargeBundleConfig::getBundleListExpireTime(int bundleTypeId)
{
	std::vector<BundleTypeList>::iterator type = std::find(bundleList.begin(), bundleList.end(), bundleTypeId);
	int expireTime = 0;
	if (type == bundleList.end())
		return expireTime;
	expireTime = type->pushCondition.refreshTime;
	if (expireTime <= 0)
		expireTime = bundleRefreshTime;
	return expireTime;
}

BundlePushCondition* RechargeBundleConfig::getBundleListPushCondition(int bundleTypeId)
{
	std::vector<BundleTypeList>::iterator type = std::find(bundleList.begin(), bundleList.end(), bundleTypeId);
	if (type == bundleList.end())
		return nullptr;
	return &type->pushCondition;
}

std::string RechargeBundleConfig::getBundlePushConditionStrById(int bundleTypeId)
{
	BundlePushCondition* pushCondition = getBundleListPushCondition(bundleTypeId);
	if (pushCondition)
		return pushCondition->condition;
	return "";
}

bool RechargeBundleConfig::IsBundleListAvailable(const BundleTypeList& i_list)
{
	std::string condition = i_list.pushCondition.condition;
	return condition == "always";
}

bool RechargeBundleConfig::IsBundleAvailable(const BundleItem& i_item, const int& rechargeAmount)
{
	const std::vector<int>& priceLimit = i_item.priceLimit;
	if (priceLimit.size() == 1)
		return rechargeAmount < priceLimit[0];
	if (priceLimit.size() > 1)
		return rechargeAmount >= priceLimit[0] && rechargeAmount < priceLimit[1];
	return true;
}

/////////////// UI ///////////////

static bool operator==(const RechargeUIConfig& i_config, const std::string& i_type)
{
	return i_config.type == i_type;
}

std::string RechargeBundleConfig::getBGImageByType(const std::string& type)
{
	std::vector<RechargeUIConfig>::iterator config = std::find(k_recharge_ui_config.begin(), k_recharge_ui_config.end(), type);
	if (config == k_recharge_ui_config.end())
		return "";
	return config->image;
}

RechargeUIType RechargeBundleConfig::getUITypeByType(const std::string& type)
{
	std::vector<RechargeUIConfig>::iterator config = std::find(k_recharge_ui_config.begin(), k_recharge_ui_config.end(), type);
	if (config == k_recharge_ui_config.end())
		return RechargeUIType_Default;
	return config->UItype;
}

/////////////// Bundle selection ///////////////

void RechargeBundleConfig::makeAvailableBundleList(const BundleTypeList& i_list, std::vector<BundleItem>& i_availableList, bool i_ignoreListCheck, const int& rechargeAmount)
{
	i_availableList.clear();
	if (__builtin_expect(!!(i_ignoreListCheck || IsBundleListAvailable(i_list)), 1))
	{
		std::vector<BundleItem> items = i_list.bundleList;
		if (__builtin_expect(!!(items.size() != 0), 1))
		{
			ProfileMgr::GetInstance().GetCurrentProfile();
			std::vector<BundleItem>::iterator it = items.begin();
			std::vector<BundleItem>::iterator end = items.end();
			while (it != end)
			{
				const BundleItem& item = *it;
				if (__builtin_expect(!!(IsBundleAvailable(item, rechargeAmount)), 0))
					i_availableList.push_back(item);
				++it;
			}
		}
	}
}

BundleDetail* RechargeBundleConfig::chooseRandomBundleFromType(int bundleTypeId, bool i_ignoreListCheck, const int& rechargeAmount)
{
	std::vector<BundleTypeList>::iterator type = std::find(bundleList.begin(), bundleList.end(), bundleTypeId);
	BundleDetail* detail = nullptr;
	if (type == bundleList.end())
		return detail;
	std::vector<BundleItem> availableList;
	makeAvailableBundleList(*type, availableList, i_ignoreListCheck, rechargeAmount);
	if (availableList.size() != 0)
	{
		int index = Sexy::Rand((int)availableList.size());
		detail = getBundleDetailById(availableList[index].objectId);
	}
	return detail;
}
