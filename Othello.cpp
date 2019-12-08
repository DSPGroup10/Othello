#include "Othello.h"

Othello::Othello() {
	for (int i = 0; i < BOARD_SIZE; i++) { // 보드 모두 초기화
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = BOARD_EMPTY;
		}
	}
	board[3][3] = board[4][4] = player[0].getMark(); 
	board[3][4] = board[4][3] = player[1].getMark();
	playerFlag = false; 
}

void Othello::playGame() {
	int r, c;

	while (true) {
		while (true) { 
			printScore(); 
			printBoard();
			if (!playerFlag)
				cout << "플레이어 1의 돌 " << player[0].getMark() << " 놓기 (R, C): ";
			else
				cout << "플레이어 2의 돌 " << player[1].getMark() << " 놓기 (R, C): ";
			cin >> r >> c;
			system("cls"); 
			if (putBoardMark(r, c)) break; // 올바른 자리에 놓였다면 말들 뒤집고 반복문 종료
			cout << "돌을 둘 수 없는 자리입니다!!\n" << endl;
		}
		playerFlag = !playerFlag; // 플레이어 순서 변경

		if (checkAllFinish()) { // 게임 종료 상황
			cout << "***** 경기 종료 *****" << endl;
			break;
		}
		else if (checkPassFinish()) { // 게임 pass 상황
			cout << "***** PASS 상황의 경기 종료 *****" << endl;
			break;
		}
	}

	if (getVitoryIndex() == 0)
		cout << "플레이어 1의 승리!!\n" << endl;
	else
		cout << "플레이어 2의 승리!!\n" << endl;
	printScore();
	printBoard();
}

char Othello::getCurrentIndex() {
	return playerFlag ? 1 : 0;
}

bool Othello::putBoardMark(int r, int c) {
	if (board[r][c] != BOARD_EMPTY)return false; // 보드가 빈 공간이 아니면 말을 못 둔다.
	if (!checkBoardMark(r, c)) return false; // 보드가 말을 놓을 수 있는 공간인지 확인한다.
	int cidx = getCurrentIndex(); // 플레이어 누군지 확인
	int oidx = cidx == 0 ? 1 : 0;
	char my = player[cidx].getMark();

	board[r][c] = my; 
	int score = turnBoardMark(r, c); 
	player[cidx].setCount(player[cidx].getCount() + score); 
	player[oidx].setCount(player[oidx].getCount() - score + 1); 
	return true;
}

