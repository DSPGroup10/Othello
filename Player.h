#pragma once

class Player { 
private:
	// 오델로 게임의 말 표시
	char mark;
	// 오델로 게임의 말 개수
	int count;
	
public:
	// 플레이어 생성자 (처음 말 개수는 2점)
	Player(char mark) :mark(mark), count(2) {}
	// 플레이어의 말 표시 반환
	char getMark() { return mark; }
	// 플레이어의 말 개수 재설정
	void setCount(int n) { count = n; }
	// 플레이어의 말 개수 반환
	int getCount() { return count; }
  // 추가로 작업할 것
};
