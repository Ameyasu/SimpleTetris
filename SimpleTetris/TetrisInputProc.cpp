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
	// Še•Ï”‚ª“ü—Í’†‚Í˜A‘±“ü—ÍƒtƒŒ[ƒ€”
	// ”ñ“ü—Í’†‚Í 0 ‚É‚È‚é‚æ‚¤‚ÉŒvZ

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
	// “ü—Í‚ÌuŠÔ‚ÆDAS‚É”½‰
	return (m_moveRight == 1) || (m_moveRight >= ConstTetris::DAS);
}

bool TetrisInputProc::moveLeft() const
{
	// “ü—Í‚ÌuŠÔ‚ÆDAS‚É”½‰
	return (m_moveLeft == 1) || (m_moveLeft >= ConstTetris::DAS);
}

bool TetrisInputProc::softDrop() const
{
	// “ü—Í‚ÌuŠÔ‚©‚ç‚PƒtƒŒ[ƒ€‚¨‚«‚É”½‰
	return m_softDrop & 1;
}

bool TetrisInputProc::hardDrop() const
{
	// “ü—Í‚ÌuŠÔ‚Ì‚İ”½‰
	return m_hardDrop == 1;
}

bool TetrisInputProc::rotateRight() const
{
	// “ü—Í‚ÌuŠÔ‚Ì‚İ”½‰
	return m_rotateRight == 1;
}

bool TetrisInputProc::rotateLeft() const
{
	// “ü—Í‚ÌuŠÔ‚Ì‚İ”½‰
	return m_rotateLeft == 1;
}

bool TetrisInputProc::hold() const
{
	// “ü—Í‚ÌuŠÔ‚Ì‚İ”½‰
	return m_hold == 1;
}
