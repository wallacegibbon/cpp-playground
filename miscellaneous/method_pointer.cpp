#include <iostream>

class AnyClass {
public:
	void show1();
	void show2() const;
};

void AnyClass::show1() {
	std::cout << "this is AnyClass::show1" << std::endl;
}

void AnyClass::show2() const {
	std::cout << "this is AnyClass::show2 const" << std::endl;
}

int main(int argc, const char **argv) {
	AnyClass a;
	a.show1();
	a.show2();
	AnyClass *pa = &a;

	std::cout << "****************************" << std::endl;
	void (AnyClass::*p1_show1)() = &AnyClass::show1;
	void (AnyClass::*p1_show2)() const = &AnyClass::show2;

	(a.*p1_show1)();
	(a.*p1_show2)();
	(pa->*p1_show1)();
	(pa->*p1_show2)();

	std::cout << "****************************" << std::endl;
	using a_method_t = void (AnyClass::*)() const;
	a_method_t p2_show2 = &AnyClass::show2;

	(a.*p2_show2)();
	(pa->*p2_show2)();

	return 0;
}
