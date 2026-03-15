#include <iostream>

#include "string.hpp"
#include "wrap.hpp"


class MyString;

// ----------------------------------------------------------------------------------
// для переноса строк


TextWrapper::TextWrapper(MyString &s, int line_width) {
    simvols_v_stroke = line_width;
    stroka = s.get_str();
    vsego_dlina = s.get_len();
    ostalos_simvolov_vstroke = line_width;
    vsego_slov = 0;
    dlina_slova = 0;
    bylo = 0;

}

void TextWrapper::podschet() {
    vsego_slov = 0;
    int i = 0;
    while (stroka[i] != '\0') {
        if (stroka[i] == ' ') {
            vsego_slov++;
        }
        i++;
    }
    vsego_slov++;
}

void TextWrapper::razbiv() {
    this->podschet();
    dliny_slov = new int[vsego_slov];
    for (int i = 0; i < vsego_slov; i++) {
        dliny_slov[i] = 0;
    }
    int slovo = 0;
    int i = 0;
    while (stroka[i] != '\0') {
        if (stroka[i] == ' ') {
            slovo++;
        }
        else {
            dliny_slov[slovo]++;
        }
        i++;
    }
    bylo = 1;
}

bool TextWrapper::big() {
    if (dlina_slova > simvols_v_stroke) {
        return 1;
    }
    else {
        return 0;
    }
}

/*
bool TextWrapper::pomechaetsya() {
    if (dlina_slova + 1 <= ostalos_simvolov_vstroke) { // +1 для учета пробела
        ostalos_simvolov_vstroke -= (dlina_slova + 1);
        return 1;
    }
    else {
        while (ostalos_simvolov_vstroke != 0) {
            std::cout << ' ';
            ostalos_simvolov_vstroke--;
        }
        ostalos_simvolov_vstroke = simvols_v_stroke;
        std::cout << '\n';
        return 0;
    }
}
*/

bool TextWrapper::pomechaetsya() {
    if (dlina_slova + 1 <= ostalos_simvolov_vstroke) { // +1 для учета пробела
        return 1;
    }
    else {
        return 0;
    }
}

void TextWrapper::deistvo() {
    if (this->pomechaetsya()) {
        ostalos_simvolov_vstroke -= (dlina_slova + 1);
        return;
    }
    while (ostalos_simvolov_vstroke != 0) {
        std::cout << ' ';
        ostalos_simvolov_vstroke--;
    }
    std::cout << " |";
    ostalos_simvolov_vstroke = simvols_v_stroke;
    std::cout << '\n';
    std::cout << '|';
    ostalos_simvolov_vstroke -= (dlina_slova + 1);

}

void TextWrapper::pech_bykv() {
    std::cout << stroka[index_bykvy];
    index_bykvy++;
}

bool TextWrapper::mozhno() {
    if (index_bykvy < vsego_dlina && stroka[index_bykvy] != ' ') {
        return 1;
    }
    else {
        return 0;
    }
}

void TextWrapper::pechat_slova_norm() {
    std::cout << ' ';
    while (this->mozhno()) {
        this->pech_bykv();
    }
    index_bykvy++;
    index_slova++;
    
}

void TextWrapper::pechat_big() {
    std::cout << ' ';
    ostalos_simvolov_vstroke--;
    while (this->mozhno()) {
        if (ostalos_simvolov_vstroke > 0) {
            this->pech_bykv();
            ostalos_simvolov_vstroke--;
        }
        else {
            ostalos_simvolov_vstroke = simvols_v_stroke;
            std::cout << " |";
            std::cout << '\n';
            std::cout << "| ";
            ostalos_simvolov_vstroke--;
            this->pech_bykv();
            ostalos_simvolov_vstroke--;

        }
    }
    index_bykvy++;
    index_slova++;
}

void TextWrapper::print_wrapped() {
    if (!bylo) {
        this->razbiv();
    }
    std::cout << '\n' <<" В каждой следующей строке по " << simvols_v_stroke << " символов \n \n";
    std::cout << "|";
    index_slova = 0;
    index_bykvy = 0;
    while (index_slova < vsego_slov) {
        dlina_slova = dliny_slov[index_slova];
        if (this->big()) {
            this->pechat_big();
        }
        else {
            this->deistvo();
            this->pechat_slova_norm();
        }
        
    }

    std::cout << '\n' << '\n';
    delete[] dliny_slov;
}