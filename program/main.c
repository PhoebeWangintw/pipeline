#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_fetch.h"
#include "in_decode.h"
#include "exe.h"
#include "mem.h"
#include "struct.h"

/* initialize register & its value */
int registers[] = {0, 9, 8, 7, 1, 2, 3, 4, 5, 6};  /* $0 ~ $9 */
char *dataAddr[5] = {"0x00", "0x04", "0x08", "0x0C", "0x10"};
int dataMem[] = {5, 9, 4, 8, 7};  /* 0x00 ~ 0x10 */

/* control signal */
// TODO: check the control signal of andi_control.
char *r_control = "110000010";
char *lw_control = "000101011";
char *sw_control = "000100100";
char *addi_control = "000100010";
char *andi_control = "";
char *beq_control = "001010000";
char *bnq_control = "001010000";

int CC;
int nopCount;

/* buffer: IF/ID, ID/EX, EX/MEM, MEM/WB */
char bufferArr[4][32] = {"00000000000000000000000000000000"};

// TODO: change global variable to local variable using struct.
/* data hazard, check hazard in main.c */
/*
	1a. EX/MEM.RegisterRd = ID/EX.RegisterRs
	1b. EX/MEM.RegisterRd = ID/EX.RegisterRt
	2a. MEM/WB.RegisterRd = ID/EX.RegisterRs
	2b. MEM/WB.RegisterRd = ID/EX.RegisterRt
*/

void printHeader();
int main(int argc, char *argv[]) {
	/* read instructions */
	CC = 0;  // init PC, CC
	nopCount = 0;
	while (nopCount < 4) {
		printHeader();
		struct IF_ID *if_id = instruction_fetch();
		struct ID_EX *id_ex = instruction_decode(if_id);
		struct EX_MEM *ex_mem = execution(id_ex);
	}
	return 0;
}

/* lw, sw, add, addi, sub, or, slt */
void printHeader() {
	int i;
	CC += 1;
	printf("CC %d:\n", CC);
	printf("\nRegisters:\n");
	for (i = 0;i < 10; ++i) 
		printf("$%d: %d\n", i, registers[i]);
	printf("\nData memory:\n");
	for (i = 0;i < 5; ++i) 
		printf("%s: %d\n", dataAddr[i], dataMem[i]);
	printf("\n");
}
