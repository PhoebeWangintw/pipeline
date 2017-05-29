#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"
#include "dataHazard.h"

/* control signals */
/* 
   1. Branch
   2. MemRead
   3. MemWrite
*/

extern int dataMem[];
extern int registers[];

void mem_print(struct MEM_WB* mem_wb) {
    printf("\nMEM/WB :\n");
    printf("ReadData\t%d\n", mem_wb->ReadData);
    printf("ALUout\t\t%d\n", mem_wb->ALUOut);
    printf("Rt/Rd\t\t%d\n", mem_wb->rt_rd);
    printf("Control signals\t%s\n", mem_wb->control_signal);
    printf("=================================================================\n");
}

struct MEM_WB* mem(struct EX_MEM *ex_mem) {
    struct MEM_WB *mem_wb = (struct MEM_WB*)malloc(sizeof(struct MEM_WB));
    mem_wb->control_signal = (char *)malloc(sizeof(char) * 3);
    strncpy(mem_wb->control_signal, ex_mem->control_signal + 3, 2);
    mem_wb->control_signal[2] = '\0';
    mem_wb->rt_rd = ex_mem->rt_rd;
    mem_wb->ALUOut = ex_mem->ALUOut;
    /* beq bnq -> Branch */
    if (ex_mem->control_signal[0] == '1') {
        /* TODO: handle branch */

    }
    /* I-type rt, addr(rs) */
    /* lw -> MemRead */
    if (ex_mem->control_signal[1] == '1')    
        mem_wb->ReadData = dataMem[ex_mem->ALUOut/4];
    else 
        mem_wb->ReadData = 0;
    
    /* sw -> MemWrite */
    if (ex_mem->control_signal[2] == '1')
        dataMem[ex_mem->ALUOut/4] = registers[mem_wb->rt_rd];
    
    return mem_wb;
}