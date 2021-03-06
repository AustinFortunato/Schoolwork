//Own a musket for home defense, since that's what the founding fathers intended. Four ruffians break into my house. "What the devil?" As I grab my powdered wig and Kentucky rifle. Blow a golf ball sized hole through the first man, he's dead on the spot. Draw my pistol on the second man, miss him entirely because it's smoothbore and nails the neighbors dog. I have to resort to the cannon mounted at the top of the stairs loaded with grape shot, "Tally ho lads" the grape shot shreds two men in the blast, the sound and extra shrapnel gen.set off car alarms. Fix bayonet and charge the last terrified rapscallion. He Bleeds out waiting on the police to arrive since triangular bayonet wounds are impossible to stitch up. Just as the founding fathers intended.
#include"battleship.h"
#include "general.h"
#include<windows.h>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
using namespace std;

general gen;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_ONE 49
#define KEY_TWO 50
#define KEY_THREE 51
#define KEY_FOUR 52
#define KEY_FIVE 53
#define KEY_H 104
#define KEY_S 115

bool ships[2][6] = { {1,1,1,1,1,0}, {1,1,1,1,1,0} };
int x = 0,y=0,player=0,hitsOne=0,hitsTwo=0,playerOffSet=0,hitInt=0;
int r = -1;
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
/// Initializes and gen.sets global variables to default values
/// </summary>
battleship::battleship() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	x=0,y=x,player=x,hitsOne=x,hitsTwo=x,playerOffSet=x,hitInt=x;
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
/// Original Series of functions
/// </summary>
void battleship::main() {
	startMenu();
	while (flag) {
		print();
		centerShips();
		functionController();
		player++;
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
/// gen.sets every part of grid to a *
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
	gen.highlight("\t\tYour ships.", 10);
	gen.highlight("\t\t\t PLAYER " + to_string(player % 2 + 1) + "'S TURN", 13);
	gen.highlight("\t\tTheir ships\n", 12);
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
						gen.highlight("X", 12);
						break;
					case 'O':
						gen.highlight("O", 10);
						break;
					default:
						gen.highlight(string(1, grid[player % 2+(2*j)][b1][i]), 14);
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
						flagF = (ships[player % 2][0] || ships[player % 2][1] || ships[player % 2][2] || ships[player % 2][3] || ships[player % 2][4]);
					}
					break;
				case KEY_TWO:
					if (ships[player % 2][1]) {
						place_pieces(2);
						ships[player % 2][5] = false;
						flagF = (ships[player % 2][0] || ships[player % 2][1] || ships[player % 2][2] || ships[player % 2][3] || ships[player % 2][4]);
					}
					break;
				case KEY_THREE:
					if (ships[player % 2][2]) {
						place_pieces(3);
						ships[player % 2][5] = false;
						flagF = (ships[player % 2][0] || ships[player % 2][1] || ships[player % 2][2] || ships[player % 2][3] || ships[player % 2][4]);
					}
					break;
				case KEY_FOUR:
					if (ships[player % 2][3]) {
						place_pieces(4);
						ships[player % 2][5] = false;
						flagF = (ships[player % 2][0] || ships[player % 2][1] || ships[player % 2][2] || ships[player % 2][3] || ships[player % 2][4]);
					}
					break;
				case KEY_FIVE:
					if (ships[player % 2][4]) {
						place_pieces(5);
						ships[player % 2][5] = false;
						flagF = (ships[player % 2][0] || ships[player % 2][1] || ships[player % 2][2] || ships[player % 2][3] || ships[player % 2][4]);
					}
					break;
				case KEY_H:
				    if (flagF) {
                        hit();
                        flagF = false;
                        Sleep(300);
                    }
				    break;
				case KEY_S:
					system("cls");
					gen.setCursorPosition(0, 0);
					saveGame();
                    char s[15] = {'S', 'A','V','I','N','G',' ','G','A','M','E','.','.','.'};
					for (int i = 1; i < 16; i++) {
					    for (int j = 0; j < 15; j++) {
                            gen.highlight(&s[j], i);
                            system("cls");
                        }
					}
					gen.highlight("SAVED!", 6);
					Sleep(950);
					exit(3);
				}
                if (player % 2 && !flagF) {
                    hitInt = 64;
                    playerOffSet = 2;
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
	gen.setCursorPosition((x * 4) + xOffSet + 10, (y * 2) + 4);
	if (grid[player % 2 + playerOffSet][x][y] == '*') {
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 7);
	}
	else if (grid[player % 2 + playerOffSet][x][y] == 'X')
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 12);
	else if (grid[(player + 1) % 2][x][y] == 'O')
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 10);
	else
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 14);
	switch (m) {
	case 'u':
	    y > 0 ? y-- : y;
		break;
	case 'd':
	    y < 9 ? y++ : y;
		break;
	case 'l':
	    x > 0 ? x-- : x;
		break;
	case 'r':
	    x < 9 ? x++ : x;
		break;
	}
	gen.setCursorPosition((x * 4) + xOffSet + 10, (y * 2) + 4);
	if (grid[player % 2 + playerOffSet][x][y] == '*') {
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 240);
	}
	else if (grid[player % 2 + playerOffSet][x][y] == 'X')
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 192);
	else if (grid[(player + 1) % 2][x][y] == 'O')
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 160);
	else
		gen.highlight(string(1, grid[player % 2 + playerOffSet][x][y]), 224);
}

