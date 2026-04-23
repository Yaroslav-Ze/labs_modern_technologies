#include "../src/notification.hpp"
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>

int main() {

    // тест на прохождения условия Одновременности и выполнения следующего:
    // `мгновенное сообщение` > `обычное системное` > `уведомление от приложения`.
    NotificationPriorityQueue cher;

    cher.push(make_app(10, 10, "Sthfg", "Soob", "Nameemm sfg d"));
    cher.push(make_system(10, 10, "S", Notification::syst_n::NORM));
    cher.push(make_message(10, 10, "Name of chel", "Msg"));

    Notification n1 = cher.pop();
    assert(n1.type == Notification::MESSAGE);

    Notification n2 = cher.pop();
    assert(n2.type == Notification::SYSTEM);

    Notification n3 = cher.pop();
    assert(n3.type == Notification::APP);

    assert(cher.size() == 0);
    std::cout << "Тест 1 пройден \n";
    return 0;
}