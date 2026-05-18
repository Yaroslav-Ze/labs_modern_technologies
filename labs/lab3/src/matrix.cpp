#include <iostream>
#include "matrix.hpp"
 
Matrix::Matrix(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Размер матрицы ДОЛЖЕН быть положительным");
    }
    
    str = n;
    stolb = n;
    massiv = new double[str * stolb];
    
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] = 0.0;
    }
    
    for (int i = 0; i < n; i++) {
        massiv[i * stolb + i] = 1.0;
    }
}

Matrix::Matrix(int m, int n, double fill_value) {
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Размеры матрицы обязаны быть положительными");
    }
    
    str = m;
    stolb = n;
    massiv = new double[str * stolb];
    
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] = fill_value;
    }
}

Matrix::Matrix(const Matrix& other) {
    str = other.str;
    stolb = other.stolb;
    massiv = new double[str * stolb];
    
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] = other.massiv[i];
    }
}



Matrix::~Matrix() {
    delete[] massiv;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this; 
    }
    
    delete[] massiv;
    
    str = other.str;
    stolb = other.stolb;
    
    massiv = new double[str * stolb];
    
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] = other.massiv[i];
    }
    
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (str != other.str || stolb != other.stolb) {
        throw std::invalid_argument("Несовместимые размеры матриц для сложения");
    }
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] += other.massiv[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (str != other.str || stolb != other.stolb) {
        throw std::invalid_argument("Несовместимые размеры матриц для вычитания");
    }
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] -= other.massiv[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(const double value) {
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] *= value;
    }
    return *this;
}

Matrix& Matrix::operator/=(const double value) {
    if (value == 0.0) {
        throw std::invalid_argument("Деление на ноль");
    }
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] /= value;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix out = *this;
    out += other;
    return out;

}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix out = *this;
    out -= other;
    return out;    
}

Matrix Matrix::operator*(double value) const {
    Matrix out = *this;
    out *= value;
    return out;     
}

Matrix Matrix::operator/(double value) const {
    Matrix out = *this;
    out /= value;
    return out;    
}

int Matrix::index(int i, int j) const {
    return i * stolb + j;
}

double Matrix::get(int i, int j) const {
    if (i < 0 || i >= str || j < 0 || j >= stolb) {
        throw std::out_of_range("Индекс выходит за границы матрицы");
    }
    return massiv[index(i, j)];
}

void Matrix::set(int i, int j, double value) {
    if (i < 0 || i >= str || j < 0 || j >= stolb) {
        throw std::out_of_range("Индекс выходит за границы матрицы");
    }
    massiv[index(i, j)] = value;
}

int Matrix::get_height() {
    return str;
}

int Matrix::get_width() {
    return stolb;
}

void Matrix::negate() {
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] = -massiv[i];
    }
}

void Matrix::add_in_place(Matrix& other) {
    if (str != other.str || stolb != other.stolb) {
        throw std::invalid_argument("Несовместимые размеры матриц для сложения");
    }
    
    for (int i = 0; i < str * stolb; i++) {
        massiv[i] += other.massiv[i];
    }
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (stolb != other.str) {
        throw std::invalid_argument("Несовместимые размеры матриц для умножения");
    }
    
    Matrix res(str, other.stolb, 0.0);
    
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < other.stolb; j++) {
            double eli = 0.0;
            for (int k = 0; k < stolb; k++) {
                eli += get(i, k) * other.get(k, j);
            }
            res.set(i, j, eli);
        }
    }
    
    return res;
}

Matrix Matrix::operator*(const Matrix& other) const {
    return multiply(other);
}

void Matrix::print() const {
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < stolb; j++) {
            std::cout << massiv[i * stolb + j] << " ";
        }
        std::cout << '\n';
    }
}

Matrix operator*(double value, const Matrix& m) {
    return m * value;  
}

Matrix operator-(const Matrix& m) {
    Matrix res = m;
    res *= -1;
    return res;
}

Matrix::Matrix(Matrix&& other) {
    str = other.str;
    stolb = other.stolb;
    massiv = other.massiv;

    other.str = 0;
    other.stolb = 0;
    other.massiv = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) {
    if (this != &other) {
        delete[] massiv;

        str = other.str;
        stolb = other.stolb;
        massiv = other.massiv;

        other.str = 0;
        other.stolb = 0;
        other.massiv = nullptr;
    }
    return *this;
}