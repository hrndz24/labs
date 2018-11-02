#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

char* pieceOfLine(char *line, int start, int end) {
	char *piece = (char *)malloc(sizeof(char) * 20);
	int p, l;
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

bool isGoodMark(char mark[2]) {
	// if the mark has two digits
	if (strlen(mark) == 2) {
		return true;
	}
	// if the mark has one digit
	else if (strlen(mark) == 1) {
		// 53 is number of int 5 in ASCII
		if ((int)mark[0] < 53) {
			
			return false;
		}
		else {
			
			return true;
		}
	}
	else {
		printf("Invalid mark was found");
		return false;
	}
}

bool isZachyot(char *zachyot) {
	if (zachyot[0] == 'з') {
		return true;
	}
	else {
		return false;
	}
}

// sets startMark to be the index after the first space after searchFrom position
int findStartMark(char *line, int searchFrom) {
	int startMark = 0;
	for (int i = searchFrom; i < strlen(line); i++) {
		if ((int)line[i] == 32) {
			startMark = i + 1;
			break;
		}
	}
	return startMark;
}

// sets endMark to be the first index of space after searchFrom position
int findEndMark(char *line, int searchFrom) {
	int endMark = 0;
	for (int i = searchFrom; i < strlen(line); i++) {
		if ((int)line[i] == 32 || (int)line[i] == 13) {
			endMark = i;
			break;
		}
	}
	return endMark;
}

int findEndName(char *line) {
	int endName = 0;
	for (int i = 8; i < strlen(line); i++) {
		if ((int)line[i] == 32) {
			endName = i;
			break;
		}
	}
	return endName;
}

void checkStudent(FILE *f2) {
	char line[356];
	while (fgets(line, sizeof(line), f2) != NULL){
		
		int debt = 0;
		// the char where name begins
		int endMark = 8;
		for (int i = 0; i < 5; i++) {
			
			int startMark = findStartMark(line, endMark);
			endMark = findEndMark(line, startMark);
			char *mark = pieceOfLine(line, startMark, endMark);
			
			if (!(isGoodMark(mark))) {
				debt += 1;
			}
		}
		// sets the value to be the index of space after the last mark
		int endZachyot = endMark;;
		for (int i = 0; i < 5; i++) {

			int startZachyot = findStartMark(line, endZachyot);
			endZachyot = findEndMark(line, startZachyot);
			char *zachyot = pieceOfLine(line, startZachyot, endZachyot);
			
			if (!(isZachyot(zachyot))) {
				debt += 1;
			}
		}
		// if debt is not = 0
		if (debt) {
			int endName = findEndName(line);
			char *nameAndGroup = pieceOfLine(line, 0, endName);
			printf("%s %i\n", nameAndGroup, debt);
		}
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	FILE *f2;
	if (!(f2 = fopen("e:\\work\\session.txt", "r + b")))
	{
		puts("\n Файл не создан!");
		return 0;
	}
	checkStudent(f2);
	return 0;
}