
#include "Customer.h"

Customer::Customer(double _arrival, double _order, double _brew, double _price) {
    this->arrival = _arrival;
    this->order = _order;
    this->brew = _brew;
    this->price = _price;
    this->orderIn = 0;
    this->brewIn = 0;
    this->total = this->arrival;
    this->where = 0;
    this->cash = 0;
    this->bar = 0;
}

Customer::Customer(const Customer &_other) {

    this->arrival = _other.arrival;
    this->order = _other.order;
    this->brew = _other.brew;
    this->price = _other.price;
    this->orderIn = _other.orderIn;
    this->brewIn = _other.brewIn;
    this->cash = _other.cash;
    this->bar = _other.bar;
    this->total =_other.total;
    this->where = _other.where;
}

Customer& Customer::operator=(const Customer &_other) {
    this->arrival = _other.arrival;
    this->order = _other.order;
    this->brew = _other.brew;
    this->price = _other.price;
    this->orderIn = _other.orderIn;
    this->brewIn = _other.brewIn;
    this->cash = _other.cash;
    this->bar = _other.bar;
    this->total =_other.total;
    this->where = _other.where;

    return *this;
}

Customer::~Customer() {
}