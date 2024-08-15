#pragma once

#include<windows.h>
#include<string>
#include<conio.h>

using CellType = bool;

const enum Color {
	Gray = 8,
	Blue,
	Red,
	Yellow,
	Green,
	Orang,
	Purple,
	White,
	Black
};

const enum BlockDirection {
	up = 100,
	right,
	down,
	left,
};

extern struct Cell {
	CellType type;
	int color;
};

const enum BlockTyoeNo {
	B_I = 0,
	B_L,
	B_J,
	B_Z,
	B_S,
	B_T,
	B_O
};

const static int BlockTypeTran[7][4][4][2] = {
	//I形方块
	{
		//UP方向
		{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
		//RIGHT方向
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
		//DOWN方向
		{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
		//LEFT方向
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } }
	},

	//L形方块
	{
		//UP方向
		{	{ 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 }	},
		//RIGHT方向
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 1 } },
		//DOWN方向
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
		//LEFT方向
		{ { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } }
	},

	//J形方块
	{
		//UP方向
		{ { 1, 0 }, { 1, 1 }, { 0, 2 }, { 1, 2 } },
		//RIGHT方向
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } },
		//DOWN方向
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 2 } },
		//LEFT方向
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 } }
	},

	//Z形方块
	{
		//UP方向
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } },
		//RIGHT方向
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } },
		//DOWN方向
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } },
		//LEFT方向
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } }
	},

	//S形方块
	{
		//UP方向
		{ { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } },
		//RIGHT方向
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } },
		//DOWN方向
		{ { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } },
		//LEFT方向
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } }
	},

	//T形方块
	{
		//UP方向
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } },
		//RIGHT方向
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } },
		//DOWN方向
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 1, 1 } },
		//LEFT方向
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } }
	},

	//O形方块
	{
		//UP方向
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
		//RIGHT方向
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
		//DOWN方向
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
		//LEFT方向
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } }
	},
	};

const static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

extern struct BoardAttr {
	int x_offset;
	int y_offset;
	bool boardType;
	Cell cell;
};

inline void GotoXY(int x, int y)
{
	COORD pos;
	pos.X = x * 2 ;
	pos.Y = y;
	SetConsoleCursorPosition(h, pos);
}

inline void PrintCell(Cell cell, int x, int y)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	if (cell.type == true)
		WriteConsoleOutputCharacterA(h, "■", 2, pos, &unuse);
	else
		WriteConsoleOutputCharacterA(h, "□", 2, pos, &unuse);
	FillConsoleOutputAttribute(h, cell.color, 2, pos, &unuse);
}

inline void PrintInt(int num, int x, int y) {
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	char str[20];
	_itoa_s(num, str, 10);
	size_t len{ strlen(str) };
	WriteConsoleOutputCharacterA(h, str, len, pos, &unuse);
	FillConsoleOutputAttribute(h, 15, len, pos, &unuse);
}

inline void PrintString(std::string string, int x, int y) {
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	const char* str = string.c_str();
	size_t len{ strlen(str) };
	WriteConsoleOutputCharacterA(h, str, len, pos, &unuse);
	FillConsoleOutputAttribute(h, 15, len, pos, &unuse);
}

inline int operator-(SYSTEMTIME a, SYSTEMTIME b) {
	if (a.wSecond == b.wSecond)
		return a.wMilliseconds - b.wMilliseconds;
	else if (a.wSecond - b.wSecond == 1 || a.wSecond - b.wSecond == -59)
		return a.wMilliseconds - b.wMilliseconds + 1000;
	else
		return a.wMilliseconds - b.wMilliseconds + 2000;
}
