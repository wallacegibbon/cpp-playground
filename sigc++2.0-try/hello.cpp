// g++ compile options:
//  -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -lsigc-2.0

#include <iostream>
#include <sigc++/sigc++.h>

class SimpleClass1 {
public:
    void fn1(int i) { std::cout << "this is from SimpleClass1: " << i << std::endl; }
};

class SimpleClass2 {
public:
    void fn2(int i) { std::cout << "this is from SimpleClass2: " << i << std::endl; }
};

void signal_class_test() {
    sigc::signal<void, int> my_signal;
    SimpleClass1 c1;
    SimpleClass2 c2;
    my_signal.connect(sigc::mem_fun(c1, &SimpleClass1::fn1));
    my_signal.connect(sigc::mem_fun(c2, &SimpleClass2::fn2));
    my_signal.emit(100);
}

void simple_function(const std::string &str) { std::cout << str << std::endl; }

void signal_function_test() {
    sigc::signal<void, const std::string &> my_signal;
    my_signal.connect(sigc::ptr_fun(&simple_function));
    my_signal.emit("hello");
}

int main(int argc, const char **argv) {
    signal_class_test();
    signal_function_test();
    return 0;
}