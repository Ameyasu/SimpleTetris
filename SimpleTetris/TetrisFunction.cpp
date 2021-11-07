#include "TetrisFunction.h"
#include "OnException.h"
#include "DxLib.h"

using namespace ConstTetris;

namespace TetrisFunction
{

void initialize(TetrisOneGameState& tetris)
{
	// ����������
	SRand(GetNowCount());

	tetris.matchState = MatchState::COUNTDOWN;
	tetris.countdown = MATCH_START_COUNTDOWN;
	tetris.inputProc.initialize();

	// �{�[�h
	for (int y = 0; y < BOARD_Y_SIZE; ++y)
		for (int x = 0; x < BOARD_X_SIZE; ++x)
			tetris.board[y][x] = MinoType::EMPTY;

	// �z�[���h
	tetris.holdMinoType = MinoType::EMPTY;
	tetris.canHold = true;

	// �o�b�O
	initBag(tetris.bag);

	// �l�N�X�g
	for (int i = 0; i < NEXT_NUM; ++i)
		circulateNext(tetris.next, tetris.bag);

	// �J�����g�~�m
	// ������Ԃ͍��W�Ƃ������Ƃ��̊T�O�͎����Ȃ�
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
	// 7��̃~�m��S���o�b�O�ɋl�߂�
	for (int i = 0; i < BAG_SIZE; ++i)
		bag[i] = MinoType(i);

	// �o�b�O���V���b�t������
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
	// �l�N�X�g�z��
	for (int i = 0; i < NEXT_NUM - 1; ++i)
		next[i] = next[i + 1];

	// �o�b�O�̋�łȂ��v�f��T��
	for (int i = 0; i < BAG_SIZE; ++i)
		if (bag[i] != MinoType::EMPTY)
		{
			// �l�N�X�g�̍Ō���̃~�m�^�C�v�̓o�b�O����Ⴄ
			next[NEXT_NUM - 1] = bag[i];
			bag[i] = MinoType::EMPTY;
			return;
		}

	// �o�b�O���󂾂�����o�b�O��������
	initBag(bag);

	// �l�N�X�g�̍Ō���̃~�m�^�C�v�̓o�b�O����Ⴄ
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