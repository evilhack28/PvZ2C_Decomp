//
//  ZombieType.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "ZombieType.h"

bool ZombieType::IsAbstract() const
{
	return false;
}

ZombiePropsPtr ZombieType::GetPropsPtr() const
{
	return Properties;
}

const ZombiePropertySheet* ZombieType::GetProps() const
{
	return Properties.operator->();
}

const std::vector<std::string>& ZombieType::GetArtResourceGroups() const
{
	return ResourceGroups;
}
