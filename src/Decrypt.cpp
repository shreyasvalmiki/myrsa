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
#include <openssl/rsa.h>
#include "lib/RSA.h"
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
			myRSA.tbDecrypt(argv[2],argv[3],argv[4]);
		}
		else if(strcmp(argv[1],"-p") == 0){

			myRSA.osslDecrypt(argv[2],argv[3],argv[4],RSA_PKCS1_PADDING);
		}
		else if(strcmp(argv[1],"-o") == 0){

			myRSA.osslDecrypt(argv[2],argv[3],argv[4],RSA_PKCS1_OAEP_PADDING);
		}
		else{
			cout << "Enter the correct flag." <<endl;
		}
	}
	else{
		cout << "Command not properly built. Needs 4 arguments: <Flag> <Key Filename> <Cryptext Filename> <Plaintext Filename> \nFlags:\t-t: Textbook RSA Decryption\n\t-p: PKCS Padded Decryption\n\t-o: OAEP Padded Decryption"<<endl;
	}
	return 0;
}
