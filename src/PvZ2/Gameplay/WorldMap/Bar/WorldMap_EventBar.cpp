//
//  WorldMap_EventBar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_EventBar.h"

void WorldMap_EventBar::forceLODCheck()
{
}

void WorldMap_EventBar::createYetiEventBar()
{
}

void WorldMap_EventBar::onServerTimeChanged()
{
}

void WorldMap_EventBar::lodReplayForAdCallback()
{
}

void WorldMap_EventBar::prepareLODDisplayCommon()
{
}

time_t WorldMap_EventBar::getNextEventTimeRemaining()
{
	return NULL;
}

time_t WorldMap_EventBar::getCurrentEventTimeRemaining()
{
	return NULL;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_EventBar);

bool WorldMap_EventBar::drawProgressBar(Sexy::Graphics* i_g)
{
	return false;
}

void WorldMap_EventBar::createPlayNowButton(SexyString buttonText, EventBarType i_eventType, int i_coinCost)
{
}

void WorldMap_EventBar::createLODUpcomingText(std::string& headerText, std::string& descText)
{
}

void WorldMap_EventBar::prepareLODDisplayUpcoming(bool shouldCreatePlayButton, EventBarType i_eventBarType)
{
}
