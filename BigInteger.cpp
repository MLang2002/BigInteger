#include"BigInteger.h"

void BigInteger::reform(void)
{
    while (s.size() > 1 && s[s.size() - 1] == 0)
        s.pop_back();
    if (s.size() == 0)
        s.push_back(0);
    if (s.size() == 1 && s[s.size() - 1] == 0)
        sign = true;
}

BigInteger::BigInteger(const BigInteger& b):sign(b.sign){ s.assign(b.s.begin(), b.s.end());}
BigInteger::BigInteger():sign(true){s.push_back(0);}
BigInteger::BigInteger(const string& str){*this=str.c_str();}
BigInteger::BigInteger(const char* str){*this=str;}
BigInteger::BigInteger(const int&num){*this=num;}
BigInteger::BigInteger(const long long& num) { *this = num; }
BigInteger& BigInteger::operator=(long long num)
{
    sign = num >= 0 ? true:false;
    long long number = num;
    number = abs(number);
    s.clear();
    do {
        s.push_back(number % base);
        number /= base;
    } while (number > 0);
    return *this;
}

BigInteger& BigInteger::operator=(const char* str)
{
    int numberpos = 0;
    int strlength = strlen(str);
    int devider = 0;
    sign = true;
    s.clear();
    while (numberpos < strlength)
    {
        if (str[numberpos] == '+')
            numberpos++;
        else if (str[numberpos] == '-')
        {
            numberpos++;
            sign = !sign;
        }
        else
            break;
    }
    for (int i = strlength - 1; i >= numberpos; i -= width)
    {
        devider = 0;
        for (int j = width - 1; j >= 0; j--)
            if (i - j >= numberpos)
                devider = devider * 10 + str[i - j] - '0';
        s.push_back(devider);
    }
    this->reform();
    return *this;
}

BigInteger& BigInteger::operator=(const string& str)
{
    *this = str.c_str();
    return *this;
}


BigInteger BigInteger::operator=(const int& num)
{
    *this = (long long)num;
    return *this;
}

ostream& operator<<(ostream& out, const BigInteger& x)
{
    if (!x.sign)
        out << '-';
    for (int i = x.s.size() - 1; i >= 0; i--)
        if (i == x.s.size() - 1)
            out << x.s[i];
        else
            out << setw(x.width) << setfill('0') << x.s[i];
    return out;
}

istream& operator>>(istream& in, BigInteger& x)
{
    string s;
    if (!(in >> s))
        return in;
    x = s;
    return in;
}

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs)
{
    if (lhs.sign ^ rhs.sign)
    {
        BigInteger negative;
        negative = lhs.sign ? rhs : lhs;
        negative.sign = true;
        return lhs.sign ? (lhs - negative) : (rhs - negative);
    }
    BigInteger sum;
    int carry = 0;
    sum = lhs;
    sum.s.resize(max(lhs.s.size(), rhs.s.size()) + 1, 0);
    for (int i = 0; i < (int)rhs.s.size(); ++i)
    {
        sum.s[i] += rhs.s[i] + carry;
        carry = sum.s[i] / sum.base;
        sum.s[i] %= sum.base;
    }
    if (carry != 0)
        sum.s[rhs.s.size()] += carry;
    sum.reform();
    sum.sign = lhs.sign;
    return sum;
}

BigInteger& BigInteger::operator+=(const BigInteger& rhs)
{
    *this = *this + rhs;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& rhs)
{
    *this = *this - rhs;
    return *this;
}

BigInteger& BigInteger::operator++()
{
    *this = *this + "1";
    return *this;
}

BigInteger& BigInteger::operator--()
{
    *this = *this - "1";
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger ret = *this;
    ++* this;
    return ret;
}
BigInteger BigInteger::operator--(int)
{
    BigInteger ret = *this;
    --* this;
    return ret;
}
BigInteger& BigInteger::operator*=(const BigInteger& rhs)
{
    *this = *this * rhs;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& rhs)
{
    *this=*this/rhs;
    return *this;
}

BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger a = lhs, b = rhs;
    a.sign = b.sign = true;
    BigInteger result, temp = a / b * b;
    result = a - temp;
    result.sign = lhs.sign;
    return result;
}

bool BigInteger::operator<(const BigInteger& b)const
{
    if (sign ^ b.sign)
        return b.sign;
    if (s.size() != b.s.size())
        return sign ? (s.size() < b.s.size()) : (s.size() > b.s.size());
    for (int i = s.size() - 1; i >= 0; i--)
        if (s[i] != b.s[i])
            return sign ? (s[i] < b.s[i]) : (s[i] > b.s[i]);
    return false;
}

