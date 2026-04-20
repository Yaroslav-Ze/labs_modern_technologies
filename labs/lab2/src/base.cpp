#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "base.hpp"

BaseFile::BaseFile() : sth_file(nullptr) {
    mode[0] = '\0';
    std::cout << "Конструктор родительского класса по умолчанию: файл открыт, режим - " << mode << "\n";
}

BaseFile::BaseFile(const char* way, const char* how) : sth_file(nullptr) {
    if (way && how) {
        sth_file = fopen(way, how);
        if (sth_file) {
            strncpy(mode, how, 2);
            mode[2] = '\0';
        } 
        else {
            mode[0] = '\0';
        }
    }
    if (sth_file) {
        std::cout << "Конструктор родительского класса: файл открыт, режим " << mode << "\n";
    } else {
        std::cout << "Конструктор родительского класса: получен NULL!\n";
    }
}

BaseFile::BaseFile(FILE* some_file, const char* how) : sth_file(some_file) {
    if (some_file) {
        if (how) {
            strncpy(mode, how, 2);
            mode[2] = '\0';
        } 
        else {
            mode[0] = '\0';
        }
    } 
    else {
        sth_file = nullptr; 
        mode[0] = '\0';
    }
    if (sth_file) {
        std::cout << "Конструктор родительского класса с FILE*: файл открыт, режим " << mode << "\n";
    } else {
        std::cout << "Конструктор родительского класса с FILE*: получен NULL!\n";
    }
}

BaseFile::~BaseFile() {
    if (sth_file) {
        fclose(sth_file);
        sth_file = nullptr;
    }
    std::cout  << "Вызван деструктор для родительского класса \n";
}

bool BaseFile::is_open() {
    if (sth_file) {
        return 1;
    }
    return 0;
}

bool BaseFile::can_read() {
    if (!sth_file) return false;
    if (mode[0] == 'r' || strchr(mode, '+')) {
        return true;
    }
    return false;
}    

bool BaseFile::can_write() {
    if (!sth_file) return false;
    if (mode[0] == 'w' || mode[0] == 'a' || strchr(mode, '+')) {
        return true;
    }
    return false;
}

size_t BaseFile::write_raw(const void *buf, size_t n_bytes) {
    if (!sth_file || !buf || !can_write()) {
        return 0;
    }
    return fwrite(buf, 1, n_bytes, sth_file);
}

size_t BaseFile::read_raw(void *buf, size_t max_bytes) {
    if (!sth_file || !buf || !can_read()) {
        return 0;
    }
    return fread(buf, 1, max_bytes, sth_file);
}

long BaseFile::tell() {
    if (!sth_file) return -1;
    
    return ftell(sth_file);
}

