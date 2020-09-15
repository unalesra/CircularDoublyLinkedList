/**     * @fileDosya FileReader.cpp
		* @description Dosyanın okunduğu sınıf
		* @courseDersi 1A
		* @assignment 1.Ödev
		* @dateKodu 06.08.2020
		* @authorÖğrencinin Esra Ünal
*/

#include "FileReader.hpp"


FileReader::FileReader(){
	this->number="";
	this->fileSize = 0;
	list = NULL;
}

//dosya boyutu döndürülür.
int FileReader::getFileSize() {
	return this->fileSize;
}

//dosya bitene kadar okunur ve döndürülür.
string FileReader::ReadFile(string dosyaYolu) {
	ifstream file;
	string numberReaded = "";
	file.open(dosyaYolu);

	if (file.is_open()) {
		while (getline(file, numberReaded)) {
			this->number +=numberReaded+"\n";
		}
		this->fileSize = this->number.size();
		return this->number;
	}
		
	file.close();
	return "Dosya Bos";
}
