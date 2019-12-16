#include <iostream>
#include <fstream>
#include "lzw.h"

using namespace std;

int main()
{
	int dictionaryLength = 511; //parameter?
	int encodedLen = 9;
	string filename = "test2.txt";
	string encodedFilename = "entest2";


	Lzw lzw(dictionaryLength);
	lzw.compress(filename, encodedFilename, encodedLen);
	cout << "Encoded" << endl;
	
	//cout << "Decoded" << endl;
	lzw.printTable();
	cout << endl << "test table" << endl << endl;
	//lzw.printTableMAP();

	lzw.decode("entest2", "detest.txt", encodedLen);
}
