#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"

void mem_print(struct MEM_WB* mem_wb) {
    printf("\nMEM/WB :\n");
    printf("ReadData\t\n");
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
    return mem_wb;
}