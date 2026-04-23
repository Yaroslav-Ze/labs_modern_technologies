#include <iostream>
#include "string.hpp"

MyString::MyString() {
    len = 0;
    string = new char[1];
    string[0] = '\0';
} 

MyString::MyString(const char * str) {
    int i = 0;
    len = 0;
    if (str) {
        while (str[i] != '\0') {
            i++;
        }
        len = i;
    }
    
    string = new char[len + 1];
    for (int z = 0; z < len; z++) {
        string[z] = str[z];
    }
    string[len] = '\0';
}

MyString::MyString(const MyString& other) {
    len = other.len;
    string = new char[len + 1];
    for (int i = 0; i < len; i++) {
        string[i] = other.string[i];
    }
    string[len] = '\0';
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) { 
        
        delete[] string;
        
        len = other.len;
        string = new char[len + 1];
        for (int i = 0; i < len; i++) {
            string[i] = other.string[i];
        }
        string[len] = '\0';
    }
    return *this;
}

MyString& MyString::operator=(const char* other) {
    if (other != nullptr) { 
        int i = 0;
        
        while (other[i] != '\0') {
            i++;
        }
        len = i;
        
        
        
        char * newstr = new char[len + 1];

        for (int z = 0; z < len; z++) {
            newstr[z] = other[z];
        }
        newstr[len] = '\0'; 

        delete[] string;
        string = newstr;

    }
    return *this;
}

MyString::~MyString() {
    delete[] string;
    
    string = nullptr;
    len = 0;
}

char MyString::get(int i) {
    if ((i >= 0) && (i < len)) {
        return string[i];
    }
    //throw std::out_of_range("Индекс выходит за границы строки");
    return '\0';
}

int MyString::get_len() {
    
    return len;
}

char* MyString::get_str() const {
    return string;
}

void MyString::set(int i, char c) {
    if (i >= 0 && i < len) {
        string[i] = c;  
    }
}

void MyString::set_new_string(const char *str) {
    if (str == nullptr) {
        delete[] string;
        string = new char[1];
        string[0] = '\0';
        len = 0;
        return;
    }

    if (str == string) {
        return;
    }

    int i = 0;
    
    while (str[i] != '\0') {
        i++;
    }
        
    len = i;

    delete[] string;
    
    string = new char[i + 1];
    for (int z = 0; z < len; z++) {
        string[z] = str[z];
    }
    string[len] = '\0';
}

void MyString::print() {
    if (len == 0) return;
    std::cout << string << std::endl;
}

void MyString::read_line() {
    int newlen = 0;
    int mesto = 30;
    char bykva;
    char *newst = new char[mesto];
    while ((std::cin.get(bykva)) && (bykva != '\n')) {
        if (newlen + 1 >= mesto) {
            //char copy[mesto];
            char *copy = new char[mesto];
            for (int i = 0; i < mesto; i++) {
                copy[i] = newst[i];

            }
            delete[] newst;
            mesto = mesto + 30;
            newst = new char[mesto];
            for (int i = 0; i < mesto - 30; i++) {
                newst[i] = copy[i];
            }
            delete[] copy;

        }
        newst[newlen] = bykva;
        newlen++;
    }
    delete[] string; // поле класса
    len = newlen; // поле класса
    string = new char[len + 1];
    for (int i = 0; i < len; i++) {
        string[i] = newst[i];
    }
    string[len] = '\0';
    delete[] newst;
    


}

MyString& MyString::operator+=(const MyString& other) {
    int newLen = len + other.len;
    char* newStr = new char[newLen + 1];

    for (int i = 0; i < len; i++) {
        newStr[i] = string[i];
    }

    for (int i = 0; i < other.len; i++) {
        newStr[len + i] = other.string[i];
    }

    newStr[newLen] = '\0';

    delete[] string;
    string = newStr;
    len = newLen;

    return *this;
}

MyString& MyString::operator+=(const char* other) {
    if (other == nullptr) {
        return *this;
    }
    MyString sth(other);  
    return *this += sth;   
}

MyString MyString::operator+(const MyString& other) const {
    MyString out = *this;
    out += other;
    return out;
}

MyString MyString::operator+(const char* other) const {
    MyString out = *this;
    out += other;
    return out;
}

MyString operator+(const char* left, const MyString& right) {
    MyString out(left);
    out += right;
    return out;
}

MyString::MyString(MyString&& other) {
    string = other.string;
    len = other.len;

    other.string = nullptr;
    other.len = 0;
}

MyString& MyString::operator=(MyString&& other) {
    if (this != &other) {
        delete[] string;

        string = other.string;
        len = other.len;

        other.string = nullptr;
        other.len = 0;
    }
    return *this;
}

int MyString::compare(const MyString& other) const {
    int min = (len < other.len) ? len : other.len;

    for (int i = 0; i < min; i++) {
        if (string[i] < other.string[i]) {
            return -1;
        }
        if (string[i] > other.string[i]) {
            return 1;
        }
    }

    if (len < other.len) {
        return -1;
    }
    if (len > other.len) {
        return 1;
    }
    return 0;
}

bool MyString::operator==(const MyString& other) const {
    return compare(other) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return compare(other) != 0;
}

bool MyString::operator<(const MyString& other) const {
    return compare(other) < 0;
}

bool MyString::operator<=(const MyString& other) const {
    return compare(other) <= 0;
}

bool MyString::operator==(const char* other) const {
    if (other == nullptr) {
        return 0;
    }
    return *this == MyString(other);
}

bool MyString::operator!=(const char* other) const {
    if (other == nullptr) {
        return 1;
    }
    return *this != MyString(other);
}

bool MyString::operator<(const char* other) const {
    if (other == nullptr) {
        return 0;
    }
    return *this < MyString(other);
}

bool MyString::operator<=(const char* other) const {
    if (other == nullptr) {
        return 0;
    }
    return *this <= MyString(other);
}

bool operator==(const char* left, const MyString& right) {
    if (left == nullptr) {
        return 0;
    }
    return MyString(left) == right;
}

bool operator!=(const char* left, const MyString& right) {
    if (left == nullptr) {
        return 1;
    }
    return MyString(left) != right;
}

bool operator<(const char* left, const MyString& right) {
    if (left == nullptr) {
        return 1;  
    }
    return MyString(left) < right;
}

bool operator<=(const char* left, const MyString& right) {
    if (left == nullptr) {
        return 1;
    }
    return MyString(left) <= right;
}

char& MyString::operator[](int i) {
    if (i < 0 || i >= len) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return string[i];
}

const char& MyString::operator[](int i) const {
    if (i < 0 || i >= len) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return string[i];
}

std::ostream& operator<<(std::ostream& os, const MyString& s) { // ссылка на поток вывода
    os << s.get_str();
    return os;
}

std::istream& operator>>(std::istream& is, MyString& s) { // ссылка на поток ввода
    s.read_line();
    return is;
}

MyString addTxtExtension(const MyString &path) { 
    return path + ".txt"; 
}