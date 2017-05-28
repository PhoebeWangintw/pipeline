/* execution */
/* 1. Add using ALU
   2. Read control signals to decide which action to take.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char *control_signal_e;
extern char *control_signal_m;
extern int rs_v, rt_v, rd_v, addr_v, funct_v;
extern int ALUOut, WriteData;

void exe_print() {
    // TODO: handle Rt/Rd register
    printf("\nEX/MEM :\n");
    printf("ALUOut\t\t%d\n", ALUOut);
    printf("WriteData\t%d\n", WriteData);
    printf("Rt/Rd\t\n");
    printf("Control signals\t%s\n", control_signal_m);
}

/* funct: */
const int add_funct = 32;
const int sub_funct = 34;
const int and_funct = 36;
const int or_funct = 37;
const int slt_funct = 42;

void execution() {
    char ALUOp[2];
    char *control_bits;
    control_signal_m = (char *)malloc(sizeof(char) * 6);
    strncpy(control_signal_m, control_signal_e + 4, 5);
    control_signal_m[5] = '\0';
    ALUOp[0] = control_signal_e[1];
    ALUOp[1] = control_signal_e[2];
    if (strcmp(ALUOp, "10") == 0) {
        /* r-type, see func */
        switch(funct_v) {
            case add_funct:
                ALUOut = rs_v + rt_v;
                break;
            case sub_funct:
                ALUOut = rs_v - rt_v;
                break;
            case and_funct:
                ALUOut = rs_v & rt_v;
                break;
            case or_funct:
                ALUOut = rs_v | rt_v;
                break;
            case slt_funct:
                if (rs_v < rt_v) ALUOut = 1;
                else ALUOut = 0;
                break;
            default:
                printf("cannot recognize function value!!!!!!!!!!!!!!!!!!!");
                break;
        }
    } else if (strcmp(ALUOp, "00") == 0) {
        /* lw or sw -> rs + addr*/
        ALUOut = rs_v + addr_v;
    } else if (strcmp(ALUOp, "11")) {
        /* andi */
    } else if (strcmp(ALUOp, "01") == 0) {
        /* branch */
        // TODO: check if is rt - rs
        ALUOut = rt_v - rs_v;
    }
    WriteData = rt_v;
}