#ifndef ISTREAM_H
#define ISTREAM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <bitset>

using namespace std;

class Istream {

	private:

		static const size_t B = 512;
		static const size_t L = B*8;
		char buffer[B];
		bitset<L> b;
		int n = -1;
		int cursor;
		bool eof = false;

		ifstream file;

	public:

		int getN() { return n; }
		bool isEof() { return eof; }

		//reads file to buffer
		void readFromFile();
		//returns byte and moves cursor to other byte
		char getNextByte();

		int get_k_bits(int k);
		void read_bits_from_file();
		void get_bits(char s[B]);
		
		Istream(string filename);
		~Istream();
};

#endif
