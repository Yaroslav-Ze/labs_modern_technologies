#include <cassert>
#include "../src/rect.hpp"

int main() {
    {  
        Rect rect;  // Конструктор по умолчанию
        assert(rect.get_left() == 0);
        assert(rect.get_right() == 0);
        assert(rect.get_bottom() == 0);
        assert(rect.get_top() == 0);
    }

    {
        Rect rect(22, 10, 33, 8);      //Конструктор с параметрами где (верх, низ, право, лево)
        assert(rect.get_top() == 22);
        assert(rect.get_bottom() == 10);    
        assert(rect.get_right() == 33);
        assert(rect.get_left() == 8);
        
    }

    {
        Rect rect;
        rect.set_all(-100, 100, 30, 0); // проверка сет олл (с опечатанным вводом верха и низа)
        assert(rect.get_top() == 100);
        assert(rect.get_bottom() == -100);    
        assert(rect.get_right() == 30);
        assert(rect.get_left() == 0);
    }

    {
        Rect rect(1, 2, 3, 4); // сет олл после конструктора с параметрами
        rect.set_all(5, 2, 90, -40);
        assert(rect.get_top() == 5);
        assert(rect.get_bottom() == 2);    
        assert(rect.get_right() == 90);
        assert(rect.get_left() == -40);
    }

    return 0;
}
