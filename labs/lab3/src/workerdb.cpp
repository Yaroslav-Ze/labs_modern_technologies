#include "workerdb.hpp"
#include <iostream>

WorkerData::WorkerData() : name(""), age(0) {
}

WorkerData::WorkerData(const MyString& imya, int year) : name(imya), age(year) {
}

WorkerData::WorkerData(WorkerData&& other)
    : name(std::move(other.name)), age(other.age) {
    other.age = 0;
}

WorkerData& WorkerData::operator=(WorkerData&& other) {
    if (this != &other) {
        name = std::move(other.name);
        age = other.age;
        other.age = 0;
    }
    return *this;
}

Worker::Worker() : surname(), data() {}

Worker::Worker(Worker&& other)
    : surname(std::move(other.surname)), data(std::move(other.data)) {}

Worker& Worker::operator=(Worker&& other) {
    if (this != &other) {
        surname = std::move(other.surname);
        data = std::move(other.data);
    }
    return *this;
}

WorkerDb::WorkerDb() : razm(8), zanyato(0) {
    table = new Worker*[razm];
    sizes = new int[razm];
    razmery = new int[razm];

    for (int i = 0; i < razm; i++) {
        table[i] = nullptr;
        sizes[i] = 0;
        razmery[i] = 0;
    }
}

WorkerDb::~WorkerDb() {
    for (int i = 0; i < razm; i++) {
        delete[] table[i];
    }
    delete[] table;
    delete[] sizes;
    delete[] razmery;
}


int WorkerDb::hash(const MyString& surname) const {
    int h = 0;
    int length = surname.get_len();

    for (int i = 0; i < length; i++) {
        unsigned char c = surname[i]; // чтобы былоо положителным
        h = h * 37 + c;  // набираем хэш-сумму
    }

    return h % razm; // определяем куда положить
}

void WorkerDb::rehash() {
    int old_capacity = razm;
    Worker** old_table = table;
    int* old_sizes = sizes;
    int* old_capacities = razmery;

    razm *= 2;
    table = new Worker*[razm];
    sizes = new int[razm];
    razmery = new int[razm];
    zanyato = 0;

    for (int i = 0; i < razm; i++) {
        table[i] = nullptr;
        sizes[i] = 0;
        razmery[i] = 0;
    }

    for (int i = 0; i < old_capacity; i++) {
        for (int j = 0; j < old_sizes[i]; j++) {
            Worker worker = std::move(old_table[i][j]);
            (*this)[worker.surname] = std::move(worker.data);
        }
        delete[] old_table[i];
    }

    delete[] old_table;
    delete[] old_sizes;
    delete[] old_capacities;
}

WorkerData& WorkerDb::operator[](const MyString& surname) {
    int ind = hash(surname);

    for (int i = 0; i < sizes[ind]; i++) {
        if (table[ind][i].surname == surname) {
            return table[ind][i].data;
        }
    }

    if (zanyato >= razm) {
        rehash();
        ind = hash(surname);
    }

    if (sizes[ind] >= razmery[ind]) {
        int newc = razmery[ind] == 0 ? 1 : razmery[ind] * 2;
        Worker* newb = new Worker[newc];

        for (int i = 0; i < sizes[ind]; i++) {
            newb[i] = std::move(table[ind][i]);
        }

        delete[] table[ind];
        table[ind] = newb;
        razmery[ind] = newc;
    }

    table[ind][sizes[ind]].surname = surname;
    table[ind][sizes[ind]].data = WorkerData();
    sizes[ind]++;
    zanyato++;

    return table[ind][sizes[ind] - 1].data;
}

WorkerData& WorkerDb::operator[](const char* surname) {
    return (*this)[MyString(surname)];
}

WorkerDb::Iterator::Iterator(WorkerDb* db, int n, int ind)
    : db(db), nomer(n), index(ind) {}

WorkerData& WorkerDb::Iterator::operator*() {
    return db->table[nomer][index].data;
}

WorkerData* WorkerDb::Iterator::operator->() {
    return &db->table[nomer][index].data;
}

WorkerDb::Iterator& WorkerDb::Iterator::operator++() {
    index++;
    while (nomer < db->razm) {
        if (index < db->sizes[nomer]) {
            break;
        }
        nomer++;
        index = 0;
    }
    return *this;
}

WorkerDb::Iterator WorkerDb::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool WorkerDb::Iterator::operator!=(const Iterator& other) const {
    return nomer != other.nomer || index != other.index;
}

bool WorkerDb::Iterator::operator==(const Iterator& other) const {
    return nomer == other.nomer && index == other.index;
}

MyString WorkerDb::Iterator::key() const {
    return db->table[nomer][index].surname;
}

WorkerDb::Iterator WorkerDb::begin() {
    for (int i = 0; i < razm; ++i) {
        if (sizes[i] > 0) {
            return Iterator(this, i, 0);
        }
    }
    return end();
}

WorkerDb::Iterator WorkerDb::end() {
    return Iterator(this, razm, 0);
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

/*WorkerDb::WorkerDb() {
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
        newdb[i] = std::move(arr[i]);
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
}*/