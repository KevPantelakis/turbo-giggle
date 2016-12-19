#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float a, b, c, d, e, f, g;

extern void func_s(void);

static void func_c(void) {
	a = (((g+d) / (b* c)) * ((e / (f-c)))) - (b * (g + d));
}

int main(void) {
	srand48(time(0));
	b = 2;//drand48();
	c = 3;//drand48();
	d = 4;//drand48();
	e = 5;//drand48();
	f = 6;//drand48();
	g = 7;//drand48();

	printf("Le résultat devrait être le même les 3 fois :\n\n");
	func_c();
	printf("Version en langage C : %f\n", a);
	a = 123456789;
	func_s();
	printf("Version en assembleur : %f\n", a);
	func_c();
	printf("Version en langage C : %f\n", a);
	
	return 0;
}
