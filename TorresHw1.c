#include <stdio.h>
#include <math.h> 
#include <stdlib.h>

//converts binary number to decimal number
int binToDec(int x[]) {
	int i, dec = 0, z = 0;

	//input was recieved left to right, so convert in reverse to get proper number
	for (i = 7; i >= 0; i--) {
		dec += x[i] * pow(2, z);
		z++;
	}
	return dec;
}

//determines parity and returns whether odd or even
void parity(int x[], char* par) {
	int sum = 0, i = 0;
	for (i = 0; i < 8; i++) {
		sum += x[i];
	}
	if (sum % 2 == 0)
	{
		*par = "EVEN";
	}
	else {
		*par = "ODD";
	}
}

//print the ascii of the decimal number
void printAscii(int dec) {
	printf("%c", dec);
}

void printInfo(int x[]) {
	int i = 0;
	//print the 8 binary numbers
	for (i = 0; i < 8; i++)
	{
		printf("%d", x[i]);
	}
	printf(" ");
	//print ascii char

	printf(" ");

	//print dec version

	printf(" ");

	//print parity


}

void fileReader(char* name) {
	int val[8] = { 0 };
	int fileEOF = 0, i = 0, num = 0, size = 4;
	char* par = (char*)malloc(size);
	FILE* file = fopen(name, "r");
	printf("Original ASCII    Decimal  Parity \n");
	printf("-------- -------- -------- -------- \n");
	while ((num = fgetc(file)) != EOF)
	{
		val[i] = num;
		i++;
		//put values into array until all 8 binary numbers are recieved
		if (i % 7 == 0) {
			//binary number recieved, print the converted data taken from binary
			printInfo(val);
		}
	}
}

int main() {
	char* filename = (char*)malloc(20);
	scanf("%s", filename);
	fileReader(filename);
	return 0;
}