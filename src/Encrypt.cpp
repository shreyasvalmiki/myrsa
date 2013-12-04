//============================================================================
// Name        : Cryptography.cpp
// Author      : svalmiki
// Version     :
// Copyright   : Your copyright notice
// Description : RSA Encryption
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "lib/RSA.h"
#include <openssl/rsa.h>
using namespace std;
/**
 * This is for all types of encryptions:
 * -t : Textbook RSA
 * -p : padded RSA with PKCS1
 * -o : OAEP
 */
int main(int argc, char* argv[]) {
	MyRSA myRSA;

	if(argc >= 5){
		if(strcmp(argv[1],"-t") == 0){
			myRSA.tbEncrypt(argv[2],argv[3],argv[4]);
		}
		else if(strcmp(argv[1],"-p") == 0){

			myRSA.osslEncrypt(argv[2],argv[3],argv[4],RSA_PKCS1_PADDING);
		}
		else if(strcmp(argv[1],"-o") == 0){

			myRSA.osslEncrypt(argv[2],argv[3],argv[4],RSA_PKCS1_OAEP_PADDING);
		}
		else{
			cout << "Enter the correct flag." <<endl;
		}
	}
	else{
		cout << "Command not properly built. Needs 4 arguments: <Flag> <Key Filename> <Message Filename> <Cryptext Filename> \nFlags:\t-t: Textbook RSA Encryption\n\t-p: PKCS Padded Encryption\n\t-o: OAEP Padded Encryption"<<endl;
	}
	return 0;
}
