/* instruction decode */
/* 1. 16-bit immediate field -> sign-extended to 32 bit
   2. read two register (rs, rt)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "bin2dec.h"
#include "dataHazard.h"

extern int registers[];
extern char* forwardA;
extern char* forwardB;

/* control signal */
char *r_control = "110000010";
char *lw_control = "000101011";
char *sw_control = "000100100";
char *addi_control = "000100010";
char *andi_control = "011100010";
char *beq_control = "001010000";
char *bnq_control = "001010000";

/* R-type */
/* add, sub, or, slt */
/* op: 6(0), rs: 5, rt: 5, rd: 5, shamt: 5, funct: 6(ALU instruction) */
/* R-type rd, rs, rt */

/* I-type */
/* lw, sw, addi */
/* op: 6, rs: 5, rt: 5, address: 16 */
/* I-type rt, addr(rs) */

char op[7], rs[6], rt[6], rd[6], funct[7], addr[17];
char *r_op = "000000";
char *lw_op = "100011";
char *sw_op = "101011";
char *beq_op = "000100";
char *bnq_op = "000101";
char *addi_op = "001000";
char *andi_op = "001100";

void in_decode_print(struct ID_EX* id_ex) {
    printf("ID/EX :\n");
    printf("ReadData1\t%d\n", registers[id_ex->rs]);
    printf("ReadData2\t%d\n", registers[id_ex->rt]);
    printf("sign_ext\t%d\n", id_ex->addr);
    printf("Rs\t\t%d\n", id_ex->rs);
    printf("Rt\t\t%d\n", id_ex->rt);
    printf("Rd\t\t%d\n", id_ex->rd);
    printf("Control signals\t%s\n", id_ex->control_signal);
}

struct ID_EX* instruction_decode(struct IF_ID* if_id) {
    struct ID_EX *id_ex = (struct ID_EX*)malloc(sizeof(struct ID_EX));
    id_ex->control_signal = (char *)malloc(sizeof(char)*strlen(r_control));
    if (strcmp(if_id->instr, "00000000000000000000000000000000") == 0) {
        id_ex->rs = 0;
        id_ex->rt = 0;
        id_ex->rd = 0;
        id_ex->rs_v = 0;
        id_ex->rt_v = 0;
        id_ex->addr = 0;
        id_ex->funct = 0;
        strcpy(id_ex->control_signal, "000000000");
        id_ex->control_signal[9] = '\0';
        return id_ex;
    }
    // op code
    strncpy(op, if_id->instr, 6);
    strncpy(rs, if_id->instr + 6, 5);
    strncpy(rt, if_id->instr + 11, 5);
    strncpy(rd, if_id->instr + 16, 5);
    strncpy(addr, if_id->instr + 16, 16);
    strncpy(funct, if_id->instr + 26, 6);
    op[6] = '\0';
    rs[5] = '\0';
    rt[5] = '\0';
    rd[5] = '\0';
    addr[16] = '\0';
    funct[6] = '\0';
    
    id_ex->rs = bin2dec(rs);
    id_ex->rt = bin2dec(rt);
    id_ex->rd = bin2dec(rd);
    id_ex->addr = bin2dec(addr);
    id_ex->funct = bin2dec(funct);
    id_ex->rs_v = registers[id_ex->rs];
    id_ex->rt_v = registers[id_ex->rt];
    
    if (strcmp(op, r_op) == 0) {
        // r-type
        strcpy(id_ex->control_signal, r_control);
    } else if (strcmp(op, lw_op) == 0) {
        strcpy(id_ex->control_signal, lw_control);
    } else if (strcmp(op, sw_op) == 0) {
        strcpy(id_ex->control_signal, sw_control);
    } else if (strcmp(op, addi_op) == 0){
        strcpy(id_ex->control_signal, addi_control);
    } else if (strcmp(op, andi_op) == 0) {
        strcpy(id_ex->control_signal, andi_control);
    } else if (strcmp(op, beq_op) == 0) {
        strcpy(id_ex->control_signal, beq_control);
    } else if (strcmp(op, bnq_op) == 0) {
        strcpy(id_ex->control_signal, bnq_control);
    }

    return id_ex;
}
