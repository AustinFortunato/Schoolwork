#include"tictactoe.h"
#include"battleship.h"
#include"fractions.h"
#include"general.h"
#include "lunchLine.h"
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#define SELECTION_SIZE 6

using namespace std;
class activeGame
{
public:
    activeGame();
    void main();
    char get_char(float);
    void printGrid();
    void draw(int[4][4], int, int, bool);
    void setCursorPosition(int, int);
    void purgeGrid();
    void printHold(int);
    void lineBreak();
    void dropDown(int);
    void highlight(const string&, int);
    void shadow(int[4][4], int, int);
    void placePiece(int[4][4], int, int);
    int canMove(int[4][4], int, int);
    int dropPiece(int[4][4][4]);
    ~activeGame();
};

void fraction();

int main() {
    int y = 0;
    int get = 72;
    string selection[SELECTION_SIZE] = {"1: TicTacToe", "2: BattleShip", "3: Tetris", "4: Fractions", "5: Lunch Line", "5: Exit"};

    tictactoe ttt;
    battleship b;
    activeGame tet;
    general gen;
    lunchLine lunch;

    while (1) {
        system("cls");
        gen.setCursorPosition(0,0);
        cout << "Select an option:\n";
        for(int index = 0; index < SELECTION_SIZE; index++) {
            cout << selection[index] << "\n";
        }
        gen.setCursorPosition(0, y+1);
        gen.highlight(selection[y], 112);
        get = 0;
        while(get != 13) {
            get = _getch();
            if (get != 224) {
                gen.setCursorPosition(0,y+1);
                switch (get) {
                    case 72: // Up
                        if (y > 0) {
                            gen.highlight(selection[y], 7);
                            y--;
                            break;
                        }
                    case 80: // Down
                        if (y < SELECTION_SIZE - 1) {
                            gen.highlight(selection[y], 7);
                            y++;
                            break;
                        }
                    case 13:
                        break;
                }
                gen.setCursorPosition(0, y+1);
                gen.highlight(selection[y], 112);
            }
        }
        system("Cls");
        switch (y+1) {
            case 1: {
                cout << "Tic Tac Toe\n";
                ttt.main();
                ttt = tictactoe();
                break;
            }
            case 2: {
                b.main();
                b = battleship();
                break;
            }
            case 3: {
                tet.main();
                tet = activeGame();
                break;
            }
            case 4: {
                fraction();
                break;
            }
            case 5: {
                lunch.main();
                lunch = lunchLine();
                break;
            };
            case 6: {
                cout << "Goodbye!\n";
                return EXIT_SUCCESS;
            }
            default: {
                cout << "Invalid option\n";
            }
        }
    }
}

int pieceT[4][4][4] = {
        0,5,0,0,
        5,5,5,0,
        0,0,0,0,
        0,0,0,0,

        0,5,0,0,
        0,5,5,0,
        0,5,0,0,
        0,0,0,0,

        0,0,0,0,
        5,5,5,0,
        0,5,0,0,
        0,0,0,0,

        0,5,0,0,
        5,5,0,0,
        0,5,0,0,
        0,0,0,0
};

int pieceJ[4][4][4] = {
        1,0,0,0,
        1,1,1,0,
        0,0,0,0,
        0,0,0,0,

        0,1,1,0,
        0,1,0,0,
        0,1,0,0,
        0,0,0,0,

        0,0,0,0,
        1,1,1,0,
        0,0,1,0,
        0,0,0,0,

        0,1,0,0,
        0,1,0,0,
        1,1,0,0,
        0,0,0,0
};

int pieceL[4][4][4] = {
        0,0,6,0,
        6,6,6,0,
        0,0,0,0,
        0,0,0,0,

        0,6,0,0,
        0,6,0,0,
        0,6,6,0,
        0,0,0,0,

        0,0,0,0,
        6,6,6,0,
        6,0,0,0,
        0,0,0,0,

        6,6,0,0,
        0,6,0,0,
        0,6,0,0,
        0,0,0,0,
};

int pieceO[4][4][4] = {
        14,14,0,0,
        14,14,0,0,
        0,0,0,0,
        0,0,0,0,

        14,14,0,0,
        14,14,0,0,
        0,0,0,0,
        0,0,0,0,

        14,14,0,0,
        14,14,0,0,
        0,0,0,0,
        0,0,0,0,

        14,14,0,0,
        14,14,0,0,
        0,0,0,0,
        0,0,0,0,
};

int pieceI[4][4][4] = {
        0,0,0,0,
        11,11,11,11,
        0,0,0,0,
        0,0,0,0,

        0,0,11,0,
        0,0,11,0,
        0,0,11,0,
        0,0,11,0,

        0,0,0,0,
        0,0,0,0,
        11,11,11,11,
        0,0,0,0,

        0,11,0,0,
        0,11,0,0,
        0,11,0,0,
        0,11,0,0
};

