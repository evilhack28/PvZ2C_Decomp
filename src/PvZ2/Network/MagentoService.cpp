//
//  MagentoService.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-10.
//

#include "SexyAppFramework/Common.h"

#include "LawnApp.h"
#include "PVZDB.h"
#include "PurchaseBroker.h"
#include "ProfileMgr.h"
#include "PvZ/logServer/md5.h"
#include <sstream>
#include "MagentoService.h"
#include "ReflectionBuilder.h"

/////////////// MagentoCategoryProps ///////////////

RT_CLASS_IMPLEMENT(MagentoCategoryProps);

void MagentoCategoryProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MagentoCategoryProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);
	REFLECTION_CLASSBUILDER_END(MagentoCategoryProps);
}

/////////////// PlantGiftMagentoProps ///////////////

RT_CLASS_IMPLEMENT(PlantGiftMagentoProps);

void PlantGiftMagentoProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGiftMagentoProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(MagentoProductProps);
	REFLECTION_CLASSBUILDER_END(PlantGiftMagentoProps);
}

/////////////// MagentoProductProps ///////////////

RT_CLASS_IMPLEMENT(MagentoProductProps);

void MagentoProductProps::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(PurchaseType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(gem, PURCHASE_GEM);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(money, PURCHASE_MONEY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(coin, PURCHASE_COIN);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(leaf, PURCHASE_LEAF);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(stone, PURCHASE_STONE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(ad, PURCHASE_AD);
	REFLECTION_ENUMBUILDER_END(PurchaseType);

	REFLECTION_CLASSBUILDER_BEGIN(TierPrice);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Name);
		REFLECTION_CLASSBUILDER_FIELD(float, Price);
	REFLECTION_CLASSBUILDER_END(TierPrice);

	REFLECTION_CLASSBUILDER_BEGIN(LevelUpPriceData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iCurrentLevel, CurrentLevel);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iPieceCount, PieceCount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iSpecialPieceCount, SpecialPieceCount);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iCurrentPrice, CurrentPrice);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(PurchaseType, eType, PurchaseType);
	REFLECTION_CLASSBUILDER_END(LevelUpPriceData);

	REFLECTION_CLASSBUILDER_BEGIN(MagentoProductProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, Sku);
		REFLECTION_CLASSBUILDER_FIELD(int32, actid);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, Names);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, Descriptions);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ShortDescriptions);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Image);
		REFLECTION_CLASSBUILDER_FIELD(int, PriceIndex);
		REFLECTION_CLASSBUILDER_FIELD(int, PoolIdx);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ObjectType);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ObjectItem);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ObjectPurchaseType);
		REFLECTION_CLASSBUILDER_FIELD(int, ObjectCount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<MagentoProductProps> >, BundleProps);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TierPrice>, Prices);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<LevelUpPriceData>, m_strLevelUpPriceDataArray, LevelUpPrice);
		REFLECTION_CLASSBUILDER_FIELD(bool, AvailableFromGacha);
		REFLECTION_CLASSBUILDER_FIELD(bool, SpecialWay);
		REFLECTION_CLASSBUILDER_FIELD(std::string, SpecialWayContent);
	REFLECTION_CLASSBUILDER_END(MagentoProductProps);

}

std::string MagentoProductProps::GetLocalizedName() const
{
	return Names[gLawnApp->GetMagentoLanguage()];
}

std::string MagentoProductProps::GetLocalizedDescription() const
{
	return Descriptions[gLawnApp->GetMagentoLanguage()];
}

std::string MagentoProductProps::GetLocalizedShortDescription() const
{
	return ShortDescriptions[gLawnApp->GetMagentoLanguage()];
}

std::string MagentoProductProps::GetInternalName() const
{
	return Names[0];
}

std::string MagentoCategoryProps::GetLocalizedName() const
{
	return DisplayNames[gLawnApp->GetMagentoLanguage()];
}

std::string MagentoCategoryProps::GetInternalName() const
{
	return Name;
}

/////////////// Price sign ///////////////

std::string MagentoCategoryProps::MagentoAllPricesSign;

std::string MagentoCategoryProps::CalAllPriceSign()
{
	Sexy::OutputDebugStrF("Call CheckAllPriceSign\n");
	std::stringstream stream(std::ios_base::out | std::ios_base::in);
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_MAGENTO); it; ++it)
	{
		MagentoCategoryProps* category = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<MagentoCategoryProps>();
		if (category != NULL)
		{
			for (size_t i = 0; i < category->Products.size(); i++)
			{
				MagentoProductPropsPtr product = category->Products[i];
				if (product.IsValid())
				{
					stream << product->ObjectCount;
					size_t j = 0;
					size_t k;
					goto test;
body:
					stream << product->Prices[k].Price;
test:
					k = j++;
					if (k < product->Prices.size())
						goto body;
				}
			}
		}
	}
	Sexy::OutputDebugStrF("*Magento sign = (%s)\n", stream.str().c_str());
	return MD5(stream.str()).toString();
}

