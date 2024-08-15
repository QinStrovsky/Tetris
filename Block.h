#pragma once
#include<thread>
#include<windows.h>
#include <conio.h>	

class Block
{
public:
	Block();
	Block(int type, int dire,int color_tmp);
	int GetBlockType();
	int GetBlockDire();
	int GetBlockX();
	int GetBlockY();
	int GetBlockColor();
	void BlockInit();
	void BlockCtrl(int);
	void BlockDrop();
	void SetRightBool(bool value);
	void SetLeftBool(bool value);
	void SetDownBool(bool value);
	void SetRevoleBool(bool value);
	bool GetDownBool();
private:
	void BlockMove(int);
	void BlockRevolve();	
private:
	int blockType;
	int blockDire;
	int m_x;
	int m_y;
	int heigh = 0;
	int color;
	SYSTEMTIME block_temp_time;
	bool edge_right = true, edge_left = true, edge_down = true, revole_bool = false;
};

