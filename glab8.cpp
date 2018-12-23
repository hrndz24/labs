#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// ����������, ����� �������� ���������
int enterCode() {
	int code;
	printf("\n\nWhat do you want to do:\n\n");
	printf("Create new file - 1\n");
	printf("Search through stock - 2\n");
	printf("Exit - 0\n");
	printf("Enter: ");
	scanf_s("%i", &code);
	return code;
}

// ���������(� ������ ������ �������, � � �� ���������, 
// ���� ���� �� ������, �� ��� ������) ���� � ������ ������
// b ������ �������� ������ (��� ���� ���������)
void createFile() {
	FILE *f1;
	f1 = fopen("e:\\work\\new_stock.txt", "w + b");
	printf("\nA new stock file was created in e:\\\\work\n");
	fclose(f1);
}

// �������� � ���������� �� ������ � ����� � ������� start � �� end
char* cutPieceFromLine(char *line, int start, int end) {
	// �������� ��� ����� ����� ������ � 20 ��������
	char *piece = (char *)malloc(sizeof(char) * 20);
	int p, l;
	// ���������� ������� �� line � piece
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

// ��������� ���� ���� ������ 1000
bool checkPrice(char *price) {
	// ���� ���� ������� �� 4 � ����� ����
	if (strlen(price) >= 4) {
		return true;
	}
	// ���� ���� ������� �� ����� 4 ����
	else {
		return false;
	}
}

// ������� ������� ������� � ������, � �������� ���������� ����
int findStartPrice(char *product) {
	int count = 0, startPrice = 0;
	for (int i = 0; i < strlen(product); i++) {
		// count ������� ',' 44 ��� ',' � ASCII 
		if ((int)product[i] == 44) {
			count += 1;			
		}
		// ����� ������� 2 �������
		if (count == 2) {
			// ���� ���������� ����� 2 ������� ����� �������
			startPrice = i + 2;
			break;
		}
	}
	return startPrice;
}

// ������� ������� �������, �� ������� ���� �������������
int findEndPrice(char *product) {
	int count = 0, endPrice = 0;
	for (int i = 0; i < strlen(product); i++) {
		// count ������� ',' 44 ��� ',' � ASCII 
		if ((int)product[i] == 44) {
			count += 1;
		}
		// ���� ������������� 3 �������
		if (count == 3) {			
			endPrice = i;
			break;			
		}
	}
	return endPrice;
}

// ���������, ���� ����� �������� ����� ������ �����
bool checkDate(char *date) {
	//����������� ���� � ����
	int todayInDays = 21 + 12 * 30 + 2018 * 365;
	// ���� ������ � ����
	// ������ ������(����� �����) ���� ����������� � �����, ������� � ����������� �� ������� ����������� �� ������ ���������� ����
	// ��� �������� ������� ����� � �����, ������������ �������� ������ ������� �� 48, ������� 48 ����������
	int dateInDays = (((int)date[0]-48) * 10 + ((int)date[1])-48)     +    (((int)date[3]-48) * 10 + ((int)date[4])-48)*30    +
		(((int)date[6]-48)*1000 + ((int)date[7]-48)*100+ ((int)date[8]-48)*10+ ((int)date[9]-48))*365;
	// ���� ������� � ���� ��������� 30
	if ((todayInDays - dateInDays)>30) {
		return true;
	} // ���� ������� � ���� ������ 30
	else {
		return false;
	}
}

// ������� ������� �������, � �������� ���������� ����
int findStartDate(char *product) {
	int count = 0, startDate = 0;
	for (int i = 0; i < strlen(product); i++) {
		// count ������� ',' 44 ��� ',' � ASCII 
		if ((int)product[i] == 44) {
			count += 1;
		}
		// ����� ������ 3 �������
		if (count == 3) {
			// ���� ���������� ����� 2 ������� ����� �������
			startDate = i + 2;
			break;
		}
	}
	return startDate;
}

// ���������, ���� ����� �������� �� ���� ���������
bool checkProduct(char *product) {
	// �������� �� ������ ��� ����
	int startPrice = findStartPrice(product);
	int endPrice = findEndPrice(product);
	char *price = cutPieceFromLine(product, startPrice, endPrice);
	// �������� �� ������ ��� ����
	int startDate = findStartDate(product);
	int endDate = strlen(product);
	char *date = cutPieceFromLine(product, startDate, endDate);
	// ���� ���� ������ 1000 � �������� �����, ��� ����� �����
	if (checkPrice(price) && checkDate(date)) {
		return true;
	}
	else {
		return false;
	}
}

// ��������� ��������� ������ ������� �� ��������
char** sortAlphabetically(char **products, int length) {
	char *zam;
	for (int i = 0; i < length - 1; i++) {
		for (int j = 1; j < length; j++) {
			// ���������� ����� � ���, ��� ����� �� ����
			// ���� ����� �� � ��� �������, �� ������ �� �������
			if (strcmp(products[j], products[j - 1])<0) {
				zam = products[j];
				products[j] = products[j - 1];
				products[j - 1] = zam;
			}
		}
	}
	return products;
}

// ������� ������, ������� �������� �� ��������� 
void findProducts(char **products, int length) {
	printf("\nProducts:\n");
	// �������� �� ������� � ���� ����� ��������, �� ������� ��� �� �����
	for (int i = 0; i < length; i++) {
		if (checkProduct(products[i])) {
			printf("\n%s", products[i]);
		}
	}
}

void doAllTheStuff() {
	// ��������� ���� � ������ ������	
	FILE *f2;
	if (!(f2 = fopen("e:\\work\\stock.txt", "r + b")))
	{
		puts("\n File was not found!");
		return;
	}
	// ������ ��������� ������ ��� ������� � �������� ��� ������ ����� ������
	char **products;
	products = new char*[24];
	for (int i = 0; i < 24; i++) {
		products[i] = new char[256];
	}
	int k = 0;
	// ��������� �� ������ �� ����� � ��������� � � ������
	// 256 ������������ ���-�� ��������, �� ������� ����� �������� ������
	while (fgets(products[k], 256, f2) != NULL){
		// �������� �� ������
		for (int i = 0; i < 256; i++) {
			// ����� '\n'(�13 � ASCII) �����������, ������ ����� ������ � ���� �����
			if ((int)products[k][i] == 13) {
				products[k][i] = '\0';
			}
		}
		k += 1;
	}
	// ����� ������� �������
	int length = k;
	// ��������������� �� �������� ������ �������
	products = sortAlphabetically(products, length);
	// �������� �������, ������� ���� ���������� ������
	findProducts(products, length);
}
int main() {
	// ����������� ����
	while (1) {
		int code = enterCode();
		// � ����������� �� �������� ����� ��������� ��������
		switch (code){
		case 0:
			// ������� �� ���������
			return 0;
		case 1:
			// �������� �������, ������� ������ ����� ����
			createFile();
			break;
		case 2:
			// �������� �������, ������� ������ ��� ������ �� ������ �������
			doAllTheStuff();
			break;
		default:
			// ���� ������� �����-�� ������ �����, ��������� ������ ������
			continue;
		}
	}
	return 0;
}