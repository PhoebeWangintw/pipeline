#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "dataHazard.h"
#include "in_fetch.h"
#include "in_decode.h"
#include "exe.h"
#include "mem.h"
#include "write_back.h"

/* initialize register & its value */
int registers[] = {0, 9, 8, 7, 1, 2, 3, 4, 5, 6};  /* $0 ~ $9 */
char *dataAddr[5] = {"0x00", "0x04", "0x08", "0x0C", "0x10"};
int dataMem[] = {5, 9, 4, 8, 7};  /* 0x00 ~ 0x10 */

int PC = 0;
/* setting jump checker */
int jump = 1;
int clear_id = 0;
int CC;
int lw_detect = 0;
int noCount;
char* forwardA;
char* forwardB;
struct IF_ID *if_id;
struct ID_EX *id_ex;
struct EX_MEM *ex_mem;
struct MEM_WB *mem_wb;

void printHeader();
void init();
int main(int argc, char *argv[]) {
	/* read instructions */
	CC = 0;  // init PC, CC
	noCount = 0;
	init();
	while (noCount < 4) {
		write_back(mem_wb);
		mem_wb = mem(ex_mem);
		ex_mem = execution(id_ex, mem_wb);
		id_ex = instruction_decode(if_id);
		if_id = instruction_fetch(if_id);
		lw_detect = lwDetect(id_ex, if_id);
		checkHazard(mem_wb, ex_mem, id_ex, if_id);
		printHeader();
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
	in_fetch_print(if_id);
	in_decode_print(id_ex);
	exe_print(ex_mem);
	mem_print(mem_wb);
}

void init() {
	if_id = (struct IF_ID*)malloc(sizeof(struct IF_ID));
	if_id->PC = 0;
	if_id->rs = 0;
	if_id->rt = 0;
	if_id->instr = (char *)malloc(sizeof(char) * 33);
	strcpy(if_id->instr,"00000000000000000000000000000000");
	if_id->instr[32] = '\0';
	id_ex = (struct ID_EX*)malloc(sizeof(struct ID_EX));
	id_ex->rs = 0;
	id_ex->rt = 0;
	id_ex->rd = 0;
	id_ex->rs_v = 0;
	id_ex->rt_v = 0;
	id_ex->addr = 0;
	id_ex->funct = 0;
	id_ex->control_signal = (char *)malloc(sizeof(char)*10);
	strcpy(id_ex->control_signal, "000000000");
	ex_mem = (struct EX_MEM*)malloc(sizeof(struct EX_MEM));
	ex_mem->rt_rd = 0;
	ex_mem->ALUOut = 0;
	ex_mem->WriteData = 0;
	ex_mem->control_signal = (char *)malloc(sizeof(char)*6);
	strcpy(ex_mem->control_signal, "00000");
	ex_mem->control_signal[5] = '\0';
	mem_wb = (struct MEM_WB*)malloc(sizeof(struct MEM_WB));
	mem_wb->rt_rd = 0;
	mem_wb->ReadData = 0;
	mem_wb->ALUOut = 0;
	mem_wb->control_signal = (char *)malloc(sizeof(char)*3);
	strcpy(mem_wb->control_signal, "00");
	mem_wb->control_signal[2] = '\0';
}