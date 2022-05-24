#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

/// argument "element" is const (left-value) reference to support both left-value and right-value
template <typename T>
int find_index(std::vector<T> container, const T &element) {
    int index = std::find(container.begin(), container.end(), element) - container.begin();
    if (index == container.size()) {
        return -1;
    } else {
        return index;
    }
}

void find_index_test1() {
    std::vector<int> tmp = {10, 17, 23, 15, 24, 32, 9, 14, 5};

    std::cout << __FUNCTION__ << ", right-value test" << std::endl;
    std::cout << find_index(tmp, 23) << std::endl;
    std::cout << find_index(tmp, 99) << std::endl;

    std::cout << __FUNCTION__ << ", left-value test" << std::endl;
    int i = 32;
    std::cout << find_index(tmp, i) << std::endl;
}

void find_index_test2() {
    std::vector<std::tuple<int, int>> tmp{std::make_tuple(1, 2), std::make_tuple(3, 4)};

    std::cout << __FUNCTION__ << ", right-value test" << std::endl;
    std::cout << find_index(tmp, std::make_tuple(3, 4)) << std::endl;
    std::cout << find_index(tmp, std::make_tuple(3, 5)) << std::endl;

    std::cout << __FUNCTION__ << ", left-value test" << std::endl;
    std::tuple<int, int> i(3, 4);
    std::cout << find_index(tmp, i) << std::endl;
}

int main(int argc, const char **argv) {
    find_index_test1();
    find_index_test2();
    return 0;
}