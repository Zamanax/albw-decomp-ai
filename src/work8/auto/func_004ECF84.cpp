#include "../../work7/gpt30/npc_exec136.h"
struct NpcX {u8 pad0[0x568];NpcExecState30 state;};
NpcX* func_004ED008(NpcX*);
NpcX* target(NpcX*p){p->state.execute();return func_004ED008(p);}
