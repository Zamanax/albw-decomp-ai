typedef unsigned int u32;
typedef int s32;

typedef struct Obj {
    void** vt;
    u32 m4;
    u32 m8;
    u32 mc;
    u32 m10;
} Obj;

u32 func_003D0B10(Obj* o) {
    u32 local;
    ((u32 (*)(Obj*, u32, u32, u32, u32*))o->vt[2])(o, o->m4, 10, 8, &local);
    u32 r = ((u32 (*)(Obj*, u32*, u32, u32, u32, u32))o->vt[12])(o, &o->m10, 0x18c, o->m4, 1, 0x14);
    u32 s = r >> 31;
    if (s == 0) {
        r = ((u32 (*)(Obj*, u32*, u32, u32*, u32, u32, u32))o->vt[13])(o, &o->m10, 0x18c, &local, o->m4, 1, 0x12);
    }
    return r;
}
