//
// Created by casper on 16.11.2017.
//

#ifndef PROJECT2_BARISTA_H
#define PROJECT2_BARISTA_H


class Barista {
public:
    bool empty;
    double workTime;

    Barista();
    Barista (const Barista& _other);
    Barista& operator=(const Barista& _other);
    ~Barista();


};


#endif //PROJECT2_BARİSTA_H
