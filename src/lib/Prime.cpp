/*
 * Prime.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: svalmiki
 */

#include "Prime.h"
#include <cstdlib>
#include <ctime>
/**
 * Constructor
 */
Prime::Prime() {
	//Creating a random seed
	srand(time(NULL));
}

Prime::~Prime() {
	// TODO Auto-generated destructor stub
}

/**
 * Creates a list of primes
 * This function is unused as there are better methods to get primes
 * refer: getPrime
 */
void Prime::setPrimes(long start, long end){
	if(start<2){
		start = 2;
	}
	if(end < 2){
		end = 2;
	}
	if(end < start){
		end = end + start;
		start = end - start;
		end = end - start;
	}
	for(long i=start; i<=end; ++i){
		bool isPrime = true;
		for(long j=0; (unsigned)j<primes.size(); ++j){
			if(i%primes[j]==0){
				isPrime = false;
				break;
			}
		}
		if(isPrime){
			primes.push_back(i);
		}
	}
}

long Prime::getRndPrime(){

	return primes[rand()%primes.size()-1];
}

/**
 * Finding the modulo of the a^n using Euler's theorem
 * Ref: wikipedia.com, stackoverflow.com
 */
long Prime::powerMod(long a, long m, long n){
	long r = 1;
	while ( m ) {
		if ( (m & 1) == 1 )
			r = a*r % n;
		m >>= 1;
		a = a*a % n;
	}
	return r;
}

/**
 * Check if the number is prime using Miller-Rabin test
 * Ref: wikipedia.com, rosettacode.com
 */
bool Prime::isPrime(long n, int precision){
	long s = 0, d = 0, a = 0, x = 0;
	for(d = n-1; !(d&1); ++s, d>>=1);
	for(int i=0; i<precision; ++i){
		bool shouldContinue = false;
		a = rand()% n-1 + 2;
		x = powerMod(a,d,n);
		if(x == 1 || x == n-1){
			shouldContinue = true;
		}
		if(!shouldContinue){
			for(int r = 1; r < s; ++r){
				x = powerMod(x,2,n);
				if(x == 1)
					return false;
				else if(x == n-1){
					shouldContinue = true;
					break;
				}
			}
		}
		if(!shouldContinue){
			return false;
		}
	}
	return true;
}

long Prime::getPrime(long start, long end){
	if(start<2){
		start = 2;
	}
	if(end < 2){
		end = 2;
	}
	if(end < start){
		end = end + start;
		start = end - start;
		end = end - start;
	}

	long rnd = rand()%end + start;

	rnd = rnd%2 == 0 ? rnd - 1: rnd;

	while(!isPrime(rnd,3)){
		rnd -= 2;
	}
	return rnd;
}
/**
 * Gets the GCD of 2 numbers
 */
long Prime::gcd (long n1, long n2) {
	return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}
/**
 * Finds the inverse mod of a mod b with Extended Euclidean Method
 * Ref: comeoncodeon.wordpress.com
 */
long Prime::inverseMod(long a, long b){
	long b0 = b, t, q;
	long x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
