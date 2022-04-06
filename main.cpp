#include <cstdlib>	//srand()
#include <iostream>	//cout
#include <cstring>	//strcmp()
#include <string>
#include "RSA.h"	//GenerateKeyPair()
#include "keyPair.h"
#include "key.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

void genfilekey(unsigned long int digits);
void encryptFile(string fileName, string fileNamePublicKey);
void decryptFile(string fileName,string fileNamePrivateKey);
void MENU();

int main(int argc, char *argv[])
{
	std::srand(time(NULL));
	MENU();
	return 0;
	
}
void exitError(const char *message = "\0")
{
	cout << message << endl;
	// std::exit(EXIT_FAILURE);
	// return;
}

void missingArgumentError(const char *argName)
{
	cout << "Missing argument: '" << argName << "'." << endl;
	exitError();
}

void genfilekey(unsigned long int digits) 
{
	cout << "\nGenerating key...";
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
	cout << "\nDone! Please check files 'publickey.txt' and 'privatekey.txt'\n";
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
		if (arr[0] < '0' || arr[0] > '9') {
			cout << "cannot open file '"<< fileNamePublicKey << "', please check your filename\n";
			return;
		}
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
        cout << "\nEncrypting the file: " << "\"" << fileName << "\"" << " ... \n";
        RSA::Encrypt(messageFile,cypherFile,publicKey);
        cout << "Done!\nEncrypted the file '" << fileName << "' to file '" << cypherFile <<"'\n";
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
		if (arr[0] < '0' || arr[0] > '9') {
			cout << "cannot open file '"<< fileNamePrivateKey << "', please check your filename\n";
			return;
		}
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
		char destFile[] = "new_message.txt";
        cout << "\n" << "Decrypting the message: " << "\"" << fileName << "\"" << " ... \n";
        RSA::Decrypt(cypherFile, destFile, privateKey);
        cout << "Done!\nDecrypted the file '" << cypherFile << "' to file '" << destFile <<"'\n"; 
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
void encryptfile(){
	std::string key;
    std::string fileName,filePublicKey;
	cout<<"Enter the file name to be encrypted: ";
    cin>>fileName;
	cout<<"Enter the public key filename: ";
	cin>>filePublicKey;
	encryptFile(fileName,filePublicKey);
}
void newfilekey(){
	unsigned long int n;
	cout<<"Enter the key length (10 <= N <= 100): ";
	cin>>n;
	while (n<10||n>100){
		cout<<"Please enter again: ";
		cin>>n;
	} 
	genfilekey(n);
}
void decryptfile(){
    std::string fileName,filenamePrivatekey;
	cout<<"Enter the file name to be decrypted: ";
	cin>>fileName;
	cout<<"Enter the private key filename: ";
	cin>>filenamePrivatekey;
	decryptFile(fileName,filenamePrivatekey);// mã hóa text
}
void MENU(){
    bool key=true;
    int i,dcr=1;
    while(key==true){
        cout<<"\nMENU PROGRAM\n\n";
		cout<<"1: Generate key\n";
		cout<<"2: Encrypt file\n";
		cout<<"3: Decrypt file\n";
		cout<<"4: Exit\n";
        cout<<"Enter your selection: ";
        cin>>i;
        switch (i){
        case 1:
			newfilekey();
			cout << "\nDo you want to continue?\n";
			cout << "0: No\n1: Yes\nEnter your selection: ";
			cin >> dcr;
            break;
        case 2:
			encryptfile();
			cout << "\nDo you want to continue?\n";
			cout << "0: No\n1: Yes\nEnter your selection: ";
			cin >> dcr;
            break;
        case 3:
			decryptfile();
			cout << "\nDo you want to continue?\n";
			cout << "0: No\n1: Yes\nEnter your selection: ";
			cin >> dcr;
            break;
    	default:
			key=false;
            break;
        }
		if (dcr == 0) break;
    }
}