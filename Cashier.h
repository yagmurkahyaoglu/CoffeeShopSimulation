//
// Created by casper on 16.11.2017.
//

#ifndef PROJECT2_CASHIER_H
#define PROJECT2_CASHIER_H


class Cashier {
public:
    bool empty;
    double workTime;

    Cashier();
    Cashier (const Cashier& _other);
    Cashier& operator=(const Cashier& _other);
    ~Cashier();
};


#endif //PROJECT2_CASHİER_H
