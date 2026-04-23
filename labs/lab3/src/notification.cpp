#include <iostream>
#include "notification.hpp"


Notification::syst_n::syst_n(const MyString& p, serios s) : prishlo_soob(p), ser(s) {}

Notification::message_n::message_n(const MyString& n, const MyString& p) : name(n), prishlo_soob(p) {}

Notification::app_n::app_n(const MyString& n, const MyString& z, const MyString& p) : name_app(n), zagolovok(z), prishlo_soob(p) {}

Notification::Notification() : hour(0), minute(0),  type(SYSTEM) {
    data.system = nullptr;
}

void Notification::clear() {
    if (type == SYSTEM) {
        delete data.system;
        data.system = nullptr;
    }
    else if (type == MESSAGE) {
        delete data.message;
        data.message = nullptr;
    }
    else if (type == APP) {
        delete data.app;
        data.app = nullptr;
    }
}

Notification::~Notification() {
    clear();
}

Notification::Notification(const Notification& other)
    : hour(other.hour), minute(other.minute), type(other.type)
{
    if (type == SYSTEM) {
        if (other.data.system != nullptr) {
            data.system = new syst_n(*other.data.system);
        } else {
            data.system = nullptr;
        }
    }
    else if (type == MESSAGE) {
        if (other.data.message != nullptr) {
            data.message = new message_n(*other.data.message);
        } else {
            data.message = nullptr;
        }
    }
    else if (type == APP) {
        if (other.data.app != nullptr) {
            data.app = new app_n(*other.data.app);
        } else {
            data.app = nullptr;
        }
    }
}

Notification& Notification::operator=(const Notification& other) {
    if (this != &other) {
        clear();

        hour = other.hour;
        minute = other.minute;
        type = other.type;

        if (type == SYSTEM) {
            if (other.data.system != nullptr) {
                data.system = new syst_n(*other.data.system);
            } else {
                data.system = nullptr;
            }
        }
        else if (type == MESSAGE) {
            if (other.data.message != nullptr) {
                data.message = new message_n(*other.data.message);
            } else {
                data.message = nullptr;
            }
        }
        else if (type == APP) {
            if (other.data.app != nullptr) {
                data.app = new app_n(*other.data.app);
            } else {
                data.app = nullptr;
            }
        }
    }

    return *this;
}

int right_hour(int h) {
    if (h >= 0 && h <= 23) {
        return h;
    }
    return 0;
}

int right_minute(int m) {
    if (m >= 0 && m <= 59) {
        return m;
    }
    return 0;
}

Notification make_system(int hou, int min, const MyString& msg, Notification::syst_n::serios lvl) {
    Notification sth;
    sth.hour = right_hour(hou);
    sth.minute = right_minute(min);
    sth.type = Notification::SYSTEM;
    sth.data.system = new Notification::syst_n(msg, lvl);

    return sth;
}

Notification make_message(int hou, int min, const MyString& contact, const MyString& text) {
    Notification sth;
    sth.hour = right_hour(hou);
    sth.minute = right_minute(min);
    sth.type = Notification::MESSAGE;
    sth.data.message = new Notification::message_n(contact, text);

    return sth;
}

Notification make_app(int hou, int min, const MyString& app_name, const MyString& title, const MyString& text) {
    Notification sth;
    sth.hour = right_hour(hou);
    sth.minute = right_minute(min);
    sth.type = Notification::APP;
    sth.data.app = new Notification::app_n(app_name, title, text);

    return sth;
}

void Notification::print() const {
    std::cout << "\nПолучено в " << hour << ":" << (minute >= 10 ? "" : "0") << minute << "\n";

    if (type == SYSTEM) {
        if (data.system != nullptr) {
            std::cout << "Системное уведомление: " << data.system->prishlo_soob
                      << "\nСрочность: " << (data.system->ser == Notification::syst_n::NORM ? "Обычно" : "Срочно");
        }
    }
    else if (type == MESSAGE) {
        if (data.message != nullptr) {
            std::cout << "Сообщение от " << data.message->name
                      << ":\n" << data.message->prishlo_soob;
        }
    }
    else if (type == APP) {
        if (data.app != nullptr) {
            std::cout << "Уведомление от приложения: " << data.app->name_app
                      << "\nЗaголовок: " << data.app->zagolovok
                      << "\n" << data.app->prishlo_soob;
        }
    }

    std::cout << '\n';
}


