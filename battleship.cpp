//Own a musket for home defense, since that's what the founding fathers intended. Four ruffians break into my house. "What the devil?" As I grab my powdered wig and Kentucky rifle. Blow a golf ball sized hole through the first man, he's dead on the spot. Draw my pistol on the second man, miss him entirely because it's smoothbore and nails the neighbors dog. I have to resort to the cannon mounted at the top of the stairs loaded with grape shot, "Tally ho lads" the grape shot shreds two men in the blast, the sound and extra shrapnel set off car alarms. Fix bayonet and charge the last terrified rapscallion. He Bleeds out waiting on the police to arrive since triangular bayonet wounds are impossible to stitch up. Just as the founding fathers intended.
#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<vector>
#include<fstream>
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
int r = -1;
bool ships[5] = { true, true, true, true, true };
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

char pieces[5][7] = {
	{'<','-','-','0','-','>'},
	{'<','-','-','-','>'},
	{'<','-','-','>'},
	{'<','-','>'},
	{'<','0','-','0','>'},
};

battleship::battleship() {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void battleship::setCursorPosition(int xx, int yy) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)xx, (SHORT)yy };
	SetConsoleCursorPosition(hOut, coord);
}

void battleship::highlight(string text, int color) {
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, 7);
}

void battleship::bsmain() {
	startMenu();
	print();
	centerShips();
	functionController();
	saveGame();
}

void battleship::startMenu() {
	char option;
	cout << "Would you like to start a new game (n) or load an existing one (l)?\n> ";
	cin >> option;
	switch (option) {
	case 'n':
		initGrid();
		break;
	case 'l':
		loadGame();
		break;
	default:
		cout << "\nError enter a valid choice\n";
		break;
	}
}

void battleship::initGrid() {
	for (int k = 0; k < 4; k++) {
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
			if (grid[player % 2][b1][i] == '*') {
				cout << grid[player % 2][b1][i];
			}
			else {
				highlight(string(1, grid[player % 2][b1][i]), 14);
			}
			cout << " | ";
		}
		cout << "\t\t|   " << i + 1 << "\t| ";
		for (int b2 = 0; b2 < 10; b2++) {
			if (grid[player % 2 + 2][b2][i] == '*') {
				cout << grid[player % 2 + 2][b2][i];
			}
			else {
				highlight(string(1, grid[player % 2 + 2][b2][i]), 14);
			}
			cout << " | ";
		}
		cout << "\n|-------|---|---|---|---|---|---|---|---|---|---|\t\t|-------|---|---|---|---|---|---|---|---|---|---|\n";
	}
}

void battleship::functionController() {
	bool flag = true;
	while (flag) {
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
			case KEY_ONE:
				if (ships[0]) {
					place_pieces(1);
				}
				break;
			case KEY_TWO:
				if (ships[1]) {
					place_pieces(2);
					break;
				}
			case KEY_THREE:
				if (ships[2]) {
					place_pieces(3);
					break;
				}
			case KEY_FOUR:
				if (ships[3]) {
					place_pieces(4);
					break;
				}
			case KEY_FIVE:
				if (ships[4]) {
					place_pieces(5);
					flag = false;
					break;
				}
			}
		}
	}
}

void battleship::move(char m) {
	switch (m) {
	case 'u':
		if (y > 0) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				cout << grid[player % 2][x][y];
			}
			else
				highlight(string(1, grid[player % 2][x][y]), 14);
			y--;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				highlight(string(1, grid[player % 2][x][y]), 240);
			}
			else
				highlight(string(1, grid[player % 2][x][y]), 224);
		}
		break;
	case 'd':
		if (y < 9) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				cout << grid[player % 2][x][y];
			}
			else
				highlight(string(1, grid[player % 2][x][y]), 14);
			y++;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				highlight(string(1, grid[player % 2][x][y]), 240);
			}
			else
				highlight(string(1, grid[player % 2][x][y]), 224);
		}
		break;
	case 'l':
		if (x > 0) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				cout << grid[player % 2][x][y];
			}
			else
				highlight(string(1, grid[player % 2][x][y]), 14);
			x--;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				highlight(string(1, grid[player % 2][x][y]), 240);
			}
			else
				highlight(string(1, grid[player % 2][x][y]), 224);
		}
		break;
	case 'r':
		if (x < 9) {
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				cout << grid[player % 2][x][y];
			}
			else
				highlight(string(1, grid[player % 2][x][y]), 14);
			x++;
			setCursorPosition((x * 4) + 10, (y * 2) + 4);
			if (grid[player % 2][x][y] == '*') {
				highlight(string(1, grid[player % 2][x][y]), 240);
			}
			else {
				highlight(string(1, grid[player % 2][x][y]), 224);
			}
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
		if (ships[i])
			highlight(pieces[i], 2);
		else
			highlight(pieces[i], 12);
	}

}

