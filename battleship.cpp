#include "battleship.h"
#include<iostream>
#include<windows.h>
#include<string>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

HANDLE  hConsole;
int slct[2] = { 1,2 };

battleship::battleship() {
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid[k][i][j] = ';';
			}
		}
	}
}

void battleship::bsmain() {
	int player = 0;
	bool win = false;	
	highlightMove(player);
	/*do {
		print(player);
		player++;
	} while (win);*/
}

void battleship::highlight(string wurdz) {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 240);
	cout << wurdz;
	SetConsoleTextAttribute(hConsole, 7);
}

void battleship::highlightMove(int player) {
	int inpt;
	print(player);
	while (1) {
		inpt = _getch();
		switch (inpt) {
		case KEY_RIGHT:
			if (slct[1] < 9)
				slct[1]++;
			break;
		case KEY_LEFT:
			if (slct[1] > 0)
				slct[1]--;
			break;
		case KEY_UP:
			if (slct[0] > 0)
				slct[0]--;
			break;
		case KEY_DOWN:
			if (slct[0] < 9)
				slct[0] ++;
			break;
		default:
			break;
		}
		system("cls");
		print(0);
	}
}

void battleship::print(int player) {
	cout << "\n\nIt is player " << player + 1 << "'s turn.\n";
	cout << "|       | A | B | C | D | E | F | G | H | I | J |\t\t|       | A | B | C | D | E | F | G | H | I | J |\n";
	cout << "|-------|---|---|---|---|---|---|---|---|---|---|\t\t|-------|---|---|---|---|---|---|---|---|---|---|\n";
	for (int i = 0; i < 10; i++) {
		cout << "|   " << i+1 << "\t| ";
		for (int b1 = 0; b1 < 10; b1++) {
			if (i == slct[0] && b1 == slct[1]) {
				highlight(string(1, grid[player][i][b1]));
				//cout << grid[player][i][b1];
				cout << " | ";
			}
			else
				cout << grid[player][i][b1] << " | ";
		}
		cout << "\t\t" << "|   " << i+1 << "\t| ";
		for (int b2 = 0; b2 < 10; b2++) {
			cout << grid[player][i][b2] << " | ";
		}
		cout << "\n|-------|---|---|---|---|---|---|---|---|---|---|\t\t|-------|---|---|---|---|---|---|---|---|---|---|\n";
	}
}

void battleship::setships() {
	//cout << "<-0-->"
}

battleship::~battleship() {

}