#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int findIndex(int *arr, int n) {
	int index = -1;
	for (int i = 0; i < n; i++) {
		if (arr[i] == 0) {
			index = i;
			break;
		}
	}
	return index;
}

int sum(int index, int *arr, int n) {
	int s = 0;
	if (index != -1) {
		for (int i = index; i < n; i++) {
			s += fabs(arr[i]);
		}
	}
	else {
		printf("no zero found\n");
	}
	return s;
}

int main() {
	int n, i, s, index;
	printf("Enter integer n:  ");
	scanf_s("%i", &n);
	int *a = new int[n];
	for (i = 0; i < n; i++) {
		scanf_s("%i", &a[i]);
	}	
	index = findIndex(a, n);	
	s = sum(index, a, n);
	printf("s = %i", s);
	_getch();
	return(0);
}