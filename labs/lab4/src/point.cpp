#include <iostream>
#include <cassert>
#include <cstdio>
#include <fstream>

#include "point.hpp"

Point::Point(double x1, double y1) : x(x1), y(y1) {}

Point::Point(const Point& p) : x(p.get_x()), y(p.get_y()) {}

double Point::get_x() const{
    return x;
}

double Point::get_y() const{
    return y;
}



void Point::set_x(double x1) {
    x = x1;
    return;
}

void Point::set_y(double y1) {
    y = y1;
    return;
}


//----------------------


Circle::Circle() : centre(0, 0), radius(0) {}
Circle::Circle(double r) : centre(0, 0), radius(r) {}
Circle::Circle(double x1, double y1, double r) : centre(x1, y1), radius(r) {}

double Circle::get_radius() const{
    return radius;
}

double Circle::get_x() const{
    return centre.get_x();
}

double Circle::get_y() const{
    return centre.get_y();
}

void Circle::set_x(double x1) {
    centre.set_x(x1);
}

void Circle::set_y(double y1) {
    centre.set_y(y1);
} 

void Circle::set_centre(double x1, double y1) {
    centre.set_x(x1);
    centre.set_y(y1);

}

void Circle::set_radius(double r) {
    radius = r;
    return;
}

Circle::Circle(const Circle& other) : centre(other.get_x(), other.get_y()), radius(other.get_radius()) {}

Circle& Circle::operator=(const Circle& other) {
    this->set_centre(other.get_x(), other.get_y());
    this->set_radius(other.get_radius());
    return *this;
}

bool Circle::operator==(const Circle& other) const
{
    return radius == other.get_radius() &&
           this->get_x() == other.get_x() && this->get_y() == other.get_y();
}

double Circle::area() const {
    return 3.14 * radius * radius;
}


//-------------------------------------

Node::Node() : pPrev(nullptr), pNext(nullptr), m_Data() {}

Node::Node(Node* prev, Node* next, const Circle& pc) : pPrev(prev), pNext(next), m_Data(pc) //передать параметр pc конструктору встроенного объекта m_Data
{
    if (pPrev)
        pPrev->pNext = this;
    if (pNext)
        pNext->pPrev = this;
}
//Деструктор
Node::~Node()
{
    if (pPrev)
        pPrev->pNext = pNext;
    if (pNext)
        pNext->pPrev = pPrev;
}


// Листок -----------------------------------

void List::copy(const List& other)
{
    Node* cur = other.Head.pNext;

    while (cur != &other.Tail)
    {
        push_back(cur->m_Data);
        cur = cur->pNext;
    }
}

List::List() : Head(), Tail(), m_size(0) {
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}

List::List(const List& other) : Head(), Tail(), m_size(0)
{
    Head.pNext = &Tail;
    Tail.pPrev = &Head;

    copy(other);
}

List& List::operator=(const List& other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

List::~List()
{
    clear();
}

void List::clear()
{
    Node* cur = Head.pNext;
    while (cur != &Tail)
    {
        Node* temp = cur;
        cur = cur->pNext;
        delete temp;
    }

    Head.pNext = &Tail;
    Tail.pPrev = &Head;
    m_size = 0;
}

size_t List::size() const
{
    return m_size;
}

void List::push_back(const Circle& sth) {
    Node *sthnew = new Node(Tail.pPrev, &Tail, sth);
    m_size++;
}

void List::push_back(double x, double y, double r)
{
    push_back(Circle(x, y, r));
}

void List::push_front(const Circle& sth) {
    Node *sthnew = new Node(&Head, Head.pNext, sth);
    m_size++;
}

void List::push_front(double x, double y, double r)
{
    push_front(Circle(x, y, r));
}

bool List::remove_one(double r) {
    Node *cur = Head.pNext;
    while (cur != &Tail) {
        if (cur->m_Data.get_radius() == r) {
            delete cur;
            m_size--;
            return 1;
        }
        cur = cur->pNext;
    }
    return 0;
}

bool List::remove_one(const Point& p) {
    Node *cur = Head.pNext;
    while (cur != &Tail) {
        if (cur->m_Data.get_x() == p.get_x() && cur->m_Data.get_y() == p.get_y()) {
            delete cur;
            m_size--;
            return 1;
        }
        cur = cur->pNext;
    }
    return 0;
}

bool List::remove_one(const Circle& c) {
    Node *cur = Head.pNext;
    while (cur != &Tail) {
        if (cur->m_Data == c) {
            delete cur;
            m_size--;
            return 1;
        }
        cur = cur->pNext;
    }
    return 0;
}

size_t List::remove_all(const Circle& c) {
    size_t kolvo = 0;
    Node *cur = Head.pNext;
    while (cur != &Tail) {
        Node *next = cur->pNext;
        if (cur->m_Data == c) {
            delete cur;
            m_size--;
            kolvo++;
        }
        cur = next;
    }  
    return kolvo;  
}


Node* List::split(Node* first)
{
    Node* a = first;
    Node* b = first->pNext;

    while (b != nullptr && b->pNext != nullptr)
    {
        a = a->pNext;
        b = b->pNext->pNext;
    }

    Node* second = a->pNext;
    a->pNext = nullptr;

    if (second != nullptr)
        second->pPrev = nullptr;

    return second;
}

Node* List::sliyan(Node* a, Node* b)
{
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->m_Data.get_radius() <= b->m_Data.get_radius())
    {
        a->pNext = sliyan(a->pNext, b);
        if (a->pNext != nullptr) {
            a->pNext->pPrev = a;
        }
        a->pPrev = nullptr;
        return a;
    }
    else
    {
        b->pNext = sliyan(a, b->pNext);
        if (b->pNext != nullptr) {
            b->pNext->pPrev = b;
        }
        b->pPrev = nullptr;
        return b;
    }
}

