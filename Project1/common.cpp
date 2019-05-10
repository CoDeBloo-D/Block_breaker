#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "common.h"
#include "ball.h"
#include "board.h"
#include "block.h"

void set_Console(short x, short y) {
	COORD dst;
	dst.X = x + 1;
	dst.Y = y;
	SetConsoleCursorPosition(handle, dst);
	return;
}

bool ball_Move(Ball * ball, Board * board, Block * block) {
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
	set_Console(ball->pos.first - 1, ball->pos.second);
	std::cout<<"  ";

	std::vector<std::pair<int, int>>::iterator tmp = block->v.end() - 1;
	bool hit = false;
	while (1) {
		if (ball->pos.first - (*tmp).first <= 2 && (*tmp).first - ball->pos.first <= 2 && ball->pos.second - (*tmp).second <= 1 && (*tmp).second - ball->pos.second <= 1) {
			hit = true;
			if(ball->pos.second == (*tmp).second)
				ball->v = (ball->v + 1) % 2;
			else
			ball->h = (ball->h + 1) % 2;
		}
		if (hit) {
			set_Console((*tmp).first - 1, (*tmp).second);
			printf("  ");
			block->v.erase(tmp);
			ball->refresh_Score();
			break;
		}
		if (tmp == block->v.begin())
			break;
		tmp--;
	}

	if (ball->pos.first <= 2)
		ball->v = 0;
	else if (ball->pos.first >= MAX_W - 2)
		ball->v = 1;
	if (ball->pos.second <= 1)
		ball->h = 0;
	else if (ball->pos.second >= MAX_H)
		ball->h = 1;

	if (ball->v)
		ball->pos.first -= 2;
	else
		ball->pos.first += 2;
	if (ball->h)
		ball->pos.second -= 1;
	else
		ball->pos.second += 1;

	set_Console(ball->pos.first - 1, ball->pos.second);
	printf("¡ñ");

	if ((ball->pos.first < board->pos.first || ball->pos.first > board->pos.first + board->len - 1) && ball->pos.second == MAX_H) {
		SetConsoleTextAttribute(handle, FOREGROUND_RED);
		set_Console(MAX_W / 2 - 8, MAX_H / 2);
		printf(" You Lose!              ");
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
		set_Console(MAX_W / 2 - 8, MAX_H / 2 + 2);
		printf(" Press Enter to Restart ");
		set_Console(MAX_W / 2 - 8, MAX_H / 2 + 4);
		printf(" Press ESC to the Menu  ");
		return true;
	}
	else if (ball->pos.second == MAX_H - 1) {
		SetConsoleTextAttribute(handle, FOREGROUND_RED);
		set_Console(board->pos.first - 1, board->pos.second);
		memset(board->p_len, '_', board->len);
		printf("%s", board->p_len);
	}

	if (ball->target <= ball->score) {
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
		set_Console(MAX_W / 2 - 8, MAX_H / 2);
		printf(" You Win!               ");
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
		set_Console(MAX_W / 2 - 8, MAX_H / 2 + 2);
		printf(" Press Enter to Restart ");
		set_Console(MAX_W / 2 - 8, MAX_H / 2 + 4);
		printf(" Press ESC to the Menu  ");
		return true;
	}
	return false;
}

void init() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(handle, &cursor_info);
	SetConsoleTitle("The Block Breaker");
	return;
}

void print_MainMenu() {
	system("cls");
	set_Console(MAX_W / 2, MAX_H / 2 - 2);
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	printf("The  Block  Breaker");
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
	set_Console(MAX_W / 2, MAX_H / 2 + 2);
	printf("Start  Game");
	set_Console(MAX_W / 2, MAX_H / 2 + 4);
	printf("Set  Difficulty");
	set_Console(MAX_W / 2, MAX_H / 2 + 6);
	printf("Exit");
	set_Console(MAX_W / 2, MAX_H / 2 + 10);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
	printf("Press key W and S to switch, Press Enter to confirm");
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
	set_Console(MAX_W / 2 - 6, MAX_H / 2 + 2);
	printf("==>");
	
	int sw = 0;
	
	while (1) {
		if (_kbhit()) {
			if (GetKeyState(83) < 0) {
				set_Console(MAX_W / 2 - 6, MAX_H / 2 + 2 + sw * 2);
				printf("   ");
				sw = (sw + 1) % 3;
				set_Console(MAX_W / 2 - 6, MAX_H / 2 + 2 + sw * 2);
				printf("==>");
			}
			if (GetKeyState(87) < 0) {
				set_Console(MAX_W / 2 - 6, MAX_H / 2 + 2 + sw * 2);
				printf("   ");
				sw = (sw - 1 + 3) % 3;
				set_Console(MAX_W / 2 - 6, MAX_H / 2 + 2 + sw * 2);
				printf("==>");
			}
			if (GetKeyState(13) < 0) {
				switch (sw) {
					case 0:
						game_Loop(dif);
						break;
					case 1:
						dif = set_Difficulty();
						break;
					case 2:
						return;
					default:
						break;
				}
				Sleep(100);
				return print_MainMenu();
			}
		}
		Sleep(100);
	}
	return;
}

int set_Difficulty() {
	Sleep(100);
	system("cls");
	set_Console(MAX_W / 2, MAX_H / 2 + 2);
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
	printf("Difficulty:");
	set_Console(MAX_W / 2, MAX_H / 2 + 10);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
	printf("Press key A and D to switch, Press Enter to confirm");
	SetConsoleTextAttribute(handle, DEFAULT_FONT);
	int ret = dif;
	set_Console(MAX_W / 2 + 12, MAX_H / 2 + 2);
	printf("%d", ret);

	while (1) {
		if (_kbhit()) {
			if (GetKeyState(65) < 0 && ret >= 2) {
				ret--;
				set_Console(MAX_W / 2 + 12, MAX_H / 2 + 2);
				printf("%d", ret);
			}
			if (GetKeyState(68) < 0 && ret <= 5) {
				ret++;
				set_Console(MAX_W / 2 + 12, MAX_H / 2 + 2);
				printf("%d", ret);
			}
			if (GetKeyState(13) < 0) {
				break;
			}
		}
		Sleep(100);
	}
	system("cls");
	return ret;
}

void game_Loop(int difficulty) {
	while (1) {
		system("cls");
		bool exit = false;
		Ball ball;
		Board board;
		Block block;
		block.gen_Blocks(difficulty + 3);
		ball.set_Speed(10 - difficulty);
		ball.set_Target((difficulty + 3) * 25);

		srand((unsigned)time(NULL));

		while (1) {
			if (_kbhit())
				if (GetKeyState(83) < 0)
					break;
		}

		int speed = 10 - difficulty;
		bool quit = false;
		while (!quit) {
			speed--;
			if (speed == 0) {
				quit = ball_Move(&ball, &board, &block);
				speed = 10 - difficulty;
			}
			board.board_Move();
			Sleep(10);
		}

		while (1) {
			if (_kbhit()) {
				if (GetKeyState(27) < 0) {
					exit = true;
					break;
				}
				if (GetKeyState(13) < 0)
					break;
			}
		}

		system("cls");
		if (exit)
			break;
	}
}