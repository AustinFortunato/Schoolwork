#include <iostream>
#include <fractions.h>
#include <conio.h>
using namespace std;

fractions::fractions() = default;

void fractions::main() {
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
    int waste = 0;
    cout << "PRESS ANY KEY TO CONTINUE";
    _getch();
}

int fractions::gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

void fractions::fractionadd(int a, int b, int c, int d, int *e, int *f) {
    *e = (a*d) + (b*c);
    *f = (b*d);
}

void fractions::fractionsub(int a, int b, int c, int d, int *e, int *f) {
    *e = (a*d) - (b*c);
    *f = (b*d);
}

void fractions::fractiondiv(int a, int b, int c, int d, int *e, int *f) {
    *e = a*d;
    *f = b*c;
}

void fractions::fractionply(int a, int b, int c, int d, int *e, int *f) {
    *e = a*c;
    *f = b*d;
}

void fractions::fractionsimp(int *a, int*b) {
    int d = gcd(*a, *b);
    *a = *a/d;
    *b = *b/d;
}

fractions::~fractions() = default;