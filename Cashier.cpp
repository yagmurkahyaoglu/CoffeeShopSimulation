//
// Created by casper on 16.11.2017.
//

#include "Cashier.h"

Cashier::Cashier() {
    this->empty = true;
    this->workTime = 0;
}

Cashier::Cashier(const Cashier &_other) {
    this->empty = _other.empty;
    this->workTime = _other.workTime;
}

Cashier& Cashier::operator=(const Cashier &_other) {
    this->empty = _other.empty;
    this->workTime = _other.workTime;
    return *this;
}

Cashier::~Cashier() {}
