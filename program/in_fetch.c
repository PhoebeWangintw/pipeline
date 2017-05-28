/* instruction fetch */
/* 1. add PC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

static int PC = 0;
extern int nopCount;
char *nop_instruction = {"00000000000000000000000000000000"};

void addPC() {
    PC += 4;
}

void in_fetch_print(struct IF_ID *if_id) {
    printf("IF/ID: \n");
    printf("PC\t\t%d\n", if_id->PC);
    printf("Instruction\t%s\n\n", if_id->instr);
}

struct IF_ID* instruction_fetch() {
    struct IF_ID *if_id = (struct IF_ID*)malloc(sizeof(struct IF_ID));
    if_id->instr = (char *)malloc(sizeof(char) * 33);

    char *buffer;
    size_t bufsize = 40;
    size_t characters;
	buffer = (char *)malloc(bufsize * sizeof(char));

    if (buffer == NULL) {
        perror("Unable to allocate buffer");
        exit(1);
	}
    if (getline(&buffer,&bufsize,stdin) != EOF){
        strncpy(if_id->instr, buffer, 32);
        nopCount = 0;
    } else {
        strncpy(if_id->instr, nop_instruction, 32);
        nopCount += 1;
    }
    if_id->instr[32] = '\0';
    addPC();
    if_id->PC = PC;
    in_fetch_print(if_id);

    return if_id;
}