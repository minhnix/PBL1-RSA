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
void exitError(const char *message = "\0")
{
	cout << message << endl;
	std::exit(EXIT_FAILURE);
}

void missingArgumentError(const char *argName)
{
	cout << "Missing argument: '" << argName << "'." << endl;
	exitError();
}

void genfilekey(unsigned long int digits) 
{
	cout << "Generating key...";
	KeyPair newKeyPair(RSA::GenerateKeyPair(digits));
	FILE * filePublic = NULL; 
	FILE * filePrivate = NULL;
	filePublic = fopen("publickey.txt", "w");
	filePrivate = fopen("privatekey.txt", "w"); 
	string n = newKeyPair.GetPublicKey().GetModulus().ToString();
	string e = newKeyPair.GetPublicKey().GetExponent().ToString();
	string d = newKeyPair.GetPrivateKey().GetExponent().ToString();
	fputs(n.c_str(), filePublic);
	fputs("\n", filePublic);
	fputs(e.c_str(),filePublic);
	fputs(n.c_str(), filePrivate);
	fputs("\n", filePrivate);
	fputs(d.c_str(),filePrivate);
	fclose(filePublic);fclose(filePrivate);
	cout << "\nDone! Please check files...";
}

void encryptFile(string fileName, string fileNamePublicKey)
{
    try
	{
		char arr[201];
		FILE * fp = NULL; 
		fp = fopen(fileNamePublicKey.c_str(), "r"); 
		int i;
		fgets(arr, 200, fp);
		for (i = 0;i < 200 ;i++) {
			if (arr[i] == '\n' ) break;
		}
		arr[i] = '\0';
		BigInt n(arr);
		fgets(arr, 200, fp);
		for (i = 0; i< 200;i++) {
			if (arr[i] == '\n' ) break;
		}
		arr[i] = '\0';
		BigInt e(arr);
		fclose(fp);
		Key publicKey(n,e);
		char* messageFile = (char*)fileName.c_str();
		char cypherFile[] = "cyphertext.txt";
        cout << "\n" << "Encrypting the file: " << "\"" << fileName << "\"" << " ... \n";
        RSA::Encrypt(messageFile,cypherFile,publicKey);
        cout << "Done!\nEncrypted the file '" << fileName << "' to file '" << cypherFile <<"'";
    }
	catch (const char errorMessage[])
	{
		exitError(errorMessage);
	}
	catch (...)
	{
		exitError("Unknown error.");
	}
}

void decryptFile(string fileName,string fileNamePrivateKey)
{
    try
	{
		char arr[201];
		FILE * fp = NULL; 
		fp = fopen(fileNamePrivateKey.c_str(), "r"); 
		int i;
		fgets(arr, 200, fp);
		for (i = 0;i < 200 ;i++) {
			if (arr[i] == '\n' ) break;
		}
		arr[i] = '\0';
		BigInt n(arr);
		fgets(arr, 200, fp);
		for (i = 0; i< 200;i++) {
			if (arr[i] == '\n' ) break;
		}
		arr[i] = '\0';
		BigInt d(arr);
		fclose(fp);
		Key privateKey(n,d);
		
		char* cypherFile = (char*) fileName.c_str();
		// FILE * fp = NULL; 
		// fp = fopen(cypherFile, "a"); 
		// fputc(' ', fp);
		char destFile[] = "new_message.txt";
        cout << "\n" << "Decrypting the message: " << "\"" << fileName << "\"" << " ... \n";
        RSA::Decrypt(cypherFile, destFile, privateKey);
        cout << "Done!\nDecrypted the file '" << cypherFile << "' to file '" << destFile <<"'"; 
    }
	catch (const char errorMessage[])
	{
		exitError(errorMessage);
	}
	catch (...)
	{
		exitError("Unknown error.");
	}
}
