#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]) {
	return 0;
}

/* initialize register */
int register[] = {0, 9, 8, 7, 1, 2, 3, 4, 5, 6}  /* $0 ~ $9 */
int dataRegister[] = {5, 9, 4, 8 , 7}  /* 0x00 ~ 0x10 */

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

void readInstruction() {
	
}
