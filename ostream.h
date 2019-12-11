#ifndef OSTREAM_H
#define OSTREAM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

class Ostream {

	private:

	static const size_t B = 512;
	char buffer[B];
	int cursor;

	ofstream file;

	public:

	Ostream(string filename);
	~Ostream();

	//writes buffer to file
	void writeToFile();
	//puts string of dictionarLength bits to buffer
	void putWordToWrite(string w);
};

#endif
