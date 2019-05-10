#pragma once
#include <utility>
#include <vector>
#include "common.h"

extern class Ball;
extern class Board;

class Block {
private:
	std::vector<std::pair<int, int>> v;
public:
	Block();
	~Block();
	bool gen_Blocks(int num);
	friend bool ball_Move(Ball * ball, Board * board, Block * block);
};