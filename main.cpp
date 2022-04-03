#include <cstdlib>	//srand()
#include <iostream>	//cout
#include <ctime>	//time()
#include <cstring>	//strcmp()
#include <string>
#include "RSA.h"	//GenerateKeyPair()
#include "PrimeGenerator.h"	//Generate()
#include "keyPair.h"
#include "key.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

void genfilekey(unsigned long int digits);
void encryptFile(string fileName, string fileNamePublicKey);
void decryptFile(string fileName,string fileNamePrivateKey);

int main(int argc, char *argv[])
{
	std::srand(time(NULL));

	return 0;
	
}
