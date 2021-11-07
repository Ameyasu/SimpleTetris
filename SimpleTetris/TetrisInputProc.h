// ������͊Ǘ��N���X
// ���͒������Ɣ����E���͂����u�Ԃ��������EDAS�Ȃǂ��v�Z���A
// �E�ړ����ׂ��t���[���E�n�[�h�h���b�v���ׂ��t���[���Ȃǂ𔻒f����
//

#pragma once

class TetrisInputProc
{
public:
	TetrisInputProc();

public:
	void initialize();

	// �P�t���[���Ɉ�x�Ă�
	void update(int input);

public:
	// �ȉ��̊֐��Q��true��Ԃ��Ƃ�
	// �Ăяo�����͊Y���̑�����s��

	bool moveRight() const;
	bool moveLeft() const;
	bool softDrop() const;
	bool hardDrop() const;
	bool rotateRight() const;
	bool rotateLeft() const;
	bool hold() const;

private:
	int m_moveRight;
	int m_moveLeft;
	int m_softDrop;
	int m_hardDrop;
	int m_rotateRight;
	int m_rotateLeft;
	int m_hold;
};