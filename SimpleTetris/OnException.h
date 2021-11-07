#pragma once

namespace OnException
{

// プログラムで意図しない値が引数に渡されたりなどしたときにプログラムを即終了させる
// 使い方：
//	OnException::TerminateProgram(__FUNCTION__, __LINE__, <あれば異常な値>, <あれば異常な値>);
void TerminateProgram(const char* functionName, int line, int param1 = 0, int param2 = 0);

}