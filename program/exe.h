#ifndef EXE_H
#define EXE_H

//struct EX_MEM* execution(struct ID_EX* id_ex);
struct EX_MEM* execution(struct ID_EX* id_ex, struct MEM_WB* mem_wb);
void exe_print(struct EX_MEM* ex_mem);

#endif