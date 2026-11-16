struct Q { char a[0xc]; unsigned int c; };
struct Ent {
    void *link;
    char a4[4];
    void *p8;
    char a0c[0x14];
    unsigned short h20;
    char a22[0x0c];
    unsigned char b2e;
    char a2f[3];
    unsigned short h32;
    char a34[9];
    unsigned char b3d;
    char a3e[2];
    unsigned char b40;
};
struct Mgr {
    void **vt;
    char a4[0x110];
    char node[0x14];
    struct Ent *cur;
};
struct Obj {
    char a0[0x14];
    struct Q *q;
    char a18[0x5c];
    struct Mgr *mgr;
    unsigned char flag;
};

void func_00425C38(struct Obj *o, struct Ent *e)
{
    struct Mgr *m = o->mgr;
    if (m != 0) {
        if (e != 0) {
            unsigned int z = 0;
            m->cur = e;
            char *node = o->mgr->node;
            *(void **)e = node;
            *(struct Ent **)(node + 0x14) = e;
            m = o->mgr;
            e->h32 = z;
            e->b3d = z;
            ((void (*)(struct Mgr *, void *, unsigned int, unsigned int))m->vt[24])(m, e->p8, z, (unsigned int)e->h20 >> 1);
            unsigned int f;
            if (e->b2e != 0 && e->b40 == 0) f = 0;
            else f = 1;
            o->flag = f;
            struct Q *q = o->q;
            q->c = f ? 1 : 3;
        }
    }
}
