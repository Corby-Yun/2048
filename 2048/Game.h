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
};

