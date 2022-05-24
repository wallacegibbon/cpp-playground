#include <initializer_list>
#include <iostream>
#include <vector>

/// The programmer says {1, 2, 3, 4}, and the compiler creates an object of type initializer_list<int> out of it,
/// containing the same sequence of elements in it.
///
/// This contract is a requirement imposed by the language specification on thecompiler implementation.

void mytest1(std::initializer_list<int> const &items) {
    for (int i : items) {
        std::cout << i << std::endl;
    }
}

class Blah {
public:
    /// both of the two constructors supports right-value argument
    // Blah(std::initializer_list<int> &&values);
    Blah(const std::initializer_list<int> &values);

    Blah &operator=(Blah rhv) = delete;
    Blah &operator=(Blah &rhv) = delete;
    Blah &operator=(Blah &&rhv) = delete;

    void display();

private:
    std::vector<int> values_;
};

// Blah::Blah(std::initializer_list<int> &&values) {
Blah::Blah(const std::initializer_list<int> &values) {
    for (int i : values) {
        std::cout << "pushing " << i << " into Blah..." << std::endl;
        values_.push_back(i);
    }
}

void Blah::display() {
    for (int i : values_) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
}

int main(int argc, const char **argv) {
    mytest1({1, 2, 3, 4, 5, 6});
    // mytest1{1, 2, 3, 4, 5, 6}; // this is an error. this syntax is for Class constructors.

    Blah tmp1{10, 11, 12, 13}; /// same as : Blah tmp1({10, 11, 12, 13});
    tmp1.display();

    /// this is same as the previous initialization, it does NOT call the copy constructor
    Blah tmp2 = {10, 11, 12, 13};
    tmp2.display();

    /// the following example shows that the previous (Blah tmp2 = {...}) did NOT call the copy constructor

    // Blah tmp3 = tmp2; // error: use of deleted function ‘Blah::Blah(const Blah&)’

    /// just like those modern languages, you can create objects in the new way shown below
    Blah{20, 30, 40}.display();

    /// also, this is OK
    (new Blah{20, 30, 40})->display();

    return 0;
}