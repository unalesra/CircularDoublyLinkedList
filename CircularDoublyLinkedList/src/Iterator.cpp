/**     * @fileDosya Iterator.cpp
		* @description Düğümler üzerinde işlem yapmak için kullanılan sınıf. 
		* @courseDersi 1A
		* @assignment 1.Ödev
		* @dateKodu 06.08.2020
		* @author Esra Ünal
*/

#include "Iterator.hpp"

Iterator::Iterator() {}

//eğer sadece head varsa bunun kontolü CircularDoublyLinkedList sınıfında yapıldığı için index 1'den başlatılmıştır.
//düğümde her ilerlenildiğinde index bir arttırılır. En son düğüme gelindiğinde index=size olacağından o düğüm döndürülür.
Node* Iterator::EndNode(Node *node, int size) {
	int index = 1;
	while (true) {
			node = node->next;
		index++;
		if (index == size)
			return node;
	}

	return NULL;
}
