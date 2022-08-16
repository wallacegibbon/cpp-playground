#include <stdio.h>

struct Blah { int a; char *b; };

Blah x = {101, "hello"};

void a() {
	printf("hello, this is a, x.a: %d, x.b: %s (%x)\n", x.a, x.b, x.b);
}

extern void b();

int main(int argc, const char **argv) {
	a();
	b();
	return 0;
}

