//Own a musket for home defense, since that's what the founding fathers intended. Four ruffians break into my house. "What the devil?" As I grab my powdered wig and Kentucky rifle. Blow a golf ball sized hole through the first man, he's dead on the spot. Draw my pistol on the second man, miss him entirely because it's smoothbore and nails the neighbors dog. I have to resort to the cannon mounted at the top of the stairs loaded with grape shot, "Tally ho lads" the grape shot shreds two men in the blast, the sound and extra shrapnel set off car alarms. Fix bayonet and charge the last terrified rapscallion. He Bleeds out waiting on the police to arrive since triangular bayonet wounds are impossible to stitch up. Just as the founding fathers intended.
#include"battleship.h"
#include<windows.h>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
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

bool ships[2][6] = { {1,1,1,1,1,0}, {1,1,1,1,1,0} };
int x = 0;
int y = 0;
int player = 0;
int r = -1;
int hitsOne = 0;
int hitsTwo = 0;
int playerOffset = 0;
int hitInt = 0;
bool flag = true;

char pieces[5][7] = {
	{'<','-','-','0','-','>'},
	{'<','-','-','-','>'},
	{'<','-','-','>'},
	{'<','-','>'},
	{'<','0','-','0','>'},
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/// <summary>
/// Initializes and sets global variables to default values
/// </summary>
battleship::battleship() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	x=0,y=x,player=x,hitsOne=x,hitsTwo=x,playerOffset=x,hitInt=x;
	r = -1;
	flag = true;
	for (auto & ship : ships) {
		for (int i = 0; i < 5; i++) {
			ship[i] = true;
		}
		ship[5] = false;
	}
}

/// <summary>
/// Changes the cursor position in the console
/// </summary>
/// <param name="xx">Sets the x of cursor pos</param>
/// <param name="yy">Sets the y of cursor pos</param>
void battleship::setCursorPosition(int xx, int yy) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
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
	while (flag) {
		print();
		centerShips();
		functionController();
		player++;
	}
	saveGame();
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
		for (int h = 0; h < 2; h++) {
			for (int i = 0; i < 5; i++) {
				ships[h][i] = true;
			}
			ships[h][5] = false;
		}

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
		for (int j = 0; j < 2; j++) {
			cout << "|   " << i + 1 << "\t| ";
			for (int b1 = 0; b1 < 10; b1++) {
				switch (grid[player % 2+(2*j)][b1][i]) {
					case '*':
						cout << grid[player % 2+(2*j)][b1][i];
						break;
					case 'X':
						highlight("X", 12);
						break;
					case 'O':
						highlight("O", 10);
						break;
					default:
						highlight(string(1, grid[player % 2+(2*j)][b1][i]), 14);
						break;
				}
				cout << " | ";
			}
			cout << "\t\t";
		}
		cout << "|-------|---|---|---|---|---|---|---|---|---|---|\t\t|-------|---|---|---|---|---|---|---|---|---|---|\n";
	}
}

