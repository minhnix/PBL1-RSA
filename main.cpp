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
	std::exit(EXIT_FAILURE);
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
	cout << "\nDone! Please check files...\n";
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
		if (arr[0] < '0' || arr[0] > '9') exitError("cannot open file, please check your filename");
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
		if (arr[0] < '0' || arr[0] > '9') exitError("cannot open file, please check your filename");
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
	cout<<"NHAP FILE BAN CAN MA HOA\n";
	cout<<"BAN CO THE SU DUNG FILE message.txt HOAC NHAP DUONG DAN DEN FILE CAN MA HOA:\n";
    cin>>fileName;
	cout<<"\n-------------------------------------------------------------------------------------------------\n";
	cout<<"NHAP FILE CHUA PUBLICKEY\n";
	cout<<"BAN CO THE SU DUNG FILE publickey.txt HOAC NHAP DUONG DAN DEN FILE CHUA PUBLICKEY:\n";
    
	cin>>filePublicKey;
	cout<<"\n-------------------------------------------------------------------------------------------------\n";
	encryptFile(fileName,filePublicKey);
	cout<<"\n-------------------------------------------------------------------------------------------------\n";
}
void newfilekey(){
	unsigned long int n;
	cout<<"ENTER KEY LENGTH TO CREATE\t  8 < LENGTH < 100\n";
	cout<<"\n-------------------------------------------------------------------------------------------------\n";
	cin>>n;
	while (n<8||n>=100){
		cout<<"LENGTH INCORRECT, TRY AGAIN\n";
		cin>>n;
	cout<<"\n-------------------------------------------------------------------------------------------------\n";
	} 
	genfilekey(n);
	cout<<"\n-------------------------------------------------------------------------------------------------\n";

	//ghi con cụ key vào file key
}
void decryptfile(){
    std::string fileName,filenamePrivatekey;
	cout<<"ENTER THE FILE NAME TO BE DECRYPTED\n";
	cout<<"YOU CAN USE cyphertext.txt OR ENTER YOUR FILE:\n";
	// cout<<"DEFAULT: cyphertext.txt\n";
	// cout<<"NHAP FILENAME CAN MA HOA\n";
	cin>>fileName;
	cout<<"\n-------------------------------------------------------------------------------------------------\n";
	// cout<<"DEFAULT: privatekey.txt\n";
	// cout<<"NHAP FILENAME PRIVETEKEY\n";
	cout<<"ENTER FILENAME PRIVATEKEY\n";
	cout<<"YOU CAN USE privatekey.txt OR ENTER YOUR FILE:\n";
	cin>>filenamePrivatekey;
	cout<<"\n-------------------------------------------------------------------------------------------------\n";
	decryptFile(fileName,filenamePrivatekey);// mã hóa text
}
void openfilemessage(){
	char text[100];
	std::cout << "Nhap vao 1 chuoi: \n";
	std::cin.getline(text, sizeof(text));
	
	std::cout << "Chuoi da nhap: " << text << "\n";
	FILE * fp ; 
		fp = fopen("message.txt", "w+"); 
		//std::string text;
		//std::cout<<"NHAP VAN BAN CAN GUI DI\n";
		//fflush(stdin);
		// fgets(text,sizeof(text)+1,stdin);
		//std::getline(cin,textS
		//std::getline(cin,str);
		//fgets(arr, 200, fp);
		// fprintf(fp,"%s",text);
		fputs(text,fp);
		fclose(fp);
}

void openfilemessage_new(){	
	//mở file message_new.txt
}
void MENU(){
    bool key=true;
    int i;
    while(key==true){
		//std::string one="NEW PUBLICKEY AND PRIVATEKEY",two="ENCRYPTFILE",three="DECRYPTFILE",four="OPEN FILE MESSAGE SENT",five="OPEN FILE MESSAGE RECIEVE",six="EXIT";
        cout<<"\n\t\tMENU PROGRAM\n";
		cout<<" _______________________________________________\n";
		cout<<"|\t1: NEW PUBLICKEY AND PRIVATEKEY \t|\n";
		cout<<"|\t2: ENCRYPTFILE                  \t|\n";
		cout<<"|\t3: DECRYPTFILE                  \t|\n";
		//cout<<"|\t4: OPEN FILE MESSAGE SENT       \t|\n";
		//cout<<"|\t5: OPEN FILE MESSAGE RECIEVE    \t|\n";
		cout<<" -----------------------------------------------\n";
		cout<<"\t   PRESS ANY KEY TO EXIT\n";
        cout<<"ENTER YOUR SELECTION\n";
        cin>>i;
        switch (i){
        case 1:
			newfilekey();
            break;
        case 2:
			encryptfile();
            break;
        case 3:
			decryptfile();
            break;
        // case 4:
		// 	openfilemessage();
        //     break;
        // case 5:
        //     openfilemessage_new();
        //     break;
    	default:
		key=false;
        cout<<"EXIT";
            break;
        }
    }
}