#ifndef LZW_H
#define LZW_H

#include <vector>
#include <algorithm>
#include <string>
#include "istream.h"
#include "ostream.h"

using namespace std;

class Lzw {

	private:

	vector<string> table; //table of words, first 256 elements are characters from ASCII table
	string word;
	char letter;
	int dictionaryLength; // our parameter

	void initTable();

	public:
	void setWord(string w) { word = w; }
	string getWord() { return word; }
	void setLetter(char l) { letter = l; }
	char getLetter() { return letter; }
	//checks if word is in table
	bool isInTable(string w);
	//puts word to table
	void addToTable(string w);

	Lzw(int length);
	~Lzw();

	//lzw compression algorythm
	void compress(string filename, string encodedFilename);
};

#endif
