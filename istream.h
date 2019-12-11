#ifndef ISTREAM_H
#define ISTREAM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

class Istream {

	private:

	static const size_t B = 512;
	char buffer[B];
	int n = -1;
	int cursor;
	bool eof = false;

	ifstream file;

	public:

	int getN() { return n; }
	bool isEof() { return eof; }

	Istream(string filename);
	~Istream();

	//reads file to buffer
	void readFromFile();
	//returns byte and moves cursor to other byte
	char getNextByte();
};

#endif
