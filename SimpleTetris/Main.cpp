// ���̃v���O�����쐬�̖ړI�F
// �@�@���l�i�P�T�Ԍ�̎������܂ށj�����ĕ�����R�[�h����������
// �@�@�ێ琫�̍����R�[�h����������
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


// �v���O�����̑S�̑�


/////////////////////////////////////////////////////////////////////////////
//
// �R�[�f�B���O�K��
//
// �����O�t��
// �@�ϐ��@�@�@�@�F�@appleOrenge
// �@�����o�ϐ��@�F�@m_appleOrenge
// �@�萔�@�@�@�@�F�@APPLE_OORENGE
// �@�֐��@�@�@�@�F�@appleOrenge
// �@�N���X�@�@�@�F�@AppleOrange
// �@���O��ԁ@�@�F�@AppleOrenge
//
// ���g���@�\
// �@��Ԃ݂̂����@�@�F�@struct
// �@��ԂƑ�������@�F�@class
// �@��Ԃ������Ȃ��@�@�F�@namespace
//
// ��enum class�̎��l�ƘA������z��Ȃǂ�����ꍇ
// �@[�A��] enumclass��
// �@�Ƃ����R�����g��z��ɕt���Ēu��
// �@�ォ��enum class��ύX�����Ƃ��ɃR�����g����������
// �@�A���ӏ����ꏏ�ɕύX����
//


/////////////////////////////////////////////////////////////////////////////
//
// �v���O�����S��
//
// ��Main
// �@�@���C���֐��݂̂̃\�[�X
//
// ��ConstScreenLayout
// �@�@��ʏ�̊e�v�f�̑傫���E���W�Ȃǂ̒萔���`����
//
// ��OnException <namespace>
// �@�@���v���O�����ňӐ}���Ȃ��l�������ɓn���ꂽ��Ȃǂ����Ƃ���
// �@�@�@�v���O�����𑦏I�������邽�߂̋@�\
// �@�@���v���O�����I�����ɌĂяo�������@�\������΂��̋@�\�̒��ɒǋL����
//


/////////////////////////////////////////////////////////////////////////////
//
// �e�g���X�̋@�\
//
// ��ConstTetris
// �@�@�{�[�h�̑傫���A�~�m�̌`�Ȃǂ̒萔�݂̂��`����
//
// ��TetrisOneGameOperator <class>
// �@�@�e�g���X�̎����󋵂̐i�s���N���X
// �@�@���g�p����\�[�X
// �@�@�@�ETetrisOneGameState
// �@�@�@�ETetrisFunction
//
// ��TetrisOneGameState <struct>
// �@�@�e�g���X�̎����󋵂�\����Ԓl�Q
//
// ��CurrentMinoState <struct>
// �@�@�J�����g�~�m�̏�Ԓl
//
// ��TetrisFunction <namespace>
// �@�@�e�g���X�̏�Ԓl��ω�������֐��Q
//
// ��PaintTetris <namespace>
// �@�@�e�g���X�̏�Ԓl��`�悷��֐��Q
//
// ��TetrisInputProc <class>
// �@�@DAS�Ƃ��������u�Ԃ��������Ƃ����Ǘ�����N���X
//


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// ���܂��F�݌v�N�C�Y�I
//
// �����x���P
// �@Q1. �l�N�X�g�E�z�[���h�̕\����傫���������ł�
// �@�@�@�ǂ���ύX����΂����ł��傤��
//
// �@Q2. �J�����g�~�m(����~�m)�������ŉ��ړ�����܂ł̒������̎��Ԃ�Z���������ł�
// �@�@�@�ǂ���ύX����΂����ł��傤��
//
// �@Q3. �E��]�E����]�ɂ��A���ړ��̂悤��DAS��t�������ł�
// �@�@�@�ǂ���ύX����΂����ł��傤��
//
// �����x���Q
// �@Q1. ���̃v���O�����ɂ̓��C�������@�\���t���Ă��܂���
// �@�@�@���C�������@�\��t����ɂ͂ǂ���ύX����΂����ł��傤��
//
// �@Q2. �~�m�̉�]��SRS�̋@�\��ǉ�����ɂ͂ǂ���ύX����΂����ł��傤��
//
// �����x���R
// �@Q1. �v���C���[��TSS�ETSD�ETST�������Ƃ��ɉ�ʂɂ��̏���`�悷��ɂ�
// �@�@�@�ǂ��ύX����΂����ł��傤��
//
// �@Q2. �R���{(REN)���̃J�E���g�E�Η͌v�Z�@�\��ǉ�����ɂ�
// �@�@�@�ǂ��ύX����΂����ł��傤��
//
// �@Q3. �L�[�R���t�B�O�@�\��t����ɂ͂ǂ��ύX����΂����ł��傤��
//
// �����x���S
// �@Q1. 40���C���E�E���g���E�Q�l�ΐ�̋@�\��V���ɕt���邱�ƂɂȂ�܂���
// �@�@�@���݂̃t���[�v���C�̋@�\�͎c�����܂܂����̋@�\��ǉ�����ɂ�
// �@�@�@�ǂ��ύX����΂����ł��傤��
//
// �@Q2. �t���[�v���C�Ƀ��v���C�@�\��t���邱�ƂɂȂ�܂���
// �@�@�@�ǂ��ύX����΂����ł��傤��
//
// �@Q3. ���Ȃ��̓e�g���X���v���C����R���s���[�^�����܂���
// �@�@�@1P�E2P�̑���҂����ꂼ��l�Ԃ��R���s���[�^����؂�ւ������ł�
// �@�@�@�ǂ��ύX����΂����ł��傤��
//
