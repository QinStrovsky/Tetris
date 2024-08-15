#include "UI.h"
#include "Define.h"

CUI::CUI()
{
	SYSTEMTIME current_time;
	GetLocalTime(&current_time);
	srand(current_time.wMilliseconds);
	int currentblocktype = (rand() % 7 - 0) + 0;
	int nextblocktype = (rand() % 7 - 0) + 0;
	int currentblockdire = (rand() % 4 - 0) + 0;
	int nextblockdire = (rand() % 4 - 0) + 0;
	int currentcolor = (rand() % 8) + 9;
	int nextcolor = (rand() % 8) + 9;
	currentBlock = Block(currentblocktype, currentblockdire,currentcolor);
	nextBlock = Block(nextblocktype, nextblockdire,nextcolor);
	for (int i{ 0 }; i < 17; i++) {
		for (int j{ 0 }; j < 22; j++) {
			boardCell[i][j].boardType = false;	//表示边缘
			boardCell[i][j].x_offset = 9;
			boardCell[i][j].y_offset = 0;
		}
	}
}

void CUI::DrawBoard()
{
	int i, j;
	for (i = 1; i < 16; i++)
		for (j = 1; j < 21; j++)
			PrintCell(boardCell[i][j].cell, i+boardCell[i][j].x_offset, j+boardCell[i][j].y_offset);
	GotoXY(10, 1);
	Cell nextCell;
	nextCell.type = false;
	nextCell.color = Gray;
	for (int k{ 0 }; k < 5; k++) {
		for (int z{ 0 }; z < 5; z++) {
			PrintCell(nextCell, k + 27, z + 5);
		}
	}
}

void CUI::BoardInit()
{
	for (int i{1}; i < 16; i++) {
		for (int j{1}; j < 21; j++) {
			boardCell[i][j].cell.color = Gray;
			boardCell[i][j].cell.type = false;
			boardCell[i][j].boardType = true;
		}							
	}
}

void CUI::ShowInfo()
{
	PrintString("当前得分：", 1, 8);
	PrintInt(50, 6, 8);
	PrintString("俄罗斯方块1.0", 27, 13);
	PrintString("作者：Mo", 27, 14);
	PrintString("邮箱：", 27, 15);
	PrintString("该版本原作者：", 27, 16);
}

void CUI::DrawBlock()
{
	int m_x = currentBlock.GetBlockX();
	int m_y = currentBlock.GetBlockY();
	EdgeJudg();
	DrawCurrentBlock(m_x, m_y);
	DrawNextBlock();
}

void CUI::KeyFetch(char s)
{
	switch (s) {
	case 'A':
		currentBlock.BlockCtrl(left);
		break;
	case 'D':
		currentBlock.BlockCtrl(right);
		break;
	case 'S':
		currentBlock.BlockCtrl(down);
		break;
	case 'W':
		RevoleJudg();
		currentBlock.BlockCtrl(up);
		break;
	default:
		break;
	}
}

void CUI::SetDropBool(bool value)
{
	drawDrop = value;
	if (drawDrop == true) {
		currentBlock.BlockDrop();
		drawDrop = false;
	}
}

void CUI::EdgeJudg()
{
	int m_x = currentBlock.GetBlockX();
	int m_y = currentBlock.GetBlockY();
	int x = currentBlock.GetBlockType();
	int y = currentBlock.GetBlockDire();
	DownEdgeJudg(x, y, m_x, m_y);
	LeftRightJudg(x, y, m_x, m_y);
}

void CUI::RevoleJudg()
{
	int x = currentBlock.GetBlockType();
	int y = currentBlock.GetBlockDire();
	int m_x = currentBlock.GetBlockX();
	int m_y = currentBlock.GetBlockY();
	int dire = (y + 1) % 4;
	for (int i{ 0 }; i < 4; i++) {
		if (boardCell[BlockTypeTran[x][dire][i][0] + 7 + m_x][BlockTypeTran[x][dire][i][1] + 1 + m_y].cell.type == true)
			currentBlock.SetRevoleBool(false);
	}
	currentBlock.SetRevoleBool(true);
}

bool CUI::IsBottom()
{
	return currentBlock.GetDownBool();
}

void CUI::BlockLandProc()
{
	Cell cell;
	cell.type = true;
	cell.color = currentBlock.GetBlockColor();
	int x = currentBlock.GetBlockType();
	int y = currentBlock.GetBlockDire();
	int m_x = currentBlock.GetBlockX();
	int m_y = currentBlock.GetBlockY();
	for (int i{ 0 }; i < 4; i++) {
		boardCell[BlockTypeTran[x][y][i][0] + 7 + m_x][BlockTypeTran[x][y][i][1] + 1 + m_y].cell.type = true;
		boardCell[BlockTypeTran[x][y][i][0] + 7 + m_x][BlockTypeTran[x][y][i][1] + 1 + m_y].cell.color = currentBlock.GetBlockColor();
	}
	currentBlock = nextBlock;

	SYSTEMTIME current_time;
	GetLocalTime(&current_time);
	srand(current_time.wMilliseconds);
	int nextblocktype = rand() % 7;
	int nextblockdire = rand() % 4;
	int nextcolor = (rand() % 8) + 9;
	nextBlock = Block(nextblocktype, nextblockdire, nextcolor);
}

