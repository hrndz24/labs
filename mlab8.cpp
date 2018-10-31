#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// checks if salary is lower than the one before
bool checkSalary(char salary[8], char salary_before[8]) {
	if (strlen(salary) < strlen(salary_before)) {
		return true;
	}
	else if (strlen(salary) > strlen(salary_before)) {
		return false;
	}
	else {
		for (int i = 0; i < 8; i++) {
			if ((int)salary[i] < (int)salary_before[i]) {
				return true;
			}
			else if ((int)salary[i] > (int)salary_before[i]) {
				return false;
			}
			else {
				continue;
			}
		}
	}
}

// checks if GPA is greater tha the one before
bool checkGPA(char gpa[5], char gpa_before[5]) {
	
	if (strlen(gpa) > strlen(gpa_before)) {
		return true;
	}
	else if (strlen(gpa) < strlen(gpa_before)) {
		return false;
	}
	else {
		for (int i = 0; i < 5; i++) {
			if ((int)gpa[i] > (int)gpa_before[i]) {
				return true;
			}
			else if ((int)gpa[i] < (int)gpa_before[i]) {
				return false;
			}
			else {
				continue;
			}
		}
	}
}

// checks if salary is less than 2 min salaries
bool isLessThanMin(char *salary) {
	if (strlen(salary) < 3) {
		return true;
	}
	else if (strlen(salary) == 3) {
		if ((int)salary[0] < 6) {
			return true;
		}
	}
	else {
		return false;
	}
}

// cuts out a piece from line
char* pieceOfLine(char *line, int start, int end) {	
	char *piece = (char *)malloc(sizeof(char) * 20);
	int p, l;
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

int findStartSalary(char *student) {
	int startSalary = 0;	
	for (int i = 0; i < strlen(student); i++) {

		if ((int)student[i] == 32) {
			// sets startSalary every time space is met
			// in the end its value will be after the last space
			startSalary = i + 1;
		}
	}	
	return startSalary;
}

int findEndGPA(char *student) {
	int endGPA = 0;
	for (int i = 0; i < strlen(student); i++) {

		if ((int)student[i] == 32) {
			// sets endGPA every time space is met
			// in the end its value will be the last space
			endGPA = i;
		}
	}
	return endGPA;
}

int findStartGPA(char *student) {
	int startGPA = 0;
	for (int i = 0; i < strlen(student); i++) {
		// when a dot(from GPA) is met 
		if ((int)student[i] == 46) {
			// if 3 chars away is space
			if ((int)student[i - 3] == 32) {
				// '.' is 2 chars away from the first character of GPA
				startGPA = i - 2;
				break;
			}
			else {
				// '.' is 1 char away from the first character of GPA
				startGPA = i - 1;
				break;
			}
		}
	}
	return startGPA;
}

// finds where normal salaries start
int findDivider(char **students, int length) {
	int divider;
	for (int i = 0; i < length; i++) {
		int endSalary1 = strlen(students[i]) - 2;
		char *salary = pieceOfLine(students[i], findStartSalary(students[i]), endSalary1);
		if (!(isLessThanMin(salary))) {
			divider = i;
			break;
		}
	}
	return divider;
}

// prints array sorted by GPA
void sortByGPA(char **students, int startIndex, int endIndex) {
	for (int i = startIndex; i < endIndex-1; i++) {
		for (int j = startIndex+1; j < endIndex; j++) {			
			char *GPA = pieceOfLine(students[j], findStartGPA(students[j]), findEndGPA(students[j]));
			char *GPA_before = pieceOfLine(students[j-1], findStartGPA(students[j-1]), findEndGPA(students[j-1]));
			if (checkGPA(GPA, GPA_before)) {
				// changes these two students
				char *zam = students[j];
				students[j] = students[j - 1];
				students[j - 1] = zam;
			}
		}
	}
	for (int i = startIndex; i < endIndex; i++) {
		printf("%s\n", students[i]);
	}
}

char** sortBySalary(char **students, int length) {
	for (int i = 0; i < length - 1; i++) {
		for (int j = 1; j < length; j++) {
			int endSalary = strlen(students[j]);
			int endSalary_before = strlen(students[j - 1]);
			char *salary = pieceOfLine(students[j], findStartSalary(students[j]), endSalary);
			char *salary_before = pieceOfLine(students[j - 1], findStartSalary(students[j - 1]), endSalary_before);
			// if salary is less than the one before
			if (checkSalary(salary, salary_before)) {
				// changes these two students
				char *zam = students[j];
				students[j] = students[j - 1];
				students[j - 1] = zam;
			}
		}
	}
	return students;
}

int main() {

	FILE *f2;
	if (!(f2 = fopen("e:\\work\\students.txt", "r + b")))
	{
		puts("\n Файл не создан!");
		return 0;
	}
	// just accept it
	char **students;
	students = new char*[24];
	//creating every student array
	for (int i = 0; i < 24; i++) {
		students[i] = new char[256];
	}
	//reads the file and adds every line to students array
	int k = 0;
	char line[256];
	while (fgets(students[k], 256, f2) != NULL)	{
		students[k][256] = '\0';
		k += 1;
	}
	// length of the array
	int length = k;	
	// sorts the array by salary
	students = sortBySalary(students, length);
	// where people with normal salaries start
	int divider = findDivider(students, length);
	// sorts the array before the rich by GPA
	sortByGPA(students, 0, divider);
	// sorts the array with the rich by GPA
	sortByGPA(students, divider, length);
}