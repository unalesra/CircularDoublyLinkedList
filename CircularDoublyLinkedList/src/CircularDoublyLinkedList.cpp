/**     * @fileDosya CircularDoublyLinkedList.cpp
		* @description ListCreator s�n�f�ndan gelen say�lar ile listenin olu�turulmas�
		* @courseDersi 1A
		* @assignment 1.�dev
		* @dateKodu 06.08.2020
		* @author Esra �nal
*/

#include "CircularDoublyLinkedList.hpp"

//kurucu fonksiyon
CircularDoublyLinkedList::CircularDoublyLinkedList() {
	size = 0;
	obeb = 0;
	this->biggestObeb = 0;
	itr = NULL;
	head = NULL;
}

//listenin boyutu d�nd�r�l�r
int CircularDoublyLinkedList::getSize() {
	return size;
}

////obeb hesaplan�rken �klid algoritmas� kullan�lm��t�r.
int CircularDoublyLinkedList::Obeb(int n1, int n2) {
	int remaining = 0;
	if (n1 == 0)
		return n1;
	if (n2 != 0)
		remaining = n1 % n2;
	if (remaining == 0)
		return n2;
	return Obeb(n2, remaining);
}

//sa�a ya da sola ekleme i�lemenin kontrol edildi�i fonksiyon
void CircularDoublyLinkedList::InsertNode(int data) {
	//boyut s�f�r de�ilse yeni obeb bulunur yoksa s�f�r olarak kalmaya devam eder.
	if(size!=0)
		obeb = Obeb(data, head->data);
	
	//boyut s�f�rsa ilk eklenen d���m head'dir
	if (size == 0) {
		head = new Node(data, head, head);
		size++;
	}
	//obeb ya da mod s�f�rsa algortimaya g�re sa�a eklenir. Boyut bir artt�r�l�r.
	else if (obeb == 0 || data == 0) {
		InsertRight(data);
		this->size++;
	}
	//d���m sola eklenir boyut bir artt�r�l�r
	else {
		InsertLeft(data);
		this->size++;
	}
}

//Liste i�ersinde arada bir d���me ekleme yap�lmas� gerekti�inde false d�nerse sola, true d�nerse sa�a ekleme yap�l�r.
bool CircularDoublyLinkedList::ObebKontrol(int obeb, int data) {
	itr = head;
	Iterator iterator;
	Node* endNode = iterator.EndNode(head, size); //son d���m bulunur
	//yeni obeb, en b�y�k obebden k���k oldu�u s�rece d�ner, e�er yeni obeb en b�y�k obebden b�y�kse false d�ner, sola ekle demektir.
	while (obeb < this->biggestObeb) {
		//yeni obeb, en b�y�k obebden b�y�kse, art�k yeni obeb en b�y�k obeb olur ve sola eklenmesi i�in false d�ner.
		if (obeb > this->biggestObeb) {
			this->biggestObeb = obeb;
			return false;
		}
		//e�er obeb=0 gelirse sa�a eklenmesi i�i true d�nd�r�l�r.
		if (obeb == 0)
			return true;
		//e�er yeni obeb ile en b�y�k obeb e�itse o d���mde kal�nmal�nmal� ve sola ekleme yap�lmal�
		if (obeb == biggestObeb)
			return false;
		
		//liste i�eriinde ilerleme
		itr = itr->next;
		//ilerledik�e yeni obebin hesaplanmas�
		obeb = Obeb(itr->data, data);

		//e�er son d���me gelinmi�se sola ekleme yap�lmas� i�in false d�ner.
		if (itr == endNode) {
			obeb = Obeb(itr->data, data);
			return false;
		}
	}
	
	//while d�ng�s�ne girmedi�i i�in yeni obeb en b�y�k obebden k���k gelmemi� demektir. Bu durumda en b�y�k obeb olmal�d�r. Sola eklenmesi i�in false d�ner.
	this->biggestObeb = obeb;
	return false;
}

//sa�a ekle yap�l�r
void CircularDoublyLinkedList::InsertRight(int data) {
	/** Boyut 1 ise, datan�n s�f�r olup olmamas�na g�re kontol yap�l�r. E�er s�f�rsa s�f�r ekleme metodu �a��r�l�r.
	* boyut bir de�ilse ve data 0 gelmemi�se normal sa�a ekleme algoritmas� uygulan�r
	*/
	if (size == 1) {
		if (data != 0) {
			Node* newNode = new Node(data, head, head);
			head->next = newNode;
			head->prev = newNode;
			biggestObeb = obeb;
			itr = head;
		}
		else if(data==0)
			addZero();
	}
	else if (data == 0) {
		addZero();
	}
	else {
		Node* newNode = new Node(data, itr->next, itr);
		itr->next->prev = newNode;
		itr->next = newNode;
		itr = head;
	}
}

