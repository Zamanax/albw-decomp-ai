#include "cp15.h"
#include "range.h"
extern "C" void func_0010BFD4(RecursiveLock12*);
extern "C" void func_0010C0C0(RecursiveLock12* p) {
    u32 current;
    current = tls_tp;u32 owner=p->owner;
    if(current!=owner) {
        func_0010BFD4(p);
        current = tls_tp;p->owner=current;
    }
    ++p->count;
}
