#include <cassert>
#include "../src/rect.hpp"

int main() {
    {
        Rect rect(10, 20, 30, 40);
        assert(rect.get_width() == 10); 
        assert(rect.get_height() == 10); 
    }

    {
        Rect rect(7, 0, 5, 10);
        assert(rect.get_square() == 35); 
    }

    {
        Rect rect(30, 10, 30, 25);
        rect.set_width(25);
        assert(rect.get_width() == 25);
        assert(rect.get_left() == 25);
        assert(rect.get_right() == 50); 
    }

    {
        Rect rect(30, 10, 30, 25);
        rect.set_height(30);
        assert(rect.get_height() == 30);
        assert(rect.get_bottom() == 10);
        assert(rect.get_top() == 40); 
    }

    {
        Rect rect(30, 10, 30, 25);
        rect.set_width(-15);
        assert(rect.get_width() == 0); 
        rect.set_height(-15);
        assert(rect.get_height() == 0);
        assert(rect.get_right() == 25); 
    }

    return 0;
}
