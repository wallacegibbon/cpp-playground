#include <iostream>

struct MyObject {
	const char *information;
	int anything_else;
};

void reference_version(const MyObject &obj) {
	std::cout << "obj(" << &obj << ") " << obj.information << std::endl;
}

void pointer_version(MyObject *obj) {
	std::cout << "obj(" << obj << ") " << obj->information << std::endl;
}

int main(int argc, const char **argv) {
	/// for pointer, you need to store the temporary data in a variable

	/// this will cause compilation error: taking address of rvalue
	//pointer_version(&MyObject{"hello, pointer", 1});

	MyObject myvar{"hello, pointer", 1};
	pointer_version(&myvar);

	/// but for reference, you can simply:
	reference_version(MyObject{"hello, reference", 1});

	return 0;
}

