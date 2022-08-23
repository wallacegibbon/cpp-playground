#include <iostream>
#include <cstring>

int main(int argc, const char **argv) {

	union { char str[8]; long long num; };

	/// if you give the union a name, like:
	///
	/// >>	union blah { char str[8]; long long num; };
	///
	/// you will get an error complaining that `str` and `num` were not
	/// declared in this scope.
	///
	/// I don't think using anonymous to define variable is a good idea.
	///

	strcpy(str, "hello");

	for (char c : str)
		std::cout << std::hex << static_cast<int>(c);

	std::cout << '(' << str << ')' << std::endl;

	std::cout << std::hex << num << std::endl;

	return 0;
}

