//
//  ButtonListener.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-16.
//

#include "ButtonListener.h"

using namespace Sexy;

ButtonListener::ButtonListener() {}

void ButtonListener::ButtonPress(int theId) {}

void ButtonListener::ButtonPress(int theId, int theClickCount)
{
	ButtonPress(theId);
}

void ButtonListener::ButtonDepress(int theId) {}

void ButtonListener::ButtonDownTick(int theId) {}

void ButtonListener::ButtonMouseEnter(int theId) {}

void ButtonListener::ButtonMouseLeave(int theId) {}

void ButtonListener::ButtonMouseMove(int theId, int theX, int theY) {}
