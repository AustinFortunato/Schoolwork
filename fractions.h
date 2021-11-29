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
    ~fractions();
};