#ifndef STRUCT_H
#define STRUCT_H

/* IF/ID */
struct IF_ID {
	int PC;
	char *instr;
} *if_id;

/* ID/EX */
struct ID_EX {
	int rs;
	int rt;
	int rd;
	int addr;
	int funct;
	char *control_signal;
} *id_ex;

/* EX/MEM */
struct EX_MEM {
	int rs;
	int rt_rd;
	int ALUOut;
	int WriteData;
	char *control_signal;
} *ex_mem;

/* MEM/WB */
struct MEM_WB {
	int rt_rd;
	int ALUOut;
	char *control_signal;
} *mem_wb;

#endif