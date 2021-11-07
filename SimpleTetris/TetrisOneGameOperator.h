// �e�g���X�̎����󋵂̐i�s���N���X
// �Q�[�������藧�悤�� TetrisOneGameState �� TetrisFunction �ő��삷��
//

#pragma once

#include "TetrisOneGameState.h"

class TetrisOneGameOperator
{
public:
	// ������Ԃ���J�n�������ꍇ
	TetrisOneGameOperator();

	// �����ɓn�����Q�[���̏�Ԃ���n�߂����ꍇ
	TetrisOneGameOperator(const TetrisOneGameState& state);

public:
	// ������Ԃ�������
	void initialize();

	// �P�t���[���Ɉ�x�ĂԂ��ƂŃQ�[�����i�s����
	// �����ɂ� ConstTetris::INPUT_*** ��OR���Z�������̂�n��
	void update(int input);

public:
	const TetrisOneGameState& getGameState() const { return m_state; }

private:
	bool circulateNext();

private:
	TetrisOneGameState m_state;
};