#include <cassert>
#include "../src/rect.hpp"

int main() {
    {
        Rect rect(5, -20, 30, 0);
        rect.move(5, -10); 
        assert(rect.get_top() == -5);     
        assert(rect.get_bottom() == -30);   
        assert(rect.get_right() == 35);   
        assert(rect.get_left() == 5);    
        
       
    }

    {
        Rect rect(55, 5, 115, 15);
        rect.move(0, 0);
        assert(rect.get_top() == 55);     
        assert(rect.get_bottom() == 5);   
        assert(rect.get_right() == 115);   
        assert(rect.get_left() == 15);  
       
    }

    {
        Rect rect(100, -20, 30, 0);
        rect.inflate(5);  
        assert(rect.get_top() == 105);     
        assert(rect.get_bottom() == -25);   
        assert(rect.get_right() == 35);   
        assert(rect.get_left() == -5);  
         
    }

    {
        Rect rect(8, 2, 16, 6);
        rect.inflate(-3, 6);  
        assert(rect.get_top() == 14);     
        assert(rect.get_bottom() == -4);   
        assert(rect.get_right() == 13);   
        assert(rect.get_left() == 9);     
    }

    { // l r t b 
        Rect rect(4, 0, 6, 0);
        rect.inflate(3, 6, 3, 6);  
        assert(rect.get_top() == 7);     
        assert(rect.get_bottom() == -6);   
        assert(rect.get_right() == 12);   
        assert(rect.get_left() == -3);     
    }
   
    {
        Rect rect(10, 10, 9, 5);  
        rect.inflate(-5);  
        assert(rect.get_width() >= 0);
        assert(rect.get_height() >= 0);
    }

    return 0;
}