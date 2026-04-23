#pragma once
#include <iostream>
#include <utility>


class MyString {
    char *string;
    int len;

public:
    MyString();
    MyString(const char * str);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    MyString& operator=(const char* other);
    ~MyString(); 

    char get(int i);
    int get_len();
    char* get_str() const;
    void set(int i, char c);
    void set_new_string(const char *str);
    void print();
    void read_line();

    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* other);

    MyString operator+(const MyString& other) const;
    MyString operator+(const char* other) const;

    MyString(MyString&& other);
    MyString& operator=(MyString&& other);

    int compare(const MyString& other) const;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;

    bool operator==(const char* other) const;
    bool operator!=(const char* other) const;
    bool operator<(const char* other) const;
    bool operator<=(const char* other) const;

    char& operator[](int i);
    const char& operator[](int i) const;

};

MyString operator+(const char* left, const MyString& right);



bool operator==(const char* left, const MyString& right);
bool operator!=(const char* left, const MyString& right);
bool operator<(const char* left, const MyString& right);
bool operator<=(const char* left, const MyString& right);


std::ostream& operator<<(std::ostream& os, const MyString& s);
std::istream& operator>>(std::istream& is, MyString& s);

MyString addTxtExtension(const MyString &path);