/// <summary>
/// This directs the users controls to the right function
/// </summary>
void battleship::functionController() {
    bool flagF = 1;
	while (flagF) { //hits1 < 23 && hits2 < 23
		int input = _getch();
		if (input != 224) {
		    // TODO Make rotate auto place when r is pressed.
			if (!(ships[player % 2][0] && ships[player % 2][1] && ships[player % 2][2] && ships[player % 2][3] && ships[player % 2][4] && ships[player % 2][5])) {
			    switch (input) {
				case KEY_UP:
					move('u', hitInt);
					break;
				case KEY_DOWN:
					move('d', hitInt);
					break;
				case KEY_LEFT:
					move('l', hitInt);
					break;
				case KEY_RIGHT:
					move('r', hitInt);
					break;
				case KEY_ONE:
					if (ships[player % 2][0]) {
						place_pieces(1);
						ships[player % 2][5] = false;
                        flagF = (ships[player%2][0] || ships[player%2][1] || ships[player%2][2] || ships[player%2][3] || ships[player%2][4]);
					}
					break;
				case KEY_TWO:
					if (ships[player % 2][1]) {
						place_pieces(2);
						ships[player % 2][5] = false;
                        flagF = (ships[player%2][0] || ships[player%2][1] || ships[player%2][2] || ships[player%2][3] || ships[player%2][4]);
					}
					break;
				case KEY_THREE:
					if (ships[player % 2][2]) {
						place_pieces(3);
						ships[player % 2][5] = false;
                        flagF = (ships[player%2][0] || ships[player%2][1] || ships[player%2][2] || ships[player%2][3] || ships[player%2][4]);
					}
					break;
				case KEY_FOUR:
					if (ships[player % 2][3]) {
						place_pieces(4);
						ships[player % 2][5] = false;
                        flagF = (ships[player%2][0] || ships[player%2][1] || ships[player%2][2] || ships[player%2][3] || ships[player%2][4]);
					}
					break;
				case KEY_FIVE:
					if (ships[player % 2][4]) {
						place_pieces(5);
						ships[player % 2][5] = false;
                        flagF = (ships[player%2][0] || ships[player%2][1] || ships[player%2][2] || ships[player%2][3] || ships[player%2][4]);
					}
					break;
				case KEY_H:
					for (int h = 0; h < 2; h++) {
						for (int i = 0; i < 5; i++) {
							if (ships[h][i] == false) {
								hit();
								flagF = false;
								Sleep(40);
							}
						}
					}
					x = 0,y=x;
				}
                if (player % 2 && !flagF) {
                    hitInt = 64;
                    playerOffset = 2;
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
void battleship::move(char m, int xOffSet) {
	setCursorPosition((x * 4) + xOffSet + 10, (y * 2) + 4);
	if (grid[player % 2 + playerOffset][x][y] == '*') {
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 7);
	}
	else if (grid[player % 2 + playerOffset][x][y] == 'X')
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 12);
	else if (grid[(player + 1) % 2][x][y] == 'O')
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 10);
	else
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 14);
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
	setCursorPosition((x * 4) + xOffSet + 10, (y * 2) + 4);
	if (grid[player % 2 + playerOffset][x][y] == '*') {
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 240);
	}
	else if (grid[player % 2 + playerOffset][x][y] == 'X')
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 192);
	else if (grid[(player + 1) % 2][x][y] == 'O')
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 160);
	else
		highlight(string(1, grid[player % 2 + playerOffset][x][y]), 224);
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
		if (ships[player % 2][i])
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

/// <summary>
/// Checks to see if a path is clear
/// </summary>
/// <param name="eks"></param> X of the start path
/// <param name="why"></param> Y of the start path
/// <returns></returns>
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
						ships[player % 2][z] = false;
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
						ships[player % 2][z] = false;
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
						ships[player % 2][z] = false;
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
					if (lastLine[0] != 0 || lastLine[1] != 0) {
						rotate(x + lastLine[0] * i, y + lastLine[1] * i, '*', 7);
					}
					if (grid[player % 2][x][y] == '*' || set) {
						rotate(x, y - i, pieces[z][i], 14);
						ships[player % 2][z] = false;
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
/// lets a player hit an opponents ships
/// </summary>
void battleship::hit() {
	hitInt = 64;
	playerOffset = 2;
	if (grid[(player + 1) % 2][x][y] != '*' && grid[(player + 1) % 2][x][y] != 'X' && grid[(player + 1) % 2][x][y] != 'O') {
		grid[player % 2 + playerOffset][x][y] = 'X';
		grid[(player + 1) % 2][x][y] = 'X';
		setCursorPosition(x * 4 + 74, y * 2 + 4);
		highlight(string(1, 'X'), 12);
		switch (player % 2) {
		case 0:
			hitsOne++;
			break;
		case 1:
			hitsTwo++;
			break;
		}
	}
	else if (grid[(player + 1) % 2][x][y] == '*') {
		grid[player % 2 + playerOffset][x][y] = 'O';
		grid[(player + 1) % 2][x][y] = 'O';
		setCursorPosition(x * 4 + 74, y * 2 + 4);
		highlight(string(1, 'O'), 10);
	}
}

/// <summary>
/// Allows a player to win then it will loop the program
/// </summary>
void battleship::win() {
	if (hitsOne == 23 || hitsTwo == 23) {
		char loop;
		system("cls");
		setCursorPosition(0, 0);
		for (int h = 0; h < 2; h++) {
			for (int i = 0; i < 5; i++) {
				ships[h][i] = true;
			}
			ships[h][5] = false;
		}
		flag = true;
		r = -1;
		x, y, player, hitsOne, hitsTwo, playerOffset, hitInt = 0;
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

/// <summary>
/// Saves the game board to be pulled up later
/// </summary>
void battleship::saveGame() {
	string fName = "save.txt";
	fstream save;
	save.open(fName, ios::out);
	if (save.is_open()) {
		for (auto & a : grid) {
			for (int b = 0; b < 10; b++) {
				for (auto & c : a) {
					save << c[b] << ' ';
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
		for (auto & a : grid) {
			for (int b = 0; b < 10; b++) {
				for (auto & c : a) {
					save >> c[b];
				}
			}
		}
	}
	save.close();
}

battleship::~battleship() {

}