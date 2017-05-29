/* check data hazard */
/*
	1a. EX/MEM.RegisterRd = ID/EX.RegisterRs forwardA = "10"
	1b. EX/MEM.RegisterRd = ID/EX.RegisterRt forwardB = "10"
	2a. MEM/WB.RegisterRd = ID/EX.RegisterRs forwardA = "01"
	2b. MEM/WB.RegisterRd = ID/EX.RegisterRt forwardB = "01"
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

extern char* forwardA;
extern char* forwardB;
extern int dataMem[];
extern int PC;

void checkHazard(struct MEM_WB *mem_wb, struct EX_MEM *ex_mem, struct ID_EX *id_ex, struct IF_ID *if_id);

int exHazard(struct EX_MEM *ex_mem, struct ID_EX *id_ex) {
    /* control signal -> check Regwrite (R-type) */
    /* check the dest register (cannot be $0) */
    /* check the dest register and the next instruction's used registers */
    forwardA = (char *)malloc(sizeof(char) * 3);
    forwardB = (char *)malloc(sizeof(char) * 3);
    if ((ex_mem->control_signal[3] == '1') && (ex_mem->rt_rd != 0) && 
        (ex_mem->rt_rd == id_ex->rs)) {
        strcpy(forwardA, "10");
        forwardA[2] = '\0';
        return 1;
    }
    if ((ex_mem->control_signal[3] == '1') && (ex_mem->rt_rd != 0) &&
        (ex_mem->rt_rd == id_ex->rt)) {
        strcpy(forwardB, "10");
        forwardB[2] = '\0';
        return 2;
    }
    strcpy(forwardA, "00");
    forwardA[2] = '\0';
    strcpy(forwardB, "00");
    forwardB[2] = '\0';
    return 0;
}

int memHazard(struct MEM_WB *mem_wb, struct EX_MEM *ex_mem, struct ID_EX *id_ex) {
    /* control signal -> check RegWrite (R-type) */
    /* check the dest register (cannot be $0) */
    forwardA = (char *)malloc(sizeof(char) * 3);
    forwardB = (char *)malloc(sizeof(char) * 3);
    int condition_1 = (mem_wb->control_signal[0] == '1') && (mem_wb->rt_rd != 0);
    int condition_2 = !(ex_mem->control_signal[3] == '1') && ex_mem->rt_rd != 0 && (ex_mem->rt_rd != id_ex->rs);
    int condition_3 = !(ex_mem->control_signal[3] == '1') && ex_mem->rt_rd != 0 && (ex_mem->rt_rd != id_ex->rt);
    if (condition_1 &&
        (mem_wb->rt_rd == id_ex->rs)) {
        strcpy(forwardA, "01");
        forwardA[2] = '\0';
        return 1;   
    }
    if (condition_1 &&
        (mem_wb->rt_rd == id_ex->rt)) {
        strcpy(forwardB, "01");
        forwardB[2] = '\0';
        return 2;   
    }
    strcpy(forwardA, "00");
    forwardA[2] = '\0';
    strcpy(forwardB, "00");
    forwardB[2] = '\0';
    return 0;
}

int lwDetect(struct ID_EX *id_ex, struct IF_ID *if_id) {
    /* check lw & check the dest of lw and the registers used in next instruction. */
    if (id_ex->control_signal[5] == '1' &&
        ((id_ex->rt == if_id->rs) || (id_ex->rt == if_id->rt))) {
        /* stalling */
        /* set control signal to all 0s */
        /* do not increment PC -> not reading the next instruction */
        return 1;
    }
    return 0;
}

void checkHazard(struct MEM_WB *mem_wb, struct EX_MEM *ex_mem, struct ID_EX *id_ex, struct IF_ID *if_id) {
    int ex_hazard = exHazard(ex_mem, id_ex);
    switch(ex_hazard) {
        /* forward = "00" */
        case 1:
            /* the first ALU operand is forwarded from the prior ALU result. */
            id_ex->rs_v = ex_mem->ALUOut;
            break;
        case 2:
            /* the second ALU operand is forwarded from the prior ALU result. */
            id_ex->rt_v = ex_mem->ALUOut;
            break;
        default:
            /* no hazard */
            break;
    }

    int mem_hazard = memHazard(mem_wb, ex_mem, id_ex);
    switch(mem_hazard) {
        /* forward = "01" */
        case 1:
            /* the first ALU operand is forwarded from 
            data memory or an earlier ALU result */
            if (mem_wb->control_signal[1] == '1') {
                /* MemtoReg */
                id_ex->rs_v = mem_wb->ReadData;
            } else {
                id_ex->rs_v = mem_wb->ALUOut;    
            }
            break;
        case 2:
            /* the second ALU operand is forwarded from 
            data memory or an earlier ALU result */
            if (mem_wb->control_signal[1] == '1') {
                /* MemtoReg */
                id_ex->rt_v = mem_wb->ReadData;
            } else {
                id_ex->rt_v = mem_wb->ALUOut;
            }
            break;
        default:
            /* no hazard */
            break;
    }
}