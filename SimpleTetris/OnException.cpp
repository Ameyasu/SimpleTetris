#include "OnException.h"

#include "DxLib.h"

namespace OnException
{

void TerminateProgram(const char* functionName, int line, int param1, int param2)
{
	/////////////////////////////////////////////////////////////////////////////
	//
	// �ُ팟�m���b�Z�[�W�\��
	//

	TCHAR buf[256];
	_stprintf_s(buf, TEXT("�ُ�����m���܂���\n\n�֐��F%s\n�s���F%d\n�p�����[�^�P�F%d\n�p�����[�^�Q�F%d\n\n�v���O�������I�����܂�"), functionName, line, param1, param2);
	MessageBox(nullptr, buf, TEXT("��O"), MB_OK);


	/////////////////////////////////////////////////////////////////////////////
	//
	// �I������
	//

	// �ǉ��������I�������͂����ɑ}��

	DxLib_End();
	

	/////////////////////////////////////////////////////////////////////////////
	//
	// �v���O�����I��
	//

	exit(0);
}

}