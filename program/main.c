#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_fetch.h"

/* initialize register */
int registers[] = {0, 9, 8, 7, 1, 2, 3, 4, 5, 6};  /* $0 ~ $9 */
const char dataMemAddr[][4] = {"0x00", "0x04", "0x08", "0x0C", "0x10"};
int dataMem[] = {5, 9, 4, 8, 7};  /* 0x00 ~ 0x10 */

/* control signal */
int r_control[] = {1, 1, 0, 0, 0, 0, 0, 1, 0};
int lw_control[] = {0, 0, 0, 1, 0, 1, 0, 1, 1};
int sw_control[] = {0, 0, 0, 1, 0, 0, 1, 0, 0};
int beq_control[] = {0, 0, 1, 0, 1, 0, 0, 0, 0};

/* PC */
int PC;
int main(int argc, char *argv[]) {
	char *buffer;
    size_t bufsize = 40;
    size_t characters;
	buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL) {
        perror("Unable to allocate buffer");
        exit(1);
	}
	/* read instructions */
	PC = 0;  // init PC
	while (getline(&buffer,&bufsize,stdin) != EOF) {
		instruction_fetch(buffer);
	}
	return 0;
}

/* lw, sw, add, addi, sub, or, slt */



/* R-type */
/* add, sub, or, slt */
/* op: 6(0), rs: 5, rt: 5, rd: 5, shamt: 5, funct: 6(ALU instruction) */
/* R-type rd, rs, rt */
/* funct: */
/* add: 100000 */
/* sub: 100010 */
/* or: 100101 */
/* slt: 101010 */


/* I-type */
/* lw, sw, addi */
/* op: 6, rs: 5, rt: 5, address: 16 */
/* I-type rt, addr(rs) */
/* opcode: */
/* lw: 100011 */
/* sw: 101011 */
/* addi: 001000 */
