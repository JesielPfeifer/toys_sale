#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;


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
        while(current != NULL) {
            cout << current->getElement();
            current = current->getNext();
            if(current)
                cout << ", ";
        }
    }

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
            return key + ":\t" + item->getElement();
        else
            return key + ":\tnot found";
    }

    void printTable() {
        cout << endl << "HashTable:";
        for(int i = 0; i < this->length; i++) {
            cout << endl << "List:  " << i << ": ";
            table[i].printList();
        }
    }

    void printHistogram() {
        cout << "\n\nHash Table Contains ";
        cout << this->getNumberOfItems() << " Items\n";
        for(int i = 0; i < this->length; i++) {
            cout << i + 1 << ":\t";
            for(int j = 0; j < this->table[i].size(); j++)
                cout << " X";
            cout << "\n";
        }
    }

    int getNumberOfItems() {
        int itemCount = 0;
        for(int i = 0; i < this->length; i++)
            itemCount += this->table[i].size();
        return itemCount;
    }

    ~HashTable() {
        delete [] this->table;
    }
};

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

    HashTable<Registro*> *getRegistroProductLineCountry(string key) {
        // fazer essa caralha
        return this->hashProductLine;
    }

    void imprimiRegistroTeste() {
        vector<string>aleatorio;
        for(vector<Registro*>::iterator it = this->dados.begin(); it != this->dados.end(); ++it) {
            aleatorio.push_back((*it)->getCity());
            cout << (*it)->getCity() << '\t';
        }
    }

};

int main() {
    int opc;
    string fodase = "motorcycle";
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



        if(opc == 2){

        }

    }

    system("pause");
    return 0;
}
