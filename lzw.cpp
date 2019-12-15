#include "lzw.h"

Lzw::Lzw(int length) {
	dictionaryLength = length;
	initTable();
}

Lzw::~Lzw() {}

void Lzw::initTable() {
    string bf;
	for(int i = 0; i < 256; i++) {
		//cout <<(char)i << " ";
		bf = (char)i;
		//table.push_back(""+(char)i);
		table.push_back(bf);

		codes[bf] = i;

	}
	cout << endl << endl;
}

bool Lzw::isInTable(string w) {
	
	if(find(table.begin(), table.end(), w) != table.end()) {
		return true;
	}
	return false;
}

void Lzw::addToTable(string w) {

	table.push_back(w);
	//cout<<codes.size()<<endl;
	codes[w] = codes.size();

	//cout<<w<<endl;
}

//atspausdina lenteles vektoriu, informacia saugoma table vektoriuje ta pati kaip ir codes map'e
void Lzw::printTable(){
    cout<<"Table in vector: "<<endl;
    for(int i = 0; i<table.size(); i++)
    {
        cout<<table[i]<<" ";

    }
	cout<<endl;
    cout<<"Size of table: "<<table.size()<<endl;
}

//atspausdina lenteles vektoriu, informacia saugoma codes map'e ta pati kaip ir table vektoriuje
void Lzw::printTableMAP(){
    cout<<"Table in map: "<<endl;

    vector<string> keys;
    for(map<string, int>::iterator it = codes.begin(); it != codes.end(); ++it) {
        keys.push_back(it->first);
       // cout << it->first << "\n";
    }

    cout<<"Words:"<<endl;
    for(int i = 0; i<keys.size(); i++){
        cout<<keys[i]<<" ";
    }
    cout<<endl;

    cout<<"Codes:"<<endl;
    for(int i = 0; i<keys.size(); i++){
        cout<<codes[keys[i]]<<" ";
    }

    /*for(int i = 0; i<keys.size(); i++){
        //cout<<keys[i]<<" ";
        cout<<" |Word: "<<keys[i]<<" word code: "<<codes[keys[i]]<<" | ";
    }*/
	cout<<endl;
    cout<<"Size of table: "<<codes.size()<<endl;
}


// naudojama compress DEBUG PRINT.... kad atspausdinti zodzio kodo bitu seka
void Lzw::debug_print_bool_vector(vector<bool> bit_vec){
    for(int i = 0; i< bit_vec.size(); i++)
    {
        cout<<bit_vec[i];
    }
}

void Lzw::compress(string filename, string encodedFilename, int encodedLen) {
	Istream in(filename);
	Ostream of(encodedFilename, encodedLen);
	word = in.getNextByte();
	while(true) {
		letter = in.getNextByte();
		if(in.isEof()) break;
		if(isInTable(word + letter)) {
			word = word + letter;
		}
		else {

			//of.putWordToWrite(word); //write word to the file as 12 bit sequence
			//cout<<table[codes[word]]<<endl;

			//DEBUG PRINT
			cout<<"Word: "<<word<<" | Code of word: "<<codes[word]<<" |bin of code: ";    //" Test vector: "<<table[codes[word]]<<endl;
			debug_print_bool_vector(of.GenLBitSet(encodedLen,codes[word]));
			cout<<endl;
			//PRINT END

			of.putWordToWrite(codes[word]);//write word to the file as encodedLen bit sequence
			addToTable(word + letter);

			//DEBUG PRINT
			cout<<"New word: "<<word + letter<<" | Code of word: "<<codes[word+letter]<<" |bin of code: ";    //" Test vector: "<<table[codes[word]]<<endl;
			debug_print_bool_vector(of.GenLBitSet(encodedLen,codes[word+letter]));
			cout<<endl;
			//PRINT END

			word = letter;
		}
	}
	//of.putWordToWrite(word);

	//DEBUG PRINT
    cout<<"Word: "<<word<<" |Code of word: "<<codes[word]<<" |bin of code: ";    //" Test vector: "<<table[codes[word]]<<endl;
	debug_print_bool_vector(of.GenLBitSet(encodedLen,codes[word]));
    cout<<endl;
    //PRINT END


	of.putWordToWrite(codes[word]);
	cout << endl;

	if(of.lastConverted == false)
    {
        of.bitset_to_bytes();
	}


   /*vector<string> keys;
    for(map<string, int>::iterator it = codes.begin(); it != codes.end(); ++it) {
        keys.push_back(it->first);
       // cout << it->first << "\n";
    }
    cout<<"Map size: "<<codes.size()<<endl;
    for(int i = 0; i<keys.size(); i++){
        //cout<<keys[i]<<" ";
        cout<<codes[keys[i]]<<" ";
    }
    cout<<endl;*/
}


void Lzw::decode(string encodedFilename, string filename, int encodedLen){

	//Istream in(encodedFilename);
	stream = new Streamer(encodedFilename, filename, 1);
	Ostream of(filename, encodedLen);
	stream->get_k_bits(9);
	dictionaryLength = stream->w;

	cout << "dictionaryLength: " << dictionaryLength << endl;

	for(int i = 0; i < 256; i++) 
	{
		dictionary[i] = (char)i;

	}
	int cursor = 257;

	int temp;
	stream->get_k_bits(9);
	temp = stream->w; 
	dictionary[cursor] = dictionary[temp];
	cursor++;
	bool cont;
	for(int i = 1; i < dictionaryLength; i++)
	{
		cont = stream->get_k_bits(9);
		temp = stream->w; 
		dictionary[cursor] = dictionary[temp];
		of.fillCursor(dictionary[cursor-1]);

		dictionary[cursor-1] = dictionary[cursor-1] + dictionary[cursor][0];

		cursor++;
	}
	
	while(cont)
	{
		if(stream->get_k_bits(9) == 0)
		{
			temp = stream->w; 
			of.fillCursor(dictionary[temp]);
			break;
		}
		else
		{
			temp = stream->w; 
		}
	}
	of.writeToFile();


}