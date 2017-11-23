
#ifndef PROJECT2_CUSTOMER_H
#define PROJECT2_CUSTOMER_H

#include <iostream>
using namespace std;

class Customer {

public:
    double arrival;
    double order;
    double brew;
    double price;
    double orderIn;
    double brewIn;
    double total;
    int where;
    int cash;
    int bar;

    Customer(double _arrival, double _order, double _brew, double _price);
    Customer(const Customer& _other);
    Customer& operator=(const Customer& _other);
    ~Customer();

};


#endif //PROJECT2_CUSTOMER_H
