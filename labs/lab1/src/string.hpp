class MyString {
    char *string;
    int len;

public:
    MyString();
    MyString(const char * str);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    char get(int i);
    int get_len();
    char* get_str();
    void set(int i, char c);
    void set_new_string(const char *str);
    void print();
    void read_line();

};

