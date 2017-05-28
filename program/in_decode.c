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
extern char *beq_control;
extern char control_signal[9];

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

extern int rs_r, rt_r, rd_r, addr_v;
char op[6];
char rs[5];
char rt[5];
char rd[5];
char funct[6];
char addr[16];
char *r_op = "000000";
char *lw_op = "100011";
char *sw_op = "101011";
char *addi_op = "001000";

void in_decode_print() {
    printf("ID/EX :\n");
    printf("ReadData1\t%d\n", registers[rs_r]);
    printf("ReadData2\t%d\n", registers[rt_r]);
    printf("sign_ext\t%d\n", addr_v);
    printf("Rs\t\t%d\n", rs_r);
    printf("Rt\t\t%d\n", rt_r);
    printf("Rd\t\t%d\n", rt_r);
    printf("Control signals\t%s\n", control_signal);
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
    rs_r = bin2dec(rs);
    rt_r = bin2dec(rt);
    rd_r = bin2dec(rd);
    addr_v = bin2dec(addr);
    
    if (strcmp(op, r_op) == 0) {
        // r-type
        strncpy(control_signal, r_control, 9);
    } else if (strcmp(op, lw_op) == 0) {
        strncpy(control_signal, lw_control, 9);
    } else if (strcmp(op, sw_op) == 0) {
        strncpy(control_signal, sw_control, 9);
    } else {
        strncpy(control_signal, addi_control, 9);
    }
}
