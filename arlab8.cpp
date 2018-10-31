#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

char* pieceOfLine(char *line, int start, int end) {
	char *piece = (char *)malloc(sizeof(char) * 30);
	int p, l;
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

bool checkYear(char* year_from, char* year) {
	for (int i = 0; i < 4; i++) {
		if ((int)year_from[i] < (int)year[i]) {
			return true;
		}
		else if ((int)year_from[i] > (int)year[i]) {
			return false;
		}
		else {
			continue;
		}
	}
}

void checkClient(FILE* f2, char* fam) {
	char client[256];
	while (fgets(client, sizeof(client), f2) != NULL)
	{
		client[strlen(client) - 2] = '\0';
		int startSurname = 0, endSurname;
		for (int i = 0; i < strlen(client); i++) {
			if ((int)client[i] == 32) {
				endSurname = i;
				break;
			}
		}
		int startNumber=endSurname+6, endNumber = strlen(client);
		char *number = pieceOfLine(client, startNumber, endNumber);
		char *surname = pieceOfLine(client, startSurname, endSurname);
		if (strcmp(fam, surname) == 0)
			printf("%s %s\n", surname, number);

	}
}

void findNumberOfPhones(FILE* f2, char* year_from) {
	char client[256];
	int count = 0;
	while (fgets(client, sizeof(client), f2) != NULL)
	{
		client[strlen(client) - 2] = '\0';
		int startYear;
		for (int i = 0; i < strlen(client); i++) {
			if ((int)client[i] == 32) {
				startYear = i + 1;
				break;
			}
		}
		int endYear = startYear + 4;

		char *year = pieceOfLine(client, startYear, endYear);
		
		if (checkYear(year_from, year)) {
			count += 1;
		}
	}
	printf("%i", count);
}

int main() {

	FILE *f2;
	if (!(f2 = fopen("e:\\work\\clients.txt", "r + b")))
	{
		puts("\n Файл не создан!");
		return 0;
	}

	int code;
	printf("Choose an action:\nFind a client - 1\nFind telephones - 2\n");
	scanf_s("%i", &code);
	fseek(stdin, 0, SEEK_END);
	switch (code) {
	case 1:
		char fam[30];
		printf("Enter client's surname: ");
		fgets(fam, 30, stdin);
		fam[strlen(fam) - 1] = '\0';
		checkClient(f2, fam);
		break;
	case 2:
		char year[5];
		printf("Enter year: ");
		fgets(year, 5, stdin);
		year[strlen(year)] = '\0';
		findNumberOfPhones(f2, year);
		break;
	}	
	return 0;
}