#pragma once

class Player {
private:
	char mark;
	int count;

public:
	Player(char mark) :mark(mark), count(2) {}
	char getMark() { return mark; }
	void setCount(int n) { count = n; }
	int getCount() { return count; }
	// 추가로 작업할 것
};