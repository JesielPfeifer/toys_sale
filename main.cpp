#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

class Registro {
private:
    int orderNumber, quantityOrdered;
    float priceEach;
    string orderDate, status, productLine, productCode, customerName;
    string city, country, contactLastName, contactFirstName, dealSize;
    string linhaArq;
public:
    Registro() {};

    Registro(string linhaArq) {
        this->linhaArq = linhaArq;
        string issOrderNumber, issQuantityOrdered, issPriceEach;
        istringstream issLinha(linhaArq);

        getline(issLinha,issOrderNumber, ';');
        this->orderNumber = atoi(issOrderNumber.c_str());

        getline(issLinha,issQuantityOrdered, ';');
        this->quantityOrdered = atoi(issQuantityOrdered.c_str());

        getline(issLinha,issPriceEach, ';');
        this->priceEach = atof(issPriceEach.c_str());

        getline(issLinha,orderDate, ';');
        getline(issLinha,status, ';');
        getline(issLinha,productLine, ';');
        getline(issLinha,productCode, ';');
        getline(issLinha,customerName, ';');
        getline(issLinha,city, ';');
        getline(issLinha,country, ';');
        getline(issLinha,contactLastName, ';');
        getline(issLinha,contactFirstName, ';');
        getline(issLinha,dealSize, '\n');

    }

    int getOrderNumber() {
        return this->orderNumber;
    }
    int getQuantityOrdered() {
        return this->quantityOrdered;
    }
    float getPriceEach() {
        return this->priceEach;
    }
    string getOrderDate() {
        return this->orderDate;
    }
    string getStatus() {
        return this->status;
    }
    string getProductLine() {
        return this->productLine;
    }
    string getProductCode() {
        return this->productCode;
    }
    string getCustomerName() {
        return this->customerName;
    }
    string getCity() {
        return this->city;
    }
    string getCountry() {
        return this->country;
    }
    string getContactLastName() {
        return this->contactLastName;
    }
    string getContactFirstName() {
        return this->contactFirstName;
    }
    string getDealSize() {
        return this->dealSize;
    }
};

template <class T>
class HItem {
private:
    string key;
    T element;
    HItem *next;
    HItem *previous;

public:
    HItem(T element) {
        this->element = element;
        this->next = NULL;
    }
    string getKey() {
        return this->key;
    }
    void setKey(string key) {
        this->key = key;
    }
    void setKey(int key) {
        this->key = key;
    }
    T getElement() {
        return this->element;
    }
    void setElement(T element) {
        this->element = element;
    }
    HItem* getNext() {
        return this->next;
    }
    void setNext(HItem *next) {
        this->next = next;
    }
    HItem* getPrevious() {
        return this->previous;
    }
    void setPrevious(HItem *previous) {
        this->previous = previous;
    }
};

template <class T>
class HLinkedList {
    HItem<T> *head;
    HItem<T> *tail;
    int length;
public:
    HLinkedList() {
        head = tail = 0;
        length = 0;
    }
    bool isEmpty() {
        return head == 0;
    }
    int size() {
        return this->length;
    }

    HItem<T>* getItem(string key) {
        HItem<T>* current = head;
        while(current != NULL && current->getKey() != key) {
            current = current->getNext();
        }
        return current;
    }

    void insert(string key, T element) {
        bool empty = this->isEmpty();
        HItem<T> *node = new HItem<T>(element);
        node->setKey(key);

        node->setPrevious(this->tail);
        node->setNext(NULL);

        if(empty) {
            this->tail = this->head = node;
        } else {
            this->tail->setNext(node);
            this->tail = node;
        }
        this->length++;
    }

    void printList() {
        HItem<T>* current = head;
        cout<< "registro: "<<endl;
        cout << current->getElement()<<endl;
        cout << current->getNext()<<endl;
        cout << "end"<<endl;
        while(current != NULL) {
            cout << current->getElement();
            current = current->getNext();
            if(current)
                cout << ", ";
        }
    }


//    unsigned int find(string elemento) {
//        HItem *current = this->front();
//        unsigned int indice = 0;
//        while(current != NULL) {
//            if(current->getElement() != elemento) {
//                current = current->getNext();
//                indice++;
//            } else {
//                return indice;
//            }
//        }
//    }
//    HItem* at(int position) {
//        HItem *current = this->front();
//        unsigned int indice = 0;
//        while(current != NULL) {
//            if(indice != position) {
//                indice++;
//                current = current->getNext();
//            } else {
//                return current;
//            }
//        }
//        return NULL;
//    }

};

template <class T>
class HashTable {
    HLinkedList<T> *table;
    int length;

