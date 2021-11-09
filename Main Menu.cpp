#include"tictactoe.h"
#include"battleship.h"
#include "tetris.h"
#include<iostream>
using namespace std;

int main() {
	char menu;
	tictactoe t;
	battleship b;

	while (1) {
		cout << "Select an option\nt: TicTacToe\nb: BattleShip\n>";
		cin >> menu;
		switch (menu) {
		case 't': {
			t.tttmain();
			t = tictactoe();
			break;
		}
		case 'b': {
			cout << "Battleship\n";
			b.bsmain();
			break;
		}
		default: {
			cout << "Invalid option\n";
		}
		}
	}
	cout << "This is the main menu of tictactoe." << endl;
	system("pause");
	return EXIT_SUCCESS;
}