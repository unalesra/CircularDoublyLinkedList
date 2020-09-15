/**     * @fileDosya CircularDoublyLinkedList.cpp
		* @description ListCreator sýnýfýndan gelen sayýlar ile listenin oluþturulmasý
		* @courseDersi 1A
		* @assignment 1.Ödev
		* @dateKodu 06.08.2020
		* @author Esra Ünal
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

//listenin boyutu döndürülür
int CircularDoublyLinkedList::getSize() {
	return size;
}

////obeb hesaplanýrken öklid algoritmasý kullanýlmýþtýr.
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

//saða ya da sola ekleme iþlemenin kontrol edildiði fonksiyon
void CircularDoublyLinkedList::InsertNode(int data) {
	//boyut sýfýr deðilse yeni obeb bulunur yoksa sýfýr olarak kalmaya devam eder.
	if(size!=0)
		obeb = Obeb(data, head->data);
	
	//boyut sýfýrsa ilk eklenen düðüm head'dir
	if (size == 0) {
		head = new Node(data, head, head);
		size++;
	}
	//obeb ya da mod sýfýrsa algortimaya göre saða eklenir. Boyut bir arttýrýlýr.
	else if (obeb == 0 || data == 0) {
		InsertRight(data);
		this->size++;
	}
	//düðüm sola eklenir boyut bir arttýrýlýr
	else {
		InsertLeft(data);
		this->size++;
	}
}

//Liste içersinde arada bir düðüme ekleme yapýlmasý gerektiðinde false dönerse sola, true dönerse saða ekleme yapýlýr.
bool CircularDoublyLinkedList::ObebKontrol(int obeb, int data) {
	itr = head;
	Iterator iterator;
	Node* endNode = iterator.EndNode(head, size); //son düðüm bulunur
	//yeni obeb, en büyük obebden küçük olduðu sürece döner, eðer yeni obeb en büyük obebden büyükse false döner, sola ekle demektir.
	while (obeb < this->biggestObeb) {
		//yeni obeb, en büyük obebden büyükse, artýk yeni obeb en büyük obeb olur ve sola eklenmesi için false döner.
		if (obeb > this->biggestObeb) {
			this->biggestObeb = obeb;
			return false;
		}
		//eðer obeb=0 gelirse saða eklenmesi içi true döndürülür.
		if (obeb == 0)
			return true;
		//eðer yeni obeb ile en büyük obeb eþitse o düðümde kalýnmalýnmalý ve sola ekleme yapýlmalý
		if (obeb == biggestObeb)
			return false;
		
		//liste içeriinde ilerleme
		itr = itr->next;
		//ilerledikçe yeni obebin hesaplanmasý
		obeb = Obeb(itr->data, data);

		//eðer son düðüme gelinmiþse sola ekleme yapýlmasý için false döner.
		if (itr == endNode) {
			obeb = Obeb(itr->data, data);
			return false;
		}
	}
	
	//while döngüsüne girmediði için yeni obeb en büyük obebden küçük gelmemiþ demektir. Bu durumda en büyük obeb olmalýdýr. Sola eklenmesi için false döner.
	this->biggestObeb = obeb;
	return false;
}

//saða ekle yapýlýr
void CircularDoublyLinkedList::InsertRight(int data) {
	/** Boyut 1 ise, datanýn sýfýr olup olmamasýna göre kontol yapýlýr. Eðer sýfýrsa sýfýr ekleme metodu çaðýrýlýr.
	* boyut bir deðilse ve data 0 gelmemiþse normal saða ekleme algoritmasý uygulanýr
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

//baþa ekleme yapýlýrken mod bulmak ayrý bir metodla saðlanmýþtýr.
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

//Sola ekleme yapýlýr. 
void CircularDoublyLinkedList::InsertLeft(int data) {

//Eðer boyut 1 ise ve mod 0 gelmiþse baþa ekleme yapýlýr. Yoksa sola ekleme algoritmasý kullanýlýr.

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
	// Eðer boyut 1 deðilse
	else {
		int index = 0;
		Iterator iter;
		Node* endNode = iter.EndNode(head, size);  //son düðüm 
		Node* oldHead = NULL;
	
	//Obeb kontrol ile true mu dönecek false mu dönecek kontrol edilir. True dönerse saða ekle metodu çaðýrýlýr. False dönerse sola ekle metodunda devam edilir.
		if (!ObebKontrol(obeb, data)) {
			Node *node = itr;
			
			//mod hesaplanýr
			if (data > this->itr->data) {
				if(this->itr->data!=0)
				index = data % this->itr->data;
			}
			else {
				if (data != 0)
				index = this->itr->data%data;
			}

			//eðer mod 0 geldiyse saða eklensin
			//yoksa sola eklensin
			if (index==0) {
				InsertRight(data);
			}
			else {
				while (index != 0) {
					oldHead = head;
					
					//Eðer sola gide gide düðümün baþýna gelindiyse en baþa ekleme yapýlýr
					if (index >= size) {
						head = new Node(data, oldHead, endNode);
						oldHead->prev = head;
						endNode->next = head;
						itr = head;
						break;
					}
					//Eðer baþa gelinmemiþse index bir azaltýlýr ve önceki düðüme gidilir.
					else {
						index--;
						if(obeb!=this->biggestObeb)
							if(node!=endNode->next && index!=0)
							node = node->prev;
					}
				}
				//Eðer mod kadar ilerlenmiþse düðüm içerisinde sola ekleme algoritmasý çalýþtýrýlýr. (index-- denilerek bunun kontrolü yapýldý.)
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
		//obeb kontrol true dönmüþ demektir. Saða ekle algoritmasý çalýþtýrýlýr.
		else {
			obeb = 0;
			InsertRight(data);
		}
	}
}

//Sýfýra ekleme durumu sonradan düþünüldüðü için programý bozmamak adýna sýfýr eklemesi gereken durumlar için bu fonksiyon yazýlmýþtýr.
void CircularDoublyLinkedList::addZero(){
	//eðer boyut bir ise saða 0 eklenir.
	if (size == 1) {
		Node* newNode = new Node(0, head, head);
		head->next = newNode;
		head->prev = newNode;
		itr = head;
	}
	// saða ekleme algoritmasý kullanýlýr.
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

//Liste yazdýlýr
void CircularDoublyLinkedList::Yazdir(CircularDoublyLinkedList* list) {
	int index = 0;

	cout << "Sifre: ";

		for (Node *itr = list->head; index < list->size; itr = itr->next, index++) {
			cout <<(char)itr->data;
		}

}

//Yýkýcý fonksiyon.
//Oluþturlan liste ListCreator içerisinde silinmiþtir.
CircularDoublyLinkedList::~CircularDoublyLinkedList(){
	delete head;
	delete itr;
}