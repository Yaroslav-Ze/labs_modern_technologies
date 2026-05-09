#include "string.hpp"

struct WorkerData {
    MyString name;
    int age;

    WorkerData();
    WorkerData(const MyString& imya, int year);

    WorkerData(WorkerData&& other);
    WorkerData& operator=(WorkerData&& other);
};

struct Worker {
    MyString surname;   
    WorkerData data;  

    Worker();
    
    Worker(Worker&& other);
    Worker& operator=(Worker&& other);
};

class WorkerDb {
private:
    Worker** table; // Массив указателей на Worker
    int* sizes;    // количество элементов в каждом подотделе
    int* razmery; // вместимость каждого подотдела
    int razm;  // общий размер 
    int zanyato;   // занятое количество элементов

    int hash(const MyString& surname) const;
    void rehash();

public:
    WorkerDb();
    ~WorkerDb();

    WorkerData& operator[](const MyString& surname);
    WorkerData& operator[](const char* surname);

    class Iterator {
    private:
        WorkerDb* db;
        int nomer;
        int index;

    public:
        Iterator(WorkerDb* db, int n, int ind);

        WorkerData& operator*();
        WorkerData* operator->();

        Iterator& operator++();
        Iterator operator++(int);

        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;

        MyString key() const;
    };

    Iterator begin();
    Iterator end();
};

void print_db(WorkerDb& db);
double get_avg_age(WorkerDb& db);

/*
class WorkerDb {
    Worker* arr;
    int zanyato;
    int dostupno;

    void rashirenie();

public:
    WorkerDb();
    ~WorkerDb();

    WorkerData& operator[](const MyString& surname);
    WorkerData& operator[](const char* surname);

    class Iterator {
    private:
        Worker* ptr;

    public:
        Iterator(Worker* p);

        WorkerData& operator*();
        WorkerData* operator->();

        Iterator& operator++();      
        Iterator operator++(int);   

        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;

        MyString key() const;
    };

    Iterator begin();
    Iterator end();
};

void print_db(WorkerDb& db);
double get_avg_age(WorkerDb& db);

*/