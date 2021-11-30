#pragma once
#include <iostream>
class battleship
{
public:
	battleship();
	void main();
	void startMenu();
	char grid[4][10][10];
	void print();
	void move(char,int);
	void place_pieces(int);
	void initGrid();
	void centerShips();
	void rotate(int, int, char, int);
	void functionController();
	bool pathfinder(int, int);
	void hit();
	void win();
	void saveGame();
	void loadGame();
	~battleship();
private:
protected:
};