void MagentoCategoryProps::RestAllPriceSign()
{
	MagentoAllPricesSign = CalAllPriceSign();
}

bool MagentoCategoryProps::CheckAllPriceSign()
{
	return MagentoAllPricesSign == CalAllPriceSign();
}

/////////////// Copy ///////////////

MagentoProductProps& MagentoProductProps::operator=(const MagentoProductProps&) = default;

/////////////// Pricing ///////////////

float MagentoProductProps::GetPriceInUSD(bool doCheckSign) const
{
	if (doCheckSign)
	{
		if (!MagentoCategoryProps::CheckAllPriceSign())
		{
			gLawnApp->ShowDataErrorDialog();
			return 2147483648.0f;
		}
	}
	return Prices[PriceIndex].Price;
}

bool MagentoProductProps::GetCurrentLevelPriceData(int nCurrentLevel, LevelUpPriceData& strData)
{
	for (size_t i = 0; i != m_strLevelUpPriceDataArray.size(); i++)
	{
		if (m_strLevelUpPriceDataArray[i].iCurrentLevel == nCurrentLevel)
		{
			strData = m_strLevelUpPriceDataArray[i];
			return true;
		}
	}
	return false;
}

const std::vector<LevelUpPriceData>& MagentoProductProps::GetCurrentLevelPriceDataArray()
{
	return m_strLevelUpPriceDataArray;
}

void MagentoProductProps::SetPriceTier(const std::string& i_tier)
{
	size_t i = 0;
	int idx = 0;
	size_t j;
	int k;
	goto test;
body:
	if (Prices[j].Name == i_tier)
	{
		PriceIndex = k;
		return;
	}
test:
	j = i++;
	k = idx++;
	if (j != Prices.size())
		goto body;
}

bool MagentoProductProps::ContainsItem(const std::string& i_objectType, const std::string& i_objectItem)
{
	if (i_objectType == ObjectType && i_objectItem == ObjectItem)
		return true;
	for (size_t i = 0; i < BundleProps.size(); i++)
	{
		if (i_objectType == BundleProps[i]->ObjectType && i_objectItem == BundleProps[i]->ObjectItem)
			return true;
	}
	return false;
}

/////////////// Magento ///////////////

MagentoCategoryPropsPtr Magento::GetStore(const std::string& i_storeName)
{
	MagentoCategoryPropsPtr result;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_MAGENTO); it; ++it)
	{
		MagentoCategoryProps* category = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<MagentoCategoryProps>();
		if (category != NULL && category->GetInternalName() == i_storeName)
		{
			result = *it;
			break;
		}
	}
	return result;
}

MagentoCategoryPropsPtr Magento::GetStoreCategory(const std::string& i_storeName, const std::string& i_categoryName)
{
	Sexy::OutputDebugStrF("MagentoCategoryPropsPtr  :%s           %s", i_storeName.c_str(), i_categoryName.c_str());
	MagentoCategoryPropsPtr store = GetStore(i_storeName);
	MagentoCategoryPropsPtr result;
	if (store.IsValid())
	{
		size_t i = 0;
		size_t k;
		while ((k = i++) < store->ChildCategories.size())
		{
			if (store->ChildCategories[k]->GetInternalName() == i_categoryName)
			{
				result = store->ChildCategories[k];
				break;
			}
		}
	}
	return result;
}

MagentoProductPropsPtr Magento::FindStoreProduct(const std::string& i_storeName, const std::string& i_categoryName, const std::string& i_objectType, const std::string& i_objectItem)
{
	size_t i = 0;
	MagentoProductPropsPtr result;
	MagentoCategoryPropsPtr category = GetStoreCategory(i_storeName, i_categoryName);
	while (category.IsValid() && i < category->Products.size())
	{
		if (category->Products[i]->ObjectType == i_objectType && category->Products[i]->ObjectItem == i_objectItem)
		{
			result = category->Products[i];
			break;
		}
		i++;
	}
	return result;
}

MagentoProductPropsPtr Magento::GetGesturePtr(const std::string& i_productId)
{
	size_t i = 0;
	MagentoProductPropsPtr result;
	MagentoCategoryPropsPtr category = GetStoreCategory("iOS PvZ2 Gesture Store", "Gestures");
	while (category.IsValid() && i < category->Products.size())
	{
		if (category->Products[i]->Sku == i_productId)
		{
			result = category->Products[i];
			break;
		}
		i++;
	}
	return result;
}

