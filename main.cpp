//#include<stdio.h>
#include <iostream>
#include <Windows.h>
#include "node.h"


using namespace std;

node board[8][8];

int color = 2; //백 순서에는 1 흑 순서에는 2 흑 시작이기에 초기값은 2

void print_Board(node board[][8]); //출력 형식

int change_char(char y); //세로를 표현하는 알파벳을 숫자로 맵핑

bool checkpass(node board[][8]); //PASS 체크

bool input(node board[][8], int x, int y); //보드판 위치를 입력 받고 작업 실행

bool checkinput(node board[][8], int x, int y);

void change_Color(); //입력이 성공적으로 종료 되었을 때 color를 바꿔주는 함수

void order(); //누가 놓을 차례인지 알려주는 함수

int white(node board[][8]); //흰색 돌 개수 알려주는 함수

int black(node board[][8]); //검은색 돌 개수 알려주는 함수

int main(void) {

	for (int i = 0; i < 8; i++) { //보드 노드 8방향 연결 리스트 구현
		for (int j = 0; j < 8; j++) {
			board[i][j].setData(0);
			if (i == 0) {
				if (j == 0) {
					board[i][j].setLeft(NULL);
					board[i][j].setDlc(NULL);
					board[i][j].setRight(&board[i][j + 1]);
					board[i][j].setDrc(&board[i + 1][j + 1]);

				}
				else if (j == 7) {
					board[i][j].setRight(NULL);
					board[i][j].setDrc(NULL);
					board[i][j].setLeft(&board[i][j - 1]);
					board[i][j].setDlc(&board[i + 1][j - 1]);
				}
				else {
					board[i][j].setRight(&board[i][j + 1]);
					board[i][j].setDrc(&board[i + 1][j + 1]);
					board[i][j].setLeft(&board[i][j - 1]);
					board[i][j].setDlc(&board[i + 1][j - 1]);

				}
				board[i][j].setUp(NULL);
				board[i][j].setDown(&board[i + 1][j]);
				board[i][j].setUlc(NULL);
				board[i][j].setUrc(NULL);
			}
			else if (i == 7) {
				if (j == 0) {
					board[i][j].setLeft(NULL);
					board[i][j].setUlc(NULL);
					board[i][j].setRight(&board[i][j + 1]);
					board[i][j].setUrc(&board[i - 1][j + 1]);
				}
				else if (j == 7) {
					board[i][j].setRight(NULL);
					board[i][j].setDrc(NULL);
					board[i][j].setLeft(&board[i][j - 1]);
					board[i][j].setUlc(&board[i - 1][j - 1]);
				}
				else {
					board[i][j].setRight(&board[i][j + 1]);
					board[i][j].setUrc(&board[i - 1][j + 1]);
					board[i][j].setLeft(&board[i][j - 1]);
					board[i][j].setUlc(&board[i - 1][j - 1]);
				}
				board[i][j].setUp(&board[i - 1][j]);
				board[i][j].setDown(NULL);
				board[i][j].setDlc(NULL);
				board[i][j].setDrc(NULL);
			}
			else {
				if (j == 0) {
					board[i][j].setLeft(NULL);
					board[i][j].setUlc(NULL);
					board[i][j].setDlc(NULL);
					board[i][j].setRight(&board[i][j + 1]);
					board[i][j].setUrc(&board[i - 1][j + 1]);
					board[i][j].setDrc(&board[i + 1][j + 1]);
				}
				else if (j == 7) {
					board[i][j].setRight(NULL);
					board[i][j].setUrc(NULL);
					board[i][j].setDrc(NULL);
					board[i][j].setLeft(&board[i][j - 1]);
					board[i][j].setUlc(&board[i - 1][j - 1]);
					board[i][j].setDlc(&board[i + 1][j - 1]);
				}
				else {
					board[i][j].setRight(&board[i][j + 1]);
					board[i][j].setUrc(&board[i - 1][j + 1]);
					board[i][j].setDrc(&board[i + 1][j + 1]);
					board[i][j].setLeft(&board[i][j - 1]);
					board[i][j].setUlc(&board[i - 1][j - 1]);
					board[i][j].setDlc(&board[i + 1][j - 1]);
				}
				board[i][j].setUp(&board[i - 1][j]);
				board[i][j].setDown(&board[i + 1][j]);
			}
		}
	}

	board[3][3].setData(1);
	board[3][4].setData(2);
	board[4][3].setData(2);
	board[4][4].setData(1);
	
	int x;
	char y;
	while (1) {
		int exit = 0;
		print_Board(board);
		if (checkpass(board) == true)
			exit++;
		if (checkpass(board) == true)
			exit++;

		if (exit == 2) {
			int bcount = 0;
			int wcount = 0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (board[i][j].getData() == 1) {
						wcount++;
					}
					else if (board[i][j].getData() == 2) {
						bcount++;
					}
				}
			}
			if (wcount > bcount) {
				cout << "백이 이겼습니다. 게임을 종료합니다." << endl;
				break;
			}
			else if (bcount > wcount) {
				cout << "흑이 이겼습니다. 게임을 종료합니다." << endl;
				break;
			}
			else
				cout << "돌의 개수가 같습니다. 무승부입니다." << endl; break;
		}
		cout << "(";
		order();
		cout << ")차례입니다. 놓을 자리를 선택하여 주세요(숫자 영어 순으로 입력해주세요)...... " << endl;
		cout << "현재 놓을 수 있는 자리:";
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (checkinput(board, i, j) == true) {
					char ch = j + 65;
					cout << i + 1 << ch << " ";
				}
			}
		}
		cout << endl;
		cout << "입력할 위치:";
		cin >> x >> y;

		if (input(board, x - 1, change_char(y)) == true) {
			system("cls"); //cmd 초기화
		}
		else {
			while (1) {
				cout << "돌을 놓을 수 없는 자리입니다. 다시 선택하여 주세요.....";
				cin >> x >> y;
				if (input(board, x - 1, change_char(y)) == true) {
					system("cls");
					break;
				}
			}
		}
	}
	cout << "게임을 종료합니다." << endl;
	Sleep(5000);
	return 0;
} // int main

