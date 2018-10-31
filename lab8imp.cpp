#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// asks user what action they want to implement
int enterCode() {
	int code;
	printf("\nWhat do you want to do:\n");
	printf("Create schedule - 1\n");
	printf("Search routes - 2\n");
	printf("Add routes - 3\n");
	printf("Exit - 0\n");
	printf("Enter: ");
	scanf_s("%i", &code);
	return code;
}

//opens (creates) a new file in writing mode
void createSchedule() {
	FILE *f1;
	f1 = fopen("e:\\work\\new_schedule.txt", "w + b");
	printf("\nA new schedule was created in e:\\\\work");
	fclose(f1);
}

// opens file in adding mode and allows user add a new route
void addRoutes() {
	FILE *f3;
	f3 = fopen("e:\\work\\schedule.txt", "a + b");
	printf("Enter a new route in exact format '#### type Destination hh.mm hh.mm' :\n");
	// route a user wants to add
	char new_line[256];
	fgets(new_line, 256, stdin);
	fprintf(f3, "\r\n%s", new_line);
	fclose(f3);
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

// compares destination user needs with the line's one
bool checkDestination(char destination_needed[20], char destination[20]) {
	if (strcmp(destination_needed, destination) == 0) {
		return true;
	}
	else {
		return false;
	}
}

// checks if time user needs is later than bus' arrival time
bool checkTime(char time_needed[6], char time[6]) {
	for (int i = 0; i < 5; i++) {
		if ((int)time_needed[i] > (int)time[i]) {
			return true;
		}
		else if ((int)time_needed[i] < (int)time[i]) {
			return false;
		}
		else {
			continue;
		}
	}
}

// finds the index of startTime in the line
int findStartTime(char *line) {
	int startTime=0;
	for (int i = 0; i < strlen(line); i++) {

		if ((int)line[i] == 32) {			
			// sets startTime every time space is met
			// in the end its value will be after the last space
			startTime = i+1;
		}
	}
	return startTime;
}

// finds the index of startDestination in the line
int findStartDestination(char *line) {
	int count = 0, startDestination=0;
	for (int i = 0; i < strlen(line); i++) {
		if ((int)line[i] == 32) {
			count += 1;
		}
		if (count == 2) {
			startDestination = i+1;
			break;
		}
	}
	return startDestination;
}

// finds the index of endDestination in the line
int findEndDestination(char *line) {
	int endDestination = 0;
	for (int i = 0; i < strlen(line); i++) {
		// when a dot(from departure time in the end) is met sets the end of destination
		if ((int)line[i] == 46) {
			// '.' is 3 chars away from the last character of destination
			endDestination = i - 3;
			break;
		}
	}
	return endDestination;
}

// reads line by line from a file and checks routes
void checkLine(FILE* f2, char* destination_needed, char* time_needed) {
	char line[256];
	while (fgets(line, sizeof(line), f2) != NULL)
	{
		line[strlen(line)] = '\0';
		int endTime = strlen(line) - 2;		
		int startTime=findStartTime(line);
		int startDestination=findStartDestination(line);
		int endDestination=findEndDestination(line);

		char *destination = pieceOfLine(line, startDestination, endDestination);
		char *time = pieceOfLine(line, startTime, endTime);
		// if time and destination are suitable prints the line
		if (checkDestination(destination_needed, destination) && checkTime(time_needed, time)) {
			printf("\n%s", line);
		}
	}
}

int main() {

	while (1) {
		int code = enterCode();
		fseek(stdin, 0, SEEK_END);
		switch (code) {
		case 0:
			// exits the main() function => exits the program
			return 0;
		case 1:			
			createSchedule();
			break;
		case 2:
			// open file in reading mode		
			FILE *f2;
			if (!(f2 = fopen("e:\\work\\schedule.txt", "r + b")))
			{
				puts("\n Файл не создан!");
				return 0;
			}
			
			char time_needed[7], destination_needed[20];
			// just a placeholder, so that time_needed doesn't keep old values
			time_needed[2] = 'a';

			// asks user for time and destination they need
			// if they enter time in wrong format asks to enter again
			// if the 3rd element of time array is not '.' time was entered incorrectly
			while ((int)time_needed[2] != 46) {
				printf("\nEnter time in exact format hh.mm and destination: ");
				fgets(time_needed, 7, stdin);
				fgets(destination_needed, 20, stdin);
				destination_needed[strlen(destination_needed) - 1] = '\0';
				time_needed[strlen(time_needed) - 1] = '\0';
			}

			printf("\nAvailable routes: ");
			checkLine(f2, destination_needed, time_needed);
			fclose(f2);
			break;
		case 3:
			addRoutes();
			break;
		}
	}
}