// テトリスの試合状況の進行役クラス
// ゲームが成り立つように TetrisOneGameState を TetrisFunction で操作する
//

#pragma once

#include "TetrisOneGameState.h"

class TetrisOneGameOperator
{
public:
	// 初期状態から開始したい場合
	TetrisOneGameOperator();

	// 引数に渡したゲームの状態から始めたい場合
	TetrisOneGameOperator(const TetrisOneGameState& state);

public:
	// 試合状態を初期化
	void initialize();

	// １フレームに一度呼ぶことでゲームが進行する
	// 引数には ConstTetris::INPUT_*** をOR演算したものを渡す
	void update(int input);

public:
	const TetrisOneGameState& getGameState() const { return m_state; }

private:
	bool circulateNext();

private:
	TetrisOneGameState m_state;
};