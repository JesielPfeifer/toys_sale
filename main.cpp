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

    HItem<T>* getHead() {
        return this->head;
    }

    void printList() {
        HItem<T>* current = head;
        int flag = 0;
        while(current != NULL) {
            flag++;
            cout << current->getElement();
            current = current->getNext();
            if(current)
                cout << ", ";
        }
        cout << "\nTotal: " << flag << endl;
    }

    string saveNewFile(string city) {
        HItem<T>* current = head;
        stringstream oss;
        while(current != NULL) {
            if(current->getElement()->getCity() == city) {
                oss << current->getElement()->getOrderNumber() << ';';
                oss << current->getElement()->getQuantityOrdered() << ';';
                oss << current->getElement()->getPriceEach() << ';';
                oss << current->getElement()->getOrderDate() << ';';
                oss << current->getElement()->getStatus() << ';';
                oss << current->getElement()->getProductLine() << ';';
                oss << current->getElement()->getProductCode() << ';';
                oss << current->getElement()->getCustomerName() << ';';
                oss << current->getElement()->getCity() << ';';
                oss << current->getElement()->getCountry() << ';';
                oss << current->getElement()->getContactLastName() << ';';
                oss << current->getElement()->getContactFirstName() << ';';
                oss << current->getElement()->getDealSize() << endl;
            }
            current = current->getNext();
        }
        return oss.str();
    }
};


template <class T>
class HashTable {
    HLinkedList<T> *table;
    int length;

    int hash(string key) {

        int retorno;
        if(key == "Classic Cars") {
            retorno = 0;
        } else if(key == "Motorcycles") {
            retorno = 1;
        } else if(key == "Planes") {
            retorno = 2;
        } else if(key == "Ships") {
            retorno = 3;
        } else if(key == "Trains") {
            retorno = 4;
        } else if(key == "Trucks and Buses") {
            retorno = 5;
        } else if(key == "Vintage Cars") {
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
            for(int j = 0; j < this->table[i].size(); j++) {
                flag++;
            }
            cout << flag << endl;
        }
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
    int getHashIndice(string key) {
        return this->hash(key);
    }

    ~HashTable() {
        delete [] this->table;
    }
};


class Sistema {
private:
    vector <Registro*> dados;
    HashTable<Registro*> *hashProductLine;
    HashTable<Registro*> *hashCidade;

public:

    Sistema(string arqDados) {
        hashProductLine = new HashTable<Registro*>(7);
        hashCidade = new HashTable<Registro*>(11);
        fstream arq;
        arq.open(arqDados.c_str(), fstream::in);
        string linha, topLine;
        if(arq.is_open()) {
            getline(arq,topLine);
            while(!arq.eof()) {
                getline(arq,linha,'\n');
                if(linha != "") {
                    Registro *reg = new Registro(linha);
                    dados.push_back(reg);
                    this->hashProductLine->insert(reg->getProductLine(), reg);
                    this->hashCidade->insert(reg->getCity(), reg);
                }
            }
        } else {
            cout << "Erro ao abrir o arquivo!" << endl;
        }
    };


    ~Sistema() {};

    HashTable<Registro*> *getHashProductLine() {
        return this->hashProductLine;
    }

    HashTable <Registro*> *getHashCidade() {
        return this->hashCidade;
    }


    void getRegistroProductLineCountry(string productLine, string country) {
        int flag = 0;
        cout << "Product line: " << productLine << endl;
        int indice = getHashProductLine()->getHashIndice(productLine);
        cout << "indice: " <<indice << endl;
        getHashProductLine()->getTable()[indice].printList();
        cout<<endl;
    }

    void exportNewCity(string cityName) {
        string novoArq = "Toy Sales " + cityName + ".csv";
        fstream arq;
        int indice = getHashCidade()->getHashIndice(cityName);
        arq.open(novoArq.c_str(), fstream::out);
        if(arq.is_open()) {
            cout << "Salvando dados filtrados em novo arquivo..." << endl;
            arq << "ORDERNUMBER;QUANTITYORDERED;PRICEEACH;ORDERDATE;STATUS;PRODUCTLINE;PRODUCTCODE;CUSTOMERNAME;CITY;COUNTRY;CONTACTLASTNAME;CONTACTFIRSTNAME;DEALSIZE\n";
            arq << getHashCidade()->getTable()[indice].saveNewFile(cityName);
            cout << getHashCidade()->getTable()[indice].saveNewFile(cityName);
        }
    }

