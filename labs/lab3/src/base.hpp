#include <cstddef>
#include <cstdio>

class IFile {

public:
    virtual ~IFile() {}
    virtual bool can_read() = 0; // чисто виртуальные методы
    virtual bool can_write() = 0;

    virtual size_t write(const void *buf, size_t n_bytes) = 0;
    virtual size_t read(void *buf, size_t max_bytes) = 0;
};


class BaseFile : public IFile {
    FILE* sth_file;
    char mode[3];

public:
    BaseFile();
    BaseFile(const char* way, const char* how);
    BaseFile(FILE* some_file, const char* how);
    ~BaseFile();

    BaseFile(const BaseFile& other) = delete;
    BaseFile& operator=(const BaseFile& other) = delete;

    BaseFile(BaseFile&& other);
    BaseFile& operator=(BaseFile&& other);

    bool is_open();
    bool can_read();
    bool can_write();
    size_t write_raw(const void *buf, size_t n_bytes);
    size_t read_raw(void *buf, size_t max_bytes);
    long tell();
    bool seek(long offset);
    virtual size_t write(const void *buf, size_t n_bytes);
    virtual size_t read(void *buf, size_t max_bytes);
};


class Base32File : public BaseFile {
    const char* abcde;

    char write_buffer[5];
    int write_buf_size = 0;

    char read_buffer[5];
    int read_buf_size = 0;
    int read_buf_pos = 0;

public:
    Base32File();
    Base32File(const char* way, const char* how, const char* abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    Base32File(FILE* sth_file, const char* how, const char* abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    ~Base32File();

    

    size_t encoded32_size(size_t raw_size);
    size_t decoded32_size(size_t encode_size);

    bool encode32(const char *raw_data, int raw_size, char *dst);
    char decode32(const char *encoded_data, int encoded_size, char *dst);

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);

    
};

class RleFile : public BaseFile {
    char last_char;
    unsigned char count;
    bool has_str;

    char read_char;
    unsigned char read_count;
    bool has_read;

public:
    RleFile();
    RleFile(const char* way, const char* how);
    RleFile(FILE* sth_file, const char* how);
    ~RleFile();

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};

void write_int(IFile &file, int n);


// ----------------------------------

class Base32File2 : public IFile {
    IFile* file;
    const char* abcde;

    char write_buffer[5];
    int write_buf_size;

    char read_buffer[5];
    int read_buf_size;
    int read_buf_pos;

public:
    Base32File2(IFile* file, const char* abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    ~Base32File2();

    bool can_read();
    bool can_write();

    size_t encoded32_size(size_t raw_size);
    size_t decoded32_size(size_t encode_size);

    bool encode32(const char *raw_data, int raw_size, char *dst);
    char decode32(const char *encoded_data, int encoded_size, char *dst);

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};

class RleFile2 : public IFile {
    IFile* file;

    char last_char;
    unsigned char count;
    bool has_str;

    char read_char;
    unsigned char read_count;
    bool has_read;

public:
    RleFile2(IFile* file);
    ~RleFile2();

    bool can_read();
    bool can_write();

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};

char* random_data(size_t size);

void compare(const char* a, const char* b, size_t size);