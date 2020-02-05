#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//converts binary number to decimal number
int binToDec(int x[]) {
    int i, dec = 0, z = 0;

    //input was recieved left to right, so convert in reverse to get proper number
    for (i = 7; i >= 1; i--) {
        dec += x[i] * pow(2, z);
        z++;
    }
    return dec;
}

//determines parity and returns whether odd or even
char* parity(int x[]) {
    int sum = 0, i = 0;
    for (i = 0; i < 8; i++) {
        sum += x[i];
    }
    if (sum % 2 == 0)
    {
        return "EVEN";
    }
    else {
        return "ODD";
    }
}

//print the ascii of the decimal number
//void printAscii(int dec) {
//	printf("%c", dec);
//}

void printInfo(int x[]) {
    int i = 0;
    //print the 8 binary numbers
    for (i = 0; i < 8; i++)
    {
        printf("%d", x[i]);
    }
    printf("\t");

    //print ascii char
    printf("%c", binToDec(x));

    //print dec version
    printf("%8d\t", binToDec(x));

    //print parity
    printf("%s", parity(x));
}

void fileReader(int argc, char** argv) {
    int val[8] = { 0 };
    int fileEOF = 0, i = 0, num = 0, size = 4, z = 0;
    //char* filename = (char*)malloc(20);
    char test = malloc((50)*sizeof(char));
    File * file;

    if (argc < 2) {
        printf("Please enter the file name.\n");
        scanf("%s", test);
        file = fopen(test, "r");
    } else {
        file = fopen(argv[1], "r");
    }

    printf("Original ASCII    Decimal  Parity \n");
    printf("-------- -------- -------- -------- \n");
    while ((num = fgetc(file)) != EOF)
    {
        val[i] = num - 48;
        i++;
        //put values into array until all 8 binary numbers are recieved
        if (i % 8 == 0) {
            //binary number recieved, print the converted data taken from binary
            printInfo(val);
            //reset the array to all 0s
            for (z = 0; z < 8; z++) {
                val[z] = 0;
            }
            i = 0;
            if ((num = fgetc(file)) == EOF) {
                break;
            }
            printf("\n");
        }
    }
    printInfo(val);
}

int main(int argc, char** argv) {
    fileReader(argc, argv);
    return 0;
}