//
//  IViewContainer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "AndroidViewContainerMgr.h"
#include "IViewContainer.h"

/////////////// IViewContainer ///////////////

IViewContainer::IViewContainer()
{
}

IViewContainer* IViewContainer::CreateViewContainerManager()
{
	return new AndroidViewContainerMgr();
}