bool Othello::checkLineMark(int r, int c, Direction d) {
	char my = player[getCurrentIndex()].getMark(); // 현재 플레이어의 말 표시를 저장
	char other = my == BOARD_PLAYER_1 ? BOARD_PLAYER_2 : BOARD_PLAYER_1; // 상대의 말 표시 저장

	switch (d) { 
	case UP:
		if (r - 1 >= 0 && board[r - 1][c] == other) { // 12시 방향 검사
			int rt = r - 2;
			while (rt >= 0) {
				if (board[rt][c] == ' ')break;
				else if (board[rt][c] == my)return true;
				rt--;
			}
		}
		break;
	case UP_RIGHT:
		if (r - 1 < BOARD_SIZE && c + 1 < BOARD_SIZE && board[r - 1][c + 1] == other) { // 1시 방향 대각선 검사
			int rt = r - 2;
			int ct = c + 2;
			while (rt >= 0 && ct < BOARD_SIZE) {
				if (board[rt][ct] == ' ')break;
				else if (board[rt][ct] == my)return true;
				rt--;
				ct++;
			}
		}
		break;
	case RIGHT:
		if (c + 1 < BOARD_SIZE && board[r][c + 1] == other) { // 3시 방향 검사
			int ct = c + 2;
			while (ct < BOARD_SIZE) {
				if (board[r][ct] == ' ')break;
				else if (board[r][ct] == my)return true;
				ct++;
			}
		}
		break;
	case DOWN_RIGHT:
		if (r + 1 < BOARD_SIZE && c + 1 < BOARD_SIZE && board[r + 1][c + 1] == other) { // 5시 방향 대각선 검사
			int rt = r + 2;
			int ct = c + 2;
			while (rt < BOARD_SIZE && ct < BOARD_SIZE) {
				if (board[rt][ct] == ' ')break;
				else if (board[rt][ct] == my)return true;
				rt++;
				ct++;
			}
		}
		break;
	case DOWN:
		if (r + 1 < BOARD_SIZE && board[r + 1][c] == other) { // 6시 방향 검사
			int rt = r + 2;
			while (rt < BOARD_SIZE) {
				if (board[rt][c] == ' ')break;
				else if (board[rt][c] == my)return true;
				rt++;
			}
		}
		break;
	case DOWN_LEFT:
		if (r + 1 < BOARD_SIZE && c - 1 < BOARD_SIZE && board[r + 1][c - 1] == other) { // 7시 방향 대각선 검사
			int rt = r + 2;
			int ct = c - 2;
			while (rt < BOARD_SIZE && ct >= 0) {
				if (board[rt][ct] == ' ')break;
				else if (board[rt][ct] == my)return true;
				rt++;
				ct--;
			}
		}
		break;
	case LEFT:
		if (c - 1 >= 0 && board[r][c - 1] == other) { // 9시 방향 검사
			int ct = c - 2;
			while (ct >= 0) {
				if (board[r][ct] == ' ')break;
				else if (board[r][ct] == my)return true;
				ct--;
			}
		}
		break;
	case UP_LEFT:
		if (r - 1 < BOARD_SIZE && c - 1 < BOARD_SIZE && board[r - 1][c - 1] == other) { // 11시 방향 대각선 검사
			int rt = r - 2;
			int ct = c - 2;
			while (rt >= 0 && ct >= 0) {
				if (board[rt][ct] == ' ')break;
				else if (board[rt][ct] == my)return true;
				rt--;
				ct--;
			}
		}
		break;
	}
	return false;
}

bool Othello::checkBoardMark(int r, int c) {
	for (int i = 0; i < DIRECTION_SIZE; i++) { 
		if (checkLineMark(r, c, Direction(i)))return true; // 놓을 수 있는 곳이 있으면 참을 반환
	}
	return false;
}

int Othello::turnLineMark(int r, int c, Direction d) {
	char my = player[getCurrentIndex()].getMark(); // 현재 플레이어의 말 표시를 저장
	int count = 0; // 점수 계산을 위한 뒤집힌 말의 개수 저장
	int rt, ct;

	switch (d) { // 방향에 따라 뒤집으면서 점수 올린다.
	case UP:
		rt = r - 1;
		while (rt >= 0) {
			if (board[rt][c] == my)break;
			board[rt][c] = my;
			count++;
			rt--;
		}
		break;
	case UP_RIGHT:
		rt = r - 1;
		ct = c + 1;
		while (rt >= 0 && ct < BOARD_SIZE) {
			if (board[rt][ct] == my)break;
			board[rt][ct] = my;
			count++;
			rt--;
			ct++;
		}
		break;
	case RIGHT:
		ct = c + 1;
		while (ct < BOARD_SIZE) {
			if (board[r][ct] == my)break;
			board[r][ct] = my;
			count++;
			ct++;
		}
		break;
	case DOWN_RIGHT:
		rt = r + 1;
		ct = c + 1;
		while (rt < BOARD_SIZE && ct < BOARD_SIZE) {
			if (board[rt][ct] == my)break;
			board[rt][ct] = my;
			count++;
			rt++;
			ct++;
		}
		break;
	case DOWN:
		rt = r + 1;
		while (rt < BOARD_SIZE) {
			if (board[rt][c] == my)break;
			board[rt][c] = my;
			count++;
			rt++;
		}
		break;
	case DOWN_LEFT:
		rt = r + 1;
		ct = c - 1;
		while (rt < BOARD_SIZE && ct >= 0) {
			if (board[rt][ct] == my)break;
			board[rt][ct] = my;
			count++;
			rt++;
			ct--;
		}
		break;
	case LEFT:
		ct = c - 1;
		while (ct >= 0) {
			if (board[r][ct] == my)break;
			board[r][ct] = my;
			count++;
			ct--;
		}
		break;
	case UP_LEFT:
		rt = r - 1;
		ct = c - 1;
		while (rt >= 0 && ct >= 0) {
			if (board[rt][ct] == my)break;
			board[rt][ct] = my;
			count++;
			rt--;
			ct--;
		}
		break;
	}

	return count; // 계산된 점수 반환
}

