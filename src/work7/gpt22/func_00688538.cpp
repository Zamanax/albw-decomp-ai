#include "range.h"
void*operator new(u32,void*,s32)throw();

#include "sead_string.h"

struct Object{u8 storage[0x210];Object(FactoryArg22*,const SafeString&);};
Object*target(FactoryArg22*p){return new(p->list->heaps[p->list->index],4)Object(p,SafeString("CapFader_UraOmote"));}
