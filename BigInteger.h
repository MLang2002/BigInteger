#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<stack>
#include<string>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<iosfwd>
#include<cmath>
#include<cstdlib>
#include<iomanip>
using namespace std;

class BigInteger{
private:
    static const int base = 10000;//equal to 10^_bit
    static const int width = 4;//compress bits£¬_bit
    vector<int> s;
    bool sign;//signal bit,>=0 is true(positive); <0 is false(negative)
    void reform();
public:
    BigInteger(const BigInteger& b);
    BigInteger();
    BigInteger(const string& str);
    BigInteger(const char* str);
    BigInteger(const int& num);
    BigInteger(const long long& num);
    ~BigInteger() = default;
    BigInteger& operator=(long long num);
    BigInteger& operator=(const char* str);
    BigInteger& operator=(const string& str);
    BigInteger operator=(const int& num);
    friend ostream& operator<<(ostream& out, const BigInteger& x);
    friend istream& operator>>(istream& in, BigInteger& x);
    friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
    BigInteger & operator+=(const BigInteger& rhs);
    BigInteger& operator-=(const BigInteger& rhs);
    BigInteger& operator++();
    BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);
    BigInteger& operator*=(const BigInteger& rhs);
    BigInteger& operator/=(const BigInteger& rhs);
    friend BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs);
    bool operator<(const BigInteger& b)const;
    bool operator>(const BigInteger& b)const;
    bool operator<=(const BigInteger& b)const;
    bool operator>=(const BigInteger& b)const;
    bool operator==(const BigInteger& b)const;
    bool operator!=(const BigInteger& b)const;
    friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator/(const BigInteger& divid, const BigInteger& divis);
    BigInteger pow(const BigInteger& num)const;
    BigInteger factorial()const;
    BigInteger Sqrt()const;

};



#endif
