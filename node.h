#ifndef __NODE_H__
#define __NODE_H__

class node { //8���� ���Ḯ��Ʈ�� ���� ��� Ŭ����
private:
	int data; //

	node * up;
	node * down;
	node * right;
	node * left;
	node * urcross; //����� �밢��
	node * ulcross;	//�»��� �밢��
	node * drcross; //������ �밢�� 
	node * dlcross; //������ �밢��

public:

	node(); //������ ����Ʈ �����ڸ� ���� data 0���� ���� ���� �ٰ���
	void setData(int data);
	void setUp(node *up);
	void setDown(node *down);
	void setRight(node *down);
	void setLeft(node *left);
	void setUrc(node *urc); //urcross setter
	void setUlc(node *ulc); //ulcross setter
	void setDrc(node *drc); //drcross setter
	void setDlc(node *dlc); //dlcross setter

	int getData();
	node * getUp();
	node * getDown();
	node * getRight();
	node * getLeft();
	node * getUrc();
	node * getUlc();
	node * getDrc();
	node * getDlc();
};

#endif