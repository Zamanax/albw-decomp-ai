typedef unsigned int u32;
typedef int s32;
typedef signed char s8;
typedef unsigned char u8;

extern void func_002ADE0C(void*, u32);
extern void func_004FBCC0(void*);
extern void func_002AD658(void*, s32, s32, s32, s32, s32);

void func_002AF84C(char* self, u32 arg)
{
    func_002ADE0C(self, arg);
    func_004FBCC0(*(void**)(self + 0x34));
    s8* q = (s8*)(self + 0x100);
    func_002AD658(self, 5, (u8)arg, q[0x10], q[0x11], 1);
}
