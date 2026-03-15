class Matrix {
    int str; // элементы в строке олнрй
    int stolb; // элементы в столбце одном
    double* massiv;
public:
    Matrix(int n);                                     // единичная матрица
    Matrix(int m, int n, double fill_value = 0.0);     // матрица заполненная fill_value
    Matrix(const Matrix& other); 
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int index(int i, int j);
    double get(int i, int j);
    void set(int i, int j, double value);
    int get_height();
    int get_width();
    
    void negate();
    void add_in_place(Matrix& other);
    Matrix multiply(Matrix& other);
    
    
    
};