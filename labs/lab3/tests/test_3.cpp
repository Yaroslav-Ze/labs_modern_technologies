#include "../src/notification.hpp"
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>

int main() {

    // тест на прохождения условия времени. Кто раньше тот важнее.
    
    NotificationPriorityQueue cher;

    cher.push(make_message(3, 0, "Name of chel", "Msg"));
    cher.push(make_message(1, 0, "Name of chel", "Msg"));
    cher.push(make_message(2, 0, "Name of chel", "Msg"));

    Notification n1 = cher.pop();
    assert(n1.hour == 1);

    Notification n2 = cher.pop();
    assert(n2.hour == 2);

    Notification n3 = cher.pop();
    assert(n3.hour == 3);

    assert(cher.size() == 0);
    std::cout << "Тест 3 пройден \n";
    return 0;
}