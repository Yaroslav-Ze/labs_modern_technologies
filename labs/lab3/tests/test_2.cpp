#include "../src/notification.hpp"
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>

int main() {

    // тест на приоритет срочности сообщения
    //
    NotificationPriorityQueue cher;

    cher.push(make_system(0, 30, "S1", Notification::syst_n::VAZHNO));
    cher.push(make_system(0, 30, "s2", Notification::syst_n::VAZHNO));
    cher.push(make_message(0, 1, "Name of chel", "Msg"));
    cher.push(make_system(0, 15, "s2", Notification::syst_n::VAZHNO));

    Notification n1 = cher.pop();
    assert(n1.minute == 15);

    Notification n2 = cher.pop();
    assert(n2.data.system->prishlo_soob == "S1");

    Notification n3 = cher.pop();
    assert(n3.data.system->prishlo_soob == "s2");

    Notification n4 = cher.pop();
    assert(n4.minute == 1);

    assert(cher.size() == 0);

    std::cout << "Тест 2 пройден \n";

    return 0;
}