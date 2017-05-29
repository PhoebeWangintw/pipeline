#ifndef DATAHAZARD_H
#define DATAHAZARD_H

int lwDetect(struct ID_EX *id_ex, struct IF_ID *if_id);
int exHazard(struct EX_MEM *ex_mem, struct ID_EX *id_ex);
int memHazard(struct MEM_WB *mem_wb, struct EX_MEM *ex_mem,struct ID_EX *id_ex);
void checkHazard(struct MEM_WB *mem_wb, struct EX_MEM *ex_mem, struct ID_EX *id_ex, struct IF_ID *if_id);

#endif