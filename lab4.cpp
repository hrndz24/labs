 #include <stdio.h>
#include <conio.h>
#include <math.h>
#define pi 3.14159265358979323846

int factorial(int k) {
	int f;
	if (k == 0 || k == 1)
		return 1;
	f = factorial(k - 1)*k;
	return f;
}

double sFunction(double x, int n) {
	double s = 0;
	int f;
	for (int k = 0; k < n; k++) {
		f = factorial(k);
		s += ((cos(k*pi / 4)) / f)*pow(x, k);
	}
	return s;
}

double yFunction(double x) {
	double y = exp(x*cos(pi / 4))*cos(x*sin(pi / 4));
	return y;
}

int main() {
	double s, x, y, z;
	int n;
	printf("Enter integer n:  ");
	scanf_s("%i", &n);
	printf("Enter x:  ");
	scanf_s("%lf", &x);	
	s = sFunction(x, n);
	y = yFunction(x);
	z = fabs(y - s);
	printf("s= %lf\n", s);
	printf("y= %lf\n", y);	
	printf("|y-s|= %lf\n", z);
	_getch();
	return(0);
}