int count_type(const Notification* arr, int n, Notification::Type type) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].type == type) {
            count++;
        }
    }

    return count;
}

//-----------------------------------

//Буфер закольцован. Теперь не надо при Поп сдвигать элементы, запоминаем индексы Хэд и Тэйл. И премещаемся
// относительно их. Все моменты в духе 'чтото % vmestimost' обеспечивают ход по кругу массива.  

NotificationQueue::Iterator::Iterator(Notification* a, int i, int vmest, int h)
    : arr(a), index(i), vmestimost(vmest), head(h) {}

Notification& NotificationQueue::Iterator::operator*() {
    return arr[(head + index) % vmestimost];
}

Notification* NotificationQueue::Iterator::operator->() {
    return &arr[(head + index) % vmestimost];
}

NotificationQueue::Iterator& NotificationQueue::Iterator::operator++() {
    index++;
    return *this;
}

NotificationQueue::Iterator NotificationQueue::Iterator::operator++(int) {
    Iterator temp = *this;
    index++;
    return temp;
}

bool NotificationQueue::Iterator::operator==(const Iterator& other) const {
    return arr == other.arr &&
           index == other.index &&
           vmestimost == other.vmestimost &&
           head == other.head;
}

bool NotificationQueue::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

//-----------------------------------

NotificationQueue::NotificationQueue() {
    kolvo = 0;
    vmestimost = 2;
    head = 0;
    tail = 0;
    arr = new Notification[vmestimost];
}

NotificationQueue::NotificationQueue(const NotificationQueue& other) {
    kolvo = other.kolvo;
    vmestimost = other.vmestimost;
    head = 0;
    tail = kolvo;

    arr = new Notification[vmestimost];

    for (int i = 0; i < kolvo; i++) {
        arr[i] = other.arr[(other.head + i) % other.vmestimost];
    }
}

NotificationQueue& NotificationQueue::operator=(const NotificationQueue& other) {
    if (this != &other) {
        delete[] arr;

        kolvo = other.kolvo;
        vmestimost = other.vmestimost;
        head = 0;
        tail = kolvo;

        arr = new Notification[vmestimost];

        for (int i = 0; i < kolvo; i++) {
            arr[i] = other.arr[(other.head + i) % other.vmestimost];
        }
    }
    return *this;
}

NotificationQueue::~NotificationQueue() {
    delete[] arr;
}

void NotificationQueue::rashirit() {
    int bylo = vmestimost;
    vmestimost *= 2;

    Notification* noviy = new Notification[vmestimost];

    for (int i = 0; i < kolvo; i++) {
        noviy[i] = arr[(head + i) % bylo];
    }

    delete[] arr;
    arr = noviy;

    head = 0;
    tail = kolvo;
}

void NotificationQueue::push(const Notification& n) {
    if (kolvo >= vmestimost) {
        rashirit();
    }

    arr[tail] = n;
    tail = (tail + 1) % vmestimost;
    kolvo++;
}

int NotificationQueue::size() const {
    return kolvo;
}

Notification NotificationQueue::pop() {
    if (kolvo == 0) {
        throw "пусто";
    }

    Notification first = arr[head];

    head = (head + 1) % vmestimost;
    kolvo--;

    if (kolvo == 0) {
        head = 0;
        tail = 0;
    }

    return first;
}

NotificationQueue::Iterator NotificationQueue::begin() {
    return Iterator(arr, 0, vmestimost, head);
}

NotificationQueue::Iterator NotificationQueue::end() {
    return Iterator(arr, kolvo, vmestimost, head);
}


//-------------------

