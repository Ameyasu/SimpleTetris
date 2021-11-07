#include "TetrisOneGameOperator.h"
#include "TetrisFunction.h"

TetrisOneGameOperator::TetrisOneGameOperator()
{
	initialize();
}

TetrisOneGameOperator::TetrisOneGameOperator(const TetrisOneGameState& state)
	: m_state(state)
{
}

void TetrisOneGameOperator::initialize()
{
	TetrisFunction::initialize(m_state);
}

void TetrisOneGameOperator::update(int input)
{
	// �����̏��s�����܂��Ă����牽�����Ȃ�
	if (m_state.matchState == ConstTetris::MatchState::WIN || m_state.matchState == ConstTetris::MatchState::LOSE)
		return;

	// ������͂̕Ȃ̕�������������i���͒������Ɣ����E���͂����u�Ԃ��������EDAS�Ȃǁj
	// �J�E���g�_�E�������O�ɌĂяo�����ƂŃJ�E���g�_�E�����ɂ�DAS������
	m_state.inputProc.update(input);

	// �J�E���g�_�E�����̓J�E���g�_�E��������������return
	if (m_state.matchState == ConstTetris::MatchState::COUNTDOWN)
	{
		if (TetrisFunction::countdown(m_state.matchState, m_state.countdown))
		{
			if (!circulateNext())
				return;
		}
		return;
	}

	// �ȉ��������̓�����L�q

	if (m_state.inputProc.moveRight())
		TetrisFunction::moveRight(m_state.board, m_state.current);

	if (m_state.inputProc.moveLeft())
		TetrisFunction::moveLeft(m_state.board, m_state.current);

	if (m_state.inputProc.softDrop())
		TetrisFunction::moveDown(m_state.board, m_state.current);

	if (m_state.inputProc.rotateRight())
		TetrisFunction::rotateRight(m_state.board, m_state.current);

	if (m_state.inputProc.rotateLeft())
		TetrisFunction::rotateLeft(m_state.board, m_state.current);

	if (m_state.inputProc.hardDrop())
	{
		// �J�����g����ԉ��܂ňړ�
		TetrisFunction::moveDownEdge(m_state.board, m_state.current);

		// �J�����g��Ֆʂɐݒu
		TetrisFunction::put(m_state.board, m_state.current);

		// �l�N�X�g�z��
		// �J�����g���o�����s�����瑦return
		if (!circulateNext())
			return;

		// �z�[���h���܂��ł���悤�ɂ���
		m_state.canHold = true;
	}

	if (m_state.inputProc.hold())
	{
		if (m_state.canHold)
		{
			// �J�����g�̃~�m�^�C�v�ƃz�[���h�̃~�m�^�C�v�����ւ�
			ConstTetris::MinoType t = m_state.current.type;
			m_state.current.type = m_state.holdMinoType;
			m_state.holdMinoType = t;

			// �J�����g�̃~�m�^�C�v���󂾂�����l�N�X�g�z��
			if (m_state.current.type == ConstTetris::MinoType::EMPTY)
			{
				if (!circulateNext())
					return;
			}

			// �z�[���h���ł��Ȃ�����
			m_state.canHold = false;
		}
	}
}

bool TetrisOneGameOperator::circulateNext()
{
	// �l�N�X�g�̐擪����J�����g�Ƀ~�m�^�C�v���R�s�[
	m_state.current.type = m_state.next[0];

	// �l�N�X�g�z��
	TetrisFunction::circulateNext(m_state.next, m_state.bag);

	// �J�����g���o���ʒu�Ɉړ�
	// ����������true
	if (TetrisFunction::setCurrentStartPos(m_state.board, m_state.current))
		return true;

	// �J�����g���o���ł��Ȃ���Ύ�����Ԃ𕉂��ɂ���
	m_state.matchState = ConstTetris::MatchState::LOSE;
	return false;
}
