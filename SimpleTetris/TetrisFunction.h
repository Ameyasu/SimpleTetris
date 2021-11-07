// �e�g���X��\������̂ɕK�v�ȋ@�\�Q
// ���g�͏�Ԃ��������A�����ɓn���ꂽ��Ԃɑ΂��鑀��݂̂��s��
// 
// �l�X�ȉӏ�����Ăяo����邱�Ƃ�z�肵�A���ۓI�ȋ@�\�݂̂�񋟂��邱��
// �@�Ăяo�����̗�j
//�@ �@�E�P�̎�����\������ȂǑS�̓I�ȋ@�\��K�v�Ƃ���\�[�X
// �@�@�E��̒T���Ȃǈꕔ�̋@�\�݂̂�K�v�Ƃ���\�[�X
//

#pragma once

#include "TetrisOneGameState.h"

namespace TetrisFunction
{
/////////////////////////////////////////////////////////////////////////////
//
// �S��
//

void initialize(TetrisOneGameState& tetris);
bool countdown(ConstTetris::MatchState& matchState, int& countdown);

bool isInBoard(int x, int y);

/////////////////////////////////////////////////////////////////////////////
//
// �l�N�X�g�֘A
//

void initBag(ConstTetris::Bag& bag);
void circulateNext(ConstTetris::Next& next, ConstTetris::Bag& bag);


/////////////////////////////////////////////////////////////////////////////
//
// �J�����g�~�m�֘A
//

// �J�����g�o�����̏������W���Z�b�g����
// �~�m�^�C�v�͂��̂܂�
// �o�����邽�߂̃X�y�[�X���{�[�h�ɂȂ���� false ��Ԃ�
bool setCurrentStartPos(ConstTetris::Board& board, CurrentMinoState& current);

// �E�P�}�X�ړ�����
// �ł��Ȃ���Έړ����� false ��Ԃ�
bool moveRight(ConstTetris::Board& board, CurrentMinoState& current);

// ���P�}�X�ړ�����
// �ł��Ȃ���Έړ����� false ��Ԃ�
bool moveLeft(ConstTetris::Board& board, CurrentMinoState& current);

// ���P�}�X�ړ�����
// �ł��Ȃ���Έړ����� false ��Ԃ�
bool moveDown(ConstTetris::Board& board, CurrentMinoState& current);

// ���Ɉړ��ł���Ƃ���܂ňړ�����
// �ړ������}�X����Ԃ��i�ړ����ĂȂ��ꍇ��0�j
int moveDownEdge(ConstTetris::Board& board, CurrentMinoState& current);

// �E��]����
// ��]�ł��Ȃ���� 0�A�ł���� SRS �̃e�X�g�񐔂�Ԃ�
int rotateRight(ConstTetris::Board& board, CurrentMinoState& current);

// ����]����
// ��]�ł��Ȃ���� 0�A�ł���� SRS �̃e�X�g�񐔂�Ԃ�
int rotateLeft(ConstTetris::Board& board, CurrentMinoState& current);

// �{�[�h��̃u���b�N�ƃJ�����g�~�m������Ă��Ȃ�
// ���� �{�[�h����͂ݏo�Ă��Ȃ���� true ��Ԃ�
bool canPut(const ConstTetris::Board& board, const CurrentMinoState& current);

// �J�����g�~�m���{�[�h��̂��̏�ɒu��
// �u���b�N������Ă��Ă��u��
// �{�[�h����͂ݏo�Ă���ꍇ�� OnException
void put(ConstTetris::Board& board, CurrentMinoState& current);
}