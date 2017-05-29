#ifndef STRUCT_H
#define STRUCT_H

/* IF/ID */
struct IF_ID {
	int PC;
	int rs;
	int rt;
	char *instr;
};

/* ID/EX */
struct ID_EX {
	int rs;
	int rt;
	int rd;
	int rs_v;
	int rt_v;
	int addr;
	int funct;
	char *control_signal;
};

/* EX/MEM */
struct EX_MEM {
	int rt_rd;
	int ALUOut;
	int WriteData;
	char *control_signal;
};

/* MEM/WB */
struct MEM_WB {
	int rt_rd;
	int ALUOut;
	int ReadData;
	char *control_signal;
};

#endif