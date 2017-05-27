/* instruction fetch */
/* 1. add PC */
#include <stdio.h>
extern int PC;
void addPC(int PC) {
    PC += 4;
}

void in_fetch_print(char *instr) {
    printf("IF/ID: \n");
    printf("PC\t\t%d\n", PC);
    printf("Instruction\t%s", instr);
}

void instruction_fetch(char *instr) {
    addPC(PC);
    in_fetch_print(instr);
}