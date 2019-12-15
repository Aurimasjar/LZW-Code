#include <iostream>
#include <fstream>
#include "lzw.h"

using namespace std;

int main()
{
	int dictionaryLength = 256; //parameter?
	int encodedLen = 9;
	string filename = "test.txt";
	string encodedFilename = "encoded";


	Lzw lzw(dictionaryLength);
	lzw.compress(filename, encodedFilename, encodedLen);

	lzw.decode("encod", "testUno.txt", 9);
	/*lzw.printTable();
	cout << endl << "test table" << endl << endl;
	lzw.printTableMAP();*/
}
