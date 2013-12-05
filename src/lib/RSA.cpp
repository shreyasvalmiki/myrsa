/*
 * MyRSA.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: svalmiki
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <string.h>
#include "RSA.h"
#include "Prime.h"
#include "Key.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>

using namespace std;




/**
 * Constructor
 */
MyRSA::MyRSA() {

	//Initialize OpenSSL
	if(SSL_library_init())
	{
		SSL_load_error_strings();
		OpenSSL_add_all_algorithms();
		RAND_load_file("/dev/urandom", 1024);
	}
	else
		exit(EXIT_FAILURE);

}

MyRSA::~MyRSA() {
}

/**
 * Handles OpenSSL Errors
 */
void MyRSA::handleOpensslError(void)
{
	ERR_print_errors_fp(stderr);
}


/**
 * Gets the key for the textbook RSA from the given filename
 */
TBKey MyRSA::getTbKey(char* filename){
	TBKey key;
	std::string line;
	std::ifstream file(filename);
	std::getline(file,line);
	key.n = atol(line.c_str());
	std::getline(file,line);
	key.key = atol(line.c_str());
	file.close();
	return key;
}

/**
 * Encrypts the message with naive RSA
 */
vector<long> MyRSA::tbEncrypt(vector<char> msg, TBKey key){
	std::vector<long> crypt;
	Prime prime;
	//Gets m^e mod n for each character.
	for(unsigned int i=0; i<msg.size(); ++i){
		crypt.push_back(prime.powerMod(msg[i],key.key,key.n));
	}
	return crypt;
}

/**
 * Saves the encrypted message in the file
 */
void MyRSA::tbEncrypt(char* kFilename, char* mFilename, char* oFilename){
	std::ifstream keyFile,mFile;
	std::ofstream oFile;
	vector<char> msg;
	vector<long> crypt;
	Prime prime;
	TBKey key = getTbKey(kFilename);

	oFile.open(oFilename);
	mFile.open(mFilename);
	char c;
	while(mFile >> noskipws >> c){
		msg.push_back(c);
	}
	mFile.close();

	crypt = tbEncrypt(msg,key);
	//
	for(unsigned int i=0; i<crypt.size(); ++i){
		oFile << crypt[i] << " ";
	}
}
/**
 * Decrypts the encrypted message
 */
vector<char> MyRSA::tbDecrypt(vector<long> crypt, TBKey key){
	vector<char> msg;
	Prime prime;
	//gets c^d mod n
	for(int i=0; i<crypt.size(); ++i){
		msg.push_back((char)prime.powerMod(crypt[i],key.key,key.n));
	}
	return msg;
}
/**
 * Decrypts the message and saves it in a file
 */
void MyRSA::tbDecrypt(char* kFilename, char* mFilename, char* oFilename){
	std::ifstream keyFile,mFile;
	std::ofstream oFile;
	vector<char> msg;
	vector<long> crypt;
	Prime prime;
	TBKey key = getTbKey(kFilename);

	oFile.open(oFilename);
	mFile.open(mFilename);
	long c;
	while(mFile >> c){
		crypt.push_back(c);
	}
	mFile.close();

	msg = tbDecrypt(crypt,key);

	for(unsigned int i=0; i<msg.size(); ++i){
		oFile << msg[i];
	}
}

/**
 * Checks the size of the message to validate whether it can be encrypted
 */
bool MyRSA::checkMessageSize(long len,long keySize, int type){
	bool isValid = true;
	switch(type){
	case RSA_PKCS1_PADDING:
		if(len >= (keySize - 41))
		{
			isValid = false;
		}
		break;
	case RSA_PKCS1_OAEP_PADDING:
		if(len >= (keySize - 41))
		{
			isValid = false;
		}
		break;
	default:
		if(len >= keySize)
		{
			isValid = false;
		}
		break;
	}
	return isValid;
}

/**
 * gets the contents of the file
 */
vector<char> MyRSA::readFromFile(char* mFilename){
	ifstream file(mFilename);
	char c;
	vector<char> msg;
	while(file >> noskipws >> c){
		msg.push_back(c);
	}
	return msg;
}

