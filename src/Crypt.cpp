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
#include "lib/RSA.h"
#include "lib/Key.h"
using namespace std;

int main(int argc, char* argv[]) {

	//MyRSA myRSA;
//	SSLKey key;
//	key.generateKey("public.pem","private.pem",2048);


	MyRSA myRSA;
	char* key;
	char* iFile;
	char* oFile;

	key = "pub.pem";
	iFile = "message";
	oFile = "out.bin";
	myRSA.osslEncrypt(key,iFile,oFile,RSA_PKCS1_PADDING);

//	ifstream file("message");
//	char c;
//	vector<char> msg;
//	while(file >> noskipws >> c){
//		msg.push_back(c);
//	}
//	char* m = &msg[0];
//	cout << m <<endl;
	key = "pri.pem";
	iFile = "out.bin";
	oFile = "plaintext";
	myRSA.osslDecrypt(key,iFile,oFile,RSA_PKCS1_PADDING);
//	if(argc >= -5){
//		if(strcmp(argv[1],"-e") == 0){
//			myRSA.tbEncrypt(argv[2],argv[3],argv[4]);
//		}
//		//Decryption
//		else if(strcmp(argv[1],"-d") == 0){
//
//			myRSA.tbDecrypt(argv[2],argv[3],argv[4]);
//		}
//		else{
//			cout << "Enter the correct flag." <<endl;
//		}
//	}
	return 0;
}
