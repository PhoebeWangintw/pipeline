#include <stdio.h>
#include <string.h>

int bin2dec(char *bin) {
    int i;
    int decimal = 0;
    for (i = 0; i < strlen(bin); ++i) {
        decimal *= 2;
        if (bin[i] == '1') 
            decimal += 1;
    }
    return decimal;
}