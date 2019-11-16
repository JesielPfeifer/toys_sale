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
        int value = 0;
        for(unsigned int i = 0; i < key.length(); i++)
            value += key[i];
        return value % length;
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
    }

    void printTable() {
        cout << endl << "HashTable:";
        for(int i = 0; i < this->length; i++) {
            cout << endl << "List:  " << i << ": ";
            table[i].printList();
        }
    }

    void printHistogram() {
        int flag = 0;
        cout << "\n\nHash Table Contains ";
        cout << this->getNumberOfItems() << " Items\n";
        for(int i = 0; i < this->length; i++) {
            flag =0;
            cout << i + 1 << ":\t";
            for(int j = 0; j < this->table[i].size(); j++) {
                flag++;
            }
            cout << flag;
            cout << "\n";
        }
    }
    int getNumberOfItems() {
        int itemCount = 0;
        for(int i = 0; i < this->length; i++)
            itemCount += this->table[i].size();
        return itemCount;
    }

    int getLenght() {
        return this->length;
    }

    ~HashTable() {
        delete [] this->table;
    }
};

class Sistema {
private:
    vector <Registro*> dados;
    HashTable<Registro*> *hashCidade;

public:

    Sistema(string arqDados) {
        hashCidade = new HashTable<Registro*>(11);
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
                hashCidade->insert(reg->getCity(), reg);
            }
        } else {
            cout << "Erro ao abrir o arquivo!" << endl;
        }
        cout << dados.size() << endl;
        system("pause");
    };

    ~Sistema() {};

    HashTable <Registro*> *getHashCidade() {
        return this->hashCidade;
    }

    void imprimiRegistroTeste() {
        for(vector<Registro*>::iterator it = this->dados.begin(); it != this->dados.end(); ++it) {
            cout << (*it)->getOrderNumber() << '\t';
            cout << (*it)->getQuantityOrdered() << '\t';
            cout << (*it)->getPriceEach() << '\t';
            cout << (*it)->getOrderDate() << '\t';
            cout << (*it)->getStatus() << '\t';
            cout << (*it)->getProductLine() << '\t';
            cout << (*it)->getProductCode() << '\t';
            cout << (*it)->getCustomerName() << '\t';
            cout << (*it)->getCity() << '\t';
            cout << (*it)->getCountry() << '\t';
            cout << (*it)->getContactLastName() << '\t';
            cout << (*it)->getContactFirstName() << '\t';
            cout << (*it)->getDealSize() << '\n';
        }
    }
    void imprimiteste() {
        for(int i = 0; i < getHashCidade()-)
    }

    void exportNewCity(string cityName) {
        string novoArq = "Toy Sales " + cityName + ".csv";
        fstream arq;
        arq.open(novoArq.c_str(), fstream::out);
        if(arq.is_open()) {
            cout << "Salvando dados filtrados em novo arquivo..." << endl;
            arq << "ORDERNUMBER;QUANTITYORDERED;PRICEEACH;ORDERDATE;STATUS;PRODUCTLINE;PRODUCTCODE;CUSTOMERNAME;CITY;COUNTRY;CONTACTLASTNAME;CONTACTFIRSTNAME;DEALSIZE\n";
            for(int i = 0; i < getHashCidade()->getNumberOfItems(); i++) {
                arq << getHashCidade()->getItem(cityName)->getOrderNumber() << ';';
                arq << getHashCidade()->getItem(cityName)->getQuantityOrdered() << ';';
                arq << getHashCidade()->getItem(cityName)->getPriceEach() << ';';
                arq << getHashCidade()->getItem(cityName)->getOrderDate() << ';';
                arq << getHashCidade()->getItem(cityName)->getStatus() << ';';
                arq << getHashCidade()->getItem(cityName)->getProductLine() << ';';
                arq << getHashCidade()->getItem(cityName)->getProductCode() << ';';
                arq << getHashCidade()->getItem(cityName)->getCustomerName() << ';';
                arq << getHashCidade()->getItem(cityName)->getCity() << ';';
                arq << getHashCidade()->getItem(cityName)->getCountry() << ';';
                arq << getHashCidade()->getItem(cityName)->getContactLastName() << ';';
                arq << getHashCidade()->getItem(cityName)->getContactFirstName() << ';';
                arq << getHashCidade()->getItem(cityName)->getDealSize() << '\n';
            }
        }
    }
};

int main() {
    int opc, order;
    string arquivo = "toy_sales.csv", nomeArq, cityName;
    Sistema *sistema = new Sistema(arquivo);
    sistema->getHashCidade()->printHistogram();
    sistema->imprimiteste();

    cout << endl;

    system("pause");


    while(1) {
        system("cls");
        cout << "1 - Localizar por Order Number" << endl;
        cout << "2 - Localizar por Product Code e Country" << endl;
        cout << "3 - Exportar por city" << endl;
        cout << "4 - Histogramas" << endl;
        cin >> opc;

        switch(opc) {
//        case 1:
//            cout << "Digite o numero de ordem que deseja pesquisar: ";
//            cin >> order;
//            sistema->findOrderNumber(order);
//            break;
//        case 2:
//            break;
        case 3:
            cout << "Digite o nome da cidade da qual deseja exportar os dados: ";
            cin.ignore();
            getline(cin, cityName);
            sistema->exportNewCity(cityName);
            system("pause");
            break;
        }
    }
    system("pause");
    return 0;
}
