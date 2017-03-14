#include "Game.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

Map::Map() {
}
Map::~Map(){}

void Map::init(){
	score = 0;
	moveLog = 1;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			map[i][j] = 0;
}

void Map::render() {
	system("cls");
	cout << "SCORE : " << score << endl << endl;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			switch (map[j][i]) {
			case 0:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
			case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); break;
			case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); break;
			case 8:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); break;
			case 16:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); break;
			case 32:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); break;
			case 64:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); break;
			case 128:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); break;
			case 256:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); break;
			case 512:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); break;
			default:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
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
					score += map[ob.x][ob.y];
					map[ob.x][ob.y - 1] *= 2;
					map[ob.x][ob.y] = 0;
				}break;
			case DOWN:
				if (map[ob.x][ob.y] == map[ob.x][ob.y + 1]) {
					moveLog = 1;
					score += map[ob.x][ob.y];
					map[ob.x][ob.y + 1] *= 2;
					map[ob.x][ob.y] = 0;
				}break;
			case LEFT:
				if (map[ob.x][ob.y] == map[ob.x - 1][ob.y]) {
					moveLog = 1;
					score += map[ob.x][ob.y];
					map[ob.x - 1][ob.y] *= 2;
					map[ob.x][ob.y] = 0;
				}break;
			case RIGHT:
				if (map[ob.x][ob.y] == map[ob.x + 1][ob.y]) {
					moveLog = 1;
					score += map[ob.x][ob.y];
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
	//_sleep(400);
}