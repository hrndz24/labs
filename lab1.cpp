#include <stdio.h>
#include <conio.h>
#include <math.h>

int main() {

	float a, up, down, z1, z2;
	printf("Enter a number:  ");
	scanf_s("%f", &a);
	up = sin(2 * a) + sin(5 * a) - sin(3 * a);
	down = cos(a) + 1 - 2 * pow(sin(2 * a), 2);
	z1 = up / down;
	z2 = 2 * sin(a);
	printf("z1=%f\n", z1);
	printf("z2=%f\n", z2);
	_getch();
	return (0);
}