#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_fetch.h"
#include "in_decode.h"

/* initialize register & its value */
int registers[] = {0, 9, 8, 7, 1, 2, 3, 4, 5, 6};  /* $0 ~ $9 */
char *dataAddr[5] = {"0x00", "0x04", "0x08", "0x0C", "0x10"};
int dataMem[] = {5, 9, 4, 8, 7};  /* 0x00 ~ 0x10 */
int rs_r, rt_r, rd_r, addr_v;

/* control signal */
char *r_control = "110000010";
char *lw_control = "000101011";
char *sw_control = "000100100";
char *addi_control = "000000000";
char *beq_control = "001010000";
char control_signal[9] = "000000000";

/* PC */
int PC, CC;
char bufferArr[5][32] = {"00000000000000000000000000000000"};

void printHeader();
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
	PC = 0, CC = 0;  // init PC, CC
	while (getline(&buffer,&bufsize,stdin) != EOF) {
		instruction_fetch(buffer);
		printHeader(buffer);
		instruction_decode(bufferArr[0]);
	}
	return 0;
}

/* lw, sw, add, addi, sub, or, slt */
void printHeader(char *instr) {
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
	in_fetch_print(instr);
	in_decode_print();
}
