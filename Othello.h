#pragma once

#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Othello {
private:
	// 오델로 게임 보드의 크기
	const static int BOARD_SIZE = 8;
	// 오델로 보드의 빈 곳
	const static char BOARD_EMPTY = ' ';
	// 플레이어 1의 말 표시
	const static char BOARD_PLAYER_1 = 'O';
	// 플레이어 2의 말 표시
	const static char BOARD_PLAYER_2 = 'X';
	// 플레이어의 말 검사 시 방향 탐지를 위한 열거형
	enum Direction {
		UP, UP_RIGHT, RIGHT, DOWN_RIGHT,
		DOWN, DOWN_LEFT, LEFT, UP_LEFT, DIRECTION_SIZE
	};

	// 오델로 게임 보드
	char board[BOARD_SIZE][BOARD_SIZE];
	// 보드에서 말을 둘 수 있는 곳을 체크하기 위한 2차원 배열
	bool passCheck[BOARD_SIZE][BOARD_SIZE];
	// 오델로 게임 플레이어 배열
	Player player[2] = { BOARD_PLAYER_1,BOARD_PLAYER_2 };
	// 플레이어 순서를 표시
	bool playerFlag;

	// 현재 플레이어의 순서 반환 메소드
	char getCurrentIndex();
	// 플레이어가 말을 놓는 메소드
	bool putBoardMark(int r, int c);
	// 플레이어가 말을 놓을 곳을 줄 단위로 검사하는 메소드
	bool checkLineMark(int r, int c, Direction d);
	// 플레이어가 말을 놓을 곳을 전체 검사하는 메소드
	bool checkBoardMark(int r, int c);
	// 플레이어가 말을 놓았을 때 바뀌는 말들을 줄 단위로 바꾸는 메소드
	int turnLineMark(int r, int c, Direction d);
	// 플레이어가 말을 놓았을 때 바뀌는 말들을 모두 바꾸는 메소드
	int turnBoardMark(int r, int c);
  // 오델로 게임의 보드를 출력하는 메소드
	void printBoard();
  
  public:
	// 오델로 클래스의 기본 생성자
	Othello(); 
	// 오델로 게임을 시작하는 메소드
	void playGame();
};