int Othello::turnBoardMark(int r, int c) {
	int count = 1;
	for (int i = 0; i < DIRECTION_SIZE; i++) { // 전방향 검사하면서 
		if (checkLineMark(r, c, Direction(i))) { // 뒤집을 수 있는 줄이 있으면
			count += turnLineMark(r, c, Direction(i)); // 모두 뒤집고 점수 모두 합해 올린다.
		}
	}
	return count;
}

void Othello::clearPassCheck() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			passCheck[i][j] = false;
		}
	}
}

void Othello::updatePassCheck() {
	int oidx = getCurrentIndex() == 0 ? 1 : 0;
	char other = player[oidx].getMark(); // 상대 플레이어의 말 표시를 저장

	clearPassCheck(); // passCheck 배열 초기화하고
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == other) { 
				if (i - 1 >= 0 && board[i - 1][j] == ' ') // 해당 좌표 기준 전방향을 검사해 빈 공간이면 
					passCheck[i - 1][j] = true; // 말을 놓을 수 있는 지 검사하도록 참으로 표시한다.
				if (i - 1 < BOARD_SIZE && j + 1 < BOARD_SIZE && board[i - 1][j + 1] == ' ')
					passCheck[i - 1][j + 1] = true;
				if (j + 1 < BOARD_SIZE && board[i][j + 1] == ' ')
					passCheck[i][j + 1] = true;
				if (i + 1 < BOARD_SIZE && j + 1 < BOARD_SIZE && board[i + 1][j + 1] == ' ')
					passCheck[i + 1][j + 1] = true;
				if (i + 1 < BOARD_SIZE && board[i + 1][j] == ' ')
					passCheck[i + 1][j] = true;
				if (i + 1 < BOARD_SIZE && j - 1 < BOARD_SIZE && board[i + 1][j - 1] == ' ')
					passCheck[i + 1][j - 1] = true;
				if (j - 1 >= 0 && board[i][j - 1] == ' ')
					passCheck[i][j - 1] = true;
				if (i - 1 < BOARD_SIZE && j - 1 < BOARD_SIZE && board[i - 1][j - 1] == ' ')
					passCheck[i - 1][j - 1] = true;
			}
		}
	}
}

bool Othello::checkPassFinish() {
	updatePassCheck(); // passCheck의 자리를 모두 할당하고

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (passCheck[i][j]) { 
				if (checkBoardMark(i, j))return false; 
			}
		}
	}
	return true;
}

bool Othello::checkAllFinish() {
	if (player[0].getCount() == 0 || player[1].getCount() == 0)return true; // 플레이어의 말이 없으면 게임 끝이다.
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == BOARD_EMPTY) return false; // 보드의 빈 공간이 없어도 게임 끝이다.
		}
	}
	return true;
}

int Othello::getVitoryIndex() {
	return player[0].getCount() > player[1].getCount() ? 0 : 1;
}

void Othello::printScore() {
	cout << "플레이어 1: " << player[0].getCount() << "점" << endl;
	cout << "플레이어 2: " << player[1].getCount() << "점" << endl;
}

void Othello::printBoard() {
	cout << "┌──┬──┬──┬──┬──┬──┬──┬──┐" << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << "│";
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << " " << board[i][j] << "│";
		}
		cout << endl;
		if (i == BOARD_SIZE - 1)break;
		cout << "├──┼──┼──┼──┼──┼──┼──┼──┤" << endl;
	}
	cout << "└──┴──┴──┴──┴──┴──┴──┴──┘" << endl;
}