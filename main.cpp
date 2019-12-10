#pragma once
#pragma once
#ifndef __NODE_H__
#define __NODE_H__

class node { //8방향 연결리스트를 위한 노드 클래스
private:
	int data; //

	node* up;
	node* down;
	node* right;
	node* left;
	node* urcross; //우상향 대각선
	node* ulcross;	//좌상향 대각선
	node* drcross; //우하향 대각선 
	node* dlcross; //좌하향 대각선

public:

	node(); //생성자 디폴트 생성자만 쓰고 data 0으로 생성 시켜 줄거임
	void setData(int data);
	void setUp(node* up);
	void setDown(node* down);
	void setRight(node* down);
	void setLeft(node* left);
	void setUrc(node* urc); //urcross setter
	void setUlc(node* ulc); //ulcross setter
	void setDrc(node* drc); //drcross setter
	void setDlc(node* dlc); //dlcross setter

	int getData();
	node* getUp();
	node* getDown();
	node* getRight();
	node* getLeft();
	node* getUrc();
	node* getUlc();
	node* getDrc();
	node* getDlc();
};

#endif
