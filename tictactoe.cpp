#include "tictactoe.h"
#include<conio.h>
#include<iostream>
using namespace std;

tictactoe::tictactoe()
{
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			grid[x][y] = ' ';
		}
	}
}

void tictactoe::main() {
	int x = 2;
	int movez = 0;
	int player = 2;
	char playagain = 'y';
	cout << "\n\t=====================\n\tWelcome to tictactoe!\n\t=====================\n\n";
	while (playagain != 'n') {
		do {
			print();
			movez += move(player, movez);
			x = check(movez, player);
			player++;
		} while (x == 2);
		cout << "Would you like to play again? y/n\n";
		cin >> playagain;
		player = 2;
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				grid[x][y] = ' ';
				movez = 0;
			}
		}
	}
}

void tictactoe::print() {
	int j = 7;
	cout << "\t   Board\t       Numpad\n";
	for (int i = 0; i < 3; i++) {
		cout << "\t  " << grid[0][i] << " | " << grid[1][i] << " | " << grid[2][i] << "\t     " << j << " | " << j + 1 << " | " << j + 2 << endl;
		if (i < 2) {
			cout << "\t ---|---|---\t    ---|---|---\n";
		}
		j -= 3;
	}
	cout << endl;
}

//make move char, tie condition
int tictactoe::move(int player, int movesz) {
	char move;
	int moves[9][2] = { {1,3},{2,3},{3,3},{1,2},{2,2},{3,2},{1,1},{2,1},{3,1} };
	char pieces[2] = { 'X', 'O' };
	cout << "Player " << (player % 2) + 1 << ">";
	move = _getch();
	int movea = move - '0';
	if (grid[moves[movea - 1][0] - 1][moves[movea - 1][1] - 1] == ' ') {
		grid[moves[movea - 1][0] - 1][moves[movea - 1][1] - 1] = pieces[player % 2];
		movesz++;
	}
	else {
		cout << "You cannot move there!\n";
		tictactoe::move(player, movesz);
	}
	return 1;
}

int tictactoe::check(int movez, int player) {
	for (int i = 0; i < 3; i++) {
		if ((grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ')
			|| (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ')
			|| (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[1][1] != ' ')
			|| (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && grid[1][1] != ' ')) {
			print();
			cout << "Player " << player % 2 + 1 << " Wins!\n\n";
			return 0;
		}
		else if (movez >= 9) {
			cout << "Tie! Neither players win.\n"; // Tie
			return 1;
		}
	}
	cout << movez;
	print();
	return 2;
}

tictactoe::~tictactoe()
{
}
