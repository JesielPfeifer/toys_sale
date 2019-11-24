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

        getline(issLinha, issOrderNumber, ';');
        this->orderNumber = atoi(issOrderNumber.c_str());

        getline(issLinha, issQuantityOrdered, ';');
        this->quantityOrdered = atoi(issQuantityOrdered.c_str());

        getline(issLinha, issPriceEach, ';');
        this->priceEach = atof(issPriceEach.c_str());

        getline(issLinha, orderDate, ';');
        getline(issLinha, status, ';');
        getline(issLinha, productLine, ';');
        getline(issLinha, productCode, ';');
        getline(issLinha, customerName, ';');
        getline(issLinha, city, ';');
        getline(issLinha, country, ';');
        getline(issLinha, contactLastName, ';');
        getline(issLinha, contactFirstName, ';');
        getline(issLinha, dealSize, '\n');

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

template<class T>
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

    HItem *getNext() {
        return this->next;
    }

    void setNext(HItem *next) {
        this->next = next;
    }

    HItem *getPrevious() {
        return this->previous;
    }

    void setPrevious(HItem *previous) {
        this->previous = previous;
    }
};

template<class T>
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

    HItem<T> *getItem(string key) {
        HItem<T> *current = head;
        while (current != NULL && current->getKey() != key) {
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

        if (empty) {
            this->tail = this->head = node;
        } else {
            this->tail->setNext(node);
            this->tail = node;
        }
        this->length++;
    }

    void printList() {
        HItem<T> *current = head;
        int flag = 0;
        while (current != NULL) {
            flag++;
            cout << current->getElement();
            current = current->getNext();
            if (current)
                cout << ", ";
        }
        cout << "\nTotal: " << flag << endl;
    }

    string saveNewFile(string city) {
        HItem<T> *current = head;
        stringstream oss;
        while (current != NULL) {
            if (current->getElement()->getCity() == city) {
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
                oss << current->getElement()->getDealSize() << '\n';
            }
            current = current->getNext();
        }
        return oss.str();
    }

    void printListCountry(string country) {
        // TODO: Remover do HLinkedList e falar com o sor sobre a duplicata
        HItem<T> *current = head;
        while (current != NULL) {
            if (current->getElement()->getCountry() == country) {
                cout << current->getElement()->getOrderNumber() << "\t";
                cout << current->getElement()->getOrderDate() << "\t";
                cout << current->getElement()->getStatus() << "\t";
                cout << current->getElement()->getCity() << "\t";
                cout << current->getElement()->getCustomerName() << endl;
            }
            current = current->getNext();
        }
    }
};


template<class T>
class HashTable {
    HLinkedList<T> *table;
    int length;

