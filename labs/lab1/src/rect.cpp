#include <iostream>
#include "rect.hpp"

/*
// конструктор по умолчанию
Rect::Rect() 
    {
        top = 0;
        bottom = 0;
        right = 0;
        left = 0;
        std::cout << "Вызван конструктор по умолчаниЮ для обьекта " << this << " \n" << std::endl;
    }

// конструктор с параметрами
Rect::Rect(int a, int b, int c, int d) 
    {
        if (a > b) {
            top = a;
            bottom =b;
        }
        else {
            top = b;
            bottom =a;
        }
        if (c > d) {
            right = c;
            left = d;
        }
        else {
            right = d;
            left = c;
        }
        
        std::cout << "Вызван конструктор с параметрами для обьекта " << this << "\n" << std::endl;
    }


// конструктор копирования
Rect::Rect(const Rect &A) 
    {
        top = A.top;
        bottom = A.bottom;
        right = A.right;
        left = A.left;
        std::cout << "Вызван Конструктор копирования для обьекта " << this << " \n" << std::endl;
    }

// деконструктор 
Rect::~Rect() {std::cout << "Вызван Деструктор для обьекта " << this << " \n" << std::endl;}

// геттеры:
int Rect::get_top() {
    return top;
}

int Rect::get_bottom() {
    return bottom;
}

int Rect::get_left() {
    return left;
}

int Rect::get_right() {
    return right;
}

// сеттеры:
void Rect::set_all(int top, int bottom, int right, int left) {
    if (top > bottom) {
        this->top = top;
        this->bottom = bottom;
    }
    else {
        this->top = bottom;
        this->bottom = top;
    }
    if (right > left) {
        this->right = right;
        this->left = left;
    }
    else {
        this->right = left;
        this->left = right;
    }
}


void Rect::inflate(int amount) {
    this->set_all(this->top + amount, this->bottom - amount, this->right + amount, this->left - amount);
}
    

void Rect::inflate(int dw, int dh) {
    this->set_all(this->top + dh, this->bottom - dh, this->right + dw, this->left - dw);
}
    

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    this->set_all(this->top + d_top, this->bottom - d_bottom, this->right + d_right, this->left - d_left);
}

void Rect::move(int x, int y) {
    this->top += y;
    this->bottom += y;
    this->right += x;
    this->left += x;
}

Rect bounding_rect(Rect r1, Rect r2) {
    Rect res;
    int top = (r1.get_top() > r2.get_top()) ? r1.get_top() : r2.get_top();
    int bottom = (r1.get_bottom() < r2.get_bottom()) ? r1.get_bottom() : r2.get_bottom();
    int right = (r1.get_right() > r2.get_right()) ? r1.get_right() : r2.get_right();
    int left = (r1.get_top() < r2.get_top()) ? r1.get_left() : r2.get_left();
    res.set_all(top, bottom, right, left);
    return res;
}

void print_rect(Rect &r) {
    std::cout << "Прямоугольник с координатами: \n" << "Верхняя: " << r.get_top()  
        << "\nНижняя: " << r.get_bottom() << "\nПравая: " 
        << r.get_right() << "\nЛевая: " << r.get_left() << '\n' << std::endl;  
}


int Rect::get_width() {
    return (this->right -this->left);
}

int Rect::get_height() {
    return (this->top -this->bottom);
}

int Rect::get_square() {
    return (get_height() * get_width());
}

void Rect::set_width(int w) {
    if (w <= 0) {
        this->right = this->left;
        return;
    }
    this->right = this->left + w;
}
    
void Rect::set_height(int h) {
    if (h <= 0) {
        this->top = this->bottom;
        return;
    }
    this->top = this->bottom + h;
}

*/

// конструктор по умолчанию
Rect::Rect() 
    {
        pointx = 0;
        pointy = 0;
        h = 0;
        w = 0;
        std::cout << "Вызван конструктор по умолчаниЮ для обьекта " << this << " \n" << std::endl;
    }

// конструктор с параметрами
Rect::Rect(int a, int b, int c, int d) 
    {
        if (a > b) {
            pointy = b;
            h = a - b;
        }
        else {
            pointy = a;
            h = b -a;
        }
        if (c > d) {
            pointx = d;
            w = c - d;
        }
        else {
            pointx = c;
            w = d - c;
        }
        
        
        std::cout << "Вызван конструктор с параметрами для обьекта " << this << "\n" << std::endl;
    }


// конструктор копирования
Rect::Rect(const Rect &A) 
    {
        pointx = A.pointx;
        pointy = A.pointy;
        h = A.h;
        w = A.w;
        std::cout << "Вызван Конструктор копирования для обьекта " << this << " \n" << std::endl;
    }

// деконструктор 
Rect::~Rect() {std::cout << "Вызван Деструктор для обьекта " << this << " \n" << std::endl;}

// геттеры:
int Rect::get_top() {
    return (pointy + h);
}

int Rect::get_bottom() {
    return pointy;
}

int Rect::get_left() {
    return pointx;
}

int Rect::get_right() {
    return (pointx + w);
}

// сеттеры:
void Rect::set_all(int top, int bottom, int right, int left) {
    if (top > bottom) {
        pointy = bottom;
        h = top - bottom;
    }
    else {
        pointy = top;
        h = bottom - top;
    }
    if (right > left) {
        pointx = left;
        w = right - left;
    }
    else {
        pointx = right;
        w = left - right;
    }
}


void Rect::inflate(int amount) {
    this->set_all(this->get_top() + amount, this->get_bottom() - amount, this->get_right() + amount, this->get_left() - amount);
}
    

void Rect::inflate(int dw, int dh) {
    this->set_all(this->get_top() + dh, this->get_bottom() - dh, this->get_right() + dw, this->get_left() - dw);
}
    

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    this->set_all(this->get_top() + d_top, this->get_bottom() - d_bottom, this->get_right() + d_right, this->get_left() - d_left);
}

void Rect::move(int x, int y) {
    this->set_all(this->get_top() + y, this->get_bottom() + y, this->get_right() + x, this->get_left() + x);
}

Rect bounding_rect(Rect r1, Rect r2) {
    Rect res;
    int top = (r1.get_top() > r2.get_top()) ? r1.get_top() : r2.get_top();
    int bottom = (r1.get_bottom() < r2.get_bottom()) ? r1.get_bottom() : r2.get_bottom();
    int right = (r1.get_right() > r2.get_right()) ? r1.get_right() : r2.get_right();
    int left = (r1.get_top() < r2.get_top()) ? r1.get_left() : r2.get_left();
    res.set_all(top, bottom, right, left);
    return res;
}

void print_rect(Rect &r) {
    std::cout << "Прямоугольник с координатами: \n" << "Верхняя: " << r.get_top()  
        << "\nНижняя: " << r.get_bottom() << "\nПравая: " 
        << r.get_right() << "\nЛевая: " << r.get_left() << '\n' << std::endl;  
}


int Rect::get_width() {
    return w;
}

int Rect::get_height() {
    return h;
}

int Rect::get_square() {
    return (h * w);
}

void Rect::set_width(int w) {
    if (w <= 0) {
        this->w = 0;
        return;
    }
    this->w = w;
}
    
void Rect::set_height(int h) {
    if (h <= 0) {
        this->h = 0;
        return;
    }
    this->h = h;
}