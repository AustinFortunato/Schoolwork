//Own a musket for home defense, since that's what the founding fathers intended. Four ruffians break into my house. "What the devil?" As I grab my powdered wig and Kentucky rifle. Blow a golf ball sized hole through the first man, he's dead on the spot. Draw my pistol on the second man, miss him entirely because it's smoothbore and nails the neighbors dog. I have to resort to the cannon mounted at the top of the stairs loaded with grape shot, "Tally ho lads" the grape shot shreds two men in the blast, the sound and extra shrapnel set off car alarms. Fix bayonet and charge the last terrified rapscallion. He Bleeds out waiting on the police to arrive since triangular bayonet wounds are impossible to stitch up. Just as the founding fathers intended.
#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<vector>
#include"battleship.h"
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75

int x = 0;
int y = 0;	
int player = 0;
int slct[2] = { 0, 1 };

battleship::battleship() {
	
}

void battleship::bsmain() {
	initGrid();
	print();
	move();
	place_pieces();
}

void battleship::highlight(string text, int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, 7);
}

void battleship::initGrid() {
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid[k][i][j] = '*';
			}
		}
	}
}

void battleship::print() {
	cout << "\n\nIt is player " << player + 1 << "'s turn.\n";
	cout << "|\t| A | B | C | D | E | F | G | H | I | J |\t\t|\t| A | B | C | D | E | F | G | H | I | J |\n|-------|---|---|---|---|---|---|---|---|---|---|\t\t|-------|---|---|---|---|---|---|---|---|---|---|\n";
	for (int i = 0; i < 10; i++) {
		cout << "|   " << i + 1 << "\t| ";
		for (int b1 = 0; b1 < 10; b1++) {
			if (i == slct[0] && b1 == slct[1]) {
				highlight(string(1, grid[player][i][b1]), 140);
				cout << " | ";
			}
			else
				cout << grid[player][i][b1] << " | ";
		}
		cout << "\t\t" << "|   " << i + 1 << "\t| ";
		for (int b2 = 0; b2 < 10; b2++) {
			cout << grid[player][i][b2] << " | ";
		}
		cout << "\n|-------|---|---|---|---|---|---|---|---|---|---|\t\t|-------|---|---|---|---|---|---|---|---|---|---|\n";
	}
}

void battleship::setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void battleship::move() {
	bool go = true;
	while (go) {
		int move = _getch();
		if (move != 224) {
			switch (move) {
			case KEY_UP:
				if (y > 0) {
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					cout << grid[player % 2 + 1][x][y];
					y--;
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					highlight(string(1, grid[player % 2 + 1][x][y]), 240);
				}
				break;
			case KEY_DOWN:
				if (y < 9) {
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					cout << grid[player % 2 + 1][x][y];
					y++;
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					highlight(string(1, grid[player % 2 + 1][x][y]), 240);
				}
				break;
			case KEY_LEFT:
				if (x > 0) {
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					cout << grid[player % 2 + 1][x][y];
					x--;
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					highlight(string(1, grid[player % 2 + 1][x][y]), 240);
				}
				break;
			case KEY_RIGHT:
				if (x < 9) {
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					cout << grid[player % 2 + 1][x][y];
					x++;
					setCursorPosition((x * 4) + 10, (y * 2) + 10);
					highlight(string(1, grid[player % 2 + 1][x][y]), 240);
				}
				break;
			case 13:
				setCursorPosition(0, 22);
				go = false;
				break;
			}
		}
	}
}

void battleship::place_pieces() {
	// Player presses number 1-5, boat spawns, r to rotate 90 degrees
	char pieces[5][7] = {
		{'<','-','-','0','-','>'},
		{'<','-','-','-','>'},
		{'<','-','-','>'},
		{'<','-','>'},
		{'<','0','-','0','>'},
	};
	int x;
	cout << "Ships:\n1: " << pieces[0] << "\n2: " << pieces[1] << "\n3: " << pieces[2] << "\n4: " << pieces[3] << "\n5: " << pieces[4] << "\n";
	cin >> x;
	for (int i = 0; i < 6; i++) {
		grid[player % 2 + 1][y][x + i] = pieces[x - 1][i];
		setCursorPosition(((x + i) * 4) + 10, (y * 2) + 10);
		highlight(string(1, grid[player % 2 + 1][y][x + i]), 50);
	}
	setCursorPosition(30, 30);
}

battleship::~battleship() {

}
