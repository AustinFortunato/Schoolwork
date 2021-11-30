#pragma once
class fractions
{
public:
    fractions();
    void main();
    void fractionadd(int,int,int,int,int*,int*);
    void fractionsub(int,int,int,int,int*,int*);
    void fractionply(int,int,int,int,int*,int*);
    void fractiondiv(int,int,int,int,int*,int*);
    void fractionsimp(int*,int*);
    int gcd(int,int);
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
    ~fractions();
};