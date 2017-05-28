/* write_back */
/* 
   1. write data back to registers
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"

extern int registers[];

/* control signal */
/* RegWrite & MemtoReg */

void write_back(struct MEM_WB* mem_wb) {
    if (strcmp(mem_wb->control_signal, "10") == 0) {
        /* R-type */
        registers[mem_wb->rt_rd] = mem_wb->ALUOut;
    } else if (strcmp(mem_wb->control_signal, "11") == 0) {
        /* lw */
        registers[mem_wb->rt_rd] = mem_wb->ReadData;
    } else if (strcmp(mem_wb->control_signal, "00") == 0) {
        /* sw & beq */
        // do nothing
    }
}