MagentoProductPropsPtr Magento::GetProduct(const std::string& i_productName)
{
	MagentoProductPropsPtr result;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_MAGENTO); it; ++it)
	{
		MagentoProductProps* product = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<MagentoProductProps>();
		if (product != NULL && product->Sku == i_productName)
		{
			result = *it;
			break;
		}
	}
	return result;
}

MagentoCategoryPropsPtr Magento::GetPlantLevelUp()
{
	MagentoCategoryPropsPtr result;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_MAGENTO); it; ++it)
	{
		MagentoCategoryProps* category = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<MagentoCategoryProps>();
		if (category != NULL && category->GetInternalName() == "Plant Level Up")
		{
			result = *it;
			break;
		}
	}
	return result;
}

MagentoProductPropsPtr Magento::GetPlantLevelUpPlant(const std::string& sPlantName)
{
	size_t i = 0;
	MagentoCategoryPropsPtr category;
	MagentoProductPropsPtr result;
	category = GetPlantLevelUp();
	while (category.IsValid() && i < category->Products.size())
	{
		if (category->Products[i]->ObjectItem == sPlantName)
		{
			result = category->Products[i];
			break;
		}
		i++;
	}
	return result;
}

PlantGiftMagentoPropsPtr Magento::FindPlantGiftByLevel(const int i_level)
{
	size_t i = 0;
	PlantGiftMagentoPropsPtr result;
	MagentoCategoryPropsPtr store = GetStore("PlantGift Store");
	while (store.IsValid() && i < store->Products.size())
	{
		PlantGiftMagentoPropsPtr gift = store->Products[i];
		i++;
		if (gift->Level == i_level)
		{
			result = gift;
			break;
		}
	}
	return result;
}

MagentoCategoryPropsPtr Magento::GetPlantPieceProductsData(bool bIsAvatar)
{
	MagentoCategoryPropsPtr result;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_MAGENTO); it; ++it)
	{
		MagentoCategoryProps* category = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<MagentoCategoryProps>();
		if (bIsAvatar)
		{
			if (category != NULL && category->GetInternalName() == "Avatars")
			{
				result = *it;
				break;
			}
		}
		else if (category != NULL && category->GetInternalName() == "Plant Pieces")
		{
			result = *it;
			break;
		}
	}
	return result;
}

MagentoProductPropsPtr Magento::GetBundleProductPtrByPrice(float i_price)
{
	size_t i = 0;
	MagentoProductPropsPtr result;
	MagentoCategoryPropsPtr category = GetStoreCategory("iOS PvZ2 Gem Store", "Bundles");
	while (category.IsValid() && i < category->Products.size())
	{
		if (category->Products[i]->Prices[0].Price == i_price)
		{
			result = category->Products[i];
			break;
		}
		i++;
	}
	return result;
}

MagentoProductPropsPtr Magento::EventGetBundleProductPtrByPrice(float i_price)
{
	size_t i = 0;
	MagentoProductPropsPtr result;
	MagentoCategoryPropsPtr category = GetStoreCategory("iOS PvZ2 Gem Store", "Event Bundles");
	if (category)
	{
		while (category.IsValid() && i < category->Products.size())
		{
			if (category->Products[i]->Prices[0].Price == i_price)
			{
				result = category->Products[i];
				break;
			}
			i++;
		}
	}
	return result;
}

