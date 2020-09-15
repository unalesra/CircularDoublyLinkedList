#ifndef CIRCULARDOUBLYLINKEDLIST_HPP
#define CIRCULARDOUBLYLINKEDLIST_HPP

#include "Iterator.hpp"

class CircularDoublyLinkedList {
private:
	int size;
	int obeb;
	int biggestObeb;
	Node*itr;
	Node*head;

public:
	CircularDoublyLinkedList();
	int getSize();
	int Obeb(int, int);
	bool ObebKontrol(int, int);
	void InsertNode(int);
	void InsertRight(int);
	void InsertLeft(int);
	void addZero();
	int Mod(int);
	void Yazdir(CircularDoublyLinkedList*);
	~CircularDoublyLinkedList();


};
#endif