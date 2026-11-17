typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;

typedef struct Obj Obj;
typedef struct Vt {
    void (*f0)(void*);
    void (*f1)(void*);
    void (*f2)(void*);
    void (*f3)(void*);
    void* f4;
} Vt;
struct Obj {
    Vt* vt;
    u8 p4[9];
    u8 b13;
    u8 b14;
    u8 p0f[0xd];
    Obj* m1c;
    u32 m20;
    u8 p24[0xc];
    u8 m30;
};
typedef struct Self {
    u8 p0[0x1c];
    s32 m1c;
    u8 p20[4];
    Obj** m24;
    u8 p28[0x74 - 0x28];
    Obj* m74;
    u8 p78[8];
    void* m80;
    void* m84;
} Self;

extern int func_0051E300(void* p);
extern void func_0012C85C(void* p);
extern void func_00232750(void* p);
extern void func_002326C0(void* p, u32 v);
extern void func_002327BC(void* p, u32 v);

void func_0038A948(Self* s)
{
    Obj* a = s->m74;
    if (func_0051E300(a)) {
        a->vt->f3(a);
    }
    func_0012C85C(s);
    u32 sb = 0;
    u32 r8 = 0;
    func_00232750(s->m80);
    func_00232750(s->m84);
    Obj** it = s->m24;
    Obj** end = s->m24 + s->m1c;
    for (; it != end; it++) {
        Obj* o = *it;
        if (func_0051E300(o)) {
            o->vt->f3(o);
        }
        Obj* p = ((*it)->b13 || (*it)->b14) ? (*it)->m1c : 0;
        if (p) {
            void* q = p->vt->f4;
            if (q && (((u8*)q)[0x44] & 1)) {
                if ((*it)->m30 == 0) {
                    if (r8 == 0) {
                        r8 = (*it)->m20;
                        func_002327BC(s->m84, r8);
                    } else {
                        func_002326C0(s->m84, (*it)->m20);
                    }
                } else {
                    if (sb == 0) {
                        sb = (*it)->m20;
                        func_002327BC(s->m80, sb);
                    } else {
                        func_002326C0(s->m80, (*it)->m20);
                    }
                }
            }
        }
    }
}
