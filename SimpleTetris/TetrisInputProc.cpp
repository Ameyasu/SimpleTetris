#include "TetrisInputProc.h"
#include "ConstTetris.h"

TetrisInputProc::TetrisInputProc()
	: m_moveRight()
	, m_moveLeft()
	, m_softDrop()
	, m_hardDrop()
	, m_rotateRight()
	, m_rotateLeft()
	, m_hold()

{
}

void TetrisInputProc::initialize()
{
	m_moveRight = 0;
	m_moveLeft = 0;
	m_softDrop = 0;
	m_hardDrop = 0;
	m_rotateRight = 0;
	m_rotateLeft = 0;
	m_hold = 0;
}

void TetrisInputProc::update(int input)
{
	// �e�ϐ������͒��͘A�����̓t���[����
	// ����͒��� 0 �ɂȂ�悤�Ɍv�Z

	if (input & ConstTetris::INPUT_MOVE_RIGHT)
		++m_moveRight;
	else
		m_moveRight = 0;

	if (input & ConstTetris::INPUT_MOVE_LEFT)
		++m_moveLeft;
	else
		m_moveLeft = 0;

	if (input & ConstTetris::INPUT_SOFT_DROP)
		++m_softDrop;
	else
		m_softDrop = 0;

	if (input & ConstTetris::INPUT_HARD_DROP)
		++m_hardDrop;
	else
		m_hardDrop = 0;

	if (input & ConstTetris::INPUT_ROTATE_RIGHT)
		++m_rotateRight;
	else
		m_rotateRight = 0;

	if (input & ConstTetris::INPUT_ROTATE_LEFT)
		++m_rotateLeft;
	else
		m_rotateLeft = 0;

	if (input & ConstTetris::INPUT_HOLD)
		++m_hold;
	else
		m_hold = 0;
}

bool TetrisInputProc::moveRight() const
{
	// ���͂̏u�Ԃ�DAS�ɔ���
	return (m_moveRight == 1) || (m_moveRight >= ConstTetris::DAS);
}

bool TetrisInputProc::moveLeft() const
{
	// ���͂̏u�Ԃ�DAS�ɔ���
	return (m_moveLeft == 1) || (m_moveLeft >= ConstTetris::DAS);
}

bool TetrisInputProc::softDrop() const
{
	// ���͂̏u�Ԃ���P�t���[�������ɔ���
	return m_softDrop & 1;
}

bool TetrisInputProc::hardDrop() const
{
	// ���͂̏u�Ԃ̂ݔ���
	return m_hardDrop == 1;
}

bool TetrisInputProc::rotateRight() const
{
	// ���͂̏u�Ԃ̂ݔ���
	return m_rotateRight == 1;
}

bool TetrisInputProc::rotateLeft() const
{
	// ���͂̏u�Ԃ̂ݔ���
	return m_rotateLeft == 1;
}

bool TetrisInputProc::hold() const
{
	// ���͂̏u�Ԃ̂ݔ���
	return m_hold == 1;
}
