//
//  MetricsCollector.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "MetricsCollector.h"
#include "DamageInfo.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Accessors ///////////////

std::string MetricsCollector::GetPCPID()
{
	return MetricsCollectorNameSpace::GetPCPID();
}

std::string MetricsCollector::GetPackageName()
{
	return Android::Util::GetPackageName();
}

void MetricsCollector::SetGameplayMetrics(const GameplayMetrics& i_metrics)
{
	m_gameplayMetrics = i_metrics;
}

/////////////// Logic ///////////////

void MetricsCollector::flushCashedEvents()
{
}

void MetricsCollector::setMetricsManager()
{
}

void MetricsCollector::onSNSFlow()
{
}

void MetricsCollector::onSunProducedByShovel(int i_amount)
{
	m_gameplayMetrics.SunSpent += i_amount;
	m_gameplayMetrics.SunShoveUsedCount++;
}

void MetricsCollector::onRechargeLogWithSalesUiReward(const MagentoProductPropsPtr& product)
{
	m_tempMagento = *product.Get();
}

void MetricsCollector::onPlantDamageTaken(Plant* i_plant, Damage_Info& i_damageRemaining)
{
	m_gameplayMetrics.TotalPlantDamage = m_gameplayMetrics.TotalPlantDamage + i_damageRemaining.Amount;
}
