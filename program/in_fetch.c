/* instruction fetch */
/* 1. add PC */
#include <stdio.h>
#include <string.h>
extern int PC;
extern char bufferArr[5][32];

void addPC() {
    PC += 4;
}

void in_fetch_print() {
    printf("IF/ID: \n");
    printf("PC\t\t%d\n", PC);
    printf("Instruction\t%s\n\n", bufferArr[0]);
}

void instruction_fetch(char *instr) {
    addPC();
    strncpy(bufferArr[0], instr, 32);
}