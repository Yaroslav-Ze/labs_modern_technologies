#include "../src/notification.hpp"
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>

int main() {

    // тест на первостепенность добавления в очередь
    //
    NotificationPriorityQueue cher;

    cher.push(make_system(0, 0, "s1", Notification::syst_n::NORM));
    cher.push(make_system(0, 0, "s2", Notification::syst_n::NORM));
    cher.push(make_system(0, 0, "s3", Notification::syst_n::NORM));


    Notification n1 = cher.pop();
    assert(n1.data.system->prishlo_soob == "s1");

    Notification n2 = cher.pop();
    assert(n2.data.system->prishlo_soob == "s2");

    Notification n3 = cher.pop();
    assert(n3.data.system->prishlo_soob == "s3");



    assert(cher.size() == 0);

    std::cout << "Тест 4 пройден \n";

    return 0;
}