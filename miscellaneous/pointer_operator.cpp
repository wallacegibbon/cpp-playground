#include <iostream>

class MyDataClass {
public:
    MyDataClass(std::string name_, int age_) : name(name_), age(age_) {}
    std::string info() { return name + std::to_string(age); }

private:
    std::string name;
    int age;
};

template <typename T>
class MyPointer {
public:
    MyPointer(T *arg) { p = arg; }
    T *operator->() { return p; }

private:
    T *p;
};

int main(int argc, const char **argv) {
    MyDataClass data("wallace", 30);

    MyPointer<MyDataClass> p1(&data);
    /// `p1->info()` is just like `(p1->operator->())->info()`
    std::cout << p1->info() << std::endl;

    /// this doesn't work
    // MyPointer<MyPointer<MyDataClass>> p2(&p1);
    // std::cout << p2->info() << std::endl;

    return 0;
}