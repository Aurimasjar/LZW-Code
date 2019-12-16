#include <iostream>
#include <fstream>
#include "lzw.h"

using namespace std;

int main()
{
	int dictionaryLength = 400; //parameter?
	int encodedLen = 9;
	string filename = "test.txt";
	string encodedFilename = "bigtxt";


	Lzw lzw(dictionaryLength);
	lzw.compress(filename, encodedFilename, encodedLen);
	//cout << "Encoded" << endl;

	//cout << "Decoded" << endl;
	//lzw.printTable();
	//cout << endl << "test table" << endl << endl;
	//lzw.printTableMAP();

	lzw.decode("bigtxt", "decbigtxt.txt", encodedLen);
}
