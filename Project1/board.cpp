#include "board.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

Board::Board() {
	len = 12;
	pos.first = MAX_W / 2 - len / 2 + 1;
	pos.second = MAX_H;
	p_len = new char[len + 1];
	p_len[len] = '\0';
	for (size_t i = 0; i < (size_t)len; i++)
		p_len[i] = '_';
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	set_Console(pos.first - 1, pos.second);
	printf("%s", p_len);
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
}

Board::~Board() {
	delete []p_len;
}

void Board::board_Move() {
	int x = pos.first;
	int y = pos.second;
	if (_kbhit()) {
		if (GetKeyState(65) < 0 && pos.first >= 4)
			pos.first-= 2;
		if (GetKeyState(68) < 0 && pos.first <= MAX_W - len)
			pos.first+= 2;
		if (GetKeyState(VK_SPACE) < 0)
			system("pause>nul");
	}

	if (x == pos.first && y == pos.second)
		return;
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	set_Console(x - 1, y);
	memset(p_len, ' ', len);
	printf("%s", p_len);
	set_Console(pos.first - 1, pos.second);
	memset(p_len, '_', len);
	printf("%s", p_len);
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
}