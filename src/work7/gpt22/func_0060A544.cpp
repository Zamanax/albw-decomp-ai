#include "range.h"

#include "sead_heap.h"
void* operator new(unsigned,NoThrow) throw();
struct Object_004BC368{u8 data[0x450];Object_004BC368(void*);};
Object_004BC368* target(void* arg){return new((NoThrow())) Object_004BC368(arg);}

