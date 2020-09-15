/**     * @fileDosya ListCreator.cpp
		* @description Okunan satırdaki sayıların ayıklanıp liste sınıfına gönderilmesi, oluşturulan listenin yazdırılması
		* @courseDersi 1A
		* @assignment 1.Ödev
		* @dateKodu 06.08.2020
		* @author Esra Ünal
*/

#include "ListCreator.hpp"

//kurucu fonksiyon
ListCreator::ListCreator(){
	this->biggestObeb = 0;
}

/**dosyadan okunan satır, bir stringe atanır. Döngü ile string içerisinde dolaşılır.
 *Döngü boşluğa gelinceye kadar ilerler, boşluk gördüğünde boşluktan öncesini okur ve bunu listeye gönderir. Tüm satır bitene kadar bu işlem devam eder. Satır bitince ekrana yazdırılır. Alt satıra 
 *geçmiş olduğu için yeni liste oluşturulur. Aynı işlemler yeni liste üzeriden devam eder.  Dosya bitinceye kadar işlemler devam eder.
 */
void ListCreator::CreateList() {
	list = new CircularDoublyLinkedList();
	string readedNumber = fileReader.ReadFile("Sayilar.txt");
	int size = fileReader.getFileSize();
	string newNumber = "";
	int i = 0;
	int j = 0;
	int k = 0;
	if (readedNumber != "Dosya Bos") {
		while (fileReader.getFileSize() >= i) {
			if (readedNumber[i] == ' ' || readedNumber[i] == '\n') {
				while (i > j) {
					newNumber += readedNumber[j];
					j++;
				}
				this->list->InsertNode(atoi(newNumber.c_str()));
				newNumber = "";
				k++;
				j++;

				if (readedNumber[i] == '\n') {
					list->Yazdir(list);
					cout << endl;
					list = new CircularDoublyLinkedList();
				}
			}
			i++;
		}

	}else
		cout << "Dosya Bos";

}

//yıkıcı fonksiyon
ListCreator::~ListCreator() {
	delete list;
}