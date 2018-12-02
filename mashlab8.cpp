#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <winuser.h>

int enterCode() {
	int code;
	printf("\nWhat do you want to do: \n");
	printf("\nExit - 0 \n");
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
	printf("\nA new session file was created in e:\\\\work\n");
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

	if (strlen(mark) == 2) {
		return true;
	} else if (strlen(mark) == 1) {
		// 52 is number of int 4 in ASCII
		if ((int)mark[0] < 52) {			
			return false;
		}
		else {			
			return true;
		}
	}
	else {
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
		if ((int)line[i] == 32) {
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
	// searches after position where group number ends
	for (int i = 8; i < strlen(line); i++) {
		if ((int)line[i] == 32) {
			endName = i;
			break;
		}
	}
	return endName;
}

//searches for the 7th space
int findEndOfExamMarks(char *student) {
	int endOfExamMarks = 0, count = 0;
	for (int i = 0; i < strlen(student); i++) {
		if ((int)student[i] == 32) {
			count += 1;
		}
		if (count == 7) {
			endOfExamMarks = i;
			break;
		}
	}
	return endOfExamMarks;
}

int findExamDebtOfStudent(char *student) {
	int debt = 0;
	// the char where name begins
	int endMark = 8;
	for (int i = 0; i < 5; i++) {

		int startMark = findStartMark(student, endMark);
		endMark = findEndMark(student, startMark);
		char *mark = cutPieceFromLine(student, startMark, endMark);

		if (!(isGoodMark(mark))) {
			debt += 1;
		}
	}
	return debt;
}

int findZachDebtOfStudent(char *student) {
	int endZachyot = findEndOfExamMarks(student), debt = 0;
	for (int i = 0; i < 5; i++) {

		int startZachyot = findStartMark(student, endZachyot);
		endZachyot = findEndMark(student, startZachyot);
		char *zachyot = cutPieceFromLine(student, startZachyot, endZachyot);

		if (!(isZachyot(zachyot))) {
			debt += 1;
		}
	}
	return debt;
}

void checkStudent(char *student) {
	int debt = findExamDebtOfStudent(student);
	debt += findZachDebtOfStudent(student);
	if (debt) {
		int endName = findEndName(student);
		char *nameAndGroup = cutPieceFromLine(student, 0, endName);
		if (strlen(nameAndGroup) != 0) {
			printf("%s %i\n", nameAndGroup, debt);
		}
	}
}

void checkStudents() {
	FILE *f2;
	if (!(f2 = fopen("e:\\work\\session.txt", "r + b")))
	{
		puts("\n Файл не создан!");
		return;
	}
	char student[356];
	while (fgets(student, sizeof(student), f2) != NULL){

		checkStudent(student);
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
		//converts array into a number
		sscanf(mark, "%d", &markDigital);
		marksSum += markDigital;
	}
	double GPA = marksSum / 5.0;
	char *name = cutPieceFromLine(student, 7, findEndName(student));
	printf("\n%s GPA = %2.2lf", name, GPA);
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
	int studentsCount = 0;
	while (fgets(student, sizeof(student), f2) != NULL) {
		char *group = cutPieceFromLine(student, 0, 6);
		if (strcmp(group, group_needed)==0) {
			
			studentsCount += 1;
			groupGPA += findGPA(student);
		}
	}
	if (studentsCount != 0) {
		groupGPA /= studentsCount;
		printf("\n\nGroup GPA = %2.2lf\n", groupGPA);
	}
	else {
		printf("\nGroup wasn't found!\n");
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
			printf("\nStudents with debt:\n");
			checkStudents();
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