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
#define KEY_ENTER 13
#define KEY_ONE 49
#define KEY_TWO 50
#define KEY_THREE 51
#define KEY_FOUR 52
#define KEY_FIVE 53

int x = 0;
int y = 0;
int player = 0;
int r = 0;

char pieces[5][7] = {
	{'<','-','-','0','-','>'},
	{'<','-','-','-','>'},
	{'<','-','-','>'},
	{'<','-','>'},
	{'<','0','-','0','>'},
};

battleship::battleship() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid[k][i][j] = '*';
			}
		}
	}
}

void battleship::bsmain() {
	initGrid();
	print();
	centerShips();
	functionController();
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
	system("cls");
	highlight("\t\tYour ships.", 10);
	highlight("\t\t\t PLAYER " + to_string(player % 2 + 1) + "'S TURN", 13);
	highlight("\t\tTheir ships\n", 12);
	cout << "-------------------------------------------------\t\t-------------------------------------------------\n|\t| A | B | C | D | E | F | G | H | I | J |\t\t|\t| A | B | C | D | E | F | G | H | I | J |\n|-------|---|---|---|---|---|---|---|---|---|---|\t\t|-------|---|---|---|---|---|---|---|---|---|---|\n";
	for (int i = 0; i < 10; i++) {
		cout << "|   " << i + 1 << "\t| ";
		for (int b1 = 0; b1 < 10; b1++) {
			cout << grid[player][i][b1] << " | ";
		}
		cout << "\t\t|   " << i + 1 << "\t| ";
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

void battleship::move(char m) {
	switch (m) {
	case 'u':
		if (y > 0) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				cout << grid[player % 2 + 1][x][y];
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 14);
			y--;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				highlight(string(1, grid[player % 2 + 1][x][y]), 240);
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 224);
		}
		break;
	case 'd':
		if (y < 9) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				cout << grid[player % 2 + 1][x][y];
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 14);
			y++;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				highlight(string(1, grid[player % 2 + 1][x][y]), 240);
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 224);
		}
		break;
	case 'l':
		if (x > 0) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				cout << grid[player % 2 + 1][x][y];
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 14);
			x--;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				highlight(string(1, grid[player % 2 + 1][x][y]), 240);
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 224);
		}
		break;
	case 'r':
		if (x < 9) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				cout << grid[player % 2 + 1][x][y];
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 14);
			x++;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2 + 1][x][y] == '*') {
				highlight(string(1, grid[player % 2 + 1][x][y]), 240);
			}
			else
				highlight(string(1, grid[player % 2 + 1][x][y]), 224);
		}
		break;
	case 'e':
		setCursorPosition(0, 22);
		break;
	}
}

void battleship::centerShips() {
	setCursorPosition(54, 9);
	highlight("Ships", 14);
	for (int i = 0; i < 5; i++) {
		setCursorPosition(53, 11 + i);
		highlight(to_string(i + 1), 14);
		cout << " ";
		highlight(pieces[i], 14);
	}

}

void battleship::rotate(int eks, int why, char piece, int color) {
	if (eks > -1 && eks < 10 && why > -1 && why < 10) {
		grid[player % 2 + 1][eks][why] = piece;
		setCursorPosition(eks * 4 + 10, why * 2 + 4);
		highlight(string(1, piece), color);
		grid[player % 2 + 1][eks][why] = piece;
	}
}

bool battleship::pathfinder(int eks, int why) {
	int count = 0;
	for (int i = 0; i < abs(eks + why); i++) {
		if (eks == 0) {
			if (grid[player % 2 + 1][x][y + (why / abs(why)) * i] == '*' && x > -1 && y + why > -1 && why + y < 10) {
				count++;
			}
		}
		else {
			if (grid[player % 2 + 1][x + (eks / abs(eks)) * i][y] == '*' && x + eks > -1 && eks + x < 10) {
				count++;
			}
		}
	}
	if (count >= abs(eks + why) - 1) {
		return true;
	}
	else {
		return false;
	}
}

void battleship::place_pieces(int z) {
	// Player presses number 1-5, boat spawns, r to rotate 90 degrees
	setCursorPosition(0, 24);
	z--;

	while (_getch() == 'r') {
		r++;
		switch (r % 4) {
		case 0: // x positive
			for (int i = 0; i < strlen(pieces[z]); i++) {
				rotate(x, y - i, '*', 7);
			}
			if (pathfinder(strlen(pieces[z]), 0)) {
				for (int i = 0; i < strlen(pieces[z]); i++) {
					rotate(x + i, y, pieces[z][i], 14);
				}
			}
			break;
		case 1: // y positive
			for (int i = 0; i < strlen(pieces[z]); i++) {
				rotate(x + i, y, '*', 7);
			}
			if (pathfinder(0, strlen(pieces[z]))) {
				for (int i = 0; i < strlen(pieces[z]); i++) {
					rotate(x, y + i, pieces[z][i], 14);
				}
			}
			break;
		case 2: // x negative
			for (int i = 0; i < strlen(pieces[z]); i++) {
				rotate(x, y + i, '*', 7);
			}
			if (pathfinder(-strlen(pieces[z]), 0)) {
				for (int i = 0; i < strlen(pieces[z]); i++) {
					rotate(x - i, y, pieces[z][i], 14);
				}
			}
			break;
		case 3: // y negative
			if (pathfinder(0, -strlen(pieces[z]))) {
				for (int i = 0; i < strlen(pieces[z]); i++) {
					rotate(x - i, y, '*', 7);
				}
				for (int i = 0; i < strlen(pieces[z]); i++) {
					rotate(x, y - i, pieces[z][i], 14);
				}
			}
			break;
		}
	}
}

void battleship::functionController() {
	while (1) {
		int input = _getch();
		if (input != 224) {
			switch (input) {
			case KEY_UP:
				move('u');
				break;
			case KEY_DOWN:
				move('d');
				break;
			case KEY_LEFT:
				move('l');
				break;
			case KEY_RIGHT:
				move('r');
				break;
				//case KEY_ENTER:
				//	// Where do we use enter as of now: 
				//	// Want it to just place a ship 
				break;
			case KEY_ONE:
				place_pieces(1);
				break;
			case KEY_TWO:
				place_pieces(2);
				break;
			case KEY_THREE:
				place_pieces(3);
				break;
			case KEY_FOUR:
				place_pieces(4);
				break;
			case KEY_FIVE:
				place_pieces(5);
				break;
			}
		}
	}
}

battleship::~battleship() {

}