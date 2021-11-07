#include "TetrisFunction.h"
#include "OnException.h"
#include "DxLib.h"

using namespace ConstTetris;

namespace TetrisFunction
{

void initialize(TetrisOneGameState& tetris)
{
	// 乱数初期化
	SRand(GetNowCount());

	tetris.matchState = MatchState::COUNTDOWN;
	tetris.countdown = MATCH_START_COUNTDOWN;
	tetris.inputProc.initialize();

	// ボード
	for (int y = 0; y < BOARD_Y_SIZE; ++y)
		for (int x = 0; x < BOARD_X_SIZE; ++x)
			tetris.board[y][x] = MinoType::EMPTY;

	// ホールド
	tetris.holdMinoType = MinoType::EMPTY;
	tetris.canHold = true;

	// バッグ
	initBag(tetris.bag);

	// ネクスト
	for (int i = 0; i < NEXT_NUM; ++i)
		circulateNext(tetris.next, tetris.bag);

	// カレントミノ
	// 初期状態は座標とか向きとかの概念は持たない
	tetris.current = {MinoType::EMPTY};
}

bool countdown(MatchState& matchState, int& countdown)
{
	--countdown;
	if (countdown == 0)
	{
		matchState = MatchState::MATCH;
		return true;
	}
	return false;
}

bool isInBoard(int x, int y)
{
	return 0 <= x && x < BOARD_X_SIZE && 0 <= y && y <= BOARD_Y_SIZE;
}

void initBag(Bag& bag)
{
	// 7種のミノを全部バッグに詰める
	for (int i = 0; i < BAG_SIZE; ++i)
		bag[i] = MinoType(i);

	// バッグをシャッフルする
	for (int i = 0; i < BAG_SIZE; ++i)
	{
		int r = GetRand(BAG_SIZE - 1);
		MinoType t = bag[i];
		bag[i] = bag[r];
		bag[r] = t;
	}
}

void circulateNext(Next& next, Bag& bag)
{
	// ネクスト循環
	for (int i = 0; i < NEXT_NUM - 1; ++i)
		next[i] = next[i + 1];

	// バッグの空でない要素を探索
	for (int i = 0; i < BAG_SIZE; ++i)
		if (bag[i] != MinoType::EMPTY)
		{
			// ネクストの最後尾のミノタイプはバッグから貰う
			next[NEXT_NUM - 1] = bag[i];
			bag[i] = MinoType::EMPTY;
			return;
		}

	// バッグが空だったらバッグを初期化
	initBag(bag);

	// ネクストの最後尾のミノタイプはバッグから貰う
	next[NEXT_NUM - 1] = bag[0];
	bag[0] = MinoType::EMPTY;
}

bool setCurrentStartPos(ConstTetris::Board& board, CurrentMinoState& current)
{
	current.dir = MinoDir::UP;
	current.x = BOARD_X_SIZE / 2 - 2;
	current.y = BOARD_VISIBLE_Y_SIZE - 4;
	current.tspin = TSpin::NO;

	if (canPut(board, current))
		return true;

	++current.y;

	return canPut(board, current);
}

bool moveRight(Board& board, CurrentMinoState& current)
{
	++current.x;

	if (!canPut(board, current))
	{
		--current.x;
		return false;
	}

	current.tspin = TSpin::NO;

	return true;
}

bool moveLeft(Board& board, CurrentMinoState& current)
{
	--current.x;

	if (!canPut(board, current))
	{
		++current.x;
		return false;
	}

	current.tspin = TSpin::NO;

	return true;
}

bool moveDown(Board& board, CurrentMinoState& current)
{
	--current.y;

	if (!canPut(board, current))
	{
		++current.y;
		return false;
	}

	current.tspin = TSpin::NO;

	return true;
}

int moveDownEdge(Board& board, CurrentMinoState& current)
{
	int count = 0;
	while (moveDown(board, current))
		++count;
	return count;
}

int rotateRight(Board& board, CurrentMinoState& current)
{
	current.dir = DirRight(current.dir);

	if (!canPut(board, current))
	{
		current.dir = DirLeft(current.dir);
		return false;
	}

	current.tspin = TSpin::NO;

	return true;
}

int rotateLeft(Board& board, CurrentMinoState& current)
{
	current.dir = DirLeft(current.dir);

	if (!canPut(board, current))
	{
		current.dir = DirRight(current.dir);
		return false;
	}

	current.tspin = TSpin::NO;

	return true;
}

bool canPut(const ConstTetris::Board& board, const CurrentMinoState& current)
{
	const auto& shape = getMinoShape(current.type, current.dir);

	for (int i = 0; i < MINO_SHAPE_POS_NUM; i += 2)
	{
		int x = current.x + shape[i];
		int y = current.y + shape[i + 1];

		if (!isInBoard(x, y) || board[y][x] != MinoType::EMPTY)
			return false;
	}

	return true;
}

void put(ConstTetris::Board& board, CurrentMinoState& current)
{
	const auto& shape = getMinoShape(current.type, current.dir);

	for (int i = 0; i < MINO_SHAPE_POS_NUM; i += 2)
	{
		int x = current.x + shape[i];
		int y = current.y + shape[i + 1];

		if (!isInBoard(x, y))
			OnException::TerminateProgram(__FUNCTION__, __LINE__, x, y);

		board[y][x] = current.type;
	}
}

}