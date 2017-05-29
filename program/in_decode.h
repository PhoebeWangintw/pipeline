#ifndef IN_DECODE_H
#define IN_DECODE_H

struct ID_EX* instruction_decode(struct MEM_WB* mem_wb, struct EX_MEM *ex_mem,
                                 struct IF_ID* if_id);
void in_decode_print(struct ID_EX* id_ex);

#endif