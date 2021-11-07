// 操作入力管理クラス
// 入力中ずっと反応・入力した瞬間だけ反応・DASなどを計算し、
// 右移動すべきフレーム・ハードドロップすべきフレームなどを判断する
//

#pragma once

class TetrisInputProc
{
public:
	TetrisInputProc();

public:
	void initialize();

	// １フレームに一度呼ぶ
	void update(int input);

public:
	// 以下の関数群がtrueを返すとき
	// 呼び出し元は該当の操作を行う

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