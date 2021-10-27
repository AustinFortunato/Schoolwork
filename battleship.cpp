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
#define KEY_H 104

int x = 0;
int y = 0;
int player = 0;
int r = -1;
bool ships[2][6] = { {true, true, true, true, true, false}, {true,true,true,true,true,true} };
int hits = 0;
bool flag = true;
//hits1 = 0;
//hits2 = 0;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

char pieces[5][7] = {
	{'<','-','-','0','-','>'},
	{'<','-','-','-','>'},
	{'<','-','-','>'},
	{'<','-','>'},
	{'<','0','-','0','>'},
};

/// <summary>
/// Initializer of battleship
/// </summary>
battleship::battleship() {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

/// <summary>
/// Changes the cursor position in the console
/// </summary>
/// <param name="xx">Sets the x of cursor pos</param>
/// <param name="yy">Sets the y of cursor pos</param>
void battleship::setCursorPosition(int xx, int yy) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)xx, (SHORT)yy };
	SetConsoleCursorPosition(hOut, coord);
}

/// <summary>
/// Highlights text to a passed in color
/// </summary>
/// <param name="text"> The text to be highlighted</param>
/// <param name="color"> Color code to be highlighted</param>
void battleship::highlight(string text, int color) {
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, 7);
}

/// <summary>
/// Original Series of functions
/// </summary>
void battleship::bsmain() {
	startMenu();
	while (1) {
		print();
		centerShips();
		functionController();
		player++;
		saveGame();
	}
	while (flag) {
		startMenu();
		print();
		centerShips();
		functionController();
		saveGame();
	}
}

/// <summary>
/// This gets run at the start of the program
/// </summary>
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

/// <summary>
/// Sets every part of grid to a *
/// </summary>
void battleship::initGrid() {
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid[k][i][j] = '*';
			}
		}
	}
}

/// <summary>
/// Prints out the current players board
/// </summary>
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

/// <summary>
/// This directs the users controls to the right function
/// </summary>
void battleship::functionController() {
	bool flag = true;
	while (flag) {
	while (hits < 23) { //hits1 < 23 && hits2 < 23
		int input = _getch();
		if (input != 224) {
			if (!(ships[player%2][0] && ships[player%2][1] && ships[player%2][2] && ships[player%2][3] && ships[player%2][4] && ships[player%2][5])) {
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
					if (ships[player%2][0]) {
						place_pieces(1);
						ships[player%2][5] = false;
					}
					break;
				case KEY_TWO:
					if (ships[player%2][1]) {
						place_pieces(2);
						break;
					}
				case KEY_THREE:
					if (ships[player%2][2]) {
						place_pieces(3);
						break;
					}
				case KEY_FOUR:
					if (ships[player%2][3]) {
						place_pieces(4);
						break;
					}
				case KEY_FIVE:
					if (ships[player%2][4]) {
						place_pieces(5);
						flag = false;
						break;
					}
				}
			}
		}
	}
	win();
}

/// <summary>
/// Moves the cursor around the grid
/// </summary>
/// <param name="m">Takes a character for what dirction you want the cursor to move</param>
void battleship::move(char m) {
	setCursorPosition((x * 4) + 10, (y * 2) + 4);
	if (grid[player % 2][x][y] == '*') {
		highlight(string(1, grid[player % 2][x][y]), 7);
	}
	else if (grid[player % 2][x][y] == 'X')
		highlight(string(1, grid[player % 2][x][y]), 12);
	else if (grid[player % 2][x][y] == 'O')
		highlight(string(1, grid[player % 2][x][y]), 10);
	else
		highlight(string(1, grid[player % 2][x][y]), 14);
	switch (m) {
	case 'u':
		if (y > 0) {
			y--;
		}
			break;
	case 'd':
		if (y < 9) {
			y++;
		}
		break;
	case 'l':
		if (x > 0) {
			x--;
		}
		break;
	case 'r':
		if (x < 9) {
			x++;
		}
		break;
	}
	setCursorPosition((x * 4) + 10, (y * 2) + 4);
	if (grid[player % 2][x][y] == '*') {
		highlight(string(1, grid[player % 2][x][y]), 240);
	}
	else if (grid[player % 2][x][y] == 'X')
		highlight(string(1, grid[player % 2][x][y]), 192);
	else if (grid[player % 2][x][y] == 'O')
		highlight(string(1, grid[player % 2][x][y]), 160);
	else
		highlight(string(1, grid[player % 2][x][y]), 224);
}

/// <summary>
/// Centers the ships between the grids
/// </summary>
void battleship::centerShips() {
	setCursorPosition(54, 9);
	highlight("Ships", 14);
	for (int i = 0; i < 5; i++) {
		setCursorPosition(53, 11 + i);
		highlight(to_string(i + 1), 14);
		cout << " ";
		if (ships[player%2][i])
			highlight(pieces[i], 2);
		else
			highlight(pieces[i], 12);
	}

}

/// <summary>
/// Rotates a ship
/// </summary>
/// <param name="eks">X position of first part of the ship</param>
/// <param name="why">Y position of first part of the ship</param>
/// <param name="piece"></param>
/// <param name="color">The color for the ship to be highlighted</param>
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

/// <summary>
/// Places the pieces into the board and allows for the user to rotate them
/// </summary>
/// <param name="z">Determines the ship numebr</param>
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
						ships[player%2][z] = false;
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
						ships[player%2][z] = false;
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
						ships[player%2][z] = false;
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
						ships[player%2][z] = false;
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

/// <summary>
/// Saves the game board to be pulled up later
/// </summary>
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

/// <summary>
/// Pulls up a previously saved game board
/// </summary>
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

void battleship::hit() {
	if (grid[player % 2][x][y] != '*' && grid[player % 2][x][y] != 'X' && grid[player % 2][x][y] != 'O') {
		grid[player % 2][x][y] = 'X';
		setCursorPosition(x * 4 + 10, y * 2 + 4);
		highlight(string(1, 'X'), 12);
		hits++;
	}
	else if (grid[player % 2][x][y] == '*') {
		grid[player % 2][x][y] = 'O';
		setCursorPosition(x * 4 + 10, y * 2 + 4);
		highlight(string(1, 'O'), 10);
	}
}

// Add a hits1 and hits 2 functionality to this
void battleship::win() {
	if (hits > 23) {
		char loop;
		system("cls");
		setCursorPosition(0, 0);
		do {
			cout << "Player X won the game, successfully hitting all the opponenets ships!\nWould you like to play again?\ny : yes\nn : no\n> "; // Add player 1 and two
			cin >> loop;
			switch (loop) {
			case 'y':
				bsmain();
				break;
			case 'n':
				flag = false;
				break;
			default:
				break;
			}
		} while (loop != 'y' && loop != 'n');
	}
}

battleship::~battleship() {

}