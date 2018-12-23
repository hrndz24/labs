#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// спрашивает, какое действие выполнить
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

// открывает(в данном случае создает, т к по умолчанию, 
// если файл не найден, он его создаёт) файл в режиме записи
// b значит двоичный формат (ещё есть текстовый)
void createFile() {
	FILE *f1;
	f1 = fopen("e:\\work\\new_stock.txt", "w + b");
	printf("\nA new stock file was created in e:\\\\work\n");
	fclose(f1);
}

// вырезает и возвращает из строки её кусок с позиции start и до end
char* cutPieceFromLine(char *line, int start, int end) {
	// выделяет для этого куска память в 20 символов
	char *piece = (char *)malloc(sizeof(char) * 20);
	int p, l;
	// записывает символы из line в piece
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

// проверяет если цена больше 1000
bool checkPrice(char *price) {
	// если цена состоит из 4 и более цифр
	if (strlen(price) >= 4) {
		return true;
	}
	// если цена состоит из менее 4 цифр
	else {
		return false;
	}
}

// находит позицию символа в строке, с которого начинается цена
int findStartPrice(char *product) {
	int count = 0, startPrice = 0;
	for (int i = 0; i < strlen(product); i++) {
		// count считает ',' 44 это ',' в ASCII 
		if ((int)product[i] == 44) {
			count += 1;			
		}
		// когда найдено 2 запятые
		if (count == 2) {
			// цена начинается через 2 символа после запятой
			startPrice = i + 2;
			break;
		}
	}
	return startPrice;
}

// находит позицию символа, на котором цена заканчивается
int findEndPrice(char *product) {
	int count = 0, endPrice = 0;
	for (int i = 0; i < strlen(product); i++) {
		// count считает ',' 44 это ',' в ASCII 
		if ((int)product[i] == 44) {
			count += 1;
		}
		// цена заканчивается 3 запятой
		if (count == 3) {			
			endPrice = i;
			break;			
		}
	}
	return endPrice;
}

// проверяет, если товар поступил более месяца назад
bool checkDate(char *date) {
	//сегодняшняя дата в днях
	int todayInDays = 21 + 12 * 30 + 2018 * 365;
	// дата товара в днях
	// каждый символ(кроме точек) даты переводится в число, которое в зависимости от позиции домножается на нужное количество дней
	// при переводе символа цифры в число, возвращается значение больше нужного на 48, поэтому 48 вычитается
	int dateInDays = (((int)date[0]-48) * 10 + ((int)date[1])-48)     +    (((int)date[3]-48) * 10 + ((int)date[4])-48)*30    +
		(((int)date[6]-48)*1000 + ((int)date[7]-48)*100+ ((int)date[8]-48)*10+ ((int)date[9]-48))*365;
	// если разница в днях превышает 30
	if ((todayInDays - dateInDays)>30) {
		return true;
	} // если разница в днях меньше 30
	else {
		return false;
	}
}

// находит позицию символа, с которого начинается дата
int findStartDate(char *product) {
	int count = 0, startDate = 0;
	for (int i = 0; i < strlen(product); i++) {
		// count считает ',' 44 это ',' в ASCII 
		if ((int)product[i] == 44) {
			count += 1;
		}
		// когда найдно 3 запятые
		if (count == 3) {
			// дата начинается через 2 символа после запятой
			startDate = i + 2;
			break;
		}
	}
	return startDate;
}

// проверяет, если товар подходит по всем критериям
bool checkProduct(char *product) {
	// вырезает из товара его цену
	int startPrice = findStartPrice(product);
	int endPrice = findEndPrice(product);
	char *price = cutPieceFromLine(product, startPrice, endPrice);
	// вырезает из товара его дату
	int startDate = findStartDate(product);
	int endDate = strlen(product);
	char *date = cutPieceFromLine(product, startDate, endDate);
	// если цена больше 1000 и поступил более, чем месяц назад
	if (checkPrice(price) && checkDate(date)) {
		return true;
	}
	else {
		return false;
	}
}

// сортирует пузырьком массив товаров по алфавиту
char** sortAlphabetically(char **products, int length) {
	char *zam;
	for (int i = 0; i < length - 1; i++) {
		for (int j = 1; j < length; j++) {
			// сравнивает товар с тем, что стоит до него
			// если стоят не в том порядке, то меняет их местами
			if (strcmp(products[j], products[j - 1])<0) {
				zam = products[j];
				products[j] = products[j - 1];
				products[j - 1] = zam;
			}
		}
	}
	return products;
}

// выводит товары, которые подходят по критериям 
void findProducts(char **products, int length) {
	printf("\nProducts:\n");
	// проходит по массиву и если товар подходит, то выводит его на экран
	for (int i = 0; i < length; i++) {
		if (checkProduct(products[i])) {
			printf("\n%s", products[i]);
		}
	}
}

void doAllTheStuff() {
	// открывает файл в режиме чтения	
	FILE *f2;
	if (!(f2 = fopen("e:\\work\\stock.txt", "r + b")))
	{
		puts("\n File was not found!");
		return;
	}
	// создаёт двумерный массив для товаров и выделяет под каждый товар память
	char **products;
	products = new char*[24];
	for (int i = 0; i < 24; i++) {
		products[i] = new char[256];
	}
	int k = 0;
	// считывает по строке из файла и добавляет её в массив
	// 256 максимальное кол-во символов, из которых может состоять строка
	while (fgets(products[k], 256, f2) != NULL){
		// проходит по строке
		for (int i = 0; i < 256; i++) {
			// когда '\n'(№13 в ASCII) встречается, ставит конец строки в этом месте
			if ((int)products[k][i] == 13) {
				products[k][i] = '\0';
			}
		}
		k += 1;
	}
	// длина массива товаров
	int length = k;
	// отсортированный по алфавиту массив товаров
	products = sortAlphabetically(products, length);
	// вызывает функцию, которая ищет подходящие товары
	findProducts(products, length);
}
int main() {
	// бесконечный цикл
	while (1) {
		int code = enterCode();
		// в зависимости от введённой цифры выполняет действия
		switch (code){
		case 0:
			// выходит из программы
			return 0;
		case 1:
			// вызывает функцию, которая создаёт новый файл
			createFile();
			break;
		case 2:
			// вызывает функцию, которая делает всю работу по поиску товаров
			doAllTheStuff();
			break;
		default:
			// если введена какая-то другая цифра, повторяет запрос заново
			continue;
		}
	}
	return 0;
}