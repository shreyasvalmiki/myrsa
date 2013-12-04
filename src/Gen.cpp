//============================================================================
// Name        : Cryptography.cpp
// Author      : svalmiki
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "lib/Key.h"
using namespace std;

int main(int argc, char* argv[]) {
	Key key;
	if(argc < 4){
		cout << "Command not properly built. Needs 3 arguments: <Flag> <Public Key Filename> <Private Key Filename> \nFlags:\t-t: Textbook RSA KeyGen\n\t-o: OpenSSL KeyGen"<<endl;
	}
	else{
		if(strcmp(argv[1],"-t") == 0){
			key.generateKey(argv[2],argv[3]);
		}
		else if(strcmp(argv[1],"-o") == 0){
			key.generateKey(argv[2],argv[3],2048);
		}
	}

	return 0;
}
