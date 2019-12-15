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

int Istream::get_k_bits(int k){
	int letter;

	for(int i = k-1; i >= 0; i--)
	{
		letter += b[cursor]*pow(2, i);
		cursor++;

		if(n > 0)
		{
			if(cursor >= 8*n)
			{
				//all bits were read
				//cout<<cursor<<endl;
				return 0;
			}
		}
		else if(cursor >= L)
		{
			//need to take new portion of data
			cursor = 0;
			b.reset();
			read_bits_from_file();
		}
	}

	return letter;
}

void Istream::read_bits_from_file()
{
	file.read(buffer, B);
	get_bits(buffer);
	if(!file)
	{
		n = file.gcount();
	}

}

void Istream::get_bits(char s[B])
{
	for (int i = 0; i < B; ++i) {
	  char c = s[i];
	  for (int j = 7; j >= 0 && c; --j) {
		 if (c & 0x1) {
		   b.set(8 * i + j);
		 }
		 c >>= 1;
	  }
	}
}
