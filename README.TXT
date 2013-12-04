Project by: Shreyas Valmiki

Project Topic: RSA KeyGen/Encryption/Decryption

Types covered:

	Textbook RSA: No external libraries used to build this
	Padded RSA: OpenSSL used for key generation and PKCS1 used for padding
	OAEP RSA: OpenSSL used for key generation and OAEP used for padding


Usage:

OS to be run on: Linux

Key Generation:

./keygen:

Needs 3 arguments: <Flag> <Public Key Filename> <Private Key Filename> 
Flags:	-t: Textbook RSA KeyGen
	-o: OpenSSL KeyGen: 2048 bit key


./encrypt:

Needs 4 arguments: <Flag> <Key Filename> <Message Filename> <Cryptext Filename> 
Flags:	-t: Textbook RSA Encryption
	-p: PKCS Padded Encryption
	-o: OAEP Padded Encryption


./decrypt:
Needs 4 arguments: <Flag> <Key Filename> <Cryptext Filename> <Plaintext Filename> 
Flags:	-t: Textbook RSA Decryption
	-p: PKCS Padded Decryption
	-o: OAEP Padded Decryption



Constraints:

1. Textbook RSA has no constraints on file size. Encryption/Decryption is done on every character in the text like a stream cipher.
2. OAEP and Padded RSA has a constraint in file size. The file size is equal to (key size)/8


Performance report will be provided in the final submission.
All the code is commented for ease of understanding. References are also mentioned.

All the executables are in bin directory in the root directory.

