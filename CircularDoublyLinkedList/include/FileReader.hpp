#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include<iostream>
#include <fstream>
#include <string>

#include "CircularDoublyLinkedList.hpp"

using namespace std;

class FileReader {

private:
	string number;
	int fileSize;
public:
	FileReader(); 
	int getFileSize();
	CircularDoublyLinkedList* list;
	string ReadFile(string dosyaYolu);
};
#endif 
