typedef unsigned int u32; typedef int s32;
struct Q { virtual void f0(void* p, u32 z); };
struct Sub134 { char pad0[0x44]; u32 m44; Q* m48; char pad4c[4]; };
struct Obj { char pad0[0x394]; Sub134 m394; };

void func_0049A02C(Obj* self, s32 flag);
void func_0010961C(void* p);
void func_00109698(void* p);

static inline void finishSub(Sub134* p, u32 z) {
    func_0010961C(p);
    Q* q = p->m48;
    if (q != 0) {
        q->f0(p, z);
    }
    p->m44 = z;
}

void func_004953F8(Obj* self, s32 flag) {
    func_0049A02C(self, flag);
    Sub134* p = &self->m394;
    if (flag) {
        finishSub(p, 3);
    } else {
        finishSub(p, 0);
    }
    func_00109698(p);
}