void battleship::rotate(int eks, int why, char piece, int color) {
	if (eks > -1 && eks < 10 && why > -1 && why < 10) {
		grid[player % 2][eks][why] = piece;
		setCursorPosition(eks * 4 + 10, why * 2 + 4);
		highlight(string(1, piece), color);
	}
}

bool battleship::pathfinder(int eks, int why) {
	int count = 1;
	for (int i = 1; i < abs(eks + why); i++) {
		if (eks == 0) {
			if (grid[player % 2][x][y + (why / abs(why)) * i] == '*' && x > -2 && y + why > -2 && why + y <= 10) {
				count++;
			}
		}
		else {
			if (grid[player % 2][x + (eks / abs(eks)) * i][y] == '*' && x + eks > -1 && eks + x <= 10) {
				count++;
			}
		}
	}
	if (count > abs(eks + why) - 1) {
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
	int size = strlen(pieces[z]);
	bool tmp = false;
	bool temp = false;
	bool set = false;
	int lastLine[2] = { 0,0 };
	while (_getch() == 'r') {
		r++;
		switch (r % 4) {
		case 0: // x positive
			if (pathfinder(size, 0)) {
				for (int i = 0; i < size; i++) {
					if (lastLine[0] != 0 || lastLine[1] != 0)
						rotate(x + lastLine[0] * i, y + lastLine[1] * i, '*', 7);
					if (grid[player % 2][x][y] == '*' || set) {
						rotate(x + i, y, pieces[z][i], 14);
						ships[z] = false;
						centerShips();
						set = true;
					}
				}
				lastLine[0] = 1;
				lastLine[1] = 0;
				set = false;
				break;
			}
			else {
				r++;
			}
		case 1: // y positive
			if (pathfinder(0, size)) {
				for (int i = 0; i < size; i++) {
					if (lastLine[0] != 0 || lastLine[1] != 0)
						rotate(x + lastLine[0] * i, y + lastLine[1] * i, '*', 7);
					if (grid[player % 2][x][y] == '*' || set) {
						rotate(x, y + i, pieces[z][i], 14);
						set = true;
						ships[z] = false;
						centerShips();
					}
				}
				lastLine[0] = 0;
				lastLine[1] = 1;
				set = false;
				break;
			}
			else {
					r++;
			}
		case 2: // x negative
			if (pathfinder(-size, 0)) {
				for (int i = 0; i < size; i++) {
					if (lastLine[0] != 0 || lastLine[1] != 0)
						rotate(x + lastLine[0] * i, y + lastLine[1] * i, '*', 7);
					if (grid[player % 2][x][y] == '*' || set) {
						rotate(x - i, y, pieces[z][i], 14);
						set = true;
						ships[z] = false;
						centerShips();
					}
				}
				lastLine[0] = -1;
				lastLine[1] = 0;
				set = false;
				break;
			}
			else {
				r++;
			}
		case 3: // y negative
			if (pathfinder(0, -size)) {
				for (int i = 0; i < size; i++) {
					if (lastLine[0] != 0 || lastLine[1] != 0){
						rotate(x + lastLine[0] * i, y + lastLine[1] * i, '*', 7);
					}
					if (grid[player % 2][x][y] == '*' || set) {
						rotate(x, y - i, pieces[z][i], 14);
						ships[z] = false;
						set = true;
						centerShips();
					}
				}
				lastLine[0] = 0;
				lastLine[1] = -1;
				set = false;
				break;
			}
		}
	}
}

void battleship::saveGame() {
	string fName = "save.txt";
	fstream save;
	save.open(fName, ios::out);
	if (save.is_open()) {
		for (int a = 0; a < 4; a++) {
			for (int b = 0; b < 10; b++) {
				for (int c = 0; c < 10; c++) {
					save << grid[a][c][b] << ' ';
				}
			}
		}
	}
	save.close();
	system("cls");
}

void battleship::loadGame() {
	string fName = "save.txt";
	fstream save;
	save.open(fName, ios::in);
	if (save.is_open()) {
		for (int a = 0; a < 4; a++) {
			for (int b = 0; b < 10; b++) {
				for (int c = 0; c < 10; c++) {
					save >> grid[a][c][b];
				}
			}
		}
	}
	save.close();
}

battleship::~battleship() {

}