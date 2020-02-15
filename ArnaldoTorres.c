#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <io.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Programmer: Arnaldo Torres
 * COMP 322
 * LAB 0:
 * read from console or read from a file, and then convert to ascii and decimal and show parity
 *
 */
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

//functon to print ascii characters that are outside the printable section
char * iAscii(int n)
{
    char * nonPrint[34] = {
            "NUL", "SOH", "STX", "ETX" , "EOT", "ENQ", "ACK", "BEL", "BS",
            "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2",
            "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS",
            "GS", "RS", "US", "DEL"
    };

    if (n == 127){
        return nonPrint[34];
    } else {
        return nonPrint[n];
    }
}

void printInfo(int x[]) {
    int i = 0, dec = binToDec(x);
    //print the 8 binary numbers
    for (i = 0; i < 8; i++)
    {
        printf("%d", x[i]);
    }
    //print ascii char
    if(dec < 33 || dec == 127)
    {
        printf("%9s", iAscii(dec));
    } else {
        printf("%9c", binToDec(x));
    }

    //print dec version
    printf("%9d", dec);

    //print parity
    printf("%9s", parity(x));
}

void fileLoop(char * arg)
{
    int i = 0, z = 0;
    int val[8] = { 0 };
    char fileContents[150] = { 0 };
    char space = ' ';

    int fd = open(arg, O_RDONLY);
    int valRead = read(fd, fileContents, 150);

    for( i = 0; i < valRead - 1; i++)
    {
        for(z = 0; z < 8; z++) {
            if (space == fileContents[i] || fileContents[i] == '\000') {
                printInfo(val);
                //reset the array to all 0s
                for (z = 0; z < 8; z++) {
                    val[z] = 0;
                }
                printf("\n");
                break;
            } else {
                val[z] = fileContents[i] - 48;

                //put values into array until all 8 binary numbers are received
                if (z == 7) {
                    //binary number received, print the converted data taken from binary
                    printInfo(val);
                    //reset the array to all 0s
                    for (z = 0; z < 8; z++) {
                        val[z] = 0;
                    }
                    printf("\n");
                }
            }
            i++;
        }
    }
}

void handleArgs(int argc, char** argv) {\

    if (argc < 2){
        //no input end program
        printf("less than 2 arg");
    } else {
        int val[8] = {0};
        int i = 0, z = 0, dashFound = 0, notFile = 0;
        char* dash = "-";

        printf("Original ASCII    Decimal  Parity \n");
        printf("-------- -------- -------- -------- \n");

        if (strcmp(dash,argv[1]) == 0) {
            //first argument is a dash, no need to check for filename
            dashFound++;
        }
            //check that first char is either binary or text
        else if ((argv[1][0] == '1' || argv[1][0] == '0')){
            notFile++;
        }
        //checks to see if a filename was input or instead just binary
        if (notFile == 0 && dashFound == 0) {
            fileLoop(argv[1]);
        } else {
            //filename not found read contents from the console
            for( i = 1; i < argc; i++) {
                if (dashFound > 0) {
                    //decrement to avoid redundant skips
                    dashFound--;
                    //skip past the dash element
                    continue;
                } else {
                    for (z = 0; z < strlen(argv[i]); z++) {
                        val[z] = argv[i][z] - 48;
                    }
                    printInfo(val);
                    for (z = 0; z < 8; z++) {
                        val[z] = 0;
                    }
                    printf("\n");
                }
            }
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    handleArgs(argc, argv);
    return 0;
}