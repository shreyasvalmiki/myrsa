/*
 * RSA.h
 *
 *  Created on: Nov 29, 2013
 *      Author: svalmiki
 */

#ifndef RSA_H_
#define RSA_H_
#include <vector>

class TBKey{
public:
	long n, key;
};
class MyRSA {
private:
	TBKey getTbKey(char*);

public:
	MyRSA();
	virtual ~MyRSA();
	std::vector<long> tbEncrypt(std::vector<char>,TBKey);
	std::vector<char> tbDecrypt(std::vector<long>,TBKey);
	void tbEncrypt(char*,char*,char*);
	void tbDecrypt(char*,char*,char*);
	void osslEncrypt(char*,char*,char*,int);
	void osslDecrypt(char*,char*,char*,int);
	std::vector<char> readFromFile(char*);
	void handleOpensslError(void);
	int* passwdCallback(char *pcszBuff,int size,int rwflag, void *pPass);
	bool checkMessageSize(long,long,int);
};

#endif /* RSA_H_ */
