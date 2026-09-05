//
//  WorldMapEditorFactory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "WorldMapEditorFactory.h"

/////////////// WorldMapEditorFactory ///////////////

WorldMapEditorFactory::WorldMapEditorFactory()
{
	mEditorFlags = (MapEditorFlags)0;
	SetFlag(mEditorFlags, EDITORFLAG_DRAW_BACKGROUND, true);
	SetFlag(mEditorFlags, EDITORFLAG_DRAW_FOREGROUND, true);
	SetFlag(mEditorFlags, EDITORFLAG_DRAW_HIDDEN_FOREGROUND, true);
	SetFlag(mEditorFlags, EDITORFLAG_DRAW_EVENTS, true);
}

WorldMapEditor& WorldMapEditorFactory::GetEditor()
{
	return mDefaultEditor;
}

void WorldMapEditorFactory::SetEditorEnabled(bool i_isEnabled)
{
	SetFlag(mEditorFlags, EDITORFLAG_ENABLED, i_isEnabled);
}

bool WorldMapEditorFactory::IsEditorEnabled()
{
	return TestFlag(mEditorFlags, EDITORFLAG_ENABLED);
}
