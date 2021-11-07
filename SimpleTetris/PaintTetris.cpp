#include "PaintTetris.h"

namespace PaintTetris
{

void paintTetris(const TetrisOneGameState& tetris)
{
	/////////////////////////////////////////////////////////////////////////////
	//
	// �{�[�h�̕`��
	//

	// ���݂̕`��͈͂�ۑ�
	RECT r;
	GetDrawArea(&r);

	// 21�i�ڂ͏������������Ȃ��Ƃ����`������邽�߂�
	// �`��͈͂�ύX����
	SetDrawArea(
		ConstScreenLayout::BOARD_FRAME_X,
		ConstScreenLayout::BOARD_FRAME_Y,
		ConstScreenLayout::BOARD_FRAME_X + ConstScreenLayout::BOARD_FRAME_X_SIZE,
		ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE
	);

	// �Z���̕`��
	for (int y = 0; y < ConstTetris::BOARD_VISIBLE_Y_SIZE; ++y)
		for (int x = 0; x < ConstTetris::BOARD_X_SIZE; ++x)
			paintBoardFrameCell(x, y, tetris.board[y][x]);

	// �g�̕`��
	paintBaordFrame();


	/////////////////////////////////////////////////////////////////////////////
	//
	// �J�����g�̕`��
	//

	if (tetris.current.type != ConstTetris::MinoType::EMPTY)
	{
		const auto& currentMinoShape = ConstTetris::getMinoShape(tetris.current.type, tetris.current.dir);

		for (int i = 0; i < ConstTetris::MINO_SHAPE_POS_NUM; i += 2)
			paintBoardFrameCell(tetris.current.x + currentMinoShape[i], tetris.current.y + currentMinoShape[i + 1], tetris.current.type);
	}

	// �`��͈͂����ɖ߂�
	SetDrawArea(r.left, r.top, r.right, r.bottom);


	/////////////////////////////////////////////////////////////////////////////
	//
	// �z�[���h�̕`��
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

	// �g�̕`��
	paintHoldFrame();

	if (!tetris.canHold)
		paintCannotHold();


	/////////////////////////////////////////////////////////////////////////////
	//
	// �l�N�X�g�̕`��
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

		// �g�̕`��
		paintNextFrame(index);
	}


	/////////////////////////////////////////////////////////////////////////////
	//
	// �J�E���g�_�E���̕`��
	//

	if (tetris.matchState == ConstTetris::MatchState::COUNTDOWN)
	{
		// ���݂̃t�H���g�T�C�Y��ۑ�
		int fontSize = GetFontSize();

		// �t�H���g�T�C�Y�ύX
		SetFontSize(128);
		
		// �J�E���g�_�E�����Ԃ𕶎���ɕϊ�
		TCHAR buf[16];
		_stprintf_s(buf, "%d", tetris.countdown / 60 + 1); // �b�ɕϊ�

		// �e�̕`��
		DrawString(
			(ConstScreenLayout::BOARD_FRAME_X + ConstScreenLayout::BOARD_FRAME_X_SIZE) / 2 + 12,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3 + 12,
			buf,
			0U
		);

		// �����̕`��
		DrawString(
			(ConstScreenLayout::BOARD_FRAME_X + ConstScreenLayout::BOARD_FRAME_X_SIZE) / 2,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3,
			buf,
			0x22AAFF
		);

		// �t�H���g�T�C�Y�����ɖ߂�
		SetFontSize(fontSize);
	}


	/////////////////////////////////////////////////////////////////////////////
	//
	// �Q�[���I���̕`��
	//

	if (tetris.matchState == ConstTetris::MatchState::WIN || tetris.matchState == ConstTetris::MatchState::LOSE)
	{
		// ���݂̃t�H���g�T�C�Y��ۑ�
		int fontSize = GetFontSize();

		// �t�H���g�T�C�Y�ύX
		SetFontSize(96);

		TCHAR buf[16];

		// �\�����镶����𐶐�
		if (tetris.matchState == ConstTetris::MatchState::WIN)
			_stprintf_s(buf, "������I");
		else
			_stprintf_s(buf, "����˂�");

		// �e�̕`��
		DrawString(
			ConstScreenLayout::BOARD_FRAME_X - 36 + 10,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3 + 10,
			buf,
			0U
		);

		// �����̕`��
		DrawString(
			ConstScreenLayout::BOARD_FRAME_X - 36,
			(ConstScreenLayout::BOARD_FRAME_Y + ConstScreenLayout::BOARD_FRAME_Y_SIZE) / 3,
			buf,
			0x22BBFF
		);

		// �t�H���g�T�C�Y�����ɖ߂�
		SetFontSize(fontSize);
	}
}

}