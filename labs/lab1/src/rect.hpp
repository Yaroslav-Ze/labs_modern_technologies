
/*
class Rect {
    int top;
    int bottom;
    int right;
    int left;

public:
    Rect();
    Rect(int a, int b, int c, int d);
    Rect(const Rect &A);
    ~Rect();
    int get_top();
    int get_bottom();
    int get_left();
    int get_right();
    void set_all(int top, int bottom, int right, int left);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);
    void move(int x = 0, int y = 0);
    int get_width();
    int get_height();
    int get_square();

    void set_width(int w);
    void set_height(int h);
};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);
*/

class Rect {
    int pointx;
    int pointy;
    int h;
    int w;
    
public:
    Rect();
    Rect(int a, int b, int c, int d);
    Rect(const Rect &A);
    ~Rect();
    int get_top();
    int get_bottom();
    int get_left();
    int get_right();
    void set_all(int top, int bottom, int right, int left);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);
    void move(int x = 0, int y = 0);
    int get_width();
    int get_height();
    int get_square();

    void set_width(int w);
    void set_height(int h);
};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);