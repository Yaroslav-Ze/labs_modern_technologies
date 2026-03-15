class Barrel{
    int v; // обьем, >= 0
    int zhid; // сколько жидкости (<= v)
    int spirt; // содержание спирта в бочке в процентах, e [0; 100]
public:
    Barrel(int v0 = 0, int zhid0 = 0, float spirt0 = 0);
    float get_spirt();
    int get_zhid();
    int get_v();
    void set_spirt(float s);
    void set_v(int v0);
    void set_zhid(int zhid0);
    void pereliv(Barrel &sth, int kryzhka);

};