/// <summary>
/// Centers the ships between the grids
/// </summary>
void battleship::centerShips() {
	gen.setCursorPosition(54, 9);
	gen.highlight("Ships", 14);
	for (int i = 0; i < 5; i++) {
		gen.setCursorPosition(53, 3 + i);
		gen.highlight(to_string(i + 1), 14);
		cout << " ";
		if (ships[player % 2][i])
			gen.highlight(pieces[i], 2);
		else
			gen.highlight(pieces[i], 12);
	}
	gen.setCursorPosition(50,9);
	gen.highlight("Arrow Keys to",9);
	gen.setCursorPosition(55,10);
	gen.highlight("Move.",9);
	gen.setCursorPosition(50,12);
	gen.highlight("Numbers (1-5)", 9);
	gen.setCursorPosition(50,13);
	gen.highlight("to place ship",9);
	gen.setCursorPosition(52,15);
	gen.highlight("R to rotate",9);
	gen.setCursorPosition(53,17);
	gen.highlight("H to hit",9);
	gen.setCursorPosition(52,19);
	gen.highlight("S to Save.", 13);
}

/// <summary>
/// Rotates a ship
/// </summary>
/// <param name="eks">X position of first part of the ship</param>
/// <param name="why">Y position of first part of the ship</param>
/// <param name="piece"></param>
/// <param name="color">The color for the ship to be gen.highlighted</param>
void battleship::rotate(int eks, int why, char piece, int color) {
	if (eks > -1 && eks < 10 && why > -1 && why < 10) {
		grid[player % 2][eks][why] = piece;
		gen.setCursorPosition(eks * 4 + 10, why * 2 + 4);
		gen.highlight(string(1, piece), color);
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
	gen.setCursorPosition(0, 24);
	z--;
	int size = strlen(pieces[z]);
	bool set = false;
	int lastLine[2] = { 0,0 };
	do {
	    r = 0;
	    bool breakCon = true;
        while (breakCon && r < 10) {
            r++;
            switch (r % 4) {
                case 0: // x positive
                    if (pathfinder(size, 0)) {
                        breakCon = false;
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
                    } else {
                        r++;
                    }
                case 1: // y positive
                    if (pathfinder(0, size)) {
                        breakCon = false;
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
                    } else {
                        r++;
                    }
                case 2: // x negative
                    if (pathfinder(-size, 0)) {
                        breakCon = false;
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
                    } else {
                        r++;
                    }
                case 3: // y negative
                    if (pathfinder(0, -size)) {
                        breakCon = false;
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
    while (_getch() == 'r');
}

/// <summary>
/// lets a player hit an opponents ships
/// </summary>
void battleship::hit() {
	hitInt = 64;
	playerOffSet = 2;
	if (grid[(player + 1) % 2][x][y] != '*' && grid[(player + 1) % 2][x][y] != 'X' && grid[(player + 1) % 2][x][y] != 'O') {
		grid[player % 2 + playerOffSet][x][y] = 'X';
		grid[(player + 1) % 2][x][y] = 'X';
		gen.setCursorPosition(x * 4 + 74, y * 2 + 4);
		gen.highlight(string(1, 'X'), 12);
        player % 2 ? hitsOne++ : hitsTwo++;
	}
	else if (grid[(player + 1) % 2][x][y] == '*') {
		grid[player % 2 + playerOffSet][x][y] = 'O';
		grid[(player + 1) % 2][x][y] = 'O';
		gen.setCursorPosition(x * 4 + 74, y * 2 + 4);
		gen.highlight(string(1, 'O'), 10);
	} else if (grid[(player+1) % 2][x][y] == 'X' || grid[(player+1)%2][x][y] == 'O') {
	    player--;
	}
}

/// <summary>
/// Allows a player to win then it will loop the program
/// </summary>
void battleship::win() {
	if (hitsOne == 23 || hitsTwo == 23) {
		char loop;
		system("cls");
		gen.setCursorPosition(0, 0);
		for (int h = 0; h < 2; h++) {
			for (int i = 0; i < 5; i++) {
				ships[h][i] = true;
			}
			ships[h][5] = false;
		}
		flag = true;
		r = -1;
		x=0, y=x, player=x, hitsOne=x, hitsTwo=x, playerOffSet=x, hitInt=x;
		do {
			cout << "Player X won the game, successfully hitting all the opponenets ships!\nWould you like to play again?\ny : yes\nn : no\n> "; // Add player 1 and two
			cin >> loop;
			switch (loop) {
			case 'y':
				main();
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
