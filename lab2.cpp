#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define pi 3.14159265358979323846

int main() {
	double b, z, x, y;
	printf("Enter b:  ");
	scanf_s("\n %lf", &b);
	printf("Enter z:  ");
	scanf_s("\n %lf", &z);
	
	if (z < 0) {
		x = z / b;
		y = -pi + pow(cos(pow(x, 3)), 2) + pow(sin(pow(x, 2)), 3);
		printf("\n z < 0, x = z / b\n");
		printf("\n answer: y = %lf", y);		
	}
	else {
		x = sqrt(pow((z * b), 3));
		y = -pi + pow(cos(pow(x, 3)), 2) + pow(sin(pow(x, 2)), 3);
		printf("\n z >= 0, x = sqrt(pow((z * b), 3))\n");
		printf("\n answer: y = %lf", y);

	}
	_getch();
	return (0);
}