    int hash(string key) {

        int retorno;
        if(key == "classicCars") {
            retorno = 0;
        } else if(key == "motorcycles") {
            retorno = 1;
        } else if(key == "planes") {
            retorno = 2;
        } else if(key == "ships") {
            retorno = 3;
        } else if(key == "trains") {
            retorno = 4;
        } else if(key == "trucksAndBuses") {
            retorno = 5;
        } else if(key == "vintageCars") {
            retorno = 6;
        } else {
            int value = 0;
            for(unsigned int i = 0; i < key.length(); i++)
                value += key[i];
            retorno = value % length;
        }
        return retorno;
    }

public:
    HashTable(int length) {
        table = new HLinkedList<T>[length];
        this->length = length;
    }

    void insert(string key, T element) {
        int index = hash(key);
        table[index].insert(key, element);
    }

    bool remove(string key) {
        int index = hash(key);
        return table[index].remove(key);
    }

    T getItem(string key) {
        int index = hash(key);
        HItem<T>* item = table[index].getItem(key);
        if(item)
            return item->getElement();
//        else
//            return key + ":\tnot found";
    }

    void printTable() {
        cout << endl << "HashTable:";
        for(int i = 0; i < this->length; i++) {
            cout << endl << "List:  " << i << ": ";
            table[i].printList();
        }
    }

    HLinkedList<T> *getTable() {
        return this->table;
    }

    void printHistogram() {
        int flag;
        cout << "\n\nHash Table Contains ";
        cout << this->getNumberOfItems() << " Items\n";
        for(int i = 0; i < this->length; i++) {
            flag = 0;
            cout << i + 1 << ":\t";
            for(int j = 0; j < this->table[i].size(); j++)
                flag++;
        }
        cout << flag << endl;
    }

    int getNumberOfItems() {
        int itemCount = 0;
        for(int i = 0; i < this->length; i++)
            itemCount += this->table[i].size();
        return itemCount;
    }
    int getLength() {
        return this->length;
    }

    ~HashTable() {
        delete [] this->table;
    }
};


class Sistema {
private:
    vector <Registro*> dados;
    HashTable <Registro*> *hashProductLine;
public:

    Sistema(string arqDados) {
        hashProductLine = new HashTable<Registro*>(7);
        fstream arq;
        arq.open(arqDados.c_str(), fstream::in);
        string linha, topLine;
        cout << dados.size() << endl;
        if(arq.is_open()) {
            getline(arq,topLine);
            if(topLine != "ORDERNUMBER;QUANTITYORDERED;PRICEEACH;ORDERDATE;STATUS;PRODUCTLINE;PRODUCTCODE;CUSTOMERNAME;CITY;COUNTRY;CONTACTLASTNAME;CONTACTFIRSTNAME;DEALSIZE\n");
            while(!arq.eof()) {
                getline(arq,linha,'\n');
                Registro *reg = new Registro(linha);
                dados.push_back(reg);
                this->hashProductLine->insert(reg->getProductLine(), reg);
            }
        } else {
            cout << "Erro ao abrir o arquivo!" << endl;
        }
        cout << dados.size() << endl;
        system("pause");
    };


    ~Sistema() {};

    HashTable<Registro*> *getHashProductLine() {
        return this->hashProductLine;
    }

    void getRegistroProductLineCountry(string productLine, string country) {
        int flag = 0;

        getHashProductLine()->getTable()->printList();
        cout<<endl;
        for(int i = 0; i < getHashProductLine()->getNumberOfItems(); i++) {
            flag++;
        }
        cout << flag << endl;
        //return this->hashProductLine;
    }

    string toCamelCase(string palavra) {
        char c, anterior;
        int i = 0;
        string camelCase = "";
        while (palavra[i]) {
            c = palavra[i];
            if (c != ' ') {
                if (anterior == ' ') {
                    camelCase += toupper(c);
                } else {
                    camelCase += tolower(c);
                }
            }
            anterior = palavra[i];
            i++;
        }
        return camelCase;
    }

};

int main() {
    int opc;
    string productLine = "Motorcycles", country = "brazil";
    string arquivo = "toy_sales.csv", nomeArq;
    Sistema *sistema = new Sistema(arquivo);
    //sistema->imprimiRegistroTeste();

    while(1) {
        system("cls");
        cout << "1 - Localizar por Order Number" << endl;
        cout << "2 - Localizar por Product Line e Country" << endl;
        cout << "3 - Exportar por city" << endl;
        cout << "4 - Histogramas" << endl;
        //cout << sistema->hashProductLine("motorcycle");
        cin >> opc;
        switch(opc) {
        case 1:
            break;
        case 2:
            sistema->getRegistroProductLineCountry(productLine, country);
            system("pause");
            break;
        case 3:
            break;
        case 4:
            sistema->getHashProductLine()->printHistogram();
            break;
        }

    }

    system("pause");
    return 0;
}
