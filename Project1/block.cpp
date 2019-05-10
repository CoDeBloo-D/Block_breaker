#include "block.h"
#include <iostream>
#include <Windows.h>

Block::Block() {
	v.reserve(200);
}

Block::~Block() {
	v.clear();
}

bool Block::gen_Blocks(int num) {
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j < MAX_W / 2 + 1; j++) {
			if (j == 1)
				set_Console(1, i);
			v.push_back(std::pair<int, int>(j * 2, i));
			printf("■");
		}
	}
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
	return true;
}
