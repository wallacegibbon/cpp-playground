#include <iostream>

template <int N>
struct binary {
	static constexpr int value = binary<N / 10>::value << 1 | N % 10;
};

/// specialization when N == 0. (the end of the recursion)
template <>
struct binary<0> {
	static constexpr int value = 0;
};

/// binary<101>::value
/// binary<10>::value << 1 | 1
/// (binary<1>::value << 1 | 0) << 1 | 1
/// (((binary<0>::value << 1 | 1) << 1) | 0) << 1 | 1
/// (((0 << 1 | 1) << 1) | 0) << 1 | 1
/// ((1 << 1) | 0) << 1 | 1
/// 10 << 1 | 1
/// 101

/// binary<101>::value
/// binary<10>::value                      << 1 | 1
/// (binary<1>::value            << 1 | 0) << 1 | 1
/// ((binary<0>::value << 1 | 1) << 1 | 0) << 1 | 1
/// ((0                << 1 | 1) << 1 | 0) << 1 | 1
/// (1                           << 1 | 0) << 1 | 1
/// 10                                     << 1 | 1
/// 101

int main(int argc, char **argv) {
	std::cout << binary<101>::value << std::endl;
	std::cout << binary<1011>::value << std::endl;
	return 0;
}
