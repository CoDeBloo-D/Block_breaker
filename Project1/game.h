#pragma once
#include "common.h"

class Game {
protected:
	int score;
	int target;
public:
	Game();
	~Game();
	void set_Target(int t);
	void refresh_Score();
};