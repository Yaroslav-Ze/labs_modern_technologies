#include <utility>

class Matrix {
    int str; // элементы в строке олнрй
    int stolb; // элементы в  столбце одном
    double* massiv;
public:
    Matrix(int n);                                     // единичная матрица
    Matrix(int m, int n, double fill_value = 0.0);     // матрица заполненная fill_value
    Matrix(const Matrix& other); 
    ~Matrix();

    Matrix& operator=(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const double value);
    Matrix& operator/=(const double value);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double value) const;
    Matrix operator/(double value) const;

    int index(int i, int j) const;
    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height();
    int get_width();
    
    void negate();
    void add_in_place(Matrix& other);
    Matrix multiply(const Matrix& other) const;


    void print() const;

    Matrix(Matrix&& other);
    Matrix& operator=(Matrix&& other);
    
};

Matrix operator*(double value, const Matrix& m);

Matrix operator-(const Matrix& m);