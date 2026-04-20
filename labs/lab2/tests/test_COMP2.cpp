#include "../src/base.hpp"
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>

int main() {
    const int SIZE = 50000;
    const int CHUNK = 256;

    char* data = new char[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        data[i] = rand() % 256;
    }

    {
        Base32File2 f(new RleFile("test_COMP2.bin", "wb"));

        int pos = 0;
        while (pos < SIZE) {
            int sz = CHUNK;
            if (pos + sz > SIZE) {
                sz = SIZE - pos;
            }
            f.write(data + pos, sz);
            pos += sz;
        }
    }

    char* read_data = new char[SIZE];

    {
        Base32File2 f(new RleFile("test_COMP2.bin", "rb"));

        int pos = 0;
        while (pos < SIZE) {
            int n = f.read(read_data + pos, CHUNK);
            if (n == 0) break;
            pos += n;
        }

        assert(pos == SIZE);
    }

    for (int i = 0; i < SIZE; ++i) {
        if (data[i] != read_data[i]) {
            std::cout << "Ошибка на позиции " << i << "\n";
            delete[] data;
            delete[] read_data;
            return 1;
        }
    }

    std::cout << "COMP2 тест пройден\n";

    delete[] data;
    delete[] read_data;

    return 0;
}