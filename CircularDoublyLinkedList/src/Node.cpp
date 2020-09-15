/**     * @fileDosya Node.cpp
		* @description Düğüm sınıfı, data, next ve prev'in ilk atamaları yapılır
		* @courseDersi 1A
		* @assignment 1.Ödev
		* @dateKodu 06.08.2020
		* @author Esra Ünal
*/

#include "Node.hpp"

//Sınıfın kurucu fonksiyonu
Node::Node(const int& data, Node*next, Node*prev) {
	this->data = data;
	this->next = next;
	this->prev = prev;
}