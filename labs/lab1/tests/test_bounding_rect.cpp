#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    {
        Rect r1(5, 0, 5, 0);
        Rect r2(6, 1,5, 0);
        Rect bou = bounding_rect(r1, r2);
        assert(bou.get_top() == 6);     
        assert(bou.get_bottom() == 0);   
        assert(bou.get_right() == 5);   
        assert(bou.get_left() == 0);    
    }

    { // перепутаем ккординаты
        Rect r1(5, 10, 5, 0);
        Rect r2(6, 0, -1, 5);
        Rect bou = bounding_rect(r1, r2);
        assert(bou.get_top() == 10);     
        assert(bou.get_bottom() == 0);   
        assert(bou.get_right() == 5);   
        assert(bou.get_left() == -1);    
    }
        
    return 0;
}

