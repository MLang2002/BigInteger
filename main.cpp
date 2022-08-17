#include"BigInteger.h"

int main(void)
{
	using namespace BigInt_Vector;
	BigInteger a("00123");
	BigInteger b("003");
	cout << a/b << endl;
	BigInteger c("000123");
	cout << c << endl;
	return 0;
}