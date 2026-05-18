
#include <iostream>
#include "string.hpp"

// ОПТИМАЛЬНОЕ решение для очередей нотификаций и базы раьотников

// Хранить указатель на оптимальное место. если чтото удалено в середине то хранить на это указатель. 
// укказатель 

// приоритеты через дерево?

struct Notification {
    enum Type {
    SYSTEM,
    MESSAGE,
    APP
    };

    struct syst_n {
        MyString prishlo_soob;
        enum serios {
            NORM,
            VAZHNO
        };
        serios ser;
        syst_n(const MyString& p, serios s);
    };
    struct message_n {
        MyString name;
        MyString prishlo_soob;

        message_n(const MyString& n, const MyString& p);
    };
    struct app_n {
        MyString name_app;
        MyString zagolovok;
        MyString prishlo_soob;

        app_n(const MyString& n, const MyString& z, const MyString& p);
    };
    union {
        syst_n* system;
        message_n* message;
        app_n* app;
    } data;

    
    int hour;
    int minute;

    Type type;

    Notification();
    Notification(const Notification& other);
    Notification& operator=(const Notification& other);
    ~Notification();  
    
    void clear();

    void print() const;
};

int right_hour(int h);

int right_minute(int m);

Notification make_system(int hou, int min, const MyString& msg, Notification::syst_n::serios lvl);
Notification make_message(int hou, int min, const MyString& contact, const MyString& text);
Notification make_app(int hou, int min, const MyString& app_name, const MyString& title, const MyString& text);

int count_type(const Notification* arr, int n, Notification::Type type);


//-------------------------------------


// новый

class NotificationQueue {
    Notification* arr;
    int kolvo;
    int vmestimost;

    int head;
    int tail;

    void rashirit();

public:
    class Iterator {
        Notification* arr;
        int index;
        int vmestimost;
        int head;

    public:
        Iterator(Notification* a = nullptr, int i = 0, int cap = 0, int h = 0);

        Notification& operator*();
        Notification* operator->();

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    NotificationQueue();
    NotificationQueue(const NotificationQueue& other);
    NotificationQueue& operator=(const NotificationQueue& other);
    virtual ~NotificationQueue();

    void push(const Notification& n);
    int size() const;
    virtual Notification pop();

    Iterator begin();
    Iterator end();
};

// ---------

class NotificationPriorityQueue {
    struct Node {
        Notification data;
        int nomer;
        Node* left;
        Node* right;

        Node(const Notification& n, int num);
    };

    Node* root;
    int kolvo;
    int nextn;

    bool aktualnee(const Notification& a, int nomer_a,
                   const Notification& b, int nomer_b) const;

    int types(const Notification& n) const;
    bool important_system(const Notification& n) const;

    Node* insert(Node* node, const Notification& n, int num);
    Node* removeright(Node* node, Notification& result);
    void clear(Node* node);
    Node* copy(Node* node);

public:
    NotificationPriorityQueue();
    NotificationPriorityQueue(const NotificationPriorityQueue& other);
    NotificationPriorityQueue& operator=(const NotificationPriorityQueue& other);
    ~NotificationPriorityQueue();

    void push(const Notification& n);
    int size() const;
    Notification pop();
};

//-----------------

// ДО ПОПЫТКИ В ДЕРЕВО

/*class NotificationPriorityQueue {
    Notification* arr;
    int kolvo;
    int vmestimost;

    void rashirit();

public:
    class Iterator {
        Notification* ptr;

    public:
        Iterator(Notification* p);

        Notification& operator*();
        Notification* operator->();

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    NotificationPriorityQueue();
    NotificationPriorityQueue(const NotificationPriorityQueue& other);
    NotificationPriorityQueue& operator=(const NotificationPriorityQueue& other);
    ~NotificationPriorityQueue();

    void push(const Notification& n);
    int size() const;
    virtual Notification pop();

    Iterator begin();
    Iterator end();
};

bool vazhno(const Notification& one);

int ransche_timing(const Notification& one, const Notification& another);

int sravnenie(const Notification& one, const Notification& another);
*/

/*


int right_hour(int h);
int right_minute(int m);

class Notification {
    int hour;
    int minute;
    Type type;

public:
    enum Type {
        SYSTEM,
        MESSAGE,
        APP
    };
    Notification(int h, int m, Type t);
    Notification(const Notification& other);
    Notification& operator=(const Notification& other);
    virtual ~Notification();

    int get_hour() const;
    int get_minute() const;
    Type get_type() const;

    virtual void print() const = 0;
};

class SystemNotification : public Notification {
public:
    enum serios {
        NORM,
        VAZHNO
    };

private:
    MyString prishlo_soob;
    serios ser;

public:
    SystemNotification(int h, int m, const MyString& p, serios s);
    SystemNotification(const SystemNotification& other);
    SystemNotification& operator=(const SystemNotification& other);

    void print() const;
};

class MessageNotification : public Notification {
private:
    MyString name;
    MyString prishlo_soob;

public:
    MessageNotification(int h, int m, const MyString& n, const MyString& p);
    MessageNotification(const MessageNotification& other);
    MessageNotification& operator=(const MessageNotification& other);

    void print() const;
};

class AppNotification : public Notification {
private:
    MyString name_app;
    MyString zagolovok;
    MyString prishlo_soob;

public:
    AppNotification(int h, int m, const MyString& n, const MyString& z, const MyString& p);
    AppNotification(const AppNotification& other);
    AppNotification& operator=(const AppNotification& other);

    void print() const;
};

int count_system(Notification** arr, int n);
int count_message(Notification** arr, int n);
int count_app(Notification** arr, int n);


*/