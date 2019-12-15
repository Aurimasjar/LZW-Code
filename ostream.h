#ifndef OSTREAM_H
#define OSTREAM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <bitset>

using namespace std;

class Ostream {

	private:

		static const size_t B = 512;
		static const size_t L = 8*B;
		//char buffer[B];
		int cursor;
		int encodedLen;

		char ofBuffer[B];
		int ofBuffSize = 0;
		bitset<L> ofB;
		int ofBConPos = 0;
		int ofCursor = 0;

		ofstream file;

		void put_bits_in_to_bitset(vector<bool> oneW);

	public:

		bool lastConverted = false;

		vector<bool> GenLBitSet(int L, int Dec);
		void bitset_to_bytes();
		//writes buffer to file
		void writeToFile();
		//puts string of dictionarLength bits to buffer
		void putWordToWrite(int w);
		void fillCursor(string word);

		Ostream(string filename, int len);
		~Ostream();
};

#endif
