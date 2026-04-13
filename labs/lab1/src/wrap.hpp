#include "string.hpp"

class TextWrapper {
    char *stroka; // указатель на общую строку
    int *dliny_slov; // указатель на массив из длин соответсвующих слов
    int vsego_dlina; // длина общей строки
    int simvols_v_stroke; // на какое количесвто символов в строке разбивать
    int vsego_slov; // сколько всего слов в строке
    int dlina_slova; // длина слова ?
    int ostalos_simvolov_vstroke; // подсчет оставшегося места в строке
    bool bylo;
    int index_slova;
    int index_bykvy;
    
    void podschet();
    void razbiv();
    bool pomechaetsya();
    bool big();
    void pech_bykv();
    void pechat_slova_norm();
    void pechat_big();
    bool mozhno();
    void deistvo();

public:
    // TODO: не нужен ли #include?
    TextWrapper(MyString &s, int line_width);

    void print_wrapped();


};
