#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <io.h>

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

void fileLoop(char * arg)
{
    int i = 0, z = 0, num = 0;
    int val[8] = { 0 };
    char fileContents[160];
    char space = ' ';
    FILE * file;
    file = open(arg, "r");
    int fd = fileno(file);
    size_t numBytes = sizeof(fileContents);;
    ssize_t bytesRead = read(fd, fileContents, numBytes);

    for( i =0; i < bytesRead; i++)
    {
        if(space == fileContents[i] && (z < 8 && z > 0)){
            printInfo(val);
            //reset the array to all 0s
            for (z = 0; z < 8; z++) {
                val[z] = 0;
            }
            printf("\n");
        } else {
            val[z] = fileContents[i] - 48;
            z++;
            //incrememnt i to move over the space
            i++;
            //put values into array until all 8 binary numbers are received
            if (z == 8) {
                //binary number recieved, print the converted data taken from binary
                printInfo(val);
                //reset the array to all 0s
                for (z = 0; z < 8; z++) {
                    val[z] = 0;
                }
                printf("\n");
            }
        }
        z = 0;
    }
    // printInfo(val);
    free(file);
}


void handleArgs(int argc, char** argv) {

    struct stat checkFile;
    int val[8] = { 0 };
    int i = 0, z = 0, fd = 0, dashFound = 0;
    char consoleContents[160];
    size_t numBytes;
    ssize_t bytesRead;
    char dash = '-';
    char space = ' ';

    printf("Original ASCII    Decimal  Parity \n");
    printf("-------- -------- -------- -------- \n");

    if (strcmp(argv[1],dash) == 0){
        //first argument is a dash, no need to check for filename
        dashFound++;
    }
    //checks to see if a filename was input or instead just binary
    if (checkFile(argv[1], &checkFile) == 0 && dashFound == 0)
    {
        fileLoop(argv[1]);
    } else {
        //filename not found read contents from the console
        numBytes = sizeof(consoleContents);
        bytesRead = read(fd, consoleContents, numBytes);

        for( i =0; i < bytesRead; i++)
        {
            if(space == consoleContents[i] && (z < 8 && z > 0))
            {
                printInfo(val);
                //reset the array to all 0s
                for (z = 0; z < 8; z++)
                {
                    val[z] = 0;
                }
                printf("\n");
            } else {
                val[z] = consoleContents[i] - 48;
                z++;
                //incrememnt i to move over the space
                i++;
                //put values into array until all 8 binary numbers are received
                if (z == 8)
                {
                    //binary number received, print the converted data taken from binary
                    printInfo(val);
                    //reset the array to all 0s
                    for (z = 0; z < 8; z++)
                    {
                        val[z] = 0;
                    }
                    printf("\n");
                }
            }
            z = 0;
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    handleArgs(argc, argv);
    return 0;
}