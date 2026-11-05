
#include "static_init.h"



struct Obj {
    unsigned m0;
    PtrListAssign<0x40> mList;
    Obj();
};
Obj::Obj() : m0(0) {}