MagentoProductPropsPtr Magento::GetProductPtr(const std::string& i_productId)
{
	MagentoProductPropsPtr result;
	size_t i;
	MagentoCategoryPropsPtr category = GetStoreCategory("iOS PvZ2 Gem Store", "Gems");
	i = 0;
	while (category.IsValid() && i < category->Products.size())
	{
		if (category->Products[i]->Sku == i_productId)
		{
			result = category->Products[i];
			break;
		}
		i++;
	}
	if (!result.IsValid())
	{
		category = GetStoreCategory("iOS PvZ2 Gem Store", "GemsAddition");
		i = 0;
		while (category.IsValid() && i < category->Products.size())
		{
			if (category->Products[i]->Sku == i_productId)
			{
				result = category->Products[i];
				break;
			}
			i++;
		}
	}
	if (!result.IsValid())
	{
		category = GetStoreCategory("iOS PvZ2 Gem Store", "Bundles");
		i = 0;
		while (category.IsValid() && i < category->Products.size())
		{
			if (category->Products[i]->Sku == i_productId)
			{
				result = category->Products[i];
				break;
			}
			i++;
		}
	}
	if (!result.IsValid())
	{
		category = GetStoreCategory("iOS PvZ2 Gem Store", "Event Bundles");
		i = 0;
		while (category.IsValid() && i < category->Products.size())
		{
			if (category->Products[i]->Sku == i_productId)
			{
				result = category->Products[i];
				break;
			}
			i++;
		}
	}
	if (!result.IsValid())
	{
		category = GetStoreCategory("iOS PvZ2 Gem Store", "GemsFor360");
		i = 0;
		while (category.IsValid() && i < category->Products.size())
		{
			if (category->Products[i]->Sku == i_productId)
			{
				result = category->Products[i];
				break;
			}
			i++;
		}
	}
	if (!result.IsValid())
	{
		category = GetStoreCategory("iOS PvZ2 Avatar Ticket Store", "AvatarTicket");
		i = 0;
		while (category.IsValid() && i < category->Products.size())
		{
			if (category->Products[i]->Sku == i_productId)
			{
				result = category->Products[i];
				break;
			}
			i++;
		}
	}
	return result;
}

void Magento::InitMagentoDataSign()
{
	MagentoCategoryProps::RestAllPriceSign();
}

bool Magento::IsMagentoDataSafe()
{
	return MagentoCategoryProps::CheckAllPriceSign();
}

float MagentoProductProps::GetPriceByTypeName(const std::string strTypeName, bool doCheckSign) const
{
	if (doCheckSign)
	{
		if (!MagentoCategoryProps::CheckAllPriceSign())
		{
			gLawnApp->ShowDataErrorDialog();
			return 2147483648.0f;
		}
	}
	for (size_t i = 0; i != Prices.size(); i++)
	{
		if (Prices[i].Name == strTypeName)
			return Prices[i].Price;
	}
	return -1.0f;
}

std::string MagentoProductProps::GetCombinedSkuTierName() const
{
	if (PriceIndex < 0 || (size_t)PriceIndex >= Prices.size() || Prices[PriceIndex].Name.size() == 0)
		return Sku;
	return Sku + "." + Prices[PriceIndex].Name;
}

PurchaseType MagentoProductProps::GetPurchaseType() const
{
	if (ObjectPurchaseType == "coin")
		return PURCHASE_COIN;
	if (ObjectPurchaseType == "gem")
		return PURCHASE_GEM;
	if (ObjectPurchaseType == "money")
		return PURCHASE_MONEY;
	if (ObjectPurchaseType == "leaf")
		return PURCHASE_LEAF;
	if (ObjectPurchaseType == "stone")
		return PURCHASE_STONE;
	if (ObjectPurchaseType == "ad")
		return PURCHASE_AD;
	return PURCHASE_MONEY;
}

/////////////// Localized price ///////////////

SexyString MagentoProductProps::GetLocalizedPriceString(bool* bRMB) const
{
	switch (GetPurchaseType())
	{
	case PURCHASE_GEM:
	case PURCHASE_COIN:
		return Sexy::UTF8StringToWString(Sexy::StrFormat("%d", __builtin_iroundf(GetPriceInUSD(false))));
	case PURCHASE_MONEY:
	{
		Sexy::IPurchaseDriver::Product product;
		if (bRMB != NULL)
		{
			*bRMB = false;
			if (ProfileMgr::GetInstance().GetPurchaseBroker()->m_purchaseDriver->GetProduct(GetCombinedSkuTierName(), &product))
			{
				int pos = product.localizedPrice.find(L"\u00a5", 0);
				if (pos != -1)
				{
					product.localizedPrice = product.localizedPrice.replace(pos, 1, L"");
					*bRMB = true;
				}
				pos = product.localizedPrice.find(L".00", 0);
				if (pos != -1)
					product.localizedPrice = product.localizedPrice.replace(pos, 3, L"");
				return product.localizedPrice;
			}
			*bRMB = true;
		}
		else if (ProfileMgr::GetInstance().GetPurchaseBroker()->m_purchaseDriver->GetProduct(GetCombinedSkuTierName(), &product))
		{
			int pos = product.localizedPrice.find(L"\u00a5", 0);
			if (pos != -1)
				product.localizedPrice = product.localizedPrice.replace(pos, 1, L"");
			pos = product.localizedPrice.find(L".00", 0);
			if (pos != -1)
				product.localizedPrice = product.localizedPrice.replace(pos, 3, L"");
			return product.localizedPrice;
		}
		break;
	}
	}
	return Sexy::UTF8StringToWString(Sexy::StrFormat("%d", __builtin_iroundf(GetPriceInUSD(false))));
}
