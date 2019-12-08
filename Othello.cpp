#include "Othello.h"

Othello::Othello() {
	for (int i = 0; i < BOARD_SIZE; i++) { // ���� ��� �ʱ�ȭ
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
				cout << "�÷��̾� 1�� �� " << player[0].getMark() << " ���� (R, C): ";
			else
				cout << "�÷��̾� 2�� �� " << player[1].getMark() << " ���� (R, C): ";
			cin >> r >> c;
			system("cls"); 
			if (putBoardMark(r, c)) break; // �ùٸ� �ڸ��� �����ٸ� ���� ������ �ݺ��� ����
			cout << "���� �� �� ���� �ڸ��Դϴ�!!\n" << endl;
		}
		playerFlag = !playerFlag; // �÷��̾� ���� ����

		if (checkAllFinish()) { // ���� ���� ��Ȳ
			cout << "***** ��� ���� *****" << endl;
			break;
		}
		else if (checkPassFinish()) { // ���� pass ��Ȳ
			cout << "***** PASS ��Ȳ�� ��� ���� *****" << endl;
			break;
		}
	}

	if (getVitoryIndex() == 0)
		cout << "�÷��̾� 1�� �¸�!!\n" << endl;
	else
		cout << "�÷��̾� 2�� �¸�!!\n" << endl;
	printScore();
	printBoard();
}

char Othello::getCurrentIndex() {
	return playerFlag ? 1 : 0;
}

bool Othello::putBoardMark(int r, int c) {
	if (board[r][c] != BOARD_EMPTY)return false; // ���尡 �� ������ �ƴϸ� ���� �� �д�.
	if (!checkBoardMark(r, c)) return false; // ���尡 ���� ���� �� �ִ� �������� Ȯ���Ѵ�.
	int cidx = getCurrentIndex(); // �÷��̾� ������ Ȯ��
	int oidx = cidx == 0 ? 1 : 0;
	char my = player[cidx].getMark();

	board[r][c] = my; 
	int score = turnBoardMark(r, c); 
	player[cidx].setCount(player[cidx].getCount() + score); 
	player[oidx].setCount(player[oidx].getCount() - score + 1); 
	return true;
}

bool Othello::checkLineMark(int r, int c, Direction d) {
	char my = player[getCurrentIndex()].getMark(); // ���� �÷��̾��� �� ǥ�ø� ����
	char other = my == BOARD_PLAYER_1 ? BOARD_PLAYER_2 : BOARD_PLAYER_1; // ����� �� ǥ�� ����

	switch (d) { 
	case UP:
		if (r - 1 >= 0 && board[r - 1][c] == other) { // 12�� ���� �˻�
			int rt = r - 2;
			while (rt >= 0) {
				if (board[rt][c] == ' ')break;
				else if (board[rt][c] == my)return true;
				rt--;
			}
		}
		break;
	case UP_RIGHT:
		if (r - 1 < BOARD_SIZE && c + 1 < BOARD_SIZE && board[r - 1][c + 1] == other) { // 1�� ���� �밢�� �˻�
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
		if (c + 1 < BOARD_SIZE && board[r][c + 1] == other) { // 3�� ���� �˻�
			int ct = c + 2;
			while (ct < BOARD_SIZE) {
				if (board[r][ct] == ' ')break;
				else if (board[r][ct] == my)return true;
				ct++;
			}
		}
		break;
	case DOWN_RIGHT:
		if (r + 1 < BOARD_SIZE && c + 1 < BOARD_SIZE && board[r + 1][c + 1] == other) { // 5�� ���� �밢�� �˻�
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
		if (r + 1 < BOARD_SIZE && board[r + 1][c] == other) { // 6�� ���� �˻�
			int rt = r + 2;
			while (rt < BOARD_SIZE) {
				if (board[rt][c] == ' ')break;
				else if (board[rt][c] == my)return true;
				rt++;
			}
		}
		break;
	case DOWN_LEFT:
		if (r + 1 < BOARD_SIZE && c - 1 < BOARD_SIZE && board[r + 1][c - 1] == other) { // 7�� ���� �밢�� �˻�
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
		if (c - 1 >= 0 && board[r][c - 1] == other) { // 9�� ���� �˻�
			int ct = c - 2;
			while (ct >= 0) {
				if (board[r][ct] == ' ')break;
				else if (board[r][ct] == my)return true;
				ct--;
			}
		}
		break;
	case UP_LEFT:
		if (r - 1 < BOARD_SIZE && c - 1 < BOARD_SIZE && board[r - 1][c - 1] == other) { // 11�� ���� �밢�� �˻�
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
		if (checkLineMark(r, c, Direction(i)))return true; // ���� �� �ִ� ���� ������ ���� ��ȯ
	}
	return false;
}

int Othello::turnLineMark(int r, int c, Direction d) {
	char my = player[getCurrentIndex()].getMark(); // ���� �÷��̾��� �� ǥ�ø� ����
	int count = 0; // ���� ����� ���� ������ ���� ���� ����
	int rt, ct;

	switch (d) { // ���⿡ ���� �������鼭 ���� �ø���.
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

	return count; // ���� ���� ��ȯ
}

int Othello::turnBoardMark(int r, int c) {
	int count = 1;
	for (int i = 0; i < DIRECTION_SIZE; i++) { // ������ �˻��ϸ鼭 
		if (checkLineMark(r, c, Direction(i))) { // ������ �� �ִ� ���� ������
			count += turnLineMark(r, c, Direction(i)); // ��� ������ ���� ��� ���� �ø���.
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
	char other = player[oidx].getMark(); // ��� �÷��̾��� �� ǥ�ø� ����

	clearPassCheck(); // passCheck �迭 �ʱ�ȭ�ϰ�
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == other) { 
				if (i - 1 >= 0 && board[i - 1][j] == ' ') // �ش� ��ǥ ���� �������� �˻��� �� �����̸� 
					passCheck[i - 1][j] = true; // ���� ���� �� �ִ� �� �˻��ϵ��� ������ ǥ���Ѵ�.
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
	updatePassCheck(); // passCheck�� �ڸ��� ��� �Ҵ��ϰ�

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
	if (player[0].getCount() == 0 || player[1].getCount() == 0)return true; // �÷��̾��� ���� ������ ���� ���̴�.
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == BOARD_EMPTY) return false; // ������ �� ������ ��� ���� ���̴�.
		}
	}
	return true;
}

int Othello::getVitoryIndex() {
	return player[0].getCount() > player[1].getCount() ? 0 : 1;
}

void Othello::printScore() {
	cout << "�÷��̾� 1: " << player[0].getCount() << "��" << endl;
	cout << "�÷��̾� 2: " << player[1].getCount() << "��" << endl;
}

void Othello::printBoard() {
	cout << "��������������������������������������������������" << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << "��";
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << " " << board[i][j] << "��";
		}
		cout << endl;
		if (i == BOARD_SIZE - 1)break;
		cout << "��������������������������������������������������" << endl;
	}
	cout << "��������������������������������������������������" << endl;
}