#pragma once

#include <QObject>
#include <iostream>

class MyClassA : public QObject {
    Q_OBJECT

public:
    MyClassA();
    void slot1() { std::cout << "this is message from slot1" << std::endl; }
    void slot2() { std::cout << "this is message from slot2" << std::endl; }
    void slot3() { std::cout << "this is message from slot3" << std::endl; }
    void test();

signals:
    void signal1();
};