//
//  PVZ2UIDialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UIDialog.h"

/////////////// Accessors ///////////////

void PVZ2UIDialog::SetBackgroundDarken(bool hasBackgroundDarken, float backgroundAlphaPercent)
{
	m_hasBackgroundDarken = hasBackgroundDarken;
	m_backgroundAlphaPercent = backgroundAlphaPercent;
}
