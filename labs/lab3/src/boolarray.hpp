

int nuzhno_bytes(int n);
int index_byte(int bool_index);
int index_bit(int bool_index);

class BoolArray {
    unsigned char* arrb;
    int len;



    bool get_bit(int index) const;
    void set_bit(int index, bool value);

public:
    class Boolik {
        BoolArray& arr;
        int index;

    public:
        Boolik(BoolArray& a, int i);

        Boolik& operator=(bool value);
        Boolik& operator=(const Boolik& other);

        operator bool() const; // оператор неявного приведения типа, 
        //который позволяет объекту класса преобразовываться к bool
    };

    BoolArray();
    BoolArray(int n, bool value = false);
    BoolArray(const BoolArray& other);
    BoolArray& operator=(const BoolArray& other);
    ~BoolArray();

    int size() const;

    Boolik operator[](int index);
    bool operator[](int index) const;

    void resize(int new_size, bool value = false);
};