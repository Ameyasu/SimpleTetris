// テトリスを表現するのに必要な機能群
// 自身は状態を持たず、引数に渡された状態に対する操作のみを行う
// 
// 様々な箇所から呼び出されることを想定し、抽象的な機能のみを提供すること
// 　呼び出し元の例）
//　 　・１つの試合を表現するなど全体的な機能を必要とするソース
// 　　・手の探索など一部の機能のみを必要とするソース
//

#pragma once

#include "TetrisOneGameState.h"

namespace TetrisFunction
{
/////////////////////////////////////////////////////////////////////////////
//
// 全般
//

void initialize(TetrisOneGameState& tetris);
bool countdown(ConstTetris::MatchState& matchState, int& countdown);

bool isInBoard(int x, int y);

/////////////////////////////////////////////////////////////////////////////
//
// ネクスト関連
//

void initBag(ConstTetris::Bag& bag);
void circulateNext(ConstTetris::Next& next, ConstTetris::Bag& bag);


/////////////////////////////////////////////////////////////////////////////
//
// カレントミノ関連
//

// カレント出現時の初期座標をセットする
// ミノタイプはそのまま
// 出現するためのスペースがボードになければ false を返す
bool setCurrentStartPos(ConstTetris::Board& board, CurrentMinoState& current);

// 右１マス移動する
// できなければ移動せず false を返す
bool moveRight(ConstTetris::Board& board, CurrentMinoState& current);

// 左１マス移動する
// できなければ移動せず false を返す
bool moveLeft(ConstTetris::Board& board, CurrentMinoState& current);

// 下１マス移動する
// できなければ移動せず false を返す
bool moveDown(ConstTetris::Board& board, CurrentMinoState& current);

// 下に移動できるところまで移動する
// 移動したマス数を返す（移動してない場合は0）
int moveDownEdge(ConstTetris::Board& board, CurrentMinoState& current);

// 右回転する
// 回転できなければ 0、できれば SRS のテスト回数を返す
int rotateRight(ConstTetris::Board& board, CurrentMinoState& current);

// 左回転する
// 回転できなければ 0、できれば SRS のテスト回数を返す
int rotateLeft(ConstTetris::Board& board, CurrentMinoState& current);

// ボード上のブロックとカレントミノが被っていない
// かつ ボードからはみ出ていなければ true を返す
bool canPut(const ConstTetris::Board& board, const CurrentMinoState& current);

// カレントミノをボード上のその場に置く
// ブロックが被っていても置く
// ボードからはみ出ている場合は OnException
void put(ConstTetris::Board& board, CurrentMinoState& current);
}