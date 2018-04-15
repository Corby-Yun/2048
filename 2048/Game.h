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
		BLACK,   //����
		D_BLUE, //��ο� �Ķ�
		D_GREEN, //��ο� �ʷ�
		D_SKYBLUE, //��ο� �ϴ�
		D_RED, //��ο� ����
		D_VIOLET, //��ο� ����
		D_YELLOW, //��ο� ���
		GRAY, //ȸ��
		D_GRAY, //��ο� ȸ��
		BLUE, //�Ķ�
		GREEN, //�ʷ�
		SKYBLUE, //�ϴ�
		RED, //����
		VIOLET, //����
		YELLOW, //���
		WHITE, //���
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
	Pos moveToZero(int x,int y,int d);//0������ �̵�
	void sortToZero(int d);//������0�̵�
	void highScoreUpdate();
private:
	void score_up(int num);
	void set_color(int Back_Color, int Font_Color);
};

