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
class Sistema {
private:
    vector <Registro*> dados;
public:

    Sistema(string arqDados) {
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
            }
        } else {
            cout << "Erro ao abrir o arquivo!" << endl;
        }
        cout << dados.size() << endl;
        system("pause");
    };
    int hash1(string palavra) {
        int temp = 0;
        for(int i=0; i<palavra.size(); i++) {
            temp+=palavra[i];
        }
        return temp;
    }
    ~Sistema() {};

    void imprimiRegistroTeste() {
        vector<string>aleatorio;
        for(vector<Registro*>::iterator it = this->dados.begin(); it != this->dados.end(); ++it) {
//            cout << (*it)->getOrderNumber() << '\t';
//            cout << (*it)->getQuantityOrdered() << '\t';
//            cout << (*it)->getPriceEach() << '\t';
//            cout << (*it)->getOrderDate() << '\t';
//            cout << (*it)->getStatus() << '\t';
//            cout << (*it)->getProductLine() << '\t';
//            cout << (*it)->getProductCode() << '\t';
//            cout << (*it)->getCustomerName() << '\t';
            aleatorio.push_back((*it)->getCity());
            cout << (*it)->getCity() << '\t';
//            cout << (*it)->getCountry() << '\t';
//            cout << (*it)->getContactLastName() << '\t';
//            cout << (*it)->getContactFirstName() << '\t';
//            cout << (*it)->getDealSize() << '\n';

        }
    }

};

int main() {
    int opc;
    string arquivo = "toy_sales.csv", nomeArq;
    Sistema *sistema = new Sistema(arquivo);
    //sistema->imprimiRegistroTeste();

    while(1) {
        system("cls");
        cout << "1 - Localizar por Order Number" << endl;
        cout << "2 - Localizar por Product Code e Country" << endl;
        cout << "3 - Exportar por city" << endl;
        cout << "4 - Histogramas" << endl;
        cout << sistema->hash1("Nashua");
        cin >> opc;

    }

    system("pause");
    return 0;
}
