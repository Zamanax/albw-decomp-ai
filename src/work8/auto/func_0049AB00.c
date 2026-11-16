typedef unsigned int u32;
typedef int s32;

extern void func_005FF418(void* p);
extern void func_006003D8(u32 k, u32* out);
extern void func_006017F0(u32 v);
extern void func_00601600(void);
extern void func_005FF760(void);
extern void func_005FEF2C(u32 n);
extern void func_005FF5DC(void* o);

struct Obj {
    char p0[0x124];
    s32 m124;
    void* a128[3];
    char p1[0x148 - 0x134];
    s32 m148;
    s32 m14c;
};

void func_0049AB00(struct Obj* self) {
    s32 idx;
    if (self->m14c <= 0) return;
    idx = 1 - self->m148;
    func_005FF418(self->a128[idx]);
    {
        u32 v;
        func_006003D8(0x201, &v);
        if (v != 0) func_006017F0(v);
    }
    func_00601600();
    func_005FF760();
    {
        s32 k = (self->m124 + 2) % 3;
        void** q;
        func_005FEF2C(0x400);
        q = (void**)((char*)self + k * 4);
        func_005FF5DC(q[0x130 / 4]);
        func_005FEF2C(0x401);
        func_005FF5DC(q[0x13c / 4]);
    }
    func_005FF418(self->a128[self->m148]);
}
