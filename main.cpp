#include"UI.h"
#include<iostream>
#include<windows.h>
#include <conio.h>	
#include"Define.h"

int main() {
	unsigned __int64 num = 0;
	system("mode con:cols=80 lines=25");
	CUI ui;
	ui.BoardInit();
	ui.DrawBoard();
	ui.ShowInfo();
	int key = 0;
	while (1) {
		ui.DrawBlock();
		if (num % 5000 == 4999) {
			ui.SetDropBool(true);
			ui.DrawBoard();
		}
		num++;
		if (_kbhit()) {
			key = _getch();
			ui.KeyFetch(key);
			PrintInt(key, 1, 1);
			ui.DrawBoard();
		}	
		if (!ui.IsBottom()) {
			if (!ui.IsGameOver()) {
				ui.BlockLandProc();
				ui.BlockClear();
			}
			else {
				exit(0);
			}
		}
	}
}