// pass check
bool checkpass(node board[][8]) {
	int checknum = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (checkinput(board, i, j) == false) {
				checknum++;
			}
		}
	}
	cout << endl;
	if (checknum == 64) {
		if (color == 2) {
			cout << "흑이 놓을 수 있는 자리가 없습니다. 차례를 넘깁니다." << endl; Sleep(2000);
			change_Color();
			system("cls");
			print_Board(board);
			return 1;
		}
		else if (color == 1)
			cout << "백이 놓을 수 있는 자리가 없습니다. 차례를 넘깁니다." << endl; Sleep(2000);
		change_Color();
		system("cls");
		print_Board(board);
		return 1;
	}
	return 0;
}


void print_Board(node board[][8]) {
	int bcount = 0;
	int wcount = 0;

	cout << " _____  _____  _   _  _____  _      _      _____ " << endl;
	cout << "|  _  ||_   _|| | | ||  ___|| |    | |    |  _  | " << endl;
	cout << "| | | |  | |  | |_| || |___ | |    | |    | | | |" << endl;
	cout << "| | | |  | |  |  _  ||  ___|| |    | |    | | | | " << endl;
	cout << "| |_| |  | |  | | | || |___ | |___ | |___ | |_| |   " << endl;
	cout << "|_____|  |_|  |_| |_||_____||_____||_____||_____|   " << endl << endl;
	cout << "Released 2019 12 11" << endl;
	cout << "Directed By. KWU DSPGroup10 (Byeon hyosang, Kim hyunil, Park jaehyun, Seo jongwon)" << endl;
	cout << "   +----+----+----+----+----+----+----+----+ " << endl;


	for (int i = 0; i < 8; i++) {
		cout << " " << i + 1 << " |";
		for (int j = 0; j < 8; j++) {
			if (board[i][j].getData() == 1) {
				cout << " ● |"; wcount++;
			}
			else if (board[i][j].getData() == 2) {
				cout << " ○ |"; bcount++;
			}
			else {
				cout << "    |";
			}
		}
		cout << endl << "   +----+----+----+----+----+----+----+----+ " << endl;
	}
	cout << "     A    B    C    D    E    F    G    H    " << endl << endl;
	cout << "현재 돌 개수 >> ○: " << bcount << " | ●:" << wcount << endl;
	if (bcount == 0) {
		cout << "백이 이겼습니다. 게임을 종료합니다." << endl;
		Sleep(5000);
		exit(0);
	}
	else if (wcount == 0) {
		cout << "흑이 이겼습니다. 게임을 종료합니다." << endl;
		Sleep(5000);
		exit(0);
	}
	else if (wcount + bcount == 64) {
		cout << "더 이상 둘 곳이 없습니다. 돌의 개수가 더 많은 쪽이 승리합니다." << endl << endl;
		if (wcount > bcount) {
			cout << "백이 이겼습니다. 게임을 종료합니다." << endl;
			Sleep(5000);
			exit(0);
		}
		else if (bcount > wcount) {
			cout << "흑이 이겼습니다. 게임을 종료합니다." << endl;
			Sleep(5000);
			exit(0);
		}
		else
			cout << "돌의 개수가 같습니다. 무승부입니다." << endl; Sleep(5000); exit(0);
	}
}

