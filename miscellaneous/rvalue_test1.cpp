#include <iostream>

/**
 * The difference between `i++` and `++i` (only in C++)
 *
 * `i++` returns a rvalue
 * `++i` returns a lvalue
 *
 */

int main(int argc, const char **argv) {
	int i = 0;

	int &&j = i++;
	int &&j1 = 1;

	/// error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
	// int &&k = ++i;

	/// error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
	// int &m = i++;

	/// but you can bind const lvalue reference to any type
	const int &m1 = i++;

	int &n = ++i;

	// i++ = 100; /// error: lvalue required as left operand of assignment

	/// this is invalid in C, but valid in C++
	++i = 100;

	/// rvalue reference itself is a lvalue

	/// error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
	// int &&x = j;

	int &&x = std::move(j);

	return 0;
}
