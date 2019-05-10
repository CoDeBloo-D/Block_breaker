#pragma once
#include <utility>
#include "common.h"
#include "game.h"

extern class Board;
extern class Block;

class Ball : public Game {
private:
	std::pair<int, int> pos;
	int speed;
	unsigned int v :	1;
	unsigned int h :	1;
public:
	Ball();
	~Ball();
	void set_Speed(int s);
	friend bool ball_Move(Ball * ball, Board * board, Block * block);
};