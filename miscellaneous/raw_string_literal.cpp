#include <iostream>

int main(int argc, const char **argv) {
    /// R"(....)"
    std::cout << R"(hello, this is a "raw string literal".)" << std::endl;

    /// "\" will not escape special characters inside raw string literal
    std::cout << R"(hello\t\t\nworld".)" << std::endl;

    /// R"d-char-sequences(raw-char-sequences)d-char-sequences" is another useful syntax
    std::cout << R"blah(hello, this is another "raw string literal".)blah" << std::endl;

    /// you can cantain )" in this syntax
    std::cout << R"blah(there can be )" now )blah" << std::endl;

    return 0;
}