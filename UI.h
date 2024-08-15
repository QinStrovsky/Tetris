#pragma once
#include "Block.h"
#include "Define.h"

class CUI
{
public:
	CUI();
	void DrawBoard();
	void BoardInit();
	void ShowInfo();
	void DrawBlock();
	void KeyFetch(char s);
	void SetDropBool(bool);
	void EdgeJudg();
	void RevoleJudg();
	bool IsBottom();
	void BlockLandProc();
	void BlockClear();
	bool IsGameOver();
private:
	void DownEdgeJudg(int x, int y, int m_x, int m_y);
	void LeftRightJudg(int x, int y, int m_x, int m_y);
	void DrawCurrentBlock(int m_x,int m_y);
	void DrawNextBlock();
private:
	BoardAttr boardCell[17][22];
	Block currentBlock;
	Block nextBlock;
	bool drawDrop = false;
};

