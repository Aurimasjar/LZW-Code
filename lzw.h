#ifndef LZW_H
#define LZW_H

#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "istream.h"
#include "ostream.h"
#include "streamer.h"
#include "treeManagement.h"

using namespace std;

class Lzw {

	private:

		//vector<string> table; //table of words, first 256 elements are characters from ASCII table
		binaryTree<string> *bTree;
		string word;
		char letter;
		int dictionaryLength; // our parameter
		map<int, string> dictionary;

		void initTable();

		Streamer *stream;


	public:
		map<string,int> codes;

		void setWord(string w) { word = w; }
		string getWord() { return word; }

		void setLetter(char l) { letter = l; }
		char getLetter() { return letter; }

		bool isInTable(string w);
		void addToTable(string w);

		void printTable();
		void printTableMAP();

		void compress(string filename, string encodedFilename, int encodedLen);

		//???
		void debug_print_bool_vector(vector<bool> bit_vec);

		void decode(string encodedFilename, string filename, int encodedLen);

		Lzw(int length);
		~Lzw();
};

#endif
