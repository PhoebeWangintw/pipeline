/* instruction decode */
/* 1. 16-bit immediate field -> sign-extended to 32 bit
   2. read two register (rs, rt)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int registers[];
extern char *r_control;
extern char *lw_control;
extern char *sw_control;
extern char *addi_control;
extern char *andi_control;
extern char *beq_control;
extern char *bnq_control;
extern char *control_signal_e;

/* R-type */
/* add, sub, or, slt */
/* op: 6(0), rs: 5, rt: 5, rd: 5, shamt: 5, funct: 6(ALU instruction) */
/* R-type rd, rs, rt */

/* I-type */
/* lw, sw, addi */
/* op: 6, rs: 5, rt: 5, address: 16 */
/* I-type rt, addr(rs) */

/*  */

extern int rs_v, rt_v, rd_v, addr_v, funct_v;
char op[6];
char rs[5];
char rt[5];
char rd[5];
char funct[6];
char addr[16];
char *r_op = "000000";
char *lw_op = "100011";
char *sw_op = "101011";
char *beq_op = "000100";
char *bnq_op = "000101";
char *addi_op = "001000";
char *andi_op = "001100";

void in_decode_print() {
    printf("ID/EX :\n");
    printf("ReadData1\t%d\n", registers[rs_v]);
    printf("ReadData2\t%d\n", registers[rt_v]);
    printf("sign_ext\t%d\n", addr_v);
    printf("Rs\t\t%d\n", rs_v);
    printf("Rt\t\t%d\n", rt_v);
    printf("Rd\t\t%d\n", rt_v);
    printf("Control signals\t%s\n", control_signal_e);
}

int bin2dec(char *bin) {
    int i;
    int decimal = 0;
    for (i = 0; i < strlen(bin); ++i) {
        decimal *= 2;
        if (bin[i] == '1') 
            decimal += 1;
    }
    return decimal;
}

void instruction_decode(char *instr) {
    // op code
    strncpy(op, instr, 6);
    strncpy(rs, instr + 6, 5);
    strncpy(rt, instr + 11, 5);
    strncpy(rd, instr + 16, 5);
    strncpy(funct, instr + 26, 6);
    strncpy(addr, instr + 16, 16);
    // TODO: check if rd == $0
    rs_v = bin2dec(rs);
    rt_v = bin2dec(rt);
    rd_v = bin2dec(rd);
    addr_v = bin2dec(addr);
    funct_v = bin2dec(funct);
    
    control_signal_e = (char *)malloc(sizeof(char)*strlen(r_control));
    if (strcmp(op, r_op) == 0) {
        // r-type
        strcpy(control_signal_e, r_control);
    } else if (strcmp(op, lw_op) == 0) {
        strcpy(control_signal_e, lw_control);
    } else if (strcmp(op, sw_op) == 0) {
        strcpy(control_signal_e, sw_control);
    } else if (strcmp(op, addi_op) == 0){
        strcpy(control_signal_e, addi_control);
    } else if (strcmp(op, andi_op) == 0) {
        strcpy(control_signal_e, andi_control);
    } else if (strcmp(op, beq_op) == 0) {
        strcpy(control_signal_e, beq_control);
    } else if (strcmp(op, bnq_op) == 0) {
        strcpy(control_signal_e, bnq_control);
    }
}