//ba�a ekleme yap�l�rken mod bulmak ayr� bir metodla sa�lanm��t�r.
int CircularDoublyLinkedList::Mod(int data) {
	int index = 0;
	if (data > head->data) {
		if (head->data != 0)
			index = data % head->data;
	}
	else {
		if (data != 0)
			index = head->data;
	}
	return index;
}

//Sola ekleme yap�l�r. 
void CircularDoublyLinkedList::InsertLeft(int data) {

//E�er boyut 1 ise ve mod 0 gelmi�se ba�a ekleme yap�l�r. Yoksa sola ekleme algoritmas� kullan�l�r.

	if (size == 1) {
		if (Mod(data) == 0) {
			InsertRight(data);
		}
		else {
			itr = head;
			head = new Node(data, this->itr, this->itr);
			itr->next = head;
			itr->prev = head;
		}
		itr = head;
		biggestObeb = obeb;


	}
	// E�er boyut 1 de�ilse
	else {
		int index = 0;
		Iterator iter;
		Node* endNode = iter.EndNode(head, size);  //son d���m 
		Node* oldHead = NULL;
	
	//Obeb kontrol ile true mu d�necek false mu d�necek kontrol edilir. True d�nerse sa�a ekle metodu �a��r�l�r. False d�nerse sola ekle metodunda devam edilir.
		if (!ObebKontrol(obeb, data)) {
			Node *node = itr;
			
			//mod hesaplan�r
			if (data > this->itr->data) {
				if(this->itr->data!=0)
				index = data % this->itr->data;
			}
			else {
				if (data != 0)
				index = this->itr->data%data;
			}

			//e�er mod 0 geldiyse sa�a eklensin
			//yoksa sola eklensin
			if (index==0) {
				InsertRight(data);
			}
			else {
				while (index != 0) {
					oldHead = head;
					
					//E�er sola gide gide d���m�n ba��na gelindiyse en ba�a ekleme yap�l�r
					if (index >= size) {
						head = new Node(data, oldHead, endNode);
						oldHead->prev = head;
						endNode->next = head;
						itr = head;
						break;
					}
					//E�er ba�a gelinmemi�se index bir azalt�l�r ve �nceki d���me gidilir.
					else {
						index--;
						if(obeb!=this->biggestObeb)
							if(node!=endNode->next && index!=0)
							node = node->prev;
					}
				}
				//E�er mod kadar ilerlenmi�se d���m i�erisinde sola ekleme algoritmas� �al��t�r�l�r. (index-- denilerek bunun kontrol� yap�ld�.)
				if (index == 0) {
					Node* newNode = new Node(data, node, node->prev);
					node->prev->next = newNode;
					node->prev = newNode;
					if (newNode->prev == endNode)
						head = newNode;
					itr = head;
				}
			}
		}
		//obeb kontrol true d�nm�� demektir. Sa�a ekle algoritmas� �al��t�r�l�r.
		else {
			obeb = 0;
			InsertRight(data);
		}
	}
}

//S�f�ra ekleme durumu sonradan d���n�ld��� i�in program� bozmamak ad�na s�f�r eklemesi gereken durumlar i�in bu fonksiyon yaz�lm��t�r.
void CircularDoublyLinkedList::addZero(){
	//e�er boyut bir ise sa�a 0 eklenir.
	if (size == 1) {
		Node* newNode = new Node(0, head, head);
		head->next = newNode;
		head->prev = newNode;
		itr = head;
	}
	// sa�a ekleme algoritmas� kullan�l�r.
	else {
		Node*iter = head;
		Iterator i;
		Node* endNode = i.EndNode(head, size);
		while (iter != endNode) {
			if (iter->data == 0)
				break;
			iter = iter->next;
		}
		Node* newNode = new Node(0, itr->next, itr);
		itr->next->prev = newNode;
		itr->next = newNode;
		itr = head;
	}
}

//Liste yazd�l�r
void CircularDoublyLinkedList::Yazdir(CircularDoublyLinkedList* list) {
	int index = 0;

	cout << "Sifre: ";

		for (Node *itr = list->head; index < list->size; itr = itr->next, index++) {
			cout <<(char)itr->data;
		}

}

//Y�k�c� fonksiyon.
//Olu�turlan liste ListCreator i�erisinde silinmi�tir.
CircularDoublyLinkedList::~CircularDoublyLinkedList(){
	delete head;
	delete itr;
}