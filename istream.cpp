#include "istream.h"

Istream::Istream(string filename) {
	file.open(filename, ios::in | ios::binary);
	readFromFile();
}

Istream::~Istream() {
	file.close();
}

void Istream::readFromFile() {
	cursor = 0;
	file.read(buffer, B);
	if(!file)
	{
		n = file.gcount();
	}
	//n = how many bytes were read
	//cout << "Bytes read: " << n << endl;
}

char Istream::getNextByte() {
	char letter = buffer[cursor];
	cursor++;
	if(n >= 0 && cursor > n) {
		letter = 0;
		eof = true;
	}
	else if(cursor >= B) {
		readFromFile();
	}
	return letter;
}
