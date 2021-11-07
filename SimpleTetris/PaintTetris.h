// テトリス関連の画面描画
//

#pragma once

#include "DxLib.h"
#include "ConstTetris.h"
#include "ConstScreenLayout.h"
#include "TetrisOneGameState.h"

namespace PaintTetris
{

/////////////////////////////////////////////////////////////////////////////
//
// 1x1のブロックの描画
//

inline void paintCell(int x, int y, int xSize, int ySize, ConstTetris::MinoType minoType)
{
	DrawFillBox(x, y, x + xSize, y + ySize, ConstScreenLayout::getMinoColor(minoType));
	DrawBox(x, y, x + xSize, y + ySize, 0x888888, FALSE);
}

inline void paintBoardFrameCell(int x, int y, ConstTetris::MinoType minoType)
{
	paintCell(
		ConstScreenLayout::BOARD_FRAME_X + (x * ConstScreenLayout::BOARD_FRAME_CELL_X_SIZE),
		(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) - ((y + 1) * ConstScreenLayout::BOARD_FRAME_CELL_Y_SIZE),
		ConstScreenLayout::BOARD_FRAME_CELL_X_SIZE,
		ConstScreenLayout::BOARD_FRAME_CELL_Y_SIZE,
		minoType
	);
}

inline void paintHoldFrameCell(int x, int y, ConstTetris::MinoType minoType)
{
	paintCell(
		ConstScreenLayout::HOLD_FRAME_X + (x * ConstScreenLayout::MINO_FRAME_CELL_X_SIZE),
		(ConstScreenLayout::HOLD_FRAME_Y + ConstScreenLayout::MINO_FRAME_Y_SIZE) - ((y + 1) * ConstScreenLayout::MINO_FRAME_CELL_Y_SIZE),
		ConstScreenLayout::MINO_FRAME_CELL_X_SIZE,
		ConstScreenLayout::MINO_FRAME_CELL_Y_SIZE,
		minoType);
}

inline void paintNextFrameCell(int index, int x, int y, ConstTetris::MinoType minoType)
{
	int y2 = ConstScreenLayout::NEXT_FRAME_Y + (index * (ConstScreenLayout::MINO_FRAME_Y_SIZE + ConstScreenLayout::FRAME_MARGIN));

	paintCell(
		ConstScreenLayout::NEXT_FRAME_X + (x * ConstScreenLayout::MINO_FRAME_CELL_X_SIZE),
		(y2 + ConstScreenLayout::MINO_FRAME_Y_SIZE) - ((y + 1) * ConstScreenLayout::MINO_FRAME_CELL_Y_SIZE),
		ConstScreenLayout::MINO_FRAME_CELL_X_SIZE,
		ConstScreenLayout::MINO_FRAME_CELL_Y_SIZE,
		minoType);
}


/////////////////////////////////////////////////////////////////////////////
//
// フレームの描画
//

inline void paintHoldFrame()
{
	DrawBox(
		ConstScreenLayout::HOLD_FRAME_X,
		ConstScreenLayout::HOLD_FRAME_Y,
		ConstScreenLayout::HOLD_FRAME_X + ConstScreenLayout::MINO_FRAME_X_SIZE,
		ConstScreenLayout::HOLD_FRAME_Y + ConstScreenLayout::MINO_FRAME_Y_SIZE,
		0xEE4400,
		FALSE
	);
}
inline void paintCannotHold()
{
	DrawLine(
		ConstScreenLayout::HOLD_FRAME_X,
		ConstScreenLayout::HOLD_FRAME_Y,
		ConstScreenLayout::HOLD_FRAME_X + ConstScreenLayout::MINO_FRAME_X_SIZE,
		ConstScreenLayout::HOLD_FRAME_Y + ConstScreenLayout::MINO_FRAME_Y_SIZE,
		0xEE4400,
		3
	);
}

inline void paintNextFrame(int index)
{
	int y = ConstScreenLayout::NEXT_FRAME_Y + (index * (ConstScreenLayout::MINO_FRAME_Y_SIZE + ConstScreenLayout::FRAME_MARGIN));
	DrawBox(
		ConstScreenLayout::NEXT_FRAME_X,
		y,
		ConstScreenLayout::NEXT_FRAME_X + ConstScreenLayout::MINO_FRAME_X_SIZE,
		y + ConstScreenLayout::MINO_FRAME_Y_SIZE,
		0x44EE00,
		FALSE
	);
}

inline void paintBaordFrame()
{
	DrawBox(ConstScreenLayout::BOARD_FRAME_X,
		ConstScreenLayout::BOARD_FRAME_Y,
		ConstScreenLayout::BOARD_FRAME_X + ConstScreenLayout::BOARD_FRAME_X_SIZE,
		ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE,
		0x0044EE,
		FALSE
	);
}


/////////////////////////////////////////////////////////////////////////////
//
// あるゲーム状態の描画
//

void paintTetris(const TetrisOneGameState& tetris);

}