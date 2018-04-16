#include <conio.h>
#include "Game.h"
#include <iostream>

using namespace std;

int main() {
	Map map;
	try {
		map.load();
		map.start();
		while (1) {
			static char key;
			static int exec = 1;
			do {
				key = getch();
				exec = 1;
				switch (key) {
				case 'w':
				case 'W':map.move(UP);break;
				case 's':
				case 'S':map.move(DOWN);break;
				case 'a':
				case 'A':map.move(LEFT);break;
				case 'd':
				case 'D':map.move(RIGHT);break;
				case 'r':
				case 'R':cout << "You want RESET GAME? (one more press R)" << endl;
					key = getch();
					if (key == 'r' ||
						key == 'R') {
						map.save();
						map.restart();
					}
					break;
				default:
					exec = 0;
					break;
				}
			} while (exec == 0);
			map.createBlock();
			//map.debug();
		}
	}catch (char* error) {
		cout << error << endl;
	}
	return 0;
}