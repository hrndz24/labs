#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "string.h"

int main() {
	int length, i, k;
	char s[256], newS[256], a;
	printf("Enter a string: ");
	fgets(s, 256, stdin);
	length = strlen(s);
	k = 0;
	//33 is the code for ! in ASCII Table
	for (i = 0; i < length; i++) {
		a = s[i];
		if (int(s[i]) == 33) {
			if (k == 0) {
				k = 1;
				a = s[i];
			}
			else {
				a = '$';
				k = 0;
			}
		}
		newS[i] = a;		
	}
	newS[length] = '\0';
	printf("\n%s", newS);
	_getch();
	return(0);
} 