#include <iostream>
#include <cassert>
#include <cstdio>
#include "boolarray.hpp"

int nuzhno_bytes(int n) {
    return (n + 7) / 8;
}

int index_byte(int bool_index) {
    return bool_index / 8;
}

int index_bit(int bool_index) {
    return bool_index % 8;
}

bool BoolArray::get_bit(int index) const {
    if (index < 0 || index >= len) {
        throw std::out_of_range("Индекс вне диапазона");
    }

    int b = index_byte(index);
    int bit = index_bit(index);
        //Байты идут слева направо по индексам массива а биты внутри байта нумеруются справа налево
    return (arrb[b] >> bit) & 1; // сдвинули нужный бит до правого края байта, и конъюнкцией с '00000001' получили значение Булика  
}

void BoolArray::set_bit(int index, bool value) {
    if (index < 0 || index >= len) {
        throw std::out_of_range("Индекс вне диапазона");
    }

    int byte = index_byte(index);
    int bit = index_bit(index);

    if (value) {
        arrb[byte] = arrb[byte] | (1 << bit);
    } else {
        arrb[byte] = arrb[byte] & (~(1 << bit));
    }
}

// --------------------

BoolArray::Boolik::Boolik(BoolArray& a, int i) : arr(a), index(i) {}

BoolArray::Boolik& BoolArray::Boolik::operator=(bool value) {
    arr.set_bit(index, value);
    return *this;
}

BoolArray::Boolik& BoolArray::Boolik::operator=(const Boolik& other) {
    arr.set_bit(index, (bool)other);
    return *this;
}

BoolArray::Boolik::operator bool() const {
    return arr.get_bit(index);
}

BoolArray::BoolArray() : arrb(nullptr), len(0) {}

BoolArray::BoolArray(int n, bool value) : len(n) {
    if (n < 0) {
        throw std::invalid_argument("Размер < 0");
    }

    int bytes = nuzhno_bytes(len);
    arrb = new unsigned char[bytes];

    unsigned char filler = 0;
    if (value) {
        filler = 255;
    }

    for (int i = 0; i < bytes; i++) {
        arrb[i] = filler;
    }

}

BoolArray::BoolArray(const BoolArray& other) : len(other.len) {
    int bytes = nuzhno_bytes(len);
    arrb = new unsigned char[bytes];

    for (int i = 0; i < bytes; i++) {
        arrb[i] = other.arrb[i];
    }
}

BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] arrb;

        len = other.len;
        int bytes = nuzhno_bytes(len);
        arrb = new unsigned char[bytes];

        for (int i = 0; i < bytes; i++) {
            arrb[i] = other.arrb[i];
        }
    }

    return *this;
}

BoolArray::~BoolArray() {
    delete[] arrb;
}

int BoolArray::size() const {
    return len;
}

BoolArray::Boolik BoolArray::operator[](int index) {
    return Boolik(*this, index);
}

bool BoolArray::operator[](int index) const {
    return get_bit(index);
}

void BoolArray::resize(int new_size, bool value) {
    if (new_size < 0) {
        throw std::invalid_argument("неправильный размер");
    }

    int old = len;
    int newbytes = nuzhno_bytes(new_size);

    unsigned char* new_data = new unsigned char[newbytes];

    for (int i = 0; i < newbytes; i++) {
        new_data[i] = 0;
    }

    int minsize = (old < new_size) ? old : new_size;

    for (int i = 0; i < minsize; i++) {
        if (get_bit(i)) {
            int b = i / 8;
            int bit = i % 8;
            new_data[b] = new_data[b] | (1 << bit);
        }
    }

    if ((new_size > old) && (value)) {
        for (int i = old; i < new_size; i++) {
            int b = i / 8;
            int bit = i % 8;
            new_data[b] = new_data[b] | (1 << bit);
        }
    }

    delete[] arrb;
    arrb = new_data;
    len = new_size;
}