NotificationPriorityQueue::Node::Node(const Notification& n, int num)
    : data(n), nomer(num), left(nullptr), right(nullptr) {}

NotificationPriorityQueue::NotificationPriorityQueue() {
    root = nullptr;
    kolvo = 0;
    nextn = 0;
}

bool NotificationPriorityQueue::important_system(const Notification& n) const {
    return n.type == Notification::SYSTEM &&
           n.data.system != nullptr &&
           n.data.system->ser == Notification::syst_n::VAZHNO;
}

int NotificationPriorityQueue::types(const Notification& n) const {
    if (n.type == Notification::MESSAGE) {
        return 3;
    }
    if (n.type == Notification::SYSTEM) {
        return 2;
    }
    return 1; 
}

bool NotificationPriorityQueue::aktualnee(const Notification& a, int nomer_a,
                                          const Notification& b, int nomer_b) const {
    bool a_imp = important_system(a);
    bool b_imp = important_system(b);

    if (a_imp && !b_imp) {
        return true;
    }
    if (!a_imp && b_imp) {
        return false;
    }

    if (a.hour < b.hour) {
        return true;
    }
    if (a.hour > b.hour) {
        return false;
    }

    if (a.minute < b.minute) {
        return true;
    }
    if (a.minute > b.minute) {
        return false;
    }

    if (types(a) > types(b)) {
        return true;
    }
    if (types(a) < types(b)) {
        return false;
    }

    return nomer_a < nomer_b;
}

NotificationPriorityQueue::Node* NotificationPriorityQueue::insert(Node* node, const Notification& n, int num) {
    if (node == nullptr) {
        return new Node(n, num);
    }

    if (aktualnee(n, num, node->data, node->nomer)) {
        node->right = insert(node->right, n, num);
    } else {
        node->left = insert(node->left, n, num);
    }

    return node;
}

NotificationPriorityQueue::Node* NotificationPriorityQueue::removeright(Node* node, Notification& result) {
    if (node->right == nullptr) {
        result = node->data;
        Node* left_sub = node->left;
        delete node;
        return left_sub;
    }

    node->right = removeright(node->right, result);
    return node;
}

void NotificationPriorityQueue::clear(Node* node) {
    if (node == nullptr) {
        return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
}

NotificationPriorityQueue::Node* NotificationPriorityQueue::copy(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* new_node = new Node(node->data, node->nomer);
    new_node->left = copy(node->left);
    new_node->right = copy(node->right);
    return new_node;
}

NotificationPriorityQueue::NotificationPriorityQueue(const NotificationPriorityQueue& other) {
    root = copy(other.root);
    kolvo = other.kolvo;
    nextn = other.nextn;
}

NotificationPriorityQueue& NotificationPriorityQueue::operator=(const NotificationPriorityQueue& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
        kolvo = other.kolvo;
        nextn = other.nextn;
    }
    return *this;
}

NotificationPriorityQueue::~NotificationPriorityQueue() {
    clear(root);
}

void NotificationPriorityQueue::push(const Notification& n) {
    root = insert(root, n, nextn);
    nextn++;
    kolvo++;
}

int NotificationPriorityQueue::size() const {
    return kolvo;
}

Notification NotificationPriorityQueue::pop() {
    if (kolvo == 0) {
        throw "пусто";
    }

    Notification result;
    root = removeright(root, result);
    kolvo--;
    return result;
}

//===========================

//ДО ПОПЫТКИ В ДЕРЕВО

