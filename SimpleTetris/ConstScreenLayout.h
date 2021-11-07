// ��ʃT�C�Y�����肷��萔�Q
//

#pragma once

#include "ConstTetris.h"
#include "OnException.h"

namespace ConstScreenLayout
{

/////////////////////////////////////////////////////////////////////////////
//
// �{�[�h�g�ł�1x1�̃u���b�N�̉摜�T�C�Y
//

static constexpr int BOARD_FRAME_CELL_X_SIZE = 32;
static constexpr int BOARD_FRAME_CELL_Y_SIZE = 32;


/////////////////////////////////////////////////////////////////////////////
//
// �l�N�X�g�g��z�[���h�g�ł�1x1�̃u���b�N�̃T�C�Y
//

static constexpr int MINO_FRAME_CELL_X_SIZE = 18;
static constexpr int MINO_FRAME_CELL_Y_SIZE = 18;


/////////////////////////////////////////////////////////////////////////////
//
// �l�N�X�g�g�ƃz�[���h�g�̃~�m��\������g�̃T�C�Y
//

static constexpr int MINO_FRAME_X_CELL_NUM = 4;
static constexpr int MINO_FRAME_Y_CELL_NUM = 4;

static constexpr int MINO_FRAME_X_SIZE = MINO_FRAME_CELL_X_SIZE * MINO_FRAME_X_CELL_NUM;
static constexpr int MINO_FRAME_Y_SIZE = MINO_FRAME_CELL_Y_SIZE * MINO_FRAME_Y_CELL_NUM;


/////////////////////////////////////////////////////////////////////////////
//
// �{�[�h�g�̃T�C�Y
//

static constexpr int BOARD_FRAME_X_SIZE = BOARD_FRAME_CELL_X_SIZE * ConstTetris::BOARD_X_SIZE;
static constexpr int BOARD_FRAME_Y_SIZE = (BOARD_FRAME_CELL_Y_SIZE * ConstTetris::BOARD_VISIBLE_Y_SIZE) - (BOARD_FRAME_CELL_Y_SIZE * 2 / 3); // �ŏ�i�͏����B��


/////////////////////////////////////////////////////////////////////////////
//
// �{�[�h�g�E�l�N�X�g�g�E�z�[���h�g�̍��W
//

static constexpr int FRAME_MARGIN = 10; // �g���m�̌��Ԃ��J����L��

static constexpr int HOLD_FRAME_X = 0;
static constexpr int HOLD_FRAME_Y = 100;

static constexpr int BOARD_FRAME_X = HOLD_FRAME_X + MINO_FRAME_X_SIZE + FRAME_MARGIN;
static constexpr int BOARD_FRAME_Y = HOLD_FRAME_Y - FRAME_MARGIN * 2;

static constexpr int NEXT_FRAME_X = BOARD_FRAME_X + BOARD_FRAME_X_SIZE + FRAME_MARGIN;
static constexpr int NEXT_FRAME_Y = HOLD_FRAME_Y;


/////////////////////////////////////////////////////////////////////////////
//
// �E�B���h�E�̃N���C�A���g�̈�̃T�C�Y
//

static constexpr int CLIENT_X_SIZE = NEXT_FRAME_X + MINO_FRAME_X_SIZE;
static constexpr int CLIENT_Y_SIZE = BOARD_FRAME_Y + BOARD_FRAME_Y_SIZE;


/////////////////////////////////////////////////////////////////////////////
//
// �~�m�̐F
//

// [�A��] ConstTetris::MinoType
// ���̕ϐ��͒��ڎg�킸�AgetMinoColor�֐���ʂ��Ďg��
static constexpr unsigned int MINO_COLOR[] =
{
	0x00FFFF, // I
	0x0000FF, // J
	0xFF8822, // L
	0x22FF22, // S
	0xFF0000, // Z
	0xFF00FF, // T
	0xD0D000, // O
	0xEEEEEE, // Garbage
	0xFFFFFF, // Empty
};

// [�A��] ConstTetris::MinoType
constexpr unsigned int getMinoColor(ConstTetris::MinoType minoType)
{
	if (minoType < ConstTetris::MinoType::I || ConstTetris::MinoType::EMPTY < minoType)
		OnException::TerminateProgram(__FUNCTION__, __LINE__, static_cast<int>(minoType));

	return MINO_COLOR[static_cast<int>(minoType)];
}

}