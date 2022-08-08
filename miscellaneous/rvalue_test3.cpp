#include <iostream>

template <typename T>
void g(T &a) {
	std::cout << "T&" << std::endl;
}

template <typename T>
void g(T &&a) {
	std::cout << "T&&" << std::endl;
}

template <typename T>
void f(T &&a) {
	// g(a); /// written as this, "a" will be T& instead of T&&
	g(std::forward<T>(a));

	// g(std::move<T>(a)); /// error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
}

int main(int argc, const char **argv) {
	int a;
	f(0);
	f(a);
	return 0;
}