string MyRSA::getEncryptedText(char* keyFilename, char* mFilename, char* cFilename, int type){
	FILE * keyFile = fopen(keyFilename,"rb");
	RSA *key;
	char *err;
	int retval = 0;
	int iRet = 0;
	FILE * pFile;

	RSA* pPubKey;
	const char* pcszPassphrase = "open sesame";

	if((pFile = fopen(keyFilename,"rt")) &&
			(pPubKey= PEM_read_RSA_PUBKEY(pFile,NULL,NULL,NULL))){
	}
	else
	{
		fprintf(stderr,"Cannot read \"pubkey.pem\".\n");
		handleOpensslError();
		iRet = EXIT_FAILURE;
	}
	if(pFile)
		fclose(pFile);

	size_t result;
	FILE *mFile = fopen(mFilename,"r");
	fseek (mFile , 0 , SEEK_END);
	//Gets size of the message file
	long lSize = ftell (mFile);
	rewind (mFile);
	char* buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("ERROR: Memory error",stderr); exit (2);}

	result = fread (buffer,sizeof(char),lSize,mFile);
	buffer[lSize] = '\0';
	if (result != lSize) {fputs ("ERROR: Reading error",stderr); exit (3);}
	fclose(mFile);
	//Checks message length
	if(checkMessageSize(lSize,RSA_size(pPubKey),type)){
		unsigned char * encrypt = (unsigned char*) malloc(RSA_size(pPubKey));
		//Encrypt the message
		int temp = RSA_public_encrypt(lSize, (unsigned char*)buffer, (unsigned char*)encrypt, pPubKey, type);
		if(!temp){
			ERR_load_crypto_strings();
			ERR_error_string(ERR_get_error(), err);
			fprintf(stderr, "ERROR: Error encrypting message: %s\n", err);
		}
		string s(reinterpret_cast<char*>(encrypt));
		return s;
	}
	return "";

}
string MyRSA::getDecryptedText(char* keyFilename, char* mFilename, char* cFilename, int type){
	FILE * keyFile = fopen(keyFilename,"r");
	RSA *key;
	char *err;
	int retval = 0;
	int iRet = 0;
	FILE * pFile;

	RSA* pPrivKey = NULL;
	const char* pcszPassphrase = "open sesame";

	if((pFile = fopen(cFilename,"r")) && (pPrivKey = PEM_read_RSAPrivateKey(keyFile,NULL,NULL,NULL))){
	}
	else
	{
		fprintf(stderr,"Cannot read \"privkey.pem\".\n");
		handleOpensslError();
		iRet = EXIT_FAILURE;
	}
	if(pFile)
		fclose(pFile);

	size_t result;
	FILE *cFile = fopen(cFilename,"r");
	fseek (cFile , 0 , SEEK_END);
	long lSize = ftell (cFile);
	rewind (cFile);
	char* buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
	//char *buffer = &readFromFile(cFilename)[0];
	result = fread (buffer,1,lSize,cFile);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

	buffer[lSize] = '\0';

	fclose(cFile);
	unsigned char * decrypt = (unsigned char*) malloc(RSA_size(pPrivKey));
	int temp;
	//Decrypt the message
	temp = RSA_private_decrypt(lSize, (unsigned char*)buffer, (unsigned char*)decrypt, pPrivKey , type);

	if(!temp){
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), err);
		fprintf(stderr, "Error decrypting message: %s\n", err);
	}
	char c = decrypt[0];
	string s(reinterpret_cast<char*>(decrypt));
	return s;

}


/**
 * OpenSSL encryption
 *
 * Ref: OpenSSL.org, stackoverflow.com, cplusplus.com
 */
void MyRSA::osslEncrypt(char* keyFilename, char* mFilename, char* cFilename, int type){

	string s = getEncryptedText(keyFilename, mFilename, cFilename, type);
	if(s.compare("") != 0){

		FILE *oFile = fopen(cFilename,"w");
		//Save it in a file
		fwrite (s.c_str() , sizeof(char), s.length(), oFile);
		fclose(oFile);
	}
	else{
		fprintf(stderr,"ERROR: Message too long to encrypt\n");
	}

}

/**
 * OpenSSL Decryption
 *
 * Ref: OpenSSL.org, stackoverflow.com, cplusplus.com
 */
void MyRSA::osslDecrypt(char* keyFilename, char* cFilename, char* mFilename, int type){
	string s = getDecryptedText(keyFilename, mFilename, cFilename, type);
	FILE *oFile = fopen(mFilename,"w");
	//Save the decrypted message in the file
	fwrite (s.c_str() , sizeof(char),s.length(), oFile);
	fclose(oFile);
}
