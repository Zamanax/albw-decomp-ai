typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern "C" int func_0052E8A0(void*);
extern "C" int func_0053FD30(void*, int);
extern "C" void* func_002D55D0(void*, int);
int func_00291C30(char* self, char* a1, u32 a2) {
    if (func_0052E8A0(*(void**)(self + 0x10)) != 0) return 0;
    if (func_0053FD30(self, 0) == 0) return 0;
    char* r = (char*)func_002D55D0(*(void**)(self + 0x48), 0x85);
    if (!r) return 0;
    *(u32*)(r + 8) = a2;
    *(u8*)(r + 5) = 0;
    char* p = self + 0x154;
    u8 kind = *(u8*)a1;
    s16 id = *(s16*)(a1 + 8);
    u32 word = *(u32*)(a1 + 4);
    *(u8*)p = kind;
    *(u32*)(p + 4) = word;
    *(s16*)(p + 8) = id;
    *(u8*)(p + 0xa) = 1 + ((s32)id >> 31);
    return 1;
}
