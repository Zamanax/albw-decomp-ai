extern void func_001B6C2C(void *);
extern void func_001B6A48(void *);

struct T00474728 {
    void *vt;
    unsigned char pad[0x7c];
    unsigned int m80;
    unsigned int m84;
    unsigned int m88;
    unsigned char m8c;
};

void func_00474728(void *self, unsigned int *src, unsigned int arg2, unsigned int flag)
{
    struct T00474728 *o = (struct T00474728 *)self;
    unsigned int *p = &o->m80;
    p[0] = src[0];
    p[1] = src[1];
    o->m88 = arg2;
    o->m8c = 1;
    void **vt = (void **)o->vt;
    void (*fp)(void *) = (void (*)(void *))vt[19];
    fp(self);
    func_001B6C2C(self);
    if (!flag) {
        func_001B6A48(self);
    }
}
