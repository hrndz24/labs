#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#include <windows.h>
#include <winuser.h>

int enterCode() {
	int code;
	printf("What do you want to do: \n");
	printf("Exit - 0 \n");
	printf("Create new file - 1 \n");
	printf("Students with debt - 2 \n");
	printf("GPA of group - 3 \n");
	printf("Add students - 4 \n");
	printf("Enter code : ");
	scanf_s("%i", &code);
	return code;
}

//opens (creates) a new file in writing mode
void createFile() {
	FILE *f1;
	f1 = fopen("e:\\work\\new_session.txt", "w + b");
	printf("\nA new session file was created in e:\\\\work");
	fclose(f1);
}

void addStudent() {
	FILE *f3;
	f3 = fopen("e:\\work\\session.txt", "a + b");
	printf("Enter a new student info in exact format 'group_name Name exam_marks zachyot_marks':\n");
	char new_student[256];
	fgets(new_student, 256, stdin);
	fprintf(f3, "\r\n%s", new_student);
	fclose(f3);
}

char* cutPieceFromLine(char *line, int start, int end) {
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
		if ((int)mark[0] < 52) {			
			return false;
		}
		else {			
			return true;
		}
	}
	else {
		//printf("Invalid mark was found");
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
		if ((int)line[i] == 32 || (int)line[i] == 13 || (int)line[i] == 0) {
			endMark = i;
			break;
		}
		else if (line[i] == 'т') {
			endMark = i+1;
			break;
		}
	}
	return endMark;
}

int findEndName(char *line) {
	int endName = 0;
	// searches after the group number
	for (int i = 8; i < strlen(line); i++) {
		if ((int)line[i] == 32) {
			endName = i;
			break;
		}
	}
	return endName;
}

void checkStudent() {
	FILE *f2;
	if (!(f2 = fopen("e:\\work\\session.txt", "r + b")))
	{
		puts("\n Файл не создан!");
		return;
	}
	char line[356];
	while (fgets(line, sizeof(line), f2) != NULL){
		
		int debt = 0;
		// the char where name begins
		int endMark = 8;
		for (int i = 0; i < 5; i++) {
			
			int startMark = findStartMark(line, endMark);
			endMark = findEndMark(line, startMark);
			char *mark = cutPieceFromLine(line, startMark, endMark);
			
			if (!(isGoodMark(mark))) {
				debt += 1;
			}
		}
		// sets the value to be the index of space after the last mark
		int endZachyot = endMark;;
		for (int i = 0; i < 5; i++) {

			int startZachyot = findStartMark(line, endZachyot);
			endZachyot = findEndMark(line, startZachyot);
			char *zachyot = cutPieceFromLine(line, startZachyot, endZachyot);
			//printf("%i %i %s\n", startZachyot, endZachyot, zachyot);
			if (!(isZachyot(zachyot))) {
				debt += 1;
				//printf("zach No %i is '%s' debt = %i ", i, zachyot, debt);
			}
		}
		// if debt is not = 0
		if (debt) {
			int endName = findEndName(line);
			char *nameAndGroup = cutPieceFromLine(line, 0, endName);
			if (nameAndGroup != NULL) {
				printf("%s %i\n", nameAndGroup, debt);
			}
		}
	}
	fclose(f2);
}

double findGPA(char *student) {
	// the char where name begins
	int endMark = 8, marksSum = 0;
	for (int i = 0; i < 5; i++) {

		int startMark = findStartMark(student, endMark);
		endMark = findEndMark(student, startMark);
		char *mark = cutPieceFromLine(student, startMark, endMark);
		int markDigital;
		sscanf(mark, "%d", &markDigital);
		//printf("mark = %d ", markDigital);
		marksSum += markDigital;
	}
	double GPA = marksSum / 5.0;
	return GPA;
}

void calculateGroupGPA(char *group_needed) {
	FILE *f2;
	if (!(f2 = fopen("e:\\work\\session.txt", "r + b")))
	{
		puts("\n Файл не создан!");
		return;
	}
	char student[356];
	double groupGPA = 0;
	int count = 0;
	while (fgets(student, sizeof(student), f2) != NULL) {
		char *group = cutPieceFromLine(student, 0, 6);
		if (strcmp(group, group_needed)==0) {
			
			double GPA = findGPA(student);
			int endName = findEndName(student);
			char *name = cutPieceFromLine(student, 7, endName);
			count += 1;
			groupGPA += GPA;
			printf("%s GPA = %2.2lf\n", name, GPA);
			
		}
	}
	if (count != 0) {
		groupGPA /= count;
		printf("Group GPA = %2.2lf\n", groupGPA);
	}
	else {
		printf("Group wasn't found!\n");
	}
	fclose(f2);
}

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (1) {
		int code = enterCode();
		fseek(stdin, 0, SEEK_END);
		switch (code) {
		case 0:
			return 0;
		case 1:
			createFile();
			break;
		case 4:
			addStudent();
			break;
		case 2:
			printf("Students with debt:\n");
			checkStudent();
			break;
		case 3:
			char group_needed[7];
			printf("Enter group number: ");
			fgets(group_needed, 7, stdin);
			group_needed[6] = '\0';
			calculateGroupGPA(group_needed);
		default:
			continue;
		}
		
	}
	return 0;
}