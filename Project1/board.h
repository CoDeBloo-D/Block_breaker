#pragma once
#include <utility>
#include "common.h"

extern class Ball;
extern class Block;

class Board {
private:
	std::pair<int, int> pos;
	int len;
	char *p_len;
public:
	Board();
	~Board();
	void board_Move();
	friend bool ball_Move(Ball * ball, Board * board, Block * block);
};