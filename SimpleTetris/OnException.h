#pragma once

namespace OnException
{

// �v���O�����ňӐ}���Ȃ��l�������ɓn���ꂽ��Ȃǂ����Ƃ��Ƀv���O�����𑦏I��������
// �g�����F
//	OnException::TerminateProgram(__FUNCTION__, __LINE__, <����Έُ�Ȓl>, <����Έُ�Ȓl>);
void TerminateProgram(const char* functionName, int line, int param1 = 0, int param2 = 0);

}