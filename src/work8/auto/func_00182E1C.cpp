#include "../../work7/gpt20/ladder_types.h"
struct MinigameLoc { char pad0[0x70]; u8 m70; };
extern MinigameLoc* data_0070D858;
extern "C" void func_00182E1C(O4DBA* p) {
    u8 k = data_0070D858->m70;
    if (k == 4)
        p->dispatch(4, -1);
    else
        p->dispatch(0, -1);
}
