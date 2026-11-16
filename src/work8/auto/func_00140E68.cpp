struct Elem { char p0[0x48]; unsigned int m48; };
struct Lst { char p0[0x20]; unsigned int m20; char p1[0x28 - 0x24]; struct Elem** m28; };
struct Obj {
    char p0[0x2d7];
    unsigned char m2d7;
    char p1[0x40c - 0x2d8];
    struct Lst* m40c;
    char p2[0x4f8 - 0x410];
    unsigned int m4f8;
    char p3[0x504 - 0x4fc];
    unsigned int m504;
};
extern "C" void func_0013FC48(struct Obj* o);

extern "C" void func_00140E68(struct Obj* o) {
    if (o->m504 != 0) {
        o->m504 = o->m504 - 1;
        if (o->m504 != 0) return;
    }
    Obj * t2 = o;
    t2->m4f8 = o->m4f8 + 1;
    struct Lst* l = o->m40c;
    Lst * t1 = l;
    unsigned int t0 = t1->m20;
    if (t0 == o->m4f8) {
        func_0013FC48(o);
        return;
    }
    if (0 != t1->m28 && o->m4f8 < t1->m20) {
        struct Elem* e = l->m28[o->m4f8];
        if (e != 0) {
            o->m504 = e->m48;
            return;
        }
    }
    o->m2d7 = 1;
}
