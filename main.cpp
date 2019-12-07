#include "node.h"
#include <iostream>
#include <Windows.h>

using namespace std;

node board[8][8];

int color = 2; //�� �������� 1 �� �������� 2 �� �����̱⿡ �ʱⰪ�� 2

void print_Board(node board[][8]); //��� ����

int change_char(char y); //���θ� ǥ���ϴ� ���ĺ��� ���ڷ� ����

void input(node board[][8], int x, int y); //������ ��ġ�� �Է� �ް� �۾� ����

void change_Color(); //�Է��� ���������� ���� �Ǿ��� �� color�� �ٲ��ִ� �Լ�

int main(void) {

	for (int i = 0; i < 8; i++) { //���� ��� 8���� ���� ����Ʈ ����
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
					board[i][j].setLeft(&board[i - 1][j]);
					board[i][j].setDlc(&board[i + 1][j - 1]);
				}
				else {
					board[i][j].setRight(&board[i][j+1]);
					board[i][j].setDrc(&board[i+1][j+1]);
					board[i][j].setLeft(&board[i - 1][j]);
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
					board[i][j].setDrc(NULL);
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
				board[i][j].setDown(&board[i+1][j]);
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
		print_Board(board);

		cout << "()���Դϴ�. ���� �ڸ��� �����Ͽ� �ּ���(���� ���� ������ �Է����ּ���)...... ";

		cin >> x >> y;

		input(board, x - 1, change_char(y));

		system("cls"); //cmd �ʱ�ȭ
	}
	return 0;
}

void print_Board(node board[][8]) { 
	cout << "   +----+----+----+----+----+----+----+----+ " << endl;
	
	for (int i = 0; i < 8; i++) {
		cout << " " << i + 1 << " |";
		for (int j = 0; j < 8; j++) {
			if(board[i][j].getData()==1 ){
				cout << " �� |";
			}
			else if (board[i][j].getData() == 2) {
				cout << " �� |";
			}
			else {
				cout << "    |";
			}
		}
		cout << endl << "   +----+----+----+----+----+----+----+----+ " << endl;
	}
	cout << "     A    B    C    D    E    F    G    H    " << endl;
}

int change_char(char y) { 
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

void input(node board[][8], int x, int y) {

	node *up=board[x][y].getUp();
	node *ulc=board[x][y].getUlc();
	node *urc=board[x][y].getUrc();
	node *left=board[x][y].getLeft();
	node *right=board[x][y].getRight();
	node *down=board[x][y].getDown();
	node *dlc=board[x][y].getDlc();
	node *drc=board[x][y].getDrc();

	if (up->getData() - color != 0&&up->getData() !=0) {
		while (1) {
			up = up->getUp();
			if (up->getData() == color) {
				do {
					up = up->getDown();
					up->setData(color);
					if (up->getData() != color) {

					}
				} while (up->getData() != color);
				board[x][y].setData(color);
				change_Color();
				break;
			}
		}
	}
}

void change_Color() {
	if (color == 1) {
		color = 2;
	}
	else {
		color = 1;
	}
}