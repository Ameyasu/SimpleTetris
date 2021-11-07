// このプログラム作成の目的：
// 　　他人（１週間後の自分を含む）が見て分かるコードを書きたい
// 　　保守性の高いコードを書きたい
//

#include "DxLib.h"

#include "ConstScreenLayout.h"
#include "PaintTetris.h"
#include "TetrisOneGameOperator.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetMainWindowText("SimpleTetris");
	SetWindowSizeChangeEnableFlag(FALSE);
	SetAlwaysRunFlag(FALSE);
	SetGraphMode(ConstScreenLayout::CLIENT_X_SIZE, ConstScreenLayout::CLIENT_Y_SIZE, 16);
	//SetBackgroundColor(0xf4, 0xf5, 0xf7); // beautiful white
	SetBackgroundColor(0x15, 0x18, 0x1e); // beautiful black

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	SetFontSize(16);

	TetrisOneGameOperator tetrisOperator;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int input = 0;
		if (CheckHitKey(KEY_INPUT_RIGHT)) input |= ConstTetris::INPUT_MOVE_RIGHT;
		if (CheckHitKey(KEY_INPUT_LEFT)) input |= ConstTetris::INPUT_MOVE_LEFT;
		if (CheckHitKey(KEY_INPUT_DOWN)) input |= ConstTetris::INPUT_SOFT_DROP;
		if (CheckHitKey(KEY_INPUT_SPACE)) input |= ConstTetris::INPUT_HARD_DROP;
		if (CheckHitKey(KEY_INPUT_X)) input |= ConstTetris::INPUT_ROTATE_RIGHT;
		if (CheckHitKey(KEY_INPUT_Z)) input |= ConstTetris::INPUT_ROTATE_LEFT;
		if (CheckHitKey(KEY_INPUT_C)) input |= ConstTetris::INPUT_HOLD;

		tetrisOperator.update(input);

		PaintTetris::paintTetris(tetrisOperator.getGameState());

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}


// プログラムの全体像


/////////////////////////////////////////////////////////////////////////////
//
// コーディング規約
//
// ○名前付け
// 　変数　　　　：　appleOrenge
// 　メンバ変数　：　m_appleOrenge
// 　定数　　　　：　APPLE_OORENGE
// 　関数　　　　：　appleOrenge
// 　クラス　　　：　AppleOrange
// 　名前空間　　：　AppleOrenge
//
// ○使う機構
// 　状態のみを持つ　　：　struct
// 　状態と操作を持つ　：　class
// 　状態を持たない　　：　namespace
//
// ○enum classの持つ値と連動する配列などがある場合
// 　[連動] enumclass名
// 　というコメントを配列に付けて置く
// 　後からenum classを変更したときにコメントを検索して
// 　連動箇所も一緒に変更する
//


/////////////////////////////////////////////////////////////////////////////
//
// プログラム全般
//
// ■Main
// 　　メイン関数のみのソース
//
// ■ConstScreenLayout
// 　　画面上の各要素の大きさ・座標などの定数を定義する
//
// ■OnException <namespace>
// 　　○プログラムで意図しない値が引数に渡されたりなどしたときに
// 　　　プログラムを即終了させるための機能
// 　　○プログラム終了時に呼び出したい機能があればこの機能の中に追記する
//


/////////////////////////////////////////////////////////////////////////////
//
// テトリスの機能
//
// ■ConstTetris
// 　　ボードの大きさ、ミノの形などの定数のみを定義する
//
// ■TetrisOneGameOperator <class>
// 　　テトリスの試合状況の進行役クラス
// 　　↓使用するソース
// 　　　・TetrisOneGameState
// 　　　・TetrisFunction
//
// ■TetrisOneGameState <struct>
// 　　テトリスの試合状況を表す状態値群
//
// ■CurrentMinoState <struct>
// 　　カレントミノの状態値
//
// ■TetrisFunction <namespace>
// 　　テトリスの状態値を変化させる関数群
//
// ■PaintTetris <namespace>
// 　　テトリスの状態値を描画する関数群
//
// ■TetrisInputProc <class>
// 　　DASとか押した瞬間だけ反応とかを管理するクラス
//


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// おまけ：設計クイズ！
//
// ■レベル１
// 　Q1. ネクスト・ホールドの表示を大きくしたいです
// 　　　どこを変更すればいいでしょうか
//
// 　Q2. カレントミノ(操作ミノ)が自動で横移動するまでの長押しの時間を短くしたいです
// 　　　どこを変更すればいいでしょうか
//
// 　Q3. 右回転・左回転にも、横移動のようにDASを付けたいです
// 　　　どこを変更すればいいでしょうか
//
// ■レベル２
// 　Q1. このプログラムにはライン消し機能が付いていません
// 　　　ライン消し機能を付けるにはどこを変更すればいいでしょうか
//
// 　Q2. ミノの回転にSRSの機能を追加するにはどこを変更すればいいでしょうか
//
// ■レベル３
// 　Q1. プレイヤーがTSS・TSD・TSTをしたときに画面にその情報を描画するには
// 　　　どう変更すればいいでしょうか
//
// 　Q2. コンボ(REN)数のカウント・火力計算機能を追加するには
// 　　　どう変更すればいいでしょうか
//
// 　Q3. キーコンフィグ機能を付けるにはどう変更すればいいでしょうか
//
// ■レベル４
// 　Q1. 40ライン・ウルトラ・２人対戦の機能を新たに付けることになりました
// 　　　現在のフリープレイの機能は残したままこれらの機能を追加するには
// 　　　どう変更すればいいでしょうか
//
// 　Q2. フリープレイにリプレイ機能を付けることになりました
// 　　　どう変更すればいいでしょうか
//
// 　Q3. あなたはテトリスをプレイするコンピュータを作りました
// 　　　1P・2Pの操作者をそれぞれ人間かコンピュータかを切り替えたいです
// 　　　どう変更すればいいでしょうか
//
