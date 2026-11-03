#include "../../work7/gpt29/range.h"
struct TaggedEntry56A { u16 tag,reserved; s32 offset; };
struct TaggedTable56A { u32 count; TaggedEntry56A entries[1]; };
struct Owner56A2F0 { char pad[0x14]; s32 offset; };
void* func_0056A2F0(Owner56A2F0* p,u32 index){TaggedTable56A* table=(TaggedTable56A*)((char*)p+p->offset);u32 key=0x4902;if(index<table->count){if(table->entries[index].tag==key)return(char*)table+table->entries[index].offset;}return 0;}
