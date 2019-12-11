#include <iostream>
#include <fstream>
#include "lzw.h"

using namespace std;

int main()
{
	int dictionaryLength; //parameter?
	string filename = "test.txt";
	string encodedFilename = "encoded";

	

	Lzw lzw(dictionaryLength);
	lzw.compress(filename, encodedFilename);
}
