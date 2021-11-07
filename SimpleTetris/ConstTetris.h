// テトリスゲームの性質を決定する定数群
// 全ての座標において横軸は右向き、縦軸は上向き
// ボード上で 左下(x, y)=(0, 0) 右下(x, y)=(9, 0)
//

#pragma once

#include "OnException.h"

namespace ConstTetris
{

/////////////////////////////////////////////////////////////////////////////
//
// ミノ
//

static constexpr int MINO_TYPE_NUM = 7;
static constexpr int MINO_DIR_NUM = 4;

// ↓これを変更したら以下を検索して引っかかったのも変更
// [連動] ConstTetris::MinoType
enum class MinoType
{
	I, J, L, S, Z, T, O, GARBAGE, EMPTY
};

// [連動] ConstTetris::MinoDir
enum class MinoDir
{
	UP, RIGHT, DOWN, LEFT
};

// あるMinoDir値から右回転させた場合のMinoDir値を取得
constexpr MinoDir DirRight(MinoDir dir)
{
	return dir < MinoDir::LEFT ? MinoDir(static_cast<int>(dir) + 1) : MinoDir::UP;
}
// あるMinoDir値から左回転させた場合のMinoDir値を取得
constexpr MinoDir DirLeft(MinoDir dir)
{
	return dir > MinoDir::UP ? MinoDir(static_cast<int>(dir) - 1) : MinoDir::LEFT;
}

enum class TSpin
{
	NO, YES, MINI
};


/////////////////////////////////////////////////////////////////////////////
//
// ネクスト
//

static constexpr int NEXT_NUM = 5;
static constexpr int BAG_SIZE = MINO_TYPE_NUM; // バッグサイズはミノの種類数と常に一致すること

using Next = MinoType[NEXT_NUM];
using Bag = MinoType[BAG_SIZE];


/////////////////////////////////////////////////////////////////////////////
//
// ボード
//

static constexpr int BOARD_X_SIZE = 10;
static constexpr int BOARD_Y_SIZE = 40;
static constexpr int BOARD_VISIBLE_Y_SIZE = 21;

using Board = MinoType[BOARD_Y_SIZE][BOARD_X_SIZE];


/////////////////////////////////////////////////////////////////////////////
//
// ミノの形
//

static constexpr int MINO_SHAPE_POS_NUM = 8;

// [連動] ConstTetris::MinoType
static constexpr int MINO_SHAPE[MINO_TYPE_NUM][MINO_DIR_NUM][MINO_SHAPE_POS_NUM] =
{
	// I
	{
		// □□□□
		// ■■■■
		// □□□□
		// □□□□
		{0, 2, 1, 2, 2, 2, 3, 2},

		// □□■□
		// □□■□
		// □□■□
		// □□■□
		{2, 0, 2, 1, 2, 2, 2, 3},

		// □□□□
		// □□□□
		// ■■■■
		// □□□□
		{0, 1, 1, 1, 2, 1, 3, 1},

		// □■□□
		// □■□□
		// □■□□
		// □■□□
		{1, 0, 1, 1, 1, 2, 1, 3},
	},

	// J
	{
		// ■□□□
		// ■■■□
		// □□□□
		// □□□□
		{0, 2, 0, 3, 1, 2, 2, 2},

		// □■■□
		// □■□□
		// □■□□
		// □□□□
		{1, 1, 1, 2, 1, 3, 2, 3},

		// □□□□
		// ■■■□
		// □□■□
		// □□□□
		{0, 2, 1, 2, 2, 2, 2, 1},

		// □■□□
		// □■□□
		// ■■□□
		// □□□□
		{0, 1, 1, 1, 1, 2, 1, 3},
	},

	// L
	{
		// □□■□
		// ■■■□
		// □□□□
		// □□□□
		{0, 2, 1, 2, 2, 2, 2, 3},

		// □■□□
		// □■□□
		// □■■□
		// □□□□
		{1, 1, 1, 2, 1, 3, 2, 1},

		// □□□□
		// ■■■□
		// ■□□□
		// □□□□
		{0, 1, 0, 2, 1, 2, 2, 2},

		// ■■□□
		// □■□□
		// □■□□
		// □□□□
		{0, 3, 1, 1, 1, 2, 1, 3},
	},

	// S
	{
		// □■■□
		// ■■□□
		// □□□□
		// □□□□
		{0, 2, 1, 2, 1, 3, 2, 3},

		// □■□□
		// □■■□
		// □□■□
		// □□□□
		{1, 2, 1, 3, 2, 2, 2, 1},

		// □□□□
		// □■■□
		// ■■□□
		// □□□□
		{0, 1, 1, 1, 1, 2, 2, 2},

		// ■□□□
		// ■■□□
		// □■□□
		// □□□□
		{0, 2, 0, 3, 1, 2, 1, 1},
	},

	// Z
	{
		// ■■□□
		// □■■□
		// □□□□
		// □□□□
		{0, 3, 1, 3, 1, 2, 2, 2},

		// □□■□
		// □■■□
		// □■□□
		// □□□□
		{1, 1, 1, 2, 2, 2, 2, 3},

		// □□□□
		// ■■□□
		// □■■□
		// □□□□
		{0, 2, 1, 2, 1, 1, 2, 2},

		// □■□□
		// ■■□□
		// ■□□□
		// □□□□
		{0, 1, 0, 2, 1, 2, 1, 3},
	},

	// T
	{
		// □■□□
		// ■■■□
		// □□□□
		// □□□□
		{0, 2, 1, 2, 1, 3, 2, 2},

		// □■□□
		// □■■□
		// □■□□
		// □□□□
		{1, 1, 1, 2, 1, 3, 2, 2},

		// □□□□
		// ■■■□
		// □■□□
		// □□□□
		{0, 2, 1, 1, 1, 2, 2, 2},

		// □■□□
		// ■■□□
		// □■□□
		// □□□□
		{0, 2, 1, 1, 1, 2, 1, 3},
	},

	// O
	{
		// □■■□
		// □■■□
		// □□□□
		// □□□□
		{1, 2, 1, 3, 2, 2, 2, 3},

		// □■■□
		// □■■□
		// □□□□
		// □□□□
		{1, 2, 1, 3, 2, 2, 2, 3},

		// □■■□
		// □■■□
		// □□□□
		// □□□□
		{1, 2, 1, 3, 2, 2, 2, 3},

		// □■■□
		// □■■□
		// □□□□
		// □□□□
		{1, 2, 1, 3, 2, 2, 2, 3},
	},
};

using MinoShapeRef = const int(&)[MINO_SHAPE_POS_NUM];

// [連動] ConstTetris::MinoType
// [連動] ConstTetris::MinoDir
constexpr MinoShapeRef getMinoShape(MinoType minoType, MinoDir minoDir)
{
	if ((minoType < MinoType::I || MinoType::O < minoType) || (minoDir < MinoDir::UP || MinoDir::LEFT < minoDir))
		OnException::TerminateProgram(__FUNCTION__, __LINE__, static_cast<int>(minoType), static_cast<int>(minoDir));

	return MINO_SHAPE[static_cast<int>(minoType)][static_cast<int>(minoDir)];
}


/////////////////////////////////////////////////////////////////////////////
//
// 試合
//

static constexpr int MATCH_START_COUNTDOWN = 3 * 60; // 3秒

enum class MatchState
{
	COUNTDOWN,
	MATCH,
	WIN,
	LOSE
};


/////////////////////////////////////////////////////////////////////////////
//
// テトリス用の操作入力
//

// キーボードなどの物理的な入力とは別物
// 同時入力はOR演算して合成して表現

static constexpr int INPUT_NONE = 0x00;
static constexpr int INPUT_MOVE_RIGHT = 0x01;
static constexpr int INPUT_MOVE_LEFT = 0x02;
static constexpr int INPUT_SOFT_DROP = 0x04;
static constexpr int INPUT_HARD_DROP = 0x08;
static constexpr int INPUT_ROTATE_RIGHT = 0x10;
static constexpr int INPUT_ROTATE_LEFT = 0x20;
static constexpr int INPUT_HOLD = 0x40;

static constexpr int DAS = 9;

}
