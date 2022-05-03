#include <iostream>

void f1(int &&a) {
    a += 1;
    std::cout << "a is now " << a << std::endl;
}

int main(int argc, const char **argv) {
    f1(2);
    return 0;
}