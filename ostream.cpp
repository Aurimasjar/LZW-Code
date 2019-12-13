#include "ostream.h"

Ostream::Ostream(string filename, int len) {
    encodedLen = len;
	file.open(filename, ios::out | ios::binary);
}

Ostream::~Ostream() {
	file.close();
}

/*void Ostream::writeToFile() {
	file.write(buffer, B);
}*/

//padaro L ilgio bool (bitu) vektoriu is skaiciaus Dec
vector<bool> Ostream::GenLBitSet(int L, int Dec)
{
    bitset<64> bit_set_buffer(Dec);
    vector<bool> generated_bit_vec;
    generated_bit_vec.resize(L);

    int j = 0;
    for(int i = L-1; i>=0; i--)
    {
        generated_bit_vec[j] = bit_set_buffer[i];
        j++;
    }

    /*for(int i = 0; i< generated_bit_vec.size(); i++)
    {
        cout<<generated_bit_vec[i];
    }
    cout<<endl;*/

   return generated_bit_vec;
}


//sudeda gautus bitus vector<bool> formoje i buferi rasymui
void Ostream::put_bits_in_to_bitset(vector<bool> oneW)
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

//uzsipildzius bitu buferiui, arba tiesiog iskvietus sia funkcija kai reikia bitus buferije surasyti i faila nepasiekus limito (kai lastConverted = false), konvertuoja bitu buferi i baitus ir iraso i faila
void Ostream::bitset_to_bytes()
{
    lastConverted = true;

    bitset<8> bit8;

    ofBConPos = 0;
    ofBuffSize = 0;
    char oneBuff = 0;


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

        ofBuffer[ofBuffSize] = oneBuff;
        ofBuffSize++;


        bit8.reset();
    }

    writeToFile();


}

void Ostream::writeToFile()
{
    file.write(ofBuffer, ofBuffSize);
}


//si funkcija turetu paversti zodzius i parametro length bitu ilgio zodzius (internete dazniausiai imamas 12, kiek musu turetu aprepti nezinau, bet turbut nuo 9 iki 16, 24 ar 32)(Edit: lenght dabar paduodamas i Ostream konstruktoriu)
//ir sudeti i buferi (taigi vel teks pazaisti su bitukais, verta pasiziureti gal kas pravers is Hafmano)
void Ostream::putWordToWrite(int w) {
	//should put word written in 12 bits to buffer
	/*int n = w.length();
	for(int i = 0; i < w.length(); i++) {
		isvesti w[i]...
	}*/

    put_bits_in_to_bitset(GenLBitSet(encodedLen,w));


	//cout<<w<<endl;
	//file << w << endl;
}
