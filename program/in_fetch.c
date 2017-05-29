/* instruction fetch */
/* 1. add PC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "bin2dec.h"

extern int PC;
extern int noCount;
extern int lw_detect;
char *no_instruction = {"00000000000000000000000000000000"};

void addPC() {
    PC += 4;
}

void in_fetch_print(struct IF_ID *if_id) {
    printf("IF/ID :\n");
    printf("PC\t\t%d\n", if_id->PC);
    printf("Instruction\t%s\n\n", if_id->instr);
}

struct IF_ID* instruction_fetch(struct IF_ID* old) {
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
    if (lw_detect) {
        /* do not read next instruction */
        PC -= 4;
        strcpy(if_id->instr, old->instr);
        noCount = 0;
    } else if (getline(&buffer,&bufsize,stdin) != EOF){
        strncpy(if_id->instr, buffer, 32);
        noCount = 0;
    } else {
        strncpy(if_id->instr, no_instruction, 32);
        noCount += 1;
    }

    if_id->instr[32] = '\0';

    char rs[6], rt[6];
    strncpy(rs, if_id->instr + 6, 5);
    strncpy(rt, if_id->instr + 11, 5);
    rs[5] = '\0';
    rt[5] = '\0';
    if_id->rs = bin2dec(rs);
    if_id->rt = bin2dec(rt);
    addPC();
    if_id->PC = PC;
    return if_id;
}