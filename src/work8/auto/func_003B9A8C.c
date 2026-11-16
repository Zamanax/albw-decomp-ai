typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;
typedef float f32;

struct Sub { u8 pad[4]; u8 b4; };
struct Inner { u8 pad0[0x8bc]; struct Sub* m8bc; u8 pad1[0x936 - 0x8c0]; u8 m936; };
struct Vt { u8 pad0[0x130]; int (*f130)(void*); u8 pad1[0xc]; int (*f140)(void*); };
struct Self { struct Vt* vt; u8 pad0[0x44]; struct Inner* m48; u32 m4c; f32 m50; };

extern void* func_0058A7D4(void* a);
extern u32 func_00111A64(void* self);
extern int func_005430D4(void* a);
extern int func_00542F3C(void* a);

static u32 below(void* self, u32 n)
{
    return (u32)(((u64)func_00111A64(self) * n) >> 32);
}

void func_003B9A8C(struct Self* p)
{
    p->m4c = below(func_0058A7D4(p->m48), 61u) + 60u;
    if (func_005430D4(p->m48)) {
        if (func_00542F3C(p->m48)) {
            p->m4c = 60u;
        }
    }
    if (p->vt->f140(p)) {
        p->vt->f130(p);
    }
    if (p->m48->m936 == 2) {
        p->m4c = below(func_0058A7D4(p->m48), 31u) + 30u;
        p->m50 = (p->m48->m8bc->b4 != 0) ? 4.5f : 2.0f;
    }
}
