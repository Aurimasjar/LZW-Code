#include "streamer.h"

Streamer::Streamer(string file, string cFile)
{
	myFile.open(file, ios::in | ios::binary);

	compFile.open(cFile, ios::out | ios::binary);

	read_from_file();
}
Streamer::Streamer(string file, string cFile, int i)
{
	myFile.open(file, ios::in | ios::binary);

	compFile.open(cFile, ios::out);

	read_from_file();
}


Streamer::~Streamer()
{
	myFile.close();
	compFile.close();
}


//converts char array to bitset
void Streamer::get_bits(char s[B])
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


//returns word from k bits
int Streamer::get_k_bits(int k)
{
	w = 0;
	lBit = 0;
	for(int i = k-1; i >= 0; i--)
	{
		w += b[cursor]*pow(2, i);
		cursor++;

        lBit +=1;

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
			read_from_file();
		}
	}

	return 1;
}

//resets original file stream to beginning.
void Streamer::return_myFile_to_begining()
{
    myFile.clear();
    myFile.seekg(0);
    b.reset();
    cursor = 0;
    n = -1;

    lastConverted = false;
    ofBConPos = 0;
    ofBuffSize = 0;
    lBit = 0;
    //ofCursor = 0;
    //ofB.reset();

}

//stores given bits in a bit buffer
void Streamer::put_bits_in_to_bitset(vector<bool> oneW)
{
    for(int i = 0; i < oneW.size(); i++)
    {
        ofB[ofCursor] = oneW[i];
        ofCursor++;
        lastConverted = false;
        if(ofCursor >= L)
        {
            bitset_to_bytes();
            ofB.reset();
            ofCursor = 0;
        }

    }


}

//converts bit buffer to byte (char) buffer
void Streamer::bitset_to_bytes()
{
    lastConverted = true;

    bitset<8> bit8;

    ofBConPos = 0;
    ofBuffSize = 0;
    char oneBuff = 0;

    bool flag = true;
    while(ofBConPos < ofCursor){

        oneBuff = 0;

        for(int i = 7; i >= 0; i--)
        {
            bit8[i] = ofB[ofBConPos];
            ofBConPos++;
        }

        //cout<<bit8.to_string()<<endl;
        for (int j=0; j <8; j++)
        {
            if (bit8[j])
                oneBuff |= 1 << j;
        }
        
        if(oneBuff == '\n' && flag){
            flag = false;
        } else {
            ofBuffer[ofBuffSize] = oneBuff;
            ofBuffSize++;
            flag = true;
        }

        bit8.reset();
    }

    write_to_file();


}

//fills buffer to write to file
void Streamer::buffer_to_file(char buff)
{
    ofBuffer[ofBuffSize] = buff;
    ofBuffSize++;
    if (ofBuffSize == B){
        compFile.write(ofBuffer, ofBuffSize);
        for(int i = 0; i < B; i++){
            ofBuffer[i] = NULL;
        }
        ofBuffSize = 0;
    }
}


void Streamer::read_bits_from_file()
{
    myFile.read(buffer, B);
    	if(!myFile)
	{
		n = myFile.gcount();
	}
}



//prints byte buffer to file
void Streamer::write_to_file()
{
    compFile.write(ofBuffer, ofBuffSize);
}

//reads a portion of bits from file
void Streamer::read_from_file()
{
	myFile.read(buffer, B);
	get_bits(buffer);
	if(!myFile)
	{
		n = myFile.gcount();
	}
    //n = how many bytes were read
	//cout<<"Bytes read: "<<n<<endl;
}

