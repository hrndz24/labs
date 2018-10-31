#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int **solution(int **arr, int n, int m) {
	int i, j, max, line, column, zam;
	int *zamLine;
	//looking for the greatest number
	max = arr[0][0];
	line = 0;
	column = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
				line = i;
				column = j;
			}
		}
	}
	//replacing the first number of the column
	//with the max and vice versa
	zam = arr[line][0];
	arr[line][0] = max;
	arr[line][column] = zam;
	//replacing the first line with 
	//the one containing max and vice versa
	zamLine = arr[0];
	arr[0] = arr[line];
	arr[line] = zamLine;
	return arr;
}

int main() {
	int n, i, j, m;
	printf("Enter integer n:  ");
	scanf_s("%i", &n);
	printf("Enter integer m:  ");
	scanf_s("%i", &m);
	//creating an array of lines
	int **a;
	a = new int*[n];
	//creating every line array
	for (i = 0; i < n; i++) {
		a[i] = new int[m];
	}
	//filing in the array
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			scanf_s("%i", &a[i][j]);
		}
	} 
	printf("\n");
	int **solvedArray = solution(a, n, m);
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf("%i ", solvedArray[i][j]);
		}
		printf("\n");
	} 
	_getch();
	return(0);
}