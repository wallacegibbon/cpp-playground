#include <stdio.h>

struct Blah { int a; int b; int c; };

extern Blah x;

Blah y = {202, 303, 404};

void b() {
	printf("hello, this is b, x.a: %d, x.b: %x, x.c: %x\n", x.a, x.b, x.c);
	printf("hello, this is b, y.a: %d, y.b: %d, y.c: %d\n", y.a, y.b, y.c);
}

