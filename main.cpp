#include <iostream>
#include <fstream>
#include "lzw.h"

using namespace std;

int main()
{
	int dictionaryLength = 256; //parameter?
	int encodedLen = 9;
	string filename = "test.txt";
	string encodedFilename = "entest";


	Lzw lzw(dictionaryLength);
	lzw.compress(filename, encodedFilename, encodedLen);
	cout << "Encoded" << endl;
	//lzw.decode("entest", "detest.txt", 9);
	//cout << "Decoded" << endl;
	lzw.printTable();
	cout << endl << "test table" << endl << endl;
	//lzw.printTableMAP();
}
