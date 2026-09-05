// Reconstructed by EvilHack28 on 2026-09-05
#include <string>
#include "EASquaredCore.h"

bool EASquaredCore::inSelectedMonetizationGroup(int transactionCount, const std::string& monetizationGroup)
{
	if (monetizationGroup.compare("monetizers") == 0)
		return transactionCount > 0;
	if (monetizationGroup.compare("nonmonetizers") == 0)
		return transactionCount == 0;
	return true;
}

bool EASquaredCore::playerHasTooManyCoins(int playerCoins, int maximumCoins)
{
	return playerCoins > maximumCoins;
}

bool EASquaredCore::playerInstalledRecently(int daysSinceInstall, int minimumDaysSinceInstall)
{
	return daysSinceInstall < minimumDaysSinceInstall;
}
