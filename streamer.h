#ifndef STREAMER_H
#define STREAMER_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;


class Streamer
{
	public:
		static const size_t B = 512;
		static const size_t L = 8*B;
		char buffer[B];
		bitset<L> b;
		ifstream myFile;
		int w = 0;
		int cursor = 0;
		int n = -1;

		char ofBuffer[B];
		int ofBuffSize = 0;
		bitset<L> ofB;
		int ofBConPos = 0;
		int ofCursor = 0;
		ofstream compFile;
		bool lastConverted = false;


		int lBit = 0;

		Streamer(string file, string cFile);
		Streamer(string file, string cFile, int i);
		~Streamer();

		void get_bits(char s[B]);
		int get_k_bits(int k);
		void put_bits_in_to_bitset(vector<bool> oneW);

		void read_from_file();
		void write_to_file();
		void write_to_filed();

		void read_bits_from_file();
		void buffer_to_file(char buff);

		void return_myFile_to_begining();

	//private:
		void bitset_to_bytes();
};

#endif
