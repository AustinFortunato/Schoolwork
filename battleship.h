#pragma once
#include <iostream>
class battleship
{
public:
	battleship();
	void bsmain();
	char grid[4][10][10];
	void print();
	void highlight(std::string, int);
	void move();
	void place_pieces();
	void setCursorPosition(int, int);
	void initGrid();
	void centerShips();
	~battleship();
private:
protected:
};

