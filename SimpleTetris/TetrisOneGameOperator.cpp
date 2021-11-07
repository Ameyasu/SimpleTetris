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
	// 試合の勝敗が決まっていたら何もしない
	if (m_state.matchState == ConstTetris::MatchState::WIN || m_state.matchState == ConstTetris::MatchState::LOSE)
		return;

	// 操作入力の癖の部分を処理する（入力中ずっと反応・入力した瞬間だけ反応・DASなど）
	// カウントダウン処理前に呼び出すことでカウントダウン中にもDASが働く
	m_state.inputProc.update(input);

	// カウントダウン中はカウントダウン処理だけしてreturn
	if (m_state.matchState == ConstTetris::MatchState::COUNTDOWN)
	{
		if (TetrisFunction::countdown(m_state.matchState, m_state.countdown))
		{
			if (!circulateNext())
				return;
		}
		return;
	}

	// 以下試合中の動作を記述

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
		// カレントを一番下まで移動
		TetrisFunction::moveDownEdge(m_state.board, m_state.current);

		// カレントを盤面に設置
		TetrisFunction::put(m_state.board, m_state.current);

		// ネクスト循環
		// カレントが出現失敗したら即return
		if (!circulateNext())
			return;

		// ホールドをまたできるようにする
		m_state.canHold = true;
	}

	if (m_state.inputProc.hold())
	{
		if (m_state.canHold)
		{
			// カレントのミノタイプとホールドのミノタイプを入れ替え
			ConstTetris::MinoType t = m_state.current.type;
			m_state.current.type = m_state.holdMinoType;
			m_state.holdMinoType = t;

			// カレントのミノタイプが空だったらネクスト循環
			if (m_state.current.type == ConstTetris::MinoType::EMPTY)
			{
				if (!circulateNext())
					return;
			}

			// ホールドをできなくする
			m_state.canHold = false;
		}
	}
}

bool TetrisOneGameOperator::circulateNext()
{
	// ネクストの先頭からカレントにミノタイプをコピー
	m_state.current.type = m_state.next[0];

	// ネクスト循環
	TetrisFunction::circulateNext(m_state.next, m_state.bag);

	// カレントを出現位置に移動
	// 成功したらtrue
	if (TetrisFunction::setCurrentStartPos(m_state.board, m_state.current))
		return true;

	// カレントが出現できなければ試合状態を負けにする
	m_state.matchState = ConstTetris::MatchState::LOSE;
	return false;
}