Node* List::sortsl(Node* first)
{
    if (first == nullptr || first->pNext == nullptr) {
        return first;
    }
    Node* second = split(first);
    first = sortsl(first);
    second = sortsl(second);
    return sliyan(first, second);
}



void List::sort_rost()
{
    if (m_size <= 1) {
        return;
    }
    Node* first = Head.pNext;
    Node* last = Tail.pPrev;
    first->pPrev = nullptr;
    last->pNext = nullptr;
    Node* sorted = sortsl(first);

    Head.pNext = sorted;
    sorted->pPrev = &Head;
    Node* cur = sorted;
    while (cur->pNext != nullptr) {
        cur = cur->pNext;
    }
    cur->pNext = &Tail;
    Tail.pPrev = cur;
}

std::ostream& operator<<(std::ostream& os, const Circle& c)
{
    os << "Centre = (" 
       << c.get_x() << ", " 
       << c.get_y() << "), R = " 
       << c.get_radius();
    return os;
}

void List::each(void (*func)(const Circle&)) const
{
    const Node* cur = Head.pNext;

    while (cur != &Tail) {
        func(cur->m_Data);
        cur = cur->pNext;
    }
}

void List::print(std::ostream& os) const
{
    const Node* cur = Head.pNext;

    while (cur != &Tail) {
        os << cur->m_Data << '\n';
        cur = cur->pNext;
    }
}

void print(const Circle& c)
{
    std::cout << c << '\n';
}

std::ostream& operator<<(std::ostream& os, const List& list)
{
    list.print(os);
    return os;
}

void v_file(const List& list, const char* filename)
{
    std::ofstream fout(filename);

    if (!fout)
    {
        std::cout << "Чтото пошло не так!\n";
        return;
    }

    fout << list;

    fout.close();
}

/*std::istream& operator>>(std::istream& is, Circle& c)
{
    double x, y, r;
    char ch;
    char word[10];

    // Centre: (x, y), R = r
    std::cout << "все норм1\n";

    is >> word;           
    is >> ch;                 
    is >> x;                 
    is >> ch;                 
    is >> y;                  
    is >> word;      
    is >> word;            
    is >> ch;                 
    is >> r;                
    std::cout << "все норм2\n";

    std::cout << x << ' ' << y << ' ' << r << "\n";

    Circle sth(x, y, r);
    c = sth;
    std::cout << "все норм\n";
    

    return is;
} */

std::istream& operator>>(std::istream& is, Circle& c)
{
    double x, y, r;
    char eq1, lp, comma1, rp, comma2, eq2;
    char word1[20], word2[20];

    is >> word1 >> eq1 >> lp >> x >> comma1 >> y >> rp >> comma2 >> word2 >> eq2 >> r;

    if (!is)
        return is;

    c = Circle(x, y, r);
    return is;
}

bool List::chtenie_clear(const char* filename)
{
    std::ifstream fin(filename);

    if (!fin)
    {
        std::cerr << "Error opening file\n";
        return false;
    }

    clear();

    Circle temp;
    while (fin >> temp)
    {
        push_back(temp);
    }

    return true;
}

bool List::chtenie_without_clear(const char* filename)
{
    std::ifstream fin(filename);

    if (!fin)
    {
        std::cout << "Что то пошло не так\n";
        return 0;
    }

    Circle temp;
    while (fin >> temp)
    {
        push_back(temp);
    }

    return 1;
}
