#include <stdio.h>
#include <conio.h>
#include <math.h>
#define pi 3.14159265358979323846

int main() {
	double s, x, y, z;
	int  k, n, f;
	printf("Enter integer n:  ");
	scanf_s("%i", &n);
	printf("Enter x:  ");
	scanf_s("%lf", &x);
	f = 1;
	s = 0;
	for (k = 0; k < n; k++) {
		if (k == 0) {
			f = 1;
		}
		else {
			f *= k;
		}
		s += ((cos(k*pi / 4)) / f)*pow(x, k);

	}
	y = exp(x*cos(pi / 4))*cos(x*sin(pi / 4));
	printf("s= %lf\n", s);
	printf("y= %lf\n", y);
	z = fabs(y - s);
	printf("|y-s|= %lf\n", z);
	return(0);
}