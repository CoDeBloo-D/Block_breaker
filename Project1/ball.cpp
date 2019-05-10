#include "ball.h"
#include <iostream>

Ball::Ball() {
	pos.first = MAX_W / 2 - 1;
	pos.second = MAX_H;
	speed = 0;
	v = rand() % 2;
	h = rand() % 2;
}

Ball::~Ball() {
}

void Ball::set_Speed(int s) {
	speed = s;
	return;
}