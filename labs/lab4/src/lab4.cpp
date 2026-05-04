#include <utility>
#include <cassert>
#include <iostream>
#include <fstream>
#include "point.hpp"
/*#include "string.hpp"
#include "matrix.hpp"
#include "workerdb.hpp"
#include "notification.hpp"
#include "base.hpp"
#include "boolarray.hpp" */

int main() {
    List l;
    l.push_back(1, 1, 4);
    l.push_back(0,0, 1);
    l.push_front(0, 0, 58.5);
    l.push_front(9, 5, 4);
    std::cout << "Состояние до сортировки: \n"<< l << "\n";
    l.sort_rost();
    std::cout << "Состояние после! сортировки: \n"<< l << "\n";

    l.remove_all(Circle(1, 1, 4));
    std::cout << "Состояние после удаления: \n"<< l << "\n";

    v_file(l, "sth.txt");

    l.chtenie_without_clear("st.txt");
    l.chtenie_without_clear("sth.txt");

    std::cout << "\nСостояние после УСПЕШНОГО чтения: \n"<< l << "\n";

    l.sort_rost();
    std::cout << "Состояние после! сортировки: \n"<< l << "\n";

    /*{
        List l1;
        l1.push_back(Circle(0, 0, 1));
        l1.push_back(Circle(9, 5, 4));
        l1.push_back(Circle(0, 0, 58.5));

        v_file(l1, "sth.txt");

        List l2;
        l2.chtenie_without_clear("sth.txt");
        l2.chtenie_without_clear("sth.txt");

        std::cout << "Оригинал:\n" << l1;
        std::cout << "Стало:\n" << l2;
        std::cout << "\n" << l2.size();
    }*/

}