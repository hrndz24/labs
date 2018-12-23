#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/*
	32 это пробел в ASCII
	13 - перенос каретки или переход на новую строку
	любая count считает пробелы
*/

char* cutPieceFromLine(char *line, int start, int end) {
	// выделяет память под массив в 20 символов 
	char *piece = (char *)malloc(sizeof(char) * 20);
	int p, l;
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

int findStartFactory(char *worker) {
	int count = 0, startFactory = 0;
	for (int i = 0; i < strlen(worker); i++) {
		if ((int)worker[i] == 32) {
			count += 1;
		}
		if (count == 1) {
			startFactory = i + 1;
			break;
		}
	}
	return startFactory;
}

bool checkFactory(char *worker, char *factory) {
	int startFactory = findStartFactory(worker);
	int endFactory = startFactory + 4;
	char *workersFactory = cutPieceFromLine(worker, startFactory, endFactory);
	if (strcmp(workersFactory, factory) == 0) {
		return true;
	}
	else {
		return false;
	}
}

int findStartA(char *worker) {
	int count = 0, startA = 0;
	for (int i = 0; i < strlen(worker); i++) {
		if ((int)worker[i] == 32) {
			count += 1;
		}
		if (count == 2) {
			startA = i + 1;
			break;
		}
	}
	return startA;
}

int findEndA(char *worker) {
	int count = 0, endA = 0;
	for (int i = 0; i < strlen(worker); i++) {
		if ((int)worker[i] == 32) {
			count += 1;
		}
		if (count == 3) {
			endA = i;
			break;
		}
	}
	return endA;
}

int getAnumber(char *worker) {
	int startA = findStartA(worker);
	int endA = findEndA(worker);
	char *A = cutPieceFromLine(worker, startA, endA);
	int ADigital;
	//converts array into a number
	sscanf(A, "%d", &ADigital);
	return ADigital;
}

int findEndB(char *worker) {
	int count = 0, endB = 0;
	for (int i = 0; i < strlen(worker); i++) {
		if ((int)worker[i] == 32) {
			count += 1;
		}
		if (count == 4) {
			endB = i;
			break;
		}
	}
	return endB;
}

int getBnumber(char *worker) {
	int startB = findEndA(worker)+1;
	int endB = findEndB(worker);
	char *B = cutPieceFromLine(worker, startB, endB);
	int BDigital;
	//converts array into a number
	sscanf(B, "%d", &BDigital);
	return BDigital;
}

int getCnumber(char *worker) {
	int startC = findEndB(worker)+1;
	int endC = strlen(worker);
	char *C = cutPieceFromLine(worker, startC, endC);
	int CDigital;
	//converts array into a number
	sscanf(C, "%d", &CDigital);
	return CDigital;
}

int calculateWorkerSalary(char *worker, int Sa, int Sb, int Sc) {
	int startSurname = 0;
	int endSurname = findStartFactory(worker) - 1;
	char *surname = cutPieceFromLine(worker, 0, endSurname);

	int salary = 0;
	salary += getAnumber(worker)*Sa;
	salary += getBnumber(worker)*Sb;
	salary += getCnumber(worker)*Sc;
	printf("\n %s: %i", surname, salary);
	return salary;
}

void calculateDetailsNumber(char *factory, FILE *f2) {
	int Sa, Sb, Sc;
	printf("Enter salary for categories: ");
	scanf_s("\n%i, %i, %i", &Sa, &Sb, &Sc);

	printf("\n Salary information:\n");
	int A=0, B=0, C=0, factorySalary = 0;
	double workersCounter = 0.0;
	char worker[256];
	while (fgets(worker, sizeof(worker), f2) != NULL)
	{	// ищет в массиве worker переход на новую строку и ставит там его конец
		for (int i = 0; i < 256; i++) {
			if ((int)worker[i] == 13) {
				worker[i] = '\0';
			}
		}
		
		if (checkFactory(worker, factory)) {
			A += getAnumber(worker);
			B += getBnumber(worker);
			C += getCnumber(worker);
			factorySalary += calculateWorkerSalary(worker, Sa, Sb, Sc);
			workersCounter += 1;
		}
	}
	printf("\n\n Average salary: %lf", factorySalary/workersCounter);
	printf("\n\n Number of details:\n A: %i\n B: %i\n C: %i", A, B, C);
}

int main() {
	FILE *f2;
	if (!(f2 = fopen("e:\\work\\factory.txt", "r + b")))
	{
		puts("\n File was not found!");
		return 0;
	}
	char factory[5];
	printf("Enter the Factory number: ");
	fgets(factory, 5, stdin);	
	calculateDetailsNumber(factory, f2);
	return 0;
}