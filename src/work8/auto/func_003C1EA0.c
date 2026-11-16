typedef unsigned int u32;
typedef unsigned char u8;

extern char ro_006DE858[];
extern void func_0010F1F8(void*);
extern void* func_001E6CE8(void*);
extern void* func_004A1520(void*);

void* func_003C1EA0(void* self) {
    u8* base = (u8*)self;
    *(void**)base = ro_006DE858;
    u8* node = base + 0x10;
    u8* owner = *(u8**)(node + 0xc);
    if (owner) {
        *(u8**)(node + 0xc) = 0;
        func_0010F1F8(node);
        u32* cnt = (u32*)(owner + 8);
        *cnt = *cnt - 1;
    }
    u8* sub = (u8*)func_001E6CE8(base + 0xcc);
    return func_004A1520(sub - 0xcc);
}