bool BaseFile::seek(long offset) {
    if (!sth_file) return false;
    
    return fseek(sth_file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void *buf, size_t n_bytes) {
    if (!sth_file || !buf || !can_write()) {
        return 0;
    }
    return fwrite(buf, 1, n_bytes, sth_file);
}

size_t BaseFile::read(void *buf, size_t max_bytes) {
    if (!sth_file || !buf || !can_read()) {
        return 0;
    }
    return fread(buf, 1, max_bytes, sth_file);
}




// ---------------------------------------

Base32File::Base32File() : BaseFile(), abcde("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456") {
    write_buf_size = 0;
    read_buf_size = 0;
    read_buf_pos = 0;
    std::cout << "конструктор по умолчанию Base32File \n";
}

Base32File::Base32File(const char* way, const char* how, const char* abc) : BaseFile(way, how), abcde(abc)
{
    write_buf_size = 0;
    read_buf_size = 0;
    read_buf_pos = 0;
    std::cout << "конструктор Base32File \n";
}

Base32File::Base32File(FILE* sth_file, const char* how, const char* abc) : BaseFile(sth_file, how), abcde(abc)
{
    write_buf_size = 0;
    read_buf_size = 0;
    read_buf_pos = 0;
    std::cout << "конструктор Base32File с FILE* \n";
}

Base32File::~Base32File() {
    if (write_buf_size > 0) {
        char encoded[8] = {0};

        encode32(write_buffer, write_buf_size, encoded);

        int out_size = encoded32_size(write_buf_size);
        write_raw(encoded, out_size);
    }
    std::cout << "деструктор Base32File \n";
}

size_t Base32File::encoded32_size(size_t raw_size) {
    if (raw_size < 1) { 
        return 0;
    }
    return (raw_size * 8 + 4) / 5;
}

size_t Base32File::decoded32_size(size_t encode_size) {
    if (encode_size < 1) { 
        return 0;
    }
    return (encode_size *5 ) / 8;
}

bool Base32File::encode32(const char *raw_data, int raw_size, char *dst) {
    if (raw_data == nullptr || dst == nullptr || raw_size <= 0) {
        return 1;
    }

    int size = encoded32_size(raw_size);

    int razm = 8 * raw_size;
    while (razm % 5 != 0) {
        razm++;
    }

    bool *booliki = new bool[razm];
    for (int i = 0; i < razm; ++i) {
        booliki[i] = 0;
    }

    unsigned char mask = 128;

    for (int bait = 0; bait < raw_size; ++bait) {
        unsigned char bykv = raw_data[bait];

        for (int i = 0; i < 8; ++i) {
            booliki[bait * 8 + i] = bykv & mask;
            bykv <<= 1;
        }
    }

    for (int i = 0; i < size; ++i) {
        int shifr = 0;

        for (int j = 0; j < 5; ++j) {
            shifr |= (booliki[i * 5 + j] << (4 - j));
        }

        dst[i] = abcde[shifr];
    }

    delete[] booliki;
    return 0;
}

char Base32File::decode32(const char *encoded_data, int encoded_size, char *dst) {
    if (encoded_data == nullptr || dst == nullptr || encoded_size <= 0) {
        return 1;
    }

    int size = decoded32_size(encoded_size);

    int razm = 5 * encoded_size;
    while (razm % 8 != 0) {
        razm--;
    }

    bool *booliki = new bool[razm];
    for (int i = 0; i < razm; ++i) {
        booliki[i] = 0;
    }

    unsigned char mask = 16;

    for (int bait = 0; bait < encoded_size; ++bait) {
        int bykv = -1;

        for (int jo = 0; jo < 32; ++jo) {
            if (abcde[jo] == encoded_data[bait]) {
                bykv = jo;
                break;
            }
        }

        if (bykv == -1) {
            delete[] booliki;
            return 2;
        }

        for (int i = 0; i < 5; ++i) {
            if (bait * 5 + i >= razm) {
                break;
            }
            booliki[bait * 5 + i] = bykv & mask;
            bykv <<= 1;
        }
    }

    for (int i = 0; i < size; ++i) {
        int shifr = 0;

        for (int j = 0; j < 8; ++j) {
            shifr |= (booliki[i * 8 + j] << (7 - j));
        }

        dst[i] = shifr;
    }

    delete[] booliki;
    return 0;
}

size_t Base32File::write(const void *buf, size_t n_bytes) {
    if (!buf || n_bytes == 0 || !can_write()) {
        return 0;
    }

    const char* data = (const char*)buf;
    size_t i = 0;

    while (i < n_bytes) {
        write_buffer[write_buf_size] = data[i]; // набираем в буффер чаров
        i++;
        write_buf_size++;

        if (write_buf_size == 5) { // как только набрали достаточно для шифрования
            char encoded[8];

            encode32(write_buffer, 5, encoded);
            write_raw(encoded, 8);

            write_buf_size = 0;
        }
    }

    return n_bytes;
}

size_t Base32File::read(void *buf, size_t max_bytes) {
    if (!buf || max_bytes == 0 || !can_read()) {
        return 0;
    }

    char* out = (char*)buf;
    size_t total = 0;

    while (total < max_bytes) {
        if (read_buf_pos < read_buf_size) {
            out[total] = read_buffer[read_buf_pos];
            total++;
            read_buf_pos++;
            continue;
        }

        char encoded[8];
        size_t r = read_raw(encoded, 8);

        if (r < 8) {
            break;
        }

        if (decode32(encoded, 8, read_buffer) != 0) {
            break;
        }

        read_buf_size = 5;
        read_buf_pos = 0;
    }

    return total;
}

// ---------------------------------------

RleFile::RleFile() : BaseFile() {
    last_char = 0;
    count = 0;
    has_str = 0;

    read_char = 0;
    read_count = 0;
    has_read = 0;
    std::cout << "конструктор RleFile по умолчанию \n";
}

RleFile::RleFile(const char* way, const char* how) : BaseFile(way, how) {
    last_char = 0;
    count = 0;
    has_str = 0;

    read_char = 0;
    read_count = 0;
    has_read = 0;
    std::cout << "конструктор RleFile \n";
}

RleFile::RleFile(FILE* sth_file, const char* how) : BaseFile(sth_file, how) {
    last_char = 0;
    count = 0;
    has_str = 0;

    read_char = 0;
    read_count = 0;
    has_read = 0;
    std::cout << "конструктор RleFile с FILE*  \n";
}

RleFile::~RleFile() {
    if (has_str && count > 0) {
        write_raw(&count, 1);
        write_raw(&last_char, 1);
    }
    std::cout << "деструктор RleFile \n";
}

size_t RleFile::write(const void *buf, size_t n_bytes) {
    if (!buf || n_bytes == 0 || !can_write()) {
        return 0;
    }

    const char* str = (const char*)buf;

    for (size_t i = 0; i < n_bytes; ++i) {
        char bykv = str[i];

        if (!has_str) {
            last_char = bykv;
            count = 1;
            has_str = 1;
        }
        else if (bykv == last_char && count < 255) {
            count++;
        }
        else {
            write_raw(&count, 1);
            write_raw(&last_char, 1);

            last_char = bykv;
            count = 1;
            has_str = 1;
        }
    }

    return n_bytes;
}

size_t RleFile::read(void *buf, size_t max_bytes) {
    if (!buf || max_bytes == 0 || !can_read()) {
        return 0;
    }

    char* str = (char*)buf;
    size_t total = 0;

    while (total < max_bytes) {

        if (has_read && read_count) { // если мы прочитали символ вместе с его количеством уже  
            str[total] = read_char;
            total++;
            read_count--;

            if (read_count == 0) {
                has_read = 0;
            }

            continue; // идем дальше
        }
        // попадаем сюда когда хотим читать следующий блок
        unsigned char c;
        char bykv;

        size_t r1 = read_raw(&c, 1);
        size_t r2 = read_raw(&bykv, 1);

        if (r1 < 1 || r2 < 1) {
            break;
        }

        read_count = c;
        read_char = bykv;
        has_read = 1;
    }

    return total;
}

// ------------------------

void write_int(IFile &file, int n) {
    if (n < 0) { 
        file.write("-", 1); 
        n = -1*n;
    }

    if (n == 0) {
        file.write("0", 1);
    }

    while (n > 0) {
        int count10 = 10;
        while (n / count10 > 0) {
            count10 = count10*10;
        }
        count10 = count10 / 10;
        char c = '0' + (n/count10);
        file.write(&c, 1);
        n = n - ((n/count10)*count10);
    }

    return;

}

// --------------------------------------------------------

Base32File2::Base32File2(IFile* f, const char* abc)
    : file(f), abcde(abc), write_buf_size(0), read_buf_size(0), read_buf_pos(0)
{
    std::cout << "конструктор Base32File2\n";
}

Base32File2::~Base32File2() {
    if (write_buf_size > 0) {
        char encoded[8] = {0};
        encode32(write_buffer, write_buf_size, encoded);
        int out_size = (int)encoded32_size(write_buf_size);
        file->write(encoded, out_size);
    }

    delete file;
    std::cout << "деструктор Base32File2\n";
}

bool Base32File2::can_read() {
    return file && file->can_read();
}

bool Base32File2::can_write() {
    return file && file->can_write();
}

size_t Base32File2::encoded32_size(size_t raw_size) {
    if (raw_size < 1) {
        return 0;
    }
    return (raw_size * 8 + 4) / 5;
}

size_t Base32File2::decoded32_size(size_t encode_size) {
    if (encode_size < 1) {
        return 0;
    }
    return (encode_size * 5) / 8;
}

bool Base32File2::encode32(const char *raw_data, int raw_size, char *dst) {
    if (raw_data == nullptr || dst == nullptr || raw_size <= 0) {
        return 1;
    }

    int size = (int)encoded32_size(raw_size);

    int razm = 8 * raw_size;
    while (razm % 5 != 0) {
        razm++;
    }

    bool *booliki = new bool[razm];
    for (int i = 0; i < razm; ++i) {
        booliki[i] = 0;
    }

    unsigned char mask = 128;

    for (int bait = 0; bait < raw_size; ++bait) {
        unsigned char bykv = (unsigned char)raw_data[bait];

        for (int i = 0; i < 8; ++i) {
            booliki[bait * 8 + i] = (bykv & mask) != 0;
            bykv <<= 1;
        }
    }

    for (int i = 0; i < size; ++i) {
        int shifr = 0;

        for (int j = 0; j < 5; ++j) {
            shifr |= (booliki[i * 5 + j] << (4 - j));
        }

        dst[i] = abcde[shifr];
    }

    delete[] booliki;
    return 0;
}

char Base32File2::decode32(const char *encoded_data, int encoded_size, char *dst) {
    if (encoded_data == nullptr || dst == nullptr || encoded_size <= 0) {
        return 1;
    }

    int size = (int)decoded32_size(encoded_size);

    int razm = 5 * encoded_size;
    while (razm % 8 != 0) {
        razm--;
    }

    bool *booliki = new bool[razm];
    for (int i = 0; i < razm; ++i) {
        booliki[i] = 0;
    }

    unsigned char mask = 16;

    for (int bait = 0; bait < encoded_size; ++bait) {
        int bykv = -1;

        for (int jo = 0; jo < 32; ++jo) {
            if (abcde[jo] == encoded_data[bait]) {
                bykv = jo;
                break;
            }
        }

        if (bykv == -1) {
            delete[] booliki;
            return 2;
        }

        for (int i = 0; i < 5; ++i) {
            if (bait * 5 + i >= razm) {
                break;
            }
            booliki[bait * 5 + i] = (bykv & mask) != 0;
            bykv <<= 1;
        }
    }

    for (int i = 0; i < size; ++i) {
        int shifr = 0;

        for (int j = 0; j < 8; ++j) {
            shifr |= (booliki[i * 8 + j] << (7 - j));
        }

        dst[i] = (char)shifr;
    }

    delete[] booliki;
    return 0;
}

size_t Base32File2::write(const void *buf, size_t n_bytes) {
    if (!buf || n_bytes == 0 || !can_write()) {
        return 0;
    }

    const char* data = (const char*)buf;
    size_t i = 0;

    while (i < n_bytes) {
        write_buffer[write_buf_size] = data[i];
        i++;
        write_buf_size++;

        if (write_buf_size == 5) {
            char encoded[8];
            encode32(write_buffer, 5, encoded);
            file->write(encoded, 8);
            write_buf_size = 0;
        }
    }

    return n_bytes;
}

size_t Base32File2::read(void *buf, size_t max_bytes) {
    if (!buf || max_bytes == 0 || !can_read()) {
        return 0;
    }

    char* out = (char*)buf;
    size_t total = 0;

    while (total < max_bytes) {
        if (read_buf_pos < read_buf_size) {
            out[total] = read_buffer[read_buf_pos];
            total++;
            read_buf_pos++;
            continue;
        }

        char encoded[8];
        size_t r = file->read(encoded, 8);

        if (r < 8) {
            break;
        }

        if (decode32(encoded, 8, read_buffer) != 0) {
            break;
        }

        read_buf_size = 5;
        read_buf_pos = 0;
    }

    return total;
}


//--------------------------------

RleFile2::RleFile2(IFile* f) : file(f) {
    last_char = 0;
    count = 0;
    has_str = 0;

    read_char = 0;
    read_count = 0;
    has_read = 0;

    std::cout << "конструктор RleFile2\n";
}

RleFile2::~RleFile2() {
    if (has_str && count > 0) {
        file->write(&count, 1);
        file->write(&last_char, 1);
    }

    delete file;
    std::cout << "деструктор RleFile2\n";
}

bool RleFile2::can_read() {
    return file && file->can_read();
}

bool RleFile2::can_write() {
    return file && file->can_write();
}

size_t RleFile2::write(const void *buf, size_t n_bytes) {
    if (!buf || n_bytes == 0 || !can_write()) {
        return 0;
    }

    const char* str = (const char*)buf;

    for (size_t i = 0; i < n_bytes; ++i) {
        char bykv = str[i];

        if (!has_str) {
            last_char = bykv;
            count = 1;
            has_str = 1;
        }
        else if (bykv == last_char && count < 255) {
            count++;
        }
        else {
            file->write(&count, 1);
            file->write(&last_char, 1);

            last_char = bykv;
            count = 1;
            has_str = 1;
        }
    }

    return n_bytes;
}

size_t RleFile2::read(void *buf, size_t max_bytes) {
    if (!buf || max_bytes == 0 || !can_read()) {
        return 0;
    }

    char* str = (char*)buf;
    size_t total = 0;

    while (total < max_bytes) {
        if (has_read && read_count > 0) {
            str[total] = read_char;
            total++;
            read_count--;

            if (read_count == 0) {
                has_read = 0;
            }

            continue;
        }

        unsigned char c;
        char bykv;

        size_t r1 = file->read(&c, 1);
        size_t r2 = file->read(&bykv, 1);

        if (r1 < 1 || r2 < 1) {
            break;
        }

        read_count = c;
        read_char = bykv;
        has_read = 1;
    }

    return total;
}

char* random_data(size_t size) {
    char* data = new char[size];

    for (size_t i = 0; i < size; ++i) {
        data[i] = rand() % 256;
    }

    return data;
}

void compare(const char* a, const char* b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (a[i] != b[i]) {
            std::cout << "Ошибка в тесте " << ", позиция " << i << "\n";
            assert(false);
        }
    }
}