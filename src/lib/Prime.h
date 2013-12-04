/*
 * Prime.h
 *
 *  Created on: Nov 28, 2013
 *      Author: svalmiki
 */
#include <vector>
#ifndef PRIME_H_
#define PRIME_H_

class Prime {
private:
	std::vector<long> primes;
	bool millerRabinTest(long,int);
public:
	bool isPrime(long, int);
	void setPrimes(long,long);
	long getPrime(long,long);
	long gcd (long, long);
	long getRndPrime();
	long inverseMod(long,long);
	long powerMod(long,long,long);

	Prime();
	virtual ~Prime();
};

#endif /* PRIME_H_ */