bool BigInteger::operator>(const BigInteger& b)const
{
   return b < *this;
}
bool BigInteger::operator<=(const BigInteger& b)const
{
     return !(b < *this);
}
bool BigInteger::operator>=(const BigInteger& b)const
{
    return !(*this < b);
}
bool BigInteger::operator==(const BigInteger& b)const
{
    if (sign ^ b.sign)
        return false;
    if (s.size() != b.s.size())
        return false;
    for (int i = s.size() - 1; i >= 0; i--)
        if (s[i] != b.s[i])
            return false;
    return true;
}
bool BigInteger::operator!=(const BigInteger& b)const
{
    return !(b == *this);
}

BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger minuend = lhs, subtrahend = rhs;
    //(-a)-(-b)=b-a
    if (minuend.sign && !subtrahend.sign)
    {
        minuend.sign = true;
        subtrahend.sign = true;
        return subtrahend - minuend;
    }
    //a-(-b)=a+b
    else if (minuend.sign && !subtrahend.sign)
    {
        subtrahend.sign = true;
        return minuend + subtrahend;
    }
    //(-a)-b=-(a+b)
    else if (!minuend.sign && subtrahend.sign)
    {
        minuend.sign = true;
        BigInteger sum = minuend + subtrahend;
        sum.sign = false;
        return sum;
    }
    //a-b=-(b-a)
    else if (minuend < subtrahend)
    {
        BigInteger difference = subtrahend - minuend;
        difference.sign = false;
        return difference;
    }

    BigInteger difference = minuend;
    int borrow = 0;
    for (int i = 0; i < subtrahend.s.size(); ++i)
    {
        difference.s[i] -= subtrahend.s[i] + borrow;
        if (difference.s[i] >= 0)
            borrow = 0;
        else
        {
            borrow = 1;
            difference.s[i] += difference.base;
        }
    }
    if (borrow == 1)
        difference.s[subtrahend.s.size()]--;
    difference.reform();
    return difference;
}

BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger product;
    product.s.resize(lhs.s.size() + rhs.s.size(), 0);
    for (int i = 0; i < lhs.s.size(); ++i)
        for (int j = 0; j < rhs.s.size(); ++j)
        {
            product.s[i + j] += lhs.s[i] * rhs.s[j];
            product.s[i + j + 1] += product.s[i + j] / product.base;
            product.s[i + j] %= product.base;
        }
    product.reform();
    product.sign = rhs.sign == lhs.sign;
    return product;
}

BigInteger operator/(const BigInteger& divid, const BigInteger& divis)
{
    if (divid.s.size() - divis.s.size() + 1 <= 0 ||
        (divid.s.size() == 1 && divid.s[0] == 0) ||
        (divis.s.size() == 1 && divis.s[0] == 0))
    {
        BigInteger zero;
        return zero;
    }
    BigInteger quotient, partition, dividend = divid, divisor = divis;
    dividend.sign = divisor.sign = true;
    quotient.s.resize(divid.s.size() - divis.s.size() + 1, 0);
    int partitionbegin = divid.s.size() - 1;
    int partitionend = quotient.s.size() - 1;
    int factorleft, factorright, factor;
    string multiple = "1";
    while (partitionend >= 0)
    {
        partitionbegin = dividend.s.size() - 1;
        while (partitionbegin > 0 && dividend.s[partitionbegin] == 0)
            partitionbegin--;
        if (partitionend > partitionbegin)
            partitionend = partitionbegin;
        partition.s.assign(dividend.s.begin() + partitionend, dividend.s.begin() + partitionbegin + 1);
        if (partition < divisor)
        {
            partitionend--;
            continue;
        }

        factorleft = 1;
        factorright = quotient.base - 1;
        while (factorleft < factorright)
        {
            factor = (factorleft + factorright) / 2;
            if (factor * divisor <= partition)
                factorleft = factor + 1;
            else
                factorright = factor - 1;
        }
        while (factor * divisor < partition)
            factor++;
        while (factor * divisor > partition)
            factor--;
        quotient.s[partitionend] = factor;
        multiple.resize(partitionend * quotient.width + 1, '0');
        //BigInteger temp(multiple);
        dividend = dividend - multiple * divisor * factor;
        partitionend--;
    }
    quotient.reform();
    quotient.sign = divid.sign == divis.sign;
    return quotient;
}
BigInteger BigInteger::pow(const BigInteger& num)const
{
    BigInteger result = 1;
    for (BigInteger i = 0; i < num; ++i)
        result = result * (*this);
    return result;
}
BigInteger BigInteger::factorial()const
{
    BigInteger result = 1;
    for (BigInteger i = 1; i <= *this; ++i)
        result *= i;
    return result;
}
BigInteger BigInteger::Sqrt()const
{
    if (*this < 0)return -1;
    if (*this <= 1)return *this;
    BigInteger l = 0, r = *this, mid;
    while (r - l > 1)
    {
        mid = (l + r) / 2;
        if (mid * mid > *this)
            r = mid;
        else
            l = mid;
    }
    return l;
}