int pieceZ[4][4][4] = {
        12,12,0,0,
        0,12,12,0,
        0,0,0,0,
        0,0,0,0,

        0,0,12,0,
        0,12,12,0,
        0,12,0,0,
        0,0,0,0,

        0,0,0,0,
        12,12,0,0,
        0,12,12,0,
        0,0,0,0,

        0,12,0,0,
        12,12,0,0,
        12,0,0,0,
        0,0,0,0
};

int pieceS[4][4][4] = {
        0,2,2,0,
        2,2,0,0,
        0,0,0,0,
        0,0,0,0,

        0,2,0,0,
        0,2,2,0,
        0,0,2,0,
        0,0,0,0,

        0,0,0,0,
        0,2,2,0,
        2,2,0,0,
        0,0,0,0,

        2,0,0,0,
        2,2,0,0,
        0,2,0,0,
        0,0,0,0
};

int grid[24][10] = { 0 };
int tmpGrid[24][10] = { 0 };
int holdGrid[4][4][4] = { 0 };

int hold;
int lines = 0;
float stage = 1;
int points = 0;

activeGame::activeGame() {
    grid[24][10] = { 0 };
    tmpGrid[24][10] = { 0 };
    holdGrid[4][4][4] = { 0 };
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = 0;
            tmpGrid[i][j] = 0;
        }
    }

    hold;
    lines = 0;
    stage = 1;
    points = 0;
}

void activeGame::main() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    printGrid();

    srand(time(0));
    int f = 0;
    bool win = true;
    while (win) {
        int r = 1 + (rand() % 7);
        if (r != f) {
            switch (r) {
                case 1:
                    dropPiece(pieceT);
                    break;
                case 2:
                    dropPiece(pieceZ);
                    break;
                case 3:
                    dropPiece(pieceO);
                    break;
                case 4:
                    dropPiece(pieceL);
                    break;
                case 5:
                    dropPiece(pieceI);
                    break;
                case 6:
                    dropPiece(pieceS);
                    break;
                case 7:
                    dropPiece(pieceJ);
                    break;
            }
        }
        lineBreak();
        f = r;
    }

    setCursorPosition(0, 25);
    system("pause");
}
char activeGame::get_char(float time_limit) {
    time_t start = clock();
    while (!kbhit()) {
        if ((clock() - start) >= time_limit)
            return -1;
    }
    return getch();
}

void activeGame::printGrid() {
    for (auto& i : grid) {
        highlight(string(1, char(254)) + " ", 8);
        for (int j : i) {
            if (j == 0) {
                cout << ' ';
            }
            else {
                highlight(string(1, char(254)), j);
            }
            cout << ' ';
        }
        highlight(string(1, char(254)), 8);
        cout << "\n";
    }
    highlight(string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + "\n", 8);
    printHold(1);
    setCursorPosition(1, 25);
    cout << "Lines: " << lines << " | Points: " << points;
}

void activeGame::draw(int piece[4][4], int x, int y, bool hghlt) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece[j][i] && y + j < 24) {
                setCursorPosition((x * 2 + i * 2) + 2, y + j);
                if (hghlt)
                    highlight(string(1, char(254)), piece[j][i]);
                else
                    cout << string(1, char(254));
                tmpGrid[y + j][x + i] = 1;
            }
        }
    }
}

void activeGame::purgeGrid() {
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 10; j++) {
            if (tmpGrid[i][j] && !grid[i][j]) {
                setCursorPosition(j * 2 + 2, i);
                cout << ' ';
            }
        }
    }
}

void activeGame::setCursorPosition(int xx, int yy) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)xx, (SHORT)yy };
    SetConsoleCursorPosition(hOut, coord);
}

int activeGame::canMove(int piece[4][4], int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((grid[y + i][x + j] && piece[i][j]) || (piece[i][j] && y + i > 23)) {
                return 0;
            }
            else if ((piece[i][j] && x + j > 9) || (piece[i][j] && x + j < 0)) {
                return 0;
            }
        }
    }
    return 1;
}

void activeGame::placePiece(int piece[4][4], int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece[i][j]) {
                grid[y + i - 1][x + j] = piece[i][j];
            }
        }
    }
}

