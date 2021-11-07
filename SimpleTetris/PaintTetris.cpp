#include "PaintTetris.h"

namespace PaintTetris
{

void paintTetris(const TetrisOneGameState& tetris)
{
	/////////////////////////////////////////////////////////////////////////////
	//
	// ボードの描画
	//

	// 現在の描画範囲を保存
	RECT r;
	GetDrawArea(&r);

	// 21段目は少ししか見えないという描画をするために
	// 描画範囲を変更する
	SetDrawArea(
		ConstScreenLayout::BOARD_FRAME_X,
		ConstScreenLayout::BOARD_FRAME_Y,
		ConstScreenLayout::BOARD_FRAME_X + ConstScreenLayout::BOARD_FRAME_X_SIZE,
		ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE
	);

	// セルの描画
	for (int y = 0; y < ConstTetris::BOARD_VISIBLE_Y_SIZE; ++y)
		for (int x = 0; x < ConstTetris::BOARD_X_SIZE; ++x)
			paintBoardFrameCell(x, y, tetris.board[y][x]);

	// 枠の描画
	paintBaordFrame();


	/////////////////////////////////////////////////////////////////////////////
	//
	// カレントの描画
	//

	if (tetris.current.type != ConstTetris::MinoType::EMPTY)
	{
		const auto& currentMinoShape = ConstTetris::getMinoShape(tetris.current.type, tetris.current.dir);

		for (int i = 0; i < ConstTetris::MINO_SHAPE_POS_NUM; i += 2)
			paintBoardFrameCell(tetris.current.x + currentMinoShape[i], tetris.current.y + currentMinoShape[i + 1], tetris.current.type);
	}

	// 描画範囲を元に戻す
	SetDrawArea(r.left, r.top, r.right, r.bottom);


	/////////////////////////////////////////////////////////////////////////////
	//
	// ホールドの描画
	//

	for (int y = 0; y < ConstScreenLayout::MINO_FRAME_Y_CELL_NUM; ++y)
		for (int x = 0; x < ConstScreenLayout::MINO_FRAME_X_CELL_NUM; ++x)
			paintHoldFrameCell(x, y, ConstTetris::MinoType::EMPTY);

	if (tetris.holdMinoType != ConstTetris::MinoType::EMPTY)
	{
		const auto& holdMinoShape = ConstTetris::getMinoShape(tetris.holdMinoType, ConstTetris::MinoDir::UP);

		for (int i = 0; i < ConstTetris::MINO_SHAPE_POS_NUM; i += 2)
			paintHoldFrameCell(holdMinoShape[i], holdMinoShape[i + 1], tetris.holdMinoType);
	}

	// 枠の描画
	paintHoldFrame();

	if (!tetris.canHold)
		paintCannotHold();


	/////////////////////////////////////////////////////////////////////////////
	//
	// ネクストの描画
	//

	for (int index = 0; index < ConstTetris::NEXT_NUM; ++index)
	{
		for (int y = 0; y < ConstScreenLayout::MINO_FRAME_Y_CELL_NUM; ++y)
			for (int x = 0; x < ConstScreenLayout::MINO_FRAME_X_CELL_NUM; ++x)
				paintNextFrameCell(index, x, y, ConstTetris::MinoType::EMPTY);

		auto nextMinoType = tetris.next[index];
		if (nextMinoType != ConstTetris::MinoType::EMPTY)
		{
			const auto& nextMinoShape = ConstTetris::getMinoShape(nextMinoType, ConstTetris::MinoDir::UP);

			for (int i = 0; i < ConstTetris::MINO_SHAPE_POS_NUM; i += 2)
				paintNextFrameCell(index, nextMinoShape[i], nextMinoShape[i + 1], nextMinoType);
		}

		// 枠の描画
		paintNextFrame(index);
	}


	/////////////////////////////////////////////////////////////////////////////
	//
	// カウントダウンの描画
	//

	if (tetris.matchState == ConstTetris::MatchState::COUNTDOWN)
	{
		// 現在のフォントサイズを保存
		int fontSize = GetFontSize();

		// フォントサイズ変更
		SetFontSize(128);
		
		// カウントダウン時間を文字列に変換
		TCHAR buf[16];
		_stprintf_s(buf, "%d", tetris.countdown / 60 + 1); // 秒に変換

		// 影の描画
		DrawString(
			(ConstScreenLayout::BOARD_FRAME_X + ConstScreenLayout::BOARD_FRAME_X_SIZE) / 2 + 12,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3 + 12,
			buf,
			0U
		);

		// 文字の描画
		DrawString(
			(ConstScreenLayout::BOARD_FRAME_X + ConstScreenLayout::BOARD_FRAME_X_SIZE) / 2,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3,
			buf,
			0x22AAFF
		);

		// フォントサイズを元に戻す
		SetFontSize(fontSize);
	}


	/////////////////////////////////////////////////////////////////////////////
	//
	// ゲーム終了の描画
	//

	if (tetris.matchState == ConstTetris::MatchState::WIN || tetris.matchState == ConstTetris::MatchState::LOSE)
	{
		// 現在のフォントサイズを保存
		int fontSize = GetFontSize();

		// フォントサイズ変更
		SetFontSize(96);

		TCHAR buf[16];

		// 表示する文字列を生成
		if (tetris.matchState == ConstTetris::MatchState::WIN)
			_stprintf_s(buf, "やった！");
		else
			_stprintf_s(buf, "ざんねん");

		// 影の描画
		DrawString(
			ConstScreenLayout::BOARD_FRAME_X - 36 + 10,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3 + 10,
			buf,
			0U
		);

		// 文字の描画
		DrawString(
			ConstScreenLayout::BOARD_FRAME_X - 36,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3,
			buf,
			0x22BBFF
		);

		// フォントサイズを元に戻す
		SetFontSize(fontSize);
	}
}

}