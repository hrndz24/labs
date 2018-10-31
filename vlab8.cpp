#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// cuts a piece from line
char* pieceOfLine(char *line, int start, int end) {
	char *piece = (char *)malloc(sizeof(char) * 20);
	int p, l;
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

bool checkPrice(char price[7], char max_price[7]) {
	// if the price we have is more than max_price
	if (strlen(price) > strlen(max_price)) {
		return true;
	}
	// if the price we have is less than max_price
	else if (strlen(price) < strlen(max_price)) {
		return false;
	}
	// if the price we have is equal to max_price
	else {
		// compares every number of prices
		for (int i = 0; i < 7; i++) {
			if ((int)price[i] > (int)max_price[i]) {
				return true;
			}
			else if ((int)price[i] < (int)max_price[i]) {
				return false;
			}
			else {
				continue;
			}
		}
	}
}

void mostExpensive(FILE* f2) {
	// {0} is just a placeholder
	char maxprice[7] = { 0 }, line[256], *name = {0};
	int startName = 0, endName;
	while (fgets(line, sizeof(line), f2) != NULL)
	{
		line[strlen(line)] = '\0';
		int count = 0, startPrice = 0, endPrice;
		for (int i = 0; i < strlen(line); i++) {
			// counts ','
			if ((int)line[i] == 44) {
				count += 1;
			}
			if (count == 1 && startPrice == 0) {
				startPrice = i + 2;		
				endName = i;
			} 
			if (count==2) {
				endPrice = i;
				break;
			}			
		}
		char *price = pieceOfLine(line, startPrice, endPrice);
		
		if (checkPrice(price, maxprice)) {
			// sets maxprice to be the price we have
			for (int i = 0; i < strlen(price); i++) {
				maxprice[i] = price[i];
				maxprice[strlen(maxprice)] = '\0';				
			}
			name = pieceOfLine(line, startName, endName);
		}
	}
	printf("The price is %s\nThe toy is %s", maxprice, name);
}
void babyToys(FILE* f2) {
	char line[256];
	while (fgets(line, sizeof(line), f2) != NULL)
	{
		line[strlen(line)] = '\0';
		int count = 0, startYear, endName=0, startName=0;
		for (int i = 0; i < strlen(line); i++) {
			// counts ','
			if ((int)line[i] == 44) {
				count += 1;
				// 7 chars away from ','
				startYear = i+7;
			}
			if (count == 1 && endName==0) {
				endName = i;
			}
		}		
		// if the char after startYear is space => year has one number
		if ((int)line[startYear + 1] == 32 && line[startYear] == '1') {
			char *name = pieceOfLine(line, startName, endName);
			printf("%s\n", name);
		}
	}
}

void checkLine(FILE* f2, char *maxprice) {

	char line[256];	
	while (fgets(line, sizeof(line), f2) != NULL)
	{
		line[strlen(line)] = '\0';
		int startName = 0, endName;
		int count = 0, startPrice = 0, endPrice;
		for (int i = 0; i < strlen(line); i++) {
			// counts ','
			if ((int)line[i] == 44) {
				count += 1;
			}
			if (count == 1 && startPrice == 0) {
				startPrice = i + 2;
				endName = i;
			}
			if (count == 2) {
				endPrice = i;
				break;
			}
		}
		char *price = pieceOfLine(line, startPrice, endPrice);
		char *name = pieceOfLine(line, startName, endName);
		// it will return if price is greater than maxprice, but we need the opposite
		if (!(checkPrice(price, maxprice))) {
			printf("%s\n", name);
		}
	}
}

int main() {

	FILE *f2;
	if (!(f2 = fopen("e:\\work\\toys.txt", "r + b")))
	{
		puts("\n Файл не создан!");
		return 0;
	}

	int code;
	printf("Choose an action:\nToys for 1-3 y.o. - 1\nThe most expensive toy - 2\nFind a toy - 3\n");
	scanf_s("%i", &code);
	fseek(stdin, 0, SEEK_END);
	switch (code) {
	case 1:
		babyToys(f2);
		break;
	case 2:
		mostExpensive(f2);
		break;
	case 3:
		char maxprice[7];
		fgets(maxprice, 7, stdin);
		maxprice[strlen(maxprice)] = '\0';
		checkLine(f2, maxprice);
		break;
	}
	fclose(f2);
	return 0;
}