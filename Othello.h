#pragma once

#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Othello {
private:
	const static int BOARD_SIZE = 8;
	const static char BOARD_EMPTY = ' ';
	const static char BOARD_PLAYER_1 = 'O';
	const static char BOARD_PLAYER_2 = 'X';
	
	enum Direction {
		UP, UP_RIGHT, RIGHT, DOWN_RIGHT,
		DOWN, DOWN_LEFT, LEFT, UP_LEFT, DIRECTION_SIZE
	};

	char board[BOARD_SIZE][BOARD_SIZE];
	bool passCheck[BOARD_SIZE][BOARD_SIZE];
	Player player[2] = { BOARD_PLAYER_1,BOARD_PLAYER_2 };
	bool playerFlag;

	char getCurrentIndex();
	bool putBoardMark(int r, int c);
	bool checkLineMark(int r, int c, Direction d);
	bool checkBoardMark(int r, int c);
	int turnLineMark(int r, int c, Direction d);
	int turnBoardMark(int r, int c);
	void printBoard();

public:
	Othello();
	void playGame();
};