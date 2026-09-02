//
//  BoardTransforms.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "BoardTransforms.h"

#include <algorithm>

#include "BoardConstants.h"
#include "PlantPropertySheet.h"
#include "PlantType.h"
#include "Rect.h"
#include "TodCommon.h"

namespace BoardTransforms
{

// Grid to BoardSpace - Bounded

Sexy::Point GridToBoardSpace(const Sexy::Point& i_gridPoint)
{
	return GridToBoardSpaceUnbounded(i_gridPoint);
}

int GridToBoardSpaceX(const int i_gridX)
{
	return GridToBoardSpaceXUnbounded(i_gridX);
}

int GridToBoardSpaceY(const int i_gridY)
{
	return GridToBoardSpaceYUnbounded(i_gridY);
}

Sexy::Point GridToBoardSpacePos(int i_gridX, int i_gridY)
{
	return GridToBoardSpace(Sexy::Point(i_gridX, i_gridY));
}

// Grid to BoardSpace - Unbounded

Sexy::Point GridToBoardSpaceUnbounded(const Sexy::Point& i_gridPoint)
{
	return Sexy::Point(GridToBoardSpaceXUnbounded(i_gridPoint.mX),
	                   GridToBoardSpaceYUnbounded(i_gridPoint.mY));
}

int GridToBoardSpaceXUnbounded(const int i_gridX)
{
	int width = BoardConstants::GRIDSQUARE_WIDTH();
	return i_gridX * width + BoardConstants::GRID_LEFT + width / 2;
}

int GridToBoardSpaceYUnbounded(const int i_gridY)
{
	int height = BoardConstants::GRIDSQUARE_HEIGHT();
	// the extra 24 nudges rows down so entities sit on the ground line, not the cell top
	return i_gridY * height + BoardConstants::GRID_TOP + height / 2 + 24;
}

float GridToBoardSpaceXUnbounded_Float(const float i_gridX)
{
	int width = BoardConstants::GRIDSQUARE_WIDTH();
	return i_gridX * width + width / 2 + (float)BoardConstants::GRID_LEFT;
}

// Grid to BoardSpace Rect - Unbounded

Sexy::Rect GridToBoardSpaceRect(const int i_gridX, const int i_gridY, const int i_gridExtentsX, const int i_gridExtentsY)
{
	Sexy::Rect rect;
	rect.mWidth  = BoardConstants::GRIDSQUARE_WIDTH()  * i_gridExtentsX;
	rect.mHeight = BoardConstants::GRIDSQUARE_HEIGHT() * i_gridExtentsY;
	rect.mX = BoardConstants::GRIDSQUARE_WIDTH()  * i_gridX + BoardConstants::GRID_LEFT;
	rect.mY = BoardConstants::GRIDSQUARE_HEIGHT() * i_gridY + BoardConstants::GRID_TOP;
	return rect;
}

Sexy::Rect GridToBoardSpaceRect(const Sexy::Point& i_gridPoint)
{
	return GridToBoardSpaceRect(i_gridPoint.mX, i_gridPoint.mY);
}

Sexy::Rect GridToBoardSpaceRect(const Sexy::Point& i_gridPoint, const Sexy::Point& i_gridExtents)
{
	return GridToBoardSpaceRect(i_gridPoint.mX, i_gridPoint.mY, i_gridExtents.mX, i_gridExtents.mY);
}

Sexy::Rect GridRectToBoardSpaceRect(const Sexy::Rect& i_gridRect)
{
	return GridToBoardSpaceRect(i_gridRect.mX, i_gridRect.mY, i_gridRect.mWidth, i_gridRect.mHeight);
}

// BoardSpace to Grid - Bounded

void BoardSpaceToGrid(const int i_x, const int i_y, int& o_col, int& o_row)
{
	Sexy::Point grid = BoardSpaceToGrid(i_x, i_y);
	o_col = grid.mX;
	o_row = grid.mY;
}

void BoardSpaceToGrid(const float i_x, const float i_y, int& o_col, int& o_row)
{
	Sexy::Point grid = BoardSpaceToGrid(i_x, i_y);
	o_col = grid.mX;
	o_row = grid.mY;
}

Sexy::Point BoardSpaceToGrid(const int i_x, const int i_y)
{
	int col = BoardSpaceToGridX(i_x);
	int row = BoardSpaceToGridY(i_y);
	if (col == -1 || row == -1)
		col = row = -1;
	return Sexy::Point(col, row);
}

Sexy::Point BoardSpaceToGrid(const float i_x, const float i_y)
{
	int col = BoardSpaceToGridX(i_x);
	int row = BoardSpaceToGridY(i_y);
	if (col == -1 || row == -1)
		col = row = -1;
	return Sexy::Point(col, row);
}

int BoardSpaceToGridX(const int i_pixelX)
{
	int col = BoardSpaceToGridXUnbounded(i_pixelX);
	if (col < 0 || col >= BoardConstants::NUMBER_OF_COLUMNS())
		return -1;
	return col;
}

int BoardSpaceToGridX(const float i_pixelX)
{
	int col = BoardSpaceToGridXUnbounded(i_pixelX);
	if (col < 0 || col >= BoardConstants::NUMBER_OF_COLUMNS())
		return -1;
	return col;
}

int BoardSpaceToGridY(const int i_pixelY)
{
	int row = BoardSpaceToGridYUnbounded(i_pixelY);
	if (row < 0 || row >= BoardConstants::NUMBER_OF_ROWS())
		return -1;
	return row;
}

int BoardSpaceToGridY(const float i_pixelY)
{
	int row = BoardSpaceToGridYUnbounded(i_pixelY);
	if (row < 0 || row >= BoardConstants::NUMBER_OF_ROWS())
		return -1;
	return row;
}

// BoardSpace to Grid - Keep on Board

int BoardSpaceToGridXKeepOnBoard(const int i_pixelX)
{
	int col = BoardSpaceToGridXUnbounded(i_pixelX);
	return std::min(std::max(0, col), BoardConstants::NUMBER_OF_COLUMNS() - 1);
}

int BoardSpaceToGridXKeepOnBoard(const float i_pixelX)
{
	int col = BoardSpaceToGridXUnbounded(i_pixelX);
	return std::min(std::max(0, col), BoardConstants::NUMBER_OF_COLUMNS() - 1);
}

int BoardSpaceToGridYKeepOnBoard(const int i_pixelY)
{
	int row = BoardSpaceToGridYUnbounded(i_pixelY);
	return std::min(std::max(0, row), BoardConstants::NUMBER_OF_ROWS() - 1);
}

int BoardSpaceToGridYKeepOnBoard(const float i_pixelY)
{
	int row = BoardSpaceToGridYUnbounded(i_pixelY);
	return std::min(std::max(0, row), BoardConstants::NUMBER_OF_ROWS() - 1);
}

// Planting BoardSpace to Grid

// the column is not affected by the plant type, so these just forward
int PlantingBoardSpaceToGridX(const int i_pixelX, PlantTypePtr i_seedType)
{
	return BoardSpaceToGridX(i_pixelX);
}

int PlantingBoardSpaceToGridX(const float i_pixelX, PlantTypePtr i_seedType)
{
	return BoardSpaceToGridX(i_pixelX);
}

int PlantingBoardSpaceToGridY(const int i_pixelY, PlantTypePtr i_seedType)
{
	int y = i_pixelY;
	OffsetYForPlanting(y, i_seedType);
	return BoardSpaceToGridY(y);
}

int PlantingBoardSpaceToGridY(const float i_pixelY, PlantTypePtr i_seedType)
{
	int yOffset = 0;
	OffsetYForPlanting(yOffset, i_seedType);
	float fOffset = yOffset;
	return BoardSpaceToGridY(i_pixelY + fOffset);
}

// shifts a planting Y by the plant's per-type PlantingOffsetY so the cursor
// snaps to the cell the plant will actually occupy
void OffsetYForPlanting(int& i_y, PlantTypePtr i_seedType)
{
	if (i_seedType.IsValid())
	{
		float offset = i_seedType->Properties->PlantingOffsetY;
		i_y = (int)(i_y + offset);
	}
}

// BoardSpace to Grid - Unbounded

int BoardSpaceToGridXUnbounded(const int i_pixelX)
{
	return (i_pixelX - BoardConstants::GRID_LEFT) / BoardConstants::GRIDSQUARE_WIDTH();
}

int BoardSpaceToGridXUnbounded(const float i_pixelX)
{
	return (int)floorf((i_pixelX - BoardConstants::GRID_LEFT) / (float)BoardConstants::GRIDSQUARE_WIDTH());
}

float BoardSpaceToGridXUnboundedFloat(const float i_pixelX)
{
	return (i_pixelX - BoardConstants::GRID_LEFT) / (float)BoardConstants::GRIDSQUARE_WIDTH();
}

int BoardSpaceToGridYUnbounded(const int i_pixelY)
{
	return (i_pixelY - BoardConstants::GRID_TOP) / BoardConstants::GRIDSQUARE_HEIGHT();
}

int BoardSpaceToGridYUnbounded(const float i_pixelY)
{
	return (int)floorf((i_pixelY - BoardConstants::GRID_TOP) / (float)BoardConstants::GRIDSQUARE_HEIGHT());
}

float BoardSpaceToGridYUnboundedFloat(const float i_pixelY)
{
	return (i_pixelY - BoardConstants::GRID_TOP) / (float)BoardConstants::GRIDSQUARE_HEIGHT();
}

Sexy::Point BoardSpaceToGridUnbounded(const SexyVector3& i_boardPosition)
{
	return Sexy::Point(BoardSpaceToGridXUnbounded(i_boardPosition.x),
	                   BoardSpaceToGridYUnbounded(i_boardPosition.y));
}

// Utilities

void ClampGridCoords(int& io_gridX, int& io_gridY)
{
	io_gridX = ClampInt(io_gridX, 0, BoardConstants::NUMBER_OF_COLUMNS() - 1);
	io_gridY = ClampInt(io_gridY, 0, BoardConstants::NUMBER_OF_ROWS() - 1);
}

bool IsGridCoordinateOnBoard(const int i_gridX, const int i_gridY)
{
	return i_gridX >= 0
	    && i_gridY >= 0
	    && i_gridX < BoardConstants::NUMBER_OF_COLUMNS()
	    && i_gridY < BoardConstants::NUMBER_OF_ROWS();
}

}