/*

NotificationPriorityQueue::Iterator::Iterator(Notification* p) : ptr(p) {}

Notification& NotificationPriorityQueue::Iterator::operator*() {
    return *ptr;
}

Notification* NotificationPriorityQueue::Iterator::operator->() {
    return ptr;
}

NotificationPriorityQueue::Iterator& NotificationPriorityQueue::Iterator::operator++() {
    ptr++;
    return *this;
}

NotificationPriorityQueue::Iterator NotificationPriorityQueue::Iterator::operator++(int) {
    Iterator temp = *this;
    ptr++;
    return temp;
}

bool NotificationPriorityQueue::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

bool NotificationPriorityQueue::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}


NotificationPriorityQueue::NotificationPriorityQueue() {
    kolvo = 0;
    vmestimost = 2;
    arr = new Notification[vmestimost];
}

NotificationPriorityQueue::NotificationPriorityQueue(const NotificationPriorityQueue& other) {
    kolvo = other.kolvo;
    vmestimost = other.vmestimost;
    arr = new Notification[vmestimost];

    for (int i = 0; i < kolvo; i++) {
        arr[i] = other.arr[i];
    }
}

NotificationPriorityQueue& NotificationPriorityQueue::operator=(const NotificationPriorityQueue& other) {
    if (this != &other) {
        delete[] arr;

        kolvo = other.kolvo;
        vmestimost = other.vmestimost;
        arr = new Notification[vmestimost];

        for (int i = 0; i < kolvo; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

NotificationPriorityQueue::~NotificationPriorityQueue() {
    delete[] arr;
}

void NotificationPriorityQueue::rashirit() {
    vmestimost *= 2;

    Notification* noviy = new Notification[vmestimost];

    for (int i = 0; i < kolvo; i++) {
        noviy[i] = arr[i];
    }
    delete[] arr;
    arr = noviy;
}

void NotificationPriorityQueue::push(const Notification& n) {
    if (kolvo >= vmestimost) {
        rashirit();
    }
    arr[kolvo] = n;
    kolvo++;
}

int NotificationPriorityQueue::size() const {
    return kolvo;
}

bool vazhno(const Notification& one) {
    return one.type == Notification::SYSTEM &&
           one.data.system != nullptr &&
           one.data.system->ser == Notification::syst_n::VAZHNO;
}

int ransche_timing(const Notification& one, const Notification& another) {
    if (one.hour < another.hour) {
        return 1;
    }
    else if (one.hour > another.hour) {
        return 2;
    } 
    else {
        if (one.minute < another.minute) {
            return 1;
        }
        else if (one.minute > another.minute) {
            return 2;
        }
        else if (one.minute == another.minute) {
            return 0;
        }
    } 
    return -1;
}

int sravnenie(const Notification& one, const Notification& another) {
    if (one.type == another.type) {
        return 0;
    }
    else if (one.type == Notification::SYSTEM) {
        if (another.type == Notification::MESSAGE) {
            return 2;
        }
        else {
            return 1;
        }
    }
    else if (one.type == Notification::MESSAGE) {
        return 1;
    }
    else if (one.type == Notification::APP) {
        return 2;
    }
    return -1;
}


Notification NotificationPriorityQueue::pop() {
    if (kolvo == 0) {
        throw "пусто";
    }
    int index = 0;

    Notification etalon = arr[0];

    for (int i = 1; i < kolvo; i++) {
        if (vazhno(arr[i])) {
            if (vazhno(etalon)) {
                if (ransche_timing(etalon, arr[i]) == 2) {
                    etalon = arr[i];
                    index = i;
                }
            }
            else {
                index = i;
                etalon = arr[i];
            }
        }
        else {
            if (vazhno(etalon)) {
                continue;
            }
            else if (ransche_timing(etalon, arr[i]) == 2) {
                etalon = arr[i];
                index = i;
            }
            else if (ransche_timing(etalon, arr[i]) == 0) {
                if (sravnenie(etalon, arr[i]) == 2) {
                    index = i;
                    etalon = arr[i];
                }
            }
        }
    }

    Notification n = arr[index];

    for (int i = index + 1; i < kolvo; i++) {
        arr[i - 1] = arr[i];
    }
    kolvo--;
    return n;
}

NotificationPriorityQueue::Iterator NotificationPriorityQueue::begin() {
    return Iterator(arr);
}

NotificationPriorityQueue::Iterator NotificationPriorityQueue::end() {
    return Iterator(arr + kolvo);
}

*/

//=============================