    void swap(Registro *xp, Registro *yp) {
        Registro temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void bubbleSort() {
        int conta =0;
        int i, j, len = this->dados.size();
        bool swapped;
        for (i = 0; i < len - 1; i++) {
            swapped = false;
            for (j = 0; j < len - i - 1; j++) {
                if (this->dados[j]->getOrderNumber() > this->dados[j+1]->getOrderNumber()) {
                    swap(this->dados[j], this->dados[j+1]);
                    swapped = true;
                }
            }
            if (swapped == false)
                break;
        }
    }

    int pesquisaBinaria(int orderNum) {
        int inferior, superior, media, flag;
        inferior = 0;
        superior = this->dados.size() - 1;
        while (inferior <= superior) {
            media = (inferior + superior) / 2;
            if (orderNum == this->dados[media]->getOrderNumber()) {
                return media;
            } else if(orderNum > this->dados[media]->getOrderNumber()) {
                inferior = media + 1;
            } else if(orderNum < this->dados[media]->getOrderNumber()) {
                superior = media - 1;
            }
        }
        return -1;
    }

    void imprimePesquisa(int orderNum) {
        int media = this->pesquisaBinaria(orderNum);
        if(pesquisaBinaria(orderNum) != -1) {
            cout << this->dados[media]->getOrderNumber() << endl;
            cout << this->dados[media]->getOrderDate() << endl;
            cout << this->dados[media]->getStatus() << endl;
            cout << this->dados[media]->getCustomerName() << endl;
            cout << this->dados[media]->getCity() << endl;
            cout << this->dados[media]->getCountry() << endl;
            cout << this->dados[media]->getContactLastName() << endl;
            cout << this->dados[media]->getContactFirstName() << endl;
            cout << this->dados[media]->getDealSize() << endl;
            cout << "QUANTITYORDERED\tPRICEEACH\tPRODUCTLINE\tPRODUCTCODE" << endl;
            for(int i = media; i < this->dados.size(); i++) {
                if (this->dados[i]->getOrderNumber() == orderNum) {
                    cout << this->dados[i]->getQuantityOrdered() << '\t' << this->dados[i]->getPriceEach() << '\t';
                    cout << this->dados[i]->getProductLine() << '\t' << this->dados[i]->getProductCode() << endl;
                } else {
                    break;
                }
            }
            for(int i = media ; i > 0 ; i--) {
                if (this->dados[i]->getOrderNumber() == orderNum) {
                    cout << this->dados[i]->getQuantityOrdered() << '\t' << this->dados[i]->getPriceEach() << '\t';
                    cout << this->dados[i]->getProductLine() << '\t' << this->dados[i]->getProductCode() << endl;
                } else {
                    break;
                }
            }
        } else {
            cout << "Order Number inserido NAO EXISTE!" << endl;
        }
    }

};

int main() {
    int opc, order;
    string productLine, country;
    string arquivo = "toy_sales.csv", nomeArq, cityName;
    Sistema *sistema = new Sistema(arquivo);
    sistema->getHashCidade()->printHistogram();
    sistema->bubbleSort();
    system("pause");


    while(1) {
        system("cls");
        cout << "1 - Localizar por Order Number" << endl;
        cout << "2 - Localizar por Product Line e Country" << endl;
        cout << "3 - Exportar por city" << endl;
        cout << "4 - Histogramas" << endl;
        cin >> opc;
        switch(opc) {
        case 1:
            cout << "Digite o Order Number no qual deseja pesquisar: ";
            cin >> order;
            sistema->imprimePesquisa(order);
            system("pause");
            break;
        case 2:
            cout << "Digite o Product Line no qual deseja pesquisar: ";
            getline(cin,productLine);
            cout << "Digite o Country no qual deseja pesquisar: ";
            getline(cin,country);
            sistema->getRegistroProductLineCountry(productLine, country);
            system("pause");
            break;
        case 3:
            cout << "Digite o nome da cidade da qual deseja exportar os dados: ";
            cin.ignore();
            getline(cin, cityName);
            sistema->exportNewCity(cityName);
            system("pause");
            break;
        case 4:
            sistema->getHashProductLine()->printHistogram();
            system("pause");
            break;
        }

    }

    system("pause");
    return 0;
}
