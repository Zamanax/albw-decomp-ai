typedef unsigned int u32;
typedef unsigned char u8;

extern u32 func_0056D38C(void* p);

struct Inner00569C64 {
    void** vt;
    u8 flag;
};

struct Self00569C64 {
    u32 m0;
    void* m4;
    struct Inner00569C64* m8;
};

typedef void (*VFn00569C64)(struct Inner00569C64*, u32);

u32 func_00569C64(struct Self00569C64* self, u32 arg) {
    u32 r = func_0056D38C(self->m4);
    struct Inner00569C64* o = 0;
    if (r) o = self->m8;
    if (o) {
        u32 a = arg;
        if (o->flag) {
            VFn00569C64 fn = (VFn00569C64)o->vt[10];
            fn(o, a);
        }
        return 1;
    }
    return r;
}
