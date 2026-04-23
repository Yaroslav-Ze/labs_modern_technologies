#include "string.hpp"

struct WorkerData {
    MyString name;
    int age;

    WorkerData();
    WorkerData(const MyString& imya, int year);
};

struct Worker {
    MyString surname;   
    WorkerData data;   
};


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