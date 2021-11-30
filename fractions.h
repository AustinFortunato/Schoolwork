#pragma once
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

void fractionadd(int a, int b, int c, int d, int *e, int *f) {
    *e = (a*d) + (b*c);
    *f = (b*d);
}

void fractionsub(int a, int b, int c, int d, int *e, int *f) {
    *e = (a*d) - (b*c);
    *f = (b*d);
}

void fractiondiv(int a, int b, int c, int d, int *e, int *f) {
    *e = a*d;
    *f = b*c;
}

void fractionply(int a, int b, int c, int d, int *e, int *f) {
    *e = a*c;
    *f = b*d;
}

void fractionsimp(int *a, int*b) {
    int d = gcd(*a, *b);
    *a = *a/d;
    *b = *b/d;
}