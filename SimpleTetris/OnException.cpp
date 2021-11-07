#include "OnException.h"

#include "DxLib.h"

namespace OnException
{

void TerminateProgram(const char* functionName, int line, int param1, int param2)
{
	/////////////////////////////////////////////////////////////////////////////
	//
	// 異常検知メッセージ表示
	//

	TCHAR buf[256];
	_stprintf_s(buf, TEXT("異常を検知しました\n\n関数：%s\n行数：%d\nパラメータ１：%d\nパラメータ２：%d\n\nプログラムを終了します"), functionName, line, param1, param2);
	MessageBox(nullptr, buf, TEXT("例外"), MB_OK);


	/////////////////////////////////////////////////////////////////////////////
	//
	// 終了処理
	//

	// 追加したい終了処理はここに挿入

	DxLib_End();
	

	/////////////////////////////////////////////////////////////////////////////
	//
	// プログラム終了
	//

	exit(0);
}

}