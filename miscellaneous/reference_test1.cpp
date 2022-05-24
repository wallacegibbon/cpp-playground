#include <iostream>

int main(int argc, const char **argv) {
    int i = 0;

    int &&a = std::move(i);
    int &&b = static_cast<int &&>(i); /// basicly same as std::move
    int &c = i;

    /// the address of these variables are the same:
    std::cout << "&i=" << &i << ", &a=" << &a << ", &b=" << &b << ", &c=" << &c << std::endl;

    return 0;
}