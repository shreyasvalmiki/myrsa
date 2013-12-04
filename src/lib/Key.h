/*
 * Key.h
 *
 *  Created on: Dec 1, 2013
 *      Author: svalmiki
 */
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string>
#ifndef KEY_H_
#define KEY_H_

class Key {
public:
	Key();
	virtual ~Key();
	void generateKey(std::string, std::string);
	void generateKey(std::string, std::string, long);
	EVP_PKEY* createRSAKey(long);
	void handleOpensslError(void);
};

#endif /* KEY_H_ */
