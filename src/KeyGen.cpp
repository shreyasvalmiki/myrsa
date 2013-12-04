//============================================================================
// Name        : Cryptography.cpp
// Author      : svalmiki
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "lib/Prime.h"
using namespace std;

int test(int argc, char* argv[]) {
	Prime prime;
	srand(time(NULL));
	long p,q,n,phi,e,d;
	ofstream sk,pk;
	p = prime.getPrime(1000,5000);
	q = prime.getPrime(1000,5000);
	n = p*q;
	phi = (p-1)*(q-1);
	e = rand()%(phi-1);
	while(prime.gcd(e,phi) != 1){
		e = rand()%(phi-1);
	}
	d = prime.inverseMod(e,phi);
	cout << argc << endl;
	if(argc < 3){
		sk.open("secret.key");
		sk << n << "\n";
		sk << d;
		sk.close();
		pk.open("public.key");
		pk << n << "\n";
		pk << e;
		pk.close();
	}
	else{
		sk.open(argv[1]);
		sk << n << "\n";
		sk << d;
		sk.close();
		pk.open(argv[2]);
		pk << n << "\n";
		pk << e;
		pk.close();
	}
	cout << "Done" << endl;
	return 0;
}
