#ifndef LISTCREATOR_HPP
#define LISTCREATOR_HPP

#include "FileReader.hpp"
class ListCreator {
private:
	CircularDoublyLinkedList* list;
	FileReader fileReader;
	int biggestObeb;
public:
	ListCreator();
	void CreateList();
	~ListCreator();
};

#endif // !LISTCREATOR
