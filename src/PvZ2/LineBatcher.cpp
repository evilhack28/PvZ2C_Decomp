//
//  LineBatcher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "LineBatcher.h"

/////////////// LineBatcher ///////////////

void LineBatcher::Add(float i_x0, float i_y0, float i_x1, float i_y1, Color i_color, pvztime_t i_endTime)
{
	LineEntry* entry = add();

	if (entry)
	{
		entry->x0 = i_x0;
		entry->y0 = i_y0;
		entry->x1 = i_x1;
		entry->y1 = i_y1;
		entry->color = i_color;
		entry->endTime = i_endTime;
	}
}

void LineBatcher::DrawItem(Graphics* i_g, LineEntry* i_item)
{
	i_g->SetColor(i_item->color);
	i_g->DrawLine(i_item->x0, i_item->y0, i_item->x1, i_item->y1);
}
