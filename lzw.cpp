#include "lzw.h"

Lzw::Lzw(int length) {
	dictionaryLength = length;
	initTable();
}

Lzw::~Lzw() {
	delete bTree;
}

void Lzw::initTable() {
    string bf;
	bTree = new binaryTree<string>();
	for(int i = 0; i < 256; i++) {
		//cout <<(char)i << " ";
		bf = (char)i;
		bTree->insertValue(bf);
		//table.push_back(bf);

		codes[bf] = i;

	}
	cout << endl << endl;
}

bool Lzw::isInTable(string w) {

	return bTree->searchTree(w);
}

void Lzw::addToTable(string w) {
	bTree->insertValue(w);
	//table.push_back(w);
	//cout<<codes.size()<<endl;
	codes[w] = codes.size();

	//cout<<w<<endl;
}

//atspausdina lenteles vektoriu, informacia saugoma table vektoriuje ta pati kaip ir codes map'e
void Lzw::printTable(){
    /*cout<<"Table in vector: "<<endl;
    for(int i = 0; i<table.size(); i++)
    {
        cout<<table[i]<<" ";

    }*/
	cout << "Table in tree" << endl;
	bTree->inPrint();
	cout<<endl;
    //cout<<"Size of table: "<<table.size()<<endl;
	cout << "Size of tree: " << bTree->countNodes();
}

//atspausdina lenteles vektoriu, informacia saugoma codes map'e ta pati kaip ir table vektoriuje
void Lzw::printTableMAP(){
    cout<<"Table in map: "<<endl;

    vector<string> keys;
    for(map<string, int>::iterator it = codes.begin(); it != codes.end(); ++it) {
        keys.push_back(it->first);
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

	int encLen = encodedLen - 1;
	of.put_bits_in_to_bitset(of.GenLBitSet(5,encLen));
	cout<<dictionaryLength<<endl;
	of.put_bits_in_to_bitset(of.GenLBitSet(encodedLen,dictionaryLength));

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
			/*cout<<"New word: "<<word + letter<<" | Code of word: "<<codes[word+letter]<<" |bin of code: ";    //" Test vector: "<<table[codes[word]]<<endl;
			debug_print_bool_vector(of.GenLBitSet(encodedLen,codes[word+letter]));
			cout<<endl;*/
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

//5bit encodedLen-1, encodedLen bit. dictionaryLength, ....kodai encodedLen bit ilgio.

void Lzw::decode(string encodedFilename, string filename, int encodedLen){

	//Istream in(encodedFilename);
	stream = new Streamer(encodedFilename, filename, 1);
	Ostream of(filename, encodedLen);

	stream->get_k_bits(5);
	encodedLen = stream->w+1;
	cout<<encodedLen<<endl;

	stream->get_k_bits(encodedLen);
	dictionaryLength = stream->w;

	cout << "dictionaryLength: " << dictionaryLength << endl;

	for(int i = 0; i < 256; i++)
	{
		dictionary[i] = (char)i;

	}
	int cursor = 257;

	int temp;
	stream->get_k_bits(encodedLen);
	temp = stream->w;
	dictionary[cursor] = dictionary[temp];
	cursor++;
	bool cont = true;
	for(int i = 1; i < dictionaryLength; i++)
	{
		if(stream->get_k_bits(encodedLen) == 0){
			temp = stream->w;
			//cout << "Read: " << temp << endl;
			//cout << "Writing: " << dictionary[cursor-1] << " + " << dictionary[temp] << endl;	
			//dictionary[cursor] = dictionary[temp];
			of.fillCursor(dictionary[cursor-1]);
			if(temp != 0)
			{
				dictionary[cursor-1] = dictionary[cursor-1] + dictionary[temp][0];
				of.fillCursor(dictionary[temp]);
			}
			//of.fillCursor(dictionary[temp]);
			
			cursor++;
			cont = false;
			break;

			}
		else {
			temp = stream->w;
			of.fillCursor(dictionary[cursor-1]);
			//cout << "Writing: " << dictionary[cursor-1] << endl;

			//cout << "   Temp: " << temp << "  ";
			//cout << dictionary[cursor-1] << " ("<< cursor-1 << ") | " << dictionary[cursor][0] <<  endl;
			

			dictionary[cursor-1] = dictionary[cursor-1] + dictionary[temp][0];
			//cout << "   New: " << dictionary[cursor-1] << endl;			

			dictionary[cursor] = dictionary[temp];


			cursor++;
		}
	}
	if(cont)
	{
		of.fillCursor(dictionary[temp]);
	}

	while(cont)
	{
		if(stream->get_k_bits(encodedLen) == 0)
		{
			temp = stream->w;
			of.fillCursor(dictionary[temp]);
			break;
		}
		else
		{
			temp = stream->w;
			of.fillCursor(dictionary[temp]);
		}
	}
	of.writeToFile();


}
       // cout << it->first << "\n";
