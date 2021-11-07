// �e�g���X�̂P�����̂Ƃ���u�Ԃ̏�Ԃ�\������
// �����O�̃J�E���g�_�E����DAS�Ȃǂ̑�����͂�������Ԃ̂P�Ƃ���
// �ݒu���m�肵�Ă��Ȃ��J�����g�~�m�̓{�[�h��ɂ͒u���Ȃ�����
// �J�E���g�_�E���� [ConstTetris::MATCH_START_COUNTDOWN �` 0] �܂ł͈̔͂Ƃ��邱��
//

#pragma once

#include "ConstTetris.h"
#include "CurrentMinoState.h"
#include "TetrisInputProc.h"

struct TetrisOneGameState
{
	ConstTetris::MatchState matchState;
	int countdown;

	TetrisInputProc inputProc;

	ConstTetris::Board board;

	ConstTetris::MinoType holdMinoType;
	bool canHold;

	ConstTetris::Next next;
	ConstTetris::Bag bag;

	CurrentMinoState current;
};

