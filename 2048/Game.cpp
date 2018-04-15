#include "Game.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

Map::Map() {
}
Map::~Map(){}

void Map::init(){
	TCHAR programpath[_MAX_PATH];
	CHAR _programpath[_MAX_PATH];
	GetModuleFileName(NULL, programpath, _MAX_PATH);
	WideCharToMultiByte(CP_ACP, 0, programpath, _MAX_PATH, _programpath, _MAX_PATH, NULL, NULL);
	string path = _programpath;
	for (int i = path.size() - 1; path.at(i) != '\\'; i--) {
		path.pop_back();
	}
	score = 0;
	moveLog = 1;
	fstream high_score_file_temp;
	char temp[10] = {0,};
	high_score_file_temp.open(path + "./high.sav");
	if (!high_score_file_temp.is_open()) {
		throw "can not open file.\nyou need create file 'high.sav' at path of binary file.";
	}
	high_score_file_temp.read(temp,10);
	high_score = atoi(temp);
	high_score_file_temp.close();
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			map[i][j] = 0;
}

void Map::render() {
	system("cls");
	cout << "HIGH SCORE : " << high_score << endl;
	cout << "SCORE : " << score << endl << endl;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			switch (map[j][i]) {
			case 0:set_color(WHITE,BLACK); break;
			case 2:set_color(GRAY, BLACK); break;
			case 4:set_color(D_YELLOW, BLACK); break;
			case 8:set_color(GREEN, BLACK); break;
			case 16:set_color(D_VIOLET, BLACK); break;
			case 32:set_color(SKYBLUE, BLACK); break;
			case 64:set_color(RED, BLACK); break;
			case 128:set_color(BLUE, BLACK); break;
			case 256:set_color(VIOLET, BLACK); break;
			case 512:set_color(D_SKYBLUE, BLACK); break;
			case 1024:set_color(D_BLUE, BLACK); break;
			case 2048:set_color(D_GREEN, BLACK); break;
			}
			printf("%4d", map[j][i]);
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Map::_setBlock(int x, int y, int num){
	map[x][y] = num;
}

void Map::createBlock(){
	Pos ob;
	if (moveLog == 0)
		return;
	_sleep(250);
	do {
		ob.x = rand() % MAP_SIZE;
		ob.y = rand() % MAP_SIZE;
	} while (map[ob.x][ob.y] != 0);

	if (rand() % 2 == 0)
		map[ob.x][ob.y] = 2;
	else
		map[ob.x][ob.y] = 4;
}

void Map::move(int d) {
	moveLog = 0;
	sortToZero(d);
	if (list.empty() == 0) {
		for_each(list.begin(), list.end(), [&](Pos ob) {
			switch (d) {
			case UP:
				if (map[ob.x][ob.y] == map[ob.x][ob.y - 1]) {
					moveLog = 1;
					score_up(map[ob.x][ob.y]);
					map[ob.x][ob.y - 1] *= 2;
					map[ob.x][ob.y] = 0;
				}break;
			case DOWN:
				if (map[ob.x][ob.y] == map[ob.x][ob.y + 1]) {
					moveLog = 1;
					score_up(map[ob.x][ob.y]);
					map[ob.x][ob.y + 1] *= 2;
					map[ob.x][ob.y] = 0;
				}break;
			case LEFT:
				if (map[ob.x][ob.y] == map[ob.x - 1][ob.y]) {
					moveLog = 1;
					score_up(map[ob.x][ob.y]);
					map[ob.x - 1][ob.y] *= 2;
					map[ob.x][ob.y] = 0;
				}break;
			case RIGHT:
				if (map[ob.x][ob.y] == map[ob.x + 1][ob.y]) {
					moveLog = 1;
					score_up(map[ob.x][ob.y]);
					map[ob.x + 1][ob.y] *= 2;
					map[ob.x][ob.y] = 0;
				}break;
			}
		});
		sortToZero(d);
		list.clear();
	}
}

void Map::debug(){
	cout << "List : ";
	if (list.empty() == 0)
		cout << list.size();
	else
		cout << "Empty";
	cout << endl;
	cout << "moveLog : " << moveLog << endl;
}

Pos Map::moveToZero(int x, int y, int d){
	Pos pos;
	pos.x = -1;
	pos.y = -1;
	switch (d) {
	case UP:
		if (y == 0)
			return pos; 
		break;
	case DOWN:
		if (y == MAP_SIZE - 1)
			return pos; 
		break;
	case LEFT:
		if (x == 0)
			return pos; 
		break;
	case RIGHT:
		if (x == MAP_SIZE - 1)
			return pos; 
		break;
	}
	do {
		if (d == UP) {
			if (map[x][y - 1] == 0) {
				map[x][y - 1] = map[x][y];
				map[x][y--] = 0;
				if (y == 0)
					break;
			}
			else
				break;
		}else if (d == DOWN) {
			if (map[x][y + 1] == 0) {
				map[x][y + 1] = map[x][y];
				map[x][y++] = 0;
				if (y == MAP_SIZE-1)
					break;
			}
			else
				break;
		}else if (d == LEFT) {
			if (map[x-1][y] == 0) {
				map[x-1][y] = map[x][y];
				map[x--][y] = 0;
				if (x == 0)
					break;
			}
			else
				break;
		}else if (d == RIGHT) {
			if (map[x+1][y] == 0) {
				map[x+1][y] = map[x][y];
				map[x++][y] = 0;
				if (x == MAP_SIZE-1)
					break;
			}
			else
				break;
		}else {
			return pos;
		}
	} while (1);
	pos.x = x;
	pos.y = y;
	return pos;
}

void Map::sortToZero(int d){
	switch (d) {
	case UP:for (int j = 1; j < MAP_SIZE; j++)
		for (int i = 0; i < MAP_SIZE; i++) {
			if (map[i][j] != 0) {
				Pos ob = moveToZero(i, j, d);
				if (ob.y != j) {
					moveLog = 1;
				}
				if (ob.y != 0)
					list.push_back(ob);
			}
		}
	break;
	case DOWN:for (int j = MAP_SIZE - 2; j >= 0; j--)
		for (int i = 0; i < MAP_SIZE; i++) {
			if (map[i][j] != 0) {
				Pos ob = moveToZero(i, j, d);
				if (ob.y != j)
					moveLog = 1;
				if (ob.y != MAP_SIZE-1)
					list.push_back(ob);
			}
		}
	break;
	case LEFT:for (int i = 1; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] != 0) {
				Pos ob = moveToZero(i, j, d);
				if (ob.x != i)
					moveLog = 1;
				if (ob.x != 0)
					list.push_back(ob);
			}
		}
	break;
	case RIGHT:for (int i = MAP_SIZE - 2; i >= 0; i--)
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] != 0) {
				Pos ob = moveToZero(i, j, d);
				if (ob.x != i)
					moveLog = 1;
				if (ob.x != MAP_SIZE-1)
					list.push_back(ob);
			}
		}
	break;
	}
}

void Map::highScoreUpdate()
{
	fstream high_score_file_temp;
	high_score_file_temp.open("high.sav");
	if (!high_score_file_temp.is_open()) {
		throw "can not open file.";
	}
	string temp = to_string(high_score);
	high_score_file_temp.write(temp.c_str(),temp.size());
	high_score_file_temp.close();
}

void Map::score_up(int num)
{
	score += num;
	if (score > high_score) {
		high_score = score;
	}
}

void Map::set_color(int Back_Color, int Font_Color){
	HANDLE Console_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console_Handle, Back_Color * 16 + Font_Color);
}