int activeGame::dropPiece(int piece[4][4][4]) {
    int x = 3;
    int r = 0;
    bool run = true;
    bool runtwo = false;

    for (int i = 0; i < 25; i++) {
        if (i > 0 && run) {
            switch (get_char(float(1000.0 / (stage * 0.75)))) {
                case 'a':
                    if (canMove(piece[r % 4], x - 1, i - 1)) {
                        x--;
                        i--;
                    }
                    break;
                case 'd':
                    if (canMove(piece[r % 4], x + 1, i - 1)) {
                        x++;
                        i--;
                    }
                    break;
                case 'r':
                    if (canMove(piece[(r + 1) % 4], x, i - 1)) {
                        r++;
                        i--;
                    }
                    break;
                case 's':
                    break;
                case 'w':
                    run = false;
                    break;
                case 32:
                    if (hold) {
                        dropPiece(holdGrid);
                    }
                    else {
                        hold = true;
                    }
                    for (int w = 0; w < 4; w++) {
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                holdGrid[w][j][i] = piece[w][j][i];
                            }
                        }
                    }
                    printHold(r % 4);
                    return 0;
            }
        }
        if (canMove(piece[r % 4], x, i)) {
            purgeGrid();
            shadow(piece[r % 4], x, i);
            draw(piece[r % 4], x, i, true);
        }
        else if (i == 0 && !canMove(piece[r % 4], x, i)) {
            setCursorPosition(25, 26);
            cout << "You lost!";
            _getch();
            system("cls");
            break;
        }
        else {
            if (runtwo) {
                placePiece(piece[r % 4], x, i);
                runtwo = false;
                break;
            }
            else {
                i--;
                runtwo = true;
            }
        }
    }
    stage = (ceil((points + 1) / 10) + 1);
    return 0;
}

void activeGame::printHold(int x) {
    setCursorPosition(25, 0);
    highlight(string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " ", 8);
    for (int i = 0; i < 4; i++) {
        setCursorPosition(25, 1 + i);
        highlight(string(1, char(254)) + " ", 8);
        for (int j = 0; j < 4; j++) {
            if (holdGrid[x][i][j]) {
                highlight(string(1, char(254)) + " ", holdGrid[x][i][j]);
            }
            else {
                cout << "  ";
            }
        }
        highlight(string(1, char(254)), 8);
    }
    setCursorPosition(25, 5);
    highlight(string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " " + string(1, char(254)) + " ", 8);
}

void activeGame::lineBreak() {
    int ekses = 0;
    int brokenLines[4] = { 0 };
    int tmp = 0;

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j]) {
                ekses++;
            }
        }

        if (ekses == 10) {
            for (int& brokenLine : brokenLines) {
                if (!brokenLine) {
                    tmp++;
                    brokenLine = i;
                    break;
                }
            }
        }
        ekses = 0;
    }

    if (tmp == 1)
        points += 2;
    else if (tmp == 2)
        points += 5;
    else if (tmp == 3)
        points += 9;
    else if (tmp == 4)
        points += 16;

    for (int brokenLine : brokenLines) {
        if (brokenLine) {
            dropDown(brokenLine);
        }
    }
}

void activeGame::dropDown(int level) {
    for (int j = level; j > 0; j--) {
        for (int i = 0; i < 10; i++) {
            grid[j][i] = grid[j - 1][i];
        }
    }
    lines++;
    system("cls");
    printGrid();
}

void activeGame::highlight(const string& text, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    cout << text;
    SetConsoleTextAttribute(hConsole, 7);
}

void activeGame::shadow(int piece[4][4], int eks, int why) {
    int final = 0;
    for (int i = 0; i < 24; i++) {
        if (!canMove(piece, eks, i) && i > why) {
            final = i - 1;
            break;
        }
    }
    draw(piece, eks, final, false);
}

activeGame::~activeGame() = default;

void fraction() {
    int a,b,c,d,e,f;
    char choice;
    cout << "FRACTION ONE:\nNumerator > ";
    cin >> a;
    cout << "\nDenominator > ";
    cin >> b;
    cout << "\nFRACTION TWO:\nNumerator > ";
    cin >> c;
    cout << "\nDenominator > ";
    cin >> d;
    cout << "ADD (a) SUBTRACT (s) MULTIPLY (m) DIVIDE (d)";
    cin >> choice;
    if (b==0 || a==0) {
        a = 0;
        b = 1;
    }
    if (d==0 || c==0) {
        c = 0;
        d = 1;
    }

    switch (choice) {
        case 'a':
            fractionadd(a,b,c,d,&e,&f);
            fractionsimp(&e, &f);
            break;
        case 's':
            fractionsub(a,b,c,d,&e,&f);
            fractionsimp(&e, &f);
            break;
        case 'm':
            fractionply(a,b,c,d,&e,&f);
            fractionsimp(&e, &f);
            break;
        case 'd':
            fractiondiv(a,b,c,d,&e,&f);
            fractionsimp(&e, &f);
            break;
    }
    if (e==f)
        cout << e << endl;
    else if (e >= 0 && f < 0) {
        cout << e*-1 << "/" << f*-1 << endl;
    } else
        cout << e << "/" << f << endl;
    cout << "PRESS ANY KEY TO CONTINUE";
    _getch();
}
