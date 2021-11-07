// テトリスの１試合のとある瞬間の状態を表現する
// 試合前のカウントダウンやDASなどの操作入力も試合状態の１つとする
// 設置が確定していないカレントミノはボード上には置かないこと
// カウントダウンは [ConstTetris::MATCH_START_COUNTDOWN ～ 0] までの範囲とすること
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

