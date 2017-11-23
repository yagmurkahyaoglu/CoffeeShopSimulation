
#include "Barista.h"

Barista::Barista() {
    this->workTime = 0;
    this->empty = true;
}

Barista::Barista(const Barista &_other) {
    this->empty = _other.empty;
    this->workTime = _other.workTime;
}

Barista& Barista::operator=(const Barista &_other) {
    this->empty = _other.empty;
    this->workTime = _other.workTime;
    return *this;
}

Barista::~Barista() {}
