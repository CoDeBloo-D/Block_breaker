#include "game.h"
#include <iostream>
#include <Windows.h>

Game::Game() {
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
	score = 0;
	set_Console(-1, 0);
	for (int i = 0; i < MAX_H + 2; i++) {
		for (int j = 0; j < MAX_W / 2 + 2; j++) {
			if (i == 0 || i == MAX_H + 1)
				printf("¡õ");
			else {
				if (j == 0 || j == MAX_W / 2 + 1)
					printf("¡õ");
				else
					printf("  ");
			}
		}
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	set_Console(MAX_W + 5, 0);
	printf("---------------");
	set_Console(MAX_W + 5, 1);
	printf("|  Score:0    |");
	set_Console(MAX_W + 5, 2);
	printf("---------------");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
	set_Console(MAX_W + 5, 9);
	printf("How to Control:");
	set_Console(MAX_W + 5, 11);
	printf("Press key A and D");
	set_Console(MAX_W + 5, 13);
	printf("How to Start:");
	set_Console(MAX_W + 5, 15);
	printf("Press key S");
	set_Console(MAX_W + 5, 17);
	printf("How to Pause:");
	set_Console(MAX_W + 5, 19);
	printf("Press key Space");
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
}

Game::~Game() {

}

void Game::set_Target(int t) {
	target = t;
	return;
}

void Game::refresh_Score() {
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
	score++;
	set_Console(MAX_W + 14, 1);
	printf("%d", score);
}