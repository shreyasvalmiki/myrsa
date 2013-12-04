/*
 * Key.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: svalmiki
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "Key.h"
#include "Prime.h"
/**
 * Constructor
 */
Key::Key() {
	if(SSL_library_init())
	{
		SSL_load_error_strings();
		OpenSSL_add_all_algorithms();
		RAND_load_file("/dev/urandom", 1024);
	}
	else
		exit(EXIT_FAILURE);
}

Key::~Key() {
}

/**
 * Handles OpenSSL Errors
 */
void Key::handleOpensslError(void)
{
	ERR_print_errors_fp(stderr);
}
/**
 * Builds the RSA Key
 */
EVP_PKEY* Key::createRSAKey(long size)
{
	RSA *pRSA;
	EVP_PKEY* pKey;
	pRSA = RSA_generate_key(size,RSA_3,NULL,NULL);
	pKey = EVP_PKEY_new();
	if(pRSA && pKey && EVP_PKEY_assign_RSA(pKey,pRSA))
	{
		/* pKey owns pRSA from now */
		if(RSA_check_key(pRSA) <= 0)
		{
			fprintf(stderr,"RSA_check_key failed.\n");
			handleOpensslError();
			EVP_PKEY_free(pKey);
			pKey = NULL;
		}
	}
	else
	{
		handleOpensslError();
		if(pRSA)
		{
			RSA_free(pRSA);
			pRSA = NULL;
		}
		if(pKey)
		{
			EVP_PKEY_free(pKey);
			pKey = NULL;
		}
	}
	return pKey;
}
/**
 * Textbook RSA Key Generation
 */
void Key::generateKey(std::string pubName, std::string priName){
	Prime prime;
	srand(time(NULL));
	long p,q,n,phi,e,d;
	std::ofstream sk,pk;
	p = prime.getPrime(1000,5000);
	q = prime.getPrime(1000,5000);
	n = p*q;
	phi = (p-1)*(q-1);
	e = rand()%(phi-1);
	//makes sure e is relatively prime to phi(n)
	while(prime.gcd(e,phi) != 1){
		e = rand()%(phi-1);
	}
	//Gets the inverse mod of e
	d = prime.inverseMod(e,phi);

	sk.open(priName.c_str());
	sk << n << "\n";
	sk << d;
	sk.close();
	pk.open(pubName.c_str());
	pk << n << "\n";
	pk << e;
	pk.close();

}

/**
 * OpenSSL Key Generation
 */
void Key::generateKey(std::string pubName, std::string priName, long keySize){
	size_t pri_len;            // Length of private key
	size_t pub_len;            // Length of public key
	char   *pri_key;           // Private key
	char   *pub_key;           // Public key

	EVP_PKEY* pPrivKey = createRSAKey(keySize);
	EVP_PKEY* pPubKey = pPrivKey;
	FILE *pFile;
	const EVP_CIPHER* pCipher = NULL;
	const char* pcszPassphrase = "open sesame";
	int iRet = EXIT_SUCCESS;
	if(pPrivKey && pPubKey)
	{
		//Save the keys
		if(pFile = fopen(priName.c_str(),"wt"))
		{

			if(!PEM_write_PrivateKey(pFile,pPrivKey,NULL,
					NULL,
					0,NULL,NULL))
			{
				fprintf(stderr,"PEM_write_PrivateKey failed.\n");
				handleOpensslError();
				iRet = EXIT_FAILURE;
			}
			fflush(pFile);
			fclose(pFile);
			pFile = NULL;
			if(iRet == EXIT_SUCCESS)
			{
				if((pFile = fopen(pubName.c_str(),"wt")) && PEM_write_PUBKEY(pFile,pPubKey)){
				}
				else
				{
					handleOpensslError();
					iRet = EXIT_FAILURE;
				}
				if(pFile)
				{
					fclose(pFile);
					pFile = NULL;
				}
			}
		}
		else
		{
			fprintf(stderr,"Cannot create key.\n");
			handleOpensslError();
			iRet = EXIT_FAILURE;
			if(pFile)
			{
				fclose(pFile);
				pFile = NULL;
			}
		}
	}
}