void CUI::BlockClear()
{
	BoardAttr blockrow[20];
	for (int i{ 0 }; i < 20; i++) {
		blockrow[i].cell.color = Gray;
		blockrow[i].cell.type = false;
		blockrow[i].boardType = true;
	}

	bool blockLine[20];
	for (int i{ 1 }; i < 21; i++) {
		blockLine[i - 1] = true;
		for (int j{ 1 }; j < 15; j++) {
			if (boardCell[j][i].cell.type == false) {
				blockLine[i - 1] = false;
				break;
			}
		}
	}

	for (int j{ 0 }; j < 20; j++) {
		if (blockLine[j] == true) {
			if (j == 0) {
				for (int i{ 0 }; i < 15; i++) {
					boardCell[i + 1][j + 1].cell.type = false;
					boardCell[i + 1][j + 1].cell.color = Gray;
				}
			}
			else {
				for (int k = j; k > 0; k--) {
					for (int i{ 0 }; i < 15; i++) {
						boardCell[i + 1][k + 1].cell = boardCell[i + 1][k].cell;
					}
				}	
			}
		}
	}
}

bool CUI::IsGameOver()
{
	int x = currentBlock.GetBlockType();
	int y = currentBlock.GetBlockDire();
	int m_x = currentBlock.GetBlockX();
	int m_y = currentBlock.GetBlockY();
	int y_up = 0;
	for (int i{ 0 }; i < 4; i++) {
		if (BlockTypeTran[x][y][i][1] < y_up) {
			y_up = BlockTypeTran[x][y][i][1];
		}
	}
	if (y_up + 1 + m_y <= 1)
		return true;
	return false;
}

void CUI::DownEdgeJudg(int x, int y, int m_x, int m_y)
{
	bool blockDownJudg = true;
	int y_down = -1, x_down = 0, index = 0;	
	for (int i{ 0 }; i < 4; i++) {
		bool downJudg = true;
		int x_block = BlockTypeTran[x][y][i][0];
		for (int j{ 0 }; j < 4 && j != i; j++) {
			if (x_block == BlockTypeTran[x][y][j][0]) {
				if (BlockTypeTran[x][y][i][1] < BlockTypeTran[x][y][j][1])
					downJudg = false;
			}
		}
		if (downJudg) {
			if (boardCell[BlockTypeTran[x][y][i][0] + 7 + m_x][BlockTypeTran[x][y][i][1] + 2 + m_y].cell.type == true)
				blockDownJudg = false;
		}
	}
	for (int i{ 0 }; i < 4; i++) {
		if (BlockTypeTran[x][y][i][1] > y_down) {
			y_down = BlockTypeTran[x][y][i][1];
			index = i;
		}
	}
	if (boardCell[10][y_down + 2 + m_y].boardType == true && blockDownJudg)
		currentBlock.SetDownBool(true);
	else
		currentBlock.SetDownBool(false);
}

void CUI::LeftRightJudg(int x,int y,int m_x,int m_y)
{
	bool blockRightJudg = true;
	bool blockLeftJudg = true;
	for (int i{ 0 }; i < 4; i++) {
		bool rightJudg = true;
		bool leftJudg = true;
		int y_block = BlockTypeTran[x][y][i][1];
		for (int j{ 0 }; j < 4 && j != i; j++) {
			if (y_block == BlockTypeTran[x][y][j][1]) {
				if (BlockTypeTran[x][y][i][0] > BlockTypeTran[x][y][j][0])
					leftJudg = false;
				if (BlockTypeTran[x][y][i][0] < BlockTypeTran[x][y][j][0])
					rightJudg = false;
			}
		}
		if (leftJudg) {
			if (boardCell[BlockTypeTran[x][y][i][0] + 6 + m_x][BlockTypeTran[x][y][i][1] + 1 + m_y].boardType == false ||
				boardCell[BlockTypeTran[x][y][i][0] + 6 + m_x][BlockTypeTran[x][y][i][1] + 1 + m_y].cell.type == true)
				blockLeftJudg = false;
		}
		if (rightJudg) {
			if (boardCell[BlockTypeTran[x][y][i][0] + 6 + m_x+2][BlockTypeTran[x][y][i][1] + 1 + m_y].boardType == false ||
				boardCell[BlockTypeTran[x][y][i][0] + 6 + m_x+2][BlockTypeTran[x][y][i][1] + 1 + m_y].cell.type == true)
				blockRightJudg = false;
		}
	}
	if (blockLeftJudg)
		currentBlock.SetLeftBool(true);
	else
		currentBlock.SetLeftBool(false);
	if (blockRightJudg)
		currentBlock.SetRightBool(true);
	else
		currentBlock.SetRightBool(false);
}

void CUI::DrawCurrentBlock(int m_x,int m_y)
{
	Cell cell;
	cell.type = true;
	cell.color = currentBlock.GetBlockColor();
	int temp_type[4][2];
	int x = currentBlock.GetBlockType();
	int y = currentBlock.GetBlockDire();
	memcpy(temp_type, BlockTypeTran[x][y], sizeof(temp_type));
	int i, j;
	for (int k{ 0 }; k < 4; k++) {
		i = 6 + temp_type[k][0];
		j = temp_type[k][1];
		PrintCell(cell, i + 10 + m_x, j + 1 + m_y);
	}
}

void CUI::DrawNextBlock()
{
	int temp_type[4][2];
	int x = nextBlock.GetBlockType();
	int y = nextBlock.GetBlockDire();
	memcpy(temp_type, BlockTypeTran[x][y], sizeof(temp_type));
	int i, j;
	Cell cell;
	cell.type = true;
	cell.color = nextBlock.GetBlockColor();
	for (int k{ 0 }; k < 4; k++) {
		i = temp_type[k][0];
		j = temp_type[k][1];
		PrintCell(cell, i + 27, j + 5);
	}
}