#include "workerdb.hpp"
#include <iostream>

WorkerData::WorkerData() : name(""), age(0) {
}

WorkerData::WorkerData(const MyString& imya, int year) : name(imya), age(year) {
}

WorkerDb::WorkerDb() {
    zanyato = 0;
    dostupno = 2;
    arr = new Worker[dostupno];
}

WorkerDb::~WorkerDb() {
    delete[] arr;
}

void WorkerDb::rashirenie() {
    dostupno *= 2;

    Worker* newdb = new Worker[dostupno];

    for (int i = 0; i < zanyato; i++) {
        newdb[i] = arr[i];
    }

    delete[] arr;
    arr = newdb;
}

WorkerData& WorkerDb::operator[](const MyString& surname) {
    for (int i = 0; i < zanyato; i++) {
        if (arr[i].surname == surname) {
            return arr[i].data;
        }
    }

    if (zanyato >= dostupno) {
        rashirenie();
    }

    arr[zanyato].surname = surname;
    arr[zanyato].data = WorkerData();

    zanyato++;

    return arr[zanyato - 1].data;
}

WorkerData& WorkerDb::operator[](const char* surname) {
    return (*this)[MyString(surname)];
}

WorkerDb::Iterator::Iterator(Worker* p) {
    ptr = p;
}

WorkerData& WorkerDb::Iterator::operator*() {
    return ptr->data;
}

WorkerData* WorkerDb::Iterator::operator->() {
    return &ptr->data;
}

WorkerDb::Iterator& WorkerDb::Iterator::operator++() {
    ptr++;
    return *this;
}

WorkerDb::Iterator WorkerDb::Iterator::operator++(int) {
    Iterator temp = *this;
    ptr++;
    return temp;
}

bool WorkerDb::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

bool WorkerDb::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

MyString WorkerDb::Iterator::key() const {
    return ptr->surname;
}

WorkerDb::Iterator WorkerDb::begin() {
    return Iterator(arr);
}

WorkerDb::Iterator WorkerDb::end() {
    return Iterator(arr + zanyato);
}

void print_db(WorkerDb& db) {
    int i = 1;
    for (auto it = db.begin(); it != db.end(); ++it)
        {
            std::cout << i << ". " << it.key() << " " << it->name << ", возраст " << it->age << '\n';
            i++;
        }
}

double get_avg_age(WorkerDb& db) {
    int i = 0;
    double kolvo = 0;
    for (auto it = db.begin(); it != db.end(); ++it)
        {
            i += it->age;
            kolvo++;
        
        }
    return i / kolvo;
}