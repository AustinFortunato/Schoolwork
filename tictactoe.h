#pragma once
class tictactoe
{
public:
	tictactoe();
	void tttmain();
	char grid[3][3];
	void print();
	int move(int,int);
	int check(int, int);
	~tictactoe();
private:

protected:

};

