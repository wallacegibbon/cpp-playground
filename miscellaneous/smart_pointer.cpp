#include <iostream>

template <typename T>
class MySmartPointer {
public:
    MySmartPointer(T *ptr_ = nullptr) : ptr(ptr_) {}
    virtual ~MySmartPointer();

    MySmartPointer(const MySmartPointer &ptr) = delete;
    MySmartPointer(MySmartPointer &&ptr) noexcept;

    MySmartPointer &operator=(const MySmartPointer &ptr) = delete;
    MySmartPointer &operator=(MySmartPointer &&ptr) noexcept;

    T operator*() const { return *ptr; }
    T *operator->() const { return ptr; }

    T *get_ptr() const { return ptr; }
    void set_ptr(T *newptr) { ptr = newptr; }

private:
    T *ptr;
};

template <typename T>
MySmartPointer<T>::~MySmartPointer() {
    if (ptr != nullptr) {
        delete ptr;
        ptr = nullptr;
    }
}

template <typename T>
MySmartPointer<T>::MySmartPointer(MySmartPointer &&ptr_) noexcept {
    ptr = ptr_.get_ptr();
    ptr_.set_ptr(nullptr);
}

template <typename T>
MySmartPointer<T> &MySmartPointer<T>::operator=(MySmartPointer &&ptr_) noexcept {
    if (this == &ptr_) {
        return *this;
    }
    delete ptr;
    ptr = ptr_.get_ptr();
    ptr_.set_ptr(nullptr);
    return *this;
}

class MyDataClass {
public:
    MyDataClass(std::string name_, int age_) : name(name_), age(age_) {}
    virtual ~MyDataClass() { std::cout << info() << " is destroyed." << std::endl; }
    std::string info() { return name + std::to_string(age); }

private:
    std::string name;
    int age;
};

int main(int argc, const char **argv) {
    /*
     * if the object is not allocated with `new`, there will be runtime error like
     * (double free or corruption (out))
     */
    // MyDataClass data("wallace", 30);
    // MySmartPointer<MyDataClass> p1(&data);

    MyDataClass *data = new MyDataClass("wallace", 30);
    MySmartPointer<MyDataClass> p1(data);

    std::cout << p1->info() << std::endl;
    std::cout << "p1 is now " << p1.get_ptr() << std::endl;

    // MySmartPointer<MyDataClass> p2(p1);
    //>>  error: use of deleted function ‘MySmartPointer<T>::MySmartPointer(const MySmartPointer<T>&)

    /* std::move convert a value to an rvalue */
    MySmartPointer<MyDataClass> p2(std::move(p1));

    std::cout << "p1 is now " << p1.get_ptr() << std::endl;
    std::cout << "p2 is now " << p2.get_ptr() << std::endl;

    std::cout << p2->info() << std::endl;

    return 0;
}