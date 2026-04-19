#include <iostream>
#include "string.hpp"

MyString::MyString() {
    // TODO: постарайтесь не выделять лишнюю память в конструкторах по
    //       умолчанию, да и в любых случаях, когда строка пустая.
    len = 0;
    string = nullptr;
    
}

MyString::MyString(const char * str) {
    // TODO: нет проверки на nullptr, хотя в других частях она есть; добавьте ее
    if (str == nullptr) {
        len = 0;
        string = nullptr;
        return;
    }
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

char* MyString::get_str() {
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

