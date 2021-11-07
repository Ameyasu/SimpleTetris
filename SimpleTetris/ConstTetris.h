// �e�g���X�Q�[���̐��������肷��萔�Q
// �S�Ă̍��W�ɂ����ĉ����͉E�����A�c���͏����
// �{�[�h��� ����(x, y)=(0, 0) �E��(x, y)=(9, 0)
//

#pragma once

#include "OnException.h"

namespace ConstTetris
{

/////////////////////////////////////////////////////////////////////////////
//
// �~�m
//

static constexpr int MINO_TYPE_NUM = 7;
static constexpr int MINO_DIR_NUM = 4;

// �������ύX������ȉ����������Ĉ������������̂��ύX
// [�A��] ConstTetris::MinoType
enum class MinoType
{
	I, J, L, S, Z, T, O, GARBAGE, EMPTY
};

// [�A��] ConstTetris::MinoDir
enum class MinoDir
{
	UP, RIGHT, DOWN, LEFT
};

// ����MinoDir�l����E��]�������ꍇ��MinoDir�l���擾
constexpr MinoDir DirRight(MinoDir dir)
{
	return dir < MinoDir::LEFT ? MinoDir(static_cast<int>(dir) + 1) : MinoDir::UP;
}
// ����MinoDir�l���獶��]�������ꍇ��MinoDir�l���擾
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
// �l�N�X�g
//

static constexpr int NEXT_NUM = 5;
static constexpr int BAG_SIZE = MINO_TYPE_NUM; // �o�b�O�T�C�Y�̓~�m�̎�ސ��Ə�Ɉ�v���邱��

using Next = MinoType[NEXT_NUM];
using Bag = MinoType[BAG_SIZE];


/////////////////////////////////////////////////////////////////////////////
//
// �{�[�h
//

static constexpr int BOARD_X_SIZE = 10;
static constexpr int BOARD_Y_SIZE = 40;
static constexpr int BOARD_VISIBLE_Y_SIZE = 21;

using Board = MinoType[BOARD_Y_SIZE][BOARD_X_SIZE];


/////////////////////////////////////////////////////////////////////////////
//
// �~�m�̌`
//

static constexpr int MINO_SHAPE_POS_NUM = 8;

// [�A��] ConstTetris::MinoType
static constexpr int MINO_SHAPE[MINO_TYPE_NUM][MINO_DIR_NUM][MINO_SHAPE_POS_NUM] =
{
	// I
	{
		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 2, 2, 2, 3, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{2, 0, 2, 1, 2, 2, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 1, 1, 1, 2, 1, 3, 1},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 0, 1, 1, 1, 2, 1, 3},
	},

	// J
	{
		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 0, 3, 1, 2, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 1, 1, 2, 1, 3, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 2, 2, 2, 2, 1},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 1, 1, 1, 1, 2, 1, 3},
	},

	// L
	{
		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 2, 2, 2, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 1, 1, 2, 1, 3, 2, 1},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 1, 0, 2, 1, 2, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 3, 1, 1, 1, 2, 1, 3},
	},

	// S
	{
		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 2, 1, 3, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 2, 1, 3, 2, 2, 2, 1},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 1, 1, 1, 1, 2, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 0, 3, 1, 2, 1, 1},
	},

	// Z
	{
		// ��������
		// ��������
		// ��������
		// ��������
		{0, 3, 1, 3, 1, 2, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 1, 1, 2, 2, 2, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 2, 1, 1, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 1, 0, 2, 1, 2, 1, 3},
	},

	// T
	{
		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 2, 1, 3, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 1, 1, 2, 1, 3, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 1, 1, 2, 2, 2},

		// ��������
		// ��������
		// ��������
		// ��������
		{0, 2, 1, 1, 1, 2, 1, 3},
	},

	// O
	{
		// ��������
		// ��������
		// ��������
		// ��������
		{1, 2, 1, 3, 2, 2, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 2, 1, 3, 2, 2, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 2, 1, 3, 2, 2, 2, 3},

		// ��������
		// ��������
		// ��������
		// ��������
		{1, 2, 1, 3, 2, 2, 2, 3},
	},
};

using MinoShapeRef = const int(&)[MINO_SHAPE_POS_NUM];

// [�A��] ConstTetris::MinoType
// [�A��] ConstTetris::MinoDir
constexpr MinoShapeRef getMinoShape(MinoType minoType, MinoDir minoDir)
{
	if ((minoType < MinoType::I || MinoType::O < minoType) || (minoDir < MinoDir::UP || MinoDir::LEFT < minoDir))
		OnException::TerminateProgram(__FUNCTION__, __LINE__, static_cast<int>(minoType), static_cast<int>(minoDir));

	return MINO_SHAPE[static_cast<int>(minoType)][static_cast<int>(minoDir)];
}


/////////////////////////////////////////////////////////////////////////////
//
// ����
//

static constexpr int MATCH_START_COUNTDOWN = 3 * 60; // 3�b

enum class MatchState
{
	COUNTDOWN,
	MATCH,
	WIN,
	LOSE
};


/////////////////////////////////////////////////////////////////////////////
//
// �e�g���X�p�̑������
//

// �L�[�{�[�h�Ȃǂ̕����I�ȓ��͂Ƃ͕ʕ�
// �������͂�OR���Z���č������ĕ\��

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
