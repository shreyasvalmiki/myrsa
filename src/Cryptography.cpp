//============================================================================
// Name        : Cryptography.cpp
// Author      : svalmiki
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "lib/Prime.h"
using namespace std;

int test() {
	Prime prime;
//	long a = 2;
//	long b = a<<1;
//	long c = 5;
//	bool d = ((c & 1) == 1);
//	long n = 221;
//	long s = 0;
//	long m;
//	for(m = n-1;!(m&1);++s,m>>=1)
//		;
//	cout <<"m="<<m<<endl;
//	long r=1;
//	a = 2;
//	long temp = a;
//	int i = 0;
//
//	while ( m ) {
//		if ( (m & 1) == 1 )
//			//r = (__int128_t)a*r % n; // Slow
//			r = a*r % n;
//		m >>= 1;
//		//a = (__int128_t)a*a % n; // SLow
//		a = a*a % n;
//	}
//	cout << "i="<<i<<endl;
//	cout << "r="<<a<<endl;
//	cout << "s="<<s<<endl;
//	cout <<"m="<<m<<endl;
//	cout <<d<<endl;
//	cout << b <<endl;
//	prime.setPrimes(1000,100000);
//	long p = prime.getRndPrime();
//	cout << "is "<<p<<" a prime: "<<prime.isPrime(p,3)<<endl;
//	cout << "is 4000 a prime: "<<prime.isPrime(4000,3)<<endl;
//	usleep(1000);
//	cout << prime.getRndPrime() << endl;  // prints !!!Hello World!!!

	cout <<prime.getPrime(100000000,900000000)*prime.getPrime(100000000,900000000)<<endl;
	cout <<prime.getPrime(100000000,900000000)<<endl;

	return 0;
}