/*


int right_hour(int h) {
    if (h >= 0 && h <= 23) {
        return h;
    }
    return 0;
}

int right_minute(int m) {
    if (m >= 0 && m <= 59) {
        return m;
    }
    return 0;
}



Notification::Notification(int h, int m, Type t)
    : hour(right_hour(h)), minute(right_minute(m)), type(t) {
}

Notification::Notification(const Notification& other)
    : hour(other.hour), minute(other.minute), type(other.type) {
}

Notification& Notification::operator=(const Notification& other) {
    if (this != &other) {
        hour = other.hour;
        minute = other.minute;
        type = other.type;
    }
    return *this;
}

Notification::~Notification() {
}

int Notification::get_hour() const {
    return hour;
}

int Notification::get_minute() const {
    return minute;
}

Notification::Type Notification::get_type() const {
    return type;
}



SystemNotification::SystemNotification(int h, int m, const MyString& p, serios s)
    : Notification(h, m, Notification::SYSTEM), prishlo_soob(p), ser(s) {
}

SystemNotification::SystemNotification(const SystemNotification& other)
    : Notification(other), prishlo_soob(other.prishlo_soob), ser(other.ser) {
}

SystemNotification& SystemNotification::operator=(const SystemNotification& other) {
    if (this != &other) {
        Notification::operator=(other);
        prishlo_soob = other.prishlo_soob;
        ser = other.ser;
    }
    return *this;
}

void SystemNotification::print() const {
    std::cout << "\nПолучено в "
              << get_hour() << ":"
              << (get_minute() >= 10 ? "" : "0")
              << get_minute() << "\n";

    std::cout << "Системное уведомление: " << prishlo_soob
              << "\nСрочность: " << (ser == NORM ? "Обычно" : "Срочно")
              << "\n";
}



MessageNotification::MessageNotification(int h, int m, const MyString& n, const MyString& p)
    : Notification(h, m, Notification::MESSAGE), name(n), prishlo_soob(p) {
}

MessageNotification::MessageNotification(const MessageNotification& other)
    : Notification(other), name(other.name), prishlo_soob(other.prishlo_soob) {
}

MessageNotification& MessageNotification::operator=(const MessageNotification& other) {
    if (this != &other) {
        Notification::operator=(other);
        name = other.name;
        prishlo_soob = other.prishlo_soob;
    }
    return *this;
}

void MessageNotification::print() const {
    std::cout << "\nПолучено в "
              << get_hour() << ":"
              << (get_minute() >= 10 ? "" : "0")
              << get_minute() << "\n";

    std::cout << "Сообщение от " << name
              << ":\n" << prishlo_soob << "\n";
}



AppNotification::AppNotification(int h, int m, const MyString& n, const MyString& z, const MyString& p)
    : Notification(h, m, Notification::APP), name_app(n), zagolovok(z), prishlo_soob(p) {
}

AppNotification::AppNotification(const AppNotification& other)
    : Notification(other), name_app(other.name_app), zagolovok(other.zagolovok), prishlo_soob(other.prishlo_soob) {
}

AppNotification& AppNotification::operator=(const AppNotification& other) {
    if (this != &other) {
        Notification::operator=(other);
        name_app = other.name_app;
        zagolovok = other.zagolovok;
        prishlo_soob = other.prishlo_soob;
    }
    return *this;
}

void AppNotification::print() const {
    std::cout << "\nПолучено в "
              << get_hour() << ":"
              << (get_minute() >= 10 ? "" : "0")
              << get_minute() << "\n";

    std::cout << "Уведомление от приложения: " << name_app
              << "\nЗаголовок: " << zagolovok
              << "\n" << prishlo_soob << "\n";
}



int count_system(Notification** arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != nullptr && arr[i]->get_type() == Notification::SYSTEM) {
            count++;
        }
    }
    return count;
}

int count_message(Notification** arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != nullptr && arr[i]->get_type() == Notification::MESSAGE) {
            count++;
        }
    }
    return count;
}

int count_app(Notification** arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != nullptr && arr[i]->get_type() == Notification::APP) {
            count++;
        }
    }
    return count;
}
*/