int change_char(char y) { //입력 받는거
	if (y == 'A' || y == 'a') {
		return 0;
	}
	else if (y == 'B' || y == 'b') {
		return 1;
	}
	else if (y == 'C' || y == 'c') {
		return 2;
	}
	else if (y == 'D' || y == 'd') {
		return 3;
	}
	else if (y == 'E' || y == 'e') {
		return 4;
	}
	else if (y == 'F' || y == 'f') {
		return 5;
	}
	else if (y == 'G' || y == 'g') {
		return 6;
	}
	else if (y == 'H' || y == 'h') {
		return 7;
	}
}

bool input(node board[][8], int x, int y) {

	if (board[x][y].getData() != 0) {
		return false;
	}

	int check = 0;

	node* up = board[x][y].getUp();
	node* ulc = board[x][y].getUlc();
	node* urc = board[x][y].getUrc();
	node* left = board[x][y].getLeft();
	node* right = board[x][y].getRight();
	node* down = board[x][y].getDown();
	node* dlc = board[x][y].getDlc();
	node* drc = board[x][y].getDrc();

	if (up != NULL && up->getData() - color != 0 && up->getData() != 0) {
		while (1) {
			up = up->getUp();
			if (up == NULL) {
				break;
			}
			else if (up->getData() == 0) {
				break;
			}
			else if (up->getData() == color) {
				while (1) {
					up = up->getDown();
					if (check == 0) {
						if (up->getData() == 0) {
							break;
						}
						else {
							up->setData(color);
						}
					}
					else {
						if (up->getData() == color) {
							break;
						}
						else {
							up->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}
	if (ulc != NULL && ulc->getData() - color != 0 && ulc->getData() != 0) {
		while (1) {
			ulc = ulc->getUlc();
			if (ulc == NULL) {
				break;
			}
			else if (ulc->getData() == 0) {
				break;
			}
			else if (ulc->getData() == color) {
				while (1) {
					ulc = ulc->getDrc();
					if (check == 0) {
						if (ulc->getData() == 0) {
							break;
						}
						else {
							ulc->setData(color);
						}
					}
					else {
						if (ulc->getData() == color) {
							break;
						}
						else {
							ulc->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}
	if (urc != NULL && urc->getData() - color != 0 && urc->getData() != 0) {
		while (1) {
			urc = urc->getUrc();
			if (urc == NULL) {
				break;
			}
			else if (urc->getData() == 0) {
				break;
			}
			else if (urc->getData() == color) {
				while (1) {
					urc = urc->getDlc();
					if (check == 0) {
						if (urc->getData() == 0) {
							break;
						}
						else {
							urc->setData(color);
						}
					}
					else {
						if (urc->getData() == color) {
							break;
						}
						else {
							urc->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}
	if (left != NULL && left->getData() - color != 0 && left->getData() != 0) {
		while (1) {
			left = left->getLeft();
			if (left == NULL) {
				break;
			}
			else if (left->getData() == 0) {
				break;
			}
			else if (left->getData() == color) {
				while (1) {
					left = left->getRight();
					if (check == 0) {
						if (left->getData() == 0) {
							break;
						}
						else {
							left->setData(color);
						}
					}
					else {
						if (left->getData() == color) {
							break;
						}
						else {
							left->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}
	if (right != NULL && right->getData() - color != 0 && right->getData() != 0) {
		while (1) {
			right = right->getRight();
			if (right == NULL) {
				break;
			}
			else if (right->getData() == 0) {
				break;
			}
			else if (right->getData() == color) {
				while (1) {
					right = right->getLeft();
					if (check == 0) {
						if (right->getData() == 0) {
							break;
						}
						else {
							right->setData(color);
						}
					}
					else {
						if (right->getData() == color) {
							break;
						}
						else {
							right->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}
	if (down != NULL && down->getData() - color != 0 && down->getData() != 0) {
		while (1) {
			down = down->getDown();
			if (down == NULL) {
				break;
			}
			else if (down->getData() == 0) {
				break;
			}
			else if (down->getData() == color) {
				while (1) {
					down = down->getUp();
					if (check == 0) {
						if (down->getData() == 0) {
							break;
						}
						else {
							down->setData(color);
						}
					}
					else {
						if (down->getData() == color) {
							break;
						}
						else {
							down->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}
	if (dlc != NULL && dlc->getData() - color != 0 && dlc->getData() != 0) {
		while (1) {
			dlc = dlc->getDlc();
			if (dlc == NULL) {
				break;
			}
			else if (dlc->getData() == 0) {
				break;
			}
			else if (dlc->getData() == color) {
				while (1) {
					dlc = dlc->getUrc();
					if (check == 0) {
						if (dlc->getData() == 0) {
							break;
						}
						else {
							dlc->setData(color);
						}
					}
					else {
						if (dlc->getData() == color) {
							break;
						}
						else {
							dlc->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}
	if (drc != NULL && drc->getData() - color != 0 && drc->getData() != 0) {
		while (1) {
			drc = drc->getDrc();
			if (drc == NULL) {
				break;
			}
			else if (drc->getData() == 0) {
				break;
			}
			else if (drc->getData() == color) {
				while (1) {
					drc = drc->getUlc();
					if (check == 0) {
						if (drc->getData() == 0) {
							break;
						}
						else {
							drc->setData(color);
						}
					}
					else {
						if (drc->getData() == color) {
							break;
						}
						else {
							drc->setData(color);
						}
					}
				}
				board[x][y].setData(color);
				check++;
				break;
			}
		}
	}

	if (check > 0) {
		change_Color();
		return true;
	}
	else {
		return false;
	}
}

bool checkinput(node board[][8], int x, int y) {

	if (board[x][y].getData() != 0) {
		return false;
	}

	int check = 0;

	node* up = board[x][y].getUp();
	node* ulc = board[x][y].getUlc();
	node* urc = board[x][y].getUrc();
	node* left = board[x][y].getLeft();
	node* right = board[x][y].getRight();
	node* down = board[x][y].getDown();
	node* dlc = board[x][y].getDlc();
	node* drc = board[x][y].getDrc();

	if (up != NULL && up->getData() - color != 0 && up->getData() != 0) {
		while (1) {
			up = up->getUp();
			if (up == NULL) {
				break;
			}
			else if (up->getData() == 0) {
				break;
			}
			else if (up->getData() == color) {
				while (1) {
					up = up->getDown();
					if (up->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}
	if (ulc != NULL && ulc->getData() - color != 0 && ulc->getData() != 0) {
		while (1) {
			ulc = ulc->getUlc();
			if (ulc == NULL) {
				break;
			}
			else if (ulc->getData() == 0) {
				break;
			}
			else if (ulc->getData() == color) {
				while (1) {
					ulc = ulc->getDrc();
					if (ulc->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}
	if (urc != NULL && urc->getData() - color != 0 && urc->getData() != 0) {
		while (1) {
			urc = urc->getUrc();
			if (urc == NULL) {
				break;
			}
			else if (urc->getData() == 0) {
				break;
			}
			else if (urc->getData() == color) {
				while (1) {
					urc = urc->getDlc();
					if (urc->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}
	if (left != NULL && left->getData() - color != 0 && left->getData() != 0) {
		while (1) {
			left = left->getLeft();
			if (left == NULL) {
				break;
			}
			else if (left->getData() == 0) {
				break;
			}
			else if (left->getData() == color) {
				while (1) {
					left = left->getRight();
					if (left->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}
	if (right != NULL && right->getData() - color != 0 && right->getData() != 0) {
		while (1) {
			right = right->getRight();
			if (right == NULL) {
				break;
			}
			else if (right->getData() == 0) {
				break;
			}
			else if (right->getData() == color) {
				while (1) {
					right = right->getLeft();
					if (right->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}
	if (down != NULL && down->getData() - color != 0 && down->getData() != 0) {
		while (1) {
			down = down->getDown();
			if (down == NULL) {
				break;
			}
			else if (down->getData() == 0) {
				break;
			}
			else if (down->getData() == color) {
				while (1) {
					down = down->getUp();
					if (down->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}
	if (dlc != NULL && dlc->getData() - color != 0 && dlc->getData() != 0) {
		while (1) {
			dlc = dlc->getDlc();
			if (dlc == NULL) {
				break;
			}
			else if (dlc->getData() == 0) {
				break;
			}
			else if (dlc->getData() == color) {
				while (1) {
					dlc = dlc->getUrc();
					if (dlc->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}
	if (drc != NULL && drc->getData() - color != 0 && drc->getData() != 0) {
		while (1) {
			drc = drc->getDrc();
			if (drc == NULL) {
				break;
			}
			else if (drc->getData() == 0) {
				break;
			}
			else if (drc->getData() == color) {
				while (1) {
					drc = drc->getUlc();
					if (drc->getData() == 0) {
						break;
					}
				}
				check++;
				break;
			}
		}
	}

	if (check > 0) {
		return 1;
	}
	else {
		return 0;
	}
}
void change_Color() { //턴 바꿈
	if (color == 1) {
		color = 2;
	}
	else {
		color = 1;
	}
}

void order() { // 누구 턴인지 알려줌
	if (color == 1) {
		cout << "백";
	}
	else {
		cout << "흑";
	}
}

int white(node board[][8]) { //흰 색 갯수 세기
	int wcount = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].getData() == 1) {
				wcount++;
			}
		}
	}
	return wcount;
}

int black(node board[][8]) { //블랙 갯수 세기
	int bcount = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; i < 8; j++) {
			if (board[i][j].getData() == 2) {
				bcount++;
			}
		}
	}
	return bcount;
}
