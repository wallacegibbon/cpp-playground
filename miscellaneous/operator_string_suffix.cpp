#include <iostream>

std::string operator""_my_converter(const char *str, std::size_t len) {
	return std::string(str).replace(len - 2, len, "~~~");
}

int main(int argc, const char **argv) {
	std::string mystr = "hello, world~"_my_converter;
	std::cout << mystr << std::endl;
}
