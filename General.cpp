//Own a musket for home defense, since that's what the founding fathers intended. Four ruffians break into my house. "What the devil?" As I grab my powdered wig and Kentucky rifle. Blow a golf ball sized hole through the first man, he's dead on the spot. Draw my pistol on the second man, miss him entirely because it's smoothbore and nails the neighbors dog. I have to resort to the cannon mounted at the top of the stairs loaded with grape shot, "Tally ho lads" the grape shot shreds two men in the blast, the sound and extra shrapnel set off car alarms. Fix bayonet and charge the last terrified rapscallion. He Bleeds out waiting on the police to arrive since triangular bayonet wounds are impossible to stitch up. Just as the founding fathers intended.
#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<vector>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75

void highlight(string, int);
void initGrid();
void print();
void move();
void setCursorPosition(int,int);
void place_pieces();

char grid[10][10];
int x = 0;
int y = 0;

int main() {
	initGrid();
	print();
	move();
	place_pieces();
}

void highlight(string text, int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, 7);
}

void initGrid() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			grid[i][j] = '*';
		}
	}
}

void print() {
	for (int i = 0; i < 10; i++) {
		cout << "|---|---|---|---|---|---|---|---|---|---|\n| ";
		for (int j = 0; j < 10; j++) {
			cout << grid[i][j] << " | ";
		}
		cout << endl;
	}
	cout << "|---|---|---|---|---|---|---|---|---|---|\n";
}

void setCursorPosition(int x, int y){
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void move() {
	bool go = true;
	while (go) {
		int move = _getch();
		if (move!=224) {
			switch (move) {
			case KEY_UP:
				if (y > 0) {
					setCursorPosition((x*4)+2,(y*2)+1);
					cout << grid[x][y];
					y--;
					setCursorPosition((x*4)+2,(y*2)+1);
					highlight(string(1,grid[x][y]), 240); 
				}
				break;
			case KEY_DOWN:
				if (y < 9) {
					setCursorPosition((x*4)+2,(y*2)+1);
					cout << grid[x][y];
					y++;
					setCursorPosition((x*4)+2,(y*2)+1);
					highlight(string(1,grid[x][y]), 240); 
				}
				break;
			case KEY_LEFT:
				if (x > 0) {
					setCursorPosition((x*4)+2,(y*2)+1);
					cout << grid[x][y];
					x--;
					setCursorPosition((x*4)+2,(y*2)+1);
					highlight(string(1,grid[x][y]), 240); 
				}
				break;
			case KEY_RIGHT:
				if (x < 9) {
					setCursorPosition((x*4)+2,(y*2)+1);
					cout << grid[x][y];
					x++;
					setCursorPosition((x*4)+2,(y*2)+1);
					highlight(string(1,grid[x][y]), 240); 
				}
				break;
			case 13:
				setCursorPosition(0,22);
				go = false;
				break;
			}
		}
	}
}

void place_pieces() {
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
		grid[y][x+i] = pieces[x-1][i];
		setCursorPosition(((x+i)*4)+2,(y*2)+1);
		highlight(string(1,grid[y][x+i]), 50);
	}
	setCursorPosition(30,30);
}
