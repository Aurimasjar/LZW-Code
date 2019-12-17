#include <iostream>
#include <fstream>
#include "lzw.h"

using namespace std;


int main() {

	int dictionaryLength;// = 400; //parameter?
	int encodedLen;// = 9;
	string originalFile;// = "pdfas.pdf";
	string endcodedFile;// = "bigtxt";
	string decodedFile;
	int choice;
	Lzw *lzw;

	while(true){
		cout << "Encode = 1" << endl << "Decode = 2" << endl << "Exit = 0" << endl << ">";
		cin >> choice;
		switch(choice){
			case 0:{
				exit(1);
			}
			case 1:{
				cout << "Enter original file: ";
				cin >> originalFile;
				cout << "Enter encoded file: ";
				cin >> endcodedFile;
				//cout << "Enter dictionary length: ";
				//cin >> dictionaryLength;
				cout << "Enter encoded word length: ";
				cin >> encodedLen;

				dictionaryLength = pow(2, encodedLen) - 1;

				lzw = new Lzw(dictionaryLength);

				lzw->compress(originalFile, endcodedFile, encodedLen);

				cout << "File " << originalFile << " encoded to file " << endcodedFile << endl;
				break;
			}
			case 2:{
				cout << "Enter file to decode: ";
				cin >> endcodedFile;
				cout << "Decoded file name: ";
				cin >> decodedFile;
				lzw = new Lzw();
				lzw->decode(endcodedFile, decodedFile);
				cout << "File " << endcodedFile << " decoded to file " << decodedFile << endl;
				break;
			}
			default:{
				cout << "Please enter your choice again." << endl;
			}
		}
	}
}
