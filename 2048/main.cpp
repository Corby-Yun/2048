#include <iostream>
#include <conio.h>
#include "Game.h"

using namespace std;

int main() {
	Map map;
	try {
		map.init();
		map.createBlock();
		map.render();
		while (1) {
			static char key;
			static int exec = 1;
			do {
				key = getch();
				switch (key) {
				case 'w':
				case 'W':map.move(UP); exec = 1; break;
				case 's':
				case 'S':map.move(DOWN); exec = 1; break;
				case 'a':
				case 'A':map.move(LEFT); exec = 1; break;
				case 'd':
				case 'D':map.move(RIGHT); exec = 1; break;
				case 'r':
				case 'R':cout << "You want RESET GAME? (one more press R)" << endl;
					key = getch();
					if (key == 'r' ||
						key == 'R') {
						map.init();
						map.highScoreUpdate();
					}
					exec = 1;
					break;
				default:
					exec = 0;
					break;
				}
			} while (exec == 0);
			map.render();
			map.createBlock();
			map.render();
			//map.debug();
		}
	}catch (char* error) {
		cout << error << endl;
	}
	return 0;
}