#include <cstdio>
#include <iostream>

// Точка ---------------------------------------------

class Point {
    double x;
    double y;

public:
    Point(double x1 = 0, double y = 0);
    Point(const Point& p);
    
    double get_x() const;
    double get_y() const;

    void set_x(double x1);
    void set_y(double y1);

    
};

// Круг ---------------------------------------

class Circle{
    Point centre;
    double radius;

public:
    Circle();
    Circle(double r);
    Circle(double x1, double y1, double r);
    Circle(const Circle& other);

    Circle& operator=(const Circle& other);

    double get_radius() const;
    double get_x() const;
    double get_y() const;

    void set_x(double x1);
    void set_y(double y1);
    void set_centre(double x1, double y1);


    void set_radius(double r);

    bool operator==(const Circle& other) const;

    double area() const;

    
};

// Нода ---------------------------

class Node  
{
	Node* pPrev;		//указатель на предыдущий элемент
	Node* pNext;		//указатель на следующий элемент
	Circle m_Data;		

	Node();//скорее всего понадобится для создания вспомогательных оберток – «стражей» (Head, Tail)
	Node(Node* prev, Node* next, const Circle& pc);	//конструктор, посредством которого создаваемый Node «подключается» в список.
	~Node();//деструктор должен «исключать» уничтожаемый Node из списка
    friend class List;
};

//-----------------------------------

class List  
{
//встроенное объявление класса Node

//данные
	Node Head;	// фиктивный элемент, который является признаком начала списка
	Node Tail;	// фиктивный элемент, который является признаком конца списка
	size_t m_size;	//количество элементов
    void copy(const List& other);
public:
	List(); //сформировать Head, Tail и m_size }
    List(const List& other);
    List& operator=(const List& other);

    ~List();


    void clear();
    size_t size() const;

    void push_back(const Circle& sth);
    void push_back(double x, double y, double r);
    void push_front(const Circle& sth);
    void push_front(double x, double y, double r);

    bool remove_one(double r);
    bool remove_one(const Point& p);
    bool remove_one(const Circle& c);

    size_t remove_all(const Circle& c);

    Node* split(Node* first);
    Node* sliyan(Node* a, Node* b);
    Node* sortsl(Node* first);
    void sort_rost();

    void print(std::ostream& os) const;

    bool chtenie_clear(const char* filename);
    bool chtenie_without_clear(const char* filename);

    void each(void (*func)(const Circle&)) const;
	
};

std::ostream& operator<<(std::ostream& os, const Circle& c);
std::ostream& operator<<(std::ostream& os, const List& list);

void v_file(const List& list, const char* filename);

void print(const Circle& c);

std::istream& operator>>(std::istream& is, Circle& c);

