#pragma once
#define MAX_W 50
#define MAX_H 20
#define DEFAULT_FONT 0x7
#define handle GetStdHandle(STD_OUTPUT_HANDLE)

extern class Ball;
extern class Board;
extern class Block;
extern int dif;

void set_Console(short x, short y);
bool ball_Move(Ball * ball, Board * board, Block * block);
void init();
void print_MainMenu();
int set_Difficulty();
void game_Loop(int difficulty);