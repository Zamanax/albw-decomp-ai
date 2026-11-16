typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef float f32;

extern int func_0058A8F0(void*);
extern void* func_00161178(void*);
extern f32 func_0058A404(void*);
extern void func_0065836C(void*, s32);

void func_0015E2F0(u8* self) {
    if (!func_0058A8F0(self)) return;
    u8* p = self + 0x8bc;
    s16 v = *(s16*)(self + 0x508);
    if (v <= 0) {
        func_0065836C(p, 0x14);
        return;
    }
    if (self[0xe2c] != 0) {
        func_0065836C(p, 4);
        return;
    }
    void* q = func_00161178(self);
    if (q == 0) {
        func_0065836C(p, 0x19);
        return;
    }
    f32 r = func_0058A404(q);
    if (r <= 0.6f) {
        func_0065836C(p, 0x19);
        return;
    }
    func_0065836C(p, 4);
}
