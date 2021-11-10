#include"tictactoe.h"
#include"battleship.h"
#include "tetris.h"
#include<iostream>
#include<conio.h>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#define SELECTION_SIZE 4

using namespace std;

int main() {
	int menu;
    int y = 0;
    int get = 72;
    string selection[SELECTION_SIZE] = {"1: TicTacToe", "2: BattleShip", "3: Tetris", "4: Exit"};

    tictactoe ttt;
    battleship b;
    //tetris tet;

	while (1) {
        b.setCursorPosition(0,0);
		cout << "Select an option:\n";
        for(int index = 0; index < SELECTION_SIZE; index++) {
            cout << selection[index] << "\n";
        }
        b.setCursorPosition(0, y+1);
        b.highlight(selection[y], 112);
        while(get != 13) {
            get = _getch();
            if (get != 224) {
                b.setCursorPosition(0,y+1);
                switch (get) {
                    case 72: // Up
                        if (y > 0) {
                            b.highlight(selection[y], 7);
                            y--;
                            break;
                        }
                    case 80: // Down
                        if (y < SELECTION_SIZE - 1) {
                            b.highlight(selection[y], 7);
                            y++;
                            break;
                        }
                    case 13:
                        break;
                }
                b.setCursorPosition(0, y+1);
                b.highlight(selection[y], 112);
            }
        }
        switch (y+1) {
            case 1: {
                cout << "Battleship\n";
                ttt.main();
                ttt = tictactoe();
                break;
            }
            case 2: {
                cout << "Battleship\n";
                b.main();
                b = battleship();
                break;
            }
            case 3: {
                cout << "Tetris\n";
                break;
            }
            case 4: {
                cout << "Goodbye!\n";
                return EXIT_SUCCESS;
            }
            default: {
			cout << "Invalid option\n";
		    }
		}
	}
}
#pragma clang diagnostic pop