#include "lzw.h"

Lzw::Lzw(int length) {
	dictionaryLength = length;
	initTable();
}

Lzw::~Lzw() {}

void Lzw::initTable() {
	for(int i = 0; i < 256; i++) {
		//cout << i << " ";
		table.push_back("" + (char)i);
	}
	cout << endl << endl;
}

bool Lzw::isInTable(string w) {
	if(find(table.begin(), table.end(), w) != table.end()) {
		return true;
	}
	return false;
}

void Lzw::addToTable(string w) {
	table.push_back(w);
}

void Lzw::compress(string filename, string encodedFilename) {
	Istream in(filename);
	Ostream of(encodedFilename); //create that class
	word = in.getNextByte();
	while(true) {
		letter = in.getNextByte();
		if(in.isEof()) break;
		if(isInTable(word + letter)) {
			word = word + letter;
		}
		else {
			of.putWordToWrite(word); //write word to the file as 12 bit sequence
			addToTable(word + letter);
			word = letter;
		}
	}
	of.putWordToWrite(word);
	cout << endl;
}