    int hash(string key) {

        int retorno;
        if (key == "Classic Cars") {
            retorno = 0;
        } else if (key == "Motorcycles") {
            retorno = 1;
        } else if (key == "Planes") {
            retorno = 2;
        } else if (key == "Ships") {
            retorno = 3;
        } else if (key == "Trains") {
            retorno = 4;
        } else if (key == "Trucks and Buses") {
            retorno = 5;
        } else if (key == "Vintage Cars") {
            retorno = 6;
        } else {
            int value = 0;
            for (unsigned int i = 0; i < key.length(); i++)
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
        HItem<T> *item = table[index].getItem(key);
        if (item)
            return item->getElement();
//        else
//            return key + ":\tnot found";
    }

    void printTable() {
        cout << endl << "HashTable:";
        for (int i = 0; i < this->length; i++) {
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
        for (int i = 0; i < this->length; i++) {
            flag = 0;
            cout << i + 1 << ":\t";
            for (int j = 0; j < this->table[i].size(); j++) {
                flag++;
            }
            cout << flag << endl;
        }
    }

    int getNumberOfItems() {
        int itemCount = 0;
        for (int i = 0; i < this->length; i++)
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
        delete[] this->table;
    }
};


class Sistema {
private:
    vector<Registro *> dados;
    HashTable<Registro *> *hashProductLine;
    HashTable<Registro *> *hashCidade;

public:

    Sistema(string arqDados) {
        hashProductLine = new HashTable<Registro *>(7);
        hashCidade = new HashTable<Registro *>(11);
        fstream arq;
        arq.open(arqDados.c_str(), fstream::in);
        string linha, topLine;
        if (arq.is_open()) {
            getline(arq, topLine);
            if (topLine !=
                "ORDERNUMBER;QUANTITYORDERED;PRICEEACH;ORDERDATE;STATUS;PRODUCTLINE;PRODUCTCODE;CUSTOMERNAME;CITY;COUNTRY;CONTACTLASTNAME;CONTACTFIRSTNAME;DEALSIZE\n");
            while (!arq.eof()) {
                getline(arq, linha, '\n');
                Registro *reg = new Registro(linha);
                dados.push_back(reg);
                this->hashProductLine->insert(reg->getProductLine(), reg);
                this->hashCidade->insert(reg->getCity(), reg);
            }
        } else {
            cout << "Erro ao abrir o arquivo!" << endl;
        }
    };


    ~Sistema() {};

    HashTable<Registro *> *getHashProductLine() {
        return this->hashProductLine;
    }

    HashTable<Registro *> *getHashCidade() {
        return this->hashCidade;
    }

    void getRegistroProductLineCountry(string productLine, string country) {
        int flag = 0;
        cout << "Product line: " << productLine << endl;
        int indice = getHashProductLine()->getHashIndice(productLine);
        getHashProductLine()->getTable()[indice].printListCountry(country);
        cout << endl;
    }

    void exportNewCity(string cityName) {
        string novoArq = "Toy Sales " + cityName + ".csv";
        fstream arq;
        int indice = getHashCidade()->getHashIndice(cityName);
        arq.open(novoArq.c_str(), fstream::out);
        if (arq.is_open()) {
            cout << "Salvando dados filtrados em novo arquivo..." << endl;
            arq
                    << "ORDERNUMBER;QUANTITYORDERED;PRICEEACH;ORDERDATE;STATUS;PRODUCTLINE;PRODUCTCODE;CUSTOMERNAME;CITY;COUNTRY;CONTACTLASTNAME;CONTACTFIRSTNAME;DEALSIZE\n";
            arq << getHashCidade()->getTable()[indice].saveNewFile(cityName);
        }
    }

    void printHistrogramaProductLine() {
        int flag;
        vector<float> porcent;
        cout << "\n\nHistrograma Product Line" << endl;
        int total = this->getHashProductLine()->getNumberOfItems();
        int totalIndice = this->getHashProductLine()->getLength();

        for (int i = 0; i < totalIndice; i++) {
            flag = 0;
            for (int j = 0; j < this->getHashProductLine()->getTable()[i].size(); j++) {
                flag++;
            }

            porcent.push_back((100.0 * flag) / total);
        }

        for (int i = 0; i < totalIndice; i++) {
            printf("Chave %2d: ", i + 1);
            cout << this->toPercent(porcent[i]);
            printf(" %5.1f% %", porcent[i]);
            cout << endl;
        }
    }

    void printHistrogramaCity() {
        int flag;
        vector<float> porcent;
        cout << "\n\nHistrograma City" << endl;
        int total = this->getHashCidade()->getNumberOfItems();
        int totalIndice = this->getHashCidade()->getLength();

        for (int i = 0; i < totalIndice; i++) {
            flag = 0;
            for (int j = 0; j < this->getHashCidade()->getTable()[i].size(); j++) {
                flag++;
            }

            porcent.push_back((100.0 * flag) / total);
        }

        for (int i = 0; i < totalIndice; i++) {
            printf("Chave %2d: ", i + 1);
            cout << this->toPercent(porcent[i]);
            printf(" %5.1f% %", porcent[i]);
            cout << endl;
        }
    }

    string toPercent(float p) {
        int porCent = 0;
        string ret = "";
        for (int i = 0; i <= 100; i += 1) {
            if (p < (i + 0.5)) {
                porCent = i;
                break;
            }
        }


        for (int i = 0; i < 100; i++) {
            if (porCent > i) {
                ret += "=";
            } else {
                ret += ".";
            }
        }

        return ret;
    }


};

int main() {
    int opc;
    string productLine = "Motorcycles", country = "Germany";
    string arquivo = "toy_sales.csv", nomeArq, cityName;
    Sistema *sistema = new Sistema(arquivo);

    while (1) {
        system("cls");
        cout << "1 - Localizar por Order Number" << endl;
        cout << "2 - Localizar por Product Line e Country" << endl;
        cout << "3 - Exportar por city" << endl;
        cout << "4 - Histogramas" << endl;
        cin >> opc;
        switch (opc) {
            case 1:
                break;
            case 2:
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
                sistema->printHistrogramaProductLine();
                sistema->printHistrogramaCity();
                system("pause");
                break;
        }

    }

    system("pause");
    return 0;
}
