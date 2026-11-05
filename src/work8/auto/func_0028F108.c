typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

extern void* func_002D5C70(void* self);
extern char ro_006DA464[];
extern u32 data_00711120[];

void* func_0028F108(void* self) {
    u8* p = (u8*)func_002D5C70(self);
    *(u32*)(p + 0x70) = 0;
    *(void**)p = ro_006DA464;
    *(u32*)(p + 0x74) = 0;
    *(u32*)(p + 0x78) = 0;
    *(u8*)(p + 0x7c) = 0;
    *(u8*)(p + 0x7d) = 0;
    *(u16*)(p + 0x80) = (u16)-1;
    *(u32*)(p + 0x84) = 0;
    *(u32*)(p + 0x88) = 0;
    u32 v = data_00711120[1];
    *(u32*)(p + 0x90) = 0;
    *(u32*)(p + 0x8c) = v;
    return p;
}
