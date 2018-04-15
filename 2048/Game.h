#pragma once
#include <vector>

using namespace std;

#define MAP_SIZE 4
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

struct Pos {
	int x;
	int y;
};

class Map{
private:
	enum ColorCode{
		BLACK,   //검정
		D_BLUE, //어두운 파랑
		D_GREEN, //어두운 초록
		D_SKYBLUE, //어두운 하늘
		D_RED, //어두운 빨강
		D_VIOLET, //어두운 보라
		D_YELLOW, //어두운 노랑
		GRAY, //회색
		D_GRAY, //어두운 회색
		BLUE, //파랑
		GREEN, //초록
		SKYBLUE, //하늘
		RED, //빨강
		VIOLET, //보라
		YELLOW, //노랑
		WHITE, //흰색
	};
	int high_score = 0;
	int score = 0;
	vector<Pos> list;
	int map[MAP_SIZE][MAP_SIZE];
	int moveLog=1;
public:
	Map();
	~Map();
	void init();
	void render();
	void _setBlock(int x,int y , int num);
	void createBlock();
	void move(int d);
	void debug();
	Pos moveToZero(int x,int y,int d);//0쪽으로 이동
	void sortToZero(int d);//모든수가0이동
	void highScoreUpdate();
private:
	void score_up(int num);
	void set_color(int Back_Color, int Font_Color);
};

