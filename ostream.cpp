#include "ostream.h"

Ostream::Ostream(string filename) {
	file.open(filename, ios::out | ios::binary);
}

Ostream::~Ostream() {
	file.close();
}

void Ostream::writeToFile() {
	file.write(buffer, B);
}

//si funkcija turetu paversti zodzius i parametro length bitu ilgio zodzius (internete dazniausiai imamas 12, kiek musu turetu aprepti nezinau, bet turbut nuo 9 iki 16, 24 ar 32)
//ir sudeti i buferi (taigi vel teks pazaisti su bitukais, verta pasiziureti gal kas pravers is Hafmano)
void Ostream::putWordToWrite(string w) {
	//should put word written in 12 bits to buffer
	/*int n = w.length();
	for(int i = 0; i < w.length(); i++) {
		isvesti w[i]...
	}*/
	file << w << endl;
}
