typedef unsigned int u32;
typedef unsigned char u8;

extern u8 ro_006F05FC[];

struct Obj {
    void* vt;
    u8 flag;
    u8 pad0[7];
    u32 f0c;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 f1c;
    u32 f20;
    u32 f24;
};
void func_00410AB8(struct Obj* p, unsigned v) {
    void* vt = ro_006F05FC;
    u32 z = 0;
    struct Obj * t0 = p;
    p->f0c = z;
    t0->f10 = z;
    t0->vt = vt;
    t0->f14 = v;
    t0->f18 = z;
    struct Obj * t1 = p;
    t0->f1c = z;
    t0->f20 = 0xffffffffu;
    t1->f24 = 0xffffffffu;
    t1->flag = 1;
}
